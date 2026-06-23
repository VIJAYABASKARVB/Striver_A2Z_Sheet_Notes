# Check if Array is Sorted (Non-Decreasing Order)

## Problem Statement
Given an array of size `n`, write a program to check if the given array is sorted in **ascending / increasing / non-decreasing** order or not.  
If the array is sorted, return `True`; otherwise, return `False`.

---

## Examples

### Example 1:
**Input:**  
`N = 5, array[] = {1, 2, 3, 4, 5}`  
**Output:** `True`  
**Explanation:**  
The given array is sorted. Every element is smaller than or equal to its next element, so the answer is `True`.

### Example 2:
**Input:**  
`N = 5, array[] = {5, 4, 6, 7, 8}`  
**Output:** `False`  
**Explanation:**  
The given array is **not** sorted. Element `5` is greater than `4`, so the condition fails.

---

### Brute Approach

- Use the 2 pointer method to check the `next element is smaller than the current element`
  
  ```cpp
  if (arr[j] < arr[i]) 
    return false;
  ```

### Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to check if the array is sorted
bool isSorted(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // If any element is smaller than the previous one, return false
            if (arr[j] < arr[i]) 
                return false;
        }
    }

    return true; // Return true if no unsorted elements are found
}

int main() {
    int arr[] = {1, 2, 3, 4, 5}, n = 5;
    bool ans = isSorted(arr, n);
    
    // Output result
    if (ans) cout << "True" << endl;
    else cout << "False" << endl;
    
    return 0;
}

```

### Optimal Approach

- Use an single loop starting from `i=1 to arr.size()` and check `arr[i] < arr[i-1]` return `false`

### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;

// Function to check if the array is sorted
bool isSorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i - 1])  // If any element is smaller than the previous one, return false
            return false;
    }

    return true;  // Return true if the array is sorted
}

int main() {
    int arr[] = {1, 2, 3, 4, 5}, n = 5;
    printf("%s", isSorted(arr, n) ? "True" : "False");  // Output result
}

```
