# Find the Missing Number

## Problem Statement

Given an array `arr[]` of size **n - 1** containing **distinct integers** in the range `[1, n]`.

The array represents a permutation of numbers from `1` to `n` with exactly **one number missing**.

Find the missing number.

---

## Examples

### Example 1

**Input:** `arr[] = [8, 2, 4, 5, 3, 7, 1]`

**Output:** `6`

**Explanation:** Numbers from `1` to `8` are present except `6`.

### Example 2

**Input:** `arr[] = [1, 2, 3, 5]`

**Output:** `4`

**Explanation:** Range is `[1, 5]` and `4` is missing.

---

## Visual Representation

### Missing Number as a Gap

```text
Range :  1  2  3  4  5  6  7  8

Array : [8, 2, 4, 5, 3, 7, 1]

Present:
1 ✓
2 ✓
3 ✓
4 ✓
5 ✓
6 ✗
7 ✓
8 ✓

Missing Number = 6
```

### Sum Formula Idea

```text
Expected Sum (1..8)
= 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8
= 36

Actual Sum
= 8 + 2 + 4 + 5 + 3 + 7 + 1
= 30

Missing Number
= 36 - 30
= 6
```

---

## Approach Comparison

| Aspect | Hashing | Sum Formula |
|----------|----------|----------|
| Time Complexity | O(n) | O(n) |
| Space Complexity | O(n) | O(1) |
| Easy to Understand | Yes | Yes |
| Memory Efficient | No | Yes |

---

# 🔴 Brute Force Approach (Hashing)

## Idea

Use a boolean array to mark which numbers are present.

The number that remains unmarked is the missing number.

---

## C++ Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

int missingNum(vector<int>& arr) {

    int n = arr.size() + 1;

    vector<bool> present(n + 1, false);

    // Mark numbers present
    for (int num : arr) {
        present[num] = true;
    }

    // Find missing number
    for (int i = 1; i <= n; i++) {
        if (!present[i]) {
            return i;
        }
    }

    return -1;
}

int main() {

    vector<int> arr = {8, 2, 4, 5, 3, 7, 1};

    cout << missingNum(arr);

    return 0;
}
```

---

## Visual Flow

```text
n = 8

present array:

Index :
0 1 2 3 4 5 6 7 8

Value :
F F F F F F F F F

After marking:

0 T T T T T F T T

Only index 6 remains false.

Answer = 6
```

---

## Complexity

### Time Complexity

```text
O(n)
```

### Space Complexity

```text
O(n)
```

Extra boolean array is used.

---

# 🟢 Optimal Approach (Sum Formula)

## Idea

Use the formula:

```text
Sum of first n natural numbers

n × (n + 1)
-------------
      2
```

Subtract the array sum from the expected sum.

The difference is the missing number.

---

## C++ Code

```cpp
#include <iostream>
#include <vector>
using namespace std;

int missingNum(vector<int>& arr) {

    int n = arr.size() + 1;

    long long actualSum = 0;

    for (int num : arr) {
        actualSum += num;
    }

    long long expectedSum =
        (n * 1LL * (n + 1)) / 2;

    return expectedSum - actualSum;
}

int main() {

    vector<int> arr = {8, 2, 4, 5, 3, 7, 1};

    cout << missingNum(arr);

    return 0;
}
```

---

## Visual Flow

```text
Array:

[8, 2, 4, 5, 3, 7, 1]

n = 8

Expected Sum
= 8 × 9 / 2
= 36

Actual Sum
= 30

Missing
= 36 - 30

= 6
```

---

## Dry Run

### Input

```text
arr = [8, 2, 4, 5, 3, 7, 1]
```

| Step | Operation | Result |
|----------|----------|----------|
| 1 | n = arr.size() + 1 | 8 |
| 2 | Calculate actual sum | 30 |
| 3 | Calculate expected sum | 36 |
| 4 | expected - actual | 6 |

### Output

```text
6
```

---

## XOR Approach (Bonus Optimal Method)

### Idea

Properties of XOR:

```text
a ^ a = 0

a ^ 0 = a
```

Every number appears twice except the missing number.

All duplicate numbers cancel out.

---

## C++ Code

```cpp
int missingNum(vector<int>& arr) {

    int n = arr.size() + 1;

    int xorr = 0;

    for (int i = 1; i <= n; i++) {
        xorr ^= i;
    }

    for (int num : arr) {
        xorr ^= num;
    }

    return xorr;
}
```

---

## XOR Visualization

```text
Numbers from 1 to 5

1 ^ 2 ^ 3 ^ 4 ^ 5

Array

1 ^ 2 ^ 3 ^ 5

Combine

1 ^ 2 ^ 3 ^ 4 ^ 5
^
1 ^ 2 ^ 3 ^ 5

Pairs cancel

4 remains

Answer = 4
```

---

## Complexity Comparison

| Approach | Time | Space |
|----------|----------|----------|
| Hashing | O(n) | O(n) |
| Sum Formula | O(n) | O(1) |
| XOR | O(n) | O(1) |

---

## Edge Cases

| Case | Input | Output |
|----------|----------|----------|
| Missing First Number | `[2,3,4]` | `1` |
| Missing Last Number | `[1,2,3]` | `4` |
| Single Element | `[1]` | `2` |
| Large Input | `[1...n]` except one | Correct |
| Random Order | `[8,2,4,5,3,7,1]` | `6` |

---

## Key Takeaways

- Use **Hashing** when extra space is acceptable.
- Use **Sum Formula** for best simplicity and O(1) space.
- Use **XOR** when you want O(1) space without worrying about overflow.
- Array must contain:
  - Distinct elements
  - Numbers from `1` to `n`
  - Exactly one missing number

---

## Quick Revision

### Sum Formula

```cpp
missing =
(n * (n + 1)) / 2 - sum(arr);
```

### XOR Formula

```cpp
missing =
xor(1..n) ^ xor(arr);
```

### Complexities

```text
Hashing     -> O(n), O(n)

Sum Formula -> O(n), O(1)

XOR         -> O(n), O(1)
```

### Important

```cpp
long long expectedSum =
(n * 1LL * (n + 1)) / 2;
```

Use `long long` to avoid integer overflow.

---

## Visual Memory Aid

```text
Expected Sum
      -
Actual Sum
      =
Missing Number
```

Example:

```text
1 + 2 + 3 + 4 + 5 + 6 + 7 + 8
= 36

8 + 2 + 4 + 5 + 3 + 7 + 1
= 30

36 - 30

= 6
```

### One-Line Formula

```text
Missing Number =
n(n+1)/2 - sum(arr)
```