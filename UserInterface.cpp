#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

#include "WeatherLog.h"
#include "Math.h"
#include "Vector.h"
#include "Date.h"
#include "Time.h"
#include "WeatherRecord.h"
#include "WeatherAnalytics.h"
#include "UserInterface.h"
using std::stringstream;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::ofstream;
using std::cin;
using std::fixed;
using std::setprecision;

void UserInterface::RunMenu(const WeatherLog& log)
{
    while (true) // Keep showing menu until user exits
    {
        cout << "\n===== MENU =====\n"; // Print menu header
        cout << "1) Calculate average wind speed and sample standard deviation given a specified month and year\n";
        cout << "2) Calculate Average ambient air temperature and sample standard deviation for each month of a specified year\n";
        cout << "3) Calculate the sample Pearson Correlation Coefficient\n";
        cout << "4) Calculate Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m^2 for each   month of a specified year (Print to a file called WindTempSolar.csv).\n";
        cout << "5) Exit\n";

        int choice; // Store menu choice
        ReadIntInRange("Choice (1-5): ", choice, 1, 5); // Validate input (1..5)

        if (choice == 5) break;  // Exit menu loop if user chooses 5

        if (choice == 1)
        {
            Choice_One(log); // call the choice 1 function
        }
        else if (choice == 2)
        {
            Choice_Two(log); // call the choice 2 function
        }
        else if (choice == 3)
        {
            Choice_Three(log); // call the choice 3 function
        }
        else if (choice == 4)
        {
            Choice_Four(log); // call the choice 4 function
        }
    }


}
void UserInterface::Choice_One(const WeatherLog& log)
{
    int month, year; // Store month and year inputs
    ReadIntInRange("Enter month (1-12): ", month, 1, 12); // Validate month
    ReadIntInRange("Enter year: ", year, 0, 9999); // Validate year

    Vector<WeatherRecord> rows = WeatherAnalytics::FilterMonthYear(log, month, year); // Filter matching records
    Vector<double> wind = WeatherAnalytics::ExtractWindKmh(rows); // Extract wind values (km/h)

    cout << MonthName(month) << " " << year << ":"; // Print heading for output

    if (wind.Size() == 0)   // Check if no valid wind data
    {
        cout << " No Data\n";
    }
    else
    {
        double mean = Math::Mean(wind); // Compute mean wind speed
        double sd   = Math::SampleStdDev(wind, mean); // Compute sample stdev

        cout << "\nAverage speed: " << fixed << setprecision(1) << mean << " km/h\n"; // Output mean
        cout << "Sample stdev: "  << fixed << setprecision(1) << sd << "\n"; // Output stdev
    }
}

void UserInterface::Choice_Two(const WeatherLog& log)
{
    int year; // Store year input
    ReadIntInRange("Enter year: ", year, 0, 9999); // Validate year

    cout << year << "\n"; // Print year heading

    for (int m = 1; m <= 12; m++)  // Loop through all months
    {
        Vector<WeatherRecord> rows = WeatherAnalytics::FilterMonthYear(log, m, year); // Filter month/year records
        Vector<double> temps = WeatherAnalytics::ExtractTempC(rows); // Extract valid temperature values

        cout << MonthName(m) << ": "; // Print month label

        if (temps.Size() == 0) // If no valid temperature data
        {
            cout << "No Data\n"; // Print "No Data"
        }
        else
        {
            double mean = Math::Mean(temps); // Compute mean temperature
            double sd   = Math::SampleStdDev(temps, mean); // Compute sample stdev

            cout << "average: " << fixed << setprecision(1) << mean
                 << " degrees C, stdev: " << fixed << setprecision(1) << sd << "\n"; // Print formatted output
        }
    }
}

void UserInterface::Choice_Three(const WeatherLog& log)
{
    int month;
    ReadIntInRange("Enter month (1-12): ", month, 1, 12);

    Vector<WeatherRecord> rows = WeatherAnalytics::FilterMonth(log, month);

    Vector<double> s1, t1;
    Vector<double> s2, r2;
    Vector<double> t3, r3;

    WeatherAnalytics::ExtractSTPairs(rows, s1, t1);
    WeatherAnalytics::ExtractSRPairs(rows, s2, r2);
    WeatherAnalytics::ExtractTRPairs(rows, t3, r3);

    cout << "Sample Pearson Correlation Coefficient for " << MonthName(month) << "\n";

    if (s1.Size() >= 2)
        cout << "S_T: " << fixed << setprecision(1) << Math::SPCC(s1, t1) << "\n";
    else
        cout << "S_T: No Data\n";

    if (s2.Size() >= 2)
        cout << "S_R: " << fixed << setprecision(1) << Math::SPCC(s2, r2) << "\n";
    else
        cout << "S_R: No Data\n";

    if (t3.Size() >= 2)
        cout << "T_R: " << fixed << setprecision(1) << Math::SPCC(t3, r3) << "\n";
    else
        cout << "T_R: No Data\n";
}

void UserInterface::Choice_Four(const WeatherLog& log)
{
    int year; // Store year input
    ReadIntInRange("Enter year: ", year, 0, 9999); // Validate year

    ofstream out("WindTempSolar.csv"); // Open output CSV file
    if (!out) // Check if file creation failed
    {
        cout << "Error: could not create WindTempSolar.csv\n";
        return;
    }


    bool wroteAnyMonth = false; // Tracks if any month is written


    for (int m = 1; m <= 12; m++) // Loop through months
    {
        Vector<WeatherRecord> rows = WeatherAnalytics::FilterMonthYear(log, m, year); // Filter records for month/year


        if (!WeatherAnalytics::MonthHasAnyData(rows)) // skip month if no data at all
            continue; // Move to next month

        if (!wroteAnyMonth) // If this is the first month with data
        {
            cout << year << "\n"; // Print year heading to console
            cout << "Month,Average Wind Speed(stdev, Mad),Average Ambient Temperature(stdev, Mad),Solar Radiation\n";

            out  << year << "\n"; // Print year heading to file
            out  << "Month,Average Wind Speed(stdev, Mad),Average Ambient Temperature(stdev, Mad),Solar Radiation\n";
            wroteAnyMonth = true; // Mark that we output something
        }

        Vector<double> wind = WeatherAnalytics::ExtractWindKmh(rows); // Extract wind (km/h)
        Vector<double> temp = WeatherAnalytics::ExtractTempC(rows); // Extract temperature (�C)
        double solarTotal = 0.0; // Solar total value holder
        bool hasSolar = WeatherAnalytics::SolarTotalKWhm2(rows, solarTotal); // Compute solar total if available


        cout << MonthName(m) << ","; // Start CSV line (console)
        out  << MonthName(m) << ","; // Start CSV line (file)

        // Wind field: mean(stdev) or blank
        if (wind.Size() > 0) // Only compute if wind values exist
        {
            double wMean = Math::Mean(wind);
            double wSd   = Math::SampleStdDev(wind, wMean);
            double wMad = Math::MeanAbsoluteDeviation(wind, wMean);
            cout << fixed << setprecision(1) << wMean << "(" << wSd << ", " << wMad << ")"; // Output wind field
            out  << fixed << setprecision(1) << wMean << "(" << wSd << ", " << wMad << ")"; // Write wind field
        }
        cout << ","; // Output comma separator
        out  << ","; // Write comma separator

        // Temp field: mean(stdev) or blank
        if (temp.Size() > 0) // Only compute if temperature values exist
        {
            double tMean = Math::Mean(temp);
            double tSd   = Math::SampleStdDev(temp, tMean);
            double tMad = Math::MeanAbsoluteDeviation(temp, tMean);

            cout << fixed << setprecision(1) << tMean << "(" << tSd << ", " << tMad << ")"; // Output temp field
            out  << fixed << setprecision(1) << tMean << "(" << tSd << ", " << tMad << ")"; // Write temp field
        }
        cout << ","; // Output comma separator
        out  << ","; // Write comma separator

        if (hasSolar)  // Only output if any SR >= 100 contributed
        {
            cout << fixed << setprecision(1) << solarTotal; // Output solar total
            out  << fixed << setprecision(1) << solarTotal; // write solar total
        }

        cout << "\n"; // End console line
        out  << "\n"; // End console line
    }

    // Requirement: if entire year has no data, output year then "No Data"
    if (!wroteAnyMonth)
    {
        cout << year << "\n";
        cout << "No Data\n";

        out  << year << "\n";
        out  << "No Data\n";
    }

    out.close(); // Close output file
    cout << "Written WindTempSolar.csv\n"; // Confirmation message
}

const char* UserInterface::MonthName(int m)
{
    static const char* names[] =  // Month lookup table
    {
        "", "January","February","March","April","May","June",
        "July","August","September","October","November","December"
    };

    return (m >= 1 && m <= 12) ? names[m] : "";  // Return valid month name or empty string
}

bool UserInterface::ReadIntInRange(const string& prompt, int& out, int minVal, int maxVal)
{
    while (true)  // Keep prompting until valid input is given
    {
        cout << prompt;  // Display input prompt
        if (cin >> out && out >= minVal && out <= maxVal) // Check numeric + range
            return true;

        cout << "Invalid input. Enter " << minVal << " to " << maxVal << ".\n"; // Show error message
        cin.clear();  // Clear input error state
        cin.ignore(9999, '\n');  // Discard remaining input in the line
    }
}
