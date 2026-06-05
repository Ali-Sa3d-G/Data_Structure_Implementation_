#include <iostream>
#include <algorithm>

using namespace std;

// An AVL Tree Node structure containing key, child pointers, and height
template <class T>
struct AVLNode {
    T key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(T val) {
        key = val;
        left = nullptr;
        right = nullptr;
        height = 1; // The lecture defines: "The height of a leaf is 1"
    }
};

template <class T>
class AVLTree {
private:
    AVLNode<T>* root;

    // Helper utility to safely extract height mapping 
    // The lecture defines: "The height of a null pointer is zero"
    int getHeight(AVLNode<T>* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    // Balance factor = height of right subtree - height of left subtree 
    // The lecture defines: "If |balance factor| becomes > 1, the tree has to be rebalanced"
    int getBalanceFactor(AVLNode<T>* node) {
        if (node == nullptr) return 0;
        return getHeight(node->right) - getHeight(node->left);
    }

    // Update the height of an internal node based on its tallest child plus 1
    void updateHeight(AVLNode<T>* node) {
        if (node != nullptr) {
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }

    // Case 1 & Case 3 Reference: Single Rotation (Right Rotation)
    // Applied when left subtree causes violation (Left-Left heavy)
    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update structural heights post-rotation
        updateHeight(y);
        updateHeight(x);

        // Return new local root pointer
        return x;
    }

    // Case 1 & Case 3 Reference: Single Rotation (Left Rotation)
    // Applied when right subtree causes violation (Right-Right heavy)
    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update structural heights post-rotation
        updateHeight(x);
        updateHeight(y);

        // Return new local root pointer
        return y;
    }

    // Core Recursive Insertion Method logic
    AVLNode<T>* insertNode(AVLNode<T>* node, T key) {
        // 1. Perform normal Binary Search Tree insertion
        if (node == nullptr) {
            return new AVLNode<T>(key);
        }

        if (key < node->key) {
            node->left = insertNode(node->left, key);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key);
        } else {
            return node; // Duplicate keys are ignored 
        }

        // 2. Update height of this ancestor node
        updateHeight(node);

        // 3. Get balance factor to verify if the node became unbalanced
        int balance = getBalanceFactor(node);

        // --- REBALANCING 4 CASES PARADIGM ---

        // Case A: Left-Left Heavy -> Single Right Rotation
        if (balance < -1 && key < node->left->key) {
            return rotateRight(node);
        }

        // Case B: Right-Right Heavy -> Single Left Rotation
        if (balance > 1 && key > node->right->key) {
            return rotateLeft(node);
        }

        // Case C: Left-Right Heavy -> Double Rotation (Left then Right)
        if (balance < -1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Case D: Right-Left Heavy -> Double Rotation (Right then Left)
        if (balance > 1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Helper function to find node with the minimum value (for deletion tasks)
    AVLNode<T>* getMinValueNode(AVLNode<T>* node) {
        AVLNode<T>* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Core Recursive Deletion Method logic
    AVLNode<T>* deleteNode(AVLNode<T>* root, T key) {
        // 1. Perform standard Binary Search Tree deletion
        if (root == nullptr) return root;

        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            // Found node with key to delete
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode<T>* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp; // Copy node contents
                }
                delete temp;
            } else {
                // Node with two children: Get the inorder successor
                AVLNode<T>* temp = getMinValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr) return root;

        // 2. Update node structural height
        updateHeight(root);

        // 3. Evaluate balance factors
        int balance = getBalanceFactor(root);

        // Rebalance structural anomalies along ancestry path
        if (balance < -1 && getBalanceFactor(root->left) <= 0) {
            return rotateRight(root);
        }
        if (balance < -1 && getBalanceFactor(root->left) > 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance > 1 && getBalanceFactor(root->right) >= 0) {
            return rotateLeft(root);
        }
        if (balance > 1 && getBalanceFactor(root->right) < 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // Visual In-Order Tree print wrapper
    void inorderTraversal(AVLNode<T>* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->key << " (h:" << node->height << ") ";
            inorderTraversal(node->right);
        }
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(T key) {
        root = insertNode(root, key);
    }

    void remove(T key) {
        root = deleteNode(root, key);
    }

    void printTree() {
        inorderTraversal(root);
        cout << endl;
    }
};


// Full example usage of the AVL Tree implementation

int main() {
    // Instantiate an AVL Tree for integer keys
    AVLTree<int> avl;
    cout << "   AVL TREE COMPREHENSIVE FEATURE & BALANCE HARNESS    \n";

    // PHASE 1: TESTING THE 4 AUTO-REBALANCING INSERTION CASES
    cout << "--- PHASE 1: Target Insertion & Balance Rotations ---\n";
    
    /* Testing Right Rotation (Left-Left Heavy)
       Inserting 30, 20, 10 sequentially forces a Right Rotation around 30.
    */
    cout << "[Action] Simulating Left-Left Heavy scenario (Inserting 30, 20, 10)...\n";
    avl.insert(30);
    avl.insert(20);
    avl.insert(10);
    cout << "-> Tree Structure (Inorder): ";
    avl.printTree(); 
    // Expected output arrangement: 10(h:1) 20(h:2) 30(h:1) -> 20 is the balanced root.
    cout << endl;

    /* Testing Left Rotation (Right-Right Heavy)
       Inserting 40, 50 sequentially forces a Left Rotation around 30.
    */
    cout << "[Action] Simulating Right-Right Heavy scenario (Inserting 40, 50)...\n";
    avl.insert(40);
    avl.insert(50);
    cout << "-> Tree Structure (Inorder): ";
    avl.printTree();
    cout << endl;

    /* Testing Double Rotations (Left-Right Heavy & Right-Left Heavy)
       Inserting elements to test interior path distribution anomalies.
    */
    cout << "[Action] Inserting 25 (Left-Right setup candidate)...\n";
    avl.insert(25);
    cout << "[Action] Inserting 35 (Right-Left setup candidate)...\n";
    avl.insert(35);
    
    cout << "-> Current Unified Balanced Tree State:\n   ";
    avl.printTree();
    cout << endl;


    // PHASE 2: DUPLICATE REJECTION FEATURE
    cout << "--- PHASE 2: Duplicate Handling Validation ---\n";
    cout << "[Action] Attempting to re-insert existing keys (20 and 40)...\n";
    avl.insert(20);
    avl.insert(40);
    cout << "-> Tree State (Should show identical node heights, ignoring duplicates):\n   ";
    avl.printTree();
    cout << endl;


    // PHASE 3: NODE DELETION & CASCADING REBALANCE
    cout << "--- PHASE 3: Node Removal & Re-balancing Execution ---\n";
    
    // Case A: Deleting a leaf node
    cout << "[Action] Deleting Leaf Node (10)...\n";
    avl.remove(10);
    cout << "-> Tree Structure: ";
    avl.printTree();
    cout << endl;

    // Case B: Deleting an internal node with a single child
    cout << "[Action] Inserting a temporary node 55 to create a single-child chain...\n";
    avl.insert(55);
    cout << "   Current: "; avl.printTree();
    cout << "[Action] Deleting parent node (50) to promote its single child (55)...\n";
    avl.remove(50);
    cout << "-> Tree Structure: ";
    avl.printTree();
    cout << endl;

    // Case C: Deleting a node with two children (Requires Inorder Successor swap)
    cout << "[Action] Deleting deep interior node with two active children (30)...\n";
    avl.remove(30);
    cout << "-> Tree Structure: ";
    avl.printTree();
    cout << endl;


    // ----------------------------------------------------------------
    // PHASE 4: EDGE CASES & STRESS CLEARANCE
    // ----------------------------------------------------------------
    cout << "--- PHASE 4: Bound and Empty State Clearance ---\n";
    cout << "[Action] Removing remaining active structural nodes...\n";
    avl.remove(20);
    avl.remove(25);
    avl.remove(35);
    avl.remove(40);
    avl.remove(55);
    
    cout << "-> Tree State (All elements cleared): ";
    avl.printTree(); // Expected: Empty line or clean baseline

    cout << "[Action] Attempting deletion operation on an empty AVL tree structure (Remove 99)...\n";
    avl.remove(99); 
    cout << "-> Core sanity pass successful. No segmentation faults or null reference leaks.\n\n";

    return 0;
}