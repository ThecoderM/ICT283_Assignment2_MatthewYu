#include "Date.h"
#include <string>
using std::string;
using std::to_string;
// Default constructor
// Initializes the date to a default value
Date::Date()
{
    m_day = 1;
    m_month = 1;
    m_year = 2000;
}

// Parameterized constructor
// Initializes the date using the provided day, month, and year
Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}
// Returns the day value
int Date::GetDay() const
{
    return m_day;
}
// Returns the month value
int Date::GetMonth() const
{
    return m_month;
}
// Returns the year value
int Date::GetYear() const
{
    return m_year;
}
// Sets the day value
void Date::SetDay(int day)
{
    m_day = day;
}
// Sets the month value
void Date::SetMonth(int month)
{
    m_month = month;
}
// Sets the year value
void Date::SetYear(int year)
{
    m_year = year;
}

