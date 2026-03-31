#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <string>
/**
 * @class Date
 * @brief Represents a calendar date stored as day, month, and year.
 *
 * The Date class is used to store and manipulate a specific calendar date.
 *
 *
 * A Date object contains three integer values:
 *  - day of the month
 *  - month of the year
 *  - year
 *
 * The class provides get and set methods for each component of the date.
 * Stream input and output operators are implemented to allow Date objects
 * to be read from and written to input and output streams.
 *
 * The expected input/output format for Date is:
 * DD/MM/YYYY
 *
 * @author Matthew
 * @version 01
 * @date 2026
 *
 *
 *
 */
using std::string;

class Date
{
public:
    /**
    * @brief Default constructor.
    *
    * Initializes the date to a default valid value.
    */
    Date();
    /**
    * @brief Constructs a Date object using day, month, and year.
    *
    * @param day Day of the month.
    * @param month Month of the year.
    * @param year Year.
    */
    Date(int day, int month, int year);
    /**
    * @brief Gets the day value.
    * @return Day of the month.
    */

    int GetDay() const;
    /**
    * @brief Gets the month value.
    * @return Month of the year.
    */
    int GetMonth() const;
    /**
    * @brief Gets the year value.
    * @return Year.
    */
    int GetYear() const;
    /**
     * @brief Sets the day value.
     * @param day Day of the month.
     */
    void SetDay(int day);
    /**
    * @brief Sets the month value.
    * @param month Month of the year.
    */
    void SetMonth(int month);
    /**
    * @brief Sets the year value.
    * @param year Year.
    */
    void SetYear(int year);


private:
    /** @brief Day of the month. */
    int m_day;
    /** @brief Month of the year. */
    int m_month;
    /** @brief Year value. */
    int m_year;
};


#endif // DATE_H_INCLUDED

