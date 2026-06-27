# Last Occurrence in a Sorted Array

## Problem Statement

Given a **sorted array** of `N` integers and a target value `key`, return the **last occurrence** (last index) of the target.

If the target is not present, return `-1`.

> **Note:** Use **0-based indexing**.

---

## Examples

### Example 1

**Input**

```text
arr = [3,4,13,13,13,20,40]
key = 13
```

**Output**

```text
4
```

**Explanation**

```text
13 appears at indices:

2,3,4

The last occurrence is index 4.
```

---

### Example 2

**Input**

```text
arr = [3,4,13,13,13,20,40]
key = 60
```

**Output**

```text
-1
```

**Explanation**

```text
60 is not present.
```

---

# Core Idea

Unlike normal Binary Search,

we **do not stop** when we find the target.

Instead,

we continue searching on the **right half** because there may be another occurrence.

---

# Pattern

```text
Binary Search on Answer
```

---

# Brute Force Approach

## Idea

Start from the **end** of the array.

The first occurrence encountered is automatically the **last occurrence**.

---

## Algorithm

1. Traverse from `n-1` to `0`.
2. If `arr[i] == key`, return `i`.
3. If traversal ends, return `-1`.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// find last index of key by scanning from right
int solve(int n, int key, vector<int>& v) {
    int res = -1;

    for (int i = n - 1; i >= 0; i--) {
        if (v[i] == key) {
            res = i;
            break;
        }
    }

    return res;
}
```

---

## Dry Run

```text
Array

3 4 13 13 13 20 40

Start from end

40 ❌
20 ❌
13 ✅

Return index 4
```

---

## Complexity

### Time

```text
O(N)
```

### Space

```text
O(1)
```

---

# Optimal Approach (Binary Search)

## Key Observation

Whenever we find the target,

it **might not be the last occurrence**.

So,

- Save the index.
- Continue searching on the **right side**.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int solve(int n, int key, vector<int>& v) {

    int start = 0;
    int end = n - 1;
    int res = -1;

    while (start <= end) {

        int mid = start + (end - start) / 2;

        if (v[mid] == key) {
            res = mid;
            start = mid + 1;
        }
        else if (key < v[mid]) {
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    return res;
}
```

---

# Why Move Right?

Suppose

```text
3 4 13 13 13 20 40
```

Binary Search finds

```text
13

at index 3
```

Is it the last?

```text
No.

There is another 13 at index 4.
```

Therefore,

after finding the target,

move right.

---

# Visualization

Need

```text
Last occurrence of 13
```

```text
Index

0 1 2 3 4 5 6

Value

3 4 13 13 13 20 40

      ↑  ↑  ↑

Need this one
         ↑
      Index 4
```

---

# Pointer Placement Visualization

### Initial

```text
Index

0 1 2 3 4 5 6

Value

3 4 13 13 13 20 40

S     M       E
```

```
start = 0
end = 6

mid = 3
```

Current value

```text
13
```

Target found

Store answer

```text
res = 3
```

But continue RIGHT

```text
start = mid + 1
```

---

### Next

```text
Index

0 1 2 3 4 5 6

Value

3 4 13 13 13 20 40

        S M E
```

```
start = 4
end = 6

mid = 5
```

Current value

```text
20
```

Too large

Move LEFT

```text
end = 4
```

---

### Next

```text
Index

0 1 2 3 4 5 6

Value

3 4 13 13 13 20 40

        S
        M
        E
```

```
mid = 4
```

Current value

```text
13
```

Store

```text
res = 4
```

Move RIGHT

```text
start = 5
```

Now

```text
start > end
```

Stop.

Answer

```text
4
```

---

# Complete Dry Run

## Input

```text
arr=[3,4,13,13,13,20,40]

key=13
```

---

Initial

```text
start=0

end=6

res=-1
```

---

### Iteration 1

```text
mid=3

arr[mid]=13
```

Found

```text
res=3
```

Move Right

```text
start=4
```

---

### Iteration 2

```text
mid=5

arr[mid]=20
```

```
20>13
```

Move Left

```text
end=4
```

---

### Iteration 3

```text
mid=4

arr[mid]=13
```

Update

```text
res=4
```

Move Right

```text
start=5
```

Loop ends.

Return

```text
4
```

---

# Dry Run (Target Not Present)

Input

```text
arr=[3,4,13,13,13,20,40]

key=60
```

---

```text
mid=3

13<60

Move Right
```

↓

```text
mid=5

20<60

Move Right
```

↓

```text
mid=6

40<60

Move Right
```

↓

Loop Ends

```text
res=-1
```

Return

```text
-1
```

---

# Binary Search Flow

```text
Found Target?

      YES
       │
Store Current Index
       │
Move RIGHT
       │
Find Another Target?
       │
      YES
       │
Update Answer
       │
Move RIGHT Again
```

---

# Difference Between First and Last Occurrence

| First Occurrence | Last Occurrence |
|------------------|-----------------|
| Store answer | Store answer |
| Search LEFT | Search RIGHT |
| `end = mid - 1` | `start = mid + 1` |

---

# Memory Trick

```text
Need FIRST?

← Go LEFT

Need LAST?

Go RIGHT →
```

---

# Edge Cases

### Target at Beginning

```text
[5,5,5,8]

Answer

2
```

---

### Single Element

```text
[7]

Target=7

Answer=0
```

---

### Target Missing

```text
[2,4,6]

Target=5

Answer=-1
```

---

### All Elements Same

```text
[3,3,3,3,3]

Target=3

Answer=4
```

---

# Complexity

## Brute Force

### Time

```text
O(N)
```

### Space

```text
O(1)
```

---

## Optimal

### Time

```text
O(log N)
```

Binary Search halves the search space every iteration.

---

### Space

```text
O(1)
```

---

# Revision Template

```text
1. Initialize start, end
2. res = -1
3. Find mid
4. If arr[mid] == target
       res = mid
       start = mid + 1
5. Else if target < arr[mid]
       end = mid - 1
6. Else
       start = mid + 1
7. Return res
```

---

# Key Takeaways

- The array is sorted, so use Binary Search.
- Do **not stop** when the target is found.
- Store the current index.
- Continue searching on the **right half**.
- The last stored index is the answer.

---

# Final Intuition

> The moment Binary Search finds the target, it is only a **candidate** for the last occurrence. By saving the index and continuing to search on the **right**, we ensure that no later occurrence is missed.