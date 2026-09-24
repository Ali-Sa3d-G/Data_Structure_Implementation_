#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                         BUBBLE SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Bubble Sort repeatedly compares ADJACENT elements
 * and swaps them if they are in the wrong order.
 *
 * After every pass, the LARGEST unsorted element
 * moves to the end of the array.
 *
 * Visualization:
 *
 *   [64  34  25  12  22  11  90]
 *    ^   ^
 *   Compare adjacent elements
 *
 *   If 64 > 34:
 *
 *   [34  64  25  12  22  11  90]
 *
 * Continue comparing:
 *
 *   [34  25  12  22  11  64  90]
 *                              ^^
 *                              Largest element
 *                              is now in its place.
 *
 * After the first pass:
 *
 *   [34  25  12  22  11  64 | 90]
 *                            Sorted
 *
 * The process is repeated for the remaining unsorted part.
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
  * SWAP
  *
  * Swaps the values of two variables.
  */
template <typename T>
void swapValues(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

// =========================== BUBBLE SORT ===========================

/**
 * BUBBLE SORT
 *
 * Compares adjacent elements and swaps them
 * when they are in the wrong order.
 *
 * After each pass, the largest unsorted element
 * moves to the end of the unsorted part.
 */
template <typename T>
void bubbleSort(T arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        /*
         * The last i elements are already sorted,
         * so we do not need to compare them again.
         */
        for (int j = 0; j < n - i - 1; j++)
        {
            // Swap adjacent elements if they are in the wrong order.
            if (arr[j] > arr[j + 1])
            {
                swapValues(arr[j], arr[j + 1]);
            }
        }
    }
}

// =========================== MAIN FUNCTION - DEMONSTRATION ===========================

int main()
{
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n = sizeof(arr) / sizeof(arr[0]);

    // ==================== ORIGINAL ARRAY ====================

    cout << "Original array: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    // ==================== BUBBLE SORT ====================

    bubbleSort(arr, n);

    // ==================== SORTED ARRAY ====================

    cout << "Sorted array: ";

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    return 0;
}