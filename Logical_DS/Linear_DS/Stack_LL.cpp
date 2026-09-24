#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                         STACK - LEARNING GUIDE
 * ============================================================================
 *
 * A Stack follows the LIFO rule:
 *
 *       Last In -> First Out
 *
 * Example:
 *
 *       push(10)
 *       push(20)
 *       push(30)
 *
 *       TOP
 *        |
 *        v
 *       [30]
 *       [20]
 *       [10]
 *
 * The last element inserted (30)
 * is the first one removed.
 *
 * Main Operations:
 *   - push -> add to top
 *   - pop  -> remove from top
 *   - peek -> see top without removing
 *
 * Using a linked list, we keep the TOP at the first node.
 *
 * Time Complexity:
 *   Push : O(1)
 *   Pop  : O(1)
 *   Peek : O(1)
 *
 * Search / Count: O(n)
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

// =========================== STACK CLASS ===========================

class Stack
{
private:
    Node* top;

public:

    // ==================== CONSTRUCTOR ====================

    /**
     * Creates an empty stack.
     *
     * top == NULL means there are no elements.
     */
    Stack()
    {
        top = nullptr;
    }

    // ==================== HELPER ====================

    bool isEmpty() const
    {
        return top == nullptr;
    }

    // ==================== PUSH ====================

    /**
     * PUSH
     *
     * Adds a new element to the top.
     *
     * Before:
     *
     *       top
     *        |
     *        v
     *       [20] -> [10] -> NULL
     *
     * push(30)
     *
     * After:
     *
     *       top
     *        |
     *        v
     *       [30] -> [20] -> [10] -> NULL
     *
     * Time Complexity: O(1)
     */
    void push(int value)
    {
        Node* newNode = new Node(value);

        // New node points to the old top.
        newNode->next = top;

        // New node becomes the top.
        top = newNode;
    }

    // ==================== POP ====================

    /**
     * POP
     *
     * Removes and returns the top element.
     *
     * Before:
     *
     *       top
     *        |
     *        v
     *       [30] -> [20] -> [10]
     *
     * After pop:
     *
     *       top
     *        |
     *        v
     *       [20] -> [10]
     *
     * Time Complexity: O(1)
     */
    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack underflow." << endl;
            return -1;
        }

        Node* nodeToDelete = top;
        int value = top->data;

        top = top->next;

        delete nodeToDelete;

        return value;
    }

    // ==================== PEEK ====================

    /**
     * PEEK
     *
     * Returns the top value without removing it.
     */
    int peek() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return -1;
        }

        return top->data;
    }

    // ==================== SEARCH ====================

    int search(int key) const
    {
        Node* current = top;
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
        Node* current = top;

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
        Node* current = top;

        cout << "TOP -> ";

        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }

        cout << "-> NULL" << endl;
    }

    // ==================== CLEAR ====================

    /**
     * Deletes all nodes from the stack.
     */
    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    // ==================== DESTRUCTOR ====================

    ~Stack()
    {
        clear();
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    Stack stack;

    // ==================== PUSH ====================

    cout << "--- PUSH ---" << endl;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.display();

    // ==================== PEEK ====================

    cout << "\nTop element: "
        << stack.peek() << endl;

    // ==================== POP ====================

    cout << "\n--- POP ---" << endl;

    cout << "Popped: "
        << stack.pop() << endl;

    stack.display();

    // ==================== SEARCH ====================

    cout << "\nIndex of 10: "
        << stack.search(10) << endl;

    cout << "Is 50 found? "
        << (stack.isFound(50) ? "Yes" : "No") << endl;

    // ==================== COUNT ====================

    cout << "\nNumber of elements: "
        << stack.count() << endl;

    return 0;
}