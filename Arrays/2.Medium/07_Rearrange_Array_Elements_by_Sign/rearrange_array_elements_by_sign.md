# Rearrange Array Elements by Sign

## Problem Statement

You are given an array `A` of size `N` containing an equal number of positive and negative elements.

Rearrange the array so that positive and negative numbers appear alternately, **without changing the relative order** of the positive numbers among themselves or the negative numbers among themselves.

---

## Examples

### Example 1

**Input**

```text
arr[] = {1, 2, -4, -5}, N = 4
```

**Output**

```text
1 -4 2 -5
```

**Explanation**

- Positive elements: `1, 2`
- Negative elements: `-4, -5`

To preserve relative order:

- `1` must come before `2`
- `-4` must come before `-5`

So the rearranged array is:

```text
1 -4 2 -5
```

---

### Example 2

**Input**

```text
arr[] = {1, 2, -3, -1, -2, -3}, N = 6
```

**Output**

```text
1 -3 2 -1 3 -2
```

---

# Core Idea

We need to place:

- positive numbers at even indices
- negative numbers at odd indices

while keeping the original order of both groups.

This is a **stable rearrangement** problem.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class to encapsulate array operations
class ArrayManipulator {
public:
    // Function to rearrange elements so that positives and negatives alternate
    vector<int> RearrangeBySign(vector<int>& A, int n) {
        vector<int> pos; // Vector to store positive numbers
        vector<int> neg; // Vector to store negative numbers

        // Step 1: Separate positives and negatives
        for (int i = 0; i < n; i++) {
            if (A[i] > 0)
                pos.push_back(A[i]);
            else
                neg.push_back(A[i]);
        }

        // Step 2: Place positives at even indices and negatives at odd indices
        for (int i = 0; i < n / 2; i++) {
            A[2 * i] = pos[i];
            A[2 * i + 1] = neg[i];
        }

        return A;
    }
};
```

## How It Works

- First collect all positive numbers in one array.
- Collect all negative numbers in another array.
- Then rebuild the original array by placing:
  - positive at index `0, 2, 4, ...`
  - negative at index `1, 3, 5, ...`

## Why It Preserves Order

Because we push elements into `pos` and `neg` in the same order they appear in the input.

So relative order stays unchanged.

## Complexity

- **Time:** `O(N)`
- **Space:** `O(N)`

---

# 2) Optimal Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Define a class to handle array manipulation
class ArrayManipulator {
public:
    // Function to rearrange elements by alternating sign
    vector<int> rearrangeBySign(vector<int>& A) {
        int n = A.size();

        // Create a result array of size n initialized with 0
        vector<int> ans(n, 0);

        // posIndex will store index for next positive number (even index)
        // negIndex will store index for next negative number (odd index)
        int posIndex = 0, negIndex = 1;

        // Loop through the original array
        for (int i = 0; i < n; i++) {
            if (A[i] < 0) {
                // Place negative numbers at odd indices
                ans[negIndex] = A[i];
                negIndex += 2;
            } else {
                // Place positive numbers at even indices
                ans[posIndex] = A[i];
                posIndex += 2;
            }
        }

        return ans;
    }
};
```

---

## Main Idea

We create a new array `ans` and fill it in one pass.

- `posIndex = 0` → next positive goes to even index
- `negIndex = 1` → next negative goes to odd index

As we scan the original array:

- if element is positive, place it at `posIndex`
- if element is negative, place it at `negIndex`

Then move that pointer by `2`.

---

## Why This Works

This approach automatically preserves order because:

- positives are inserted in the order they appear
- negatives are inserted in the order they appear

So it is stable.

---

## Visualization

Suppose:

```text
A = [1, 2, -4, -5]
```

We build:

```text
ans = [_, _, _, _]
```

### Step 1
`1` is positive → put at index `0`

```text
ans = [1, _, _, _]
```

### Step 2
`2` is positive → put at index `2`

```text
ans = [1, _, 2, _]
```

### Step 3
`-4` is negative → put at index `1`

```text
ans = [1, -4, 2, _]
```

### Step 4
`-5` is negative → put at index `3`

```text
ans = [1, -4, 2, -5]
```

Final answer:

```text
1 -4 2 -5
```

---

# Dry Run

## Input

```text
A = [1, 2, -4, -5]
```

Initial state:

```text
ans = [0, 0, 0, 0]
posIndex = 0
negIndex = 1
```

| i | A[i] | Type | Action | ans | posIndex | negIndex |
|---|-----:|------|--------|-----|---------:|---------:|
| 0 | 1 | positive | ans[0] = 1 | [1, 0, 0, 0] | 2 | 1 |
| 1 | 2 | positive | ans[2] = 2 | [1, 0, 2, 0] | 4 | 1 |
| 2 | -4 | negative | ans[1] = -4 | [1, -4, 2, 0] | 4 | 3 |
| 3 | -5 | negative | ans[3] = -5 | [1, -4, 2, -5] | 4 | 5 |

Final answer:

```text
[1, -4, 2, -5]
```

---

# Complexity Analysis

## Brute Force

- **Time:** `O(N)`
- **Space:** `O(N)`

## Optimal Approach

- **Time:** `O(N)`
- **Space:** `O(N)`

---

# Key Takeaways

- Positive numbers go to even indices.
- Negative numbers go to odd indices.
- Maintain order by scanning the original array once.
- The optimal approach is simple, clean, and stable.

---

# Revision Template

```text
1. Create result array of size n
2. Keep two pointers:
   - posIndex = 0
   - negIndex = 1
3. Traverse the original array
4. If number is positive, place it at posIndex and move posIndex by 2
5. If number is negative, place it at negIndex and move negIndex by 2
6. Return the result array
```

---

# Final Intuition

> Keep positives in even positions and negatives in odd positions, while inserting them in the same order they appear in the original array.