#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Helper to sort individual buckets using Insertion Sort
void insertion_sort(vector<double>& bucket) {
    int n = bucket.size();
    for (int i = 1; i < n; ++i) {
        double key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

// Main Bucket Sort function
void bucket_sort(vector<double>& A) {
    int n = A.size();
    if (n <= 0) return;

    // 1. Create n empty buckets
    vector<vector<double>> buckets(n);

    // 2. Put array elements in different buckets based on their values
    for (int i = 0; i < n; ++i) {
        int bucket_index = static_cast<int>(n * A[i]);
        
        // Edge case handling if a value is exactly 1.0
        if (bucket_index >= n) {
            bucket_index = n - 1;
        }
        buckets[bucket_index].push_back(A[i]);
    }

    // 3. Sort individual buckets using insertion sort
    for (int i = 0; i < n; ++i) {
        insertion_sort(buckets[i]);
    }

    // 4. Concatenate all buckets back into original array A
    int index = 0;
    for (int i = 0; i < n; ++i) {
        for (size_t j = 0; j < buckets[i].size(); ++j) {
            A[index++] = buckets[i][j];
        }
    }
}

int main() {
    // Example values matching fractional entries from uniform bucket distribution slides
    vector<double> test_array = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

    cout << "--- Bucket Sort Test ---\n";
    cout << "Original Array:\n";
    cout << fixed << setprecision(2);
    for (double num : test_array) cout << num << " ";
    cout << "\n\n";

    bucket_sort(test_array);

    cout << "Sorted Array:\n";
    for (double num : test_array) cout << num << " ";
    cout << "\n";

    return 0;
}