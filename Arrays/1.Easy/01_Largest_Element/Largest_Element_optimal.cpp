#include <bits/stdc++.h>
using namespace std;

int findLargestElement(int arr[], int n) {
    int max = arr[0];

    // Iterate through the array to find the maximum element
    for (int i = 1; i < n; i++) {
        if (max < arr[i]) { 
            max = arr[i];
        }
    }

    return max;  // Return the largest element found
}

int main() {
    // Array 1
    int arr1[] = {2, 5, 1, 3, 0};
    int n = 5;  // Size of the array
    int max = findLargestElement(arr1, n);  // Call the function to find the largest element
    cout << "The largest element in the array is: " << max << endl;  // Output the result

    // Array 2
    int arr2[] = {8, 10, 5, 7, 9};
    n = 5;  // Size of the array
    max = findLargestElement(arr2, n);  // Call the function to find the largest element
    cout << "The largest element in the array is: " << max << endl;  // Output the result

    return 0;
}