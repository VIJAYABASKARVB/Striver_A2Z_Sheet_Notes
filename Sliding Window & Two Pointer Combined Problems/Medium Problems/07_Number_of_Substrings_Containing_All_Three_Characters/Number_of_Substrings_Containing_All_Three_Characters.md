# Number of Substrings Containing All Three Characters

## Problem Statement

Given a string `s` consisting only of the characters:

- `'a'`
- `'b'`
- `'c'`

Return the number of substrings that contain **at least one occurrence of all three characters**.

A substring is a **contiguous** part of the string.

---

## Examples

### Example 1

**Input**

```text
s = "abcba"
```

**Output**

```text
5
```

**Explanation**

The valid substrings are:

```text
abc
abcb
abcba
bcba
cba
```

---

### Example 2

**Input**

```text
s = "ccabcc"
```

**Output**

```text
8
```

**Explanation**

The valid substrings are:

```text
ccab
ccabc
ccabcc
cab
cabc
cabcc
abc
abcc
```

---

# Core Idea

We need to count all substrings that contain:

- at least one `'a'`
- at least one `'b'`
- at least one `'c'`

There are two approaches:

1. **Brute Force**
2. **Sliding Window**

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {

        int count = 0;
        int n = s.length();

        for (int i = 0; i < n; i++) {

            vector<int> freq(3,0);

            for (int j = i; j < n; j++) {

                freq[s[j]-'a']++;

                if(freq[0] > 0 &&
                   freq[1] > 0 &&
                   freq[2] > 0)
                {
                    count++;
                }
            }
        }

        return count;
    }
};
```

---

## How It Works

Fix every possible starting position.

For every starting position:

- keep extending the substring
- maintain the frequency of `'a'`, `'b'`, and `'c'`
- whenever all three frequencies become positive, count that substring.

---

## Visualization

Suppose

```text
s = "abcba"
```

Starting from index **0**

```
a
```

Not valid.

```
ab
```

Not valid.

```
abc
```

Valid ✔

```
abcb
```

Valid ✔

```
abcba
```

Valid ✔

Now start from index **1**

```
b
```

Not valid.

```
bc
```

Not valid.

```
bcb
```

Not valid.

```
bcba
```

Valid ✔

Continue similarly.

---

## Complexity

**Time**

```text
O(n²)
```

**Space**

```text
O(1)
```

(Only three frequency values.)

---

# 2) Optimal Approach — Sliding Window

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int numberOfSubstrings(string s) {

        vector<int> freq(3,0);

        int res = 0;
        int left = 0;

        for(int right=0; right<s.length(); right++) {

            freq[s[right]-'a']++;

            while(freq[0] > 0 &&
                  freq[1] > 0 &&
                  freq[2] > 0)
            {
                res += (s.length() - right);

                freq[s[left]-'a']--;

                left++;
            }
        }

        return res;
    }
};
```

---

# Main Intuition

This problem asks for

> **at least one** `'a'`, `'b'`, and `'c'`.

The moment a window satisfies this condition,

every larger window formed by extending its right boundary will also satisfy it.

This observation allows us to count many substrings at once.

---

# Why Sliding Window Works

Suppose we have

```text
abc...
```

If

```text
abc
```

already contains

- a
- b
- c

then

```text
abca
```

also contains them.

So does

```text
abcab
```

So does

```text
abcabc
```

Once the current window becomes valid,

**every extension to the right is automatically valid.**

---

# The Magic Formula

Whenever the window becomes valid:

```cpp
res += (n - right);
```

where

```text
n = length of string
```

---

## Why `n - right`?

Suppose

```text
s = abcabc

index

0 1 2 3 4 5
```

Current window:

```text
abc
```

```
right = 2
```

Remaining characters:

```
3
4
5
```

Every substring

```
abc
abca
abcab
abcabc
```

is valid.

Number of valid substrings

```
6 - 2 = 4
```

Exactly

```cpp
n-right
```

---

# Why Do We Shrink the Window?

After counting all substrings starting from the current `left`,

we want to discover new valid substrings beginning later.

So we remove

```cpp
s[left]
```

and move

```cpp
left++
```

Eventually the window becomes invalid again,

then we expand using `right`.

---

# Visualization

Suppose

```text
s = "abcabc"
```

Initially

```text
left = 0
right = 0
```

Window

```
a
```

Not valid.

Expand

```
ab
```

Still not valid.

Expand

```
abc
```

Now valid.

```
left
 ↓
abc
  ↑
right
```

Count

```
abc
abca
abcab
abcabc
```

There are

```
6-2 = 4
```

valid substrings.

Now shrink.

Window

```
bc
```

Invalid.

Expand.

Window

```
bca
```

Valid again.

Count

```
bca
bcab
bcabc
```

Again

```
6-3 = 3
```

Continue until the end.

---

# Dry Run

## Input

```text
s = "abcabc"
```

Initial state

```text
left = 0

res = 0

freq

a = 0
b = 0
c = 0
```

---

### right = 0

Window

```
a
```

```
freq

a=1
b=0
c=0
```

Not valid.

---

### right = 1

Window

```
ab
```

```
a=1
b=1
c=0
```

Not valid.

---

### right = 2

Window

```
abc
```

```
a=1
b=1
c=1
```

Valid.

Count

```
6-2 = 4
```

```
res = 4
```

Shrink.

Window

```
bc
```

---

### right = 3

Window

```
bca
```

Valid.

Count

```
6-3 = 3
```

```
res = 7
```

Shrink.

---

### right = 4

Window

```
cab
```

Valid.

Count

```
6-4 = 2
```

```
res = 9
```

Shrink.

---

### right = 5

Window

```
abc
```

Valid.

Count

```
6-5 = 1
```

```
res = 10
```

Final Answer

```text
10
```

---

# Why This Algorithm Works

Whenever the current window contains

```
a
b
c
```

adding more characters on the right **can never remove these characters**.

Therefore:

every larger window ending after `right` is also valid.

Instead of checking them individually,

we count them all together using

```text
n-right
```

This is what makes the algorithm linear.

---

# Complexity Analysis

## Brute Force

**Time**

```text
O(n²)
```

**Space**

```text
O(1)
```

---

## Optimal Sliding Window

**Time**

```text
O(n)
```

Each character enters and leaves the window at most once.

**Space**

```text
O(1)
```

Only three frequency values are stored.

---

# Key Takeaways

- Maintain frequencies of `'a'`, `'b'`, and `'c'`.
- Expand the window until all three characters are present.
- Once valid, **every extension to the right is also valid**.
- Count all those substrings at once using:

```text
n - right
```

- Shrink the window and continue.

---

# Revision Template

```text
1. Maintain a sliding window.

2. Keep frequencies of
      a
      b
      c

3. Expand right.

4. When all three characters exist,

      answer += n-right

5. Shrink from left.

6. Repeat until right reaches the end.
```

---

# Final Intuition

> The moment a window contains **a, b, and c**, every longer substring obtained by extending its right boundary is automatically valid. Instead of counting them one by one, count them all together using **`n - right`**.