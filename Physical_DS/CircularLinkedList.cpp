#include<iostream>
using namespace std;

/**
 * Node class for Circular Doubly Linked List
 * Each node contains:
 * - data: the actual value stored
 * - next: pointer to next node
 * - prev: pointer to previous node
 */
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    // Constructor - creates a node that points to itself (circular)
    Node(T data) {
        this->data = data;
        this->next = this;  // Points to itself initially
        this->prev = this;  // Points to itself initially
    }
};

/**
 * Circular Doubly Linked List class
 * Features:
 * - Circular: last node connects to first, first to last
 * - Doubly: each node has forward and backward links
 */
template <typename T>
class LinkedList {
private:
    Node<T>* head;  // Points to first node
    Node<T>* tail;  // Points to last node
    int size;       // Tracks number of nodes

public:
    // Constructor - initializes empty list
    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
    }

    // Returns true if list has no nodes
    bool isEmpty() const {
        return size == 0;
    }

    /**
     * Insert at the beginning of the list
     * Time Complexity: O(1)
     */
    void insertInStart(T data) {
        Node<T>* newNode = new Node<T>(data);
        size++;

        if (head == NULL) {
            // First node in empty list
            head = newNode;
            tail = newNode;
            // Node already points to itself (circular)
        }
        else {
            // Insert before head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            
            // Maintain circular connection
            head->prev = tail;
            tail->next = head;
        }
    }

    /**
     * Insert at the end of the list
     * Time Complexity: O(1)
     */
    void insertEnd(T data) {
        if (isEmpty()) {
            insertInStart(data);  // First node case
        }
        else {
            Node<T>* newNode = new Node<T>(data);
            size++;
            
            // Insert after tail
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;  // Connect to head (circular)
            tail = newNode;
            
            // Maintain circular connection from head to tail
            head->prev = tail;
        }
    }

    /**
     * Insert at a specific position (0-based index)
     * Time Complexity: O(n)
     */
    void insertAt(T data, int pos) {
        // Validate position
        if (pos < 0 || pos > size) {
            cout << "Invalid position" << endl;
            return;
        }
        else if (pos == 0) {
            insertInStart(data);
        }
        else if (pos == size) {
            insertEnd(data);
        }
        else {
            Node<T>* newNode = new Node<T>(data);
            Node<T>* temp = head;
            
            // Traverse to position before insertion point
            for (int i = 0; i < pos - 1; i++) {
                temp = temp->next;
            }
            
            // Insert between temp and temp->next
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            size++;
        }
    }

    /**
     * Display list from head to tail
     * Time Complexity: O(n)
     */
    void display() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node<T>* temp = head;
        for (int i = 0; i < size; i++) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    /**
     * Display list from tail to head (reverse order)
     * Time Complexity: O(n)
     */
    void displayReverse() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        Node<T>* temp = tail;
        for (int i = 0; i < size; i++) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }

    /**
     * Verify that circular links are properly maintained
     * Useful for debugging
     */
    void verifyCircular() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }

        cout << "Verification:" << endl;
        cout << "Head->prev = " << head->prev->data 
             << " (should be tail: " << tail->data << ")" << endl;
        cout << "Tail->next = " << tail->next->data 
             << " (should be head: " << head->data << ")" << endl;
    }

    /**
     * Search for a value and return its position
     * Returns: index if found, -1 if not found
     * Time Complexity: O(n)
     */
    int search(T key) {
        Node<T>* temp = head;
        int pos = 0;
        
        for (int i = 0; i < size; i++) {
            if (temp->data == key) {
                cout << "Found " << key << " at index " << pos << endl;
                return pos;
            }
            temp = temp->next;
            pos++;
        }
        
        cout << "Element " << key << " not found" << endl;
        return -1;
    }

    /**
     * Delete the first node
     * Time Complexity: O(1)
     */
    void deleteInStart() {
        if (isEmpty()) {
            cout << "List is empty - cannot delete" << endl;
            return;
        }

        Node<T>* temp = head;
        
        if (size == 1) {
            // Only one node in list
            delete head;
            head = NULL;
            tail = NULL;
        }
        else {
            // Move head to next node
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete temp;
        }
        
        size--;
    }

    /**
     * Delete the last node
     * Time Complexity: O(1)
     */
    void deleteEnd() {
        if (isEmpty()) {
            cout << "List is empty - cannot delete" << endl;
            return;
        }

        Node<T>* temp = tail;
        
        if (size == 1) {
            // Only one node in list
            delete head;
            head = NULL;
            tail = NULL;
        }
        else {
            // Move tail to previous node
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
            delete temp;
        }
        
        size--;
    }

    /**
     * Delete node at specific position (0-based index)
     * Time Complexity: O(n)
     */
    void deleteAt(int pos) {
        // Validate position
        if (pos < 0 || pos >= size) {
            cout << "Invalid position" << endl;
            return;
        }
        else if (pos == 0) {
            deleteInStart();
        }
        else if (pos == size - 1) {
            deleteEnd();
        }
        else {
            Node<T>* temp = head;
            
            // Traverse to node to be deleted
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            
            // Bypass the node
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            size--;
        }
    }

    /**
     * Delete entire list and free memory
     * Time Complexity: O(n)
     */
    void deleteList() {
        if (isEmpty()) {
            return;
        }
        
        // Break circular links to simplify deletion
        head->prev = NULL;
        tail->next = NULL;
        
        // Delete all nodes
        while (head != NULL) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        
        // Reset pointers and size
        head = NULL;
        tail = NULL;
        size = 0;
    }

    // Get current size of list
    int getSize() const {
        return size;
    }

    // Destructor - automatically cleans up memory
    ~LinkedList() {
        deleteList();
    }
};

/**
 * Main function to demonstrate the Circular Doubly Linked List
 */
int main() {
    LinkedList<int> list;
    
    cout << "=== Circular Doubly Linked List Demonstration ===\n" << endl;
    
    // Test 1: Insertions
    cout << "--- Testing Insertions ---" << endl;
    list.insertEnd(10);
    list.insertEnd(20);
    list.insertEnd(30);
    cout << "After insertEnd(10,20,30): ";
    list.display();
    
    list.insertInStart(5);
    cout << "After insertInStart(5): ";
    list.display();
    
    list.insertAt(15, 2);
    cout << "After insertAt(15,2): ";
    list.display();
    
    // Test 2: Reverse traversal
    cout << "\n--- Reverse Traversal ---" << endl;
    cout << "List in reverse order: ";
    list.displayReverse();
    
    // Test 3: Verify circular property
    cout << "\n--- Circular Property Verification ---" << endl;
    list.verifyCircular();
    
    // Test 4: Search operations
    cout << "\n--- Search Operations ---" << endl;
    list.search(20);
    list.search(100);
    
    // Test 5: Deletions
    cout << "\n--- Deletion Operations ---" << endl;
    list.deleteInStart();
    cout << "After deleteInStart (removed first): ";
    list.display();
    
    list.deleteEnd();
    cout << "After deleteEnd (removed last): ";
    list.display();
    
    list.deleteAt(1);
    cout << "After deleteAt(1) (removed at index 1): ";
    list.display();
    
    // Test 6: Final size
    cout << "\n--- Final Information ---" << endl;
    cout << "Final list size: " << list.getSize() << endl;
    
    return 0;
}