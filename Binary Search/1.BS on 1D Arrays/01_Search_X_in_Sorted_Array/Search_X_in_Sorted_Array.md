# Binary Search

## Problem Statement

You are given a **sorted array of integers** and a **target** value.

Your task is to search for the target in the array and return its index.

Assume:

- the array is sorted in increasing order
- all numbers are distinct
- if the target is not present, return `-1`

---

## Example

### Input

```text
nums = [3, 4, 6, 7, 9, 12, 16, 17]
target = 6
```

### Output

```text
2
```

Because `6` is present at index `2`.

---

## Core Idea

Binary Search works only on a **sorted array**.

Instead of checking every element one by one, we repeatedly cut the search space in half.

At every step:

- find the middle element
- compare it with the target
- decide whether to search in the left half or the right half

This makes the algorithm very fast.

---

# Why Binary Search Works

Since the array is sorted:

- if `target > nums[mid]`, the target can only be in the **right half**
- if `target < nums[mid]`, the target can only be in the **left half**

So after every comparison, we throw away half of the array.

That is the entire power of binary search.

---

# Optimal Solution

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to perform Binary Search on sorted array
    int binarySearch(vector<int>& nums, int target) {
        int n = nums.size();
        int low = 0, high = n - 1;

        // Keep searching until low crosses high
        while (low <= high) {
            int mid = (low + high) / 2;

            if (nums[mid] == target) return mid;
            else if (target > nums[mid]) low = mid + 1;
            else high = mid - 1;
        }

        return -1;
    }
};

int main() {
    vector<int> a = {3, 4, 6, 7, 9, 12, 16, 17};
    int target = 6;

    Solution obj;
    int ind = obj.binarySearch(a, target);

    if (ind == -1) cout << "The target is not present." << endl;
    else cout << "The target is at index: " << ind << endl;

    return 0;
}
```

---

## Important Note

In the code above, the function should use:

```cpp
int binarySearch(vector<int>& nums, int target)
```

not:

```cpp
int binarySearch(vector& nums, int target)
```

because `vector` must include the element type.

---

# How It Works

We maintain two pointers:

- `low` → left boundary of search space
- `high` → right boundary of search space

Then:

1. compute the middle index
2. compare middle value with target
3. if equal, return the index
4. if target is larger, move `low` right
5. if target is smaller, move `high` left

---

# Visualization

Suppose:

```text
nums = [3, 4, 6, 7, 9, 12, 16, 17]
target = 6
```

Initial search space:

```text
low = 0
high = 7
```

Array:

```text
Index :  0  1  2  3  4  5  6  7
Value :  3  4  6  7  9 12 16 17
```

---

### Step 1

```text
low = 0
high = 7
mid = (0 + 7) / 2 = 3
nums[mid] = 7
```

Compare:

```text
6 < 7
```

So search in the **left half**.

New boundaries:

```text
low = 0
high = 2
```

---

### Step 2

```text
low = 0
high = 2
mid = (0 + 2) / 2 = 1
nums[mid] = 4
```

Compare:

```text
6 > 4
```

So search in the **right half**.

New boundaries:

```text
low = 2
high = 2
```

---

### Step 3

```text
low = 2
high = 2
mid = (2 + 2) / 2 = 2
nums[mid] = 6
```

Target found.

Return:

```text
2
```

---

# Dry Run

## Input

```text
nums = [3, 4, 6, 7, 9, 12, 16, 17]
target = 6
```

| Step | low | high | mid | nums[mid] | Action |
|------|----:|-----:|----:|----------:|--------|
| 1 | 0 | 7 | 3 | 7 | target < nums[mid], go left |
| 2 | 0 | 2 | 1 | 4 | target > nums[mid], go right |
| 3 | 2 | 2 | 2 | 6 | found |

Final answer:

```text
2
```

---

# Why `while (low <= high)`?

We continue searching as long as the search space is valid.

When:

```text
low > high
```

it means there are no elements left to check.

At that point, the target is not present.

---

# Why `mid = (low + high) / 2`?

This gives the middle index of the current search range.

However, in very large arrays, this can overflow in some languages.

A safer version is:

```cpp
int mid = low + (high - low) / 2;
```

This avoids overflow and is the preferred form.

---

# Complexity

## Time

```text
O(log n)
```

Because we cut the search space in half after each comparison.

## Space

```text
O(1)
```

No extra space is used.

---

# Key Takeaways

- Binary search works only on a sorted array.
- Compare the middle element with the target.
- If target is smaller, search left.
- If target is larger, search right.
- Repeat until found or search space becomes empty.

---

# Revision Template

```text
1. Set low = 0 and high = n - 1
2. While low <= high
3. Find mid
4. If nums[mid] == target, return mid
5. If target < nums[mid], move high left
6. If target > nums[mid], move low right
7. If not found, return -1
```

---

# Final Intuition

> Binary search keeps cutting the sorted array into half until the target is found or the search space becomes empty.