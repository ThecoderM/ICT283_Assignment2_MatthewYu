#include "Math.h"  // Include corresponding header file for Math class

double Math::MsToKmh(double speed_mps) // Convert metres per second to kilometres per hour
{
    return speed_mps * 3.6;  // 1 m/s = 3.6 km/h (standard unit conversion)
}

double Math::Mean(const Vector<double>& values) // Compute arithmetic mean of values
{
    int n = values.Size(); // Compute arithmetic mean of values
    if (n == 0) return 0.0; // If no values, return 0.0 to avoid division by zero

    double sum = 0.0;  // Initialise accumulator for summation
    for (int i = 0; i < n; i++) sum += values[i]; // Loop through all elements Add each element to the running total
    return sum / n; // Return average (sum divided by count)
}

double Math::SampleStdDev(const Vector<double>& values, double mean) // Compute sample standard deviation
{
    int n = values.Size(); // Get number of elements
    if (n < 2) return 0.0;  // Sample standard deviation requires at least 2 values

    double acc = 0.0; // Accumulator for squared differences
    for (int i = 0; i < n; i++) // Loop through all elements
    {
        double diff = values[i] - mean; // Loop through all elements
        acc += diff * diff;  // Add squared difference to accumulator
    }
    return std::sqrt(acc / (n - 1));  // Apply sample standard deviation formula
}


double Math::SolarWm2_10min_To_kWhm2(double sr_wm2) // Convert solar radiation to kWh/m^2
{
    if (sr_wm2 < 100.0) return 0.0; // Ignore low values below threshold (assignment rule)
    return (sr_wm2 / 6.0) / 1000.0;  // Convert 10-minute W/m^2 reading to kWh/m^2
}                                    // Divide by 6 (10 minutes = 1/6 hour)
                                     // Divide by 1000 (W to kW conversion)


double Math::SPCC(const Vector<double>& x, const Vector<double>& y)
{
    int n = x.Size(); // Get number of elements in vector x

    // Check if vectors are valid:
    // - Must have at least 2 elements
    // - Both vectors must be the same size
    if (n < 2 || y.Size() != n)
        return 0.0;
    // Compute mean (average) of both datasets
    double meanX = Mean(x);
    double meanY = Mean(y);

    // Initialize accumulators:
    // sumXY - covariance numerator
    // sumX2 - variance of x
    // sumY2 - variance of y
    double sumXY = 0.0;
    double sumX2 = 0.0;
    double sumY2 = 0.0;
    // Loop through all elements
    for (int i = 0; i < n; i++)
    {   // Compute deviation from mean for x and y
        double dx = x[i] - meanX;
        double dy = y[i] - meanY;
        // Accumulate:
        // dx * dy - covariance component
        sumXY += dx * dy;
        // dx^2 - variance component for x
        sumX2 += dx * dx;
        // dy^2 - variance component for y
        sumY2 += dy * dy;
    }
    // Check for zero variance to avoid division by zero
    // If either dataset has no variation, correlation is undefined
    if (sumX2 == 0.0 || sumY2 == 0.0)
        return 0.0;
    // Compute final SPCC using Pearson correlation formula
    return sumXY / std::sqrt(sumX2 * sumY2);
}

double Math::MeanAbsoluteDeviation(const Vector<double>& values, double mean)
{
    // Check if the dataset is empty
    // MAD is undefined for empty data, so return 0
    if (values.Size() == 0)
        return 0.0;

    double sum = 0.0; // Accumulator for sum of absolute deviations

    // Loop through all values in the dataset
    for (int i = 0; i < values.Size(); i++)
    {
        // Compute deviation from mean
        double diff = values[i] - mean;
        // Convert to absolute value
        // If negative, make it positive
        if (diff < 0)
            diff = -diff; // absolute value
        // Add absolute deviation to sum
        sum += diff;
    }
    // Return mean of absolute deviations
    return sum / values.Size();
}
