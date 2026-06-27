# Merge Two Sorted Arrays Without Extra Space

## Problem Statement

Given two sorted integer arrays `nums1` and `nums2`, merge them into one sorted array in non-decreasing order.

The final result must be stored inside `nums1` itself, and the merge must be done **in-place**.

### Important setup
- `nums1` has size `m + n`
- first `m` elements are valid
- last `n` elements are `0` placeholders
- `nums2` has size `n`

---

## Examples

### Example 1

**Input**

```text
nums1 = [-5, -2, 4, 5, 0, 0, 0]
nums2 = [-3, 1, 8]
```

**Output**

```text
[-5, -3, -2, 1, 4, 5, 8]
```

### Example 2

**Input**

```text
nums1 = [0, 2, 7, 8, 0, 0, 0]
nums2 = [-7, -3, -1]
```

**Output**

```text
[-7, -3, -1, 0, 2, 7, 8]
```

---

## Core Idea

Both arrays are already sorted.

If we try to merge from the **front**, we would overwrite useful values in `nums1`.

So instead, we merge from the **back**.

That way:

- the largest remaining element is placed at the end
- we do not destroy unprocessed elements in `nums1`

This is a classic **two pointers from the end** problem.

---

## Observation

Suppose:

- `nums1` valid part ends at index `m - 1`
- `nums2` ends at index `n - 1`

We place the final merged value at index:

```text
k = m + n - 1
```

At every step:

- compare `nums1[i]` and `nums2[j]`
- put the larger one at `nums1[k]`
- move the corresponding pointer backward

---

# Optimal Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Merges nums2 into nums1 in-place in sorted order.
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // i points to last valid element in nums1
        int i = m - 1;

        // j points to last element in nums2
        int j = n - 1;

        // k is the last index of nums1 (including 0 placeholders)
        int k = m + n - 1;

        // Fill nums1 from the end by comparing nums1[i] and nums2[j]
        while (i >= 0 && j >= 0) {
            // Place larger of the two at nums1[k]
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }

        // If nums2 has remaining elements, copy them
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }

        // No need to copy remaining nums1 elements, as they are already in place
    }
};
```

---

## Why We Merge from the End

If we merge from the front:

- smaller values are placed first
- but this may overwrite valid values in `nums1`

Example:

```text
nums1 = [1, 3, 5, 0, 0, 0]
nums2 = [2, 4, 6]
```

If we start from the front, writing into `nums1[0]`, we may overwrite `1`, `3`, or `5` before we use them.

So we merge from the back, where the free space already exists.

---

## Pointer Meaning

We use three pointers:

- `i` → last valid element in `nums1`
- `j` → last element in `nums2`
- `k` → last position in `nums1`

### Initial positions

```text
i = m - 1
j = n - 1
k = m + n - 1
```

---

## Pointer Placement Visualization

Suppose:

```text
nums1 = [1, 3, 5, 0, 0, 0]
nums2 = [2, 4, 6]
```

Initial:

```text
nums1: [1, 3, 5, _, _, _]
               ↑        ↑
               i        k

nums2: [2, 4, 6]
            ↑
            j
```

We compare `5` and `6`.

- `6` is bigger
- put it at `k`

```text
nums1: [1, 3, 5, _, _, 6]
               ↑     ↑
               i     k
nums2: [2, 4, 6]
         ↑
         j
```

Then compare `5` and `4`.

- `5` is bigger
- put it at `k`

```text
nums1: [1, 3, 5, _, 5, 6]
            ↑  ↑
            i  k
nums2: [2, 4, 6]
         ↑
         j
```

Continue until done.

---

## Dry Run

### Input

```text
nums1 = [1, 3, 5, 0, 0, 0]
nums2 = [2, 4, 6]
m = 3, n = 3
```

Initial state:

```text
i = 2
j = 2
k = 5
```

---

### Step 1

Compare:

```text
nums1[i] = 5
nums2[j] = 6
```

Since `6 > 5`, place `6` at `nums1[k]`.

```text
nums1 = [1, 3, 5, 0, 0, 6]
```

Update:

```text
j = 1
k = 4
i = 2
```

---

### Step 2

Compare:

```text
nums1[i] = 5
nums2[j] = 4
```

Since `5 > 4`, place `5` at `nums1[k]`.

```text
nums1 = [1, 3, 5, 0, 5, 6]
```

Update:

```text
i = 1
k = 3
j = 1
```

---

### Step 3

Compare:

```text
nums1[i] = 3
nums2[j] = 4
```

Since `4 > 3`, place `4` at `nums1[k]`.

```text
nums1 = [1, 3, 5, 4, 5, 6]
```

Update:

```text
j = 0
k = 2
i = 1
```

---

### Step 4

Compare:

```text
nums1[i] = 3
nums2[j] = 2
```

Since `3 > 2`, place `3` at `nums1[k]`.

```text
nums1 = [1, 3, 3, 4, 5, 6]
```

Update:

```text
i = 0
k = 1
j = 0
```

---

### Step 5

Compare:

```text
nums1[i] = 1
nums2[j] = 2
```

Since `2 > 1`, place `2` at `nums1[k]`.

```text
nums1 = [1, 2, 3, 4, 5, 6]
```

Update:

```text
j = -1
k = 0
```

Now `j < 0`, so we stop.

Final answer:

```text
[1, 2, 3, 4, 5, 6]
```

---

## Why No Need to Copy Remaining nums1 Elements

If `nums2` is exhausted first, then the remaining elements in `nums1` are already in the correct place.

They are smaller values that already sit in the front portion of the array.

So only leftover `nums2` elements need copying.

---

## Example Visualization with Actual Problem Input

### Input

```text
nums1 = [-5, -2, 4, 5, 0, 0, 0]
nums2 = [-3, 1, 8]
```

### Final merged order

```text
[-5, -3, -2, 1, 4, 5, 8]
```

This is obtained by placing the largest values at the back first.

---

## Complexity

### Time

```text
O(m + n)
```

Each pointer moves at most once through its array.

### Space

```text
O(1)
```

No extra array is used.

---

## Key Takeaways

- Merge from the **end**, not the front.
- Use three pointers: `i`, `j`, `k`
- Always place the larger of `nums1[i]` and `nums2[j]` at `nums1[k]`
- If `nums2` still has leftover elements, copy them
- If `nums1` has leftover elements, they are already in place

---

## Revision Template

```text
1. Set i = m - 1, j = n - 1, k = m + n - 1
2. Compare nums1[i] and nums2[j]
3. Place the larger one at nums1[k]
4. Move that pointer backward
5. Move k backward
6. If nums2 remains, copy the rest
7. Done
```

---

## Final Intuition

> Fill the empty space from the back so you never overwrite unprocessed elements in nums1.