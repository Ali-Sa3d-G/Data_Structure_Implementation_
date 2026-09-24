#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                     BINARY SEARCH TREE - LEARNING GUIDE
 * ============================================================================
 *
 * A Binary Search Tree (BST) is a binary tree where:
 *
 *       LEFT SUBTREE  <  NODE  <  RIGHT SUBTREE
 *
 * Example:
 *
 *                         50
 *                       /    \
 *                     30      70
 *                    /  \    /  \
 *                  20   40  60   80
 *
 * For every node:
 *
 *   - Smaller values go left.
 *   - Larger values go right.
 *
 * Important:
 *
 *   In-Order traversal of a BST gives the values in SORTED order.
 *
 *       Left -> Root -> Right
 *
 * Main Operations:
 *   - Insert
 *   - Search
 *   - Find Minimum / Maximum
 *   - Delete
 *   - Tree Traversals
 *
 * Time Complexity:
 *   Average Search/Insert/Delete: O(log n)
 *   Worst Case                  : O(n)
 *
 * Space Complexity:
 *   O(h) for recursive operations
 *   h = height of tree
 *
 * ============================================================================
 */

 // =========================== NODE CLASS ===========================

 /**
  * Each tree node contains:
  *
  *               [ DATA ]
  *               /      \
  *            left      right
  *
  * left  -> smaller values
  * right -> larger values
  */
class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// =========================== BST CLASS ===========================

class BST
{
private:
    Node* root;

    // ==================== INSERT HELPER ====================

    /**
     * Recursively finds the correct position for a new value.
     */
    Node* insert(Node* node, int value)
    {
        if (node == nullptr)
            return new Node(value);

        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insert(node->right, value);
        }

        // Duplicate values are ignored.
        return node;
    }

    // ==================== SEARCH HELPER ====================

    /**
     * Uses the BST property to decide which side to search.
     */
    bool search(Node* node, int value) const
    {
        if (node == nullptr)
            return false;

        if (node->data == value)
            return true;

        if (value < node->data)
            return search(node->left, value);

        return search(node->right, value);
    }

    // ==================== MINIMUM ====================

    /**
     * The minimum value is the leftmost node.
     *
     * Example:
     *
     *          50
     *         /
     *       30
     *      /
     *    20  <- minimum
     */
    int findMin(Node* node) const
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node->data;
    }

    // ==================== DELETION ====================

    /**
     * DELETE NODE
     *
     * There are three deletion cases:
     *
     * 1. Leaf:
     *
     *       30
     *      /
     *    20   <- delete
     *
     * 2. One child:
     *
     *       30
     *         \
     *          40
     *           \
     *            50
     *
     * 3. Two children:
     *
     *          50
     *         /  \
     *       30    70
     *
     * Replace 50 with its inorder successor
     * (smallest value in the right subtree).
     */
    Node* deleteNode(Node* node, int value)
    {
        if (node == nullptr)
            return nullptr;

        if (value < node->data)
        {
            node->left = deleteNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = deleteNode(node->right, value);
        }
        else
        {
            // Case 1 and 2:
            // No left child, so return the right child.
            if (node->left == nullptr)
            {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            // No right child, so return the left child.
            if (node->right == nullptr)
            {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: two children.
            int successor = findMin(node->right);

            node->data = successor;

            // Delete the duplicated successor from the right subtree.
            node->right = deleteNode(node->right, successor);
        }

        return node;
    }

    // ==================== TRAVERSALS ====================

    void inOrder(Node* node) const
    {
        if (node == nullptr)
            return;

        inOrder(node->left);

        cout << node->data << " ";

        inOrder(node->right);
    }

    void preOrder(Node* node) const
    {
        if (node == nullptr)
            return;

        cout << node->data << " ";

        preOrder(node->left);
        preOrder(node->right);
    }

    void postOrder(Node* node) const
    {
        if (node == nullptr)
            return;

        postOrder(node->left);
        postOrder(node->right);

        cout << node->data << " ";
    }

    // ==================== CLEAR ====================

    /**
     * Post-order deletion ensures children are deleted
     * before their parent.
     */
    void clear(Node* node)
    {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

public:

    // ==================== CONSTRUCTOR ====================

    BST()
    {
        root = nullptr;
    }

    // ==================== PUBLIC OPERATIONS ====================

    void insert(int value)
    {
        root = insert(root, value);
    }

    bool search(int value) const
    {
        return search(root, value);
    }

    void deleteValue(int value)
    {
        root = deleteNode(root, value);
    }

    void inOrder() const
    {
        inOrder(root);
        cout << endl;
    }

    void preOrder() const
    {
        preOrder(root);
        cout << endl;
    }

    void postOrder() const
    {
        postOrder(root);
        cout << endl;
    }

    // ==================== DESTRUCTOR ====================

    ~BST()
    {
        clear(root);
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    BST tree;

    // ==================== INSERTION ====================

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "In-Order: ";
    tree.inOrder();

    cout << "Pre-Order: ";
    tree.preOrder();

    cout << "Post-Order: ";
    tree.postOrder();

    // ==================== SEARCH ====================

    cout << "\nSearch 40: "
        << (tree.search(40) ? "Found" : "Not Found")
        << endl;

    cout << "Search 90: "
        << (tree.search(90) ? "Found" : "Not Found")
        << endl;

    // ==================== DELETION ====================

    cout << "\nDeleting 20 (leaf):" << endl;
    tree.deleteValue(20);
    tree.inOrder();

    cout << "Deleting 30 (one child):" << endl;
    tree.deleteValue(30);
    tree.inOrder();

    cout << "Deleting 50 (two children):" << endl;
    tree.deleteValue(50);
    tree.inOrder();

    return 0;
}