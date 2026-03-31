#include "Time.h"  // Include corresponding header file

// Helper: keep values in valid ranges (simple safety)
static int Clamp(int value, int minVal, int maxVal)
{
    if (value < minVal) return minVal; // If below range, return minimum
    if (value > maxVal) return maxVal;  // If above range, return maximum
    return value;  // Otherwise return original value
}

Time::Time()
{
    m_hour = 0;// Default time initialised to 00:00:00
    m_minute = 0;
    m_second = 0;
}

Time::Time(int hour, int minute, int second) // Parameterised constructor
{
    m_hour = Clamp(hour, 0, 23); // Parameterised constructor
    m_minute = Clamp(minute, 0, 59);  // Ensure hour stays within valid range
    m_second = Clamp(second, 0, 59); // Ensure second stays within valid range
}

int Time::GetHour() const
{
    return m_hour; // Ensure second stays within valid range
}
int Time::GetMinute() const
{
    return m_minute;  // Return stored hour value
}
int Time::GetSecond() const
{
    return m_second; // Return stored second value
}


void Time::SetHour(int hour)
{
    m_hour = Clamp(hour, 0, 23); // Set hour with range validation
}
void Time::SetMinute(int minute)
{
    m_minute = Clamp(minute, 0, 59);  // Set minute with range validation
}
void Time::SetSecond(int second)
{
    m_second = Clamp(second, 0, 59); // Set second with range validation
}
// Check if hours, minutes, and seconds are all equal
bool operator==(const Time& a, const Time& b)
{
    return a.GetHour() == b.GetHour() && // Compare hours
           a.GetMinute() == b.GetMinute() && // Compare minutes
           a.GetSecond() == b.GetSecond(); // Compare seconds
}

bool operator<(const Time& a, const Time& b)
{
    // First compare hours
    if (a.GetHour() != b.GetHour())
        return a.GetHour() < b.GetHour();
    // If hours are equal, compare minutes
    if (a.GetMinute() != b.GetMinute())
        return a.GetMinute() < b.GetMinute();
    // If both hours and minutes are equal, compare seconds
    return a.GetSecond() < b.GetSecond();
}

bool operator>(const Time& a, const Time& b)
{   // Greater than is defined using the less than operator
    // If b is less than a, then a is greater than b
    return b < a;
}



