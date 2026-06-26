# Leaders in an Array

## Problem Statement

An element in an array is called a **leader** if it is greater than all the elements to its right.

The **rightmost element** is always a leader because there is nothing to its right.

---

## Examples

### Example 1

**Input**

```text
arr = [4, 7, 1, 0]
```

**Output**

```text
7 1 0
```

**Explanation**

- `0` is always a leader.
- `1` is greater than `0`.
- `7` is greater than `1` and `0`.
- `4` is not a leader because `7` is greater than it.

---

### Example 2

**Input**

```text
arr = [10, 22, 12, 3, 0, 6]
```

**Output**

```text
22 12 6
```

**Explanation**

- `6` is a leader because nothing is to its right.
- `12` is greater than `3, 0, 6`.
- `22` is greater than everything to its right.

---

# Core Idea

A leader must be greater than every element on its right.

So instead of checking from left to right, we can scan from **right to left** and keep track of the **maximum value seen so far**.

If the current element is greater than this maximum, it is a leader.

---

# 1) Brute Force Approach

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find leaders in an array.
    vector<int> leaders(vector<int>& nums) {
        vector<int> ans;

        // Iterate through each element in nums
        for (int i = 0; i < nums.size(); i++) {
            bool leader = true;

            /* Check whether nums[i] is greater
            than all elements to its right*/
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] >= nums[i]) {
                    /* If any element to the right is greater 
                    or equal, nums[i] is not a leader*/
                    leader = false;
                    break;
                }
            }

            // If nums[i] is a leader, add it to the ans vector
            if (leader) {
                ans.push_back(nums[i]);
            }
        }

       //Return the leaders 
        return ans;
    }
};
```

## How It Works

- For every element, check all elements to its right.
- If any right-side element is greater than or equal to it, it is not a leader.
- Otherwise, it is a leader.

## Complexity

- **Time:** `O(n^2)`
- **Space:** `O(1)` excluding the output array

---

# 2) Optimal Approach

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    //Function to find the leaders in an array.
    vector<int> leaders(vector<int>& nums) {
        vector<int> ans;
        
        if(nums.empty()) {
            return ans;
        }
        
        // Last element of the vector is always a leader
        int max = nums[nums.size() - 1];
        ans.push_back(nums[nums.size() - 1]);
        
        // Check elements from right to left
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] > max) {
                ans.push_back(nums[i]);
                max = nums[i];
            }
        }
        
        /* Reverse the vector to match
        the required output order*/
        reverse(ans.begin(), ans.end());
        
        //Return the leaders
        return ans;
    }
};
```

---

## Main Idea

Start from the **rightmost element**.

Keep a variable `max` that stores the greatest element seen so far from the right.

For each element moving left:

- if `nums[i] > max`, it is a leader
- update `max`

Since we scan from right to left, the leaders are collected in reverse order, so we reverse the answer at the end.

---

## Why This Works

If an element is greater than everything to its right, then it must be a leader.

When scanning from right to left:

- the first element we see is always a leader
- every new leader must be greater than the current maximum on the right

This gives us a linear-time solution.

---

## Visualization

For:

```text
[10, 22, 12, 3, 0, 6]
```

Scan from right to left:

- `6` → leader
- `0` → not a leader because `0 < 6`
- `3` → not a leader because `3 < 6`
- `12` → leader because `12 > 6`
- `22` → leader because `22 > 12`
- `10` → not a leader

Collected leaders:

```text
[6, 12, 22]
```

Reverse it:

```text
[22, 12, 6]
```

---

# Dry Run

## Input

```text
nums = [10, 22, 12, 3, 0, 6]
```

Initial state:

```text
max = 6
ans = [6]
```

| i | nums[i] | max | Action | ans |
|---|--------:|----:|--------|-----|
| 4 | 0 | 6 | not leader | [6] |
| 3 | 3 | 6 | not leader | [6] |
| 2 | 12 | 6 | leader → push | [6, 12] |
| 1 | 22 | 12 | leader → push | [6, 12, 22] |
| 0 | 10 | 22 | not leader | [6, 12, 22] |

Reverse:

```text
[22, 12, 6]
```

---

# Complexity Analysis

## Brute Force

- **Time:** `O(n^2)`
- **Space:** `O(1)`

## Optimal Approach

- **Time:** `O(n)`
- **Space:** `O(1)`

---

# Key Takeaways

- A leader is greater than all elements to its right.
- The last element is always a leader.
- Scan from right to left.
- Track the maximum seen so far.
- Reverse the result at the end.

---

# Revision Template

```text
1. Start from the last element
2. Keep track of the maximum element seen so far
3. If current element > maximum, it is a leader
4. Add it to the answer
5. Reverse the answer at the end
```

---

# Final Intuition

> A leader is simply an element that is stronger than everything to its right, so the cleanest way is to scan from the right and keep the best value seen so far.