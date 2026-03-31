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

    static Vector<WeatherRecord> FilterMonth(const WeatherLog& log, int month);

    static void ExtractSTPairs(const Vector<WeatherRecord>& rows, Vector<double>& s, Vector<double>& t);
    static void ExtractSRPairs(const Vector<WeatherRecord>& rows, Vector<double>& s, Vector<double>& r);
    static void ExtractTRPairs(const Vector<WeatherRecord>& rows, Vector<double>& t, Vector<double>& r);
};

#endif // WEATHERANALYTICS_H_INCLUDED
