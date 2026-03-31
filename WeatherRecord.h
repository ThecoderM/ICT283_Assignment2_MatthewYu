#ifndef WEATHERRECORD_H_INCLUDED
#define WEATHERRECORD_H_INCLUDED

#include "Date.h"
#include "Time.h"

/**
 * @class WeatherRecord
 * @brief Represents a single weather observation record.
 *
 * Stores:
 * - Date of observation
 * - Time of observation
 * - Wind speed (m/s)
 * - Ambient air temperature
 * - Solar radiation
 *
 * Design Rationale:
 * - This is a model-only class.
 * - It contains no parsing logic, no statistical calculations, and no I/O decisions.
 * - Missing values are tracked using boolean flags to distinguish
 *   between �zero value� and �no data�.
 */
class WeatherRecord
{
public:
     /**
     * @brief Default constructor.
     *
     * Initialises all numeric values to 0 and marks data flags as false.
     */
    WeatherRecord();
    /**
     * @brief Parameterised constructor.
     *
     * @param d Date of observation.
     * @param t Time of observation.
     * @param speed_mps Wind speed in metres per second.
     * @param Ambient_Air_Temperature Ambient air temperature value.
     * @param Solar_Radiation Solar radiation value.
     */
    WeatherRecord(const Date& d, const Time& t, float speed_mps, float Ambient_Air_Temperature, float Solar_Radiation);
    /** @brief Sets the date of the record. */
    void SetDate(const Date& d);
    /** @brief Sets the time of the record. */
    void SetTime(const Time& t);
    /** @brief Sets wind speed in m/s and marks speed as available. */
    void SetSpeed(float speed_mps);
    /** @brief Sets ambient air temperature and marks temperature as available. */
    void setAmbientAirTemperature(float Ambient_Air_Temperature);
    /** @brief Sets solar radiation and marks solar radiation as available. */
    void setSolarRadiation(float Solar_Radiation);
    /** @brief Returns the date of the record. */
    Date GetDate() const;
    /** @brief Returns the time of the record. */
    Time GetTime() const;
    /** @brief Returns wind speed (m/s). */
    float GetSpeed() const;
    /** @brief Returns ambient air temperature. */
    float GetAmbientAirTemperature() const;
    /** @brief Returns solar radiation value. */
    float GetSolarRadiation() const;
    /** @brief Returns true if wind speed value is valid. */
    bool GetHasSpeed() const;
    /** @brief Returns true if temperature value is valid. */
    bool GetHasAmbientAirTemperature() const;
    /** @brief Returns true if solar radiation value is valid. */
    bool GetHasSolarRadiation() const;




private:
    Date  m_date; ///<Date of observation
    Time  m_time; ///< Time of observation
    float m_speed; ///< Wind speed in m/s
    float m_Ambient_Air_Temperature;  ///< Ambient air temperature value
    float m_Solar_Radiation; ///< Solar radiation value

    bool m_hasSpeed; ///< Indicates if wind speed is valid
    bool m_hasTemp;   ///< Indicates if temperature is valid
    bool m_hasSolar;  ///< Indicates if solar radiation is valid
};
// Returns true if lhs occurs earlier than rhs based on date first, then time
// This ordering is used to maintain sorted order in the BST
bool operator<(const WeatherRecord& lhs, const WeatherRecord& rhs);
// Returns true if lhs occurs later than rhs based on date first, then time
bool operator>(const WeatherRecord& lhs, const WeatherRecord& rhs);
// Returns true if both WeatherRecord objects have the same date and time
bool operator==(const WeatherRecord& lhs, const WeatherRecord& rhs);
#endif // WEATHERRECORD_H_INCLUDED
