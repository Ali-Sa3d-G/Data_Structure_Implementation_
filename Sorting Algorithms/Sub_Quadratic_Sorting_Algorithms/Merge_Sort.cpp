#include <iostream>


using namespace std;


template <class T>
void merge(T arr[], int left, int mid, int right){
    int i = left;
    int j = mid + 1;
    int k = left;

    T temp[right + 1];

    while (i <= mid && j <= right){
        if (arr[i] <= arr[j]){
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid){
        temp[k++] = arr[i++];
    }

    while (j <= right){
        temp[k++] = arr[j++];
    }

    for (int l = left; l <= right; l++){
        arr[l] = temp[l];
    }
}




template <class T>
void mergeSort(T arr[], int left, int right){
    if (left < right){
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


int main(){
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}