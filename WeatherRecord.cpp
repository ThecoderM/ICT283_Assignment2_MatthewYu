#include "WeatherRecord.h"
// Default constructor
// Initialises numeric values to 0 and flags to false
WeatherRecord::WeatherRecord()
{
    m_speed = 0.0f;
    m_Ambient_Air_Temperature = 0.0f;
    m_Solar_Radiation = 0.0f;
    m_hasSpeed = false;
    m_hasTemp = false;
    m_hasSolar = false;
}
// Parameterised constructor
// Sets all values and marks them as available
WeatherRecord::WeatherRecord(const Date& d, const Time& t, float speed_mps, float Ambient_Air_Temperature, float Solar_Radiation)
{
    m_date = d;
    m_time = t;
    m_speed = speed_mps;
    m_Ambient_Air_Temperature = Ambient_Air_Temperature;
    m_Solar_Radiation = Solar_Radiation;
}

// Set the date of the record
void WeatherRecord::SetDate(const Date& d)
{
    m_date = d;
}
// Set the time of the record
void WeatherRecord::SetTime(const Time& t)
{
    m_time = t;
}
// Set wind speed and mark as available
void WeatherRecord::SetSpeed(float speed_mps)
{
    m_speed = speed_mps;
    m_hasSpeed = true;
}
// Set ambient air temperature and mark as available
void WeatherRecord::setAmbientAirTemperature(float Ambient_Air_Temperature)
{
    m_Ambient_Air_Temperature = Ambient_Air_Temperature;
    m_hasTemp = true;
}
// Set solar radiation and mark as available
void WeatherRecord::setSolarRadiation(float Solar_Radiation)
{
    m_Solar_Radiation = Solar_Radiation;
    m_hasSolar = true;
}
// Return date of record
Date WeatherRecord::GetDate() const
{
    return m_date;
}
// Return time of record
Time WeatherRecord::GetTime() const
{
    return m_time;
}
// Return wind speed (m/s)
float WeatherRecord::GetSpeed() const
{
    return m_speed;
}
// Return ambient air temperature
float WeatherRecord::GetAmbientAirTemperature() const
{
    return m_Ambient_Air_Temperature;
}
// Return solar radiation value
float WeatherRecord::GetSolarRadiation() const
{
    return m_Solar_Radiation;
}
// Return whether wind speed is valid
bool WeatherRecord::GetHasSpeed() const
{
    return m_hasSpeed;
}
// Return whether temperature is valid
bool WeatherRecord::GetHasAmbientAirTemperature() const
{
    return m_hasTemp;
}
// Return whether solar radiation is valid
bool WeatherRecord::GetHasSolarRadiation() const
{
    return m_hasSolar;
}

bool operator==(const WeatherRecord& a, const WeatherRecord& b)
{
    // Two WeatherRecord objects are equal if both their date and time are the same
    return a.GetDate() == b.GetDate() && // Compare dates
           a.GetTime() == b.GetTime();  // Compare times
}

bool operator<(const WeatherRecord& a, const WeatherRecord& b)
{
    // If the dates are the same, compare based on time
    if (a.GetDate() == b.GetDate())
        return a.GetTime() < b.GetTime(); // Earlier time comes first
    // Otherwise, compare based on date
    return a.GetDate() < b.GetDate();     // Earlier date comes first
}

bool operator>(const WeatherRecord& a, const WeatherRecord& b)
{
    // Greater-than is defined using the less-than operator (reverse comparison)
    return b < a;
}
