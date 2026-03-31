#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <stdexcept> // For std::out_of_range exception
#include <vector>

using std::vector;
/**
 * @class Vector
 * @brief A wrapper (encapsulation) around std::vector providing controlled access.
 *
 * This class encapsulates the STL vector container and exposes only selected
 * functionalities such as insertion, removal, indexing, and size retrieval.
 * It ensures safer operations with boundary checking and controlled interface.
 *
 * @tparam T The type of elements stored in the vector.
 */
template <class T>
class Vector
{
	public:
        /**
         * @brief Default constructor.
         * Initializes an empty vector.
         */
	    Vector() {};

	    /**
         * @brief Constructor with initial size.
         * @param n Initial number of elements.
         */
        Vector(int n);
        /**
         * @brief Destructor.
         */
        ~Vector() {};

        /**
         * @brief Inserts an element at a specific position.
         * @param data The element to insert.
         * @param pos The position where the element will be inserted.
         * @return True if insertion is successful, false otherwise.
         */
        bool Insert(const T& data, int pos);
        /**
         * @brief Removes an element at a specific position.
         * @param pos The position of the element to remove.
         * @return True if removal is successful, false otherwise.
         */
        bool Remove(int pos);
        /**
         * @brief Access element (read-only).
         * @param pos Index position.
         * @return Constant reference to the element.
         */
        const T& operator[](int pos) const;
         /**
         * @brief Access element (modifiable).
         * @param pos Index position.
         * @return Reference to the element.
         */
        T& operator[] (const int& pos);
        /**
         * @brief Returns the number of elements in the vector.
         * @return Size of the vector.
         */
        int Size() const;

        /**
         * @brief Clears all elements from the vector.
         */
        void Clear();

	private:
        vector<T> m_vec; // Underlying STL vector container
};

template <class T>
Vector<T>:: Vector(int n)
{
    // Initialize vector with size n if n is non-negative
    if (n >= 0)
    {
         m_vec.resize(n); // Allocate n default-initialized elements
    }

}

template <class T>
bool Vector<T>::Insert(const T& data, int pos)
{
    // Check for invalid position
    if(pos < 0 || pos > Size())
    {
        return false;
    }
    // If inserting at the end, use push_back for efficiency
    else if(pos == Size())
    {
        m_vec.push_back(data);
    }
    else
    {
        // Insert element at specific position
        m_vec.insert(m_vec.begin() + pos, data);
    }
    return true; // Insertion successfu
}

template <class T>
bool Vector<T>::Remove(int pos)
{
    // Check if position is valid
    if (pos < 0 || pos >= Size())
    {
         return false;
    }
    // Remove element at specified position
    m_vec.erase(m_vec.begin() + pos);

    return true; // Removal successful
}



template <class T>
const T& Vector<T>::operator[](int pos) const
{
    // Check bounds before accessing
    if (pos < 0 || pos >= Size())
        throw std::out_of_range("Vector: index out of range");
    // Return element (read-only)
    return m_vec[pos];
}

template <class T>
T& Vector<T>::operator[](const int& pos)
{
    // Check bounds before accessing
    if (pos < 0 || pos >= Size())
        throw std::out_of_range("Vector: index out of range");

    // Return element (modifiable)
    return m_vec[pos];
}

template <class T>
int Vector<T>::Size() const
{
    // Return current number of elements
    return m_vec.size();
}

template <class T>
void Vector<T>::Clear()
{
    // Remove all elements from the vector
    m_vec.clear();
}




#endif // VECTOR_H_INCLUDED



