#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <cmath>
#include "Vector.h"
#include "WeatherRecord.h"

/**
 * @class Math
 * @brief Provides static mathematical utility functions for weather data analysis.
 *
 *
 * It centralises all statistical and conversion calculations used by the program.
 *
 * Design Rationale:
 * - Keeps calculation logic separate from main() (separation of concerns).
 * - Keeps WeatherRecord as a data-only model class.
 * - Improves modularity and maintainability.
 */
class Math
{
public:
    /**
     * @brief Converts wind speed from metres per second (m/s) to kilometres per hour (km/h).
     *
     * @param speed_mps Wind speed in metres per second.
     * @return Wind speed converted to kilometres per hour.
     */
    static double MsToKmh(double speed_mps);
    /**
     * @brief Computes the arithmetic mean (average) of a set of values.
     *
     * @param values A Vector containing double values.
     * @return The mean of the values.
     *
     * If the vector is empty, behaviour depends on implementation
     * (typically returns 0.0).
     */
    static double Mean(const Vector<double>& values);
     /**
     * @brief Computes the sample standard deviation of a set of values.
     *
     * @param values A Vector containing double values.
     * @param mean The pre-computed mean of the values.
     * @return The sample standard deviation.
     *
     * Uses the sample formula:
     * sqrt( sum((x - mean)^2) / (n - 1) )
     */
    static double SampleStdDev(const Vector<double>& values, double mean);
    /**
     * @brief Converts solar radiation from W/m² (10-minute interval)
     *        into kWh/m².
     *
     * @param sr_wm2 Solar radiation value in W/m².
     * @return Converted value in kWh/m².
     *
     * The conversion accounts for the 10-minute measurement interval.
     */
    static double SolarWm2_10min_To_kWhm2(double sr_wm2);
    /**
     * @brief Computes the Sample Pearson Correlation Coefficient (SPCC) between two datasets.
     *
     * Measures the strength and direction of the linear relationship between two variables.
     * The result ranges from -1 to 1:
     * - 1   : perfect positive correlation
     * - 0   : no correlation
     * - -1  : perfect negative correlation
     *
     * Both input vectors must have the same size and contain at least two elements.
     *
     * @param x The first dataset.
     * @param y The second dataset.
     * @return The computed SPCC value.
     */
     static double SPCC(const Vector<double>& x, const Vector<double>& y);
     /**
     * @brief Computes the Mean Absolute Deviation (MAD) of a dataset.
     *
     * Calculates the average of the absolute differences between each value
     * and the provided mean.
     *
     * Formula:
     * MAD = (1/n) * Σ |value - mean|
     *
     * @param values The dataset of values.
     * @param mean The mean of the dataset.
     * @return The mean absolute deviation.
     */
     static double MeanAbsoluteDeviation(const Vector<double>& values, double mean);
};

#endif // MATH_H_INCLUDED

