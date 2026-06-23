# Rotate Array by K Elements

## Problem Statement
Given an array of integers, rotate the array by `k` elements either left or right.

---

## Examples

### Example 1: Right Rotation

**Input:** `nums = [1, 2, 3, 4, 5, 6, 7], k = 2, right`

**Output:** `[6, 7, 1, 2, 3, 4, 5]`

**Explanation:**

- Rotate 1 step right: `[7, 1, 2, 3, 4, 5, 6]`
- Rotate 2 steps right: `[6, 7, 1, 2, 3, 4, 5]`

### Example 2: Left Rotation

**Input:** `nums = [1, 2, 3, 4, 5, 6], k = 2, left`

**Output:** `[3, 4, 5, 6, 1, 2]`

**Explanation:**

- Rotate 1 step left: `[2, 3, 4, 5, 6, 1]`
- Rotate 2 steps left: `[3, 4, 5, 6, 1, 2]`

---

## Visual Representation

### Right Rotation by K = 2

```text
Original Array:     [1, 2, 3, 4, 5, 6, 7]
                    ↓
Step 1 (1 right):   [7, 1, 2, 3, 4, 5, 6]
                    ↓
Step 2 (2 right):   [6, 7, 1, 2, 3, 4, 5]
```

### Left Rotation by K = 2

```text
Original Array:     [1, 2, 3, 4, 5, 6, 7]
                    ↓
Step 1 (1 left):    [2, 3, 4, 5, 6, 7, 1]
                    ↓
Step 2 (2 left):    [3, 4, 5, 6, 7, 1, 2]
```

---

## Approach Comparison

| Aspect | Brute Force | Optimal (Reverse) |
|----------|----------|----------|
| Space | O(k) | O(1) |
| Time | O(n) | O(n) |
| In Place | Yes | Yes |
| Best For | Understanding | Interviews / Production |

---

## Brute Force Approach

### Idea

1. Store the `k` elements in a temporary array.
2. Shift the remaining elements.
3. Copy the stored elements back.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotateRight(int arr[], int n, int k) {
        if (n == 0) return;

        k %= n;

        int temp[k];

        for (int i = n - k; i < n; i++) {
            temp[i - n + k] = arr[i];
        }

        for (int i = n - k - 1; i >= 0; i--) {
            arr[i + k] = arr[i];
        }

        for (int i = 0; i < k; i++) {
            arr[i] = temp[i];
        }
    }

    void rotateLeft(int arr[], int n, int k) {
        if (n == 0) return;

        k %= n;

        int temp[k];

        for (int i = 0; i < k; i++) {
            temp[i] = arr[i];
        }

        for (int i = k; i < n; i++) {
            arr[i - k] = arr[i];
        }

        for (int i = 0; i < k; i++) {
            arr[n - k + i] = temp[i];
        }
    }
};
```

### Visual Flow (Right Rotation)

```text
Step 1: Store last k elements
        temp = [6, 7]

Step 2: Shift remaining elements
        [1, 2, 3, 4, 5, _, _]
        →
        [_, _, 1, 2, 3, 4, 5]

Step 3: Copy temp to start
        [6, 7, 1, 2, 3, 4, 5]
```

### Complexity

- Time Complexity: **O(n)**
- Space Complexity: **O(k)**

---

## Optimal Approach (Reverse Method)

### Idea

For Right Rotation:

```text
Reverse All
→ Reverse First k
→ Reverse Last n-k
```

For Left Rotation:

```text
Reverse First k
→ Reverse Last n-k
→ Reverse All
```

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void reverseArray(vector<int>& nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);
            start++;
            end--;
        }
    }

    vector<int> rotateArray(vector<int>& nums, int k, string direction) {
        int n = nums.size();

        if (n == 0 || k == 0) return nums;

        k %= n;

        if (direction == "right") {

            reverseArray(nums, 0, n - 1);
            reverseArray(nums, 0, k - 1);
            reverseArray(nums, k, n - 1);

        } else if (direction == "left") {

            reverseArray(nums, 0, k - 1);
            reverseArray(nums, k, n - 1);
            reverseArray(nums, 0, n - 1);
        }

        return nums;
    }
};
```

---

## Reverse Method Explained

### Right Rotation (k = 2)

| Step | Operation | Array |
|----------|----------|----------|
| 0 | Initial | `[1,2,3,4,5,6,7]` |
| 1 | Reverse All | `[7,6,5,4,3,2,1]` |
| 2 | Reverse First 2 | `[6,7,5,4,3,2,1]` |
| 3 | Reverse Last 5 | `[6,7,1,2,3,4,5]` |

### Left Rotation (k = 2)

| Step | Operation | Array |
|----------|----------|----------|
| 0 | Initial | `[1,2,3,4,5,6,7]` |
| 1 | Reverse First 2 | `[2,1,3,4,5,6,7]` |
| 2 | Reverse Last 5 | `[2,1,7,6,5,4,3]` |
| 3 | Reverse All | `[3,4,5,6,7,1,2]` |

---

## Dry Run

### Input

```text
nums = [1,2,3,4,5,6,7]
k = 3
direction = right
```

| Step | Array |
|----------|----------|
| Initial | `[1,2,3,4,5,6,7]` |
| Reverse All | `[7,6,5,4,3,2,1]` |
| Reverse First 3 | `[5,6,7,4,3,2,1]` |
| Reverse Last 4 | `[5,6,7,1,2,3,4]` |
| Final | `[5,6,7,1,2,3,4]` |

---

## Edge Cases

| Case | Input | Output |
|----------|----------|----------|
| Empty Array | `[]` | `[]` |
| Single Element | `[5]` | `[5]` |
| k = 0 | `[1,2,3]` | `[1,2,3]` |
| k > n | `[1,2,3], k=5` | `[2,3,1]` |
| All Same | `[2,2,2,2]` | `[2,2,2,2]` |

---

## Key Takeaways

- Optimal solution uses **O(1)** extra space.
- Brute force uses **O(k)** extra space.
- Always normalize:

```cpp
k = k % n;
```

- Right Rotation:

```text
Reverse All
→ Reverse First k
→ Reverse Last n-k
```

- Left Rotation:

```text
Reverse First k
→ Reverse Last n-k
→ Reverse All
```

- Both approaches run in **O(n)** time.

---

## Quick Revision

1. Normalize `k`.
2. Right Rotation = `Reverse All → Reverse First k → Reverse Last n-k`
3. Left Rotation = `Reverse First k → Reverse Last n-k → Reverse All`
4. Brute Force Space = `O(k)`
5. Optimal Space = `O(1)`
6. Time Complexity = `O(n)`

---

## Visual Memory Aid

### Right Rotation ➡️

```text
[1,2,3,4,5,6,7]
        ↓
Reverse All
        ↓
[7,6,5,4,3,2,1]
        ↓
Reverse First 2
        ↓
[6,7,5,4,3,2,1]
        ↓
Reverse Last 5
        ↓
[6,7,1,2,3,4,5]
```

### Left Rotation ⬅️

```text
[1,2,3,4,5,6,7]
        ↓
Reverse First 2
        ↓
[2,1,3,4,5,6,7]
        ↓
Reverse Last 5
        ↓
[2,1,7,6,5,4,3]
        ↓
Reverse All
        ↓
[3,4,5,6,7,1,2]
```