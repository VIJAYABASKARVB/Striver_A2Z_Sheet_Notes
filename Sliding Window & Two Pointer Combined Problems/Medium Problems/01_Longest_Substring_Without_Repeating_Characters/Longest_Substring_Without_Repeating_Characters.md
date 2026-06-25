# Longest Substring Without Repeating Characters

## Problem Statement

Given a string `s`, return the length of the **longest substring** that contains **no repeating characters**.

A **substring** is a contiguous sequence of characters within a string.

---

## Examples

### Example 1

**Input**

```text
s = "zxyzxyz"
```

**Output**

```text
3
```

**Explanation**

The longest substring without repeating characters is:

```text
"zxy"
```

or

```text
"xyz"
```

Both have length **3**.

---

### Example 2

**Input**

```text
s = "xxxx"
```

**Output**

```text
1
```

**Explanation**

Only one unique character can exist in a substring.

---

### Example 3

**Input**

```text
s = "abcabcbb"
```

**Output**

```text
3
```

Longest substring:

```text
abc
```

---

# Intuition

We need the **longest window** that contains **only unique characters**.

Whenever a duplicate appears,

the window becomes invalid.

So we **move the left pointer** until the duplicate is removed.

This is a classic **Sliding Window** problem.

---

# Why Sliding Window?

Instead of checking every possible substring,

maintain a window

```text
[left ........ right]
```

that always contains **unique characters**.

Whenever a duplicate is found,

move the left pointer.

---

# Visual Representation

## Example

```text
s = "abcabcbb"
```

Initially

```text
Window

[a]

Length = 1
```

---

Add **b**

```text
[a b]

Length = 2
```

---

Add **c**

```text
[a b c]

Length = 3
```

---

Next character

```text
a
```

Duplicate found.

Previous **a** was at index **0**.

Move left pointer to

```text
0 + 1 = 1
```

Window becomes

```text
[b c a]

Length = 3
```

---

Next character

```text
b
```

Duplicate found.

Move left pointer

```text
2
```

Window

```text
[c a b]
```

Still length

```text
3
```

Continue until the end.

Answer

```text
3
```

---

# Sliding Window

We maintain

```text
l → left pointer

r → right pointer
```

Also maintain a hashmap

```text
Character

↓

Last Seen Index
```

Example

```text
a → 3

b → 6

c → 5
```

Whenever a duplicate is found,

jump the left pointer directly.

---

# Algorithm

1. Create a hashmap storing the last index of every character.
2. Initialize

```text
left = 0
```

3. Traverse using the right pointer.
4. If the current character already exists,

move

```cpp
left = max(left, lastSeen[current] + 1);
```

5. Store the current index.
6. Update the maximum window size.

---

# C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        unordered_map<char,int> lastSeen;

        int left = 0;
        int ans = 0;

        for(int right = 0; right < s.size(); right++) {

            if(lastSeen.find(s[right]) != lastSeen.end()) {

                left = max(left, lastSeen[s[right]] + 1);
            }

            lastSeen[s[right]] = right;

            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};
```

---

# Dry Run

Input

```text
s = "zxyzxyz"
```

| Right | Character | Left Before | Left After | Current Window | Length | Max |
|------:|-----------|------------:|-----------:|----------------|-------:|----:|
| 0 | z | 0 | 0 | z | 1 | 1 |
| 1 | x | 0 | 0 | zx | 2 | 2 |
| 2 | y | 0 | 0 | zxy | 3 | 3 |
| 3 | z | 0 | 1 | xyz | 3 | 3 |
| 4 | x | 1 | 2 | yzx | 3 | 3 |
| 5 | y | 2 | 3 | zxy | 3 | 3 |
| 6 | z | 3 | 4 | xyz | 3 | 3 |

Final Answer

```text
3
```

---

# Why Do We Use max()?

Suppose

```text
String

abba
```

Processing

```text
a
b
b
a
```

When we reach the last **a**

Previous **a**

```text
Index = 0
```

Current left pointer

```text
2
```

If we simply write

```cpp
left = lastSeen['a'] + 1;
```

Left becomes

```text
1
```

It moves **backwards**, which is wrong.

Instead

```cpp
left = max(left, lastSeen['a'] + 1);
```

ensures

```text
Left never moves backwards.
```

---

# Complexity Analysis

| Operation | Complexity |
|-----------|------------|
| Traverse String | O(n) |
| HashMap Lookup | O(1) Average |
| Overall Time | **O(n)** |
| Extra Space | **O(min(n,m))** |

where

- `n` = length of string
- `m` = character set size

---

# Edge Cases

| Input | Output |
|--------|--------|
| `""` | 0 |
| `"a"` | 1 |
| `"aaaa"` | 1 |
| `"abcd"` | 4 |
| `"pwwkew"` | 3 |
| `"abcabcbb"` | 3 |
| `"dvdf"` | 3 |

---

# Key Takeaways

- ✅ Use the **Sliding Window** technique.
- ✅ Store the **last occurrence** of every character.
- ✅ Move the left pointer only when a duplicate appears.
- ✅ Use `max()` so the left pointer never moves backward.
- ✅ Window size is

```cpp
right - left + 1
```

- ✅ Time Complexity is **O(n)**.

---

# Quick Revision

1. Create a hashmap.
2. Start with

```text
left = 0
```

3. Traverse using the right pointer.
4. Duplicate?

```cpp
left = max(left, lastSeen[ch] + 1);
```

5. Update hashmap.
6. Update answer.

---

# Visual Memory Aid

```text
String

a b c a b c b b
      ↑       ↑
      l       r
```

Duplicate found

↓

Move left

```text
a b c a b c b b
  ↑           ↑
  l           r
```

Window always contains **unique characters**.

---

# Pattern Recognition

Whenever you hear

- Longest Substring
- No Repeating Characters
- At Most K Distinct Characters
- Minimum Window Substring
- Fixed Window
- Variable Window

Think immediately

```text
SLIDING WINDOW
```

This is one of the most important Sliding Window interview patterns.