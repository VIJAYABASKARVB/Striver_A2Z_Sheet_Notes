# Longest Consecutive Sequence in an Array

## Problem Statement

Given an integer array `nums`, return the length of the **longest sequence of consecutive integers**.

The integers in the sequence can appear in **any order** in the array.

---

## Examples

### Example 1

**Input**

```text
nums = [100, 4, 200, 1, 3, 2]
```

**Output**

```text
4
```

**Explanation**

The longest consecutive sequence is:

```text
[1, 2, 3, 4]
```

So the length is `4`.

---

### Example 2

**Input**

```text
nums = [0, 3, 7, 2, 5, 8, 4, 6, 0, 1]
```

**Output**

```text
9
```

**Explanation**

The longest consecutive sequence is:

```text
[0, 1, 2, 3, 4, 5, 6, 7, 8]
```

So the length is `9`.

---

# Core Idea

We need to find a group of numbers where each next number is exactly `+1` from the previous one.

Example:

```text
1, 2, 3, 4
```

This is a consecutive sequence.

The important part is that the elements do **not** need to be adjacent in the original array.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Helper function to perform linear search
    bool linearSearch(vector<int>& a, int num) {
        int n = a.size(); 
        for (int i = 0; i < n; i++) {
            if (a[i] == num)
                return true;
        }
        return false;
    }

public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }

        int n = nums.size();
        int longest = 1; 

        for (int i = 0; i < n; i++) {
            int x = nums[i]; 
            int cnt = 1; 

            while (linearSearch(nums, x + 1) == true) {
                x += 1; 
                cnt += 1; 
            }

            longest = max(longest, cnt);
        }

        return longest;
    }
};
```

---

## How It Works

- For every element, treat it as a possible starting point.
- Check whether `x + 1` exists.
- If yes, continue the sequence.
- Count how long the sequence becomes.
- Keep the maximum length.

---

## Why It Works

For each number, we try to extend a consecutive chain as far as possible.

Example:

```text
nums = [100, 4, 200, 1, 3, 2]
```

Starting from `1`:

- `2` exists
- `3` exists
- `4` exists
- `5` does not exist

So the chain length is `4`.

---

## Complexity

- **Time:** `O(n^2)`
- **Space:** `O(1)`

---

# 2) Optimal Approach — Hash Set

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& a) {
        int n = a.size();
        if (n == 0) return 0; 
    
        int longest = 1; 
        unordered_set<int> st;
    
        for (int i = 0; i < n; i++) {
            st.insert(a[i]);
        }
    
        for (auto it : st) {
            if (st.find(it - 1) == st.end()) {
                int cnt = 1; 
                int x = it; 
    
                while (st.find(x + 1) != st.end()) {
                    x = x + 1; 
                    cnt = cnt + 1;
                }

                longest = max(longest, cnt);
            }
        }

        return longest;
    }
};
```

---

## Main Idea

Use a hash set to check whether a number exists in **O(1)** average time.

Then only start counting from numbers that are the **beginning of a sequence**.

A number `it` is a starting number if:

```text
it - 1 is not present in the set
```

---

## Why Start Only From Sequence Beginnings?

Suppose the sequence is:

```text
1, 2, 3, 4
```

If we start from `2`, we would count:

```text
2, 3, 4
```

If we start from `3`, we would count:

```text
3, 4
```

That repeats work.

So we only start from `1`, because `1` has no previous consecutive number.

This avoids unnecessary computation.

---

## Visualization

For:

```text
[100, 4, 200, 1, 3, 2]
```

The set becomes:

```text
{100, 4, 200, 1, 3, 2}
```

Now check each element:

- `100` → `99` not present → start of sequence
- `4` → `3` present → not a start
- `200` → `199` not present → start
- `1` → `0` not present → start
- `3` → `2` present → not a start
- `2` → `1` present → not a start

So only true starts are expanded.

---

# Dry Run

## Input

```text
nums = [100, 4, 200, 1, 3, 2]
```

Set:

```text
{100, 4, 200, 1, 3, 2}
```

### Start with `100`
- `99` not found → start
- `101` not found
- length = `1`

### Start with `4`
- `3` exists → not a start

### Start with `200`
- `199` not found → start
- `201` not found
- length = `1`

### Start with `1`
- `0` not found → start
- `2` found
- `3` found
- `4` found
- `5` not found
- length = `4`

Final answer:

```text
4
```

---

# Why the Optimal Solution is Better

The brute force version repeats searches many times.

The hash set version avoids repeating work by:
- checking existence in constant time
- counting only from valid starting points

This makes it much faster.

---

# Complexity

## Brute Force

- **Time:** `O(n^2)`
- **Space:** `O(1)`

## Optimal Approach

- **Time:** `O(n)`
- **Space:** `O(n)`

---

# Key Takeaways

- A consecutive sequence increases by exactly `1`.
- Use a set for fast lookups.
- Only start counting from numbers where `x - 1` is not present.
- This prevents duplicate work and gives linear time.

---

# Revision Template

```text
1. Insert all numbers into a hash set
2. For each number, check if it is a sequence starter
3. A number is a starter if (num - 1) is not in the set
4. From that number, count forward using num + 1
5. Keep the maximum length
```

---

# Final Intuition

> Do not start counting from every number. Start only from the beginning of each consecutive chain.