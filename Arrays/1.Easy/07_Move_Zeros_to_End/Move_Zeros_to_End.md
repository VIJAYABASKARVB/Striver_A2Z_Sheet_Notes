# Move all Zeros to the End of the Array

## Problem Statement

You are given an array of integers. Your task is to move all the zeros in the array to the end and move all non-zero elements to the front while **maintaining their relative order**.

---

## Examples

### Example 1

**Input:** `[1, 0, 2, 3, 0, 4, 0, 1]`

**Output:** `[1, 2, 3, 4, 1, 0, 0, 0]`

**Explanation:** All zeros are moved to the end, while non-zero elements keep their original order.

### Example 2

**Input:** `[1, 2, 0, 1, 0, 4, 0]`

**Output:** `[1, 2, 1, 4, 0, 0, 0]`

**Explanation:** Non-zero elements `[1,2,1,4]` appear first, followed by all zeros.

---

## Visual Representation

### Before Moving

```text
Index:   0  1  2  3  4  5  6
Array:  [1, 0, 2, 3, 0, 4, 0]
        ↑        ↑     ↑
      Non-zero  Zero  Zero
```

### Step-by-Step (Optimal Two-Pointer)

```text
Initial:  [1, 0, 2, 3, 0, 4, 0]
           j  i
           (first zero at index 1)

Step 1:  i=2 (nums[2]=2 ≠ 0) → swap with j=1
         [1, 2, 0, 3, 0, 4, 0]
             j     i

Step 2:  i=3 (nums[3]=3 ≠ 0) → swap with j=2
         [1, 2, 3, 0, 0, 4, 0]
                j        i

Step 3:  i=5 (nums[5]=4 ≠ 0) → swap with j=3
         [1, 2, 3, 4, 0, 0, 0]
                   j        i

Final:   [1, 2, 3, 4, 0, 0, 0]
         All non-zeros first, then zeros
```

---

## Approach Comparison

| Aspect | Brute Force | Optimal (Two-Pointer) |
|----------|----------|----------|
| Space | O(n) | O(1) |
| Time | O(n) | O(n) |
| Modifies Original | Yes | Yes |
| Stable Order | Yes | Yes |
| Best For | Simplicity | Memory Efficiency |

---

## 🔴 Brute Force Approach

### Idea

Create a temporary array, copy all non-zero elements in order, then fill the remaining positions with zeros.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> moveZeroes(vector<int>& arr) {
        vector<int> temp(arr.size(), 0);
        int index = 0;

        // Copy non-zero elements
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] != 0) {
                temp[index] = arr[i];
                index++;
            }
        }

        // Copy temp back
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = temp[i];
        }

        return arr;
    }
};

int main() {
    vector<int> arr = {0, 1, 0, 3, 12};

    Solution sol;
    vector<int> result = sol.moveZeroes(arr);

    for (int num : result) {
        cout << num << " ";
    }

    return 0;
}
```

### Visual Flow

```text
arr:   [0, 1, 0, 3, 12]
          ↓ Copy Non-Zeros

temp:  [1, 3, 12, 0, 0]
          ↓ Copy Back

arr:   [1, 3, 12, 0, 0]
```

### Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(n)**

---

## 🟢 Optimal Approach (Two-Pointer)

### Idea

- Find the first zero.
- Let `j` point to that zero.
- Scan the remaining array using `i`.
- Whenever a non-zero element is found, swap it with `nums[j]`.
- Move `j` forward.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = -1;

        // Find first zero
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                j = i;
                break;
            }
        }

        // No zero found
        if (j == -1) return;

        for (int i = j + 1; i < nums.size(); i++) {
            if (nums[i] != 0) {
                swap(nums[i], nums[j]);
                j++;
            }
        }
    }
};

int main() {
    Solution sol;

    vector<int> nums = {0, 1, 0, 3, 12};

    sol.moveZeroes(nums);

    for (int num : nums) {
        cout << num << " ";
    }

    return 0;
}
```

### Step-by-Step Visual

```text
Input: [0, 1, 0, 3, 12]

j = 0 (first zero)

i = 1 → nums[1] = 1
Swap(1,0)

[1, 0, 0, 3, 12]
    j

i = 2 → nums[2] = 0
Skip

i = 3 → nums[3] = 3
Swap(3,1)

[1, 3, 0, 0, 12]
       j

i = 4 → nums[4] = 12
Swap(4,2)

[1, 3, 12, 0, 0]
           j

Final Answer:
[1, 3, 12, 0, 0]
```

### Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(1)**

---

## Dry Run Table

### Input

```text
[0, 1, 0, 3, 12]
```

| Step | i | nums[i] | j | Action | Array |
|----------|----------|----------|----------|----------|----------|
| 0 | - | - | -1 | Find first zero | `[0,1,0,3,12]` |
| 1 | 0 | 0 | 0 | First zero found | `[0,1,0,3,12]` |
| 2 | 1 | 1 | 0 | Swap | `[1,0,0,3,12]` |
| 3 | 2 | 0 | 1 | Skip | `[1,0,0,3,12]` |
| 4 | 3 | 3 | 1 | Swap | `[1,3,0,0,12]` |
| 5 | 4 | 12 | 2 | Swap | `[1,3,12,0,0]` |

---

## Edge Cases

| Case | Input | Output |
|----------|----------|----------|
| No zeros | `[1,2,3]` | `[1,2,3]` |
| All zeros | `[0,0,0]` | `[0,0,0]` |
| Single element | `[0]` | `[0]` |
| Zeros at end | `[1,2,0,0]` | `[1,2,0,0]` |
| Zeros at start | `[0,1,2,3]` | `[1,2,3,0]` |

---

## Key Takeaways

- Optimal solution uses **O(1)** extra space.
- Brute force uses **O(n)** extra space.
- Relative order of non-zero elements is preserved.
- `j` always points to the first zero in the processed portion.
- Whenever a non-zero element is found:
  
```cpp
swap(nums[i], nums[j]);
j++;
```

- This is a classic **Two Pointer Pattern**.

---

## Quick Revision

1. Find first zero.
2. Store its index in `j`.
3. Traverse using `i`.
4. If `nums[i] != 0`, swap with `nums[j]`.
5. Increment `j`.
6. Time = **O(n)**, Space = **O(1)**.

---

## Visual Memory Aid

```text
j = First Zero
i = Scanner

[0, 1, 0, 3, 12]
 ↑        ↑

Swap non-zero with j

↓

[1, 3, 12, 0, 0]

Non-Zeros → Left
Zeros     → Right
```

### Easy Memory Trick

```text
J = Zero Position
I = Scanner

If nums[i] is Non-Zero:
    Swap(i, j)
    j++

Think:
"Find a zero, replace it with the next non-zero."
```