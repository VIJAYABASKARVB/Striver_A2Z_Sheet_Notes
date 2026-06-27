# Implement Lower Bound

## Problem Statement

Given a **sorted array** `arr` of size `N` and a value `x`, find the **lower bound** of `x`.

### What is Lower Bound?

The **lower bound** is the **first index** such that:

```text
arr[ind] >= x
```

If no such index exists, return:

```text
N
```

---

## Examples

### Example 1

**Input**

```text
N = 4
arr = [1, 2, 2, 3]
x = 2
```

**Output**

```text
1
```

**Explanation**

The first index where value is greater than or equal to `2` is index `1`.

---

### Example 2

**Input**

```text
N = 5
arr = [3, 5, 8, 15, 19]
x = 9
```

**Output**

```text
3
```

**Explanation**

The first element greater than or equal to `9` is `15`, which is at index `3`.

---

## Core Idea

Since the array is **sorted**, we do not need to scan every element.

We can use **binary search** to find the first index where:

```text
arr[index] >= x
```

This is exactly the **lower bound**.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class containing methods for array operations
class LowerBoundFinder {
public:
    // Function to find lower bound index
    int lowerBound(vector<int> arr, int n, int x) {
        // Traverse the array
        for (int i = 0; i < n; i++) {
            // If current element is greater than or equal to x
            if (arr[i] >= x) {
                return i;  // Return index of the first such element
            }
        }
        // If all elements are smaller than x
        return n;
    }
};
```

---

## How It Works

- Start from index `0`
- Check each element one by one
- The first element that satisfies:

```text
arr[i] >= x
```

is the lower bound

If nothing satisfies it, return `n`.

---

## Complexity

- **Time:** `O(N)`
- **Space:** `O(1)`

---

# 2) Optimal Approach — Binary Search

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class to find the lower bound index in an array
class LowerBoundFinder {
public:
    // Function to find the lower bound using binary search
    int lowerBound(vector<int> arr, int n, int x) {
        int low = 0;
        int high = n - 1;
        int ans = n;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (arr[mid] >= x) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
```

---

## Main Idea

We want the **first valid position** where:

```text
arr[mid] >= x
```

If the middle element is already big enough:

- it can be a possible answer
- but maybe there is an even smaller valid index on the left

So we store it in `ans` and continue searching left side.

If the middle element is smaller than `x`:

- the lower bound must be on the right side

---

## Why This Works

Because the array is sorted:

- all values to the left of a valid lower bound are smaller
- once we find a value `>= x`, we must still check if an earlier such value exists

So we keep moving left whenever we find a possible answer.

---

## Visualization

Suppose:

```text
arr = [3, 5, 8, 15, 19]
x = 9
```

Array:

```text
Index:  0  1  2   3   4
Value:  3  5  8  15  19
```

We want the first index with value `>= 9`.

That is index `3`.

---

# Dry Run

## Input

```text
arr = [3, 5, 8, 15, 19]
x = 9
```

Initial state:

```text
low = 0
high = 4
ans = 5
```

---

### Step 1

```text
mid = (0 + 4) / 2 = 2
arr[mid] = 8
```

Since:

```text
8 < 9
```

move right:

```text
low = mid + 1 = 3
```

---

### Step 2

```text
low = 3
high = 4
mid = (3 + 4) / 2 = 3
arr[mid] = 15
```

Since:

```text
15 >= 9
```

this is a possible answer.

Update:

```text
ans = 3
high = mid - 1 = 2
```

---

Now:

```text
low = 3
high = 2
```

Since `low > high`, stop.

Final answer:

```text
3
```

---

# Pointer Movement Visualization

```text
arr = [3, 5, 8, 15, 19]
       L        M      H

Step 1:
mid = 2 -> 8 < 9 -> move right

arr = [3, 5, 8, 15, 19]
                L  H
                M

Step 2:
mid = 3 -> 15 >= 9 -> possible answer
move left to find smaller valid index

Final lower bound = 3
```

---

# Why `ans = n` Initially?

If no element is greater than or equal to `x`, we must return `n`.

Example:

```text
arr = [1, 2, 3]
x = 10
```

No valid index exists.

So the answer should be:

```text
3
```

which is the array size.

---

# Why Move Left When `arr[mid] >= x`?

Because lower bound means the **first** valid index.

If `arr[mid]` is already valid, there may still be a smaller valid index to the left.

So we store `mid` and search left side.

---

# Why Move Right When `arr[mid] < x`?

Because all values before and including `mid` are too small.

So the answer must lie on the right side.

---

# Complexity

## Brute Force

- **Time:** `O(N)`
- **Space:** `O(1)`

## Optimal Approach

- **Time:** `O(log N)`
- **Space:** `O(1)`

---

# Key Takeaways

- Lower bound = first index where `arr[i] >= x`
- If no such index exists, return `N`
- Brute force scans linearly
- Binary search finds the answer in logarithmic time
- When `arr[mid] >= x`, store `mid` and search left
- When `arr[mid] < x`, search right

---

# Revision Template

```text
1. Set low = 0, high = n - 1, ans = n
2. While low <= high
3. Find mid
4. If arr[mid] >= x:
      ans = mid
      high = mid - 1
5. Else:
      low = mid + 1
6. Return ans
```

---

# Final Intuition

> Lower bound is the first position where the sorted array becomes greater than or equal to the target, so binary search keeps moving left whenever a valid position is found.