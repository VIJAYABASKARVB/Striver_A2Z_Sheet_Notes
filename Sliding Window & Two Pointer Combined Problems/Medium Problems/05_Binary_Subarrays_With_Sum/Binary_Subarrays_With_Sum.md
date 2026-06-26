# Binary Subarrays With Sum

## Problem Statement

Given a **binary array** `nums` and an integer `goal`, return the number of **non-empty subarrays** whose sum is exactly `goal`.

A subarray is a **contiguous** part of the array.

---

## Examples

### Example 1

**Input:** `nums = [1,0,1,0,1]`, `goal = 2`
**Output:** `4`

### Example 2

**Input:** `nums = [0,0,0,0,0]`, `goal = 0`
**Output:** `15`

---

## Core Idea

This problem asks for the number of subarrays with **sum exactly equal to `goal`**.

A very useful trick is:

```text
exactly(goal) = atMost(goal) - atMost(goal - 1)
```

Why this works:

* `atMost(goal)` counts all subarrays with sum `<= goal`
* `atMost(goal - 1)` counts all subarrays with sum `<= goal - 1`
* subtracting them leaves only subarrays with sum **exactly `goal`**

This is the main idea behind the optimal solution.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int count = 0;

        for (int start = 0; start < nums.size(); ++start) {
            int sum = 0;

            for (int end = start; end < nums.size(); ++end) {
                sum += nums[end];

                if (sum == goal) {
                    count++;
                }
            }
        }

        return count;
    }
};
```

## How It Works

* Fix a starting index `start`.
* Expand the subarray using `end`.
* Keep adding values to `sum`.
* If `sum == goal`, increment the answer.

## Complexity

* **Time:** `O(n^2)`
* **Space:** `O(1)`

---

# 2) Optimal Approach — `atMost` Trick

## Code

```cpp
class Solution {
public:
    int atMost(vector<int>& nums, int goal) {
        if (goal < 0) {
            return 0;
        }

        int left = 0;
        int sum = 0;
        int ans = 0;

        for (int right = 0; right < nums.size(); right++) {
            sum += nums[right];

            while (sum > goal) {
                sum -= nums[left];
                left++;
            }

            ans += right - left + 1;
        }

        return ans;
    }

    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return atMost(nums, goal) - atMost(nums, goal - 1);
    }
};
```

---

## What `atMost(goal)` Means

`atMost(goal)` counts the number of subarrays whose sum is **less than or equal to** `goal`.

Since the array is binary:

* adding an element increases the sum by either `0` or `1`
* so a sliding window can maintain the sum efficiently

---

## Why `ans += right - left + 1`?

Once the window `[left ... right]` has sum `<= goal`, then **every subarray ending at `right` and starting anywhere from `left` to `right` is valid**.

So the number of valid subarrays ending at `right` is:

```text
right - left + 1
```

---

## Visual Intuition

```text
left                               right
|-----------------------------------|
current window with sum <= goal
```

If this window is valid, then all these subarrays are also valid:

```text
[right]
[left ... right]
[left+1 ... right]
...
```

That is why we add `right - left + 1`.

---

# Dry Run of `atMost`

## Example: `nums = [1,0,1,0,1]`, `goal = 2`

We compute `atMost(2)`.

| right | nums[right] | sum |  left | Window                | Valid? | ans added |
| ----: | ----------: | --: | ----: | --------------------- | ------ | --------: |
|     0 |           1 |   1 |     0 | `[1]`                 | Yes    |         1 |
|     1 |           0 |   1 |     0 | `[1,0]`               | Yes    |         2 |
|     2 |           1 |   2 |     0 | `[1,0,1]`             | Yes    |         3 |
|     3 |           0 |   2 |     0 | `[1,0,1,0]`           | Yes    |         4 |
|     4 |           1 |   3 | 0 → 1 | shrink until sum <= 2 | Yes    |         4 |

So:

```text
atMost(2) = 14
```

Now compute `atMost(1)`.

```text
atMost(1) = 10
```

Then:

```text
exactly(2) = 14 - 10 = 4
```

Which matches the expected answer.

---

# Why the Subtraction Trick Works

Any subarray belongs to one of these two groups:

* sum `<= goal - 1`
* sum exactly `goal`
* sum `> goal`

So if we count all subarrays with sum `<= goal` and remove those with sum `<= goal - 1`, only the exact `goal` subarrays remain.

That is the entire idea.

---

# Important Special Case

## When `goal = 0`

We call:

```text
atMost(0) - atMost(-1)
```

Since `atMost(-1)` is impossible, the function returns `0` immediately.

This makes the formula work cleanly even for `goal = 0`.

---

# Why Sliding Window Works Here

This works because the array is binary:

* elements are only `0` or `1`
* the window sum changes in a controlled way
* when sum becomes too large, moving `left` forward can reduce it

This is much easier than the general subarray sum problem on arbitrary integers.

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

* The problem asks for **exactly goal**.
* Convert it into two easier counting problems using:

```text
exactly(goal) = atMost(goal) - atMost(goal - 1)
```

* Use a sliding window to count subarrays with sum at most `goal`.
* For each `right`, add `right - left + 1` to the answer.

---

# Revision Template

```text
1. Find count of subarrays with sum <= goal
2. Find count of subarrays with sum <= goal - 1
3. Subtract them
4. Use sliding window in atMost()
5. Add right - left + 1 for each valid window
```

---

# Final Intuition

**Count all subarrays with sum at most `goal`, then remove all subarrays with sum at most `goal - 1`; what remains is the number of subarrays with sum exactly `goal`.**
