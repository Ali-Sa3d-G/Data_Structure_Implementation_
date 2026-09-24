#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                            HEAP SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Heap Sort uses a MAX HEAP.
 *
 * In a Max Heap:
 *
 *                 [MAX]
 *                 /   \
 *                /     \
 *             larger than children
 *
 * Array representation:
 *
 *                 50
 *               /    \
 *             30      40
 *            /  \    /
 *           10  20  35
 *
 *              =>
 *
 *          [50 30 40 10 20 35]
 *
 * For index i:
 *
 *      Left child  = 2*i + 1
 *      Right child = 2*i + 2
 *
 * Steps:
 *
 *   1. Build a Max Heap.
 *   2. The maximum value is at index 0.
 *   3. Swap it with the last unsorted element.
 *   4. Reduce heap size.
 *   5. Restore the Max Heap.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(log n)
 * (recursive heapify)
 *
 * ============================================================================
 */

 /**
  * Swaps two values.
  */
template <typename T>
void swapValues(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

/**
 * MAX HEAPIFY
 *
 * Restores the Max Heap property for the subtree
 * rooted at index i.
 */
template <typename T>
void maxHeapify(T arr[], int n, int i)
{
    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If a child is larger, move it up and continue.
    if (largest != i)
    {
        swapValues(arr[i], arr[largest]);

        maxHeapify(arr, n, largest);
    }
}

/**
 * BUILD MAX HEAP
 *
 * Leaf nodes are already valid heaps,
 * so we start from the last non-leaf node.
 */
template <typename T>
void buildMaxHeap(T arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxHeapify(arr, n, i);
    }
}

/**
 * HEAP SORT
 */
template <typename T>
void heapSort(T arr[], int n)
{
    // Step 1: Build a Max Heap.
    buildMaxHeap(arr, n);

    for (int i = n - 1; i > 0; i--)
    {
        // Maximum element is currently at the root.
        swapValues(arr[0], arr[i]);

        // The last element is now in its final position.
        // Heapify only the remaining heap.
        maxHeapify(arr, i, 0);
    }
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    heapSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    return 0;
}