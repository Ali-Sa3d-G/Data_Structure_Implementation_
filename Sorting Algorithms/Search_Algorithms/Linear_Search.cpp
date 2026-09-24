#include <iostream>

using namespace std;

/**
 * ============================================================================
 *                         LINEAR SEARCH - LEARNING GUIDE
 * ============================================================================
 *
 * Linear Search checks the elements ONE BY ONE
 * until the target is found.
 *
 * Visualization:
 *
 *       [5] [3] [2] [8] [1]
 *        ^
 *       Check
 *              ^
 *             Check
 *                    ^
 *                   Found!
 *
 * It works on both sorted and unsorted arrays.
 *
 * Time Complexity:
 *   Best    : O(1)
 *   Average : O(n)
 *   Worst   : O(n)
 *
 * Space Complexity: O(1)
 *
 * ============================================================================
 */

 /**
  * LINEAR SEARCH
  *
  * Returns the index of key if found.
  * Returns -1 otherwise.
  */
template <typename T>
int linearSearch(const T arr[], int n, T key)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == key)
            return i;
    }

    return -1;
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 5, 3, 2, 8, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);

    int key = 2;

    int result = linearSearch(arr, n, key);

    if (result != -1)
        cout << "Element found at index: " << result << "\n";
    else
        cout << "Element not found.\n";

    return 0;
}