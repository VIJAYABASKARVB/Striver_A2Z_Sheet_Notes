# Longest Repeating Character Replacement

## Problem Statement

You are given a string `s` consisting only of uppercase English letters and an integer `k`.

You may replace at most `k` characters in the string with any uppercase English letter.

Return the **length of the longest substring** that can be turned into a string containing **only one distinct character**.

---

## Examples

### Example 1

**Input:** `s = "XYYX"`, `k = 2`
**Output:** `4`

**Explanation:**

* Replace both `X` characters with `Y`, or
* Replace both `Y` characters with `X`

Either way, the whole string becomes a single repeated character.

### Example 2

**Input:** `s = "AAABABB"`, `k = 1`
**Output:** `5`

---

## Core Idea

For any substring:

* Let `maxf` = frequency of the most common character in that substring.
* Then the number of characters that need to be replaced is:

```text
window_length - maxf
```

If this value is `<= k`, then the substring is valid.

So the problem becomes:

> Find the longest substring where at most `k` characters need to be changed.

This is a classic **sliding window** problem.

---

# 1) Brute Force Approach

## Code

```cpp
class Solution {
public:
    int characterReplacement(string s, int k) {
        int res = 0;
        for (int i = 0; i < s.size(); i++) {
            unordered_map<char, int> count;
            int maxf = 0;
            for (int j = i; j < s.size(); j++) {
                count[s[j]]++;
                maxf = max(maxf, count[s[j]]);
                if ((j - i + 1) - maxf <= k) {
                    res = max(res, j - i + 1);
                }
            }
        }
        return res;
    }
};
```

## How It Works

* Fix the starting point `i`.
* Expand the substring to the right using `j`.
* Count character frequencies in the current substring.
* Find the most frequent character count `maxf`.
* Check whether the remaining characters can be replaced using at most `k` operations.

## Why It Works

Every possible substring is checked, so the best valid answer is found.

## Complexity

* **Time:** `O(n^2)`
* **Space:** `O(1)` if treated as uppercase letters only, otherwise `O(26)` or `O(1)` in practice

---

# 2) Optimal Approach — Sliding Window

## Code

```cpp
class Solution {
public:
    int characterReplacement(std::string s, int k) {
        unordered_map<char, int> count;
        int res = 0;

        int l = 0, maxf = 0;
        for (int r = 0; r < s.size(); r++) {
            count[s[r]]++;
            maxf = max(maxf, count[s[r]]);

            while ((r - l + 1) - maxf > k) {
                count[s[l]]--;
                l++;
            }
            res = max(res, r - l + 1);
        }

        return res;
    }
};
```

## Main Observation

A window is valid if:

```text
(window size) - (frequency of the most common character) <= k
```

Meaning:

* the window can be made uniform by replacing at most `k` characters

---

## What `maxf` Means

`maxf` is the highest frequency of any character inside the current window.

Example:

```text
Window = AABAB
Counts  = A:3, B:2
maxf    = 3
```

Then replacements needed:

```text
5 - 3 = 2
```

So if `k >= 2`, this window is valid.

---

# Why Sliding Window Works

We keep a window `[l ... r]` and try to make it valid.

### Steps

1. Expand the window by moving `r`
2. Update character frequency
3. Update `maxf`
4. If the window needs more than `k` replacements, shrink from the left
5. Track the largest valid window length

---

## Window Visualization

```text
l                              r
|------------------------------|
current substring
```

* `r` expands the window
* `l` shrinks the window when the replacement limit is exceeded

---

# Dry Run

## Dry Run for `s = "AABABBA"`, `k = 1`

This is the standard example for understanding the idea.

We track:

* `l` = left pointer
* `r` = right pointer
* `count` = frequency map
* `maxf` = max frequency in the current window
* `window size`
* `replacements needed = window size - maxf`

| r | s[r] | Window | count   | maxf | Size | Size - maxf | Valid? | l | res |
| - | ---- | ------ | ------- | ---- | ---- | ----------- | ------ | - | --- |
| 0 | A    | A      | A:1     | 1    | 1    | 0           | Yes    | 0 | 1   |
| 1 | A    | AA     | A:2     | 2    | 2    | 0           | Yes    | 0 | 2   |
| 2 | B    | AAB    | A:2 B:1 | 2    | 3    | 1           | Yes    | 0 | 3   |
| 3 | A    | AABA   | A:3 B:1 | 3    | 4    | 1           | Yes    | 0 | 4   |
| 4 | B    | AABAB  | A:3 B:2 | 3    | 5    | 2           | No     | 1 | 4   |
| 5 | B    | ABABB  | A:2 B:3 | 3    | 5    | 2           | No     | 2 | 4   |
| 6 | A    | BABBA  | A:2 B:3 | 3    | 5    | 2           | No     | 3 | 4   |

### Answer

The maximum valid length is **4**.

---

## Why the Left Pointer Moves

When the number of replacements needed becomes greater than `k`, the window is no longer valid.

So we remove characters from the left until it becomes valid again.

---

# Important Insight About `maxf`

A common doubt is:

> Why do we not always recompute `maxf` after shrinking?

In this pattern, `maxf` is allowed to be a little stale.

That is okay because:

* It never hurts correctness
* It only helps us avoid extra work
* The window still eventually shrinks when needed

This makes the solution efficient.

---

# Why the Brute Force Condition Works

For any substring:

```text
replacements needed = substring length - highest frequency character count
```

Example:

```text
Substring = AABAB
Counts = A:3, B:2
Highest frequency = 3
Length = 5
Replacements needed = 5 - 3 = 2
```

To make the whole substring one repeated character, change the two `B`s into `A`s.

---

# Complexity

## Brute Force

* **Time:** `O(n^2)`
* **Space:** `O(1)` or `O(26)` depending on implementation

## Sliding Window

* **Time:** `O(n)`
* **Space:** `O(1)` or `O(26)`

---

# Key Takeaways

* The answer is a substring that can be made uniform with at most `k` changes.
* Track the most frequent character in the current window.
* If `window size - max frequency > k`, shrink the window.
* Update the result only for valid windows.

---

# Revision Template

```text
1. Expand right pointer
2. Count the frequency of characters
3. Track the most frequent character count
4. If replacements needed > k, shrink from left
5. Update the answer with valid window size
```

---

# Final Intuition

**Find the largest window where the number of non-dominant characters is at most `k`.**
