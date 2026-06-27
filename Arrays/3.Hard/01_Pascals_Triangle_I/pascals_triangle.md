# Pascal's Triangle

## Problem Statement

Pascal’s Triangle is a triangular arrangement of numbers where:

- the **first and last element** of every row is `1`
- every inner element is the **sum of the two elements directly above it**

This problem usually has three variants:

1. **Generate the first N rows**
2. **Generate the N-th row**
3. **Find the element at position (r, c)**

---

## Example

### First 5 rows of Pascal’s Triangle

```text
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
```

### Example Element

For `r = 5`, `c = 3`:

```text
Element = 6
```

---

# Core Idea

Pascal’s Triangle follows the binomial coefficient pattern:

```text
Row r contains:
C(r-1, 0), C(r-1, 1), C(r-1, 2), ..., C(r-1, r-1)
```

So:

- the **entire triangle** can be built row by row
- the **Nth row** can be built using combinatorics
- the **element at (r, c)** is:

```text
C(r-1, c-1)
```

---

# 1) Generate the Entire Pascal’s Triangle

## Idea

To build each row:

- first and last elements are always `1`
- every middle element is:

```text
previous_row[j-1] + previous_row[j]
```

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class containing Pascal's Triangle generation logic
class Solution {
public:
    // Function to generate Pascal's Triangle up to numRows
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> triangle;

        for (int i = 0; i < numRows; i++) {
            vector<int> row(i + 1, 1);

            for (int j = 1; j < i; j++) {
                row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }

            triangle.push_back(row);
        }

        return triangle;
    }
};

int main() {
    Solution obj;
    int n = 5;

    vector<vector<int>> result = obj.generate(n);
    for (auto &row : result) {
        for (auto &val : row) cout << val << " ";
        cout << endl;
    }
}
```

---

## How It Works

For each row `i`:

- create a row of size `i + 1`
- fill all values with `1`
- update only the middle elements using the previous row

Example:

- Row 1: `1`
- Row 2: `1 1`
- Row 3: `1 2 1`
- Row 4: `1 3 3 1`

---

## Dry Run

### Input: `N = 5`

We build row by row:

### Row 0
```text
1
```

### Row 1
```text
1 1
```

### Row 2
Middle value:

```text
1 + 1 = 2
```

Row:
```text
1 2 1
```

### Row 3
Middle values:

```text
1 + 2 = 3
2 + 1 = 3
```

Row:
```text
1 3 3 1
```

### Row 4
Middle values:

```text
1 + 3 = 4
3 + 3 = 6
3 + 1 = 4
```

Row:
```text
1 4 6 4 1
```

---

## Complexity

- **Time:** `O(N^2)`
- **Space:** `O(N^2)` for storing all rows

---

# 2) Generate the N-th Row of Pascal’s Triangle

## Idea

The N-th row contains binomial coefficients:

```text
C(N-1, 0), C(N-1, 1), ..., C(N-1, N-1)
```

Instead of using factorials, we use the recurrence:

```text
C(n, k) = C(n, k-1) * (n-k+1) / k
```

This lets us compute each value in constant time.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class containing Pascal's Triangle row generation logic
class Solution {
public:
    // Function to generate the Nth row of Pascal's Triangle
    vector<long long> getNthRow(int N) {
        vector<long long> row;

        long long val = 1;
        row.push_back(val);

        for (int k = 1; k < N; k++) {
            val = val * (N - k) / k;
            row.push_back(val);
        }

        return row;
    }
};

int main() {
    int N = 5;
    Solution sol;
    vector<long long> result = sol.getNthRow(N);

    for (auto num : result) {
        cout << num << " ";
    }
    return 0;
}
```

---

## How It Works

Start with:

```text
1
```

Then compute the next values one by one using the previous value.

For `N = 5`, the 5th row is:

```text
1 4 6 4 1
```

---

## Dry Run

### Input: `N = 5`

We compute row values:

- Start: `1`
- Next:
  ```text
  1 * (5 - 1) / 1 = 4
  ```
- Next:
  ```text
  4 * (5 - 2) / 2 = 6
  ```
- Next:
  ```text
  6 * (5 - 3) / 3 = 4
  ```
- Next:
  ```text
  4 * (5 - 4) / 4 = 1
  ```

Final row:

```text
1 4 6 4 1
```

---

## Complexity

- **Time:** `O(N)`
- **Space:** `O(N)`

---

# 3) Find the Element at Position (r, c)

## Idea

The element at position `(r, c)` is:

```text
C(r-1, c-1)
```

We compute it directly using the iterative binomial formula.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Solution class to find the (r, c) element of Pascal's Triangle
class Solution {
public:
    // Function to compute binomial coefficient (nCr)
    long long findPascalElement(int r, int c) {
        int n = r - 1;
        int k = c - 1;

        long long result = 1;

        for (int i = 0; i < k; i++) {
            result *= (n - i);
            result /= (i + 1);
        }

        return result;
    }
};

int main() {
    Solution sol;
    int r = 5, c = 3;
    cout << sol.findPascalElement(r, c);
    return 0;
}
```

---

## How It Works

For position `(r, c)`:

- convert it to binomial form:
  ```text
  C(r-1, c-1)
  ```
- compute it iteratively without factorials

Example:

```text
r = 5, c = 3
```

So:

```text
C(4, 2) = 6
```

---

## Dry Run

### Input: `r = 5, c = 3`

We compute:

```text
n = 4
k = 2
```

Start:

```text
result = 1
```

Iteration 1:

```text
result = 1 * 4 / 1 = 4
```

Iteration 2:

```text
result = 4 * 3 / 2 = 6
```

Final answer:

```text
6
```

---

## Complexity

- **Time:** `O(c)`
- **Space:** `O(1)`

---

# Why These Three Variants Are Related

All three are based on the same Pascal property:

```text
Each inner number is the sum of the two numbers above it.
```

And the combinatorial identity:

```text
Pascal value at row r, col c = C(r-1, c-1)
```

So:

- **generate triangle** → build all rows
- **Nth row** → compute one full row using binomial coefficients
- **(r, c) element** → compute one specific value directly

---

# Key Takeaways

- First and last elements of every row are `1`
- Inner values come from the two values above them
- Entire triangle can be built row by row
- N-th row can be generated using binomial coefficients
- A single element can be found using `C(r-1, c-1)`

---

# Revision Template

```text
1. First and last values are always 1
2. Each middle value = top-left + top-right
3. Nth row = C(N-1, k) for k = 0 to N-1
4. Element at (r, c) = C(r-1, c-1)
5. Use iterative formula to avoid factorials
```

---

# Final Intuition

> Pascal’s Triangle is just binomial coefficients arranged row by row, where every number is built from the two numbers above it.