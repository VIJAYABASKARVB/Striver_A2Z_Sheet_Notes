# Max Consecutive Ones III

## Problem Statement

Given a binary array `nums` and an integer `k`, return the **maximum number of consecutive `1`s** in the array if you can flip **at most `k` zeros**.

---

## Examples

### Example 1

**Input:** `nums = [1,1,1,0,0,0,1,1,1,1,0]`, `k = 3`
**Output:** `10`

**Explanation:**
Flip the zeros at indices `3, 4, 5`.
The array becomes:

```text
[1,1,1,1,1,1,1,1,1,1,0]
```

So the longest consecutive block of `1`s is `10`.

### Example 2

**Input:** `nums = [0,0,1,1,1,0,1,1,1,0,0,0,0,1,1,1,1]`, `k = 3`
**Output:** `9`

---

## Core Idea

We need the **longest subarray** that contains **at most `k` zeros**.

Why? Because every zero in that window can be flipped into a `1`.
So the problem becomes:

> Find the largest window where `zero_count <= k`

This is a classic **sliding window** problem.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int maxLen = 0;

        for (int i = 0; i < nums.size(); i++) {
            int zeros = 0;

            for (int j = i; j < nums.size(); j++) {
                if (nums[j] == 0) {
                    zeros++;
                }

                if (zeros > k) {
                    break;
                }

                maxLen = max(maxLen, j - i + 1);
            }
        }

        return maxLen;
    }
};
```

## How It Works

* Fix a starting index `i`.
* Expand the subarray using `j`.
* Count how many zeros appear.
* If zeros exceed `k`, stop expanding.
* Track the maximum valid length.

## Why It Works

Every possible subarray start is checked, so no valid answer is missed.

## Complexity

* **Time:** `O(n^2)`
* **Space:** `O(1)`

---

# 2) Optimal Approach — Sliding Window

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0;
        int zerocount = 0;
        int maxlen = 0;

        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) {
                zerocount++;
            }

            if (zerocount > k) {
                if (nums[left] == 0) {
                    zerocount--;
                }
                left++;
            }

            maxlen = max(maxlen, right - left + 1);
        }

        return maxlen;
    }
};
```

## Main Observation

A window is valid only if it contains **at most `k` zeros**.

So we:

1. Expand the window by moving `right`
2. Count zeros
3. If zeros become more than `k`, shrink from the left
4. Update the answer with the current valid window length

---

## Window Visualization

```text
left                                 right
 |--------------------------------------|
 current window
```

* `right` grows the window
* `left` shrinks the window when needed
* `zerocount` tells us whether the window is valid

---

# Dry Run

## Dry Run for Example 1

`nums = [1,1,1,0,0,0,1,1,1,1,0]`, `k = 3`

We track:

* `left`
* `right`
* `zerocount`
* `window length`
* `maxlen`

| right | nums[right] | zerocount | left | Window                  | Valid? | maxlen |
| ----: | ----------: | --------: | ---: | ----------------------- | ------ | -----: |
|     0 |           1 |         0 |    0 | `[1]`                   | Yes    |      1 |
|     1 |           1 |         0 |    0 | `[1,1]`                 | Yes    |      2 |
|     2 |           1 |         0 |    0 | `[1,1,1]`               | Yes    |      3 |
|     3 |           0 |         1 |    0 | `[1,1,1,0]`             | Yes    |      4 |
|     4 |           0 |         2 |    0 | `[1,1,1,0,0]`           | Yes    |      5 |
|     5 |           0 |         3 |    0 | `[1,1,1,0,0,0]`         | Yes    |      6 |
|     6 |           1 |         3 |    0 | `[1,1,1,0,0,0,1]`       | Yes    |      7 |
|     7 |           1 |         3 |    0 | `[1,1,1,0,0,0,1,1]`     | Yes    |      8 |
|     8 |           1 |         3 |    0 | `[1,1,1,0,0,0,1,1,1]`   | Yes    |      9 |
|     9 |           1 |         3 |    0 | `[1,1,1,0,0,0,1,1,1,1]` | Yes    |     10 |
|    10 |           0 |         4 |    0 | too many zeros          | No     |     10 |

At `right = 10`, zero count becomes `4`, which is greater than `k = 3`.
So we shrink from the left in a proper sliding-window implementation.

---

# Important Note About the Given Optimal Code

The provided optimal code uses **only one shrink step**:

```cpp
if (zerocount > k) {
    if (nums[left] == 0) {
        zerocount--;
    }
    left++;
}
```

This works for many cases because the window is adjusted as the scan continues, but the **more standard and safer version** is to shrink using a `while` loop until the window becomes valid again.

### Standard version

```cpp
while (zerocount > k) {
    if (nums[left] == 0) zerocount--;
    left++;
}
```

This guarantees the window is valid before updating `maxlen`.

---

# Visual Understanding of Shrinking

Suppose the current window is:

```text
[1, 1, 0, 1, 0, 0]
```

If `k = 2`, this window has `3` zeros, so it is invalid.

We move `left` forward:

```text
Before: [1, 1, 0, 1, 0, 0]
After removing left part until zeros <= 2
```

The goal is to always keep a **legal window**.

---

# Why Sliding Window Works

* `right` only moves forward
* `left` only moves forward
* Each element is processed at most twice
* So the algorithm is efficient

This is exactly why it is much faster than brute force.

---

# Complexity

## Brute Force

* **Time:** `O(n^2)`
* **Space:** `O(1)`

## Sliding Window

* **Time:** `O(n)`
* **Space:** `O(1)`

---

# Key Takeaways

* Convert the problem into: **find the longest subarray with at most `k` zeros**
* A zero in the window can be flipped into a `1`
* Use two pointers to maintain a valid window
* Shrink the window whenever zero count becomes too large

---

# Revision Template

```text
1. Expand right pointer
2. Count zeros in the window
3. If zeros > k, move left pointer forward
4. Update answer with current valid window length
```

---

# Final One-Line Intuition

**Keep a window containing at most `k` zeros, because those zeros are the only ones you are allowed to flip.**
