#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// A modified stable counting sort helper function used by radix sort 
void counting_sort_for_radix(vector<int>& A, int place, int radix = 10) {
    int n = A.size();
    vector<int> B(n, 0);
    vector<int> C(radix, 0);

    // Calculate count of elements based on the current digit
    for (int i = 0; i < n; ++i) {
        int digit = (A[i] / place) % radix;
        C[digit]++;
    }

    // Cumulative sums
    for (int i = 1; i < radix; ++i) {
        C[i] += C[i - 1];
    }

    // Build the output array stably backwards
    for (int i = n - 1; i >= 0; --i) {
        int digit = (A[i] / place) % radix;
        B[C[digit] - 1] = A[i];
        C[digit]--;
    }

    // Copy the sorted elements back to the original array A
    A = B;
}

// Main Radix Sort function
void radix_sort(vector<int>& A) {
    if (A.empty()) return;

    // Find the maximum number to know the max number of digits
    int max_val = A[0];
    for (int num : A) {
        if (num > max_val) max_val = num;
    }

    // Apply stable counting sort for every digit position
    // place goes from 1 (1s digit) to 10 (10s digit), 100, etc.
    for (int place = 1; max_val / place > 0; place *= 10) {
        counting_sort_for_radix(A, place);
    }
}

int main() {
    // Example entries matching standard radix sort multi-digit lectures
    vector<int> test_array = {329, 457, 657, 839, 436, 720, 355};

    cout << "--- Radix Sort Test ---\n";
    cout << "Original Array: ";
    for (int num : test_array) cout << num << " ";
    cout << "\n";

    radix_sort(test_array);

    cout << "Sorted Array:   ";
    for (int num : test_array) cout << num << " ";
    cout << "\n";

    return 0;
}