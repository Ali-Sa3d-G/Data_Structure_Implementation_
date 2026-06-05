#include<iostream>
using namespace std;

/**
 * ============================================================================
 * DOUBLY LINKED LIST - COMPLETE LEARNING GUIDE
 * ============================================================================
 *
 * A doubly linked list is a linear data structure where each node contains:
 *   1. Data (the actual value)
 *   2. A pointer to the NEXT node
 *   3. A pointer to the PREVIOUS node
 *
 * Advantages over singly linked list:
 *   - Can traverse in both directions (forward AND backward)
 *   - Easier deletion operations (don't need to track previous node)
 *
 * Disadvantages:
 *   - Uses more memory (extra pointer per node)
 *   - Slightly more complex insertion/deletion logic
 *
 * ============================================================================
 */

 // =========================== NODE CLASS ===========================
 /**
  * A Node represents a single element in the linked list.
  * Each node is a building block that connects to its neighbors.
  *
  * Visual representation:
  *   [ PREV | DATA | NEXT ]
  *      ^      ^       ^
  *      |      |       |
  *   pointer to  |   pointer to
  *   previous    |   next node
  *           actual data
  */
template <typename T>
class Node {
public:
    T data;          // The actual value stored in this node
    Node* next;      // Pointer to the next node (or NULL if last)
    Node* prev;      // Pointer to the previous node (or NULL if first)

    // Constructor: creates a node with given data
    Node(T value) {
        data = value;
        next = NULL;  // Initially, no next node
        prev = NULL;  // Initially, no previous node
    }
};

// =========================== LINKED LIST CLASS ===========================
/**
 * The LinkedList class manages a collection of nodes.
 * It keeps track of the HEAD (first node) and TAIL (last node).
 *
 * Visual representation of a list with three nodes:
 *
 *   head --> [ NULL | 10 | * ] --> [ * | 20 | * ] --> [ * | 30 | NULL ] <-- tail
 *                  ^                    ^                    ^
 *                prev points          prev points          prev points
 *                to NULL              to previous          to previous
 */
template <typename T>
class LinkedList {
private:
    Node<T>* head;   // Points to the FIRST node in the list
    Node<T>* tail;   // Points to the LAST node in the list
    int nodeCount;   // Tracks how many nodes are in the list

public:
    // ==================== CONSTRUCTOR ====================
    /**
     * Initializes an empty linked list.
     * No nodes exist yet.
     */
    LinkedList() {
        head = NULL;
        tail = NULL;
        nodeCount = 0;
    }

    // ==================== HELPER METHODS ====================

    /**
     * Checks if the list is empty.
     * Returns true if no nodes exist, false otherwise.
     */
    bool isEmpty() const {
        return nodeCount == 0;
    }

    /**
     * Returns the number of nodes in the list.
     */
    int getSize() const {
        return nodeCount;
    }

    // ==================== INSERTION OPERATIONS ====================

    /**
     * INSERT AT BEGINNING
     * Adds a new node at the START of the list.
     *
     * Step-by-step for inserting 5 at beginning:
     *
     * Before: head --> [10] <-> [20] <-> [30] <-- tail
     *
     * Step 1: Create new node [5]
     * Step 2: Point new node's next to current head (10)
     * Step 3: Point current head's prev to new node
     * Step 4: Update head to point to new node
     *
     * After:  head --> [5] <-> [10] <-> [20] <-> [30] <-- tail
     */
    void insertAtBeginning(T data) {
        // Step 1: Create the new node
        Node<T>* newNode = new Node<T>(data);
        nodeCount++;

        // Special case: List was empty
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            // Step 2: Connect new node to current head
            newNode->next = head;

            // Step 3: Connect current head back to new node
            head->prev = newNode;

            // Step 4: Update head to be the new node
            head = newNode;
        }
    }

    /**
     * INSERT AT END
     * Adds a new node at the END of the list.
     *
     * Step-by-step for inserting 40 at end:
     *
     * Before: head --> [10] <-> [20] <-> [30] <-- tail
     *
     * Step 1: Create new node [40]
     * Step 2: Point current tail's next to new node
     * Step 3: Point new node's prev to current tail
     * Step 4: Update tail to point to new node
     *
     * After:  head --> [10] <-> [20] <-> [30] <-> [40] <-- tail
     */
    void insertAtEnd(T data) {
        // Step 1: Create the new node
        Node<T>* newNode = new Node<T>(data);
        nodeCount++;

        // Special case: List was empty
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            // Step 2: Connect current tail to new node
            tail->next = newNode;

            // Step 3: Connect new node back to current tail
            newNode->prev = tail;

            // Step 4: Update tail to be the new node
            tail = newNode;
        }
    }

    /**
     * INSERT AFTER A SPECIFIC VALUE
     * Finds a node with 'afterValue' and inserts a new node right after it.
     *
     * Example: Insert 25 after 20
     *
     * Before: [10] <-> [20] <-> [30]
     *                      |
     *                      v
     * Step 1: Find node with value 20
     * Step 2: Create new node [25]
     * Step 3: Connect 25's next to 20's next (which is 30)
     * Step 4: Connect 25's prev to 20
     * Step 5: Connect 30's prev to 25
     * Step 6: Connect 20's next to 25
     *
     * After:  [10] <-> [20] <-> [25] <-> [30]
     */
    void insertAfter(T data, T afterValue) {
        // Step 1: Find the node containing 'afterValue'
        Node<T>* currentNode = head;
        while (currentNode != NULL && currentNode->data != afterValue) {
            currentNode = currentNode->next;
        }

        // If we found the node
        if (currentNode != NULL) {
            // Step 2: Create the new node
            Node<T>* newNode = new Node<T>(data);

            // Step 3: Connect new node to the next node
            newNode->next = currentNode->next;

            // Step 4: Connect new node back to current node
            newNode->prev = currentNode;

            // Step 5: If there is a next node, connect it back to new node
            if (currentNode->next != NULL) {
                currentNode->next->prev = newNode;
            }
            else {
                // If we're inserting at the end, update tail
                tail = newNode;
            }

            // Step 6: Connect current node to new node
            currentNode->next = newNode;
            nodeCount++;
        }
        else {
            cout << "Warning: Value " << afterValue << " not found in list!" << endl;
        }
    }

    /**
     * INSERT AT SPECIFIC POSITION
     * Inserts a node at the given index (0-based).
     *
     * Positions:
     *   pos = 0 --> insert at beginning
     *   pos = size --> insert at end
     *   other --> insert somewhere in the middle
     */
    void insertAtPosition(T data, int position) {
        // Validate position
        if (position < 0 || position > nodeCount) {
            cout << "Error: Invalid position! Valid range: 0 to " << nodeCount << endl;
            return;
        }

        // Insert at beginning
        if (position == 0) {
            insertAtBeginning(data);
        }
        // Insert at end
        else if (position == nodeCount) {
            insertAtEnd(data);
        }
        // Insert in the middle
        else {
            // Traverse to the node BEFORE the insertion point
            Node<T>* currentNode = head;
            for (int i = 0; i < position - 1; i++) {
                currentNode = currentNode->next;
            }

            // Create new node
            Node<T>* newNode = new Node<T>(data);

            // Connect new node to its neighbors
            newNode->next = currentNode->next;
            newNode->prev = currentNode;

            // Connect neighbors to new node
            currentNode->next->prev = newNode;
            currentNode->next = newNode;

            nodeCount++;
        }
    }

    // ==================== DISPLAY OPERATIONS ====================

    /**
     * DISPLAY FORWARD
     * Prints the list from head to tail.
     *
     * Example output: 10 20 30 40
     */
    void displayForward() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }

        Node<T>* currentNode = head;
        cout << "Forward traversal (head -> tail): ";
        while (currentNode != NULL) {
            cout << currentNode->data;
            if (currentNode->next != NULL) cout << " <-> ";
            currentNode = currentNode->next;
        }
        cout << endl;
    }

    /**
     * DISPLAY REVERSE
     * Prints the list from tail to head.
     *
     * Example output: 40 30 20 10
     */
    void displayReverse() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }

        Node<T>* currentNode = tail;
        cout << "Reverse traversal (tail -> head): ";
        while (currentNode != NULL) {
            cout << currentNode->data;
            if (currentNode->prev != NULL) cout << " <-> ";
            currentNode = currentNode->prev;
        }
        cout << endl;
    }

    // ==================== SEARCH OPERATION ====================

    /**
     * SEARCH FOR A VALUE
     * Finds the position (index) of a given value.
     * Returns the position if found, -1 if not found.
     */
    int search(T key) {
        Node<T>* currentNode = head;
        int position = 0;

        while (currentNode != NULL) {
            if (currentNode->data == key) {
                cout << "[FOUND] " << key << " at position " << position << endl;
                return position;
            }
            currentNode = currentNode->next;
            position++;
        }

        cout << "[NOT FOUND] Value " << key << " not in list" << endl;
        return -1;
    }

    // ==================== DELETION OPERATIONS ====================

    /**
     * DELETE FROM BEGINNING
     * Removes the first node and updates head to point to the next node.
     *
     * Step-by-step:
     * Before: head --> [10] <-> [20] <-> [30] <-- tail
     *
     * Step 1: Store pointer to head node (to delete it later)
     * Step 2: Move head to the next node (20)
     * Step 3: Set new head's prev to NULL
     * Step 4: Delete the old head node
     *
     * After:  head --> [20] <-> [30] <-- tail
     */
    void deleteFromBeginning() {
        if (isEmpty()) {
            cout << "Error: Cannot delete - list is empty!" << endl;
            return;
        }

        Node<T>* nodeToDelete = head;

        // Special case: Only one node in list
        if (head == tail) {
            head = NULL;
            tail = NULL;
        }
        else {
            // Move head to next node
            head = head->next;
            // Disconnect the new head from the old node
            head->prev = NULL;
        }

        // Free the memory
        delete nodeToDelete;
        nodeCount--;
    }

    /**
     * DELETE FROM END
     * Removes the last node and updates tail to point to the previous node.
     */
    void deleteFromEnd() {
        if (isEmpty()) {
            cout << "Error: Cannot delete - list is empty!" << endl;
            return;
        }

        Node<T>* nodeToDelete = tail;

        // Special case: Only one node in list
        if (head == tail) {
            head = NULL;
            tail = NULL;
        }
        else {
            // Move tail to previous node
            tail = tail->prev;
            // Disconnect the new tail from the old node
            tail->next = NULL;
        }

        // Free the memory
        delete nodeToDelete;
        nodeCount--;
    }

    /**
     * DELETE AT SPECIFIC POSITION
     * Removes the node at the given index (0-based).
     */
    void deleteAtPosition(int position) {
        // Validate position
        if (position < 0 || position >= nodeCount) {
            cout << "Error: Invalid position! Valid range: 0 to " << nodeCount - 1 << endl;
            return;
        }

        // Delete from beginning
        if (position == 0) {
            deleteFromBeginning();
        }
        // Delete from end
        else if (position == nodeCount - 1) {
            deleteFromEnd();
        }
        // Delete from middle
        else {
            // Traverse to the node BEFORE the one to delete
            Node<T>* currentNode = head;
            for (int i = 0; i < position - 1; i++) {
                currentNode = currentNode->next;
            }

            // Node to delete is the next one
            Node<T>* nodeToDelete = currentNode->next;

            // Connect the node before to the node after
            currentNode->next = nodeToDelete->next;
            nodeToDelete->next->prev = currentNode;

            // Free the memory
            delete nodeToDelete;
            nodeCount--;
        }
    }

    /**
     * DELETE THE ENTIRE LIST
     * Removes all nodes and resets the list.
     */
    void deleteAllNodes() {
        while (head != NULL) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        head = NULL;
        tail = NULL;
        nodeCount = 0;
        cout << "List has been completely cleared." << endl;
    }

    // ==================== DESTRUCTOR ====================
    /**
     * Destructor automatically cleans up memory when the list goes out of scope.
     */
    ~LinkedList() {
        deleteAllNodes();
    }
};

// =========================== MAIN FUNCTION - TESTING ===========================
int main() {
    cout << "\n+================================================+" << endl;
    cout << "|     DOUBLY LINKED LIST - DEMONSTRATION PROGRAM    |" << endl;
    cout << "+================================================+\n" << endl;

    LinkedList<int> myList;

    // ===== TEST 1: INSERTION OPERATIONS =====
    cout << "[TEST 1] INSERTION OPERATIONS" << endl;
    cout << "----------------------------------------" << endl;

    cout << "\n1. Inserting at end: 10, 20, 30" << endl;
    myList.insertAtEnd(10);
    myList.insertAtEnd(20);
    myList.insertAtEnd(30);
    myList.displayForward();

    cout << "\n2. Inserting at beginning: 5" << endl;
    myList.insertAtBeginning(5);
    myList.displayForward();

    cout << "\n3. Inserting at position 2 (0-based): 15" << endl;
    myList.insertAtPosition(15, 2);
    myList.displayForward();

    cout << "\n4. Inserting after value 20: 25" << endl;
    myList.insertAfter(25, 20);
    myList.displayForward();

    cout << "\n5. Display in reverse order:" << endl;
    myList.displayReverse();

    // ===== TEST 2: SEARCH OPERATIONS =====
    cout << "\n[TEST 2] SEARCH OPERATIONS" << endl;
    cout << "----------------------------------------" << endl;
    myList.search(20);    // Should find
    myList.search(100);   // Should not find

    // ===== TEST 3: DELETION OPERATIONS =====
    cout << "\n[TEST 3] DELETION OPERATIONS" << endl;
    cout << "----------------------------------------" << endl;

    cout << "\nCurrent list: ";
    myList.displayForward();

    cout << "\n6. Deleting from beginning:" << endl;
    myList.deleteFromBeginning();
    myList.displayForward();

    cout << "\n7. Deleting from end:" << endl;
    myList.deleteFromEnd();
    myList.displayForward();

    cout << "\n8. Deleting at position 1:" << endl;
    myList.deleteAtPosition(1);
    myList.displayForward();

    // ===== FINAL STATISTICS =====
    cout << "\n[FINAL LIST STATISTICS]" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Final list contents: ";
    myList.displayForward();
    cout << "Number of nodes: " << myList.getSize() << endl;

    // Test empty list operations
    cout << "\n[TESTING EDGE CASES]" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Testing deletion from empty list (should show error):" << endl;
    LinkedList<int> emptyList;
    emptyList.deleteFromBeginning();

    cout << "\nProgram completed successfully!" << endl;

    return 0;
}