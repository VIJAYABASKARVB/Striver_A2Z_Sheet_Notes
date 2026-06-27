# Floor and Ceil in Sorted Array

## Problem Statement

You are given a **sorted array** `arr` of `n` integers and an integer `x`.

Find:

- **Floor of x** → The **largest element** in the array that is **less than or equal to x**.
- **Ceil of x** → The **smallest element** in the array that is **greater than or equal to x**.

If either floor or ceil does not exist, return `-1` for that value.

---

## Examples

### Example 1

**Input**

```text
arr = [3, 4, 4, 7, 8, 10]
x = 5
```

**Output**

```text
Floor = 4
Ceil = 7
```

**Explanation**

```text
Largest value <= 5  → 4
Smallest value >= 5 → 7
```

---

### Example 2

**Input**

```text
arr = [3,4,4,7,8,10]
x = 8
```

**Output**

```text
Floor = 8
Ceil = 8
```

Since `8` exists in the array,

both floor and ceil are `8`.

---

# Core Idea

This problem is actually a combination of two Binary Search problems.

```text
Floor
↓

Largest element <= x
```

and

```text
Ceil
↓

Smallest element >= x
```

We solve both independently using Binary Search.

---

# Pattern

```text
Binary Search
```

---

# Important Definitions

## Floor

The floor is

```text
Largest element ≤ x
```

Example

```text
Array

3 4 4 7 8 10

x = 5

Answer

4
```

---

## Ceil

The ceil is

```text
Smallest element ≥ x
```

Example

```text
Array

3 4 4 7 8 10

x = 5

Answer

7
```

---

# Memory Trick

Think of a number line.

```text
                 x

------Floor------|------Ceil------

Floor always stays on LEFT.

Ceil always stays on RIGHT.
```

---

# Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class FloorCeilFinder {
public:
    // Function to find the floor of x
    int findFloor(int arr[], int n, int x) {
        int low = 0, high = n - 1;
        int ans = -1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] <= x) {
                ans = arr[mid];
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }

    // Function to find the ceiling of x
    int findCeil(int arr[], int n, int x) {
        int low = 0, high = n - 1;
        int ans = -1;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] >= x) {
                ans = arr[mid];
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }

    pair<int, int> getFloorAndCeil(int arr[], int n, int x) {
        return {findFloor(arr,n,x), findCeil(arr,n,x)};
    }
};
```

---

# Main Idea

Although both problems look similar,

their search directions are opposite.

For Floor,

we want the **largest valid value**.

For Ceil,

we want the **smallest valid value**.

---

# Finding Floor

We want

```text
Largest element <= x
```

Whenever

```text
arr[mid] <= x
```

it is a possible floor.

Store it.

But maybe a **larger** value also satisfies the condition.

So search on the **right**.

---

# Visualization (Floor)

Suppose

```text
arr = [3,4,4,7,8,10]

x = 5
```

Need

```text
Largest value <=5
```

```
3   4   4   7   8   10
                ↑

Answer = 4
```

---

# Pointer Placement (Floor)

Initial

```text
Index

0 1 2 3 4 5

3 4 4 7 8 10

L         M         H
```

```
mid = 2

arr[mid]=4
```

Since

```text
4 <= 5
```

Possible floor

```text
ans = 4
```

Move RIGHT

```text
low = mid+1
```

---

Next

```text
3 4 4 7 8 10

      L H
       M
```

```
arr[mid]=8
```

Too large

Move LEFT

---

Continue

Eventually

```text
Answer = 4
```

---

# Finding Ceil

Need

```text
Smallest element >= x
```

Whenever

```text
arr[mid] >= x
```

Possible ceil.

Store it.

But maybe an even smaller valid value exists.

Search LEFT.

---

# Visualization (Ceil)

Need

```text
Smallest value >=5
```

```
3 4 4 7 8 10

        ↑

Answer = 7
```

---

# Pointer Placement (Ceil)

Initial

```text
3 4 4 7 8 10

L        M       H
```

```
mid=2

arr[mid]=4
```

```
4<5
```

Move RIGHT

---

Next

```text
3 4 4 7 8 10

      L H
       M
```

```
mid=4

arr[mid]=8
```

Possible ceil

```text
ans=8
```

Move LEFT

---

Eventually

```text
7
```

becomes the smallest valid answer.

---

# Dry Run

## Input

```text
arr=[3,4,4,7,8,10]

x=5
```

---

## Floor

Initial

```text
low=0

high=5

ans=-1
```

---

### Iteration 1

```text
mid=2

arr[mid]=4
```

```
4<=5
```

Store

```text
ans=4
```

Move Right

```text
low=3
```

---

### Iteration 2

```text
mid=4

arr[mid]=8
```

```
8>5
```

Move Left

```text
high=3
```

---

### Iteration 3

```text
mid=3

arr[mid]=7
```

```
7>5
```

Move Left

End

Answer

```text
4
```

---

## Ceil

Initial

```text
low=0

high=5

ans=-1
```

---

### Iteration 1

```text
mid=2

arr[mid]=4
```

```
4<5
```

Move Right

---

### Iteration 2

```text
mid=4

arr[mid]=8
```

Possible Ceil

```text
ans=8
```

Move Left

---

### Iteration 3

```text
mid=3

arr[mid]=7
```

Possible Ceil

```text
ans=7
```

Move Left

Stop

Final Answer

```text
7
```

---

# Difference Between Floor and Ceil

| Floor | Ceil |
|--------|------|
| Largest element ≤ x | Smallest element ≥ x |
| Store answer when `arr[mid] <= x` | Store answer when `arr[mid] >= x` |
| Move Right after storing | Move Left after storing |

---

# Complete Visualization

```
Array

3   4   4   7   8   10

            x=5

3   4   4 | 5 | 7   8   10
        ↑     ↑

      Floor   Ceil
```

---

# Edge Cases

## Case 1

```text
x smaller than every element

Array

3 4 5

x=1

Floor=-1

Ceil=3
```

---

## Case 2

```text
x greater than every element

3 4 5

x=10

Floor=5

Ceil=-1
```

---

## Case 3

```text
Element exists

3 4 5

x=4

Floor=4

Ceil=4
```

---

# Complexity

## Time

```text
O(log N)
```

Two Binary Searches

```text
O(logN)+O(logN)

=

O(logN)
```

---

## Space

```text
O(1)
```

---

# Key Takeaways

- Floor means **largest value ≤ x**
- Ceil means **smallest value ≥ x**
- Floor searches toward the **right**
- Ceil searches toward the **left**
- Binary Search solves both efficiently

---

# Revision Template

```text
Floor

arr[mid] <= x

↓

Store answer

↓

Go RIGHT

-------------------------

Ceil

arr[mid] >= x

↓

Store answer

↓

Go LEFT
```

---

# Memory Trick

```text
Floor

↓

Go RIGHT

because we need the BIGGEST valid value

------------------------

Ceil

↓

Go LEFT

because we need the SMALLEST valid value
```

---

# Final Intuition

> Floor searches for the largest value not exceeding the target, while Ceil searches for the smallest value not less than the target—both are mirror-image Binary Search problems.