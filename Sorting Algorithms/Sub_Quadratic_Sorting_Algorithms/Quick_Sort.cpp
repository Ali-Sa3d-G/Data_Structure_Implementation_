#include <iostream>

using namespace std;


template <class T>
void swap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}


template <class T>
void partition(T arr[], int low, int high, int &pivot_index){
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++){
        if (arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    pivot_index = i + 1;
}


template <class T>
void quickSort(T arr[], int low, int high){
    if (low < high){
        int pivot_index;
        partition(arr, low, high, pivot_index);

        quickSort(arr, low, pivot_index - 1);
        quickSort(arr, pivot_index + 1, high);
    }
}



int main(){
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}