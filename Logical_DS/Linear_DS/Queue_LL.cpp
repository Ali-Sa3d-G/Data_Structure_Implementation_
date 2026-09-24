#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                         QUEUE - LEARNING GUIDE
 * ============================================================================
 *
 * A Queue follows the FIFO rule:
 *
 *       First In -> First Out
 *
 * Example:
 *
 *       enqueue(10)
 *       enqueue(20)
 *       enqueue(30)
 *
 *       FRONT                          REAR
 *         |                              |
 *         v                              v
 *       [10] -> [20] -> [30] -> NULL
 *
 * 10 is the first element to leave the queue.
 *
 * Main Operations:
 *   - enqueue -> add at rear
 *   - dequeue -> remove from front
 *   - getFront -> see first element
 *   - getRear -> see last element
 *
 * By keeping both front and rear pointers,
 * enqueue and dequeue can both be O(1).
 *
 * Time Complexity:
 *   Enqueue     : O(1)
 *   Dequeue     : O(1)
 *   Front / Rear: O(1)
 *   Search      : O(n)
 *
 * Space Complexity: O(n)
 *
 * ============================================================================
 */

 // =========================== NODE CLASS ===========================

class Node
{
public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

// =========================== QUEUE CLASS ===========================

class Queue
{
private:
    Node* front;
    Node* rear;

public:

    // ==================== CONSTRUCTOR ====================

    /**
     * Creates an empty queue.
     *
     * Both front and rear are NULL.
     */
    Queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    // ==================== HELPER ====================

    bool isEmpty() const
    {
        return front == nullptr;
    }

    // ==================== ENQUEUE ====================

    /**
     * ENQUEUE
     *
     * Adds an element at the rear.
     *
     * Before:
     *
     *   front -> [10] -> [20] -> NULL <- rear
     *
     * enqueue(30)
     *
     * After:
     *
     *   front -> [10] -> [20] -> [30] -> NULL <- rear
     *
     * Time Complexity: O(1)
     */
    void enqueue(int value)
    {
        Node* newNode = new Node(value);

        if (isEmpty())
        {
            // First node is both front and rear.
            front = rear = newNode;
            return;
        }

        // Add the new node after the current rear.
        rear->next = newNode;

        // Move rear to the new node.
        rear = newNode;
    }

    // ==================== DEQUEUE ====================

    /**
     * DEQUEUE
     *
     * Removes the element at the front.
     *
     * Before:
     *
     *   front
     *     |
     *     v
     *   [10] -> [20] -> [30]
     *
     * After:
     *
     *   front
     *     |
     *     v
     *   [20] -> [30]
     *
     * Time Complexity: O(1)
     */
    int dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue underflow." << endl;
            return -1;
        }

        Node* nodeToDelete = front;
        int value = front->data;

        front = front->next;

        // If the queue became empty, rear must also be NULL.
        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete nodeToDelete;

        return value;
    }

    // ==================== FRONT / REAR ====================

    /**
     * Returns the first element without removing it.
     */
    int getFront() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return -1;
        }

        return front->data;
    }

    /**
     * Returns the last element without removing it.
     */
    int getRear() const
    {
        if (isEmpty())
        {
            cout << "Queue is empty." << endl;
            return -1;
        }

        return rear->data;
    }

    // ==================== SEARCH ====================

    int search(int key) const
    {
        Node* current = front;
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

    bool isFound(int key) const
    {
        return search(key) != -1;
    }

    // ==================== COUNT ====================

    int count() const
    {
        int numberOfElements = 0;
        Node* current = front;

        while (current != nullptr)
        {
            numberOfElements++;
            current = current->next;
        }

        return numberOfElements;
    }

    // ==================== DISPLAY ====================

    void display() const
    {
        Node* current = front;

        cout << "FRONT -> ";

        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << "<- REAR" << endl;
    }

    // ==================== CLEAR ====================

    /**
     * Removes all elements from the queue.
     */
    void clear()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    // ==================== DESTRUCTOR ====================

    ~Queue()
    {
        clear();
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    Queue queue;

    // ==================== ENQUEUE ====================

    cout << "--- ENQUEUE ---" << endl;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    queue.display();

    // ==================== FRONT / REAR ====================

    cout << "\nFront: " << queue.getFront() << endl;
    cout << "Rear: " << queue.getRear() << endl;

    // ==================== DEQUEUE ====================

    cout << "\n--- DEQUEUE ---" << endl;

    cout << "Dequeued: "
        << queue.dequeue() << endl;

    queue.display();

    // ==================== SEARCH ====================

    cout << "\nIndex of 30: "
        << queue.search(30) << endl;

    cout << "Is 50 found? "
        << (queue.isFound(50) ? "Yes" : "No") << endl;

    // ==================== COUNT ====================

    cout << "\nNumber of elements: "
        << queue.count() << endl;

    return 0;
}