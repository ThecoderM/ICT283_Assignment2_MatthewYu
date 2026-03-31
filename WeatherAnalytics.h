#ifndef WEATHERANALYTICS_H_INCLUDED
#define WEATHERANALYTICS_H_INCLUDED
#include "WeatherLog.h"
/**
 * @class WeatherAnalytics
 * @brief Provides statistical and filtering operations on weather data.
 *
 * This is a utility-style class containing only static methods.
 * It performs domain-specific analysis on collections of
 * WeatherRecord objects without modifying the underlying data.
 *
 * Responsibilities:
 * - Filtering records by month and year
 * - Extracting wind speed and temperature values
 * - Calculating total solar radiation for a month
 * - Checking if a month contains any valid data
 *
 *
 */
class WeatherAnalytics
{
public:
    /**
     * @brief Filters weather records by month and year.
     *
     * @param log WeatherLog containing all records.
     * @param month Month value (1�12).
     * @param year Year value (e.g., 2016).
     * @return Vector of WeatherRecord objects matching the specified month and year.
     */
    static Vector<WeatherRecord> FilterMonthYear(const WeatherLog& log, int month, int year);

     /**
     * @brief Extracts valid wind speeds (converted to km/h) from records.
     *
     * Only records with valid wind speed values are included.
     *
     * @param rows Vector of WeatherRecord objects.
     * @return Vector of wind speeds in km/h.
     */
    static Vector<double> ExtractWindKmh(const Vector<WeatherRecord>& rows);

     /**
     * @brief Extracts valid ambient air temperatures from records.
     *
     * Only records with valid temperature values are included.
     *
     * @param rows Vector of WeatherRecord objects.
     * @return Vector of temperatures in degrees Celsius.
     */
    static Vector<double> ExtractTempC(const Vector<WeatherRecord>& rows);

    /**
     * @brief Calculates total solar radiation in kWh/m^2 for a collection of records.
     *
     * Only solar radiation values greater than or equal to 100 W/m^2
     * contribute to the total (as per assignment requirement).
     *
     * @param rows Vector of WeatherRecord objects.
     * @param total Output parameter storing computed total solar energy.
     * @return true if at least one valid solar value contributed; otherwise false.
     */
    static bool SolarTotalKWhm2(const Vector<WeatherRecord>& rows, double& total);

    /**
     * @brief Determines whether a month contains any valid data.
     *
     * A month is considered to have data if at least one record contains
     * wind speed, temperature, or solar radiation.
     *
     * @param rows Vector of WeatherRecord objects.
     * @return true if any data exists; otherwise false.
     */
    static bool MonthHasAnyData(const Vector<WeatherRecord>& rows);

     /**
     * @brief Extracts Wind Speed and Ambient Temperature pairs for SPCC calculation.
     *
     * This function iterates through a collection of WeatherRecord objects and
     * extracts paired values of:
     * - Wind Speed (S)
     * - Ambient Temperature (T)
     *
     * These paired datasets are stored in separate vectors and are used as inputs
     * for the Sample Pearson Correlation Coefficient (SPCC) calculation.
     *
     * @param rows The collection of weather records.
     * @param s Output vector storing wind speed values.
     * @param t Output vector storing ambient temperature values.
     */
    static void ExtractSTPairs(const Vector<WeatherRecord>& rows, Vector<double>& s, Vector<double>& t);
    /**
     * @brief Extracts Wind Speed and Solar Radiation pairs for SPCC calculation.
     *
     * This function processes weather records and extracts paired values of:
     * - Wind Speed (S)
     * - Solar Radiation (R)
     *
     * The extracted values are stored in separate vectors and used to compute
     * the SPCC to determine the relationship between wind speed and solar radiation.
     *
     * @param rows The collection of weather records.
     * @param s Output vector storing wind speed values.
     * @param r Output vector storing solar radiation values.
     */
    static void ExtractSRPairs(const Vector<WeatherRecord>& rows, Vector<double>& s, Vector<double>& r);
    /**
     * @brief Extracts Ambient Temperature and Solar Radiation pairs for SPCC calculation.
     *
     * This function iterates through weather records and extracts paired values of:
     * - Ambient Temperature (T)
     * - Solar Radiation (R)
     *
     * These paired datasets are stored in vectors and used as input for SPCC
     * to evaluate the relationship between temperature and solar radiation.
     *
     * @param rows The collection of weather records.
     * @param t Output vector storing ambient temperature values.
     * @param r Output vector storing solar radiation values.
     */
    static void ExtractTRPairs(const Vector<WeatherRecord>& rows, Vector<double>& t, Vector<double>& r);
};

#endif // WEATHERANALYTICS_H_INCLUDED
