#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdexcept> // For std::out_of_range exception
#define INITIAL_CAPACITY 6 // Default starting capacity for the Vector
/**
 * @class Vector
 * @brief A simple templated dynamic array that manages memory manually.
 *
 * This class provides a minimal Vector implementation using a raw dynamic array.
 * It supports insertion, removal, indexing, resizing, and deep copying.
 *
 * @tparam T The element type stored in the Vector.
 */
template <class T>
class Vector
{
	public:
        /**
     * @brief Default constructor.
     *
     * Creates an empty Vector with INITIAL_CAPACITY allocated.
     */
	    Vector();
	    /**
     * @brief Constructs a Vector with space for n elements.
     *
     * Elements are default-constructed. Capacity is set to at least INITIAL_CAPACITY.
     *
     * @param n Number of elements to initialise.
     */
		Vector(int n);

		 /**
     * @brief Copy constructor (deep copy).
     *
     * Allocates new storage and copies elements from other.
     *
     * @param other Vector to copy from.
     */
        Vector(const Vector<T>& other);

         /**
     * @brief Assignment operator (deep copy).
     *
     * Replaces current contents with a deep copy of other.
     *
     * @param other Vector to assign from.
     * @return Reference to this Vector.
     */
        Vector<T>& operator=(const Vector<T>& other);

       /**
     * @brief Destructor.
     *
     * Releases dynamically allocated memory.
     */
        ~Vector();
        /**
     * @brief Inserts data at position pos (0..m_size).
     *
     * Shifts elements to the right. May trigger resizing if capacity is full.
     *
     * @param data Element to insert.
     * @param pos Index position to insert at.
     * @return true if inserted successfully; false if pos is out of range.
     */

        bool Insert(const T& data, int pos);
        /**
        * @brief Removes element at position pos (0..m_size-1).
        *        Shifts elements to the left.
        * @return true if successful, false if pos out of range
        */
        bool Remove(int pos);
        /**
     * @brief Read-only indexing operator with bounds checking.
     *
     * @param pos Index to access.
     * @return Const reference to the element at pos.
     * @throws std::out_of_range if pos is invalid.
     */
        const T& operator[](int pos) const;
        /**
     * @brief Writable indexing operator with bounds checking.
     *
     * @param pos Index to access.
     * @return Reference to the element at pos.
     * @throws std::out_of_range if pos is invalid.
     */
        T& operator[] (int pos);
       /**
     * @brief Returns the number of elements currently stored.
     *
     * @return Current size of the Vector.
     */
        int Size() const;
         /**
     * @brief Clears the Vector (logical clear).
     *
     * Sets size to 0 but keeps allocated memory for reuse.
     */
        void Clear();
/**
     * @brief Resizes internal storage to at least newCapacity.
     *
     * If newCapacity is not larger than current capacity, nothing changes.
     *
     * @param newCapacity Requested new capacity.
     */
        void Resize(int newCapacity);
	private:
        T * m_vec;  ///< Pointer to dynamic array storage
        int m_capacity;  ///< Pointer to dynamic array storage
        int m_size;   ///< Current number of stored elements


};

template <class T>
Vector<T>::Vector()
{
    m_size = 0; // Start with zero elements
    m_capacity = INITIAL_CAPACITY;  // Set initial capacity
    m_vec = new T[m_capacity];  // Allocate dynamic array of type T
}

template <class T>
Vector<T>:: Vector(int n)
{
    if (n < 0) n = 0; // Defensive: prevent negative size


    m_capacity = (n > INITIAL_CAPACITY) ? (n * 2) : INITIAL_CAPACITY; // Choose capacity
    m_vec = new T[m_capacity];  // Allocate dynamic array of type T
    m_size = n;    // Set size
}
template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
    m_vec = nullptr;  // Initialise pointer defensively
    m_capacity = other.m_capacity;  // Copy capacity value
    m_size = other.m_size;  // Copy size value

    m_vec = new T[m_capacity];  // Copy size value
    for (int i = 0; i < m_size; ++i)  // Copy each element (deep copy)
    {
        m_vec[i] = other.m_vec[i];  // Copy element i
    }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this == &other) return *this; // Protect against self-assignment


    T* newArr = new T[other.m_capacity]; // Allocate new storage first
    for (int i = 0; i < other.m_size; ++i)  // Copy elements from other
    {
        newArr[i] = other.m_vec[i];  // Copy element i
    }

    delete[] m_vec;  // Copy element i
    m_vec = newArr; // Replace with new storage
    m_capacity = other.m_capacity;  // Copy capacity
    m_size = other.m_size; // Copy size

    return *this; // Return this object
}

template <class T>
Vector<T>::~Vector()
{
    if(m_vec != nullptr) // Only delete if allocated
    {
        delete[] m_vec;  // Free dynamic array
        m_vec = nullptr;  // Avoid dangling pointer
        m_capacity = 0; // Reset capacity
        m_size = 0;  // Reset size
    }
}

template <class T>
void Vector<T>::Resize(int newCapacity)
{
    if (newCapacity <= m_capacity) return; // Do nothing if already large enough
    if (newCapacity < INITIAL_CAPACITY) newCapacity = INITIAL_CAPACITY; // Enforce minimum capacity

    T* newArr = new T[newCapacity];  // Allocate new larger array
    for (int i = 0; i < m_size; ++i)  // Copy old elements into new array
    {
        newArr[i] = m_vec[i];  // Copy element i
    }

    delete[] m_vec; // Free old storage
    m_vec = newArr; // Point to new storage
    m_capacity = newCapacity;  // Update capacity
}

template <class T>
bool Vector<T>::Insert(const T& data, int pos)
{
    if (pos < 0 || pos > m_size) return false; // Validate insertion position

    if (m_size == m_capacity) // Check if capacity is full
    {

        Resize(m_capacity * 2);  // Grow capacity
    }


    for (int i = m_size; i > pos; --i) // Shift elements to the right
    {
        m_vec[i] = m_vec[i - 1]; // Move element right by one position
    }

    m_vec[pos] = data; // Insert new element
    ++m_size; // Increase size
    return true; // Report success
}

template <class T>
bool Vector<T>::Remove(int pos)
{
    if (pos < 0 || pos >= m_size) return false; // Validate removal position


    for (int i = pos; i < m_size - 1; ++i) // Shift elements to the left
    {
        m_vec[i] = m_vec[i + 1]; // Move next element left
    }

    --m_size;  // Decrease size
    return true; // Report success
}



template <class T>
const T& Vector<T>::operator[](int pos) const
{
    if (pos < 0 || pos >= m_size)  // Validate bounds
        throw std::out_of_range("Vector: index out of range"); // Throw exception if invalid
    return m_vec[pos];  // Return const reference to element
}

template <class T>
T& Vector<T>::operator[](int pos)
{
    if (pos < 0 || pos >= m_size) // Validate bounds
        throw std::out_of_range("Vector: index out of range"); // Throw exception if invalid
    return m_vec[pos];   // Return reference to element
}

template <class T>
int Vector<T>::Size() const
{
    return m_size; // Return number of stored elements
}

template <class T>
void Vector<T>::Clear()
{
    m_size = 0;  // Reset logical size
}




#endif // VECTOR_H_INCLUDED


