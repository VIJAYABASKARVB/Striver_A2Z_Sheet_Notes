# Find out How Many Times the Array Has Been Rotated

---

# Problem Statement

You are given a **sorted array with distinct elements** that has been rotated an unknown number of times.

Your task is to determine **how many times the array has been rotated**.

### Key Observation

The **number of rotations** is exactly the **index of the smallest element**.

---

# Examples

## Example 1

**Input**

```text
arr = [4,5,6,7,0,1,2,3]
```

**Output**

```text
4
```

**Explanation**

Original array

```text
0 1 2 3 4 5 6 7
```

After 4 left rotations (or equivalently 4 positions of rotation), it becomes

```text
4 5 6 7 0 1 2 3
```

The minimum element `0` is at index **4**, so the array has been rotated **4 times**.

---

## Example 2

**Input**

```text
arr = [3,4,5,1,2]
```

**Output**

```text
3
```

---

# Core Idea / Pattern Recognition

**Pattern**

```
Modified Binary Search
```

### Why?

The rotation point is exactly where the **minimum element** exists.

Since the previous problem already finds the minimum in `O(log N)`, we simply return its **index** instead of its value.

---

# Observation

Consider

```
Original

0 1 2 3 4 5 6 7
```

After rotation

```
4 5 6 7 0 1 2 3
```

Notice

```
Minimum = 0

Index = 4
```

That index is exactly the number of rotations.

So,

```
Rotation Count

=

Index of Minimum Element
```

---

# Approach 1 — Brute Force

## Idea

Traverse the entire array and find the smallest element along with its index.

Return the index.

---

## Algorithm

1. Assume first element is minimum.
2. Traverse the array.
3. Update minimum and its index whenever a smaller element is found.
4. Return the index.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the number of rotations in a rotated sorted array
    int findRotations(vector<int>& arr) {
        // Store size of array
        int n = arr.size();

        // Assume the first element is the smallest
        int minVal = arr[0];

        // Index of the smallest element
        int minIndex = 0;

        // Traverse the array
        for (int i = 1; i < n; i++) {
            // If current element is smaller than minVal, update
            if (arr[i] < minVal) {
                minVal = arr[i];
                minIndex = i;
            }
        }

        // The index of smallest element = number of rotations
        return minIndex;
    }
};
```

---

## Visualization

```
Array

4 5 6 7 0 1 2 3
        ↑

Smallest Element

Index = 4
```

Return

```
4
```

---

## Dry Run

```
min = 4
index = 0

5 → ignore

6 → ignore

7 → ignore

0 → update

min = 0

index = 4

1 → ignore

2 → ignore

3 → ignore
```

Answer

```
4
```

---

## Complexity

**Time:** `O(N)`

**Space:** `O(1)`

---

# Approach 2 — Better Approach

## Idea

A rotated sorted array has **exactly one break point**.

Example

```
3 4 5 1 2
```

Notice

```
5 > 1
```

The break occurs here.

The next index is the rotation count.

---

## Algorithm

1. Traverse the array.
2. Find the first position where

```
arr[i] > arr[i+1]
```

3. Return `i+1`.
4. If no break exists, return `0`.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Function to find rotation count using one-pass scan
int findRotationCount(vector<int> &arr) {
    // Get the size of the array
    int n = arr.size();
    // Traverse the array till second-last element
    for (int i = 0; i < n - 1; i++) {
        // If current element is greater than the next, break point found
        if (arr[i] > arr[i + 1]) {
            // Rotation count is index of next element
            return i + 1;
        }
    }
    // If no break point found, array not rotated
    return 0;
}
```

---

## Visualization

```
3 4 5 1 2

    ↑
    |

5 > 1

Rotation Count = 3
```

---

## Dry Run

```
3 < 4 ✔

4 < 5 ✔

5 > 1 ❌

Return

2 + 1 = 3
```

---

## Complexity

**Time:** `O(N)`

**Space:** `O(1)`

---

# Approach 3 — Optimal Approach

## Main Idea

Instead of finding the minimum value,

find its **index** using Binary Search.

Since

```
Rotation Count

=

Index of Minimum
```

we simply return `low`.

---

## Why It Works

Compare

```
arr[mid]
```

with

```
arr[high]
```

### Case 1

```
arr[mid] > arr[high]
```

Example

```
4 5 6 7 0 1 2

L     M     H
```

```
7 > 2
```

Minimum is to the **right**.

```
low = mid + 1
```

---

### Case 2

```
arr[mid] <= arr[high]
```

Example

```
0 1 2

L M H
```

Minimum is at `mid` or left.

```
high = mid
```

Repeat until

```
low == high
```

That index is the answer.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find rotation count using binary search
    int findRotations(vector<int>& arr) {
        // Initialize low and high pointers
        int low = 0;
        int high = arr.size() - 1;

        // Loop until low meets high
        while (low < high) {
            // Find mid index
            int mid = low + (high - low) / 2;

            // If mid element is greater than element at high,
            // smallest element lies to the right of mid
            if (arr[mid] > arr[high]) {
                low = mid + 1;
            } else {
                // Else smallest element is at mid or to the left
                high = mid;
            }
        }

        // When low == high, we found the smallest element
        return low;
    }
};
```

---

## Pointer Placement Visualization

Initial

```
Index

0 1 2 3 4 5 6 7

4 5 6 7 0 1 2 3
L     M       H
```

```
7 > 3

Minimum is Right

↓

low = mid + 1
```

---

Next

```
0 1 2 3

L M   H
```

```
1 <= 3

Minimum is Left

↓

high = mid
```

---

Next

```
0 1

L H
```

```
0 <= 1

↓

high = mid
```

Now

```
low == high == 4
```

Rotation Count

```
4
```

---

## Dry Run

Input

```
4 5 6 7 0 1 2 3
```

### Iteration 1

```
low = 0

high = 7

mid = 3
```

```
7 > 3
```

```
low = 4
```

---

### Iteration 2

```
low = 4

high = 7

mid = 5
```

```
1 <= 3
```

```
high = 5
```

---

### Iteration 3

```
low = 4

high = 5

mid = 4
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
4
```

---

## Edge Cases

- Array not rotated → Answer = `0`
- Single element → Answer = `0`
- Rotation by `N` → Same as no rotation
- Minimum at first index
- Minimum at last index

---

## Complexity

### Time

```
O(log N)
```

Binary Search halves the search space.

### Space

```
O(1)
```

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Linear Search | `O(N)` | `O(1)` | Finds minimum index directly |
| One-Pass Scan | `O(N)` | `O(1)` | Finds the break point |
| Binary Search | `O(log N)` | `O(1)` | Finds the minimum index efficiently |

---

# Key Takeaways

- Rotation count equals the **index of the smallest element**.
- A rotated array has exactly one break point.
- The previous "Find Minimum" problem can be reused directly.
- Compare `mid` with `high` to locate the minimum.
- Return the index, not the value.

---

# Revision Template

1. Initialize `low` and `high`.
2. Compute `mid`.
3. Compare `arr[mid]` with `arr[high]`.
4. If `mid > high`, search right.
5. Otherwise search left (including `mid`).
6. Stop when `low == high`.
7. Return `low`.

---

# Memory Trick

```
Find Minimum

↓

Return Its Index

↓

That Index = Rotation Count
```

Think:

> **"Rotation Count = Position of the Smallest Element."**

---

# Final Intuition

> The smallest element marks the rotation point, so use binary search to locate it and return its index as the number of rotations.