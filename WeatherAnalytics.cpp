#include "WeatherAnalytics.h"
#include "Math.h"

Vector<double> WeatherAnalytics::ExtractWindKmh(const Vector<WeatherRecord>& rows)
{
    Vector<double> v; // Store wind values in km/h

    for (int i = 0; i < rows.Size(); i++)
    {
        if (rows[i].GetHasSpeed()) // Only include records with valid speed
            v.Insert(Math::MsToKmh(rows[i].GetSpeed()), v.Size()); // Convert m/s to km/h and append
    }

    return v;
}

Vector<double> WeatherAnalytics::ExtractTempC(const Vector<WeatherRecord>& rows)
{
    Vector<double> v;  // Store temperature values
    for (int i = 0; i < rows.Size(); i++) // Loop through records
        if (rows[i].GetHasAmbientAirTemperature()) // Only include records with valid temperature
            v.Insert(rows[i].GetAmbientAirTemperature(), v.Size()); // Append temperature
    return v; // Return temperature vector
}

bool WeatherAnalytics::SolarTotalKWhm2(const Vector<WeatherRecord>& rows, double& total)
{
    total = 0.0;  // Initialise total solar energy
    bool any = false; // Track whether any valid SR contributes

    for (int i = 0; i < rows.Size(); i++) // Loop through records
    {
        if (rows[i].GetHasSolarRadiation()) // Only process if solar radiation is present
        {
            double add = Math::SolarWm2_10min_To_kWhm2(rows[i].GetSolarRadiation()); // Convert to kWh/m^2 for 10-min interval
            if (add > 0.0) // Only include SR >= 100 W/m^2 (conversion returns 0 below threshold)
            {
                total += add; // Add to total
                any = true;  // Mark that we have valid contribution
            }
        }
    }
    return any; // Return whether there was any valid solar data
}

bool WeatherAnalytics::MonthHasAnyData(const Vector<WeatherRecord>& rows)
{
    for (int i = 0; i < rows.Size(); i++) // Loop through all records for the month
    {   // Check if wind speed, temperature, solar radiation exists
        if (rows[i].GetHasSpeed() || rows[i].GetHasAmbientAirTemperature() || rows[i].GetHasSolarRadiation())
            return true; // Month has at least one data value
    }
    return false; // No values exist for this month
}

void WeatherAnalytics::ExtractSTPairs(const Vector<WeatherRecord>& rows, Vector<double>& s, Vector<double>& t)
{
    // Loop through all weather records
    for (int i = 0; i < rows.Size(); i++)
    {
        // Check if both wind speed and temperature are available in the record
        if (rows[i].GetHasSpeed() && rows[i].GetHasAmbientAirTemperature())
        {
            // Insert converted wind speed (m/s to km/h) into vector 's'
            s.Insert(Math::MsToKmh(rows[i].GetSpeed()), s.Size());
            // Insert ambient temperature into vector 't'
            t.Insert(rows[i].GetAmbientAirTemperature(), t.Size());
        }
    }
}

void WeatherAnalytics::ExtractSRPairs(const Vector<WeatherRecord>& rows, Vector<double>& s, Vector<double>& r)
{
    // Loop through all weather records
    for (int i = 0; i < rows.Size(); i++)
    {
        // Check if both wind speed and solar radiation are available
        if (rows[i].GetHasSpeed() && rows[i].GetHasSolarRadiation())
        {
            // Insert converted wind speed into vector 's'
            s.Insert(Math::MsToKmh(rows[i].GetSpeed()), s.Size());
            // Insert solar radiation value into vector 'r'
            r.Insert(rows[i].GetSolarRadiation(), r.Size());
        }
    }
}

void WeatherAnalytics::ExtractTRPairs(const Vector<WeatherRecord>& rows, Vector<double>& t, Vector<double>& r)
{
    // Loop through all weather records
    for (int i = 0; i < rows.Size(); i++)
    {
        // Check if both temperature and solar radiation are available
        if (rows[i].GetHasAmbientAirTemperature() && rows[i].GetHasSolarRadiation())
        {
            // Insert ambient temperature into vector 't'
            t.Insert(rows[i].GetAmbientAirTemperature(), t.Size());
            // Insert solar radiation into vector 'r'
            r.Insert(rows[i].GetSolarRadiation(), r.Size());
        }
    }
}


