# 3 Sum : Find Triplets That Add Up to Zero

## Problem Statement

Given an array of `N` integers, find all **unique triplets** `[arr[a], arr[b], arr[c]]` such that:

```text
a != b != c
arr[a] + arr[b] + arr[c] = 0
```

Return all unique triplets in any order.

---

## Pre-requisite

This problem is an extension of the **2 Sum** pattern.

The main idea is:

- fix one element
- then find pairs whose sum is the negative of that element

---

## Examples

### Example 1

**Input**

```text
nums = [-1, 0, 1, 2, -1, -4]
```

**Output**

```text
[[-1,-1,2],[-1,0,1]]
```

### Example 2

**Input**

```text
nums = [-1,0,1,0]
```

**Output**

```text
[[-1,0,1],[-1,1,0]]
```

---

# Core Idea

We need to find all **unique** triplets that sum to `0`.

This means:

- triplets with the same values should not be repeated
- order inside a triplet does not matter
- the result should contain only distinct triplets

There are three ways to solve this:

1. **Brute Force**
2. **Better Approach**
3. **Optimal Two Pointers Approach**

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class to solve 3-sum problem
class Solution {
public:
    // Function to find triplets with sum zero
    vector<vector<int>> threeSum(vector<int>& arr, int n) {
        // Store unique triplets
        set<vector<int>> st;

        // First loop for first element
        for (int i = 0; i < n; i++) {
            // Second loop for second element
            for (int j = i + 1; j < n; j++) {
                // Third loop for third element
                for (int k = j + 1; k < n; k++) {
                    // If triplet sum is zero
                    if (arr[i] + arr[j] + arr[k] == 0) {
                        // Store sorted triplet to avoid duplicates
                        vector<int> temp = {arr[i], arr[j], arr[k]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
            }
        }

        // Convert set to vector
        vector<vector<int>> ans(st.begin(), st.end());
        return ans;
    }
};
```

---

## How It Works

- Choose every possible triple `(i, j, k)`
- Check whether their sum is `0`
- Sort the triplet so that the same values always look identical
- Insert into a `set` to avoid duplicates

---

## Why Sorting the Triplet is Needed

Triplets like:

```text
[-1, 0, 1]
[0, -1, 1]
[1, 0, -1]
```

all represent the same combination of numbers.

Sorting converts all of them into:

```text
[-1, 0, 1]
```

So duplicates can be removed easily.

---

## Complexity

- **Time:** `O(n^3 log m)`
- **Space:** `O(m)`

where `m` is the number of unique triplets stored in the set.

---

# 2) Better Approach — Hash Set for 2 Sum per Fixed Element

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class to solve 3-sum problem
class Solution {
public:
    // Function to find triplets with sum zero
    vector<vector<int>> threeSum(vector<int>& arr, int n) {
        // Store unique triplets
        set<vector<int>> ans;

        // First loop for first element
        for (int i = 0; i < n; i++) {
            // Set to store elements seen in this iteration
            set<int> hashset;

            // Second loop for second element
            for (int j = i + 1; j < n; j++) {
                // Calculate third element needed
                int third = -(arr[i] + arr[j]);

                // If third already in set, we found a triplet
                if (hashset.find(third) != hashset.end()) {
                    vector<int> temp = {arr[i], arr[j], third};
                    sort(temp.begin(), temp.end());
                    ans.insert(temp);
                }

                // Add current element to set
                hashset.insert(arr[j]);
            }
        }

        // Convert set to vector
        return vector<vector<int>>(ans.begin(), ans.end());
    }
};
```

---

## How It Works

For each fixed `arr[i]`:

- we want to find pairs `(arr[j], arr[k])` such that:

```text
arr[j] + arr[k] = -arr[i]
```

So we reduce the 3 Sum problem to a **2 Sum style search**.

We use a set to remember numbers already seen while scanning the array.

---

## Why It Is Better Than Brute Force

Instead of checking every possible `k` explicitly, we use a hash/set lookup to see whether the needed value already exists.

This reduces one loop’s work.

---

## Complexity

- **Time:** `O(n^2 log n)`
- **Space:** `O(n)`

---

# 3) Optimal Approach — Sorting + Two Pointers

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Class to solve 3-sum problem
class Solution {
public:
    // Function to find triplets with sum zero
    vector<vector<int>> threeSum(vector<int>& arr, int n) {
        // Sort the array
        sort(arr.begin(), arr.end());

        // Store final result
        vector<vector<int>> ans;

        // First loop for first element
        for (int i = 0; i < n; i++) {
            // Skip duplicates for first element
            if (i > 0 && arr[i] == arr[i - 1]) continue;

            // Two pointers
            int left = i + 1, right = n - 1;

            // Find pairs for current arr[i]
            while (left < right) {
                int sum = arr[i] + arr[left] + arr[right];

                if (sum == 0) {
                    ans.push_back({arr[i], arr[left], arr[right]});
                    left++, right--;

                    // Skip duplicates for left
                    while (left < right && arr[left] == arr[left - 1]) left++;

                    // Skip duplicates for right
                    while (left < right && arr[right] == arr[right + 1]) right--;
                }
                else if (sum < 0) left++;
                else right--;
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

- fix one element `arr[i]`
- use two pointers `left` and `right` to find pairs whose sum makes the total `0`

Since the array is sorted:

- if sum is too small, move `left` forward
- if sum is too large, move `right` backward

This is the standard **3 Sum = fixed element + 2 Sum with two pointers** pattern.

---

## Why Sorting Helps

Sorting gives us order.

That allows us to move pointers intelligently:

- smaller sum → increase it by moving `left`
- larger sum → decrease it by moving `right`

Without sorting, we would not know which direction to move.

---

## Duplicate Handling

This is very important.

### For the first element
If `arr[i] == arr[i - 1]`, skip it.

This avoids repeating the same triplet base.

### For `left` and `right`
After finding a valid triplet:

- move both pointers
- skip repeated values so the same triplet is not added again

---

## Visualization

Suppose:

```text
arr = [-4, -1, -1, 0, 1, 2]
```

### Fix `-1`

Now try to find two numbers that sum to `1`.

Using two pointers:

- `left = 0`
- `right = 2`

Check sums and move pointers accordingly until valid triplets are found.

This produces:

```text
[-1, -1, 2]
[-1, 0, 1]
```

---

# Dry Run

## Input

```text
nums = [-1, 0, 1, 2, -1, -4]
```

After sorting:

```text
[-4, -1, -1, 0, 1, 2]
```

---

### i = 0 → arr[i] = -4

Need pair sum = `4`

- left = 1, right = 5
- `-1 + 2 = 1` → too small → move left
- `-1 + 2 = 1` → too small → move left
- `0 + 2 = 2` → too small → move left
- `1 + 2 = 3` → too small → move left

No triplet.

---

### i = 1 → arr[i] = -1

Need pair sum = `1`

- left = 2, right = 5
- `-1 + 2 = 1` → valid

Triplet:

```text
[-1, -1, 2]
```

Move both pointers:

- left = 3
- right = 4

Now:

- `0 + 1 = 1` → valid

Triplet:

```text
[-1, 0, 1]
```

Done.

---

### i = 2
Skipped because `arr[2] == arr[1]`

This avoids duplicate triplets.

Final answer:

```text
[[-1,-1,2],[-1,0,1]]
```

---

# Why the Optimal Approach is Best

The brute force solution checks every triple.

The optimal solution reduces the problem to:

- one fixed element
- one two-pointer search

Because the array is sorted, the pointer movement is efficient and duplicates can be skipped cleanly.

---

# Complexity

## Brute Force
- **Time:** `O(n^3 log n)`
- **Space:** `O(m)`

## Better Approach
- **Time:** `O(n^2 log n)`
- **Space:** `O(n)`

## Optimal Approach
- **Time:** `O(n^2)`
- **Space:** `O(1)` excluding output

---

# Key Takeaways

- Sort the array first.
- Fix one element.
- Use two pointers for the remaining two numbers.
- Skip duplicates carefully.
- The answer contains unique triplets only.

---

# Revision Template

```text
1. Sort the array
2. Fix one element with index i
3. Use left = i + 1 and right = n - 1
4. If sum == 0, store triplet and move both pointers
5. If sum < 0, move left
6. If sum > 0, move right
7. Skip duplicates for i, left, and right
```

---

# Final Intuition

> Sort the array, fix one number, and then solve the remaining problem like 2 Sum using two pointers while skipping duplicates.