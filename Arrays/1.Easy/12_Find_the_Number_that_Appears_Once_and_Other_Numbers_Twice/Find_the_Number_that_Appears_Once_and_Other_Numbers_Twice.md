# Find the Number That Appears Once (Others Twice)

## Problem Statement

Given a **non-empty** array of integers `arr`, every element appears **exactly twice** except for one element that appears **only once**.

Return the element that appears only once.

---

## Examples

### Example 1

**Input:**

```text
arr = [2, 2, 1]
```

**Output:**

```text
1
```

**Explanation:**

```text
2 appears twice
1 appears once

Answer = 1
```

---

### Example 2

**Input:**

```text
arr = [4, 1, 2, 1, 2]
```

**Output:**

```text
4
```

**Explanation:**

```text
1 appears twice
2 appears twice
4 appears once

Answer = 4
```

---

## Visual Representation

### XOR Magic

Important XOR Properties:

```text
a ^ a = 0

a ^ 0 = a

XOR is Commutative:
a ^ b = b ^ a

XOR is Associative:
(a ^ b) ^ c = a ^ (b ^ c)
```

---

### Example

```text
arr = [4, 1, 2, 1, 2]

4 ^ 1 ^ 2 ^ 1 ^ 2

= 4 ^ (1 ^ 1) ^ (2 ^ 2)

= 4 ^ 0 ^ 0

= 4
```

Answer:

```text
4
```

---

## Cancellation Visualization

```text
Array:

[4, 1, 2, 1, 2]

Pairs:

(1,1) -> Cancel
(2,2) -> Cancel

Remaining:

4
```

---

## Approach Comparison

| Approach | Time | Space |
|-----------|-----------|-----------|
| Brute Force | O(n²) | O(1) |
| Hash Array | O(n) | O(max element) |
| XOR | O(n) | O(1) |

---

# 🔴 Brute Force Approach

## Idea

For every element:

- Count how many times it appears.
- If count becomes `1`, return that element.

---

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int getSingleElement(vector<int>& arr) {

        int n = arr.size();

        for(int i = 0; i < n; i++) {

            int num = arr[i];
            int cnt = 0;

            for(int j = 0; j < n; j++) {

                if(arr[j] == num)
                    cnt++;
            }

            if(cnt == 1)
                return num;
        }

        return -1;
    }
};

int main() {

    vector<int> arr = {4,1,2,1,2};

    Solution obj;

    cout << obj.getSingleElement(arr);

    return 0;
}
```

---

## Visual Flow

```text
arr = [4,1,2,1,2]

Check 4

Count(4) = 1

Return 4
```

---

## Complexity

```text
Time  : O(n²)

Space : O(1)
```

---

# 🟡 Better Approach (Hash Array)

## Idea

Store the frequency of every number.

Then find the element whose frequency is `1`.

---

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int getSingleElement(vector<int>& arr) {

        int n = arr.size();

        int maxi = arr[0];

        for(int i = 0; i < n; i++) {
            maxi = max(maxi, arr[i]);
        }

        vector<int> hash(maxi + 1, 0);

        for(int i = 0; i < n; i++) {
            hash[arr[i]]++;
        }

        for(int i = 0; i < n; i++) {

            if(hash[arr[i]] == 1)
                return arr[i];
        }

        return -1;
    }
};
```

---

## Visual Flow

```text
arr = [4,1,2,1,2]

Frequency Array

Number : Frequency

1 -> 2

2 -> 2

4 -> 1

Frequency 1 found

Answer = 4
```

---

## Complexity

```text
Time  : O(n)

Space : O(max element)
```

---

# 🟢 Optimal Approach (XOR)

## Idea

Use XOR on all elements.

Because:

```text
a ^ a = 0
```

All duplicate elements cancel out.

Only the single element remains.

---

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int getSingleElement(vector<int>& arr) {

        int xorr = 0;

        for(int num : arr) {
            xorr ^= num;
        }

        return xorr;
    }
};

int main() {

    vector<int> arr = {4,1,2,1,2};

    Solution obj;

    cout << obj.getSingleElement(arr);

    return 0;
}
```

---

## XOR Dry Run

### Input

```text
arr = [4,1,2,1,2]
```

| Step | Current Number | XOR Before | XOR After |
|--------|--------|--------|--------|
| 1 | 4 | 0 | 4 |
| 2 | 1 | 4 | 5 |
| 3 | 2 | 5 | 7 |
| 4 | 1 | 7 | 6 |
| 5 | 2 | 6 | 4 |

Final Answer:

```text
4
```

---

## XOR Visualization

```text
0 ^ 4 = 4

4 ^ 1 = 5

5 ^ 2 = 7

7 ^ 1 = 6

6 ^ 2 = 4
```

Result:

```text
4
```

---

## Why XOR Works

```text
4 ^ 1 ^ 2 ^ 1 ^ 2

= 4 ^ (1 ^ 1) ^ (2 ^ 2)

= 4 ^ 0 ^ 0

= 4
```

All duplicate elements become:

```text
0
```

Only the unique element remains.

---

## Complexity Comparison

| Approach | Time | Space |
|-----------|-----------|-----------|
| Brute Force | O(n²) | O(1) |
| Hash Array | O(n) | O(max element) |
| XOR | O(n) | O(1) |

---

## Edge Cases

| Case | Input | Output |
|-----------|-----------|-----------|
| Single Element | `[5]` | `5` |
| Negative Numbers | `[-1,-1,5]` | `5` |
| Large Numbers | `[100000,100000,1]` | `1` |
| Unique At Beginning | `[4,1,1,2,2]` | `4` |
| Unique At End | `[1,1,2,2,4]` | `4` |

---

## Key Takeaways

- XOR is the optimal solution.
- Duplicate elements cancel each other.
- Works for both positive and negative integers.
- Requires no extra memory.
- Most frequently asked interview solution.

---

## Quick Revision

### XOR Properties

```text
a ^ a = 0

a ^ 0 = a
```

### Core Logic

```cpp
int xorr = 0;

for(int num : arr) {
    xorr ^= num;
}

return xorr;
```

### Complexity

```text
Time  = O(n)

Space = O(1)
```

---

## Visual Memory Aid

```text
[4,1,2,1,2]

↓

4 ^ 1 ^ 2 ^ 1 ^ 2

↓

4 ^ (1^1) ^ (2^2)

↓

4 ^ 0 ^ 0

↓

4
```

### Easy Trick

```text
Same numbers destroy each other.

Only the lonely number survives.
```

---

## Pattern Recognition

This problem belongs to:

```text
Bit Manipulation Pattern
```

Common XOR-Based Problems:

- Single Number
- Missing Number
- Find Two Unique Numbers
- XOR of Range
- XOR Queries