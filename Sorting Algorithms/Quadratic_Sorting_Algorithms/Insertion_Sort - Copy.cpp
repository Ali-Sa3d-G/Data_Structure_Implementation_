#include <iostream>

using namespace std;


template <class T>

void insertionSort(T arr[], int n){
    for (int i = 1; i < n ; i++){
        T temp = arr[i];

        for (int j = i - 1; j >=0 && arr[j] > temp; j--){
            arr[j + 1] = arr[j];
            arr[j] = temp;
            
        }

    }
}


int main(){
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    insertionSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}