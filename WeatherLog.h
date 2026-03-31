#ifndef WeatherLog_H_INCLUDED
#define WeatherLog_H_INCLUDED

#include <string> // For std::string
#include "Vector.h" // Custom Vector template
#include "WeatherRecord.h" // WeatherRecord model class
#include "Date.h" // Date model class
#include "Time.h"// Time model class
using std::string; // Use string without std:: prefix
/**
 * @class WeatherLog
 * @brief Manages a collection of WeatherRecord entries loaded from dataset files.
 *
 * The WeatherLog class is responsible for:
 * - Loading and parsing weather data from input files (CSV).
 * - Storing the parsed records internally in a Vector<WeatherRecord>.
 * - Providing controlled access to records for analysis and reporting.
 *
 * Design Rationale:
 * - Keeps file parsing and storage logic out of main().
 * - Keeps WeatherRecord as a data-only model class.
 * - Improves modularity and supports separation of concerns.
 */
class WeatherLog
{
public:
    /**
     * @brief Default constructor.
     *
     * Creates an empty WeatherLog with no records loaded.
     */
    WeatherLog();

    /**
     * @brief Loads weather data records from a specified CSV file.
     *
     * Reads the file, parses required columns (e.g., WAST, S, T, SR),
     * constructs WeatherRecord objects, and stores them in m_data.
     *
     * @param filename Path to the CSV file to load.
     * @return true if the file was opened and processed successfully; otherwise false.
     */
    bool LoadData(const string& filename);

    /**
     * @brief Returns the number of records currently stored.
     *
     * @return Number of WeatherRecord entries in the log.
     */
    int Size() const;
     /**
     * @brief Returns the WeatherRecord at the specified index.
     *
     * @param index Index of record to access (0..Size()-1).
     * @return A copy of the WeatherRecord stored at index.
     */
    WeatherRecord GetAt(int index) const;

    /**
     * @brief Provides read-only access to the internal record storage.
     *
     * This is useful for iterating through all records without allowing modification.
     *
     * @return Const reference to the Vector containing all WeatherRecord entries.
     */
    const Vector<WeatherRecord>& GetData() const;

private:
    Vector<WeatherRecord> m_data; ///< Stores all loaded weather records

    /**
     * @brief Splits a CSV line into fields.
     *
     * Extracts comma-separated values into the provided array.
     *
     * @param line The raw CSV line.
     * @param fields Output array to store parsed fields.
     * @param maxFields Maximum number of fields that can be stored in fields[].
     * @param count Output parameter returning number of fields parsed.
     * @return true if parsing completed; otherwise false.
     */
    bool SplitCSVLine(const string& line, string fields[], int maxFields, int& count) const;
    /**
     * @brief Finds the index of a named column in the CSV header row.
     *
     * @param headerFields Array containing header names.
     * @param headerCount Number of header fields.
     * @param colName Column name to locate (e.g., "WAST", "S", "T", "SR").
     * @return Index of the column if found; otherwise -1.
     */
    int FindColumnIndex(const string headerFields[], int headerCount, const string& colName) const;
     /**
     * @brief Parses a WAST timestamp string into Date and Time.
     *
     * @param wast Timestamp string from CSV.
     * @param d Output Date object.
     * @param t Output Time object.
     * @return true if parsing succeeded; otherwise false.
     */
    bool ParseWAST(const string& wast, Date& d, Time& t) const;
    /**
     * @brief Attempts to parse a floating-point value from a token.
     *
     * @param token Input string token.
     * @param value Output float value if parsing succeeds.
     * @return true if token was successfully parsed into a float; otherwise false.
     */
    bool TryParseFloat(const string& token, float& value) const;
};

#endif // WeatherLog_H_INCLUDED

