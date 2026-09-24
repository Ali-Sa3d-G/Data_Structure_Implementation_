#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/**
 * ============================================================================
 *                           BUCKET SORT - LEARNING GUIDE
 * ============================================================================
 *
 * Bucket Sort distributes elements into different buckets.
 *
 * This implementation assumes that values are in the range [0, 1].
 *
 * Visualization:
 *
 *       0.0                         1.0
 *        |---------------------------|
 *        |    |    |    |    |    |  |
 *       B0   B1   B2   B3   B4  ... Bn
 *
 * Example:
 *
 *       0.17 -> bucket 1
 *       0.39 -> bucket 3
 *       0.78 -> bucket 7
 *
 * Then:
 *
 *   1. Sort every bucket.
 *   2. Concatenate all buckets.
 *
 * Average Time Complexity: O(n)
 * Worst Time Complexity: O(n²)
 * Space Complexity: O(n)
 *
 * The O(n) average case depends on a good/uniform distribution
 * of elements across the buckets.
 *
 * ============================================================================
 */

 /**
  * INSERTION SORT
  *
  * Used to sort the elements inside each bucket.
  */
void insertionSort(vector<double>& bucket)
{
    for (int i = 1; i < (int)bucket.size(); i++)
    {
        double key = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j] > key)
        {
            bucket[j + 1] = bucket[j];
            j--;
        }

        bucket[j + 1] = key;
    }
}

/**
 * BUCKET SORT
 */
void bucketSort(vector<double>& arr)
{
    int n = arr.size();

    if (n == 0)
        return;

    vector<vector<double>> buckets(n);

    // Put each value in its bucket.
    for (double value : arr)
    {
        // This implementation only supports [0, 1].
        if (value < 0 || value > 1)
        {
            cout << "Values must be in the range [0, 1].\n";
            return;
        }

        int bucketIndex = (int)(n * value);

        // 1.0 gives n, but the last valid index is n - 1.
        if (bucketIndex == n)
            bucketIndex = n - 1;

        buckets[bucketIndex].push_back(value);
    }

    // Sort every bucket separately.
    for (auto& bucket : buckets)
    {
        insertionSort(bucket);
    }

    // Combine buckets back into the original array.
    int index = 0;

    for (const auto& bucket : buckets)
    {
        for (double value : bucket)
        {
            arr[index++] = value;
        }
    }
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    vector<double> arr =
    {
        0.78, 0.17, 0.39, 0.26, 0.72,
        0.94, 0.21, 0.12, 0.23, 0.68
    };

    cout << fixed << setprecision(2);

    cout << "Original array: ";

    for (double value : arr)
        cout << value << " ";

    cout << "\n";

    bucketSort(arr);

    cout << "Sorted array: ";

    for (double value : arr)
        cout << value << " ";

    cout << "\n";

    return 0;
}