#include <iostream>

using namespace std;


template <class T>
int linearSearch(T arr[], int n, T key){
    for (int i = 0; i < n; i++){
        if (arr[i] == key){
            return i; // Return the index of the found element
        }
    }
    return -1; // Return -1 if the element is not found
}


int main(){
    int arr[] = {5, 3, 2, 8, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 2;

    int result = linearSearch(arr, n, key);
    if (result != -1){
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found in the array." << endl;
    }

    return 0;
}