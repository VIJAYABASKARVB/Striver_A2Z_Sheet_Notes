# Set Matrix Zero

## Problem Statement

Given an `m x n` matrix, if an element is `0`, set its entire **row** and **column** to `0`.

Return the modified matrix.

---

## Examples

### Example 1

**Input**

```text
matrix = [[1,1,1],
          [1,0,1],
          [1,1,1]]
```

**Output**

```text
[[1,0,1],
 [0,0,0],
 [1,0,1]]
```

**Explanation**

The element at `(1,1)` is `0`, so its entire row and column become `0`.

---

### Example 2

**Input**

```text
matrix = [[0,1,2,0],
          [3,4,5,2],
          [1,3,1,5]]
```

**Output**

```text
[[0,0,0,0],
 [0,4,5,0],
 [0,3,1,0]]
```

**Explanation**

The zeros at `(0,0)` and `(0,3)` force the first row, first column, and fourth column to become zero.

---

# Core Idea

Whenever we find a zero, we must zero out:

- its entire row
- its entire column

There are three ways to solve this:

1. **Brute force** — mark affected cells directly
2. **Better** — use extra row and column arrays
3. **Optimal** — use the first row and first column as markers

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    for (int col = 0; col < n; col++) {
                        if (matrix[i][col] != 0)
                            matrix[i][col] = -1;
                    }

                    for (int row = 0; row < m; row++) {
                        if (matrix[row][j] != 0)
                            matrix[row][j] = -1;
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == -1)
                    matrix[i][j] = 0;
            }
        }
    }
};
```

## How It Works

- Scan the matrix.
- When a `0` is found, mark all non-zero values in that row and column as `-1`.
- In a second pass, convert all `-1` values to `0`.

## Complexity

- **Time:** `O((m*n)*(m+n))`
- **Space:** `O(1)`

---

# 2) Better Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        vector<int> row(m, 0);
        vector<int> col(n, 0);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (row[i] == 1 || col[j] == 1) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
```

## How It Works

- First pass: record which rows and columns contain zero.
- Second pass: set any cell to zero if its row or column was marked.

## Complexity

- **Time:** `O(m*n)`
- **Space:** `O(m+n)`

---

# 3) Optimal Approach — O(1) Space

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        bool firstRowZero = false;
        bool firstColZero = false;

        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowZero = true;
                break;
            }
        }

        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColZero = true;
                break;
            }
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        if (firstRowZero) {
            for (int j = 0; j < n; j++) {
                matrix[0][j] = 0;
            }
        }

        if (firstColZero) {
            for (int i = 0; i < m; i++) {
                matrix[i][0] = 0;
            }
        }
    }
};
```

---

## Main Idea

Use the **first row** and **first column** of the matrix as marker arrays.

If `matrix[i][j] == 0`, then:

- mark row `i` using `matrix[i][0]`
- mark column `j` using `matrix[0][j]`

This avoids extra space.

---

## Why We Need `firstRowZero` and `firstColZero`

The first row and first column are being reused as markers.

So we need separate flags to remember whether they originally contained any zero.

Otherwise, we could not tell whether to zero them out at the end.

---

## Visualization

For a matrix like this:

```text
[1, 1, 1]
[1, 0, 1]
[1, 1, 1]
```

The zero at `(1,1)` marks:

- row 1
- column 1

Using first row and first column:

```text
[1, 0, 1]
[0, 0, 1]
[1, 1, 1]
```

Then in the second pass, all marked rows and columns become zero.

---

# Dry Run

## Input

```text
matrix = [[1,1,1],
          [1,0,1],
          [1,1,1]]
```

### Step 1: Check first row and first column

- first row has no zero → `firstRowZero = false`
- first column has no zero → `firstColZero = false`

### Step 2: Mark rows and columns

At `(1,1)` we find a zero:

- `matrix[1][0] = 0`
- `matrix[0][1] = 0`

Matrix becomes:

```text
[1,0,1]
[0,0,1]
[1,1,1]
```

### Step 3: Fill inner cells using markers

Cells in row 1 or column 1 become zero:

```text
[1,0,1]
[0,0,0]
[1,0,1]
```

### Step 4: Handle first row and first column

No need, because both flags are false.

Final matrix:

```text
[[1,0,1],
 [0,0,0],
 [1,0,1]]
```

---

# Why This Works

Every zero needs its row and column zeroed.

Instead of storing that information in extra arrays, we store it inside the matrix itself using the first row and first column.

This makes the solution space-efficient.

---

# Complexity Analysis

## Brute Force
- **Time:** `O((m*n)*(m+n))`
- **Space:** `O(1)`

## Better Approach
- **Time:** `O(m*n)`
- **Space:** `O(m+n)`

## Optimal Approach
- **Time:** `O(m*n)`
- **Space:** `O(1)`

---

# Key Takeaways

- If a cell is `0`, its row and column must become `0`.
- Brute force directly marks cells.
- Better approach uses extra row and column arrays.
- Optimal approach reuses the first row and first column as markers.

---

# Revision Template

```text
1. Check whether first row or first column contains zero
2. Use first row and first column as markers
3. For every zero cell, mark its row and column
4. Update inner matrix cells using markers
5. Finally update first row and first column if needed
```

---

# Final Intuition

> Use the matrix itself as storage for row and column markers, and keep two flags to protect the original state of the first row and first column.