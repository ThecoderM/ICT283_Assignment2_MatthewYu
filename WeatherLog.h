#ifndef WeatherLog_H_INCLUDED
#define WeatherLog_H_INCLUDED

#include <string> // For std::string
#include "Vector.h" // Custom Vector template
#include "WeatherRecord.h" // WeatherRecord model class
#include "Date.h" // Date model class
#include "Time.h"// Time model class
#include "Bst.h" // Binary Search Tree
#include "Map.h" // wrapped map class
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
     * @brief Retrieves weather records for a specific month and year.
     *
     * This function searches the internal data structure using the given year and month.
     * If records exist, they are extracted from the BST and stored in the output vector.
     *
     * @param year The year to search for.
     * @param month The month to search for (1�12).
     * @param out Output vector that will contain the matching WeatherRecord objects.
     * @return true if records are found, false otherwise.
     */
    bool GetMonthYearRecords(int year, int month, Vector<WeatherRecord>& out) const;
    /**
     * @brief Retrieves weather records for a specific month across all years.
     *
     * This function iterates through all available years and collects records
     * for the specified month from each year. The results are aggregated into
     * a single output vector.
     *
     * @param month The month to search for (1�12).
     * @param out Output vector that will contain all matching WeatherRecord objects.
     */
    void GetMonthRecordsAcrossYears(int month, Vector<WeatherRecord>& out) const;
    /**
     * @brief Checks whether a specific year exists in the dataset.
     *
     * This function verifies if the given year is present in the internal
     * year index structure.
     *
     * @param year The year to check.
     * @return true if the year exists, false otherwise.
     */
    bool HasYear(int year) const;

private:
    /**
     * @brief Nested data structure storing weather records organized by year and month.
     *
     * Structure:
     * - First level key   : Year (int)
     * - Second level key  : Month (int)
     * - Value             : BST of WeatherRecord objects
     *
     * This allows efficient retrieval of records by:
     * - Specific year and month
     * - Month across multiple years
     *
     * BST is used to maintain sorted order of records within each month.
     */
    Map<int, Map<int, Bst<WeatherRecord>>> m_dataByYearMonth;
    /**
     * @brief Index of available years stored as a BST.
     *
     * This structure keeps track of all years present in the dataset.
     * It enables efficient traversal and retrieval of all years when
     * aggregating data across multiple years.
     */
    Bst<int> m_yearIndex;

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

