#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
/**
 * @class Time
 * @brief Represents a time-of-day using hour, minute, and second.
 *
 * The Time class models a simple 24-hour clock time.
 * It is designed to be minimal and reusable.
 *
 * Design Rationale:
 * - Keeps time-related logic separate from WeatherRecord.
 * - Maintains single responsibility (represents time only).
 * - Parsing and formatting concerns belong outside this class.
 */
class Time
{
public:
    /**
     * @brief Default constructor.
     *
     * Initialises time to 00:00:00.
     */
    Time();
     /**
     * @brief Parameterised constructor.
     *
     * @param hour Hour value (0�23).
     * @param minute Minute value (0�59).
     * @param second Second value (0�59).
     */
    Time(int hour, int minute, int second);
    /**
     * @brief Returns the hour component.
     * @return Hour (0�23).
     */
    int GetHour() const;
    /**
     * @brief Returns the minute component.
     * @return Minute (0�59).
     */
    int GetMinute() const;
    /**
     * @brief Returns the second component.
     * @return Second (0�59).
     */
    int GetSecond() const;
    /**
     * @brief Sets the hour component.
     * @param hour Hour value (0�23).
     */
    void SetHour(int hour);
    /**
     * @brief Sets the minute component.
     * @param minute Minute value (0�59).
     */
    void SetMinute(int minute);
    /**
     * @brief Sets the second component.
     * @param second Second value (0�59).
     */
    void SetSecond(int second);

private:
    int m_hour; ///< Stores hour value (0�23)
    int m_minute; ///< Stores minute value (0�59)
    int m_second; ///< Stores second value (0�59)
};
// Returns true if lhs time is earlier than rhs time
bool operator<(const Time& lhs, const Time& rhs);
// Returns true if lhs time is later than rhs time
bool operator>(const Time& lhs, const Time& rhs);
// Returns true if both times are equal
bool operator==(const Time& lhs, const Time& rhs);
#endif // TIME_H_INCLUDED
