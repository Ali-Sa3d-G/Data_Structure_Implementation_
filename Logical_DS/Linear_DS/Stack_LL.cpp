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


class Stack{
    private:
        Node* top;

    public:
        // Constructor to initialize the stack
        Stack(){
            top = nullptr;
        }

        // Function to check if the stack is empty
        bool isEmpty(){
            return top == nullptr;
        }

        // Function to push an element onto the stack
        void push(int value){
            if (isEmpty()){
                top = new Node(value);
                return;
            }
            else{
                Node* new_node = new Node(value);
                new_node->next = top;
                top = new_node;
            }
        }

        // Function to pop an element from the stack and return the popped value
        int pop(){
            if(isEmpty()){
                cout<<"Stack underflow. Cannot pop from an empty stack."<<endl;
                return -1; // Return -1 to indicate stack is empty
            }
            Node* delptr = top;
            int popped_value = delptr->data;
            top = top->next;
            delete delptr;
            return popped_value;
        }

        // Function to peek at the top element of the stack without removing it
        int peek(){
            if(isEmpty()){
                cout<<"Stack is empty. Cannot peek."<<endl;
                return -1; // Return -1 to indicate stack is empty
            }
            return top->data;
        }

        // Function to display the elements of the stack
        void display(){
            Node* temp = top;
            cout<<"The elements of the stack are: ";
            while(temp != nullptr){
                cout<<temp->data<<" ";
                temp = temp->next;
            }
            cout<<endl;
        }

        // Function to count the number of elements in the stack
        int count(){
            Node* temp = top;
            int count = 0;
            while(temp != nullptr){
                count++;
                temp = temp->next;
            }
            return count;
        }

        // Function to search for an element in the stack
        bool isFound(int key){
            Node* temp = top;
            while(temp != nullptr){
                if(temp->data == key){
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }

        // Function to search for an element in the stack and return its index
        int search(int key){
            Node* temp = top;
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
};




int main() {
    Stack stack;

    // 1. Test isEmpty and display
    cout << "--- 1. Testing isEmpty & Display ---" << endl;
    cout << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << endl;
    stack.display();


    // 2. Test push and display
    cout << "--- 2. Testing Push & Display ---" << endl;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.display();


    // 3. Test peek
    cout << "--- 3. Testing Peek ---" << endl;
    cout << "Top element (peek): " << stack.peek() << endl;


    // 4. Test pop and display
    cout << "--- 4. Testing Pop & Display ---" << endl;
    cout << "Popped element: " << stack.pop() << endl;
    stack.display();


    // 5. Test popping all elements and then popping from an empty stack
    cout << "--- 5. Testing Pop from Empty Stack ---" << endl;
    cout << "Popped element: " << stack.pop() << endl;
    cout << "Popped element: " << stack.pop() << endl; // This should indicate stack is empty
    stack.display();


    // 6. Test count
    cout << "--- 6. Testing Count ---" << endl;
    cout << "Number of elements in stack: " << stack.count() << endl;


    // 7. Test search and isFound
    cout << "--- 7. Testing Search & isFound ---" << endl;
    stack.push(40);
    stack.push(50);
    cout << "Searching for 40: " << (stack.isFound(40) ? "Found" : "Not Found") << endl;
    cout << "Searching for 99: " << (stack.isFound(99) ? "Found" : "Not Found") << endl;
    stack.search(50); // Should print index 0
    stack.search(99); // Should print "Element not found"

    return 0;
}   