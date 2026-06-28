# Reverse Words in a String

---

# Problem Statement

Given a string containing words separated by one or more spaces, return a new string where the **order of the words is reversed**.

The output should:

- Have exactly **one space** between words.
- Have **no leading or trailing spaces**.

A word is any sequence of non-space characters.

---

# Examples

## Example 1

**Input**

```text
s = "welcome to the jungle"
```

**Output**

```text
"jungle the to welcome"
```

---

## Example 2

**Input**

```text
s = " amazing coding skills "
```

**Output**

```text
"skills coding amazing"
```

**Explanation**

Leading, trailing, and multiple spaces are removed in the output.

---

# Core Idea / Pattern Recognition

**Pattern**

```
Two Pointers / String Traversal
```

### Why?

Instead of splitting the string into words and reversing them later, we can traverse the string **from right to left** and directly build the answer.

This avoids storing all words separately.

---

# Observation

Suppose

```
welcome to the jungle
```

If we scan from the end,

```
← jungle

← the

← to

← welcome
```

we naturally obtain the words in reverse order.

The only extra work is skipping unnecessary spaces.

---

# Approach 1 — Brute Force

## Idea

Extract every word into a vector.

Reverse the vector.

Join the words using a single space.

---

## Algorithm

1. Traverse the string.
2. Store every word in a vector.
3. Reverse the vector.
4. Join the words with one space.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        vector<string> words;
        string word = "";

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                word += s[i];
            }
            else if (!word.empty()) {
                words.push_back(word);
                word = "";
            }
        }

        if (!word.empty()) {
            words.push_back(word);
        }

        reverse(words.begin(), words.end());

        string result = "";

        for (int i = 0; i < words.size(); i++) {
            result += words[i];

            if (i < words.size() - 1)
                result += " ";
        }

        return result;
    }
};
```

---

## Visualization

```
Input

welcome to the jungle

↓

Store

["welcome","to","the","jungle"]

↓

Reverse

["jungle","the","to","welcome"]

↓

Join

"jungle the to welcome"
```

---

## Dry Run

```
word="welcome"

↓

Push

↓

word="to"

↓

Push

↓

word="the"

↓

Push

↓

word="jungle"

↓

Push
```

Vector

```
["welcome","to","the","jungle"]
```

Reverse

```
["jungle","the","to","welcome"]
```

Answer

```
"jungle the to welcome"
```

---

## Complexity

**Time:** `O(N)`

**Space:** `O(N)`

---

# Approach 2 — Optimal Approach

## Main Idea

Traverse the string **from right to left**.

- Skip spaces.
- Extract one complete word.
- Append it to the answer.
- Repeat until the beginning.

No extra vector is needed.

---

## Why It Works

Consider

```
welcome to the jungle
```

Start from the end.

```
← jungle

↓

Answer

jungle
```

Continue

```
← the

↓

Answer

jungle the
```

Continue

```
← to

↓

Answer

jungle the to
```

Finally

```
← welcome
```

Result

```
jungle the to welcome
```

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        string result = "";

        int i = s.size() - 1;

        while (i >= 0) {

            while (i >= 0 && s[i] == ' ')
                i--;

            if (i < 0)
                break;

            int end = i;

            while (i >= 0 && s[i] != ' ')
                i--;

            string word = s.substr(i + 1, end - i);

            if (!result.empty())
                result += " ";

            result += word;
        }

        return result;
    }
};
```

---

## Pointer Placement Visualization

Input

```
" amazing coding skills "
```

### Step 1

Skip trailing spaces

```
 amazing coding skills_
                      ↑

i
```

↓

```
skills
```

Result

```
skills
```

---

### Step 2

Move left

```
 amazing coding skills

        ↑

coding
```

Result

```
skills coding
```

---

### Step 3

Move left

```
 amazing coding skills

 ↑

amazing
```

Result

```
skills coding amazing
```

---

## Dry Run

Input

```
" amazing coding skills "
```

### Iteration 1

```
Skip spaces

↓

Find

skills
```

Result

```
skills
```

---

### Iteration 2

```
Skip spaces

↓

Find

coding
```

Result

```
skills coding
```

---

### Iteration 3

```
Skip spaces

↓

Find

amazing
```

Result

```
skills coding amazing
```

Return

```
skills coding amazing
```

---

## Edge Cases

- Empty string
- Only one word
- Leading spaces
- Trailing spaces
- Multiple spaces between words

---

## Complexity

### Time

```
O(N)
```

Each character is visited at most once.

### Space

```
O(N)
```

Space required for the output string.

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Vector + Reverse | `O(N)` | `O(N)` | Store all words, then reverse |
| Reverse Traversal | `O(N)` | `O(N)` | Traverse from right to left, no extra vector |

---

# Key Takeaways

- Ignore leading and trailing spaces.
- Skip multiple consecutive spaces.
- Traverse from the end to naturally obtain reverse order.
- Add a space only if the result is not empty.
- `substr(start, length)` extracts the current word efficiently.

---

# Revision Template

1. Start from the end of the string.
2. Skip all spaces.
3. Mark the end of a word.
4. Move left until a space.
5. Extract the word using `substr()`.
6. Append it to the result.
7. Repeat until the string begins.

---

# Memory Trick

```
Start From End

↓

Skip Spaces

↓

Pick Word

↓

Append

↓

Repeat
```

Remember:

> **"Walk backwards, collect words, and build the answer forwards."**

---

# Final Intuition

> Traverse the string from right to left, skip unnecessary spaces, extract one word at a time, and append it to the result to naturally produce the reversed sentence.