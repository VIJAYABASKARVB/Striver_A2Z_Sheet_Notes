# Kadane's Algorithm: Maximum Subarray Sum

## Problem Statement

Given an integer array `nums`, find the **contiguous non-empty subarray** with the **largest sum**, and return that sum.

A subarray must be **continuous**.

---

## Examples

### Example 1

**Input:** `nums = [2, 3, 5, -2, 7, -4]`
**Output:** `15`

**Explanation:**
The subarray `[2, 3, 5, -2, 7]` has the largest sum:

```text
2 + 3 + 5 - 2 + 7 = 15
```

### Example 2

**Input:** `nums = [-2, -3, -7, -2, -10, -4]`
**Output:** `-2`

**Explanation:**
All numbers are negative, so the best answer is the **least negative** number.

---

## Core Idea

We want the maximum sum over all contiguous subarrays.

Two approaches:

1. **Brute force** — compute every subarray sum.
2. **Kadane's algorithm** — keep a running sum and reset it when it becomes harmful.

---

# 1) Brute Force Approach

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxi = INT_MIN;

        for (int i = 0; i < nums.size(); i++) {
            for (int j = i; j < nums.size(); j++) {
                int sum = 0;
                for (int k = i; k <= j; k++) {
                    sum += nums[k];
                }
                maxi = max(maxi, sum);
            }
        }

        return maxi;
    }
};
```

## How It Works

* Fix a starting index `i`.
* Fix an ending index `j`.
* Compute the sum of subarray `nums[i...j]`.
* Update the maximum sum found so far.

## Complexity

* **Time:** `O(n^3)`
* **Space:** `O(1)`

---

# 2) Optimal Approach — Kadane's Algorithm

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        long long maxi = LLONG_MIN;
        long long sum = 0;

        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];

            if (sum > maxi) {
                maxi = sum;
            }

            if (sum < 0) {
                sum = 0;
            }
        }

        return maxi;
    }
};
```

---

## Main Intuition

A **negative running sum** is useless for the future.

Why?
Because if the current sum is negative, adding it to the next numbers will only make the next subarray worse.

So:

* keep adding elements to `sum`
* if `sum` becomes negative, reset it to `0`

This means:

> Start a new subarray from the next element

---

## What `sum` Represents

`sum` is the **current subarray sum ending at the current index**.

At every index:

* either continue the current subarray
* or discard it if it becomes negative

---

## Why Reset to 0?

Suppose the current running sum is:

```text
sum = -5
```

and the next number is:

```text
3
```

If we keep the negative sum:

```text
-5 + 3 = -2
```

If we restart fresh:

```text
3
```

Clearly, restarting is better.
That is why Kadane resets the sum when it goes below 0.

---

# Dry Run

## Example: `nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`

We track:

* `sum` = current running sum
* `maxi` = best answer so far

| i | nums[i] | sum after add | maxi | action         |
| - | ------: | ------------: | ---: | -------------- |
| 0 |      -2 |            -2 |   -2 | reset sum to 0 |
| 1 |       1 |             1 |    1 | keep           |
| 2 |      -3 |            -2 |    1 | reset sum to 0 |
| 3 |       4 |             4 |    4 | keep           |
| 4 |      -1 |             3 |    4 | keep           |
| 5 |       2 |             5 |    5 | keep           |
| 6 |       1 |             6 |    6 | keep           |
| 7 |      -5 |             1 |    6 | keep           |
| 8 |       4 |             5 |    6 | keep           |

### Final Answer

`maxi = 6`

The best subarray is:

```text
[4, -1, 2, 1]
```

---

# Special Case: All Negative Numbers

Example:

```text
[-2, -3, -7, -2, -10, -4]
```

If we always reset negative sums to 0, we must still make sure the answer is correct.

That is why `maxi` is updated **before** resetting `sum`.

So even when all numbers are negative:

* `maxi` records the largest single value
* the answer becomes the least negative number

Example answer:

```text
-2
```

---

# Why the Optimal Solution Works

Kadane's algorithm is based on this observation:

* A subarray with a negative prefix is never better than starting fresh after that prefix.
* So whenever the running sum becomes negative, drop it.
* Keep the best sum seen so far.

This gives a linear-time solution.

---

# Complexity

## Brute Force

* **Time:** `O(n^3)`
* **Space:** `O(1)`

## Kadane's Algorithm

* **Time:** `O(n)`
* **Space:** `O(1)`

---

# Key Takeaways

* The problem asks for the maximum sum of a contiguous subarray.
* Brute force checks every subarray.
* Kadane keeps a running sum and resets it when it becomes negative.
* The answer is the maximum value seen while scanning once.

---

# Revision Template

```text
1. Keep a running sum
2. Add the current element
3. Update the global maximum
4. If running sum becomes negative, reset it to 0
```

---

# Final Intuition

**If the current subarray is hurting future sums, discard it and start fresh from the next element.**
