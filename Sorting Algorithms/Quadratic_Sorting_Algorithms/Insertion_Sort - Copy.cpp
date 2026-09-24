#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                         INSERTION SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Insertion Sort builds the sorted part one element at a time.
 *
 * Visualization:
 *
 *          SORTED | CURRENT | UNSORTED
 *         [10 20] |   15    | 30 40
 *
 * Take the current element (15) and move larger elements
 * to the right until the correct position is found.
 *
 * Result:
 *
 *         [10 15 20 30 40]
 *
 * The main idea is similar to arranging cards in your hand.
 *
 * Time Complexity:
 *   Best    : O(n)
 *   Average : O(n²)
 *   Worst   : O(n²)
 *
 * Space Complexity: O(1)
 *
 * ============================================================================
 */

 /**
  * INSERTION SORT
  *
  * Takes each element and inserts it into
  * its correct position in the sorted part.
  */
template <typename T>
void insertionSort(T arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        T key = arr[i];
        int j = i - 1;

        // Shift larger elements to make space for key.
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        // Put key in the empty position.
        arr[j + 1] = key;
    }
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    insertionSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    return 0;
}