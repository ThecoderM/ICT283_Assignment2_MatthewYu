#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <iostream>
using std::cout;
/**
 * @struct Node
 * @brief A basic unit of the Binary Search Tree.
 * @tparam T The type of data stored in the node.
 */
template <class T>
struct Node
{
    T data; ///< The value held by the node.
    Node<T> *left; ///< Pointer to the left child (smaller values).
    Node<T> *right; ///< Pointer to the right child (larger values).
};
/**
 * @class Bst
 * @brief A template-based Binary Search Tree implementation.
 * * This class provides standard BST operations including insertion,
 * searching, and various traversal methods.
 */
template <class T>
class Bst
{
public:
    /**
     * @brief Construct a new Bst object.
     * Initializes the root to nullptr.
     */
    Bst();
    /**
     * @brief Destroy the Bst object.
     * Invokes DeleteTree to ensure all heap memory is freed.
     */
    ~Bst();
    /**
     * @brief Inserts a new piece of data into the tree.
     * @param newData The value to be added.
     * @return true if insertion was successful, false if duplicate.
     */
    bool Insert(const T& newData);
    /**
     * @brief Searches for a specific value in the tree.
     * @param target The value to find.
     * @return true if the value exists in the tree.
     */
    bool Search(const T& target) const;
    /**
     * @brief Deallocates the entire tree memory.
     */
    void DeleteTree();
    /**
     * @brief Prints the tree content in ascending order (Left-Root-Right).
     */
    void InOrderTraversal() const;
    /**
     * @brief Prints the tree content in Pre-Order (Root-Left-Right).
     */
    void PreOrderTraversal() const;
    /**
     * @brief Prints the tree content in Post-Order (Left-Right-Root).
     */
    void PostOrderTraversal() const;
    /**
     * @brief Validates the BST properties.
     * @return true if the tree is a valid BST, false otherwise.
     */


private:
    Node<T> *m_root; ///< The entry point of the tree.
    /**
     * @brief Recursive helper for insertion.
     * @param newNode The node prepared for insertion.
     * @param parent The current node being compared against.
     */
    bool Insert(Node<T>* newNode, Node<T>* parent);
    /**
     * @brief Recursive helper for searching.
     */
    bool Search(Node<T>* root, const T& target) const;
    void InOrder(Node<T>* node) const;
    void PreOrder(Node<T>* node) const;
    void PostOrder(Node<T>* node) const;
    /**
     * @brief Recursive helper for tree deletion using Post-Order logic.
     * @param node Reference to the pointer to be deleted.
     */
    void DeleteTree(Node<T>*& node);

};
// Constructor
// Initializes the BST by setting the root pointer to null
template <class T>
Bst<T>::Bst()
{
    m_root = nullptr;
}
// Destructor
// Ensures that all dynamically allocated nodes in the tree are deleted
template <class T>
Bst<T>::~Bst()
{
    DeleteTree();
}
// Public Insert function
// Creates a new node and inserts it into the BST
template <class T>
bool Bst<T>::Insert(const T& newData)
{
    // Allocate memory for a new node
    Node<T>* newNode = new Node<T>;

    // Initialize the node values
    newNode->data = newData;
    newNode->left = nullptr;
    newNode->right = nullptr;

    // If the tree is empty, the new node becomes the root
    if (m_root == nullptr)
    {
        m_root = newNode;
        return true;
    }
    else
    {
         // Otherwise recursively insert starting from the root
        return Insert(newNode, m_root);
    }
}
// Recursive insert helper function
// Places the new node in the correct position
template <class T>
bool Bst<T>::Insert(Node<T>* newNode, Node<T>* parent)
{
    // If the new value is smaller, go to the left subtree
    if (newNode->data < parent->data)
    {
        if (parent->left == nullptr)
        {
            // insertion point
            parent->left = newNode;
            return true;
        }
        else
        {
            // Continue searching down the left subtree
            return Insert(newNode, parent->left);
        }
    }
    // If the new value is larger, go to the right subtree
    else if (newNode->data > parent->data)
    {
        if (parent->right == nullptr)
        {
            // insertion point
            parent->right = newNode;
            return true;
        }
        else
        {
            // Continue searching down the right subtree
            return Insert(newNode, parent->right);
        }
    }
    // delete the node if its a Duplicate
    else
    {
        delete newNode;
        return false;
    }
}

// Public Search function
// Begins recursive search starting from the root
template <class T>
bool Bst<T>::Search(const T& target) const
{
    return Search(m_root, target);
}

// Recursive search helper function
// Traverses the BST based on comparison with the target value
template <class T>
bool Bst<T>::Search(Node<T>* root, const T& target) const
{
    // Base case: reached a null node, value not found
    if (root == nullptr)
    {
        return false;
    }
    // Target found
    if (root->data == target)
    {
        return true;
    }
    // Search left subtree if target is smaller
    if (target < root->data)
    {
        return Search(root->left, target);
    }
    else
    {
        // Otherwise search right subtree
        return Search(root->right, target);
    }
}
// Starts an in-order traversal from the root
template <class T>
void Bst<T>::InOrderTraversal() const
{
    InOrder(m_root);
}
// In-order traversal
// Visits nodes in Left -> Root -> Right order
template <class T>
void Bst<T>::InOrder(Node<T>* node) const
{
    if (node == nullptr)
        return;

    InOrder(node->left);
    cout << node->data << " ";
    InOrder(node->right);
}
// Starts a pre-order traversal from the root
template <class T>
void Bst<T>::PreOrderTraversal() const
{
    PreOrder(m_root);
}
// Pre-order traversal
// Visits nodes in Root -> Left -> Right order
template <class T>
void Bst<T>::PreOrder(Node<T>* node) const
{
    if (node == nullptr)
        return;

    cout << node->data << " ";
    PreOrder(node->left);
    PreOrder(node->right);
}

// Starts a post-order traversal from the root
template <class T>
void Bst<T>::PostOrderTraversal() const
{
    PostOrder(m_root);
}

// Post-order traversal
// Visits nodes in Left -> Right -> Root order
template <class T>
void Bst<T>::PostOrder(Node<T>* node) const
{
    if (node == nullptr)
        return;

    PostOrder(node->left);
    PostOrder(node->right);
    cout << node->data << " ";
}
// Public delete function
// Deletes all nodes in the tree
template <class T>
void Bst<T>::DeleteTree()
{
    DeleteTree(m_root);
}
// Recursive delete helper
// Uses post-order traversal to safely delete nodes
template <class T>
void Bst<T>::DeleteTree(Node<T>*& node)
{
    if (node == nullptr)
        return;

    DeleteTree(node->left);
    DeleteTree(node->right);

    delete node;
    node = nullptr;
}


#endif // BST_H_INCLUDED

