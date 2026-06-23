# Left Rotate the Array by One

## Problem Statement

Given an integer array `nums`, rotate the array to the left by one position.

**Note:** No need to return anything, just modify the given array in-place.

---

## Examples

### Example 1:

**Input:** `nums = [1, 2, 3, 4, 5]`
**Output:** `[2, 3, 4, 5, 1]`

**Explanation:** Rotating once to the left means the first element moves to the end, and all other elements shift one position left.

### Example 2:

**Input:** `nums = [-1, 0, 3, 6]`
**Output:** `[0, 3, 6, -1]`

**Explanation:** The first element `-1` moves to the end, others shift left.

---

## Visual Representation

### Before Rotation

```text
Index:     0    1    2    3    4
Array:    [1]  [2]  [3]  [4]  [5]
            ↑
         (Stored in temp)
```

### Step-by-Step Shift

```text
Step 1: Move element at index 1 to index 0
         [2]  [2]  [3]  [4]  [5]

Step 2: Move element at index 2 to index 1
         [2]  [3]  [3]  [4]  [5]

Step 3: Move element at index 3 to index 2
         [2]  [3]  [4]  [4]  [5]

Step 4: Move element at index 4 to index 3
         [2]  [3]  [4]  [5]  [5]

Step 5: Place temp (original first element) at the end
         [2]  [3]  [4]  [5]  [1]
```

### Final Array

```text
Index:     0    1    2    3    4
Array:    [2]  [3]  [4]  [5]  [1]
```

---

## Approach Comparison

| Aspect            | Brute Force        | Optimal           |
| ----------------- | ------------------ | ----------------- |
| Space             | O(n) - Extra array | O(1) - In-place   |
| Time              | O(n)               | O(n)              |
| Modifies Original | ❌                  | ✅                 |
| Best For          | Simplicity         | Memory Efficiency |

---

## Code Solutions

### 🔴 Brute Force Approach

**Idea:** Use a temporary array to store shifted elements.

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(int arr[], int n) {
    int temp[n];

    for (int i = 1; i < n; i++) {
        temp[i - 1] = arr[i];
    }

    temp[n - 1] = arr[0];

    for (int i = 0; i < n; i++) {
        cout << temp[i] << " ";
    }

    cout << endl;
}

int main() {
    int n = 5;
    int arr[] = {1, 2, 3, 4, 5};

    solve(arr, n);

    return 0;
}
```

### Visual Flow

```text
Original: [1, 2, 3, 4, 5]
              ↓
  temp:   [2, 3, 4, 5, 1]
              ↓
Output:  [2, 3, 4, 5, 1]
```

**Time Complexity:** `O(n)`
**Space Complexity:** `O(n)`

---

### 🟢 Optimal Approach (In-Place)

**Idea:** Store the first element, shift everything left, then place the stored value at the end.

```cpp
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotateArrayByOne(vector<int>& nums) {

        int temp = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            nums[i - 1] = nums[i];
        }

        nums[nums.size() - 1] = temp;
    }
};

int main() {

    Solution solution;

    vector<int> nums = {1, 2, 3, 4, 5};

    solution.rotateArrayByOne(nums);

    for (int num : nums) {
        cout << num << " ";
    }

    return 0;
}
```

### Visual Flow

```text
Step 1: Store first element

temp = [1]

Array: [1, 2, 3, 4, 5]
         ↑

Step 2: Shift left

[1, 2, 3, 4, 5]
   ↓  ↓  ↓  ↓

[2, 3, 4, 5, 5]

Step 3: Place temp at end

[2, 3, 4, 5, 1]
            ↑
           temp
```

**Time Complexity:** `O(n)`
**Space Complexity:** `O(1)`

---

## Dry Run

### Input

```text
[1, 2, 3, 4, 5]
```

| Step | Operation              | Array State       |
| ---- | ---------------------- | ----------------- |
| 0    | Initial                | `[1, 2, 3, 4, 5]` |
| 1    | Store `temp = nums[0]` | `temp = 1`        |
| 2    | `nums[0] = nums[1]`    | `[2, 2, 3, 4, 5]` |
| 3    | `nums[1] = nums[2]`    | `[2, 3, 3, 4, 5]` |
| 4    | `nums[2] = nums[3]`    | `[2, 3, 4, 4, 5]` |
| 5    | `nums[3] = nums[4]`    | `[2, 3, 4, 5, 5]` |
| 6    | `nums[4] = temp`       | `[2, 3, 4, 5, 1]` |

---

## Key Takeaways

* ✅ Optimal approach uses **O(1)** extra space.
* ✅ Brute force approach uses **O(n)** extra space.
* ✅ Both approaches require **O(n)** time.
* 💡 Pattern: **Store → Shift → Place Back**
* 🔑 Always save the first element before shifting.

---

## Edge Cases

| Case             | Input           | Output                     |
| ---------------- | --------------- | -------------------------- |
| Single Element   | `[5]`           | `[5]`                      |
| Two Elements     | `[1, 2]`        | `[2, 1]`                   |
| Negative Numbers | `[-1, 0, 3, 6]` | `[0, 3, 6, -1]`            |
| Large Array      | `[1...100]`     | First element moves to end |

---

## Quick Revision Points

1. Brute Force → Extra array → `O(n)` space
2. Optimal → Single temp variable → `O(1)` space
3. Shift using:

```cpp
arr[i - 1] = arr[i];
```

4. Final step:

```cpp
arr[n - 1] = temp;
```

5. Never forget to store the first element before shifting.
