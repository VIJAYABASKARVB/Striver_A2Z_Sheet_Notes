# Count Number of Nice Subarrays

## Problem Statement

Given an array `nums` and an integer `k`, count the number of **continuous subarrays** that contain **exactly `k` odd numbers**.

A subarray is called **nice** if it has exactly `k` odd numbers.

---

## Examples

### Example 1

**Input:** `nums = [1,1,2,1,1]`, `k = 3`
**Output:** `2`

**Explanation:**
The nice subarrays are:

* `[1,1,2,1]`
* `[1,2,1,1]`

### Example 2

**Input:** `nums = [2,4,6]`, `k = 1`
**Output:** `0`

### Example 3

**Input:** `nums = [2,2,2,1,2,2,1,2,2,2]`, `k = 2`
**Output:** `16`

---

## Core Idea

This is an **exactly k** problem.

The most useful trick is:

```text
exactly(k) = atMost(k) - atMost(k - 1)
```

Here:

* `atMost(k)` = number of subarrays with **at most `k` odd numbers**
* `atMost(k - 1)` = number of subarrays with **at most `k - 1` odd numbers**
* subtracting them gives subarrays with **exactly `k` odd numbers**

This is the key idea behind the optimal solution.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int count = 0;

        for (int start = 0; start < nums.size(); start++) {
            int oddCount = 0;

            for (int end = start; end < nums.size(); end++) {
                if (nums[end] % 2 != 0)
                    oddCount++;

                if (oddCount > k) break;

                if (oddCount == k)
                    count++;
            }
        }

        return count;
    }
};
```

## How It Works

* Fix a starting index `start`.
* Expand the subarray with `end`.
* Count how many odd numbers appear.
* If odd count exceeds `k`, stop expanding.
* If odd count becomes exactly `k`, count that subarray.

## Complexity

* **Time:** `O(n^2)`
* **Space:** `O(1)`

---

# 2) Optimal Approach — Sliding Window with `atMost`

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countAtMost(vector<int>& nums, int k) {
        int left = 0, res = 0;

        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] % 2 != 0)
                k--;

            while (k < 0) {
                if (nums[left] % 2 != 0)
                    k++;
                left++;
            }

            res += (right - left + 1);
        }

        return res;
    }

    int numberOfSubarrays(vector<int>& nums, int k) {
        return countAtMost(nums, k) - countAtMost(nums, k - 1);
    }
};
```

---

## What `countAtMost(k)` Means

It counts the number of subarrays that contain **at most `k` odd numbers**.

If the current window has too many odd numbers:

* move `left` forward
* remove elements from the window until it becomes valid again

---

## Why `res += (right - left + 1)`?

Once the window `[left ... right]` has at most `k` odd numbers, then:

* every subarray ending at `right`
* and starting anywhere from `left` to `right`

is also valid.

So the number of valid subarrays ending at `right` is:

```text
right - left + 1
```

---

## Visualization

```text
left                               right
|-----------------------------------|
current valid window
```

If this window has at most `k` odd numbers, then all smaller windows ending at `right` and starting within this range are also valid.

---

# Dry Run

## Example: `nums = [1,1,2,1,1]`, `k = 3`

We first compute `countAtMost(3)`.

| right | nums[right] | odd? | k after update |   left | Window      | res added |
| ----: | ----------: | ---- | -------------: | -----: | ----------- | --------: |
|     0 |           1 | yes  |              2 |      0 | `[1]`       |         1 |
|     1 |           1 | yes  |              1 |      0 | `[1,1]`     |         2 |
|     2 |           2 | no   |              1 |      0 | `[1,1,2]`   |         3 |
|     3 |           1 | yes  |              0 |      0 | `[1,1,2,1]` |         4 |
|     4 |           1 | yes  |             -1 | shrink | valid again |       ... |

At the end, `countAtMost(3)` counts all subarrays with at most 3 odd numbers.

Then compute `countAtMost(2)`.

Finally:

```text
exactly(3) = countAtMost(3) - countAtMost(2)
```

That leaves only the subarrays with exactly 3 odd numbers.

---

# Why This Works

Every subarray falls into one of these groups:

* at most `k - 1` odd numbers
* exactly `k` odd numbers
* more than `k` odd numbers

So:

```text
atMost(k) - atMost(k - 1) = exactly(k)
```

That is the full trick.

---

# Important Detail

In the helper function, `k` is used like a budget:

* each odd number spends 1 unit
* when the budget goes below 0, the window is invalid
* move `left` until the budget becomes valid again

This makes the code compact and efficient.

---

# Complexity

## Brute Force

* **Time:** `O(n^2)`
* **Space:** `O(1)`

## Optimal Approach

* **Time:** `O(n)`
* **Space:** `O(1)`

---

# Key Takeaways

* The problem asks for **exactly `k` odd numbers**.
* Convert it into two easier problems using:

```text
exactly(k) = atMost(k) - atMost(k - 1)
```

* Use a sliding window to count subarrays with at most `k` odd numbers.
* Add `right - left + 1` whenever the window is valid.

---

# Revision Template

```text
1. Convert nums into odd/even condition
2. Count subarrays with at most k odd numbers
3. Count subarrays with at most k - 1 odd numbers
4. Subtract the two counts
5. The result is the number of nice subarrays
```

---

# Final Intuition

**Count all subarrays with at most `k` odd numbers, subtract all subarrays with at most `k - 1` odd numbers, and what remains are the subarrays with exactly `k` odd numbers.**
