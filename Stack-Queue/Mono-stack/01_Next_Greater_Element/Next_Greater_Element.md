# Next Greater Element I

## Problem Statement

You are given two **distinct** 0-indexed integer arrays `nums1` and `nums2`, where `nums1` is a **subset** of `nums2`.

For every element in `nums1`, find its **Next Greater Element** in `nums2`.

The **Next Greater Element** of an element `x` is the **first greater element that appears to its right** in `nums2`.

If no greater element exists, return `-1`.

Return an array `answer` where `answer[i]` is the next greater element of `nums1[i]`.

---

## Examples

### Example 1

**Input**

```text
nums1 = [4,1,2]
nums2 = [1,3,4,2]
```

**Output**

```text
[-1,3,-1]
```

**Explanation**

- 4 → No greater element to its right → -1
- 1 → Next greater element is 3
- 2 → No greater element to its right → -1

---

### Example 2

**Input**

```text
nums1 = [2,4]
nums2 = [1,2,3,4]
```

**Output**

```text
[3,-1]
```

**Explanation**

- 2 → Next greater element is 3
- 4 → No greater element → -1

---

# Intuition

For every element we need the **first greater element on its right**.

A brute-force solution scans all elements to the right.

Instead, we use a **Monotonic Decreasing Stack**.

The stack always stores possible **next greater elements**.

---

# Why Process From Right to Left?

Suppose

```text
nums2 = [1,3,4,2]
```

When we stand on an element, every element to its **right has already been processed**.

Therefore, the stack already contains every possible candidate for the next greater element.

---

# Monotonic Decreasing Stack

The stack always remains in **decreasing order**.

Example:

```text
Top
 ↓
1
3
4
```

Whenever a larger element arrives, every smaller element is removed because it can never become the next greater element for any previous number.

---

# Visual Representation

## nums2 = [1,3,4,2]

### Step 1

Current = 2

```text
Stack = []

No greater element

Map:
2 → -1

Push 2

Stack:
[2]
```

---

### Step 2

Current = 4

```text
Stack:
[2]

2 < 4

Pop 2

Stack becomes empty

Map:
4 → -1

Push 4

Stack:
[4]
```

---

### Step 3

Current = 3

```text
Stack:
[4]

Top = 4

Next Greater = 4

Map:
3 → 4

Push 3

Stack:
4
3
```

---

### Step 4

Current = 1

```text
Stack:
4
3

Top = 3

Next Greater = 3

Map:
1 → 3

Push 1

Stack:
4
3
1
```

---

Final Map

```text
1 → 3

2 → -1

3 → 4

4 → -1
```

Now answer every element in nums1.

```text
nums1

[4,1,2]

↓

[-1,3,-1]
```

---

# Algorithm

1. Create an empty stack.
2. Create an unordered map.
3. Traverse `nums2` from **right to left**.
4. While the stack is not empty and `stack.top() < current`, pop the stack.
5. If the stack is empty, store `-1` in the map.
6. Otherwise, store `stack.top()` as the next greater element.
7. Push the current element into the stack.
8. Finally, traverse `nums1` and fetch answers from the map.

---

# C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1,
                                   vector<int>& nums2) {

        stack<int> st;
        unordered_map<int, int> nextGreaterMap;

        // Process nums2 from right to left
        for (int i = nums2.size() - 1; i >= 0; i--) {

            while (!st.empty() && st.top() < nums2[i]) {
                st.pop();
            }

            if (st.empty()) {
                nextGreaterMap[nums2[i]] = -1;
            } else {
                nextGreaterMap[nums2[i]] = st.top();
            }

            st.push(nums2[i]);
        }

        vector<int> ans;

        for (int num : nums1) {
            ans.push_back(nextGreaterMap[num]);
        }

        return ans;
    }
};
```

---

# Dry Run

Input

```text
nums1 = [4,1,2]

nums2 = [1,3,4,2]
```

| Step | Current | Stack Before | Action | Stack After | Map |
|------|---------|--------------|--------|-------------|-----|
| 1 | 2 | [] | Empty → -1 | [2] | 2 → -1 |
| 2 | 4 | [2] | Pop 2 | [4] | 4 → -1 |
| 3 | 3 | [4] | Top = 4 | [4,3] | 3 → 4 |
| 4 | 1 | [4,3] | Top = 3 | [4,3,1] | 1 → 3 |

Result

```text
4 → -1

1 → 3

2 → -1

Answer

[-1,3,-1]
```

---

# Why Do We Pop Smaller Elements?

Suppose

```text
Stack

7
5
2

Current = 6
```

Can 5 become the next greater element?

No.

Because

- 6 is larger than 5.
- 6 is also closer to every element on the left.

Therefore,

```text
5 is useless.

Pop it.
```

Similarly,

```text
2 is also useless.

Pop it.
```

Now

```text
Stack

7
```

So,

```text
Next Greater of 6 = 7
```

---

# Complexity Analysis

| Operation | Complexity |
|-----------|------------|
| Process nums2 | O(n) |
| Build answer | O(m) |
| **Overall Time** | **O(n + m)** |
| **Extra Space** | **O(n)** |

---

# Edge Cases

| nums1 | nums2 | Output |
|-------|-------|--------|
| [5] | [5] | [-1] |
| [1] | [1,2] | [2] |
| [3,2,1] | [3,2,1] | [-1,-1,-1] |
| [1,2,3] | [1,2,3] | [2,3,-1] |
| [4] | [1,2,3,4] | [-1] |

---

# Key Takeaways

- ✅ Process the array from **right to left**.
- ✅ Maintain a **Monotonic Decreasing Stack**.
- ✅ Pop every smaller element.
- ✅ Stack top becomes the next greater element.
- ✅ Store answers in a hashmap.
- ✅ Lookup for `nums1` becomes O(1).

---

# Quick Revision

1. Traverse from **right → left**.
2. Pop all smaller elements.
3. If stack is empty → answer is **-1**.
4. Else → answer is **stack.top()**.
5. Push current element.
6. Store answers in a hashmap.
7. Build the final answer using `nums1`.

---

# Visual Memory Aid

```text
nums2

1   3   4   2
↑           ↑

Process

← ← ← ←

Stack

[]

↓

2

↓

4

↓

4
3

↓

4
3
1
```

---

# Pattern Recognition

Whenever you see:

- Next Greater Element
- Previous Greater Element
- Next Smaller Element
- Previous Smaller Element

Think immediately:

```text
MONOTONIC STACK
```

This is one of the most important stack patterns for coding interviews.