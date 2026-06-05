#include <iostream>

using namespace std;

class Node{
    public:
        int data;
        Node* next;

        // Constructor to initialize the node
        Node(int value){
            data = value;
            next = nullptr;
        }
};

class LinkedList{
    private:
        Node* head;

    public:
        // Constructor to initialize the linked list
        LinkedList(){
            head = nullptr;
        }

        // Function to check if the linked list is empty
        bool isEmpty(){
            return head == nullptr;
        }



        // Function to display the elements of the linked list
        void display(){
            Node* temp = head;
            cout<<"The elements of the linked list are: ";
            while(temp != nullptr){
                cout<<temp->data<<" ";
                temp = temp->next;
            }
            cout<<endl;
        }

        // Function to count the number of elements in the linked list
        int count(){
            Node* temp = head;
            int count = 0;
            while(temp != nullptr){
                count++;
                temp = temp->next;
            }
            return count;
        }

        // Function to search for an element in the linked list
        bool isFound(int key){
            Node* temp = head;
            while(temp != nullptr){
                if(temp->data == key){
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }


        // Function to search for an element in the linked list and return its index
        int search(int key){
            Node* temp = head;
            int index = 0;
            while(temp != nullptr){
                if(temp->data == key){
                    cout<<"Found "<<key<<" at index "<<index<<endl;
                    return index;
                }
                temp = temp->next;
                index++;
            }
            cout<<"Element not found"<<endl;
            return -1;
        }


        // Function to insert an element at the beginning of the linked list
        void insert_first(int value){
            Node* new_node = new Node(value);
            if (isEmpty()){
                new_node->next = nullptr;
                head = new_node;
            }
            else{
                new_node->next = head;
                head = new_node;
            }
        }   


        // Function to insert an element before a specific element in the linked list
        void insert_before(int key, int value){
            if(isEmpty()){
                cout<<"The linked list is empty. Cannot insert the element."<<endl;
                return;
            }
            if(head->data == key){
                insert_first(value);
                return;
            }
            Node* temp = head;
            while(temp->next != nullptr && temp->next->data != key){
                temp = temp->next;
            }
            if(temp->next == nullptr){
                cout<<"Element not found in the linked list. Cannot insert the element."<<endl;
                return;
            }
            Node* new_node = new Node(value);
            new_node->next = temp->next;
            temp->next = new_node;
        }


        // Function to insert an element after a specific element in the linked list
        void append(int value){
            Node* new_node = new Node(value);
            new_node->next = nullptr;
            if(isEmpty()){
                head = new_node;
                return;
            }
            Node* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = new_node;
            new_node->next = nullptr;
        }


        // Function to insert an element at a specific index in the linked list
        void insert_at_index(int index, int value){
            if(index<0 || index>count()){
                cout<<"Invalid index. Cannot insert the element."<<endl;
                return;
            }
            if(index == 0){
                insert_first(value);
                return;
            }
            Node* new_node = new Node(value);
            Node* temp = head;
            for(int i=0; i<index-1; i++){
                temp = temp->next;
            }
            new_node->next = temp->next;
            temp->next = new_node;
        }


        // Function to delete an element by value in the linked list
        void Delete(int key){
            if(isEmpty()){
                cout<<"The linked list is empty. Cannot delete the element."<<endl;
                return;
            }
            Node* delptr;
            if(head->data == key){
                Node* temp = head;
                head = head->next;
                delete temp;
                return;
            }
            else{
                Node* prev = nullptr;
                delptr = head;
                while(delptr != nullptr && delptr->data != key){
                    prev = delptr;
                    delptr = delptr->next;
                }
                if(delptr == nullptr){
                    cout<<"Element not found in the linked list. Cannot delete the element."<<endl;
                    return;
                }
                prev->next = delptr->next;
                delete delptr;

            }
        }


        void reverse(){
            if(isEmpty()){
                cout<<"The linked list is empty. Cannot reverse the list."<<endl;
                return;
            }
            Node* prev = nullptr;
            Node* current = head;
            Node* next = nullptr;
            while(current != nullptr){
                next = current->next; // Store the next node
                current->next = prev; // Reverse the current node's pointer
                prev = current;       // Move prev to the current node
                current = next;       // Move to the next node
            }
            head = prev; // Update head to the new first node
        }


};





int main() {
    LinkedList list;

    // 1. Test isEmpty and Initial State
    cout << "--- 1. Initial State Check ---" << endl;
    cout << "Is list empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
    list.display();
    cout << endl;

    // 2. Test Basic Insertions (First and Append)
    cout << "--- 2. Testing Insert First & Append ---" << endl;
    cout << "Inserting 10 at first, then 20 at first, then 30 as append..." << endl;
    list.insert_first(10);  // List: 10
    list.insert_first(20);  // List: 20 10
    list.append(30);        // List: 20 10 30
    list.display();
    cout << "Current Count: " << list.count() << endl << endl;

    // 3. Test Search & Index
    cout << "--- 3. Testing Search & Findings ---" << endl;
    int searchKey = 10;
    cout << "Searching for " << searchKey << ":" << endl;
    list.search(searchKey); // Should print index 1
    cout << "isFound(30)? " << (list.isFound(30) ? "True" : "False") << endl;
    cout << "isFound(99)? " << (list.isFound(99) ? "True" : "False") << endl << endl;

    // 4. Test Insert Before
    cout << "--- 4. Testing Insert Before ---" << endl;
    cout << "Inserting 15 before 10..." << endl;
    list.insert_before(10, 15);
    list.display(); // Expected: 20 15 10 30
    cout << endl;

    // 5. Test Insert at Index
    cout << "--- 5. Testing Insert at Index ---" << endl;
    cout << "Inserting 5 at index 0 (Head) and 25 at index 3..." << endl;
    list.insert_at_index(0, 5);  // New Head
    list.insert_at_index(3, 25); // Middle
    list.display(); // Expected: 5 20 15 25 10 30
    cout << endl;

    // 6. Test Delete
    cout << "--- 6. Testing Delete ---" << endl;
    cout << "Deleting Head (5)..." << endl;
    list.Delete(5);
    list.display();

    cout << "Deleting Tail (30)..." << endl;
    list.Delete(30);
    list.display();

    cout << "Deleting Middle (15)..." << endl;
    list.Delete(15);
    list.display(); // Expected: 20 25 10
    cout << endl;

    // 7. Test Edge Case: Delete non-existent
    cout << "--- 7. Testing Non-existent Delete ---" << endl;
    list.Delete(100); 
    cout << "Final count: " << list.count() << endl;
    list.display();

    // 8. Test Reverse
    cout << "--- 8. Testing Reverse ---" << endl;
    list.reverse();
    list.display();
    

    return 0;
}

