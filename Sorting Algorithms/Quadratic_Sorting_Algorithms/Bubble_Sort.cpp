#include <iostream>

using namespace std;

template <class T>
void swap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
void BubbleSort(T arr[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <class T>
void Bubble_Sort(T arr[], int n){
    int i = n;
    while (i > 0){
        int j = 0;
        while (j < i){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
            j++;
        }
        i--;
    }
}

int main(){
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    Bubble_Sort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    
    /////////

    int arr2[] = {5.5, 2.3, 9.8, 1.2, 4.6};
    int m = sizeof(arr2) / sizeof(arr2[0]); 

    cout << "Original array 2: ";
    for (int i = 0; i < m; i++){
        cout << arr2[i] << " ";
    }
    cout << endl;

    BubbleSort(arr2, m);

    cout << "Sorted array 2: ";
    for (int i = 0; i < m; i++){
        cout << arr2[i] << " ";
    }
    cout << endl;

    return 0;
}