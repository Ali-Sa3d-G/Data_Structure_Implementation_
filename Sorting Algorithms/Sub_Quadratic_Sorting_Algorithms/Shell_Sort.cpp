#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                           SHELL SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Shell Sort is an improved version of Insertion Sort.
 *
 * Instead of comparing only adjacent elements,
 * it first compares elements that are far apart.
 *
 * Example:
 *
 *       [12  34  54  2  3]
 *
 *             gap = 2
 *
 *       Compare elements 2 positions apart.
 *
 * The gap keeps getting smaller:
 *
 *              2 -> 1
 *
 * When gap = 1, the algorithm works like Insertion Sort.
 *
 * Time Complexity:
 *   Depends on the gap sequence.
 *   With this sequence, Worst Case: O(n²)
 *
 * Space Complexity: O(1)
 *
 * ============================================================================
 */

 /**
  * SHELL SORT
  *
  * Sorts elements using decreasing gaps.
  */
template <typename T>
void shellSort(T arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            T temp = arr[i];
            int j = i;

            // Shift larger elements in the current gap group.
            while (j >= gap && arr[j - gap] > temp)
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 12, 34, 54, 2, 3 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    shellSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    return 0;
}