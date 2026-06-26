# Subarray Sum Equals K

## Problem Statement

Given an integer array `nums` and an integer `k`, return the total number of **subarrays** whose sum is exactly `k`.

A subarray is a **contiguous, non-empty** part of the array.

---

## Examples

### Example 1

**Input**

```text
nums = [2,-1,1,2], k = 2
```

**Output**

```text
4
```

**Explanation**

The subarrays whose sum is `2` are:

- `[2]`
- `[2,-1,1]`
- `[-1,1,2]`
- `[2]`

---

### Example 2

**Input**

```text
nums = [4,4,4,4,4,4], k = 4
```

**Output**

```text
6
```

---

# Core Idea

We need to count **how many subarrays have sum exactly `k`**.

A brute force solution checks every subarray.

The optimal solution uses:

- **prefix sum**
- **hash map**

The key formula is:

```text
currentSum - previousSum = k
```

So if we know:

```text
previousSum = currentSum - k
```

then every time we have seen that prefix sum before, it means there is a subarray ending at the current index whose sum is `k`.

---

# 1) Brute Force Approach

## Code

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            int sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                if (sum == k) res++;
            }
        }
        return res;
    }
};
```

## How It Works

- Fix a starting index `i`
- Expand the subarray to the right
- Keep adding elements to `sum`
- If `sum == k`, count that subarray

## Complexity

- **Time:** `O(n^2)`
- **Space:** `O(1)`

---

# 2) Optimal Approach — Prefix Sum + Hash Map

## Code

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, curSum = 0;
        unordered_map<int, int> prefixSums;
        prefixSums[0] = 1;

        for (int num : nums) {
            curSum += num;
            int diff = curSum - k;
            res += prefixSums[diff];
            prefixSums[curSum]++;
        }

        return res;
    }
};
```

---

## Main Idea

Let:

```text
curSum = sum of elements from index 0 to current index
```

If at some point:

```text
curSum - previousPrefixSum = k
```

then the subarray between those two prefix sums has sum `k`.

So we store:

```text
prefixSums[prefixSum] = how many times this prefix sum has appeared
```

---

## Why `prefixSums[0] = 1`?

This is very important.

It means we have seen a prefix sum of `0` once before starting the array.

This helps count subarrays that start from index `0`.

Example:

```text
nums = [2, -1, 1, 2], k = 2
```

When `curSum = 2`, we want to count the subarray `[2]`.

That works because:

```text
curSum - k = 0
```

and `prefixSums[0] = 1`.

---

## Visualization

Suppose:

```text
nums = [2, -1, 1, 2]
k = 2
```

Prefix sums:

```text
index 0 -> 2
index 1 -> 1
index 2 -> 2
index 3 -> 4
```

Now check each position:

- at `curSum = 2`, need `0`
- at `curSum = 1`, need `-1`
- at `curSum = 2`, need `0`
- at `curSum = 4`, need `2`

Whenever the needed prefix sum was seen before, we add its frequency to the answer.

---

# Dry Run

## Input

```text
nums = [2, -1, 1, 2], k = 2
```

Initial state:

```text
curSum = 0
res = 0
prefixSums = {0:1}
```

---

| num | curSum | diff = curSum - k | prefixSums[diff] | res | prefixSums after update |
|-----:|-------:|------------------:|-----------------:|----:|-------------------------|
| 2 | 2 | 0 | 1 | 1 | {0:1, 2:1} |
| -1 | 1 | -1 | 0 | 1 | {0:1, 2:1, 1:1} |
| 1 | 2 | 0 | 1 | 2 | {0:1, 2:2, 1:1} |
| 2 | 4 | 2 | 2 | 4 | {0:1, 2:2, 1:1, 4:1} |

Final answer:

```text
4
```

---

# Why This Works

At each index, we are asking:

> How many earlier prefix sums can we pair with the current prefix sum to get sum `k`?

That is exactly what the hash map stores.

Because we add the frequency of `curSum - k`, we count **all** valid subarrays ending at the current index.

---

# Why This is Better Than Sliding Window

Sliding window works nicely when all numbers are non-negative.

But here `nums` can contain negative numbers.

Negative numbers break the usual “expand and shrink” logic, so sliding window is not reliable.

Prefix sum + hash map works for **positive, negative, and mixed** arrays.

---

# Complexity

## Brute Force
- **Time:** `O(n^2)`
- **Space:** `O(1)`

## Optimal Approach
- **Time:** `O(n)`
- **Space:** `O(n)`

---

# Key Takeaways

- Use prefix sums to convert subarray sum queries into difference queries.
- Store how many times each prefix sum has appeared.
- For each index, count how many previous prefix sums equal `curSum - k`.
- This counts all subarrays ending at the current index with sum `k`.

---

# Revision Template

```text
1. Initialize curSum = 0
2. Initialize hash map with prefixSums[0] = 1
3. Traverse the array
4. Update curSum
5. Compute diff = curSum - k
6. Add prefixSums[diff] to answer
7. Increment prefixSums[curSum]
8. Return answer
```

---

# Final Intuition

> If the difference between two prefix sums is `k`, then the subarray between them has sum `k`.