# Check for Balanced Parentheses

## Problem Statement

Given a string `s` containing only the characters:

- `(`
- `)`
- `{`
- `}`
- `[`
- `]`

Determine whether the string is **balanced (valid)**.

A string is valid if:

1. Every opening bracket has a matching closing bracket.
2. Brackets are closed in the correct order.
3. Every closing bracket matches the most recent unmatched opening bracket.

---

## Examples

### Example 1

**Input**

```text
s = "()[{}()]"
```

**Output**

```text
True
```

**Explanation**

Every opening bracket has a matching closing bracket in the correct order.

---

### Example 2

**Input**

```text
s = "[()"
```

**Output**

```text
False
```

**Explanation**

The opening `[` never gets closed.

---

### Example 3

**Input**

```text
s = "([)]"
```

**Output**

```text
False
```

**Explanation**

The order of closing brackets is incorrect.

---

## Why Stack?

A **Stack** follows **LIFO (Last In First Out)**.

The most recently opened bracket **must** be closed first.

Example:

```text
( { [ ] } )

Open order:
( → { → [

Close order:
] → } → )

Exactly opposite.

Perfect use case for a Stack.
```

---

# Visual Representation

## Example 1

```text
String:

( ) [ { } ( ) ]

Stack:

Step 1

(
Push

Stack:
(

-------------------

Step 2

)

Pop (

Matched

Stack:
empty

-------------------

Step 3

[

Push

Stack:
[

-------------------

Step 4

{

Push

Stack:
[
{

-------------------

Step 5

}

Pop {

Matched

Stack:
[

-------------------

Step 6

(

Push

Stack:
[
(

-------------------

Step 7

)

Pop (

Matched

Stack:
[

-------------------

Step 8

]

Pop [

Matched

Stack:
empty

Answer = True
```

---

## Invalid Example

```text
String:

[()

Step 1

[
Push

Stack:
[

------------

Step 2

(

Push

Stack:
[
(

------------

Step 3

)

Pop (

Matched

Stack:
[

------------

End of string

Stack still contains [

Not balanced

Answer = False
```

---

# Algorithm

For every character:

### Opening Bracket

```text
(
{
[
```

Push into stack.

---

### Closing Bracket

```text
)
}
]
```

If stack is empty

```text
False
```

Otherwise

Pop the top element.

If the popped bracket doesn't match

```text
False
```

Continue.

---

After processing every character:

If stack is empty

```text
True
```

Else

```text
False
```

---

# C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    bool isValid(string s) {

        stack<char> st;

        for(char c : s) {

            if(c == '(' || c == '{' || c == '[') {

                st.push(c);
            }

            else {

                if(st.empty())
                    return false;

                char top = st.top();
                st.pop();

                if((c == ')' && top == '(') ||
                   (c == '}' && top == '{') ||
                   (c == ']' && top == '[')) {

                    continue;
                }

                return false;
            }
        }

        return st.empty();
    }
};

int main() {

    Solution obj;

    string s = "()[{}()]";

    cout << (obj.isValid(s) ? "True" : "False");

    return 0;
}
```

---

# Dry Run

## Input

```text
()[{}()]
```

| Step | Character | Stack | Action |
|------|-----------|-------|--------|
| 1 | ( | ( | Push |
| 2 | ) | Empty | Pop & Match |
| 3 | [ | [ | Push |
| 4 | { | [ { | Push |
| 5 | } | [ | Pop & Match |
| 6 | ( | [ ( | Push |
| 7 | ) | [ | Pop & Match |
| 8 | ] | Empty | Pop & Match |

Final Stack

```text
Empty
```

Answer

```text
True
```

---

## Dry Run 2

Input

```text
([)]
```

| Step | Character | Stack | Action |
|------|-----------|-------|--------|
| 1 | ( | ( | Push |
| 2 | [ | ( [ | Push |
| 3 | ) | ( | Pop [ → Doesn't Match ) |

Immediately return

```text
False
```

---

# Complexity Analysis

| Operation | Complexity |
|-----------|------------|
| Traversing String | O(n) |
| Push | O(1) |
| Pop | O(1) |
| Total Time | O(n) |
| Extra Space | O(n) |

---

# Why Does This Work?

Suppose

```text
({[]})
```

Opening brackets are stored like

```text
(
{
[
```

The first bracket that must close is

```text
[
```

Exactly the **last** bracket inserted.

That's exactly what a Stack gives.

---

# Edge Cases

| Input | Output |
|--------|--------|
| `""` | True |
| `"("` | False |
| `")"` | False |
| `"((()))"` | True |
| `"({[]})"` | True |
| `"([)]"` | False |
| `"((("` | False |
| `")))"` | False |

---

# Key Takeaways

- Stack is the ideal data structure.
- Push every opening bracket.
- On a closing bracket:
  - Stack must not be empty.
  - Top must match the closing bracket.
- At the end, the stack must be empty.
- Any mismatch immediately returns `false`.

---

# Quick Revision

### Push

```text
(
[
{
```

---

### Pop

```text
)
]
}
```

Must match

```text
( → )

[ → ]

{ → }
```

---

### Final Condition

```text
Stack Empty

↓

Balanced
```

Otherwise

```text
Not Balanced
```

---

# Visual Memory Aid

```text
Push

(

↓

(

↓

({

↓

({[

↓

Pop

({

↓

(

↓

Empty

Balanced
```

---

### Easy Trick to Remember

```text
Opening Brackets

↓

Push

Closing Brackets

↓

Pop

Top matches?

↓

Yes → Continue

No → False

End

↓

Stack Empty?

↓

True
```