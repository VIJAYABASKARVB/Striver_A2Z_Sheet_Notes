# Print the Maximum Sum Subarray (Kadane's Algorithm Follow-up)

## Problem Statement

Given an integer array `nums`, print the **contiguous subarray** that has the **maximum sum**.

This is a follow-up to **Kadane's Algorithm**. Along with finding the maximum sum, we also need to keep track of the **starting** and **ending** indices of the optimal subarray.

---

## Example

### Example 1

**Input**

```text
nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
```

**Output**

```text
Maximum Sum = 6

Subarray = [4, -1, 2, 1]
```

**Explanation**

```text
4 + (-1) + 2 + 1 = 6
```

No other contiguous subarray has a larger sum.

---

## Core Idea

Kadane's Algorithm already tells us the **maximum sum**.

To print the subarray, we only need to remember **where the current subarray starts** and **where the best subarray starts and ends**.

We introduce three additional variables:

```text
start     → Starting index of the current candidate subarray

ansStart  → Starting index of the maximum sum subarray

ansEnd    → Ending index of the maximum sum subarray
```

---

# Optimal Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find maximum sum of subarrays and print the subarray
    int maxSubArray(vector<int>& nums) {

        // Maximum subarray sum
        long long maxi = LLONG_MIN;

        // Current running sum
        long long sum = 0;

        // Temporary starting index
        int start = 0;

        // Final answer indices
        int ansStart = -1, ansEnd = -1;

        for (int i = 0; i < nums.size(); i++) {

            // If starting a new subarray
            if (sum == 0) {
                start = i;
            }

            sum += nums[i];

            // Better subarray found
            if (sum > maxi) {
                maxi = sum;
                ansStart = start;
                ansEnd = i;
            }

            // Current subarray is harmful
            if (sum < 0) {
                sum = 0;
            }
        }

        cout << "Maximum Sum Subarray: [ ";
        for (int i = ansStart; i <= ansEnd; i++) {
            cout << nums[i] << " ";
        }
        cout << "]" << endl;

        return maxi;
    }
};
```

---

# Additional Variables

| Variable | Purpose |
|----------|---------|
| `sum` | Running sum of current subarray |
| `maxi` | Maximum sum found so far |
| `start` | Starting index of current candidate subarray |
| `ansStart` | Starting index of best subarray |
| `ansEnd` | Ending index of best subarray |

---

# How the Algorithm Works

For every element:

1. If the running sum is `0`, this element becomes the beginning of a new candidate subarray.
2. Add the current element to the running sum.
3. If the running sum is larger than the best sum seen so far:
   - Update `maxi`
   - Save the current start and end indices.
4. If the running sum becomes negative, discard it by resetting it to `0`.

---

# Why `start` is Updated When `sum == 0`

Suppose the running sum became negative earlier.

Example:

```text
Current Sum = -8
```

A negative sum will never help future subarrays.

So Kadane resets it:

```text
sum = 0
```

Now the next element becomes the potential beginning of a new subarray.

```cpp
if (sum == 0)
    start = i;
```

This remembers where the new subarray begins.

---

# Dry Run

## Input

```text
nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
```

### Initial State

```text
sum = 0
maxi = -∞

start = 0

ansStart = -1
ansEnd = -1
```

| i | nums[i] | sum | maxi | start | ansStart | ansEnd | Action |
|---|---------:|----:|-----:|------:|---------:|-------:|--------|
| 0 | -2 | -2 | -2 | 0 | 0 | 0 | Reset sum |
| 1 | 1 | 1 | 1 | 1 | 1 | 1 | New best |
| 2 | -3 | -2 | 1 | 1 | 1 | 1 | Reset sum |
| 3 | 4 | 4 | 4 | 3 | 3 | 3 | New best |
| 4 | -1 | 3 | 4 | 3 | 3 | 3 | Continue |
| 5 | 2 | 5 | 5 | 3 | 3 | 5 | New best |
| 6 | 1 | 6 | 6 | 3 | 3 | 6 | New best |
| 7 | -5 | 1 | 6 | 3 | 3 | 6 | Continue |
| 8 | 4 | 5 | 6 | 3 | 3 | 6 | Continue |

---

## Final Answer

```text
Maximum Sum = 6

Indices

ansStart = 3
ansEnd = 6
```

Subarray:

```text
[4, -1, 2, 1]
```

---

# Visualization

```text
Index

0   1   2   3   4   5   6   7   8
│   │   │   │   │   │   │   │   │
-2  1  -3   4  -1   2   1  -5   4
            └──────────────┘
           Maximum Sum Subarray
```

---

# Why This Works

The same idea behind Kadane's Algorithm still applies:

- A negative running sum cannot improve any future subarray.
- Whenever we find a better sum, we simply remember **where it started** and **where it ended**.
- At the end of the traversal, those indices represent the maximum-sum subarray.

---

# Complexity

| Approach | Time | Space |
|----------|------|-------|
| Kadane + Indices | **O(n)** | **O(1)** |

---

# Revision Template

```text
1. Keep a running sum.

2. If sum == 0,
      start = current index.

3. Add current element.

4. If current sum > maximum sum,
      save:
      ansStart = start
      ansEnd = current index

5. If running sum becomes negative,
      reset it to 0.

6. Print nums[ansStart ... ansEnd].
```

---

# Key Takeaways

- Kadane's Algorithm can be extended to print the actual subarray.
- Track the **temporary start** of the current subarray.
- Whenever a new maximum is found, save the current boundaries.
- The algorithm still runs in **O(n)** time and **O(1)** extra space.

---

# One-Line Intuition

> **Kadane's Algorithm finds the maximum sum; by remembering where each candidate subarray starts and where the best one ends, we can print the maximum-sum subarray without increasing the time complexity.**