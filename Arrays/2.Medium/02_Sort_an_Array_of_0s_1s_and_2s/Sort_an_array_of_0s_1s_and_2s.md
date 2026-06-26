# Sort an Array of 0s, 1s and 2s

## Problem Statement

Given an array `nums` containing only `0`, `1`, and `2`, sort it in **non-decreasing order**.

The sorting must be done **in-place**.

---

## Examples

### Example 1

**Input:** `nums = [1, 0, 2, 1, 0]`
**Output:** `[0, 0, 1, 1, 2]`

### Example 2

**Input:** `nums = [0, 0, 1, 1, 1]`
**Output:** `[0, 0, 1, 1, 1]`

---

## Core Idea

Since the array contains only **three values**, we can solve it in two ways:

1. **Counting approach** — count how many `0`s, `1`s, and `2`s there are.
2. **Dutch National Flag algorithm** — sort in one pass using three pointers.

---

# 1) Brute Force / Counting Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void sortZeroOneTwo(vector<int>& nums) {
        int count0 = 0, count1 = 0, count2 = 0;

        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == 0) count0++;
            else if(nums[i] == 1) count1++;
            else count2++;
        }

        int index = 0;

        while(count0--) {
            nums[index++] = 0;
        }

        while(count1--) {
            nums[index++] = 1;
        }

        while(count2--) {
            nums[index++] = 2;
        }
    }
};
```

## How It Works

* Count the number of `0`s, `1`s, and `2`s.
* Overwrite the array in order:

  * first all `0`s
  * then all `1`s
  * then all `2`s

## Complexity

* **Time:** `O(n)`
* **Space:** `O(1)`

---

# 2) Optimal Approach — Dutch National Flag Algorithm

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void sortZeroOneTwo(vector<int>& nums) {
        int low = 0, mid = 0, high = nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[mid], nums[low]);
                mid++;
                low++;
            }
            else if (nums[mid] == 1) {
                mid++;
            }
            else {
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }
};
```

---

## What the Three Pointers Mean

### `low`

Marks the boundary where `0`s should go.

### `mid`

Scans the array and processes each element.

### `high`

Marks the boundary where `2`s should go.

---

## Partition Idea

At any moment, the array is divided into 4 parts:

```text
[ 0s region | 1s region | unknown region | 2s region ]
   0 ... low-1   low ... mid-1   mid ... high   high+1 ... end
```

### Invariant

* Everything before `low` is `0`
* Everything between `low` and `mid - 1` is `1`
* Everything after `high` is `2`
* Everything from `mid` to `high` is still unprocessed

---

# Why Each Case Works

## Case 1: `nums[mid] == 0`

We want `0` on the left side.

So:

* swap `nums[mid]` with `nums[low]`
* move both `low` and `mid` forward

Why move `mid` too?
Because after swapping, the element brought into `mid` came from the `low` side, which is already processed or safe to move past.

---

## Case 2: `nums[mid] == 1`

`1` belongs in the middle, so no swap is needed.
Just move `mid` forward.

---

## Case 3: `nums[mid] == 2`

We want `2` on the right side.

So:

* swap `nums[mid]` with `nums[high]`
* move `high` backward

Why not move `mid` here?
Because the value swapped in from `high` has not been processed yet.
We must inspect it again.

---

# Dry Run

## Example: `nums = [2, 0, 2, 1, 1, 0]`

Initial state:

```text
low = 0, mid = 0, high = 5
nums = [2, 0, 2, 1, 1, 0]
```

### Step 1

`nums[mid] = 2`

Swap `mid` and `high`:

```text
[0, 0, 2, 1, 1, 2]
```

Update:

* `high = 4`
* `mid = 0` stays

---

### Step 2

`nums[mid] = 0`

Swap `mid` and `low`:

```text
[0, 0, 2, 1, 1, 2]
```

Update:

* `low = 1`
* `mid = 1`

---

### Step 3

`nums[mid] = 0`

Swap `mid` and `low`:

```text
[0, 0, 2, 1, 1, 2]
```

Update:

* `low = 2`
* `mid = 2`

---

### Step 4

`nums[mid] = 2`

Swap `mid` and `high`:

```text
[0, 0, 1, 1, 2, 2]
```

Update:

* `high = 3`
* `mid = 2` stays

---

### Step 5

`nums[mid] = 1`

Move `mid` forward:

* `mid = 3`

---

### Step 6

`nums[mid] = 1`

Move `mid` forward:

* `mid = 4`

Now `mid > high`, so stop.

Final array:

```text
[0, 0, 1, 1, 2, 2]
```

---

# Why This Algorithm is Optimal

The counting approach is already `O(n)`, but it uses two passes:

* one pass to count
* one pass to rewrite

The Dutch National Flag algorithm sorts in **one pass** using only three pointers.

---

# Complexity

## Counting Approach

* **Time:** `O(n)`
* **Space:** `O(1)`

## Dutch National Flag Algorithm

* **Time:** `O(n)`
* **Space:** `O(1)`

---

# Key Takeaways

* This problem is a **3-value sorting problem**.
* Counting is simple and effective.
* Dutch National Flag is the standard optimal in-place solution.
* The array is divided into regions for `0`, `1`, `2`, and unknown elements.

---

# Revision Template

```text
1. Use low, mid, high pointers
2. If nums[mid] == 0, swap with low and move both
3. If nums[mid] == 1, move mid
4. If nums[mid] == 2, swap with high and move high only
5. Stop when mid > high
```

---

# Final Intuition

**Keep `0`s on the left, `2`s on the right, and let `1`s naturally settle in the middle while scanning once through the array.**
