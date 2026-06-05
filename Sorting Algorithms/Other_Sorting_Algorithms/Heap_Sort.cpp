#include <iostream>
#include <vector>

using namespace std;

// Helper template function to swap elements
template <class T>
void swap_elements(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// Maintains the max-heap property for a subtree rooted at index 'i'
// n is the total size of the active heap inside the array
template <class T>
void max_heapify(T arr[], int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child index (0-based)
    int right = 2 * i + 2; // Right child index (0-based)

    // Check if left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Check if right child is larger than the current largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root, swap and continue heapifying the affected subtree
    if (largest != i) {
        swap_elements(arr[i], arr[largest]);
        max_heapify(arr, n, largest);
    }
}

// Builds a max-heap from an unsorted array
template <class T>
void build_max_heap(T arr[], int n) {
    // Start from the last non-leaf node and move up to the root
    for (int i = (n / 2) - 1; i >= 0; i--) {
        max_heapify(arr, n, i);
    }
}

// Main Heap Sort Function
template <class T>
void heapSort(T arr[], int n) {
    // 1. Build the max heap
    build_max_heap(arr, n);

    // 2. Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root (maximum element) to the end of the array
        swap_elements(arr, arr[i]);

        // Call max_heapify on the reduced heap to restore order
        max_heapify(arr, i, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    heapSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}