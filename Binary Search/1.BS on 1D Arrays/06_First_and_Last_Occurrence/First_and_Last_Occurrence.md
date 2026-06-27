# Find First and Last Position of Element in Sorted Array (LeetCode 34)

## Problem Statement

Given a **sorted array** `nums` in non-decreasing order and a target value, return the **starting index** and **ending index** of the target.

If the target is not present, return

```text
[-1,-1]
```

You **must** solve the problem in **O(log N)** time.

---

## Examples

### Example 1

**Input**

```text
nums = [5,7,7,8,8,10]

target = 8
```

**Output**

```text
[3,4]
```

---

### Example 2

**Input**

```text
nums = [5,7,7,8,8,10]

target = 6
```

**Output**

```text
[-1,-1]
```

---

### Example 3

**Input**

```text
nums = []

target = 0
```

**Output**

```text
[-1,-1]
```

---

# Core Idea

Instead of finding the first and last occurrence separately,

we can solve the problem using

- **Lower Bound**
- **Upper Bound**

because

```text
First Occurrence

=

Lower Bound(target)
```

and

```text
Last Occurrence

=

Upper Bound(target)-1
```

---

# Pattern

```text
Binary Search
```

---

# Important Observation

Suppose

```text
nums =

[5,7,7,8,8,10]
```

Target

```text
8
```

Lower Bound

```text
First element >=8

↓

Index 3
```

Upper Bound

```text
First element >8

↓

Index 5
```

Therefore

```text
Last occurrence

=

Upper Bound-1

=

5-1

=

4
```

Answer

```text
[3,4]
```

---

# Formula

```text
First Occurrence

=

Lower Bound(target)

------------------------

Last Occurrence

=

Upper Bound(target)-1
```

This is the entire problem.

---

# Optimal Solution

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();

        // Lower Bound
        int low = 0, high = n - 1;
        int lb = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] >= target) {
                lb = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }

        // Target doesn't exist
        if (lb == n || nums[lb] != target)
            return {-1,-1};

        // Upper Bound
        low = 0;
        high = n - 1;
        int ub = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] > target) {
                ub = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }

        return {lb, ub - 1};
    }
};
```

---

# Why Lower Bound Gives First Occurrence?

Lower Bound finds

```text
First element

>= target
```

Suppose

```text
5 7 7 8 8 10

        ↑

First 8
```

The first value

```text
>=8
```

is exactly

```text
the first occurrence.
```

---

# Why Upper Bound Gives Last Occurrence?

Upper Bound finds

```text
First element

> target
```

Suppose

```text
5 7 7 8 8 10

            ↑

First >8
```

This is

```text
10
```

located at index

```text
5
```

Therefore

```text
Previous index

↓

4
```

must be

```text
the last occurrence.
```

---

# Complete Visualization

```
Index

0 1 2 3 4 5

Value

5 7 7 8 8 10

      LB      UB
       ↓       ↓

5 7 7 8 8 10
      ↑   ↑

 First   Last
```

---

# Pointer Placement (Lower Bound)

Need

```text
First index >=8
```

Initial

```text
Index

0 1 2 3 4 5

5 7 7 8 8 10

L     M     H
```

```
mid=2

nums[mid]=7
```

```
7<8
```

Move Right

```text
low=3
```

---

Next

```text
5 7 7 8 8 10

      L M H
```

```
mid=4

nums[mid]=8
```

Possible answer

```text
lb=4
```

Search LEFT

```text
high=3
```

---

Next

```text
5 7 7 8 8 10

      L
      M
      H
```

```
mid=3

nums[mid]=8
```

Better answer

```text
lb=3
```

Move Left

```text
high=2
```

Loop ends

Lower Bound

```text
3
```

---

# Pointer Placement (Upper Bound)

Need

```text
First element >8
```

Initial

```text
5 7 7 8 8 10

L     M     H
```

```
mid=2

7<8
```

Move Right

---

Next

```text
5 7 7 8 8 10

      L M H
```

```
mid=4

8<=8
```

Still not greater

Move Right

```text
low=5
```

---

Next

```text
5 7 7 8 8 10

          L
          M
          H
```

```
mid=5

10>8
```

Possible answer

```text
ub=5
```

Search LEFT

```text
high=4
```

Loop ends

Upper Bound

```text
5
```

---

# Dry Run

Input

```text
nums=[5,7,7,8,8,10]

target=8
```

---

## Lower Bound

Initial

```text
low=0

high=5

lb=6
```

---

Iteration 1

```text
mid=2

7<8
```

Move Right

```text
low=3
```

---

Iteration 2

```text
mid=4

8>=8
```

Store

```text
lb=4
```

Move Left

```text
high=3
```

---

Iteration 3

```text
mid=3

8>=8
```

Store

```text
lb=3
```

Move Left

Stop

---

Lower Bound

```text
3
```

---

## Upper Bound

Initial

```text
low=0

high=5

ub=6
```

---

Iteration 1

```text
mid=2

7<=8
```

Move Right

---

Iteration 2

```text
mid=4

8<=8
```

Move Right

---

Iteration 3

```text
mid=5

10>8
```

Store

```text
ub=5
```

Move Left

Stop

---

Upper Bound

```text
5
```

---

Answer

```text
First = lb = 3

Last = ub-1 = 4
```

```
[3,4]
```

---

# Dry Run (Target Missing)

Input

```text
nums=[5,7,7,8,8,10]

target=6
```

Lower Bound

```text
lb=1
```

Check

```text
nums[1]=7
```

```
7!=6
```

Therefore

```text
Target absent
```

Immediately return

```text
[-1,-1]
```

No need to compute Upper Bound.

---

# Why This Check?

```cpp
if(lb==n || nums[lb]!=target)
```

Suppose

```text
nums

5 7 8 9

target=6
```

Lower Bound returns

```text
1
```

because

```text
7>=6
```

But

```text
nums[1]=7

≠6
```

Meaning

```text
Target does NOT exist.
```

Hence

```text
[-1,-1]
```

---

# Relationship with Previous Problems

| Problem | Binary Search Variant |
|----------|----------------------|
| Lower Bound | First element ≥ target |
| Upper Bound | First element > target |
| First Occurrence | Lower Bound |
| Last Occurrence | Upper Bound-1 |
| Leetcode 34 | Lower Bound + Upper Bound |

---

# Binary Search Flow

```
            Target

               │

       Lower Bound

               │

     First Occurrence

               │

       Upper Bound

               │

 Upper Bound - 1

               │

      Last Occurrence
```

---

# Edge Cases

## Empty Array

```text
[]

↓

[-1,-1]
```

---

## One Element

```text
[8]

↓

[0,0]
```

---

## All Elements Same

```text
[2,2,2,2]

↓

[0,3]
```

---

## Target Missing

```text
[1,2,3]

target=5

↓

[-1,-1]
```

---

# Complexity

## Time

Lower Bound

```text
O(logN)
```

Upper Bound

```text
O(logN)
```

Overall

```text
O(logN)
```

---

## Space

```text
O(1)
```

---

# Revision Template

```text
1. Find Lower Bound

↓

First Occurrence

2. If target missing

↓

Return [-1,-1]

3. Find Upper Bound

↓

Last Occurrence = UB-1

4. Return [LB, UB-1]
```

---

# Memory Trick

```text
Lower Bound

↓

First ≥ Target

↓

First Occurrence

--------------------------

Upper Bound

↓

First > Target

↓

Previous Index

↓

Last Occurrence
```

---

# Key Takeaways

- This problem is a direct application of **Lower Bound** and **Upper Bound**.
- **Lower Bound** gives the first occurrence.
- **Upper Bound - 1** gives the last occurrence.
- Always verify that the lower bound actually contains the target before computing the upper bound.
- Runs in **O(log N)** with constant extra space.

---

# Final Intuition

> Think of the target values as one continuous block in the sorted array. The **Lower Bound** finds where that block begins, while the **Upper Bound** finds the first position after the block ends. Subtracting one from the Upper Bound gives the last occurrence.