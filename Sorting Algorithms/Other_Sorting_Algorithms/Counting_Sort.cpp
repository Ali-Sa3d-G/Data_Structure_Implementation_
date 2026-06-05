#include <iostream>
#include <vector>

using namespace std;


template <class T>
void Counting_Sort(T arr[], int n){
    if (n <= 0) return;

    T max_element = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > max_element){
            max_element = arr[i];
        }
    }

    vector<int> count(max_element + 1, 0);
    for (int i = 0; i < n; i++){
        count[arr[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= max_element; i++){
        while (count[i] > 0){
            arr[index++] = i;
            count[i]--;
        }
    }
}





int main(){
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    Counting_Sort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}