#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                         BINARY SEARCH - LEARNING GUIDE
 * ============================================================================
 *
 * Binary Search works ONLY on a SORTED array.
 *
 * Instead of checking every element, it checks the middle element
 * and removes half of the search range.
 *
 * Visualization:
 *
 *       [1  2  3  4  5  6  7]
 *              ^
 *             mid
 *
 * If key > mid:
 *
 *       Ignore the LEFT half.
 *
 * If key < mid:
 *
 *       Ignore the RIGHT half.
 *
 * Continue until the key is found or the range becomes empty.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 *
 * ============================================================================
 */

 /**
  * BINARY SEARCH
  *
  * Returns the index of key if found.
  * Returns -1 if the key does not exist.
  */
template <typename T>
int binarySearch(const T arr[], int n, T key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
        {
            // Key must be in the right half.
            low = mid + 1;
        }
        else
        {
            // Key must be in the left half.
            high = mid - 1;
        }
    }

    return -1;
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int key = 3;

    int result = binarySearch(arr, n, key);

    if (result != -1)
        cout << "Element found at index: " << result << "\n";
    else
        cout << "Element not found.\n";

    return 0;
}