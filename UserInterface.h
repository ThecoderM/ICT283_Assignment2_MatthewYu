#ifndef USERINTERFACE_H_INCLUDED
#define USERINTERFACE_H_INCLUDED
#include "WeatherLog.h"
#include <string>
/**
 * @class UserInterface
 * @brief Provides console-based user interface functionality.
 *
 * The UserInterface class encapsulates all presentation-layer logic
 * for the program, including menu handling, user input validation,
 * and display-related helper functions.
 *
 * All functions are static because no object state is required.
 */
class UserInterface
{
public:
     /**
     * @brief Displays the main menu and executes selected options.
     *
     * Continuously prompts the user for menu selections until
     * the user chooses to exit. Calls appropriate analytics
     * functions based on user input.
     *
     * @param log Const reference to the loaded WeatherLog dataset.
     */
    static void RunMenu(const WeatherLog& log);
     /**
     * @brief Returns the month name corresponding to an integer value.
     *
     * Converts a numeric month (1-12) into its textual name.
     *
     * @param m Integer month value (1-12).
     * @return const char* Name of the month, or empty string if invalid.
     */
    static const char* MonthName(int m);
    /**
     * @brief Reads and validates an integer within a specified range.
     *
     * Prompts the user for input and ensures the value entered
     * is numeric and within the given bounds. Re-prompts until valid.
     *
     * @param prompt Message displayed to the user.
     * @param out Reference variable where the valid integer is stored.
     * @param minVal Minimum acceptable value.
     * @param maxVal Maximum acceptable value.
     * @return true when a valid value has been entered.
     */
    static bool ReadIntInRange(const string& prompt, int& out, int minVal, int maxVal);
    /**
     * @brief Executes menu option 1.
     *
     * Calculates and displays the average wind speed and
     * sample standard deviation for a specified month and year.
     *
     * @param log The loaded WeatherLog containing weather records.
     */
    static void Choice_One(const WeatherLog& log);
    /**
     * @brief Executes menu option 2.
     *
     * Calculates and displays the monthly average ambient air
     * temperature and sample standard deviation for a specified year.
     *
     * @param log The loaded WeatherLog containing weather records.
     */
    static void Choice_Two(const WeatherLog& log);
    /**
     * @brief Executes menu option 3.
     *
     * Calculates and displays the Sample Pearson Correlation Coefficient (SPCC)
     *
     * @param log The loaded WeatherLog containing weather records.
     */
    static void Choice_Three(const WeatherLog& log);
    /**
     * @brief Executes menu option 4.
     *
     * Generates a combined monthly report including:
     * wind speed statistics, temperature statistics,
     * and solar radiation totals, Mean Absolute Deviation
     * Results are displayed and written to WindTempSolar.csv.
     *
     * @param log The loaded WeatherLog containing weather records.
     */
    static void Choice_Four(const WeatherLog& log);

};

#endif // USERINTERFACE_H_INCLUDED
