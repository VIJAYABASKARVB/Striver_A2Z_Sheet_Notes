# Search Single Element in a Sorted Array

---

# Problem Statement

You are given a **sorted array** where **every element appears exactly twice except one element**, which appears only once.

Find and return that **single non-duplicate element**.

**Constraints**

- Array is sorted.
- Exactly one element appears once.
- Every other element appears twice.

---

# Examples

## Example 1

**Input**

```text
arr = [1,1,2,2,3,3,4,5,5,6,6]
```

**Output**

```text
4
```

---

## Example 2

**Input**

```text
arr = [1,1,3,5,5]
```

**Output**

```text
3
```

---

# Core Idea / Pattern Recognition

**Pattern**

```
Binary Search + Index Pattern
```

### Why?

Since the array is sorted, duplicate elements always appear **adjacent**.

The unique element breaks this pairing pattern.

Using Binary Search, we can determine **which side contains the broken pattern** and eliminate half of the array every iteration.

---

# Observation

Before the single element,

every pair starts at an **even index**.

```
Index

0 1 2 3 4 5

Array

1 1 2 2 3 3

Pairs

(0,1)

(2,3)

(4,5)
```

After the single element appears, the pairing shifts.

Example

```
1 1 2 2 3 4 4 5 5
```

Indices

```
0 1 2 3 4 5 6 7 8
```

Now,

```
4 4

starts at

5 (odd)
```

This change in parity is the key observation used in Binary Search.

---

# Approach 1 — Brute Force

## Idea

Since the array is sorted, the single element is the only one that differs from both its neighbors.

Traverse the array and compare each element with its adjacent elements.

---

## Algorithm

1. Handle first and last elements separately.
2. Traverse the array.
3. If an element is different from both neighbors, return it.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNonDuplicate(vector<int>& arr) {
        int n = arr.size();

        if (n == 1) return arr[0];

        for (int i = 0; i < n; i++) {

            if (i == 0) {
                if (arr[i] != arr[i + 1])
                    return arr[i];
            }

            else if (i == n - 1) {
                if (arr[i] != arr[i - 1])
                    return arr[i];
            }

            else {
                if (arr[i] != arr[i - 1] && arr[i] != arr[i + 1])
                    return arr[i];
            }
        }

        return -1;
    }
};
```

---

## Visualization

```
1 1 2 2 3 3 4 5 5 6 6

            ↑

Left != Current

Current != Right

Answer = 4
```

---

## Dry Run

```
1 == 1

2 == 2

3 == 3

4 != 3

4 != 5

Return 4
```

---

## Complexity

**Time:** `O(N)`

**Space:** `O(1)`

---

# Approach 2 — Optimal Approach

## Main Idea

Use Binary Search.

The unique element changes the normal pairing pattern.

### Before the unique element

Pairs begin at **even indices**.

```
0 1

2 3

4 5
```

### After the unique element

Pairs begin at **odd indices**.

```
5 6

7 8
```

Using this parity, we can identify which half contains the answer.

---

## Why It Works

Suppose

```
1 1 2 2 3 3 4 5 5 6 6
```

The single element is

```
4
```

Notice

```
Before 4

Pairs start at

Even Index
```

```
0 1

2 3

4 5
```

After 4

```
5 5

6 6
```

Pairs now start at

```
Odd Index
```

The parity changes exactly after the single element.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

int singleNonDuplicate(vector<int>& arr) {
    int n = arr.size();

    if (n == 1) return arr[0];

    if (arr[0] != arr[1]) return arr[0];

    if (arr[n - 1] != arr[n - 2]) return arr[n - 1];

    int low = 1, high = n - 2;

    while (low <= high) {

        int mid = (low + high) / 2;

        if (arr[mid] != arr[mid + 1] && arr[mid] != arr[mid - 1]) {
            return arr[mid];
        }

        if ((mid % 2 == 1 && arr[mid] == arr[mid - 1]) ||
            (mid % 2 == 0 && arr[mid] == arr[mid + 1])) {

            low = mid + 1;
        }
        else {

            high = mid - 1;
        }
    }

    return -1;
}
};
```

---

## Pointer Placement Visualization

### Initial Array

```
Index

0 1 2 3 4 5 6 7 8 9 10

1 1 2 2 3 3 4 5 5 6 6
L         M           H
```

```
mid = 5

arr[mid] = 3

mid is odd

arr[mid] == arr[mid-1]

Correct pairing
```

So,

```
Single element is on the Right

↓

low = mid + 1
```

---

### Next Iteration

```
1 1 2 2 3 3 4 5 5 6 6

            L M     H
```

```
mid = 8

arr[mid] = 5

Even index

arr[mid] != arr[mid+1]
```

Pairing breaks.

Move Left.

```
high = mid - 1
```

---

### Final

```
1 1 2 2 3 3 4 5 5

          L
          M
          H
```

```
4

Left != Current

Current != Right
```

Return

```
4
```

---

## Dry Run

Input

```
1 1 2 2 3 3 4 5 5 6 6
```

### Iteration 1

```
low=1

high=9

mid=5
```

```
mid is odd

arr[5]==arr[4]

Correct pairing
```

Move Right

```
low=6
```

---

### Iteration 2

```
low=6

high=9

mid=7
```

```
mid odd

arr[7]!=arr[6]
```

Broken pairing.

Move Left

```
high=6
```

---

### Iteration 3

```
low=6

high=6

mid=6
```

```
arr[6]

!=

arr[5]

&&

arr[6]

!=

arr[7]
```

Return

```
4
```

---

## Edge Cases

- Only one element
- Single element at the beginning
- Single element at the end
- Single element in the middle
- Smallest valid array (`n = 1`)

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
| Linear Scan | `O(N)` | `O(1)` | Compare every element with neighbors |
| Binary Search | `O(log N)` | `O(1)` | Uses index parity to locate the broken pair |

---

# Key Takeaways

- Before the single element, pairs start at **even indices**.
- After the single element, pairs start at **odd indices**.
- Binary Search identifies where the pairing pattern breaks.
- Always handle edge cases (first, last, single element) before the loop.

---

# Revision Template

1. Handle edge cases.
2. Binary Search on indices.
3. Check if `mid` is the unique element.
4. If pairing follows the expected parity, move right.
5. Otherwise, move left.
6. Return the unique element.

---

# Memory Trick

```
Before Single

Even → Even

↓

After Single

Odd → Odd

↓

Parity Changes

↓

Binary Search
```

Remember:

> **"The single element flips the pairing pattern from even-start pairs to odd-start pairs."**

---

# Final Intuition

> The unique element is exactly where the normal even-index pairing pattern breaks, so Binary Search uses index parity to locate that break in `O(log N)` time.