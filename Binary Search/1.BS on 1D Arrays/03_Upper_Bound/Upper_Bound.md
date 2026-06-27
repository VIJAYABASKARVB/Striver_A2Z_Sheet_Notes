# Implement Upper Bound

## Problem Statement

Given a **sorted array** `arr` of size `N` and a value `x`, find the **upper bound** of `x`.

### What is Upper Bound?

The **upper bound** is the **first index** such that:

```text
arr[ind] > x
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
3
```

**Explanation**

The first index where the value is **strictly greater** than `2` is index `3`.

---

### Example 2

**Input**

```text
N = 6
arr = [3, 5, 8, 9, 15, 19]
x = 9
```

**Output**

```text
4
```

**Explanation**

The first element strictly greater than `9` is `15`, which is at index `4`.

---

## Core Idea

Since the array is sorted, we can use **binary search**.

We are looking for the **first element greater than `x`**.

So this is very similar to **lower bound**, except the condition changes from:

```text
arr[mid] >= x
```

to

```text
arr[mid] > x
```

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class to find the upper bound index in an array
class UpperBoundFinder {
public:
    // Linear search method to find upper bound
    int upperBound(vector<int> &arr, int x, int n) {
        for (int i = 0; i < n; i++) {
            if (arr[i] > x) {
                return i; // First element strictly greater than x
            }
        }
        return n; // If no such element exists, return n
    }
};
```

---

## How It Works

- Traverse the array from left to right.
- The first element that is strictly greater than `x` is the upper bound.
- If no such element exists, return `n`.

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

// Class to compute upper bound
class UpperBoundFinder {
public:
    // Function to find the upper bound using binary search
    int upperBound(vector<int> &arr, int x, int n) {
        int low = 0, high = n - 1;
        int ans = n;  // Default answer if x is >= all elements

        while (low <= high) {
            int mid = (low + high) / 2;

            if (arr[mid] > x) {
                ans = mid;        // Potential answer found
                high = mid - 1;   // Try to find smaller valid index on the left
            } else {
                low = mid + 1;    // Move right if mid is <= x
            }
        }
        return ans;  // Index of the first element > x
    }
};
```

---

## Main Idea

We want the **first valid position** where:

```text
arr[mid] > x
```

If the middle element is greater than `x`:

- it can be a possible answer
- but there may be an even smaller valid index on the left

So we store it in `ans` and continue searching left.

If the middle element is less than or equal to `x`:

- the upper bound must be on the right side

---

## Why This Works

Because the array is sorted:

- all values on the left of a valid upper bound are `<= x`
- once we find a value `> x`, we still need to check if an earlier such value exists

So whenever a valid answer is found, we keep moving left.

---

## Visualization

Suppose:

```text
arr = [3, 5, 8, 9, 15, 19]
x = 9
```

We want the first index where value is **strictly greater** than `9`.

Array:

```text
Index:  0  1  2  3   4   5
Value:  3  5  8  9  15  19
```

Upper bound is index `4`, because `15 > 9`.

---

# Dry Run

## Input

```text
arr = [3, 5, 8, 9, 15, 19]
x = 9
```

Initial state:

```text
low = 0
high = 5
ans = 6
```

---

### Step 1

```text
mid = (0 + 5) / 2 = 2
arr[mid] = 8
```

Since:

```text
8 <= 9
```

move right:

```text
low = mid + 1 = 3
```

---

### Step 2

```text
low = 3
high = 5
mid = (3 + 5) / 2 = 4
arr[mid] = 15
```

Since:

```text
15 > 9
```

this is a possible answer.

Update:

```text
ans = 4
high = mid - 1 = 3
```

---

### Step 3

```text
low = 3
high = 3
mid = (3 + 3) / 2 = 3
arr[mid] = 9
```

Since:

```text
9 <= 9
```

move right:

```text
low = mid + 1 = 4
```

Now:

```text
low = 4
high = 3
```

Stop.

Final answer:

```text
4
```

---

# Pointer Movement Visualization

```text
arr = [3, 5, 8, 9, 15, 19]
       L     M        H

Step 1:
mid = 2 -> 8 <= 9 -> move right

arr = [3, 5, 8, 9, 15, 19]
             L     M  H

Step 2:
mid = 4 -> 15 > 9 -> possible answer
move left to find smaller valid index

Step 3:
mid = 3 -> 9 <= 9 -> move right

Final upper bound = 4
```

---

# Why `ans = n` Initially?

If no element is greater than `x`, return `n`.

Example:

```text
arr = [1, 2, 3]
x = 10
```

There is no element strictly greater than `10`.

So the answer should be:

```text
3
```

which is the array size.

---

# Why Move Left When `arr[mid] > x`?

Because upper bound means the **first** element that is strictly greater than `x`.

If `arr[mid]` already satisfies the condition, there may still be a smaller valid index to the left.

So we save `mid` and search left.

---

# Why Move Right When `arr[mid] <= x`?

Because values less than or equal to `x` cannot be the upper bound.

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

- Upper bound = first index where `arr[i] > x`
- If no such index exists, return `N`
- Brute force scans linearly
- Binary search finds the answer in logarithmic time
- When `arr[mid] > x`, store `mid` and search left
- When `arr[mid] <= x`, search right

---

# Revision Template

```text
1. Set low = 0, high = n - 1, ans = n
2. While low <= high
3. Find mid
4. If arr[mid] > x:
      ans = mid
      high = mid - 1
5. Else:
      low = mid + 1
6. Return ans
```

---

# Final Intuition

> Upper bound is the first position where the sorted array becomes strictly greater than the target, so binary search keeps moving left whenever a valid position is found.