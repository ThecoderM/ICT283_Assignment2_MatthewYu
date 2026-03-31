#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include "Vector.h"

/**
 * @brief Visitor helper function that inserts visited BST data into a Vector.
 *
 * @tparam T The data type stored in the BST.
 * @param data The current node data being visited.
 * @param out The output vector that receives the visited data.
 */
template <class T> // Begin template for generic data type T
void InsertIntoVector(T& data, Vector<T>& out) // Define helper function matching Visitor signature
{
    // Insert current node data into the vector at the end
    out.Insert(data, out.Size());
}
/**
 * @brief Represents a single node in the Binary Search Tree.
 *
 * @tparam T The data type stored in the node.
 */
template <class T>  // Begin template for generic node data type T
struct Node         // Define BST node structure
{
    T data; // Data stored in the node
    Node<T> *left;   // Pointer to left child
    Node<T> *right;  // Pointer to right child
};
/**
 * @brief A reusable Binary Search Tree template class.
 *
 * Stores values in sorted order based on comparison operators.
 * Supports insertion, searching, tree traversal using function pointers,
 * deep copying, destruction, and conversion of tree contents into a Vector.
 *
 * @tparam T The data type stored in the BST.
 */
template <class T>
class Bst
{
public:
    /**
     * @brief Function pointer type used during traversal.
     *
     * The visitor receives:
     * - the current node data
     * - a Vector used as an output/working container
     */
    typedef void (*Visitor)(T &, Vector<T>&);
     /**
     * @brief Default constructor.
     *
     * Creates an empty BST with a null root.
     */
    Bst();
    /**
     * @brief Copy constructor.
     *
     * Creates a deep copy of another BST.
     *
     * @param other The BST to copy from.
     */
    Bst(const Bst<T>& other);
     /**
     * @brief Destructor.
     *
     * Releases all dynamically allocated nodes in the BST.
     */
    ~Bst();
    /**
     * @brief Assignment operator.
     *
     * Replaces the contents of this BST with a deep copy of another BST.
     *
     * @param other The BST to assign from.
     * @return Reference to this BST after assignment.
     */
    Bst<T>& operator=(const Bst<T>& other);

    /**
     * @brief Inserts a new value into the BST.
     *
     * Duplicate values are not inserted.
     *
     * @param newData The value to insert.
     * @return true if insertion succeeds, false if the value is a duplicate.
     */
    bool Insert(const T& newData);

    /**
     * @brief Searches for a target value in the BST.
     *
     * @param target The value to search for.
     * @return true if the target exists in the BST, false otherwise.
     */
    bool Search(const T& target) const;

    /**
     * @brief Traverses the BST in in-order sequence using a visitor function.
     *
     * In-order sequence is: Left, Root, Right.
     *
     * @param visit Function pointer applied to each visited node.
     * @param out Vector passed to the visitor for output or accumulation.
     */
    void InOrderTraversal(Visitor visit, Vector<T>& out) const;
    /**
     * @brief Traverses the BST in pre-order sequence using a visitor function.
     *
     * Pre-order sequence is: Root, Left, Right.
     *
     * @param visit Function pointer applied to each visited node.
     * @param out Vector passed to the visitor for output or accumulation.
     */
    void PreOrderTraversal(Visitor visit, Vector<T>& out) const;
    /**
     * @brief Traverses the BST in post-order sequence using a visitor function.
     *
     * Post-order sequence is: Left, Right, Root.
     *
     * @param visit Function pointer applied to each visited node.
     * @param out Vector passed to the visitor for output or accumulation.
     */
    void PostOrderTraversal(Visitor visit, Vector<T>& out) const;
    /**
     * @brief Copies BST contents into a Vector in sorted order.
     *
     * This uses in-order traversal with the InsertIntoVector visitor.
     *
     * @param out The output vector that will receive the BST contents.
     */
    void ToVector(Vector<T>& out) const;


private:
    Node<T> *m_root; //  // Store pointer to the root node of the BST
     /**
     * @brief Recursive helper used to insert a new node beneath a parent node.
     *
     * @param newNode Pointer to the newly created node to insert.
     * @param parent Pointer to the current parent node being compared against.
     * @return true if insertion succeeds, false if a duplicate is found.
     */
    bool Insert(Node<T>* newNode, Node<T>* parent);
     /**
     * @brief Recursive helper used to search for a target value.
     *
     * @param root Pointer to the current subtree root being searched.
     * @param target The value to search for.
     * @return true if found, false otherwise.
     */
    bool Search(Node<T>* root, const T& target) const;
     /**
     * @brief Recursive helper for in-order traversal.
     *
     * @param node Pointer to the current node.
     * @param visit Visitor function applied to the node.
     * @param out Vector passed to the visitor.
     */
    void InOrder(Node<T>* node, Visitor visit, Vector<T>& out) const;
    /**
     * @brief Recursive helper for pre-order traversal.
     *
     * @param node Pointer to the current node.
     * @param visit Visitor function applied to the node.
     * @param out Vector passed to the visitor.
     */
    void PreOrder(Node<T>* node, Visitor visit, Vector<T>& out) const;
    /**
     * @brief Recursive helper for post-order traversal.
     *
     * @param node Pointer to the current node.
     * @param visit Visitor function applied to the node.
     * @param out Vector passed to the visitor.
     */
    void PostOrder(Node<T>* node, Visitor visit, Vector<T>& out) const;
    /**
     * @brief Recursively deletes all nodes in a subtree.
     *
     * @param node Reference to the pointer of the current subtree root.
     */
    void DeleteTree(Node<T>*& node);
     /**
     * @brief Recursively creates a deep copy of a subtree.
     *
     * @param node Pointer to the subtree root to copy.
     * @return Pointer to the root of the newly copied subtree.
     */
    Node<T>* CopyTree(const Node<T>* node);



};

template <class T>
Bst<T>::Bst() // Define default constructor
{
    m_root = nullptr;  // Initialize the tree as empty by setting root to null
}

template <class T>
Bst<T>::Bst(const Bst<T>& other)
{
    m_root = CopyTree(other.m_root); // Deep-copy the other tree starting from its root
}

template <class T>
Bst<T>::~Bst()
{
    DeleteTree(m_root);  // Delete all nodes in the tree starting from the root
}

template <class T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other)
{
    if (this != &other) // Check for self-assignment
    {
        DeleteTree(m_root); // Delete current tree contents before copying new contents
        m_root = CopyTree(other.m_root); // Deep-copy the other tree into this tree
    }
    return *this; // Return this object by reference
}

template <class T>
bool Bst<T>::Insert(const T& newData)
{

    Node<T>* newNode = new Node<T>; // Allocate memory for a new node

    newNode->data = newData; // Store the new data in the node
    newNode->left = nullptr; // Initialize left child pointer as null
    newNode->right = nullptr;  // Initialize right child pointer as null


    if (m_root == nullptr) // Check whether the tree is currently empty
    {
        m_root = newNode;  // Make the new node the root if tree is empty
        return true;
    }
    else
    {

        return Insert(newNode, m_root); // Insert recursively starting from the root
    }
}

template <class T>
bool Bst<T>::Insert(Node<T>* newNode, Node<T>* parent)
{

    if (newNode->data < parent->data) // Check if new node belongs in the left subtree
    {
        if (parent->left == nullptr)  // Check if left child position is empty
        {

            parent->left = newNode; // Attach new node as left child
            return true;
        }
        else // Otherwise left subtree already exists
        {

            return Insert(newNode, parent->left); // Continue recursive insertion into left subtree
        }
    }

    else if (newNode->data > parent->data) // Check if new node belongs in the right subtree
    {
        if (parent->right == nullptr) // Check if right child position is empty
        {

            parent->right = newNode; // Attach new node as right child
            return true;
        }
        else
        {

            return Insert(newNode, parent->right); // Continue recursive insertion into right subtree
        }
    }

    else // Otherwise the value is equal to parent data
    {
        delete newNode; // Delete the allocated node because duplicates are not allowed
        return false;  // Report insertion failure due to duplicate
    }
}


template <class T>
bool Bst<T>::Search(const T& target) const
{
    return Search(m_root, target);  // Start recursive search from the root
}


template <class T>
bool Bst<T>::Search(Node<T>* root, const T& target) const
{

    if (root == nullptr) // Check if current subtree is empty
    {
        return false; // Target cannot exist in an empty subtree
    }

    if (root->data == target) // Check if current node matches the target
    {
        return true;
    }

    if (target < root->data) // Check if current node matches the target
    {
        return Search(root->left, target); // Recursively search left subtree
    }
    else // Otherwise target must be searched in the right subtree
    {

        return Search(root->right, target); // Recursively search right subtree
    }
}

template <class T>
void Bst<T>::InOrderTraversal(Visitor visit, Vector<T>& out) const // Define public in-order traversal
{
    InOrder(m_root, visit, out); // Start in-order traversal from the root
}

template <class T>
void Bst<T>::InOrder(Node<T>* node, Visitor visit, Vector<T>& out) const
{
    if (node == nullptr) // Check if current node is null
        return;

    InOrder(node->left, visit, out); // Visit left subtree first
    visit(node->data, out); // Apply visitor function to current node data
    InOrder(node->right, visit, out); // Visit right subtree last
}

template <class T>
void Bst<T>::PreOrderTraversal(Visitor visit, Vector<T>& out) const
{
    PreOrder(m_root, visit, out); // Start pre-order traversal from the root
}

template <class T>
void Bst<T>::PreOrder(Node<T>* node, Visitor visit, Vector<T>& out) const
{
    if (node == nullptr) // Check if current node is null
        return;

    visit(node->data, out); // Apply visitor function to current node data first
    PreOrder(node->left, visit, out); // Traverse left subtree next
    PreOrder(node->right, visit, out); // Traverse right subtree last
}


template <class T>
void Bst<T>::PostOrderTraversal(Visitor visit, Vector<T>& out) const
{
    PostOrder(m_root, visit, out); // Start post-order traversal from the root
}


template <class T>
void Bst<T>::PostOrder(Node<T>* node, Visitor visit, Vector<T>& out) const
{
    if (node == nullptr)  // Check if current node is null
        return;

    PostOrder(node->left, visit, out); // Traverse left subtree first
    PostOrder(node->right, visit, out); // Traverse right subtree second
    visit(node->data, out);  // Apply visitor function to current node data last
}


template <class T>
void Bst<T>::DeleteTree(Node<T>*& node)
{
    if (node == nullptr) // Check if current node is null
        return;

    DeleteTree(node->left);   // Recursively delete left subtree
    DeleteTree(node->right);  // Recursively delete right subtree

    delete node; // Delete current node after its children are deleted
    node = nullptr; // Set pointer to null to avoid dangling pointer
}

template <class T>
Node<T>* Bst<T>::CopyTree(const Node<T>* node)
{
    if (node == nullptr) // Check if source subtree is empty
        return nullptr;

    Node<T>* newNode = new Node<T>; // Allocate memory for a new copied node
    newNode->data = node->data; // Copy data from source node into new node
    newNode->left = CopyTree(node->left); // Recursively copy the left subtree
    newNode->right = CopyTree(node->right); // Recursively copy the right subtree

    return newNode;
}

template <class T>
void Bst<T>::ToVector(Vector<T>& out) const
{
    out.Clear(); // Clear output vector before inserting tree contents
    InOrderTraversal(InsertIntoVector<T>, out); // Use in-order traversal with visitor to insert values into vector
}

#endif // BST_H_INCLUDED

