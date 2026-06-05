#include <iostream>

using namespace std;


class Node{
    public:
        int data;
        Node* left;
        Node* right;

        // Constructor to initialize the node
        Node(int value){
            data = value;
            left = nullptr;
            right = nullptr;
        }
};



class BST{
    private:
        Node* root;

    public:
        // Constructor to initialize the BST
        BST(){
            root = nullptr;
        }

        // Function to get the value of the root node
        Node* getRoot(){
            if (root != nullptr){
                return root;
            }
            else{
                cout << "The BST is empty." << endl;
                return nullptr; // Return nullptr to indicate the BST is empty
            }
        }



        // Function to insert a value into the BST
        void insert(int value){
            root = insertRec(root, value);
        }

        // Recursive function to insert a value into the BST
        Node* insertRec(Node* node, int value){
            if (node == nullptr){
                return new Node(value);
            }
            if (value < node->data){
                node->left = insertRec(node->left, value);
            }
            else if (value > node->data){
                node->right = insertRec(node->right, value);
            }
            return node;
        }



        // Function for in-order traversal
        void inOrder(Node* root){
            if (root != nullptr){
                inOrder(root->left);
                cout << root->data << " ";
                inOrder(root->right);
            }
        }



        // Function for pre-order traversal
        void preOrder(Node* root){
            if (root != nullptr){
                cout << root->data << " ";
                preOrder(root->left);
                preOrder(root->right);
            }
        }


        // Function for post-order traversal
        void postOrder(Node* root){
            if (root != nullptr){
                postOrder(root->left);
                postOrder(root->right);
                cout << root->data << " ";
            }
        }   



        // Function to search for a value in the BST
        int search(int value){
            if (searchRec(root, value)){
                cout << "Value " << value << " found in the BST." << endl;
                return value;
            }
            else{
                cout << "Value " << value << " not found in the BST." << endl;
                return -1; // Return -1 to indicate value not found
            }
        }
        

        // Recursive function to search for a value in the BST
        bool searchRec(Node* node, int value){
            if (node == nullptr){
                return false;
            }
            if (node->data == value){
                return true;
            }
            else if (value < node->data){
                return searchRec(node->left, value);
            }
            else{
                return searchRec(node->right, value);
            }
        }


        // Function to find the minimum value in the BST
        int findMin(Node* node){
            if (node == nullptr){
                cout << "The BST is empty." << endl;
                return -1; // Return -1 to indicate the BST is empty
            }
            while (node->left != nullptr){
                node = node->left;
            }
            return node->data;
        }


        // Function to find the maximum value in the BST
        int findMax(Node* node){
            if (node == nullptr){
                cout << "The BST is empty." << endl;
                return -1; // Return -1 to indicate the BST is empty
            }   
            while (node->right != nullptr){
                node = node->right;
            }
            return node->data;
        }


        // Function to delete a value from the BST
        void deleteValue(int value){
            root = deleteRec(root, value);
        }

        // Recursive function to delete a value from the BST
        Node* deleteRec(Node* node, int value){
            if (node == nullptr){
                return node;
            }
            if (value < node->data){
                node->left = deleteRec(node->left, value);
            }
            else if (value > node->data){
                node->right = deleteRec(node->right, value);
            }
            else{
                // Node with only one child or no child
                if (node->left == nullptr){
                    Node* temp = node->right;
                    delete node;
                    return temp;
                }
                else if (node->right == nullptr){
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }
                // Node with two children: Get the inorder successor
                int minValue = findMin(node->right);
                node->data = minValue;
                node->right = deleteRec(node->right, minValue);
            }
            return node;
        }





};




int main() {
    BST bst;


    // 1. Test Insertion and In-Order Traversal
    cout << "--- 1. Testing Insertion and In-Order Traversal ---" << endl;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    cout << "In-Order Traversal (should be sorted): ";
    bst.inOrder(bst.getRoot()); // Should print 20 30 40 50 60 70 80
    cout << endl;


    // 2. Test Pre-Order Traversal
    cout << "--- 2. Testing Pre-Order Traversal ---" << endl;
    cout << "Pre-Order Traversal: ";
    bst.preOrder(bst.getRoot()); // Should print 50 30 20 40 70 60 80
    cout << endl;


    // 3. Test Post-Order Traversal
    cout << "--- 3. Testing Post-Order Traversal ---" << endl;
    cout << "Post-Order Traversal: ";
    bst.postOrder(bst.getRoot()); // Should print 20 40 30 60 80 70 50
    cout << endl;   


    // 4. Test Search Function
    cout << "--- 4. Testing Search Function ---" << endl;
    bst.search(40); // Should find 40
    bst.search(90); // Should not find 90
    cout << endl;


    // 5. Test Deletion
    cout << "--- 5. Testing Deletion ---" << endl;
    cout << "Deleting 20 (leaf node)..." << endl;
    bst.deleteValue(20);
    cout << "In-Order Traversal after deleting 20: ";
    bst.inOrder(bst.getRoot()); // Should print 30 40 50
    cout << endl;

    cout << "Deleting 30 (node with one child)..." << endl;
    bst.deleteValue(30);
    cout << "In-Order Traversal after deleting 30: ";
    bst.inOrder(bst.getRoot()); // Should print 40 50 60 70 80
    cout << endl;

    cout << "Deleting 50 (node with two children)..." << endl;
    bst.deleteValue(50);
    cout << "In-Order Traversal after deleting 50: ";
    bst.inOrder(bst.getRoot()); // Should print 40 60 70
    cout << endl;

    return 0;
}