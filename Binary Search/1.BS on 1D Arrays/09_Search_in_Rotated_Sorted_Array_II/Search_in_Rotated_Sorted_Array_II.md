# Search Element in Rotated Sorted Array II

---

# Problem Statement

Given a **rotated sorted array** that **may contain duplicate values**, determine whether a target value `k` exists in the array.

Return:

- `true` if the target is present.
- `false` otherwise.

Unlike the previous version of this problem, **duplicates are allowed**, making it harder to determine which half of the array is sorted.

---

# Examples

## Example 1

**Input**

```text
arr = [7,8,1,2,3,3,3,4,5,6]
k = 3
```

**Output**

```text
true
```

**Explanation**

The target `3` exists in the array.

---

## Example 2

**Input**

```text
arr = [7,8,1,2,3,3,3,4,5,6]
k = 10
```

**Output**

```text
false
```

**Explanation**

The target `10` is not present.

---

# Core Idea / Pattern Recognition

**Pattern**

```
Modified Binary Search
```

### Why?

In a rotated sorted array:

- At least one half is normally sorted.
- We use that sorted half to decide where the target can lie.

However, **duplicates introduce ambiguity**.

Example:

```
3 3 3 1 2 3 3

L     M     H
```

Here,

```
arr[low] == arr[mid] == arr[high]
```

We **cannot determine** which half is sorted.

So, we shrink the search space by doing:

```cpp
low++;
high--;
```

---

# Observation

Without duplicates:

```
4 5 6 7 0 1 2

L     M     H
```

One side is always clearly sorted.

With duplicates:

```
1 0 1 1 1

L   M     H
```

```
arr[low] = 1
arr[mid] = 1
arr[high] = 1
```

Both halves appear identical.

We lose the ability to identify the sorted half.

**Solution:** Skip the duplicate boundaries.

---

# Approach 1 — Brute Force

## Idea

Traverse every element and compare it with the target.

If found, return `true`.

Otherwise, return `false`.

---

## Algorithm

1. Traverse the array.
2. If `arr[i] == k`, return `true`.
3. If traversal finishes, return `false`.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class to encapsulate search logic
class Solution {
public:
    // Linear search in rotated sorted array (with duplicates)
    bool searchInARotatedSortedArrayII(vector<int>& arr, int k) {
        int n = arr.size(); // size of the array
        for (int i = 0; i < n; i++) {
            if (arr[i] == k) return true; // if found, return true
        }
        return false; // not found
    }
};

int main() {
    vector<int> arr = {7, 8, 1, 2, 3, 3, 3, 4, 5, 6};
    int k = 3;

    Solution obj;
    bool ans = obj.searchInARotatedSortedArrayII(arr, k);

    if (!ans)
        cout << "Target is not present.\n";
    else
        cout << "Target is present in the array.\n";

    return 0;
}
```

---

## Visualization

```
Target = 3

7 8 1 2 3 3 3 4 5 6
↑ ↑ ↑ ↑ ↑
        Found
```

---

## Dry Run

```
k = 3

i=0 → 7 ❌
i=1 → 8 ❌
i=2 → 1 ❌
i=3 → 2 ❌
i=4 → 3 ✅
```

Return `true`.

---

## Complexity

**Time:** `O(N)`

**Space:** `O(1)`

---

# Approach 2 — Optimal Approach

## Main Idea

Use **Modified Binary Search**.

For every iteration:

- If `arr[mid] == target`, return `true`.
- Remove duplicate ambiguity if needed.
- Identify the sorted half.
- Decide whether the target belongs there.

---

## Why It Works

Normally,

```
One side is sorted.
```

Example

```
7 8 1 2 3 4 5

L   M       H
```

Left isn't sorted.

Right is sorted.

Use the sorted half to eliminate half of the search space.

The only exception is when

```
arr[low] == arr[mid] == arr[high]
```

because both halves look identical.

Example

```
1 1 1 0 1

L   M   H
```

We cannot decide which half is sorted.

So we safely discard the duplicate boundaries:

```cpp
low++;
high--;
```

Eventually, the ambiguity disappears.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

bool searchInARotatedSortedArrayII(vector<int>& arr, int k) {
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        // If mid points to the target
        if (arr[mid] == k) return true;

        // Edge case: all three are equal, we cannot determine which side is sorted
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }

        // If the left half is sorted
        if (arr[low] <= arr[mid]) {
            if (arr[low] <= k && k <= arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else {
            // Right half is sorted
            if (arr[mid] <= k && k <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    return false;
}
```

---

## Pointer Placement Visualization

### Initial Array

```
7 8 1 2 3 3 3 4 5 6
L       M         H
```

```
low = 0
mid = 4
high = 9
```

```
arr[mid] = 3
```

Target found immediately.

---

### Duplicate Case Visualization

Suppose

```
1 1 1 0 1

L   M   H
```

```
arr[low]
=

arr[mid]
=

arr[high]
```

We cannot determine

```
Sorted Left ?

or

Sorted Right ?
```

So

```
low++
high--
```

becomes

```
1 1 1 0 1
  L M H
```

Eventually,

```
1 0 1

L M H
```

Now one side becomes distinguishable.

---

## Dry Run

Input

```
7 8 1 2 3 3 3 4 5 6

Target = 3
```

### Iteration 1

```
low = 0
high = 9

mid = 4
```

```
7 8 1 2 3 3 3 4 5 6
L       M         H
```

```
arr[mid] = 3
```

Target found.

Return

```
true
```

---

## Duplicate Handling (Most Important)

Why do we write?

```cpp
if(arr[low]==arr[mid] && arr[mid]==arr[high]){
    low++;
    high--;
}
```

Consider

```
1 0 1 1 1

L   M   H
```

Here

```
arr[low]=1

arr[mid]=1

arr[high]=1
```

Normally we ask

```
Is Left Sorted?

OR

Is Right Sorted?
```

But both answers appear true because of duplicates.

We **cannot eliminate half the array safely**.

The only safe operation is

```
Ignore one duplicate
from each side.
```

Eventually

```
0 1 1

L M H
```

or

```
1 0 1

L M H
```

One side becomes distinguishable again.

> **Important:** This duplicate-skipping step is what changes the worst-case complexity from **O(log N)** to **O(N)**, because in the worst case (e.g., all elements are the same), we may only shrink the search space by one element from each end per iteration.

---

## Edge Cases

- Empty array
- Single element
- Target absent
- All elements identical
- Target equals pivot element
- Array not rotated
- Rotation at index `0`
- Large number of duplicates

---

## Complexity

### Average Case

**Time:** `O(log N)`

Binary search eliminates half the search space.

### Worst Case

**Time:** `O(N)`

Example

```
1 1 1 1 1 1 1 1
```

We repeatedly perform

```
low++
high--
```

without eliminating half the array.

### Space

```
O(1)
```

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Linear Search | `O(N)` | `O(1)` | Simple but ignores sorted property |
| Modified Binary Search | `O(log N)` average, `O(N)` worst | `O(1)` | Efficient, handles duplicates |

---

# Key Takeaways

- Binary Search still works after rotation.
- One half is usually sorted.
- Duplicates can hide the sorted half.
- When `arr[low] == arr[mid] == arr[high]`, shrink both ends.
- Worst case becomes `O(N)` because duplicates may force linear shrinking.

---

# Revision Template

1. Find `mid`.
2. If `arr[mid] == target`, return `true`.
3. If `low == mid == high`, do `low++`, `high--`.
4. Identify the sorted half.
5. Check if the target lies in that half.
6. Discard the other half.
7. Repeat until found or search space is empty.

---

# Memory Trick

```
Rotated Array

↓

Find Sorted Half

↓

Duplicates?

↓

Skip Ends

↓

Continue Binary Search
```

Remember:

> **"Equal on all three sides? Peel the duplicates, then decide."**

---

# Final Intuition

> Use binary search to identify the sorted half, but whenever duplicates make both halves indistinguishable, shrink the search space from both ends until the sorted half becomes identifiable.