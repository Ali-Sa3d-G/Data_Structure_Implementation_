#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                         SELECTION SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Selection Sort divides the array into two parts:
 *
 *      SORTED PART | UNSORTED PART
 *
 * At every step:
 *   1. Find the smallest element in the unsorted part.
 *   2. Swap it with the first element of the unsorted part.
 *
 * Visualization:
 *
 *   [ 64  25  12  22  11 ]
 *   ^-------------------^
 *        Unsorted
 *
 * Find the minimum -> 11
 *
 *   [ 11 | 25  12  22  64 ]
 *     ^       ^-----------
 *   Sorted       Unsorted
 *
 * Then repeat for the remaining unsorted part.
 *
 * Time Complexity:
 *   Best    : O(n²)
 *   Average : O(n²)
 *   Worst   : O(n²)
 *
 * Space Complexity: O(1)
 *
 * ============================================================================
 */

 // =========================== HELPER FUNCTION ===========================

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

// =========================== SELECTION SORT ===========================

/**
 * SELECTION SORT
 *
 * Finds the minimum element in the unsorted part
 * and places it at the beginning of that part.
 */
template <typename T>
void selectionSort(T arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        // Find the smallest element in the unsorted part.
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        // Put the minimum element in its correct position.
        if (minIndex != i)
        {
            swapValues(arr[i], arr[minIndex]);
        }
    }
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 64, 25, 12, 22, 11 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    selectionSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    return 0;
}