# Remove Duplicates in-place from Sorted Array

## Problem Statement
Given an integer array sorted in non-decreasing order, remove the duplicates in place such that each unique element appears only once. The relative order of the elements should be kept the same.

If there are `k` elements after removing the duplicates, then the first `k` elements of the array should hold the final result. It does not matter what you leave beyond the first `k` elements.

---

## Examples

### Example 1:
**Input:** `arr[] = [1, 1, 2, 2, 2, 3, 3]`  
**Output:** `[1, 2, 3, _, _, _, _]`  
**Explanation:** Total number of unique elements are 3, i.e `[1, 2, 3]` and therefore return 3 after assigning `[1, 2, 3]` in the beginning of the array.

### Example 2:
**Input:** `arr[] = [1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4]`  
**Output:** `[1, 2, 3, 4, _, _, _, _, _, _, _]`  
**Explanation:** Total number of unique elements are 4, i.e `[1, 2, 3, 4]` and therefore return 4 after assigning `[1, 2, 3, 4]` in the beginning of the array.

---

## Brute Force Approach

- Use `unordered_set` & `index=0`.

- If we find the unique number insert into the set.

- Then we will do `nums[index] = num` & `index++`

---

### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

// Solution class containing removeDuplicates method
class Solution {
public:
    // Removes duplicates using unordered_set and returns count of unique elements
    int removeDuplicates(vector<int>& nums) {
        // Unordered set to store elements we have already seen
        unordered_set<int> seen;

        // Index where the next unique element will be written
        int index = 0;

        // Loop over each element in the array
        for (int num : nums) {
            // If num is not in seen, it's unique
            if (seen.find(num) == seen.end()) {
                // Add this num to the set of seen numbers
                seen.insert(num);

                // Overwrite nums[index] with this unique num
                nums[index] = num;

                // Move index forward
                index++;
            }
        }
        // Return count of unique elements
        return index;
    }
};

int main() {
    vector<int> nums = {0,0,1,1,1,2,2,3,3,4};

    Solution sol;
    int k = sol.removeDuplicates(nums);

    cout << "k = " << k << "\nArray after removing duplicates: ";
    for (int i = 0; i < k; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

```
---

## Optimal Approach

### Two-Pointer Technique
- Use two pointers: `i` (slow) and `j` (fast)
- `i` points to the last unique element found
- `j` scans through the array
- When `arr[j] != arr[i]`, we found a new unique element → increment `i` and copy `arr[j]` to `arr[i]`
- Return `i + 1` (number of unique elements)

**Time Complexity:** `O(n)`  
**Space Complexity:** `O(1)`

---

### Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

// Class to hold the solution logic
class Solution {
public:
    // Function to remove duplicates from sorted array in-place
    int removeDuplicates(vector<int>& nums) {
        // If array is empty, return 0 directly
        if (nums.empty()) return 0;

        // Pointer for the position of last unique element
        int i = 0;

        // Traverse the array starting from the second element
        for (int j = 1; j < nums.size(); j++) {
            // If current element is different from last unique element
            if (nums[j] != nums[i]) {
                // Move pointer for unique element forward
                i++;
                // Place the new unique element at the next position
                nums[i] = nums[j];
            }
        }

        // i is index of last unique element, count = i + 1
        return i + 1;
    }
};

int main() {
    vector<int> nums = {0,0,1,1,1,2,2,3,3,4};

    Solution sol;
    int k = sol.removeDuplicates(nums);

    cout << "Unique count = " << k << "\n";
    cout << "Array after removing duplicates: ";
    for (int x = 0; x < k; x++) {
        cout << nums[x] << " ";
    }
    cout << endl;
}

```
---

