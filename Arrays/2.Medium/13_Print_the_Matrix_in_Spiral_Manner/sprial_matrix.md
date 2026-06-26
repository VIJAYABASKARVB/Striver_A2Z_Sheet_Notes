# 54. Spiral Matrix

## Problem Statement

Given an `m x n` matrix, return all elements of the matrix in **spiral order**.

---

## Examples

### Example 1

**Input**

```text
matrix = [[1,2,3],
          [4,5,6],
          [7,8,9]]
```

**Output**

```text
[1,2,3,6,9,8,7,4,5]
```

---

### Example 2

**Input**

```text
matrix = [[1,2,3,4],
          [5,6,7,8],
          [9,10,11,12]]
```

**Output**

```text
[1,2,3,4,8,12,11,10,9,5,6,7]
```

---

## Core Idea

We print the matrix layer by layer in this order:

1. top row
2. right column
3. bottom row
4. left column

To do this cleanly, we maintain four boundaries:

- `top`
- `bottom`
- `left`
- `right`

After finishing one layer, we move the boundaries inward.

---

## Optimal Solution

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to return matrix in spiral order
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;

        int top = 0;
        int bottom = matrix.size() - 1;
        int left = 0;
        int right = matrix[0].size() - 1;

        while(top <= bottom && left <= right) {

            // Traverse top row
            for(int i = left; i <= right; i++) {
                result.push_back(matrix[top][i]);
            }
            top++;

            // Traverse right column
            for(int i = top; i <= bottom; i++) {
                result.push_back(matrix[i][right]);
            }
            right--;

            // Traverse bottom row
            if(top <= bottom) {
                for(int i = right; i >= left; i--) {
                    result.push_back(matrix[bottom][i]);
                }
                bottom--;
            }

            // Traverse left column
            if(left <= right) {
                for(int i = bottom; i >= top; i--) {
                    result.push_back(matrix[i][left]);
                }
                left++;
            }
        }

        return result;
    }
};
```

---

## Why This Works

The matrix is processed in **concentric layers**.

For each layer:

- move left to right across the top
- move top to bottom down the right side
- move right to left across the bottom
- move bottom to top up the left side

Then shrink the boundaries and repeat.

---

## Boundary Meaning

```text
top    -> first unprocessed row from the top
bottom -> first unprocessed row from the bottom
left   -> first unprocessed column from the left
right  -> first unprocessed column from the right
```

---

## Visualization

For:

```text
1   2   3   4
5   6   7   8
9  10  11  12
13 14  15  16
```

### First layer

```text
1  2  3  4
            8
            12
16 15 14 13
```

Collected in order:

```text
1, 2, 3, 4, 8, 12, 16, 15, 14, 13
```

Then move inward and process the remaining submatrix.

---

## Dry Run

### Input

```text
matrix = [
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12],
  [13,14,15,16]
]
```

### Initial boundaries

```text
top = 0
bottom = 3
left = 0
right = 3
```

---

### Round 1

#### Top row
```text
1 2 3 4
```

#### Right column
```text
8 12 16
```

#### Bottom row
```text
15 14 13
```

#### Left column
```text
9 5
```

Result so far:

```text
[1,2,3,4,8,12,16,15,14,13,9,5]
```

Move boundaries inward:

```text
top = 1
bottom = 2
left = 1
right = 2
```

---

### Round 2

#### Top row
```text
6 7
```

#### Right column
```text
11
```

#### Bottom row
```text
10
```

Final result:

```text
[1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10]
```

---

## Important Edge Cases

We must check boundaries before traversing the bottom row and left column:

```cpp
if(top <= bottom)
if(left <= right)
```

This avoids duplicate traversal in:

- single row matrices
- single column matrices
- odd-sized matrices with a center element

---

## Complexity

- **Time:** `O(m * n)`
- **Space:** `O(m * n)` for the output array

---

## Key Takeaways

- Use four boundaries: `top`, `bottom`, `left`, `right`
- Traverse in spiral order layer by layer
- Shrink the boundaries after each side
- Check boundary conditions to avoid duplicates

---

## Revision Template

```text
1. Set top, bottom, left, right boundaries
2. Traverse top row
3. Traverse right column
4. Traverse bottom row if valid
5. Traverse left column if valid
6. Move boundaries inward
7. Repeat until boundaries cross
```

---

## Final Intuition

> Keep peeling the matrix layer by layer like an onion and collect elements in clockwise spiral order.