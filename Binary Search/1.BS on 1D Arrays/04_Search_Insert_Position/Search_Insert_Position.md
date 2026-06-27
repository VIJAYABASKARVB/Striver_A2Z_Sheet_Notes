# Search Insert Position

## Problem Statement

Given a **sorted array of distinct integers** and a target value `x`, return the index of `x`.

If `x` is **not present**, return the index where it should be inserted so that the array remains sorted.

---

## Examples

### Example 1

**Input**

```text
arr = [1,2,4,7]
x = 6
```

**Output**

```text
3
```

**Explanation**

`6` is not present.

If inserted at index `3`, the array becomes:

```text
[1,2,4,6,7]
```

which is still sorted.

---

### Example 2

**Input**

```text
arr = [1,2,4,7]
x = 2
```

**Output**

```text
1
```

**Explanation**

`2` already exists at index `1`.

---

## Core Idea

This problem is actually the **Lower Bound** problem.

We need the **first index** where

```text
arr[index] >= x
```

If:

- x already exists → return its index.
- x does not exist → return where it should be inserted.

That is exactly what **Lower Bound** returns.

---

# Pattern

```text
Binary Search
```

Specifically,

```text
Search Insert Position
        =
    Lower Bound
```

---

# Observation

Suppose

```text
arr = [1,2,4,7]
x = 6
```

The first element greater than or equal to `6` is

```text
7
```

located at index

```text
3
```

That is exactly where `6` should be inserted.

Similarly,

```text
arr = [1,2,4,7]
x = 2
```

The first element greater than or equal to `2` is

```text
2
```

located at index

```text
1
```

So answer = `1`.

---

# Optimal Approach (Binary Search)

## Code

```java
import java.util.*;

public class BinarySearchInsert {

    // Function to find the insert position of x in sorted array
    public int searchInsert(int[] arr, int x) {
        int n = arr.length;
        int low = 0, high = n - 1;
        int ans = n; // Default to end if x is greater than all elements

        while (low <= high) {
            int mid = (low + high) / 2;

            if (arr[mid] >= x) {
                // Potential answer found, try to go left
                ans = mid;
                high = mid - 1;
            } else {
                // Go right
                low = mid + 1;
            }
        }

        return ans;
    }
}
```

---

# Main Idea

We are looking for the **first position** where

```text
arr[mid] >= x
```

Whenever we find such an element,

it could be our answer,

but maybe there is another valid index on the left.

So,

- store it
- continue searching left

---

# Why This Works

Since the array is sorted,

every element before the lower bound is

```text
< x
```

and every possible answer satisfies

```text
>= x
```

Therefore Binary Search can eliminate half of the search space every iteration.

---

# Visualization

Suppose

```text
arr = [1,2,4,7]
x = 6
```

Array

```text
Index : 0 1 2 3
Value : 1 2 4 7
```

Need the first element

```text
>= 6
```

Answer

```text
7
```

at index

```text
3
```

Therefore

```text
Insert Position = 3
```

---

# Pointer Placement Visualization

### Initial

```text
Index : 0 1 2 3
Value : 1 2 4 7

L           H
      M
```

```
low = 0
high = 3
mid = 1
```

Current value

```text
arr[mid] = 2
```

Since

```text
2 < 6
```

Move right

```text
low = mid + 1
```

---

### Next

```text
Index : 0 1 2 3
Value : 1 2 4 7

        L   H
            M
```

```
low = 2
high = 3
mid = 2
```

Current value

```text
4
```

Still

```text
4 < 6
```

Move right

---

### Next

```text
Index : 0 1 2 3
Value : 1 2 4 7

            L
            H
            M
```

```
low = 3
high = 3
mid = 3
```

Current value

```text
7
```

Now

```text
7 >= 6
```

Possible answer

```text
ans = 3
```

Search left

```text
high = 2
```

Now

```text
low > high
```

Stop.

Return

```text
3
```

---

# Dry Run

## Input

```text
arr = [1,2,4,7]
x = 6
```

Initial

```text
low = 0
high = 3
ans = 4
```

---

### Iteration 1

```text
mid = 1
```

```
arr[mid] = 2
```

```
2 < 6
```

Move

```text
low = 2
```

---

### Iteration 2

```text
mid = 2
```

```
arr[mid] = 4
```

```
4 < 6
```

Move

```text
low = 3
```

---

### Iteration 3

```text
mid = 3
```

```
arr[mid] = 7
```

```
7 >= 6
```

Update

```text
ans = 3
```

Move

```text
high = 2
```

Loop ends.

Return

```text
3
```

---

# Another Dry Run

## Input

```text
arr = [1,2,4,7]
x = 2
```

Initial

```text
low = 0
high = 3
ans = 4
```

---

### Iteration 1

```text
mid = 1
```

```
arr[mid] = 2
```

Since

```text
2 >= 2
```

Update

```text
ans = 1
```

Search left

```text
high = 0
```

---

### Iteration 2

```text
mid = 0
```

```
arr[mid] = 1
```

```
1 < 2
```

Move right

```text
low = 1
```

Loop ends.

Answer

```text
1
```

---

# Why Initialize

```java
ans = n;
```

Consider

```text
arr = [1,2,4]
x = 10
```

No element is

```text
>= 10
```

Therefore the insertion position is

```text
3
```

which equals

```text
n
```

---

# Complexity

## Time

```text
O(log N)
```

Binary Search halves the search space every iteration.

---

## Space

```text
O(1)
```

Only constant extra space is used.

---

# Comparison with Lower Bound

| Search Insert Position | Lower Bound |
|-------------------------|-------------|
| Returns insertion index | Returns first index where `arr[i] >= x` |
| Same algorithm | Same algorithm |
| Same condition | `arr[mid] >= x` |
| Same complexity | `O(log N)` |

**Conclusion**

```text
Search Insert Position = Lower Bound
```

---

# Key Takeaways

- This problem is exactly **Lower Bound**.
- Find the first element that is **greater than or equal to x**.
- If `x` exists, return its index.
- If `x` doesn't exist, return the insertion position.
- Initialize `ans = n` to handle insertion at the end.

---

# Revision Template

```text
1. Initialize low = 0, high = n-1
2. Initialize ans = n
3. Find mid
4. If arr[mid] >= x
      ans = mid
      high = mid-1
5. Else
      low = mid+1
6. Return ans
```

---

# Memory Trick

```text
Search Insert Position

↓

Think

Lower Bound

↓

Find first element

>= target
```

---

# Final Intuition

> Search Insert Position is simply the Lower Bound problem—the answer is the first index where the array value becomes greater than or equal to the target.