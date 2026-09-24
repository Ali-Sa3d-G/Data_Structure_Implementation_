#include <iostream>
#include <vector>

using namespace std;

/**
 * ============================================================================
 *                         COUNTING SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Counting Sort does not compare elements.
 *
 * It counts how many times each value appears.
 *
 * Example:
 *
 *       Array:
 *       [4  2  2  8  3  3  1]
 *
 *       Count table:
 *
 *       Value:  0 1 2 3 4 5 6 7 8
 *       Count:  0 1 2 2 1 0 0 0 1
 *
 * Then rebuild the array using the counts:
 *
 *       [1 2 2 3 3 4 8]
 *
 * This implementation works with NON-NEGATIVE integers.
 *
 * Time Complexity: O(n + k)
 * Space Complexity: O(k)
 *
 * k = maximum value
 *
 * ============================================================================
 */

 /**
  * COUNTING SORT
  */
void countingSort(int arr[], int n)
{
    if (n <= 0)
        return;

    int maxValue = arr[0];

    // Find the maximum value.
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxValue)
            maxValue = arr[i];
    }

    // Counting Sort uses the values as indexes.
    vector<int> count(maxValue + 1, 0);

    // Count each value.
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            cout << "Counting Sort expects non-negative integers.\n";
            return;
        }

        count[arr[i]]++;
    }

    // Rebuild the array from the count table.
    int index = 0;

    for (int value = 0; value <= maxValue; value++)
    {
        while (count[value] > 0)
        {
            arr[index++] = value;
            count[value]--;
        }
    }
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 4, 2, 2, 8, 3, 3, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    countingSort(arr, n);

    cout << "Sorted array: ";

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    return 0;
}