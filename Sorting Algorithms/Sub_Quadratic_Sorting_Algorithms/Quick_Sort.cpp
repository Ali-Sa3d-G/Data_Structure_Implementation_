#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                           QUICK SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Quick Sort uses a PIVOT to divide the array.
 *
 * After partitioning:
 *
 *       Smaller values | PIVOT | Larger values
 *
 * Example:
 *
 *       [10  7  8  9  1  5]
 *                         ^
 *                       Pivot
 *
 * After partition:
 *
 *       [1  5  7  8  9] 10
 *                        ^
 *                      Pivot
 *
 * The pivot is now in its correct position.
 * Then we recursively sort the left and right parts.
 *
 * Time Complexity:
 *   Average : O(n log n)
 *   Worst   : O(n²)
 *
 * Space Complexity:
 *   Average : O(log n)
 *   Worst   : O(n)
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
 * PARTITION
 *
 * Uses the last element as the pivot.
 *
 * At the end:
 *
 *     [values < pivot] | pivot | [values >= pivot]
 *
 * Returns the final index of the pivot.
 */
template <typename T>
int partitionArray(T arr[], int low, int high)
{
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;

            // Move smaller value to the left part.
            swapValues(arr[i], arr[j]);
        }
    }

    // Put pivot between the two parts.
    swapValues(arr[i + 1], arr[high]);

    return i + 1;
}

/**
 * QUICK SORT
 */
template <typename T>
void quickSort(T arr[], int low, int high)
{
    if (low >= high)
        return;

    int pivotIndex = partitionArray(arr, low, high);

    // Sort values smaller than the pivot.
    quickSort(arr, low, pivotIndex - 1);

    // Sort values larger than the pivot.
    quickSort(arr, pivotIndex + 1, high);
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 10, 7, 8, 9, 1, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    return 0;
}