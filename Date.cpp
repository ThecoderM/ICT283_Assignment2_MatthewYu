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

// Less-than operator
// Compares two Date objects chronologically.
// Priority of comparison: Year -> Month -> Day
bool operator<(const Date& lhs, const Date& rhs)
{
    // First compare the year
    if (lhs.GetYear() != rhs.GetYear())
        return lhs.GetYear() < rhs.GetYear();
    // If years are equal, compare the month
    if (lhs.GetMonth() != rhs.GetMonth())
        return lhs.GetMonth() < rhs.GetMonth();
    // If months are also equal, compare the day
    return lhs.GetDay() < rhs.GetDay();
}
// Greater-than operator
// Implemented using the < operator to avoid duplicating logic
bool operator>(const Date& lhs, const Date& rhs)
{
    return rhs < lhs;
}
// Less than or equal operator
// Returns true if lhs is either less than or equal to rhs
bool operator<=(const Date& lhs, const Date& rhs)
{
    return !(lhs > rhs);
}
// Greater than or equal operator
// Returns true if lhs is either greater than or equal to rhs
bool operator>=(const Date& lhs, const Date& rhs)
{
    return !(lhs < rhs);
}
// Equality operator
// Returns true only if day, month, and year are identical
bool operator==(const Date& lhs, const Date& rhs)
{
    return lhs.GetDay() == rhs.GetDay() &&
           lhs.GetMonth() == rhs.GetMonth() &&
           lhs.GetYear() == rhs.GetYear();
}
// Output stream operator
// Defines how a Date object is printed using cout
// Format: DD/MM/YYYY
std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << d.GetDay() << "/"
       << d.GetMonth() << "/"
       << d.GetYear();

    return os;
}

