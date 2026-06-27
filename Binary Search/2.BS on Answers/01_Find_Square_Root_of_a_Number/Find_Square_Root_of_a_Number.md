# Finding Square Root of a Number using Binary Search

---

# Problem Statement

Given a positive integer `n`, find its **square root**.

- If `n` is a perfect square, return its exact square root.
- Otherwise, return the **floor** of the square root (largest integer whose square is less than or equal to `n`).

---

# Examples

## Example 1

**Input**

```text
n = 36
```

**Output**

```text
6
```

---

## Example 2

**Input**

```text
n = 28
```

**Output**

```text
5
```

**Explanation**

```
√28 ≈ 5.29

Floor = 5
```

---

# Core Idea / Pattern Recognition

**Pattern**

```
Binary Search on Answer
```

### Why?

Instead of searching the square root directly, search for the **largest integer whose square is ≤ n**.

The search space is sorted:

```
1 2 3 4 5 6 ...

Squares

1 4 9 16 25 36 ...
```

If `mid²` is too large, move left.

If `mid²` is valid, store it as a possible answer and try a larger value.

---

# Observation

Suppose

```
n = 28
```

Possible answers

```
1 2 3 4 5 6 7 ...

Squares

1 4 9 16 25 36
```

Notice

```
25 <= 28

36 > 28
```

Therefore

```
√28

=

5
```

We only need the **largest valid square**.

---

# Approach 1 — Brute Force

## Idea

Check every number from `1` to `n`.

Keep updating the answer while `i² <= n`.

Stop once `i² > n`.

---

## Algorithm

1. Initialize `ans = 0`.
2. Traverse from `1` to `n`.
3. If `i² <= n`, update `ans`.
4. Otherwise, stop.
5. Return `ans`.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find floor of square root using linear search
    int floorSqrt(int n) {
        // Variable to store answer
        int ans = 0;

        // Run loop from 1 to n
        for (int i = 1; i <= n; i++) {
            // Check if i*i <= n
            if ((long long)i * i <= n) {
                // Update answer
                ans = i;
            } else {
                // Break when i*i > n
                break;
            }
        }
        // Return final answer
        return ans;
    }
};
```

---

## Visualization

```
n = 28

1² = 1 ✔

2² = 4 ✔

3² = 9 ✔

4² = 16 ✔

5² = 25 ✔

6² = 36 ✖
```

Answer

```
5
```

---

## Dry Run

```
ans = 0

1² <= 28

ans = 1

↓

2² <= 28

ans = 2

↓

...

↓

5² <= 28

ans = 5

↓

6² > 28

Stop
```

Return

```
5
```

---

## Complexity

**Time:** `O(√N)` *(or `O(N)` with the given loop bounds)*

**Space:** `O(1)`

> **Note:** Since the provided code loops up to `n` (breaking early), it effectively stops around `√n`, because that's where `i²` first exceeds `n`.

---

# Approach 2 — Optimal Approach

## Main Idea

Binary Search the answer.

If

```
mid² <= n
```

then `mid` is a valid answer.

Store it and search for a **larger** one.

Otherwise,

search the left half.

---

## Why It Works

We want the

```
Largest number

whose square

<= n
```

Example

```
n = 28
```

```
1 2 3 4 5 6

1 4 9 16 25 36
```

Everything before `5` is valid.

Everything after `5` is invalid.

This forms a **monotonic property**, making Binary Search applicable.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // This function returns the floor value of the square root of a number
    int mySqrt(int x) {
        // Handle small numbers directly
        if (x < 2) return x;

        // Initialize binary search range
        int left = 1, right = x / 2, ans = 0;

        // Perform binary search
        while (left <= right) {
            // Find middle point
            long long mid = left + (right - left) / 2;

            // Check if mid*mid is less than or equal to x
            if (mid * mid <= x) {
                // Store mid as potential answer
                ans = mid;
                // Move to right half
                left = mid + 1;
            } else {
                // Move to left half
                right = mid - 1;
            }
        }

        // Return final answer
        return ans;
    }
};
```

---

## Pointer Placement Visualization

Find √28

### Iteration 1

```
Search Space

1 ---------------- 14

        M

mid = 7

49 > 28
```

Move Left

```
right = 6
```

---

### Iteration 2

```
1 ------ 6

    M

mid = 3

9 <= 28
```

Valid answer

```
ans = 3

left = 4
```

---

### Iteration 3

```
4 --- 6

  M

mid = 5

25 <= 28
```

Better answer

```
ans = 5

left = 6
```

---

### Iteration 4

```
6

mid = 6

36 > 28
```

Move Left

```
right = 5
```

Now

```
left > right
```

Return

```
5
```

---

## Dry Run

Input

```
28
```

### Iteration 1

```
left=1

right=14

mid=7

49 > 28
```

```
right=6
```

---

### Iteration 2

```
left=1

right=6

mid=3

9 <= 28
```

```
ans=3

left=4
```

---

### Iteration 3

```
left=4

right=6

mid=5

25 <= 28
```

```
ans=5

left=6
```

---

### Iteration 4

```
left=6

right=6

mid=6

36 > 28
```

```
right=5
```

Loop ends.

Return

```
5
```

---

## Why `long long`?

Instead of

```cpp
mid * mid
```

using `int`, use

```cpp
long long mid
```

or

```cpp
(long long)mid * mid
```

to avoid integer overflow.

Example

```
mid = 50000

50000 × 50000

= 2,500,000,000
```

This exceeds the range of a 32-bit integer.

---

## Edge Cases

- `n = 0`
- `n = 1`
- Perfect square
- Non-perfect square
- Very large values (avoid overflow)

---

## Complexity

### Time

```
O(log N)
```

Binary Search halves the search space every iteration.

### Space

```
O(1)
```

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Linear Search | `O(√N)` *(given code breaks around √N)* | `O(1)` | Check every possible value |
| Binary Search | `O(log N)` | `O(1)` | Search on the answer |

---

# Key Takeaways

- Search on the **answer**, not the square root directly.
- If `mid² <= n`, store `mid` and search right.
- If `mid² > n`, search left.
- Always use `long long` while computing `mid * mid`.
- Return the last valid answer.

---

# Revision Template

1. Handle `n < 2`.
2. Binary Search from `1` to `n/2`.
3. Compute `mid`.
4. If `mid² <= n`, store `mid` and move right.
5. Else move left.
6. Return the stored answer.

---

# Memory Trick

```
mid² <= n ?

↓

YES

Save Answer

Go Right

↓

NO

Go Left
```

Remember:

> **"Keep the last valid square and keep searching for a bigger one."**

---

# Final Intuition

> Binary search the largest integer whose square is less than or equal to the given number, and that integer is the floor of the square root.