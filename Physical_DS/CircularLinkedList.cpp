#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                CIRCULAR DOUBLY LINKED LIST - LEARNING GUIDE
 * ============================================================================
 *
 * A Circular Doubly Linked List combines two ideas:
 *
 *   1. Doubly Linked List
 *      Every node has next AND prev.
 *
 *   2. Circular Linked List
 *      The last node connects back to the first.
 *
 * Visualization:
 *
 *                    +--------------------------+
 *                    |                          |
 *                    v                          |
 *   head -> [10] <-> [20] <-> [30] <-> [40] <- tail
 *            ^                               |
 *            |_______________________________|
 *
 * Important circular links:
 *
 *       head->prev == tail
 *       tail->next == head
 *
 * There is NO NULL between the first and last nodes.
 *
 * Advantages:
 *   - Traverse forward and backward
 *   - Can keep moving around the list
 *   - Insert/delete at beginning and end in O(1)
 *
 * Disadvantages:
 *   - More pointer updates
 *   - Must be careful not to loop forever
 *
 * Time Complexity:
 *   Insert/Delete at beginning : O(1)
 *   Insert/Delete at end       : O(1)
 *   Search                     : O(n)
 *   Insert/Delete at position : O(n)
 *
 * Space Complexity: O(n)
 *
 * ============================================================================
 */

 // =========================== NODE CLASS ===========================

 /**
  * Each node stores:
  *
  *       [ PREV | DATA | NEXT ]
  *
  * When a single node is created:
  *
  *       +-------+
  *       |       |
  *       v       |
  *     [ 10 ]
  *       ^       |
  *       |_______|
  *
  * So the node points to itself in both directions.
  */
template <typename T>
class Node
{
public:
    T data;
    Node* next;
    Node* prev;

    Node(T value)
    {
        data = value;

        // A single node is circular by itself.
        next = this;
        prev = this;
    }
};

// =========================== CIRCULAR DOUBLY LINKED LIST ===========================

template <typename T>
class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:

    // ==================== CONSTRUCTOR ====================

    /**
     * Creates an empty circular doubly linked list.
     */
    LinkedList()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    // ==================== HELPER METHODS ====================

    bool isEmpty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }

    // ==================== INSERTION OPERATIONS ====================

    /**
     * INSERT AT BEGINNING
     *
     * Before:
     *
     *       tail <-> [10] <-> [20] <-> head
     *         ^                         |
     *         +-------------------------+
     *
     * We insert the new node before head.
     *
     * After:
     *
     *       tail <-> [5] <-> [10] <-> [20]
     *         ^                          |
     *         +--------------------------+
     */
    void insertInStart(T data)
    {
        Node<T>* newNode = new Node<T>(data);

        if (isEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            newNode->prev = tail;

            head->prev = newNode;
            tail->next = newNode;

            head = newNode;
        }

        size++;
    }

    /**
     * INSERT AT END
     *
     * Because tail is known, no traversal is needed.
     *
     * The new node is placed between tail and head.
     *
     * Time Complexity: O(1)
     */
    void insertEnd(T data)
    {
        if (isEmpty())
        {
            insertInStart(data);
            return;
        }

        Node<T>* newNode = new Node<T>(data);

        newNode->prev = tail;
        newNode->next = head;

        tail->next = newNode;
        head->prev = newNode;

        tail = newNode;

        size++;
    }

    /**
     * INSERT AT POSITION
     *
     * Position 0 -> beginning
     * Position size -> end
     * Otherwise -> insert in the middle
     */
    void insertAt(T data, int position)
    {
        if (position < 0 || position > size)
        {
            cout << "Invalid position." << endl;
            return;
        }

        if (position == 0)
        {
            insertInStart(data);
            return;
        }

        if (position == size)
        {
            insertEnd(data);
            return;
        }

        Node<T>* current = head;

        // Move to the node currently at this position.
        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }

        Node<T>* newNode = new Node<T>(data);

        // Insert newNode before current.
        newNode->prev = current->prev;
        newNode->next = current;

        current->prev->next = newNode;
        current->prev = newNode;

        size++;
    }

    // ==================== DISPLAY OPERATIONS ====================

    /**
     * DISPLAY FORWARD
     *
     * In a circular list, there is no NULL to stop at.
     * We use size to know how many nodes to visit.
     */
    void display() const
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* current = head;

        for (int i = 0; i < size; i++)
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }

    /**
     * DISPLAY REVERSE
     *
     * Start at tail and follow prev pointers.
     */
    void displayReverse() const
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* current = tail;

        for (int i = 0; i < size; i++)
        {
            cout << current->data << " ";
            current = current->prev;
        }

        cout << endl;
    }

    // ==================== SEARCH OPERATION ====================

    /**
     * SEARCH
     *
     * We cannot use current != NULL because the list is circular.
     * Instead, we stop after visiting exactly 'size' nodes.
     */
    int search(T key) const
    {
        if (isEmpty())
            return -1;

        Node<T>* current = head;

        for (int i = 0; i < size; i++)
        {
            if (current->data == key)
                return i;

            current = current->next;
        }

        return -1;
    }

    // ==================== CIRCULAR PROPERTY ====================

    /**
     * CHECK CIRCULAR LINKS
     *
     * For a correct circular doubly linked list:
     *
     *       head->prev == tail
     *       tail->next == head
     */
    void verifyCircular() const
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        cout << "head->prev = " << head->prev->data << endl;
        cout << "tail->next = " << tail->next->data << endl;
    }

    // ==================== DELETION OPERATIONS ====================

    /**
     * DELETE FROM BEGINNING
     *
     * Special case:
     * If there is only one node, both head and tail become NULL.
     *
     * Otherwise:
     *
     *   1. Move head to the next node.
     *   2. Connect new head back to tail.
     *   3. Connect tail back to new head.
     *   4. Delete the old head.
     */
    void deleteInStart()
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* nodeToDelete = head;

        if (size == 1)
        {
            head = tail = NULL;
        }
        else
        {
            head = head->next;

            head->prev = tail;
            tail->next = head;
        }

        delete nodeToDelete;
        size--;
    }

    /**
     * DELETE FROM END
     *
     * Move tail backward and reconnect it to head.
     *
     * Time Complexity: O(1)
     */
    void deleteEnd()
    {
        if (isEmpty())
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* nodeToDelete = tail;

        if (size == 1)
        {
            head = tail = NULL;
        }
        else
        {
            tail = tail->prev;

            tail->next = head;
            head->prev = tail;
        }

        delete nodeToDelete;
        size--;
    }

    /**
     * DELETE AT POSITION
     *
     * For a middle node:
     *
     *   [A] <-> [B] <-> [C]
     *             ^
     *           delete
     *
     * Connect A directly to C:
     *
     *   [A] <-> [C]
     */
    void deleteAt(int position)
    {
        if (position < 0 || position >= size)
        {
            cout << "Invalid position." << endl;
            return;
        }

        if (position == 0)
        {
            deleteInStart();
            return;
        }

        if (position == size - 1)
        {
            deleteEnd();
            return;
        }

        Node<T>* current = head;

        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;
        size--;
    }

    /**
     * DELETE ENTIRE LIST
     *
     * Because the list is circular, we cannot simply use:
     *
     *     while (head != NULL)
     *
     * We use the known size instead.
     */
    void deleteList()
    {
        if (isEmpty())
            return;

        Node<T>* current = head;

        for (int i = 0; i < size; i++)
        {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = tail = NULL;
        size = 0;
    }

    // ==================== DESTRUCTOR ====================

    /**
     * Automatically frees all nodes.
     */
    ~LinkedList()
    {
        deleteList();
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    LinkedList<int> list;

    // ==================== INSERTION ====================

    cout << "--- INSERTION ---" << endl;

    list.insertEnd(10);
    list.insertEnd(20);
    list.insertEnd(30);

    list.insertInStart(5);
    list.insertAt(15, 2);

    cout << "Forward: ";
    list.display();

    cout << "Reverse: ";
    list.displayReverse();

    // ==================== CIRCULAR PROPERTY ====================

    cout << "\n--- CIRCULAR LINKS ---" << endl;
    list.verifyCircular();

    // ==================== SEARCH ====================

    cout << "\nIndex of 20: "
        << list.search(20) << endl;

    // ==================== DELETION ====================

    cout << "\n--- DELETION ---" << endl;

    list.deleteInStart();
    list.deleteEnd();
    list.deleteAt(1);

    list.display();

    return 0;
}