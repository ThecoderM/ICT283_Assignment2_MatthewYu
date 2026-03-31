#include "WeatherLog.h"

#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include "Math.h"

using std::ifstream;
using std::stringstream;
using std::string;
using std::getline;
using std::isspace;

static string Trim(const string& s) // helper function
{
    int start = 0; // Track start index (first non-space)
    while (start < (int)s.length() && isspace((unsigned char)s[start])) // Skip leading spaces
        start++; // Move start forward

    int end = (int)s.length() - 1; // Track end index (last non-space)
    while (end >= start && isspace((unsigned char)s[end])) // Skip trailing spaces
        end--; // Move end backward

    return s.substr(start, end - start + 1); // Return substring between start and end
}

WeatherLog::WeatherLog() // Default constructor
{
    // m_data initialises itself automatically
}

int WeatherLog::Size() const // Return number of stored records
{
    return m_data.Size(); // Delegate to Vector<WeatherRecord>::Size()
}

WeatherRecord WeatherLog::GetAt(int index) const // Return record at a given index
{
    return m_data[index]; // Use Vector indexing operator (with bounds check)
}

const Vector<WeatherRecord>& WeatherLog::GetData() const // Read-only access to internal vector
{
    return m_data; // Return const reference to internal storage
}

bool WeatherLog::LoadData(const string& sourceFilename) // Load records using data_source.txt file
{
    string sourcePath = "data/" + sourceFilename; // Build path to data_source.txt under data folder

    ifstream source(sourcePath); // Open the data_source.txt file
    if (!source)                        // Check if the file opened successfully
        return false;                   // Return false if file cannot be opened

    string csvName;                     // Store the CSV filename read from data_source.txt
    while (getline(source, csvName))    // Read lines until a valid filename is found
    {
        csvName = Trim(csvName);        // Trim whitespace
        if (csvName != "")              // Stop once a non-empty line is found
            break;                      // Exit loop when filename is obtained
    }
    source.close();                     // Close the data_source.txt file

    if (csvName == "")                  // If no CSV filename was found
        return false;                   // Fail loading process


    string csvPath = csvName;           // Default: assume csvName already contains a path

    bool hasSlash = (csvName.find('/') != std::string::npos) || (csvName.find('\\') != std::string::npos); // Check if name already contains a folder separator
    if (!hasSlash)                      // If no folder separator is present
        csvPath = "data/" + csvName;    // Force CSV file to be loaded from data/ folder

    ifstream fin(csvPath);      // Open the actual CSV file
    if (!fin)
        return false;


    string headerLine;                  // Store header row
    if (!getline(fin, headerLine))      // Read first line (header)
        return false;                   // Fail if header cannot be read

    const int MAX_FIELDS = 256;         // Define max number of CSV fields supported
    string headerFields[MAX_FIELDS];    // Array to store header field names
    int headerCount = 0;                // Number of header fields extracted

    if (!SplitCSVLine(headerLine, headerFields, MAX_FIELDS, headerCount)) // Split header into fields
        return false;

    // Find required columns
    int idxWAST = FindColumnIndex(headerFields, headerCount, "WAST");
    int idxS    = FindColumnIndex(headerFields, headerCount, "S");
    int idxT    = FindColumnIndex(headerFields, headerCount, "T");
    int idxSR   = FindColumnIndex(headerFields, headerCount, "SR");

    if (idxWAST < 0 || idxS < 0 || idxT < 0 || idxSR < 0)  // Ensure all required columns exist
        return false;


    string line;    // Holds each CSV data row
    string fields[MAX_FIELDS]; // Holds parsed fields for each row
    int count = 0; // Holds parsed fields for each row

    while (getline(fin, line)) // Read each data row
    {
        if (Trim(line) == "") // Read each data row
            continue; // Move to next row

        if (!SplitCSVLine(line, fields, MAX_FIELDS, count)) // Split row into fields store them in fields
            continue; // Skip malformed lines

        int maxIndex = (idxWAST > idxS) ? idxWAST : idxS; // Determine minimum required index for safety
        if (count <= maxIndex) // Determine minimum required index for safety
            continue; // Skip incomplete rows


        Date d; // Date object to store parsed date
        Time t; // Time object to store parsed time
        if (!ParseWAST(fields[idxWAST], d, t)) // Parse WAST timestamp into Date and Time
            continue;       // Skip row if timestamp parsing fails


        float speed = 0.0f; // Parsed wind speed value
        float Temp = 0.0f; // Parsed temperature value
        float SR = 0.0f;   // Parsed solar radiation value
        bool hasSpeed = TryParseFloat(fields[idxS], speed); // Try parse wind speed field
        bool hasTemp  = TryParseFloat(fields[idxT], Temp);  // Try parse temperature field
        bool hasSR    = TryParseFloat(fields[idxSR], SR);   // Try parse solar radiation field




        WeatherRecord rec; // Try parse solar radiation field
        rec.SetDate(d);    // Store parsed Date into record
        rec.SetTime(t);    // Store parsed Time into record
        if (hasSpeed) rec.SetSpeed(speed);  // Only set speed if parsed successfully
        if (hasTemp)  rec.setAmbientAirTemperature(Temp); // Only set temperature if valid
        if (hasSR)    rec.setSolarRadiation(SR); // Only set solar radiation if valid

        m_data.Insert(rec, m_data.Size()); // Append record
    }

    fin.close(); // Close the CSV file
    return true; // Close the CSV file
}

bool WeatherLog::SplitCSVLine(const string& line, string fields[], int maxFields, int& count) const // Split CSV line into tokens
{
    count = 0;  // Reset output count
    stringstream ss(line); // Wrap line in a stringstream for token extraction
    string token; // Buffer for each token

    while (getline(ss, token, ',')) // Extract tokens separated by commas
    {
        if (count >= maxFields) // Prevent buffer overflow
            return false; // Fail if too many fields

        fields[count] = Trim(token);  // Store trimmed token
        count++;  // Increment number of stored fields
    }
    return true; // Return success when split completes
}

int WeatherLog::FindColumnIndex(const string headerFields[], int headerCount, const string& colName) const // Find a header column index
{
    for (int i = 0; i < headerCount; i++) // Loop through header fields
    {
        if (headerFields[i] == colName) // Compare exact column name
            return i;                   // Return index when found
    }
    return -1; // Return -1 when not found
}

bool WeatherLog::ParseWAST(const string& wast, Date& d, Time& t) const // Parse WAST timestamp into Date and Time
{

    stringstream ss(Trim(wast)); // Trim and read the WAST string
    string datePart, timePart;   // Store date and time tokens

    if (!(ss >> datePart >> timePart)) // Expected format "DD/MM/YYYY HH:MM"
        return false;


    int day = 0, month = 0, year = 0; // Variables for parsed date components
    char s1 = 0, s2 = 0;  // Separator characters for '/' checking
    {
        stringstream ds(datePart);  // Parse date portion
        if (!(ds >> day >> s1 >> month >> s2 >> year)) // Extract day/month/year with separators
            return false;  // Fail if date extraction fails
        if (s1 != '/' || s2 != '/') // Validate date separators
            return false;  // Fail if separators are wrong
        // Store day, month, year
        d.SetDay(day);
        d.SetMonth(month);
        d.SetYear(year);
    }


    int hour = 0, minute = 0; // Variables for parsed time components
    char colon = 0;           // Separator character for ':' checking
    {
        stringstream ts(timePart); // Parse time portion
        if (!(ts >> hour >> colon >> minute)) // Extract hour and minute
            return false;  // Fail if time extraction fails
        if (colon != ':')  // Validate separator is ':'
            return false;  // Fail if separator is wrong

        t = Time(hour, minute, 0);  // Construct Time (seconds default to 0)
    }

    return true;
}

bool WeatherLog::TryParseFloat(const string& token, float& value) const // Attempt safe float parsing
{
    string s = Trim(token); // Trim whitespace from token


    if (s == "" || s == "N/A" || s == "NA" || s == "NaN" || s == "nan") // Reject known invalid tokens
        return false;  // Indicate parsing failed

    stringstream ss(s); // Use stringstream for conversion
    ss >> value; // Attempt to extract float value

    if (ss.fail()) // Attempt to extract float value
        return false; // Indicate parsing failed

    return true;
}
