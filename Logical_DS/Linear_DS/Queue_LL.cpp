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

class Queue{
    private:
        Node* front;
        Node* rear;

    public:
        // Constructor to initialize the queue
        Queue(){
            front = nullptr;
            rear = nullptr;
        }

        // Function to check if the queue is empty
        bool isEmpty(){
            return front == nullptr;
        }

        // Function to enqueue an element into the queue
        void enqueue(int value){
            Node* new_node = new Node(value);
            if (isEmpty()){
                front = rear = new_node;
                return;
            }
            rear->next = new_node;
            rear = new_node;
        }

        // Function to dequeue an element from the queue and return the dequeued value
        int dequeue(){
            if(isEmpty()){
                cout<<"Queue underflow. Cannot dequeue from an empty queue."<<endl;
                return -1; // Return -1 to indicate queue is empty
            }
            else if (front == rear){
                int dequeued_value = front->data;
                delete front;
                front = rear = nullptr;
                return dequeued_value;
            }
            else{
                Node* delptr = front;
                int dequeued_value = delptr->data;
                front = front->next;
                delete delptr;
                return dequeued_value;
            }

        }

        // Function to peek at the front element of the queue without removing it
        int getFront(){
            if(isEmpty()){
                cout<<"Queue is empty. Cannot peek."<<endl;
                return -1; // Return -1 to indicate queue is empty
            }
            return front->data;
        }

        // Function to peek at the rear element of the queue without removing it
        int getRear(){
            if(isEmpty()){
                cout<<"Queue is empty. Cannot peek."<<endl;
                return -1; // Return -1 to indicate queue is empty
            }
            return rear->data;
        }

        // Function to display the elements of the queue
        void display(){
            Node* temp = front;
            cout<<"The elements of the queue are: ";
            while(temp != nullptr){
                cout<<temp->data<<" ";
                temp = temp->next;
            }
            cout<<endl;
        }

        // Function to count the number of elements in the queue
        int count(){
            Node* temp = front;
            int count = 0;
            while(temp != nullptr){
                count++;
                temp = temp->next;
            }
            return count;
        }

        // Function to search for an element in the queue
        bool isFound(int key){
            Node* temp = front;
            while(temp != nullptr){
                if(temp->data == key){
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }

        // Function to search for an element in the queue and return its index
        int search(int key){
            Node* temp = front;
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
            return -1; // Return -1 to indicate element not found
        }

        // Function to clear the queue by dequeuing all elements
        void clear(){
            while(!isEmpty()){
                dequeue();
            }
        }


    };


int main() {
    Queue queue;

    // 1. Test isEmpty and Initial State
    cout << "--- 1. Initial State Check ---" << endl;
    cout << "Is queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;
    queue.display();
    cout << endl;


    // 2. Test Basic Enqueue Operations
    cout << "--- 2. Testing Enqueue ---" << endl;
    cout << "Enqueuing 10, then 20, then 30..." << endl;
    queue.enqueue(10);  // Queue: 10
    queue.enqueue(20);  // Queue: 10 20
    queue.enqueue(30);  // Queue: 10 20 30
    queue.display();
    cout << "Current Count: " << queue.count() << endl << endl;


    // 3. Test Peek Operations
    cout << "--- 3. Testing Peek Operations ---" << endl;
    cout << "Front element: " << queue.getFront() << endl; // Should be 10
    cout << "Rear element: " << queue.getRear() << endl;   // Should be 30
    cout << endl;


    // 4. Test Dequeue Operations
    cout << "--- 4. Testing Dequeue ---" << endl;
    cout << "Dequeuing an element..." << endl;
    int dequeuedValue = queue.dequeue(); // Should dequeue 10
    if (dequeuedValue != -1) {
        cout << "Dequeued value: " << dequeuedValue << endl;
        queue.display();
        cout << "Current Count: " << queue.count() << endl;
    }
    cout << endl;


    // 5. Test Search & Index
    cout << "--- 5. Testing Search & Findings ---" << endl;
    int searchKey = 20;
    cout << "Searching for " << searchKey << ":" << endl;
    queue.search(searchKey); // Should print index 0 (after dequeuing 10)
    searchKey = 40;
    cout << "Searching for " << searchKey << ":" << endl;
    queue.search(searchKey); // Should indicate element not found
    cout << endl;


    // 6. Test Dequeueing All Elements and Dequeue from Empty Queue
    cout << "--- 6. Testing Dequeue from Empty Queue ---" << endl;
    queue.dequeue(); // Dequeue 20
    queue.dequeue(); // Dequeue 30
    cout << "Dequeuing from an empty queue..." << endl;
    queue.dequeue(); // Should indicate queue is empty
    queue.display();
    cout << "Current Count: " << queue.count() << endl; 

    // 7. Test Clear Function
    cout << "--- 7. Testing Clear Function ---" << endl;
    queue.clear();
    queue.display();
    cout << "Current Count: " << queue.count() << endl; 
    

    return 0;

}
