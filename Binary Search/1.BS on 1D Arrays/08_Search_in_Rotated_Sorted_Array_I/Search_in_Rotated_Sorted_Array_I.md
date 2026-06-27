# Search Element in a Rotated Sorted Array

## Problem Statement

You are given an integer array `nums` that was originally sorted in ascending order, but then rotated at some unknown pivot.

All values are distinct.

Your task is to find the index of the target value `k`.

If the target does not exist, return `-1`.

---

## Examples

### Example 1

**Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `k = 0`
**Output:** `4`

### Example 2

**Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `k = 3`
**Output:** `-1`

---

## Core Idea

The array is **rotated sorted**, which means:

* one half of the array is always sorted
* we can use that sorted half to decide where the target may lie

This allows us to use **Binary Search** and discard half the search space every time.

---

# 1) Brute Force Approach

## Idea

Scan the array linearly and check each element.

If any element equals the target, return its index.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                return i;
            }
        }
        return -1;
    }
};
```

---

## Complexity

* **Time:** `O(N)`
* **Space:** `O(1)`

---

# 2) Optimal Approach — Binary Search in Rotated Array

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (nums[mid] == target)
                return mid;

            // Left half is sorted
            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            // Right half is sorted
            else {
                if (nums[mid] < target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        return -1;
    }
};
```

---

# Main Idea

In a rotated sorted array with distinct values, at least one half of the current range is always sorted.

We check:

* if the **left half** is sorted
* otherwise the **right half** must be sorted

Then we decide whether the target lies inside that sorted half.

---

# Why This Works

A rotated sorted array looks like this:

```text
[4, 5, 6, 7, 0, 1, 2]
```

Even though the full array is not sorted, one side of the midpoint is always sorted.

So we do this:

1. Check which half is sorted
2. If target lies in that sorted half, search there
3. Otherwise search in the other half

This preserves the binary search idea of eliminating half the search space each time.

---

# Important Observation

If

```text
nums[low] <= nums[mid]
```

then the **left half** is sorted.

If not, then the **right half** is sorted.

This is the key condition that makes the algorithm work.

---

# Visualization

Suppose:

```text
nums = [4, 5, 6, 7, 0, 1, 2]
```

Target:

```text
0
```

Initial search range:

```text
low = 0
high = 6
```

Array:

```text
Index : 0 1 2 3 4 5 6
Value : 4 5 6 7 0 1 2
```

---

# Pointer Placement Visualization

### Initial

```text
4 5 6 7 0 1 2
L       M     H
```

```text
low = 0
mid = 3
high = 6
```

`nums[mid] = 7`

`nums[low] = 4`

Since

```text
4 <= 7
```

the **left half is sorted**.

Now check whether target `0` lies inside:

```text
4 <= 0 < 7   ?
```

No.

So search right half.

```text
low = mid + 1 = 4
```

---

### Next

```text
4 5 6 7 0 1 2
        L M   H
```

```text
low = 4
mid = 5
high = 6
```

`nums[mid] = 1`

`nums[low] = 0`

Since

```text
0 <= 1
```

the **left half is sorted** again.

Now check target `0`:

```text
0 <= 0 < 1
```

Yes.

So search left half.

```text
high = mid - 1 = 4
```

---

### Next

```text
4 5 6 7 0 1 2
        L
        M
        H
```

```text
low = 4
mid = 4
high = 4
```

`nums[mid] = 0`

Target found.

Return:

```text
4
```

---

# Dry Run

## Input

```text
nums = [4, 5, 6, 7, 0, 1, 2]
target = 0
```

### Iteration 1

```text
low = 0
high = 6
mid = 3
nums[mid] = 7
```

Left half sorted:

```text
nums[low] <= nums[mid]
4 <= 7  -> true
```

Check target in left half:

```text
4 <= 0 < 7  -> false
```

Move right:

```text
low = 4
```

---

### Iteration 2

```text
low = 4
high = 6
mid = 5
nums[mid] = 1
```

Left half sorted:

```text
0 <= 1  -> true
```

Check target in left half:

```text
0 <= 0 < 1  -> true
```

Move left:

```text
high = 4
```

---

### Iteration 3

```text
low = 4
high = 4
mid = 4
nums[mid] = 0
```

Target found.

Return:

```text
4
```

---

# Case When Target Is Not Present

Example:

```text
nums = [4, 5, 6, 7, 0, 1, 2]
target = 3
```

The algorithm keeps narrowing the search space using the sorted-half logic.

Since `3` is not in the array, eventually:

```text
low > high
```

and we return:

```text
-1
```

---

# Why We Check the Sorted Half

In a normal sorted array, we can decide left or right using the midpoint value alone.

But in a rotated array:

* the whole array is not sorted
* only one half is sorted at a time

So we first identify the sorted half, then decide whether the target lies inside it.

That is the key trick.

---

# Complexity

## Brute Force

* **Time:** `O(N)`
* **Space:** `O(1)`

## Optimal Approach

* **Time:** `O(log N)`
* **Space:** `O(1)`

---

# Key Takeaways

* A rotated sorted array still contains a sorted half in every step.
* Check whether the left half is sorted or the right half is sorted.
* If the target lies in the sorted half, search there.
* Otherwise search the other half.
* This is standard binary search adapted for rotation.

---

# Revision Template

```text
1. Set low and high
2. Find mid
3. If nums[mid] == target, return mid
4. Check which half is sorted
5. If target lies in sorted half, search there
6. Otherwise search the other half
7. If not found, return -1
```

---

# Memory Trick

```text
Rotated array = sorted half + unsorted half

Find the sorted half first

Then ask:

Is target inside that half?

If yes -> go there
If no  -> go to the other half
```

---

# Final Intuition

> In every step of a rotated-array binary search, one half is still sorted; use that sorted half to decide where the target can and cannot be.
