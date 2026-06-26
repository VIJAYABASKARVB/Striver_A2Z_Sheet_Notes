# 31. Next Permutation

## Problem Statement

A permutation of an array is an arrangement of its elements.

The **next permutation** is the next lexicographically greater arrangement of the array.

If no greater permutation exists, rearrange the array into the **smallest possible order**.

The transformation must be done **in-place** and with **constant extra space**.

---

## Examples

### Example 1
**Input:** `nums = [1,2,3]`  
**Output:** `[1,3,2]`

### Example 2
**Input:** `nums = [3,2,1]`  
**Output:** `[1,2,3]`

### Example 3
**Input:** `nums = [1,1,5]`  
**Output:** `[1,5,1]`

---

## Core Idea

We want to make the array just a little bigger in lexicographic order.

The key steps are:

1. Find the **first decreasing element from the right**
2. Find the **smallest element greater than it** on the right
3. Swap them
4. Reverse the suffix after that position

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextPermutation(vector<int>& nums) {
        vector<vector<int>> all;

        sort(nums.begin(), nums.end());
        do {
            all.push_back(nums);
        } while (next_permutation(nums.begin(), nums.end()));

        for (int i = 0; i < all.size(); i++) {
            if (all[i] == nums) {
                if (i == all.size() - 1)
                    return all[0];
                return all[i + 1];
            }
        }

        return nums;
    }
};
```

## How It Works

- Generate all permutations.
- Sort them in lexicographic order.
- Find the current one.
- Return the next one.

## Complexity

- **Time:** `O(n!)`
- **Space:** `O(n!)`

---

# 2) Optimal Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int index = -1;

        for (int i = nums.size() - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }

        for (int i = nums.size() - 1; i > index; i--) {
            if (nums[i] > nums[index]) {
                swap(nums[i], nums[index]);
                break;
            }
        }

        reverse(nums.begin() + index + 1, nums.end());
    }
};
```

---

## Main Idea

We scan from the right because the suffix on the right is usually the part that can be changed with the smallest increase.

We want the **first place from the right** where:

```text
nums[i] < nums[i + 1]
```

This position is called the **pivot**.

---

## Why This Pivot Matters

The suffix to the right of the pivot is in **descending order**.

That means:

- it is already the largest arrangement of that suffix
- to get the next permutation, we must change the pivot
- then make the suffix as small as possible

---

## Step-by-Step Logic

### Step 1: Find the pivot
Find the first index `index` from the right such that:

```text
nums[index] < nums[index + 1]
```

If no such index exists, the array is completely descending.

Example:

```text
[3,2,1]
```

This is already the last permutation.

So we reverse it to get the smallest one:

```text
[1,2,3]
```

---

### Step 2: Find the next larger element
From the right side of the pivot, find the first element greater than `nums[index]`.

Swap them.

This ensures we increase the permutation by the **smallest possible amount**.

---

### Step 3: Reverse the suffix
After swapping, the right part is still in descending order.

To make the permutation as small as possible after the swap, reverse the suffix.

That turns it into ascending order.

---

## Visualization

Suppose:

```text
nums = [1, 2, 3]
```

### Find pivot
From the right:

- `2 < 3` → pivot is at index `1`

So:

```text
[1, 2, 3]
     ^
```

### Find element just greater than `2`
That is `3`.

Swap:

```text
[1, 3, 2]
```

### Reverse suffix after pivot
Suffix is just `[2]`, so it stays the same.

Final answer:

```text
[1, 3, 2]
```

---

# Dry Run

## Example: `nums = [1,2,3]`

### Step 1: Find pivot
Check from right:

- `2 < 3` → pivot = `1`

### Step 2: Find next greater element
From the right, first number greater than `2` is `3`.

Swap:

```text
[1,3,2]
```

### Step 3: Reverse suffix
Suffix after pivot is `[2]`

Final result:

```text
[1,3,2]
```

---

## Example: `nums = [3,2,1]`

### Step 1: Find pivot
Check from right:

- `2 < 1` → no
- `3 < 2` → no

No pivot found.

So reverse the whole array:

```text
[1,2,3]
```

---

## Example: `nums = [1,1,5]`

### Step 1: Find pivot
From right:

- `1 < 5` → pivot = second index

### Step 2: Find next greater element
`5` is greater than `1`.

Swap:

```text
[1,5,1]
```

### Step 3: Reverse suffix
Suffix is `[1]`, so unchanged.

Final answer:

```text
[1,5,1]
```

---

# Why Reversing Works

After finding the pivot and swapping it with the next greater element, the suffix is still in descending order.

But we want the **smallest possible suffix** after the pivot to get the next lexicographic permutation.

So reversing the suffix gives ascending order, which is the smallest arrangement.

---

# Complexity

## Brute Force
- **Time:** `O(n!)`
- **Space:** `O(n!)`

## Optimal Approach
- **Time:** `O(n)`
- **Space:** `O(1)`

---

# Key Takeaways

- Scan from the right to find the pivot.
- Pivot is the first index where `nums[i] < nums[i+1]`.
- If no pivot exists, reverse the whole array.
- Swap pivot with the smallest greater element on the right.
- Reverse the suffix after the pivot.

---

# Revision Template

```text
1. Find the first decreasing element from the right
2. If none exists, reverse the whole array
3. Find the next greater element on the right
4. Swap pivot and next greater element
5. Reverse the suffix after the pivot
```

---

# Final Intuition

> Find the rightmost place where the array can still increase, make the smallest possible increase there, and then sort the tail into the smallest order.