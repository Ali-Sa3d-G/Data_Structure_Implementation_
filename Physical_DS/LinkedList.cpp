#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                      SINGLY LINKED LIST - LEARNING GUIDE
 * ============================================================================
 *
 * A singly linked list is a collection of nodes.
 *
 * Each node contains:
 *   1. Data
 *   2. A pointer to the NEXT node
 *
 * Visualization:
 *
 *   head
 *    |
 *    v
 *   [10 | *] -> [20 | *] -> [30 | NULL]
 *
 * Every node points only FORWARD.
 *
 * Main Operations:
 *   - Insert at beginning
 *   - Insert at end
 *   - Insert before / after a value
 *   - Insert at index
 *   - Search
 *   - Delete
 *   - Reverse
 *
 * Time Complexity:
 *   Insert at beginning : O(1)
 *   Insert at end       : O(n)
 *   Search              : O(n)
 *   Delete              : O(n)
 *   Reverse             : O(n)
 *
 * Space Complexity: O(n)
 *
 * ============================================================================
 */

 // =========================== NODE CLASS ===========================

 /**
  * A Node represents one element of the linked list.
  *
  * Visual representation:
  *
  *       [ DATA | NEXT ]
  *                |
  *                v
  *            next node
  */
template <typename T>
class Node
{
public:
    T data;
    Node* next;

    // Constructor: creates a node with the given value.
    Node(T value)
    {
        data = value;
        next = nullptr;
    }
};

// =========================== LINKED LIST CLASS ===========================

/**
 * The LinkedList class manages the nodes.
 *
 * head points to the FIRST node.
 *
 * Example:
 *
 *   head --> [10] --> [20] --> [30] --> NULL
 */
template <typename T>
class LinkedList
{
private:
    Node<T>* head;
    int size;

public:

    // ==================== CONSTRUCTOR ====================

    /**
     * Creates an empty linked list.
     */
    LinkedList()
    {
        head = nullptr;
        size = 0;
    }

    // ==================== HELPER METHODS ====================

    bool isEmpty() const
    {
        return head == nullptr;
    }

    int getSize() const
    {
        return size;
    }

    // ==================== INSERTION OPERATIONS ====================

    /**
     * INSERT AT BEGINNING
     *
     * Example:
     *
     *   Before:
     *   head -> [10] -> [20] -> [30]
     *
     *   Insert 5
     *
     *   Step 1: Create [5]
     *   Step 2: [5] points to old head
     *   Step 3: Move head to [5]
     *
     *   After:
     *   head -> [5] -> [10] -> [20] -> [30]
     *
     * Time Complexity: O(1)
     */
    void insertAtBeginning(T data)
    {
        Node<T>* newNode = new Node<T>(data);

        // Connect new node to the old head.
        newNode->next = head;

        // Make the new node the head.
        head = newNode;

        size++;
    }

    /**
     * INSERT AT END
     *
     * Finds the last node and connects it to the new node.
     *
     * Time Complexity: O(n)
     */
    void insertAtEnd(T data)
    {
        Node<T>* newNode = new Node<T>(data);

        if (isEmpty())
        {
            head = newNode;
        }
        else
        {
            Node<T>* current = head;

            // Move until the last node.
            while (current->next != nullptr)
            {
                current = current->next;
            }

            current->next = newNode;
        }

        size++;
    }

    /**
     * INSERT AFTER A SPECIFIC VALUE
     *
     * Example:
     *
     *   [10] -> [20] -> [30]
     *
     *   Insert 25 after 20:
     *
     *   [10] -> [20] -> [25] -> [30]
     */
    void insertAfter(T target, T data)
    {
        Node<T>* current = head;

        // Search for the target node.
        while (current != nullptr && current->data != target)
        {
            current = current->next;
        }

        if (current == nullptr)
            return;

        Node<T>* newNode = new Node<T>(data);

        // Put new node between current and current->next.
        newNode->next = current->next;
        current->next = newNode;

        size++;
    }

    /**
     * INSERT BEFORE A SPECIFIC VALUE
     *
     * Example:
     *
     *   [10] -> [20] -> [30]
     *
     *   Insert 15 before 20:
     *
     *   [10] -> [15] -> [20] -> [30]
     */
    void insertBefore(T target, T data)
    {
        if (isEmpty())
            return;

        // Special case: target is the head.
        if (head->data == target)
        {
            insertAtBeginning(data);
            return;
        }

        Node<T>* current = head;

        // Find the node just before target.
        while (current->next != nullptr &&
            current->next->data != target)
        {
            current = current->next;
        }

        if (current->next == nullptr)
            return;

        Node<T>* newNode = new Node<T>(data);

        newNode->next = current->next;
        current->next = newNode;

        size++;
    }

    /**
     * INSERT AT INDEX
     *
     * Index 0 means the beginning.
     */
    void insertAtIndex(int index, T data)
    {
        if (index < 0 || index > size)
            return;

        if (index == 0)
        {
            insertAtBeginning(data);
            return;
        }

        Node<T>* current = head;

        // Reach the node before the insertion position.
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }

        Node<T>* newNode = new Node<T>(data);

        newNode->next = current->next;
        current->next = newNode;

        size++;
    }

    // ==================== SEARCH OPERATIONS ====================

    /**
     * SEARCH
     *
     * Returns the index of the first occurrence.
     * Returns -1 if the value does not exist.
     *
     * Time Complexity: O(n)
     */
    int search(T key) const
    {
        Node<T>* current = head;
        int index = 0;

        while (current != nullptr)
        {
            if (current->data == key)
                return index;

            current = current->next;
            index++;
        }

        return -1;
    }

    /**
     * Checks whether a value exists in the list.
     */
    bool isFound(T key) const
    {
        return search(key) != -1;
    }

    // ==================== DELETION OPERATIONS ====================

    /**
     * DELETE FIRST NODE
     *
     * Example:
     *
     *   head -> [10] -> [20] -> [30]
     *
     *   Move head:
     *
     *   head -> [20] -> [30]
     *
     * Then delete the old head.
     *
     * Time Complexity: O(1)
     */
    void deleteFirst()
    {
        if (isEmpty())
            return;

        Node<T>* nodeToDelete = head;

        head = head->next;

        delete nodeToDelete;

        size--;
    }

    /**
     * DELETE LAST NODE
     *
     * We need the node BEFORE the last node
     * so that it can point to NULL.
     *
     * Time Complexity: O(n)
     */
    void deleteLast()
    {
        if (isEmpty())
            return;

        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            size = 0;
            return;
        }

        Node<T>* current = head;

        while (current->next->next != nullptr)
        {
            current = current->next;
        }

        delete current->next;
        current->next = nullptr;

        size--;
    }

    /**
     * DELETE AT INDEX
     *
     * Finds the node before the target,
     * skips the target, then deletes it.
     */
    void deleteAtIndex(int index)
    {
        if (index < 0 || index >= size)
            return;

        if (index == 0)
        {
            deleteFirst();
            return;
        }

        Node<T>* current = head;

        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }

        Node<T>* nodeToDelete = current->next;

        // Bypass the node to delete.
        current->next = nodeToDelete->next;

        delete nodeToDelete;

        size--;
    }

    /**
     * DELETE BY VALUE
     *
     * Deletes the first occurrence of key.
     */
    void deleteByValue(T key)
    {
        int index = search(key);

        if (index != -1)
            deleteAtIndex(index);
    }

    // ==================== REVERSAL ====================

    /**
     * REVERSE
     *
     * Reverses the direction of all next pointers.
     *
     * Before:
     *
     *   head -> [10] -> [20] -> [30] -> NULL
     *
     * After:
     *
     *   head -> [30] -> [20] -> [10] -> NULL
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    void reverse()
    {
        Node<T>* previous = nullptr;
        Node<T>* current = head;

        while (current != nullptr)
        {
            Node<T>* nextNode = current->next;

            // Reverse the current node's pointer.
            current->next = previous;

            previous = current;
            current = nextNode;
        }

        head = previous;
    }

    // ==================== DISPLAY ====================

    void display() const
    {
        Node<T>* current = head;

        cout << "head -> ";

        while (current != nullptr)
        {
            cout << current->data << " -> ";
            current = current->next;
        }

        cout << "NULL\n";
    }

    // ==================== CLEAR ====================

    /**
     * DELETE ALL NODES
     *
     * Deletes every node and returns the list
     * to its empty state.
     *
     * Time Complexity: O(n)
     */
    void clear()
    {
        while (head != nullptr)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }

        size = 0;
    }

    // ==================== DESTRUCTOR ====================

    ~LinkedList()
    {
        clear();
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    LinkedList<int> list;

    cout << "--- INSERTION ---\n";

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);

    list.display();

    list.insertAtBeginning(5);
    list.insertAfter(20, 25);
    list.insertBefore(30, 27);

    list.display();

    cout << "\nIndex of 25: "
        << list.search(25) << "\n";

    cout << "\n--- DELETION ---\n";

    list.deleteFirst();
    list.deleteLast();
    list.deleteByValue(20);

    list.display();

    cout << "\n--- REVERSE ---\n";

    list.reverse();
    list.display();

    return 0;
}