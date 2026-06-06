#include <iostream>

using namespace std;

// ==============================
// NODE CLASS
// Represents a single element in the linked list
// ==============================
class Node {
public:
    int data;       // Value stored in the node
    Node* next;     // Pointer to the next node

    // Constructor: Initializes a node with a given value
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// ==============================
// LINKED LIST CLASS
// Manages a singly linked list with automatic size tracking
// ==============================
class LinkedList {
private:
    Node* head;     // Pointer to the first node in the list
    int size;       // Tracks the number of elements in the list

public:
    // Constructor: Creates an empty linked list
    LinkedList() {
        head = nullptr;
        size = 0;   // Initially empty list
    }

    // Destructor: Clean up all nodes to prevent memory leaks
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // ========== GETTER METHODS ==========
    
    // Get the current size of the linked list
    int getSize() {
        return size;
    }

    // ========== UTILITY FUNCTIONS ==========
    
    // Check if the list has any nodes
    bool isEmpty() {
        return head == nullptr;
    }

    // Display all elements in the list
    void display() {
        if (isEmpty()) {
            cout << "The linked list is empty." << endl;
            return;
        }
        
        Node* temp = head;
        cout << "The elements of the linked list are: ";
        
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
        cout << "Current size: " << size << endl;
    }

    // ========== SEARCH FUNCTIONS ==========
    
    // Check if a specific value exists in the list
    bool isFound(int key) {
        Node* temp = head;
        
        while (temp != nullptr) {
            if (temp->data == key) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Find index of a value (returns -1 if not found)
    int search(int key) {
        Node* temp = head;
        int index = 0;
        
        while (temp != nullptr) {
            if (temp->data == key) {
                cout << "Found " << key << " at index " << index << endl;
                return index;
            }
            temp = temp->next;
            index++;
        }
        
        cout << "Element not found" << endl;
        return -1;
    }

    // ========== INSERTION FUNCTIONS ==========
    
    // Add a new node at the beginning of the list
    void insertFirst(int value) {
        Node* newNode = new Node(value);
        
        if (isEmpty()) {
            // List is empty: newNode becomes the only node
            newNode->next = nullptr;
            head = newNode;
        }
        else {
            // List has nodes: insert before current head
            newNode->next = head;
            head = newNode;
        }
        
        size++;  // Increment size after insertion
        cout << "Inserted " << value << " at the beginning. New size: " << size << endl;
    }

    // Add a new node at the end of the list
    void append(int value) {
        Node* newNode = new Node(value);
        newNode->next = nullptr;
        
        if (isEmpty()) {
            // List is empty: newNode becomes the only node
            head = newNode;
        }
        else {
            // Traverse to the last node
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            
            // Link the last node to the new node
            temp->next = newNode;
        }
        
        size++;  // Increment size after insertion
        cout << "Appended " << value << " at the end. New size: " << size << endl;
    }

    // Insert a new node before a specific existing value
    void insertBefore(int targetValue, int newValue) {
        // Check if list is empty
        if (isEmpty()) {
            cout << "The linked list is empty. Cannot insert the element." << endl;
            return;
        }
        
        // Special case: inserting before the head
        if (head->data == targetValue) {
            insertFirst(newValue);
            return;  // Size already incremented in insertFirst
        }
        
        // Find the node that comes before the target
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != targetValue) {
            temp = temp->next;
        }
        
        // If target not found
        if (temp->next == nullptr) {
            cout << "Element not found in the linked list. Cannot insert the element." << endl;
            return;
        }
        
        // Insert the new node
        Node* newNode = new Node(newValue);
        newNode->next = temp->next;
        temp->next = newNode;
        
        size++;  // Increment size after insertion
        cout << "Inserted " << newValue << " before " << targetValue << ". New size: " << size << endl;
    }

    // Insert a new node after a specific existing value
    void insertAfter(int targetValue, int newValue) {
        // Check if list is empty
        if (isEmpty()) {
            cout << "The linked list is empty. Cannot insert the element." << endl;
            return;
        }
        
        // Find the target node
        Node* temp = head;
        while (temp != nullptr && temp->data != targetValue) {
            temp = temp->next;
        }
        
        // If target not found
        if (temp == nullptr) {
            cout << "Element not found in the linked list. Cannot insert the element." << endl;
            return;
        }
        
        // Insert the new node after target
        Node* newNode = new Node(newValue);
        newNode->next = temp->next;
        temp->next = newNode;
        
        size++;  // Increment size after insertion
        cout << "Inserted " << newValue << " after " << targetValue << ". New size: " << size << endl;
    }

    // Insert a new node at a specific position (0-based index)
    void insertAtIndex(int index, int value) {
        // Validate index range
        if (index < 0 || index > size) {
            cout << "Invalid index: " << index << ". Valid range: 0 to " << size << endl;
            return;
        }
        
        // Insert at the beginning
        if (index == 0) {
            insertFirst(value);
            return;  // Size already incremented in insertFirst
        }
        
        // Insert at other positions
        Node* newNode = new Node(value);
        Node* temp = head;
        
        // Traverse to the node just before the insertion point
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        
        // Insert the new node
        newNode->next = temp->next;
        temp->next = newNode;
        
        size++;  // Increment size after insertion
        cout << "Inserted " << value << " at index " << index << ". New size: " << size << endl;
    }

    // ========== DELETION FUNCTIONS ==========
    
    // Delete the first occurrence of a value from the list
    void deleteByValue(int key) {
        // Check if list is empty
        if (isEmpty()) {
            cout << "The linked list is empty. Cannot delete the element." << endl;
            return;
        }
        
        Node* nodeToDelete = nullptr;
        
        // Case 1: Deleting the head node
        if (head->data == key) {
            nodeToDelete = head;
            head = head->next;
            delete nodeToDelete;
            size--;  // Decrement size after deletion
            cout << "Deleted " << key << " from the beginning. New size: " << size << endl;
            return;
        }
        
        // Case 2: Deleting from middle or end
        Node* previous = nullptr;
        nodeToDelete = head;
        
        // Search for the node to delete
        while (nodeToDelete != nullptr && nodeToDelete->data != key) {
            previous = nodeToDelete;
            nodeToDelete = nodeToDelete->next;
        }
        
        // If key not found
        if (nodeToDelete == nullptr) {
            cout << "Element " << key << " not found in the linked list. Cannot delete." << endl;
            return;
        }
        
        // Bypass the node to delete
        previous->next = nodeToDelete->next;
        delete nodeToDelete;
        size--;  // Decrement size after deletion
        cout << "Deleted " << key << " from the list. New size: " << size << endl;
    }

    // Delete the first node (head) of the list
    void deleteFirst() {
        if (isEmpty()) {
            cout << "The linked list is empty. Cannot delete." << endl;
            return;
        }
        
        Node* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        size--;
        cout << "Deleted first node. New size: " << size << endl;
    }

    // Delete the last node of the list
    void deleteLast() {
        if (isEmpty()) {
            cout << "The linked list is empty. Cannot delete." << endl;
            return;
        }
        
        // Only one node in the list
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            size--;
            cout << "Deleted last node. New size: " << size << endl;
            return;
        }
        
        // Traverse to the second last node
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        
        // Delete the last node
        delete temp->next;
        temp->next = nullptr;
        size--;
        cout << "Deleted last node. New size: " << size << endl;
    }

    // Delete a node at a specific index
    void deleteAtIndex(int index) {
        if (isEmpty()) {
            cout << "The linked list is empty. Cannot delete." << endl;
            return;
        }
        
        if (index < 0 || index >= size) {
            cout << "Invalid index: " << index << ". Valid range: 0 to " << size - 1 << endl;
            return;
        }
        
        // Delete first node
        if (index == 0) {
            deleteFirst();
            return;
        }
        
        // Find node before the one to delete
        Node* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        
        Node* nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        delete nodeToDelete;
        size--;
        cout << "Deleted node at index " << index << ". New size: " << size << endl;
    }

    // ========== REVERSAL FUNCTION ==========
    
    // Reverse the entire linked list
    void reverse() {
        // Check if list is empty
        if (isEmpty()) {
            cout << "The linked list is empty. Cannot reverse the list." << endl;
            return;
        }
        
        Node* previous = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;
        
        // Iteratively reverse the links
        while (current != nullptr) {
            nextNode = current->next;  // Save the next node
            current->next = previous;  // Reverse the pointer
            previous = current;        // Move previous forward
            current = nextNode;        // Move current forward
        }
        
        // Update head to the new first node
        head = previous;
        cout << "List reversed. Size remains: " << size << endl;
    }
    
    // Clear the entire list
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;
        cout << "List cleared. Size: " << size << endl;
    }
};

// ==============================
// MAIN FUNCTION - DEMONSTRATION
// ==============================
int main() {
    LinkedList list;

    // ----- 1. Initial State -----
    cout << "--- 1. Initial State Check ---" << endl;
    cout << "Is list empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
    cout << "Initial size: " << list.getSize() << endl;
    list.display();
    cout << endl;

    // ----- 2. Basic Insertions -----
    cout << "--- 2. Testing Insert First & Append ---" << endl;
    list.insertFirst(10);   // List: 10, Size: 1
    list.insertFirst(20);   // List: 20 10, Size: 2
    list.append(30);        // List: 20 10 30, Size: 3
    list.display();
    cout << "Current size from getter: " << list.getSize() << endl << endl;

    // ----- 3. Search Operations -----
    cout << "--- 3. Testing Search & Findings ---" << endl;
    int searchKey = 10;
    cout << "Searching for " << searchKey << ":" << endl;
    list.search(searchKey);                     // Should print index 1
    cout << "isFound(30)? " << (list.isFound(30) ? "True" : "False") << endl;
    cout << "isFound(99)? " << (list.isFound(99) ? "True" : "False") << endl << endl;

    // ----- 4. Insert Before & After -----
    cout << "--- 4. Testing Insert Before & After ---" << endl;
    cout << "Inserting 15 before 10..." << endl;
    list.insertBefore(10, 15);
    list.display();
    
    cout << "Inserting 25 after 20..." << endl;
    list.insertAfter(20, 25);
    list.display();
    cout << endl;

    // ----- 5. Insert at Index -----
    cout << "--- 5. Testing Insert at Index ---" << endl;
    cout << "Inserting 5 at index 0 (Head) and 35 at index 4..." << endl;
    list.insertAtIndex(0, 5);   // New Head
    list.insertAtIndex(4, 35);  // Middle
    list.display();
    cout << endl;

    // ----- 6. Delete Operations -----
    cout << "--- 6. Testing Delete Operations ---" << endl;
    cout << "Deleting Head (5)..." << endl;
    list.deleteByValue(5);
    list.display();

    cout << "Deleting Tail (30)..." << endl;
    list.deleteByValue(30);
    list.display();

    cout << "Deleting Middle (15)..." << endl;
    list.deleteByValue(15);
    list.display();
    
    cout << "Deleting first node..." << endl;
    list.deleteFirst();
    list.display();
    
    cout << "Deleting last node..." << endl;
    list.deleteLast();
    list.display();
    cout << endl;

    // ----- 7. Edge Cases -----
    cout << "--- 7. Testing Edge Cases ---" << endl;
    list.deleteByValue(100);     // Should show error message
    cout << "Deleting at index 5 (invalid)..." << endl;
    list.deleteAtIndex(5);
    cout << "Final size: " << list.getSize() << endl;
    list.display();

    // ----- 8. Insert at Index with validation -----
    cout << "\n--- 8. Testing Insert with Index Validation ---" << endl;
    cout << "Trying to insert at index 10 (invalid)..." << endl;
    list.insertAtIndex(10, 99);
    
    // ----- 9. Reverse List -----
    cout << "\n--- 9. Testing Reverse ---" << endl;
    list.reverse();
    list.display();
    
    // ----- 10. Clear List -----
    cout << "\n--- 10. Testing Clear ---" << endl;
    list.clear();
    cout << "Is list empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
    cout << "Size after clear: " << list.getSize() << endl;
    list.display();

    return 0;
}