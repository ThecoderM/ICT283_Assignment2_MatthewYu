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
    int n = x.Size();

    if (n < 2 || y.Size() != n)
        return 0.0;

    double meanX = Mean(x);
    double meanY = Mean(y);

    double sumXY = 0.0;
    double sumX2 = 0.0;
    double sumY2 = 0.0;

    for (int i = 0; i < n; i++)
    {
        double dx = x[i] - meanX;
        double dy = y[i] - meanY;

        sumXY += dx * dy;
        sumX2 += dx * dx;
        sumY2 += dy * dy;
    }

    if (sumX2 == 0.0 || sumY2 == 0.0)
        return 0.0;

    return sumXY / std::sqrt(sumX2 * sumY2);
}

double Math::MeanAbsoluteDeviation(const Vector<double>& values, double mean)
{
    if (values.Size() == 0)
        return 0.0;

    double sum = 0.0;

    for (int i = 0; i < values.Size(); i++)
    {
        double diff = values[i] - mean;

        if (diff < 0)
            diff = -diff; // absolute value

        sum += diff;
    }

    return sum / values.Size();
}
