# Rotate Image by 90 Degrees Clockwise

## Problem Statement

Given an `N x N` 2D integer matrix, rotate it by **90 degrees clockwise**.

The rotation must be done **in-place**, meaning the original matrix must be modified directly.

---

## Examples

### Example 1

**Input**

```text
matrix = [
  [1, 2, 3],
  [4, 5, 6],
  [7, 8, 9]
]
```

**Output**

```text
matrix = [
  [7, 4, 1],
  [8, 5, 2],
  [9, 6, 3]
]
```

**Explanation**

First transpose the matrix, then reverse each row.

---

### Example 2

**Input**

```text
matrix = [
  [0, 1, 1, 2],
  [2, 0, 3, 1],
  [4, 5, 0, 5],
  [5, 6, 7, 0]
]
```

**Output**

```text
matrix = [
  [5, 4, 2, 0],
  [6, 5, 0, 1],
  [7, 0, 3, 1],
  [0, 5, 1, 2]
]
```

---

# Core Idea

A 90° clockwise rotation can be done in two steps:

1. **Transpose the matrix**
2. **Reverse each row**

This works because transposing swaps rows with columns, and reversing each row moves the elements into their rotated positions.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to rotate the matrix 90 degrees clockwise using extra space
    vector<vector<int>> rotateClockwise(vector<vector<int>>& matrix) {
        int n = matrix.size();

        vector<vector<int>> rotated(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                rotated[j][n - i - 1] = matrix[i][j];
            }
        }

        return rotated;
    }
};
```

## How It Works

For every element `matrix[i][j]`, place it in its rotated position:

```text
rotated[j][n - i - 1] = matrix[i][j]
```

This directly builds a new rotated matrix.

## Complexity

- **Time:** `O(N^2)`
- **Space:** `O(N^2)`

---

# 2) Optimal Approach — In-Place Rotation

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to rotate matrix 90 degrees clockwise in-place
    void rotateClockwise(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Step 1: Transpose the matrix
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: Reverse each row
        for (int i = 0; i < n; ++i) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
```

---

## Why This Works

### Step 1: Transpose
Transpose means:

```text
matrix[i][j] ↔ matrix[j][i]
```

So rows become columns.

For example:

```text
Original:
1 2 3
4 5 6
7 8 9

Transpose:
1 4 7
2 5 8
3 6 9
```

### Step 2: Reverse Each Row
Now reverse every row:

```text
1 4 7   ->   7 4 1
2 5 8   ->   8 5 2
3 6 9   ->   9 6 3
```

That gives the matrix rotated 90° clockwise.

---

# Visualization

## Original Matrix

```text
1 2 3
4 5 6
7 8 9
```

## After Transpose

```text
1 4 7
2 5 8
3 6 9
```

## After Reversing Each Row

```text
7 4 1
8 5 2
9 6 3
```

---

# Dry Run

## Input

```text
matrix = [
  [1, 2, 3],
  [4, 5, 6],
  [7, 8, 9]
]
```

### Step 1: Transpose

Swap `matrix[i][j]` with `matrix[j][i]` for `j > i`.

Result:

```text
[
  [1, 4, 7],
  [2, 5, 8],
  [3, 6, 9]
]
```

### Step 2: Reverse Each Row

Reverse row 0:

```text
[1, 4, 7] -> [7, 4, 1]
```

Reverse row 1:

```text
[2, 5, 8] -> [8, 5, 2]
```

Reverse row 2:

```text
[3, 6, 9] -> [9, 6, 3]
```

Final matrix:

```text
[
  [7, 4, 1],
  [8, 5, 2],
  [9, 6, 3]
]
```

---

# Why the Optimal Approach is Better

The brute force solution uses extra space to build a new matrix.

The optimal solution modifies the matrix directly using:

- transpose
- row reversal

So it satisfies the in-place requirement.

---

# Complexity

## Brute Force
- **Time:** `O(N^2)`
- **Space:** `O(N^2)`

## Optimal Approach
- **Time:** `O(N^2)`
- **Space:** `O(1)`

---

# Key Takeaways

- A 90° clockwise rotation can be done by:
  1. transposing the matrix
  2. reversing each row
- This is the standard in-place trick for matrix rotation.
- The rotated position of an element can also be written as:
  
```text
rotated[j][n - i - 1] = matrix[i][j]
```

---

# Revision Template

```text
1. Transpose the matrix
2. Reverse each row
3. Done
```

---

# Final Intuition

> Rotate the matrix by first turning rows into columns, then flipping each row horizontally.