# Longest Substring Without Repeating Characters

## Problem Summary

Given a string `s`, find the **length of the longest substring** that contains **no repeated characters**.

A **substring** is a **contiguous** part of a string.

---

## Examples

### Example 1

**Input:** `s = "zxyzxyz"`
**Output:** `3`
**Reason:** The substring `"xyz"` has all unique characters and is the longest such substring.

### Example 2

**Input:** `s = "xxxx"`
**Output:** `1`
**Reason:** Every valid substring can only contain one `x`.

---

## Key Idea

We need the **longest window** with **all distinct characters**.

Two approaches:

1. **Brute Force** — try every starting point and expand until a duplicate appears.
2. **Optimal Sliding Window** — maintain a window of unique characters and move pointers efficiently.

---

# 1) Brute Force Solution

## Python Code

```python
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        res = 0
        for i in range(len(s)):
            charSet = set()
            for j in range(i, len(s)):
                if s[j] in charSet:
                    break
                charSet.add(s[j])
            res = max(res, len(charSet))
        return res
```

## How It Works

* Fix a starting index `i`.
* Expand to the right using `j`.
* Keep a `set` of characters seen in the current substring.
* If a character repeats, stop expanding for that start.
* Track the maximum length found.

## Time and Space Complexity

* **Time:** `O(n^2)`
* **Space:** `O(n)` for the set in the worst case

## Why It Works

For every possible substring start, we greedily extend until repetition breaks the validity.

---

# 2) Optimal Solution — Sliding Window

## C++ Code

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> mp;
        int l = 0, res = 0;

        for (int r = 0; r < s.size(); r++) {
            if (mp.find(s[r]) != mp.end()) {
                l = max(mp[s[r]] + 1, l);
            }
            mp[s[r]] = r;
            res = max(res, r - l + 1);
        }
        return res;
    }
};
```

## Core Idea

Use a **sliding window** `[l ... r]` such that the substring inside it always has **unique characters**.

### What the map stores

`mp[ch] = last index where character ch appeared`

### Why `l = max(mp[s[r]] + 1, l)`?

This prevents the left pointer from moving **backward**.

* If the repeated character was inside the current window, move `l` right past its previous position.
* If the repeated character was seen earlier outside the current window, do nothing.

---

## Visual Intuition

Think of the window as a box:

```text
l                                      r
|--------------------------------------|
current substring with unique chars
```

When a duplicate appears:

* shrink the left side until the duplicate is removed
* continue expanding from the right

---

# Dry Run

## Dry Run for `s = "zxyzxyz"`

We track:

* `l` = left pointer
* `r` = right pointer
* `mp` = last seen index of each character
* `res` = answer so far

| r | s[r] | Seen Before? | Action on l           | Window After Update | res |
| - | ---- | ------------ | --------------------- | ------------------- | --- |
| 0 | z    | No           | `l = 0`               | `z`                 | 1   |
| 1 | x    | No           | `l = 0`               | `zx`                | 2   |
| 2 | y    | No           | `l = 0`               | `zxy`               | 3   |
| 3 | z    | Yes, at 0    | `l = max(0+1, 0) = 1` | `xyz`               | 3   |
| 4 | x    | Yes, at 1    | `l = max(1+1, 1) = 2` | `yzx`               | 3   |
| 5 | y    | Yes, at 2    | `l = max(2+1, 2) = 3` | `zxy`               | 3   |
| 6 | z    | Yes, at 3    | `l = max(3+1, 3) = 4` | `xyz`               | 3   |

### Final Answer

`res = 3`

---

## Dry Run for `s = "xxxx"`

| r | s[r] | Seen Before? | Action on l | Window | res |
| - | ---- | ------------ | ----------- | ------ | --- |
| 0 | x    | No           | `l = 0`     | `x`    | 1   |
| 1 | x    | Yes, at 0    | `l = 1`     | `x`    | 1   |
| 2 | x    | Yes, at 1    | `l = 2`     | `x`    | 1   |
| 3 | x    | Yes, at 2    | `l = 3`     | `x`    | 1   |

### Final Answer

`res = 1`

---

# Step-by-Step Visualization of the Optimal Approach

## Example: `s = "abcabcbb"`

### Step 1

```text
Window: a
```

### Step 2

```text
Window: ab
```

### Step 3

```text
Window: abc
```

### Step 4 — duplicate `a`

```text
Before: [abc]a
Duplicate found: a
Move l to one position after previous a
New window: bca
```

### Step 5 — duplicate `b`

```text
Before: [bca]b
Move l forward again
New window: cab
```

This continues while maintaining uniqueness.

---

# Why the Optimal Solution is Better

## Brute Force

* Rebuilds a set for every starting point
* Rechecks many characters repeatedly
* Slower for larger strings

## Sliding Window

* Each character is processed efficiently
* Left pointer only moves forward
* Much faster and cleaner for revision

---

# Important Observations

* A substring must be **contiguous**.
* The window must always contain **distinct characters**.
* When a duplicate is found, do **not** blindly move `l` by 1.
* Use the **last seen index** to jump `l` directly.
* `max(mp[s[r]] + 1, l)` is essential to avoid invalid backward movement.

---

# Template to Remember

```text
1. Keep two pointers: l and r
2. Expand r one step at a time
3. If current char is repeated inside the window:
   - move l to one position after its last occurrence
4. Update last seen index
5. Update answer with current window length
```

---

# Final Revision Note

This problem is a classic **sliding window + hash map** problem.

* Brute force checks all starts.
* Optimal solution stores the **last seen index** of each character.
* The answer is the maximum valid window length seen while scanning the string once.

---

# One-Line Summary

**Use a moving window of unique characters and jump the left pointer past duplicates using last seen indices.**
