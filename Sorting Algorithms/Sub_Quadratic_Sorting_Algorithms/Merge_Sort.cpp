#include <iostream>
#include <vector>

using namespace std;

/**
 * ============================================================================
 *                           MERGE SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Merge Sort uses the Divide and Conquer idea.
 *
 * Steps:
 *   1. Divide the array into two halves.
 *   2. Keep dividing until every part has one element.
 *   3. Merge the sorted parts together.
 *
 * Visualization:
 *
 *                  [38 27 43 3]
 *                    /      \
 *              [38 27]    [43 3]
 *               /   \       / \
 *             [38] [27]   [43] [3]
 *
 * Merge:
 *
 *             [27 38]     [3 43]
 *                   \       /
 *                 [3 27 38 43]
 *
 * The merge step always combines two SORTED parts.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 *
 * ============================================================================
 */

 /**
  * MERGE
  *
  * Merges two sorted parts:
  *
  *     arr[left ... mid]
  *     arr[mid + 1 ... right]
  *
  * into one sorted part.
  */
template <typename T>
void mergeArrays(T arr[], int left, int mid, int right)
{
    vector<T> temp(right - left + 1);

    int i = left;
    int j = mid + 1;
    int k = 0;

    // Compare the smallest remaining elements from both halves.
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    // Copy remaining elements from the left half.
    while (i <= mid)
        temp[k++] = arr[i++];

    // Copy remaining elements from the right half.
    while (j <= right)
        temp[k++] = arr[j++];

    // Put the merged result back into the original array.
    for (int x = 0; x < k; x++)
    {
        arr[left + x] = temp[x];
    }
}

/**
 * MERGE SORT
 *
 * Divides the array recursively,
 * then merges the sorted halves.
 */
template <typename T>
void mergeSort(T arr[], int left, int right)
{
    // One element is already sorted.
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    // Sort left half.
    mergeSort(arr, left, mid);

    // Sort right half.
    mergeSort(arr, mid + 1, right);

    // Merge the two sorted halves.
    mergeArrays(arr, left, mid, right);
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    int arr[] = { 38, 27, 43, 3, 9, 82, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    mergeSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n";

    return 0;
}