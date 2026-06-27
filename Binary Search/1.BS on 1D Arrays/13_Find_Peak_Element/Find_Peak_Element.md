# Peak Element in Array

---

# Problem Statement

Given an array, find the **index (0-based)** of any **peak element**.

A peak element is an element that is **greater than its adjacent neighbors**.

Formally,

```
arr[i-1] < arr[i] > arr[i+1]
```

If multiple peaks exist, return the index of **any one** of them.

> For boundary elements, only one neighbor exists.

---

# Examples

## Example 1

**Input**

```text
arr = [1,2,3,4,5,6,7,8,5,1]
```

**Output**

```text
7
```

**Explanation**

```
8 > 7

8 > 5
```

So index **7** is a peak.

---

## Example 2

**Input**

```text
arr = [1,2,1,3,5,6,4]
```

**Output**

```text
1
```

or

```text
5
```

Both are valid because both are peak elements.

---

# Core Idea / Pattern Recognition

**Pattern**

```
Binary Search on Answer
```

### Why?

Instead of checking every element, observe the **slope** around the middle element.

- If we're moving **uphill**, a peak must exist on the right.
- If we're moving **downhill**, a peak must exist on the left (including mid).

This lets us eliminate half of the array every iteration.

---

# Observation

Suppose

```
1 3 5 7 9 6 4
```

```
          ↑

Peak
```

Notice

```
Increasing

↓

Peak

↓

Decreasing
```

Now consider

```
1 2 3 4 5
```

```
Increasing
```

The last element itself is a peak.

Similarly,

```
5 4 3 2 1
```

The first element is a peak.

**Every array always has at least one peak.**

---

# Approach 1 — Brute Force

## Idea

Traverse the array and check whether every element is greater than its neighbors.

The first valid peak can be returned.

---

## Algorithm

1. Traverse the array.
2. Compare current element with left and right neighbors.
3. If greater than both, return its index.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find a peak element in the array
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();

        // Traverse the array
        for (int i = 0; i < n; i++) {
            // Check left neighbor if exists
            bool left = (i == 0) || (nums[i] >= nums[i - 1]);
            // Check right neighbor if exists
            bool right = (i == n - 1) || (nums[i] >= nums[i + 1]);

            // If both sides are valid, return index
            if (left && right) return i;
        }

        return -1;
    }
};
```

---

## Visualization

```
1 2 3 4 5 6 7 8 5 1
              ↑

7 < 8 > 5

Peak
```

---

## Dry Run

```
1

Not Peak

↓

2

Not Peak

↓

...

↓

8

7 < 8

8 > 5

Peak Found
```

Return

```
7
```

---

## Complexity

**Time:** `O(N)`

**Space:** `O(1)`

---

# Approach 2 — Optimal Approach

## Main Idea

Instead of checking both neighbors,

compare

```
nums[mid]
```

with

```
nums[mid+1]
```

This tells us the direction of the slope.

- Descending slope → Peak is on the left (including mid).
- Ascending slope → Peak is on the right.

---

## Why It Works

### Case 1

```
nums[mid] > nums[mid+1]
```

Example

```
1 3 7 9 6 4

      M
```

```
9 > 6
```

We are on a **downhill slope**.

A peak already exists on the left.

```
high = mid
```

---

### Case 2

```
nums[mid] < nums[mid+1]
```

Example

```
1 2 4 6 8

    M
```

```
4 < 6
```

We are climbing.

A peak must exist on the right.

```
low = mid + 1
```

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find a peak element using binary search
    int findPeakElement(vector<int>& nums) {
        // Set left and right bounds
        int low = 0, high = nums.size() - 1;

        // Binary search loop
        while (low < high) {
            // Find mid point
            int mid = (low + high) / 2;

            // If mid element is greater than next
            if (nums[mid] > nums[mid + 1]) {
                // Move to left half
                high = mid;
            } else {
                // Move to right half
                low = mid + 1;
            }
        }

        // Return peak index
        return low;
    }
};
```

---

## Pointer Placement Visualization

### Initial Array

```
1 2 1 3 5 6 4

L     M     H
```

```
mid = 3

nums[mid]=3

nums[mid+1]=5
```

```
3 < 5
```

Ascending.

Move Right.

```
low = mid + 1
```

---

### Next Iteration

```
5 6 4

L M H
```

```
6 > 4
```

Descending.

Move Left.

```
high = mid
```

---

### Final

```
5 6

L H
```

```
mid=4

5 < 6
```

```
low=5
```

Now

```
low == high
```

Peak found.

---

## Dry Run

Input

```
1 2 1 3 5 6 4
```

### Iteration 1

```
low=0

high=6

mid=3
```

```
3 < 5
```

Move Right

```
low=4
```

---

### Iteration 2

```
low=4

high=6

mid=5
```

```
6 > 4
```

Move Left

```
high=5
```

---

### Iteration 3

```
low=4

high=5

mid=4
```

```
5 < 6
```

Move Right

```
low=5
```

Now

```
low==high==5
```

Return

```
5
```

---

## Edge Cases

- Single element
- Peak at first index
- Peak at last index
- Multiple peaks
- Strictly increasing array
- Strictly decreasing array

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

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Linear Scan | `O(N)` | `O(1)` | Check every element |
| Binary Search | `O(log N)` | `O(1)` | Uses slope to locate a peak |

---

# Key Takeaways

- Every array has at least one peak.
- Compare `mid` with `mid + 1`, not both neighbors.
- If the slope is increasing, move right.
- If the slope is decreasing, move left.
- Stop when `low == high`.

---

# Revision Template

1. Initialize `low` and `high`.
2. Find `mid`.
3. Compare `nums[mid]` with `nums[mid+1]`.
4. If descending, move `high = mid`.
5. Else move `low = mid + 1`.
6. Continue until `low == high`.
7. Return `low`.

---

# Memory Trick

```
Compare Mid

↓

Downhill?

↓

YES → Peak on Left

NO → Peak on Right
```

Think:

> **"Climb the mountain if you're going uphill; stop searching left when you're already coming downhill."**

---

# Final Intuition

> Compare the middle element with its next element to determine the slope, then use binary search to move toward the side that must contain a peak until only one index remains.