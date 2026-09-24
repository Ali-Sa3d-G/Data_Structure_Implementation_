#include <iostream>
#include <algorithm>

using namespace std;

/**
 * ============================================================================
 *                         AVL TREE - LEARNING GUIDE
 * ============================================================================
 *
 * An AVL Tree is a SELF-BALANCING Binary Search Tree.
 *
 * It follows the normal BST rule:
 *
 *       LEFT < ROOT < RIGHT
 *
 * But it also keeps the tree balanced.
 *
 * For every node:
 *
 *       Balance Factor = Height(Right) - Height(Left)
 *
 * A node is balanced when:
 *
 *       -1 <= Balance Factor <= 1
 *
 * If the balance becomes:
 *
 *       less than -1 -> too heavy on the LEFT
 *       greater than 1 -> too heavy on the RIGHT
 *
 * The tree is fixed using ROTATIONS.
 *
 * Four cases:
 *
 *       LL -> Right Rotation
 *       RR -> Left Rotation
 *       LR -> Left Rotation then Right Rotation
 *       RL -> Right Rotation then Left Rotation
 *
 * Visualization of LL:
 *
 *          30
 *         /
 *       20
 *      /
 *    10
 *
 * Right Rotation:
 *
 *          20
 *         /  \
 *       10    30
 *
 * Time Complexity:
 *   Search : O(log n)
 *   Insert : O(log n)
 *   Delete : O(log n)
 *
 * Space Complexity: O(n)
 *
 * ============================================================================
 */

 // =========================== NODE CLASS ===========================

 /**
  * Each node stores:
  *
  *       [ DATA | HEIGHT ]
  *          /       \
  *       left       right
  *
  * height is used to calculate the balance factor.
  */
template <typename T>
class AVLNode
{
public:
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(T value)
    {
        data = value;
        left = nullptr;
        right = nullptr;

        // A leaf has height 1 in this implementation.
        height = 1;
    }
};

// =========================== AVL TREE CLASS ===========================

template <typename T>
class AVLTree
{
private:
    AVLNode<T>* root;

    // ==================== HEIGHT ====================

    /**
     * Returns the height of a node.
     *
     * Height of NULL = 0.
     */
    int getHeight(AVLNode<T>* node) const
    {
        if (node == nullptr)
            return 0;

        return node->height;
    }

    // ==================== BALANCE FACTOR ====================

    /**
     * Balance Factor:
     *
     *       height(right) - height(left)
     *
     * Example:
     *
     *       left height  = 3
     *       right height = 1
     *
     *       balance = 1 - 3 = -2
     *
     * The node is too heavy on the left.
     */
    int getBalanceFactor(AVLNode<T>* node) const
    {
        if (node == nullptr)
            return 0;

        return getHeight(node->right) - getHeight(node->left);
    }

    // ==================== UPDATE HEIGHT ====================

    /**
     * Recalculates a node's height using its tallest child.
     *
     *       height = max(left, right) + 1
     */
    void updateHeight(AVLNode<T>* node)
    {
        node->height =
            max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    // ==================== RIGHT ROTATION ====================

    /**
     * RIGHT ROTATION
     *
     * Used mainly for the LL case.
     *
     * Before:
     *
     *          y
     *         / \
     *        x   C
     *       / \
     *      A   B
     *
     * After:
     *
     *          x
     *         / \
     *        A   y
     *           / \
     *          B   C
     */
    AVLNode<T>* rotateRight(AVLNode<T>* y)
    {
        AVLNode<T>* x = y->left;
        AVLNode<T>* middle = x->right;

        // Rotate.
        x->right = y;
        y->left = middle;

        // Update lower node first, then the new root.
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // ==================== LEFT ROTATION ====================

    /**
     * LEFT ROTATION
     *
     * Used mainly for the RR case.
     *
     * Before:
     *
     *        x
     *       / \
     *      A   y
     *         / \
     *        B   C
     *
     * After:
     *
     *          y
     *         / \
     *        x   C
     *       / \
     *      A   B
     */
    AVLNode<T>* rotateLeft(AVLNode<T>* x)
    {
        AVLNode<T>* y = x->right;
        AVLNode<T>* middle = y->left;

        // Rotate.
        y->left = x;
        x->right = middle;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // ==================== INSERT ====================

    /**
     * INSERT
     *
     * Step 1:
     *   Insert the value like a normal BST.
     *
     * Step 2:
     *   Update heights while returning from recursion.
     *
     * Step 3:
     *   Check the balance factor.
     *
     * Step 4:
     *   Rotate if the node became unbalanced.
     */
    AVLNode<T>* insertNode(AVLNode<T>* node, T value)
    {
        if (node == nullptr)
            return new AVLNode<T>(value);

        // Normal BST insertion.
        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertNode(node->right, value);
        }
        else
        {
            // Ignore duplicates.
            return node;
        }

        updateHeight(node);

        int balance = getBalanceFactor(node);

        // ==================== FOUR CASES ====================

        /*
         * LL CASE
         *
         *      30
         *     /
         *   20
         *   /
         * 10
         *
         * Rotate right.
         */
        if (balance < -1 && value < node->left->data)
        {
            return rotateRight(node);
        }

        /*
         * RR CASE
         *
         * 10
         *   \
         *   20
         *     \
         *     30
         *
         * Rotate left.
         */
        if (balance > 1 && value > node->right->data)
        {
            return rotateLeft(node);
        }

        /*
         * LR CASE
         *
         *      30
         *     /
         *   10
         *     \
         *     20
         *
         * First left rotation on 10,
         * then right rotation on 30.
         */
        if (balance < -1 && value > node->left->data)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        /*
         * RL CASE
         *
         *   10
         *     \
         *     30
         *     /
         *    20
         *
         * First right rotation on 30,
         * then left rotation on 10.
         */
        if (balance > 1 && value < node->right->data)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // ==================== FIND MINIMUM ====================

    /**
     * The minimum node is the leftmost node.
     */
    AVLNode<T>* getMinNode(AVLNode<T>* node) const
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node;
    }

    // ==================== DELETE ====================

    /**
     * DELETE
     *
     * First perform normal BST deletion.
     *
     * Then:
     *   1. Update height.
     *   2. Calculate balance.
     *   3. Rebalance if necessary.
     *
     * Deletion may require rotations while going back
     * through the ancestors.
     */
    AVLNode<T>* deleteNode(AVLNode<T>* node, T value)
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
            // No left child.
            if (node->left == nullptr)
            {
                AVLNode<T>* temp = node->right;
                delete node;
                return temp;
            }

            // No right child.
            if (node->right == nullptr)
            {
                AVLNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            // Two children:
            // Replace with the inorder successor.
            AVLNode<T>* successor = getMinNode(node->right);

            node->data = successor->data;

            node->right =
                deleteNode(node->right, successor->data);
        }

        if (node == nullptr)
            return node;

        updateHeight(node);

        int balance = getBalanceFactor(node);

        // LL case.
        if (balance < -1 &&
            getBalanceFactor(node->left) <= 0)
        {
            return rotateRight(node);
        }

        // LR case.
        if (balance < -1 &&
            getBalanceFactor(node->left) > 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RR case.
        if (balance > 1 &&
            getBalanceFactor(node->right) >= 0)
        {
            return rotateLeft(node);
        }

        // RL case.
        if (balance > 1 &&
            getBalanceFactor(node->right) < 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // ==================== TRAVERSAL ====================

    /**
     * Prints values with their heights.
     *
     * Example:
     *
     *       10(h=1) 20(h=2) 30(h=1)
     */
    void inOrder(AVLNode<T>* node) const
    {
        if (node == nullptr)
            return;

        inOrder(node->left);

        cout << node->data
            << "(h=" << node->height << ") ";

        inOrder(node->right);
    }

    // ==================== CLEAR ====================

    void clear(AVLNode<T>* node)
    {
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

public:

    // ==================== CONSTRUCTOR ====================

    AVLTree()
    {
        root = nullptr;
    }

    // ==================== PUBLIC OPERATIONS ====================

    void insert(T value)
    {
        root = insertNode(root, value);
    }

    void remove(T value)
    {
        root = deleteNode(root, value);
    }

    void printTree() const
    {
        inOrder(root);
        cout << endl;
    }

    // ==================== DESTRUCTOR ====================

    ~AVLTree()
    {
        clear(root);
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    // ==================== LL CASE ====================

    cout << "--- LL CASE ---" << endl;

    AVLTree<int> llTree;

    llTree.insert(30);
    llTree.insert(20);
    llTree.insert(10);

    /*
     * Before rotation:
     *
     *      30
     *     /
     *   20
     *   /
     * 10
     *
     * After right rotation, 20 becomes the root.
     */

    llTree.printTree();

    // ==================== RR CASE ====================

    cout << "\n--- RR CASE ---" << endl;

    AVLTree<int> rrTree;

    rrTree.insert(10);
    rrTree.insert(20);
    rrTree.insert(30);

    /*
     * Before:
     *
     * 10
     *   \
     *   20
     *     \
     *     30
     *
     * Left rotation makes 20 the root.
     */

    rrTree.printTree();

    // ==================== LR CASE ====================

    cout << "\n--- LR CASE ---" << endl;

    AVLTree<int> lrTree;

    lrTree.insert(30);
    lrTree.insert(10);
    lrTree.insert(20);

    lrTree.printTree();

    // ==================== RL CASE ====================

    cout << "\n--- RL CASE ---" << endl;

    AVLTree<int> rlTree;

    rlTree.insert(10);
    rlTree.insert(30);
    rlTree.insert(20);

    rlTree.printTree();

    // ==================== DELETION ====================

    cout << "\n--- DELETION ---" << endl;

    AVLTree<int> tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Tree: ";
    tree.printTree();

    tree.remove(20);

    cout << "After deleting 20: ";
    tree.printTree();

    tree.remove(50);

    cout << "After deleting 50: ";
    tree.printTree();

    return 0;
}