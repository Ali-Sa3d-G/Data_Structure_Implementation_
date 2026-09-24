#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                    DOUBLY LINKED LIST - LEARNING GUIDE
 * ============================================================================
 *
 * A doubly linked list is a linear data structure where each node contains:
 *
 *   1. Data
 *   2. A pointer to the NEXT node
 *   3. A pointer to the PREVIOUS node
 *
 * Visualization:
 *
 *   head
 *    |
 *    v
 *   [NULL | 10 | *] <-> [* | 20 | *] <-> [* | 30 | NULL]
 *                                           ^
 *                                           |
 *                                          tail
 *
 * Unlike a singly linked list, we can move in both directions.
 *
 * Advantages:
 *   - Forward and backward traversal
 *   - Easier deletion when the node is already known
 *   - Fast insertion at the beginning and end when head/tail exist
 *
 * Disadvantages:
 *   - Uses extra memory for the prev pointer
 *   - Pointer updates are more complicated
 *
 * Main Operations:
 *   - Insert at beginning
 *   - Insert at end
 *   - Insert after a value
 *   - Insert at position
 *   - Delete from beginning
 *   - Delete from end
 *   - Delete at position
 *   - Search
 *
 * Time Complexity:
 *   Insert at beginning : O(1)
 *   Insert at end       : O(1)
 *   Search              : O(n)
 *   Insert/Delete at position: O(n)
 *
 * Space Complexity: O(n)
 *
 * ============================================================================
 */

 // =========================== NODE CLASS ===========================

 /**
  * A Node represents one element in the doubly linked list.
  *
  * Visualization:
  *
  *        [ PREV | DATA | NEXT ]
  *            |      |      |
  *            |      |      +----> next node
  *            |      +-----------> stored value
  *            +------------------> previous node
  */
template <typename T>
class Node
{
public:
    T data;
    Node* next;
    Node* prev;

    // Creates a node with no neighbors yet.
    Node(T value)
    {
        data = value;
        next = NULL;
        prev = NULL;
    }
};

// =========================== DOUBLY LINKED LIST CLASS ===========================

/**
 * The LinkedList class manages all nodes.
 *
 * head -> first node
 * tail -> last node
 *
 * For a normal doubly linked list:
 *
 *   head->prev == NULL
 *   tail->next == NULL
 */
template <typename T>
class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    int nodeCount;

public:

    // ==================== CONSTRUCTOR ====================

    /**
     * Creates an empty linked list.
     */
    LinkedList()
    {
        head = NULL;
        tail = NULL;
        nodeCount = 0;
    }

    // ==================== HELPER METHODS ====================

    bool isEmpty() const
    {
        return nodeCount == 0;
    }

    int getSize() const
    {
        return nodeCount;
    }

    // ==================== INSERTION OPERATIONS ====================

    /**
     * INSERT AT BEGINNING
     *
     * Example:
     *
     * Before:
     *   head -> [10] <-> [20] <-> [30] <- tail
     *
     * Insert 5:
     *
     * Step 1: Create [5]
     * Step 2: Make 5->next point to old head
     * Step 3: Make old head->prev point to 5
     * Step 4: Move head to 5
     *
     * After:
     *   head -> [5] <-> [10] <-> [20] <-> [30] <- tail
     *
     * Time Complexity: O(1)
     */
    void insertAtBeginning(T data)
    {
        Node<T>* newNode = new Node<T>(data);

        if (isEmpty())
        {
            // In an empty list, the new node is both head and tail.
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;

            head = newNode;
        }

        nodeCount++;
    }

    /**
     * INSERT AT END
     *
     * Because we keep a tail pointer, we don't need to traverse the list.
     *
     * Before:
     *
     *   head -> [10] <-> [20] <-> [30] <- tail
     *
     * Insert 40:
     *
     *   head -> [10] <-> [20] <-> [30] <-> [40] <- tail
     *
     * Time Complexity: O(1)
     */
    void insertAtEnd(T data)
    {
        Node<T>* newNode = new Node<T>(data);

        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            // Connect the old tail to the new node.
            tail->next = newNode;
            newNode->prev = tail;

            // New node becomes the tail.
            tail = newNode;
        }

        nodeCount++;
    }

    /**
     * INSERT AFTER A SPECIFIC VALUE
     *
     * Example:
     *
     * Before:
     *   [10] <-> [20] <-> [30]
     *
     * Insert 25 after 20:
     *
     *   [10] <-> [20] <-> [25] <-> [30]
     *
     * The new node must be connected in BOTH directions.
     */
    void insertAfter(T data, T afterValue)
    {
        Node<T>* currentNode = head;

        // Find the node containing afterValue.
        while (currentNode != NULL && currentNode->data != afterValue)
        {
            currentNode = currentNode->next;
        }

        if (currentNode == NULL)
            return;

        Node<T>* newNode = new Node<T>(data);

        // Connect new node to its two neighbors.
        newNode->next = currentNode->next;
        newNode->prev = currentNode;

        // Connect the next node back to the new node.
        if (currentNode->next != NULL)
        {
            currentNode->next->prev = newNode;
        }
        else
        {
            // We inserted after the old tail.
            tail = newNode;
        }

        // Connect current node to the new node.
        currentNode->next = newNode;

        nodeCount++;
    }

    /**
     * INSERT AT POSITION
     *
     * Position 0 -> beginning
     * Position size -> end
     * Anything between them -> middle
     */
    void insertAtPosition(T data, int position)
    {
        if (position < 0 || position > nodeCount)
        {
            cout << "Invalid position." << endl;
            return;
        }

        if (position == 0)
        {
            insertAtBeginning(data);
            return;
        }

        if (position == nodeCount)
        {
            insertAtEnd(data);
            return;
        }

        Node<T>* currentNode = head;

        // Move to the node currently at this position.
        for (int i = 0; i < position; i++)
        {
            currentNode = currentNode->next;
        }

        Node<T>* newNode = new Node<T>(data);

        /*
         * Insert between currentNode->prev and currentNode.
         *
         *   A <-> currentNode
         *
         * becomes
         *
         *   A <-> newNode <-> currentNode
         */
        newNode->prev = currentNode->prev;
        newNode->next = currentNode;

        currentNode->prev->next = newNode;
        currentNode->prev = newNode;

        nodeCount++;
    }

    // ==================== DISPLAY OPERATIONS ====================

    /**
     * DISPLAY FORWARD
     *
     * Traverses from head to tail using next pointers.
     */
    void displayForward() const
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* currentNode = head;

        cout << "Forward: ";

        while (currentNode != NULL)
        {
            cout << currentNode->data;

            if (currentNode->next != NULL)
                cout << " <-> ";

            currentNode = currentNode->next;
        }

        cout << endl;
    }

    /**
     * DISPLAY REVERSE
     *
     * Traverses from tail to head using prev pointers.
     */
    void displayReverse() const
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* currentNode = tail;

        cout << "Reverse: ";

        while (currentNode != NULL)
        {
            cout << currentNode->data;

            if (currentNode->prev != NULL)
                cout << " <-> ";

            currentNode = currentNode->prev;
        }

        cout << endl;
    }

    // ==================== SEARCH OPERATION ====================

    /**
     * SEARCH
     *
     * Returns the index of the first occurrence.
     * Returns -1 if the value is not found.
     *
     * Time Complexity: O(n)
     */
    int search(T key) const
    {
        Node<T>* currentNode = head;
        int position = 0;

        while (currentNode != NULL)
        {
            if (currentNode->data == key)
                return position;

            currentNode = currentNode->next;
            position++;
        }

        return -1;
    }

    // ==================== DELETION OPERATIONS ====================

    /**
     * DELETE FROM BEGINNING
     *
     * Before:
     *
     *   head -> [10] <-> [20] <-> [30] <- tail
     *
     * Steps:
     *   1. Save the old head.
     *   2. Move head to the next node.
     *   3. Remove the new head's prev link.
     *   4. Delete the old node.
     *
     * Time Complexity: O(1)
     */
    void deleteFromBeginning()
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* nodeToDelete = head;

        if (head == tail)
        {
            // The list has only one node.
            head = tail = NULL;
        }
        else
        {
            head = head->next;

            // The new head has no previous node.
            head->prev = NULL;
        }

        delete nodeToDelete;
        nodeCount--;
    }

    /**
     * DELETE FROM END
     *
     * Because we have a tail pointer,
     * we can delete the last node directly.
     *
     * Time Complexity: O(1)
     */
    void deleteFromEnd()
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* nodeToDelete = tail;

        if (head == tail)
        {
            head = tail = NULL;
        }
        else
        {
            tail = tail->prev;

            // The new tail has no next node.
            tail->next = NULL;
        }

        delete nodeToDelete;
        nodeCount--;
    }

    /**
     * DELETE AT POSITION
     *
     * Example:
     *
     *   [10] <-> [20] <-> [30] <-> [40]
     *                 ^
     *              delete
     *
     * Connect:
     *
     *   [10] <-> [30] <-> [40]
     *
     * Both directions must be updated.
     */
    void deleteAtPosition(int position)
    {
        if (position < 0 || position >= nodeCount)
        {
            cout << "Invalid position." << endl;
            return;
        }

        if (position == 0)
        {
            deleteFromBeginning();
            return;
        }

        if (position == nodeCount - 1)
        {
            deleteFromEnd();
            return;
        }

        Node<T>* currentNode = head;

        for (int i = 0; i < position; i++)
        {
            currentNode = currentNode->next;
        }

        // Connect the two neighbors together.
        currentNode->prev->next = currentNode->next;
        currentNode->next->prev = currentNode->prev;

        delete currentNode;
        nodeCount--;
    }

    /**
     * DELETE ALL NODES
     *
     * Deletes every node and returns the list to
     * its empty state.
     *
     * Time Complexity: O(n)
     */
    void deleteAllNodes()
    {
        while (head != NULL)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        head = NULL;
        tail = NULL;
        nodeCount = 0;
    }

    // ==================== DESTRUCTOR ====================

    /**
     * Automatically frees all nodes when the list is destroyed.
     */
    ~LinkedList()
    {
        deleteAllNodes();
    }
};

// =========================== MAIN FUNCTION - DEMONSTRATION ===========================

int main()
{
    LinkedList<int> list;

    // ==================== INSERTION ====================

    cout << "--- INSERTION OPERATIONS ---" << endl;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    list.displayForward();

    list.insertAtBeginning(5);
    list.insertAtPosition(15, 2);
    list.insertAfter(25, 20);

    list.displayForward();
    list.displayReverse();

    // ==================== SEARCH ====================

    cout << "\n--- SEARCH ---" << endl;

    cout << "Index of 20: " << list.search(20) << endl;
    cout << "Index of 100: " << list.search(100) << endl;

    // ==================== DELETION ====================

    cout << "\n--- DELETION OPERATIONS ---" << endl;

    list.deleteFromBeginning();
    list.displayForward();

    list.deleteFromEnd();
    list.displayForward();

    list.deleteAtPosition(1);
    list.displayForward();

    cout << "\nList size: " << list.getSize() << endl;

    return 0;
}