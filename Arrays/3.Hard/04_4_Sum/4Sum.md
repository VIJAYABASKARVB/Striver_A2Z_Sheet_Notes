# 4 Sum | Find Quads That Add Up to a Target Value

## Problem Statement

Given an array of `N` integers, find all **unique quadruplets** `[arr[a], arr[b], arr[c], arr[d]]` such that:

```text
arr[a] + arr[b] + arr[c] + arr[d] = target
```

The indices `a, b, c, d` must all be distinct.

Return the list of unique quadruplets in any order.

---

## Examples

### Example 1

**Input:** `arr = [1,0,-1,0,-2,2]`, `target = 0`
**Output:** `[-2,-1,1,2], [-2,0,0,2], [-1,0,0,1]`

### Example 2

**Input:** `arr = [4,3,3,4,4,2,1,2,1,1]`, `target = 9`
**Output:** `[1,1,3,4], [1,2,2,4], [1,2,3,3]`

---

## Core Idea

This is a direct extension of **2 Sum** and **3 Sum**.

We need to find four numbers whose total sum is equal to the target.

There are three ways to solve it:

1. **Brute Force**
2. **Better Approach**
3. **Optimal Approach**

The optimal solution uses:

* sorting
* two fixed loops
* two pointers for the remaining two numbers

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& arr, int target) {
        int n = arr.size();
        set<vector<int>> st;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        long long sum = (long long)arr[i] + arr[j] + arr[k] + arr[l];
                        if (sum == target) {
                            vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
                            sort(temp.begin(), temp.end());
                            st.insert(temp);
                        }
                    }
                }
            }
        }

        return vector<vector<int>>(st.begin(), st.end());
    }
};
```

## How It Works

* Check every possible quadruplet.
* If its sum matches the target, sort it and store it in a set.
* The set removes duplicate quadruplets.

## Why Sorting the Quadruplet Helps

A quadruplet like:

```text
[1, 0, -1, 0]
```

is the same as:

```text
[0, 1, 0, -1]
```

Sorting normalizes all such permutations into the same representation.

## Complexity

* **Time:** `O(n^4 log m)`
* **Space:** `O(m)`

where `m` is the number of unique quadruplets.

---

# 2) Better Approach — Fix Two, Search Two with Hash Set

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& arr, int target) {
        int n = arr.size();
        set<vector<int>> st;  

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                unordered_set<int> seen;

                for (int k = j + 1; k < n; k++) {
                    long long required = (long long)target - arr[i] - arr[j] - arr[k];

                    if (seen.count(required)) {
                        vector<int> temp = {arr[i], arr[j], arr[k], (int)required};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }

                    seen.insert(arr[k]);
                }
            }
        }

        return vector<vector<int>>(st.begin(), st.end());
    }
};
```

## How It Works

For every pair `(i, j)`:

* we need two more numbers whose sum is:

```text
required = target - arr[i] - arr[j]
```

Then we use a hash set to detect whether the required fourth number has appeared before.

## Why It Is Better Than Brute Force

Instead of checking all possible fourth indices explicitly, we use set lookup to see if the complement exists.

This reduces one nested loop’s work.

## Complexity

* **Time:** `O(n^3)` average with hashing, plus set insertion overhead for duplicates
* **Space:** `O(n)`

---

# 3) Optimal Approach — Sorting + Two Pointers

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& arr, int target) {
        int n = arr.size();
        vector<vector<int>> ans;

        sort(arr.begin(), arr.end());

        for (int i = 0; i < n; i++) {
            if (i > 0 && arr[i] == arr[i - 1]) continue;

            for (int j = i + 1; j < n; j++) {
                if (j > i + 1 && arr[j] == arr[j - 1]) continue;

                int left = j + 1, right = n - 1;
                while (left < right) {
                    long long sum = (long long)arr[i] + arr[j] + arr[left] + arr[right];

                    if (sum == target) {
                        ans.push_back({arr[i], arr[j], arr[left], arr[right]});

                        while (left < right && arr[left] == arr[left + 1]) left++;
                        while (left < right && arr[right] == arr[right - 1]) right--;

                        left++;
                        right--;
                    }
                    else if (sum < target) left++;
                    else right--;
                }
            }
        }

        return ans;
    }
};
```

---

## Main Idea

Sort the array first.

Then:

* fix the first number with `i`
* fix the second number with `j`
* use two pointers `left` and `right` to find the remaining two numbers

This reduces the problem to a 2 Sum style search inside the sorted array.

---

## Why Sorting Helps

Sorting gives order, which lets us move pointers intelligently:

* if the sum is too small, increase it by moving `left` rightward
* if the sum is too large, decrease it by moving `right` leftward

Without sorting, pointer movement would not be meaningful.

---

## Duplicate Handling

This part is critical.

### For `i`

If `arr[i] == arr[i-1]`, skip it.

### For `j`

If `arr[j] == arr[j-1]` and `j > i + 1`, skip it.

### For `left` and `right`

After finding a valid quadruplet, move both pointers and skip duplicates to avoid repeating the same quad.

---

## Visualization

For:

```text
arr = [1,0,-1,0,-2,2]
```

after sorting:

```text
[-2, -1, 0, 0, 1, 2]
```

Fix `-2` and `-1`.

Now find two numbers summing to `3`.

Using two pointers:

* `0 + 2 = 2` → too small
* `0 + 2 = 2` → too small
* `1 + 2 = 3` → valid

This gives:

```text
[-2, -1, 1, 2]
```

Repeat similarly for other fixed pairs.

---

# Dry Run

## Input

```text
arr = [1,0,-1,0,-2,2], target = 0
```

After sorting:

```text
[-2, -1, 0, 0, 1, 2]
```

---

### i = 0 → arr[i] = -2

#### j = 1 → arr[j] = -1

Need two numbers with sum `3`.

* left = 2, right = 5
* `0 + 2 = 2` → too small → left++
* `0 + 2 = 2` → too small → left++
* `1 + 2 = 3` → valid

Quad:

```text
[-2, -1, 1, 2]
```

---

#### j = 2 → arr[j] = 0

Need two numbers with sum `2`.

* left = 3, right = 5
* `0 + 2 = 2` → valid

Quad:

```text
[-2, 0, 0, 2]
```

---

### i = 1 → arr[i] = -1

#### j = 2 → arr[j] = 0

Need two numbers with sum `1`.

* left = 3, right = 5
* `0 + 2 = 2` → too large → right--
* `0 + 1 = 1` → valid

Quad:

```text
[-1, 0, 0, 1]
```

Final answer:

```text
[[-2,-1,1,2], [-2,0,0,2], [-1,0,0,1]]
```

---

# Why the Optimal Approach Is Best

The brute force solution checks every quadruplet.

The optimal solution reduces the problem to:

* two fixed loops
* one two-pointer search

Because the array is sorted, duplicate handling and pointer movement become efficient.

---

# Complexity

## Brute Force

* **Time:** `O(n^4 log n)`
* **Space:** `O(m)`

## Better Approach

* **Time:** `O(n^3)` average
* **Space:** `O(n)`

## Optimal Approach

* **Time:** `O(n^3)`
* **Space:** `O(1)` excluding output

---

# Key Takeaways

* Sort the array first.
* Fix two elements.
* Use two pointers for the remaining two.
* Skip duplicates at every level.
* Use `long long` for sum to avoid overflow.

---

# Revision Template

```text
1. Sort the array
2. Fix the first number with i
3. Fix the second number with j
4. Use left and right pointers for the remaining two numbers
5. If sum == target, store quadruplet and move both pointers
6. If sum < target, move left
7. If sum > target, move right
8. Skip duplicates for i, j, left, and right
```

---

# Final Intuition

> 4 Sum is 3 Sum with one more fixed element: sort the array, fix two numbers, and use two pointers for the remaining two while skipping duplicates carefully.

---

# Pointer Placement Visualization (Optimal Approach)

Let's understand **how the two pointers move**.

### Input

```text
arr = [1,0,-1,0,-2,2]
target = 0
```

### Step 1 : Sort the array

```text
Index : 0   1   2   3   4   5
Value :-2  -1   0   0   1   2
```

---

## Iteration 1

Choose

```text
i = 0
j = 1
```

So

```text
arr[i] = -2
arr[j] = -1
```

Now place the two pointers.

```text
          i   j   L           R
          ↓   ↓   ↓           ↓

Index :   0   1   2   3   4   5
Value :  -2  -1   0   0   1   2
```

Current Sum

```text
-2 + (-1) + 0 + 2 = -1
```

Since

```text
-1 < target(0)
```

we need a **bigger sum**.

Move **left**.

---

```text
          i   j       L       R
          ↓   ↓       ↓       ↓

Index :   0   1   2   3   4   5
Value :  -2  -1   0   0   1   2
```

Current Sum

```text
-2 + (-1) + 0 + 2 = -1
```

Still too small.

Move left again.

---

```text
          i   j           L   R
          ↓   ↓           ↓   ↓

Index :   0   1   2   3   4   5
Value :  -2  -1   0   0   1   2
```

Current Sum

```text
-2 + (-1) + 1 + 2 = 0
```

Perfect!

Store

```text
[-2,-1,1,2]
```

Now move both pointers.

```text
left++
right--
```

Pointers cross.

This `(i,j)` pair is finished.

---

# Iteration 2

Keep

```text
i = 0
```

Move

```text
j = 2
```

Pointers become

```text
              i       j   L       R
              ↓       ↓   ↓       ↓

Index :       0   1   2   3   4   5
Value :      -2  -1   0   0   1   2
```

Current Sum

```text
-2 + 0 + 0 + 2 = 0
```

Found

```text
[-2,0,0,2]
```

Move both pointers.

```text
left++
right--
```

Pointers meet.

Done.

---

# Iteration 3

Now

```text
i = 1
j = 2
```

Pointers

```text
                  i   j   L       R
                  ↓   ↓   ↓       ↓

Index :           0   1   2   3   4   5
Value :          -2  -1   0   0   1   2
```

Current Sum

```text
-1 + 0 + 0 + 2 = 1
```

Too large.

Need a **smaller** sum.

Move

```text
right--
```

---

```text
                  i   j   L   R
                  ↓   ↓   ↓   ↓

Index :           0   1   2   3   4   5
Value :          -2  -1   0   0   1   2
```

Current Sum

```text
-1 + 0 + 0 + 1 = 0
```

Found

```text
[-1,0,0,1]
```

Done.

---

# Why Move Left?

When

```text
sum < target
```

the sum is too small.

Since the array is sorted,

```text
moving left →
```

means

```text
0 → 1 → 2 → 3 ...
```

The sum increases.

---

# Why Move Right?

When

```text
sum > target
```

the sum is too large.

Moving

```text
right ←
```

means

```text
5 → 4 → 3 → 2 ...
```

The value decreases.

So the sum becomes smaller.

---

# Pointer Movement Summary

```text
sum < target
      │
      ▼
Move Left →

-----------------------

sum > target
      │
      ▼
Move Right ←

-----------------------

sum == target
      │
      ▼
Store Quadruplet

Move Left →
Move Right ←

Skip duplicates
```

---

# Complete Pointer Flow

```text
Sorted Array

-2   -1    0    0    1    2
 ↑     ↑    ↑              ↑
 i     j    L              R

↓

Sum < target

Move L →

-2   -1    0    0    1    2
 ↑     ↑         ↑         ↑
 i     j         L         R

↓

Sum < target

Move L →

-2   -1    0    0    1    2
 ↑     ↑              ↑    ↑
 i     j              L    R

↓

Sum == target

Store

[-2,-1,1,2]

↓

Move both pointers

L++
R--

Done for this (i,j)
```

### ⭐ Memory Trick

Think of it exactly like **3 Sum**.

```
4 Sum

Fix i
      ↓
Fix j
      ↓
Remaining problem becomes

2 Sum using Two Pointers
```

That's why the optimal complexity is **O(n³)** instead of **O(n⁴)**.