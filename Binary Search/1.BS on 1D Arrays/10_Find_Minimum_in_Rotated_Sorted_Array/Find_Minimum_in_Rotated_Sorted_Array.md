# Minimum in Rotated Sorted Array

---

# Problem Statement

You are given a **sorted array with distinct elements** that has been **rotated at an unknown pivot**.

Your task is to find the **minimum element** in the array.

The solution should be more efficient than scanning every element.

---

# Examples

## Example 1

**Input**

```text
arr = [4,5,6,7,0,1,2,3]
```

**Output**

```text
0
```

**Explanation**

The array was originally

```text
0 1 2 3 4 5 6 7
```

After rotation,

```text
4 5 6 7 0 1 2 3
```

The smallest element is **0**.

---

## Example 2

**Input**

```text
arr = [3,4,5,1,2]
```

**Output**

```text
1
```

---

# Core Idea / Pattern Recognition

**Pattern**

```
Modified Binary Search
```

### Why?

A rotated sorted array consists of **two sorted halves**.

Example

```
4 5 6 7 | 0 1 2 3
```

The minimum element is exactly where the rotation occurs.

Instead of checking every element, Binary Search helps us eliminate **half of the array** in every iteration.

---

# Observation

Consider

```
4 5 6 7 0 1 2 3
```

Notice

```
Left Half

4 5 6 7

Sorted

Right Half

0 1 2 3

Sorted
```

The minimum lies in the **unsorted transition**.

Another important observation:

If

```
nums[mid] > nums[high]
```

then

```
mid
```

belongs to the left sorted portion.

So the minimum must be **to the right**.

If

```
nums[mid] <= nums[high]
```

then the minimum lies in the **left half (including mid)**.

---

# Approach 1 — Brute Force

## Idea

Traverse the array and keep track of the smallest element.

---

## Algorithm

1. Initialize `minVal = INT_MAX`.
2. Traverse every element.
3. Update the minimum.
4. Return the minimum.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the minimum element using linear search
    int findMin(vector<int>& nums) {

        // Initialize answer with a large number
        int minVal = INT_MAX;

        // Traverse each element
        for (int i = 0; i < nums.size(); i++) {

            // Update minimum value
            minVal = min(minVal, nums[i]);
        }

        // Return the result
        return minVal;
    }
};

int main() {

    // Input array
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};

    // Create object of Solution
    Solution sol;

    // Call function and store result
    int result = sol.findMin(nums);

    // Output the result
    cout << "Minimum element is " << result << endl;

    return 0;
}
```

---

## Visualization

```
Array

4 5 6 7 0 1 2
          ↑

Minimum
```

Linear search checks every element until the smallest value is found.

---

## Dry Run

```
min = INF

4 → min = 4

5 → 4

6 → 4

7 → 4

0 → min = 0

1 → 0

2 → 0
```

Answer

```
0
```

---

## Complexity

**Time:** `O(N)`

**Space:** `O(1)`

---

# Approach 2 — Optimal Approach

## Main Idea

Use Binary Search to locate the rotation point.

Instead of searching for the minimum directly, compare

```
nums[mid]
```

with

```
nums[high]
```

This tells us **which half contains the minimum**.

---

## Why It Works

### Case 1

```
nums[mid] > nums[high]
```

Example

```
4 5 6 7 0 1 2

L     M     H

mid = 7

high = 2
```

Since

```
7 > 2
```

the minimum **cannot** be in the left half.

Discard it.

```
low = mid + 1
```

---

### Case 2

```
nums[mid] <= nums[high]
```

Example

```
0 1 2 3

L M     H
```

Everything from `mid` to `high` is sorted.

The minimum could be

- `mid`
- or somewhere to its left.

So keep `mid`.

```
high = mid
```

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the minimum element using binary search
    int findMin(vector<int>& nums) {

        // Initialize low and high pointers
        int low = 0, high = nums.size() - 1;

        // Binary search loop
        while (low < high) {

            // Calculate mid index
            int mid = low + (high - low) / 2;

            // Check which half to discard
            if (nums[mid] > nums[high]) {

                // Minimum lies in right half
                low = mid + 1;

            } else {

                // Minimum lies in left half (including mid)
                high = mid;
            }
        }

        // Return the minimum element
        return nums[low];
    }
};
```

---

## Pointer Placement Visualization

### Initial Array

```
Index

0 1 2 3 4 5 6

4 5 6 7 0 1 2
L     M     H
```

```
nums[mid]=7

nums[high]=2

7 > 2
```

Discard left half.

```
low = mid + 1
```

---

### Next Iteration

```
0 1 2

L M H
```

```
nums[mid]=1

nums[high]=2

1 <= 2
```

Minimum is in the left half (including mid).

```
high = mid
```

---

### Final

```
0 1

L H
```

```
mid = 0
```

Again

```
0 <= 1
```

```
high = mid
```

Now

```
low == high
```

Minimum found.

---

## Dry Run

Input

```
4 5 6 7 0 1 2
```

### Iteration 1

```
low=0

high=6

mid=3
```

```
4 5 6 7 0 1 2
L     M     H
```

```
7 > 2
```

```
low = 4
```

---

### Iteration 2

```
low=4

high=6

mid=5
```

```
0 1 2
L M H
```

```
1 <= 2
```

```
high = 5
```

---

### Iteration 3

```
low=4

high=5

mid=4
```

```
0 1
L H
```

```
0 <= 1
```

```
high = 4
```

Now

```
low == high == 4
```

Return

```
nums[4] = 0
```

---

## Edge Cases

- Array of size 1
- Array not rotated
- Rotation at the last index
- Minimum at index 0
- Minimum at the middle
- Large array

---

## Complexity

### Time

```
O(log N)
```

Binary Search halves the search space every iteration.

### Space

```
O(1)
```

Only pointers are used.

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Linear Search | `O(N)` | `O(1)` | Checks every element |
| Modified Binary Search | `O(log N)` | `O(1)` | Uses rotation property |

---

# Key Takeaways

- Rotated array always consists of **two sorted halves**.
- Compare `mid` with `high` to identify the side containing the minimum.
- If `nums[mid] > nums[high]`, search the right half.
- Otherwise, search the left half **including mid**.
- Stop when `low == high`.

---

# Revision Template

1. Initialize `low` and `high`.
2. Find `mid`.
3. Compare `nums[mid]` with `nums[high]`.
4. If `mid > high`, move `low = mid + 1`.
5. Else move `high = mid`.
6. Repeat until `low == high`.
7. Return `nums[low]`.

---

# Memory Trick

```
Compare Mid with High

↓

Mid > High ?

↓

YES → Minimum is Right

NO → Minimum is Left (including Mid)
```

Think:

> **"High acts as the reference. If mid is bigger than high, the rotation (minimum) is still to the right."**

---

# Final Intuition

> Compare the middle element with the last element to determine which half contains the rotation point, and repeatedly discard the other half until only the minimum element remains.