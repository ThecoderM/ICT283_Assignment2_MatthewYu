#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <map>

/**
 * @class Map
 * @brief A wrapper class around std::map providing simplified access methods.
 *
 * The Map class encapsulates the functionality of std::map and provides
 * commonly used operations such as:
 * - Checking if a key exists
 * - Accessing or inserting values using operator[]
 * - Finding values safely using pointers
 * - Clearing all stored data
 *
 * This abstraction simplifies usage and improves readability when used
 * in higher-level classes such as WeatherLog.
 *
 * @tparam k The key type.
 * @tparam v The value type.
 */

template <class k, class v>
class Map
{
public:
    /**
     * @brief Checks if a key exists in the map.
     *
     * @param key The key to search for.
     * @return true if the key exists, false otherwise.
     */
    bool Contains(const k& key) const;
    /**
     * @brief Accesses or inserts a value associated with a key.
     *
     * If the key does not exist, a new element is created with a default value.
     *
     * @param key The key to access.
     * @return Reference to the value associated with the key.
     */
    v& operator[](const k& key);
    /**
     * @brief Finds a value associated with a key.
     *
     * Unlike operator[], this does not insert a new element if the key is missing.
     *
     * @param key The key to search for.
     * @return Pointer to the value if found, otherwise nullptr.
     */
    const v* Find(const k& key) const;
    /**
     * @brief Clears all elements from the map.
     */
    void Clear();

private:
    std::map<k, v> m_data; // Internal STL map storing key-value pairs
};

template <class K, class V>
bool Map<K, V>::Contains(const K& key) const
{
    // Check if key exists by comparing iterator with end()
    return m_data.find(key) != m_data.end();
}

template <class K, class V>
V& Map<K, V>::operator[](const K& key)
{
    // Access value associated with key
    // If key does not exist, it is created with a default value
    return m_data[key];
}

template <class K, class V>
const V* Map<K, V>::Find(const K& key) const
{
    // Attempt to find the key in the map
    typename std::map<K, V>::const_iterator it = m_data.find(key);

    // If key is not found, return nullptr
    if (it == m_data.end())
        return nullptr;
    // Return pointer to the value associated with the key
    return &(it->second);
}

template <class K, class V>
void Map<K, V>::Clear()
{
    // Remove all key-value pairs from the map
    m_data.clear();
}

#endif // MAP_H_INCLUDED
