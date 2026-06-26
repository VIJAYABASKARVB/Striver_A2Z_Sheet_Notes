# Two Sum

## Problem Statement

Given an array of integers `nums` and an integer `target`, return the indices `i` and `j` such that:

```text
nums[i] + nums[j] == target
```

and `i != j`.

You may assume there is **exactly one valid answer**.

Return the answer with the **smaller index first**.

---

## Examples

### Example 1

**Input:** `nums = [3,4,5,6]`, `target = 7`
**Output:** `[0,1]`

### Example 2

**Input:** `nums = [4,5,6]`, `target = 10`
**Output:** `[0,2]`

### Example 3

**Input:** `nums = [5,5]`, `target = 10`
**Output:** `[0,1]`

---

## Core Idea

We need to find **two numbers that add up to the target**.

Two common approaches:

1. **Brute force** — check every pair.
2. **Hash map** — store previously seen values and search for the complement.

The complement of `nums[i]` is:

```text
target - nums[i]
```

If that value has already been seen, we found the answer.

---

# 1) Brute Force Approach

## Code

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {i, j};
                }
            }
        }
        return {};
    }
};
```

## How It Works

* Fix the first index `i`.
* Try every possible second index `j` after it.
* If the pair sums to `target`, return the indices.

## Complexity

* **Time:** `O(n^2)`
* **Space:** `O(1)`

---

# 2) Optimal Approach — Hash Map

## Code

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> prevMap;

        for (int i = 0; i < n; i++) {
            int diff = target - nums[i];
            if (prevMap.find(diff) != prevMap.end()) {
                return {prevMap[diff], i};
            }
            prevMap.insert({nums[i], i});
        }
        return {};
    }
};
```

## Main Idea

At each index `i`, we ask:

> Have I already seen the number needed to complete the sum?

That needed number is the **complement**:

```text
diff = target - nums[i]
```

If `diff` exists in the map, then we already found the earlier index.

---

## What the Map Stores

The hashmap stores:

```text
number -> index where it was seen
```

Example:

```text
prevMap[3] = 0
prevMap[4] = 1
```

Meaning:

* value `3` was seen at index `0`
* value `4` was seen at index `1`

---

## Why We Check Before Inserting

We first check whether the complement already exists in the map.

This is important because:

* it prevents using the same element twice
* it ensures the earlier index is returned first

Example:
`nums = [5,5]`, `target = 10`

* At index `0`, map is empty, so store `5 -> 0`
* At index `1`, complement is `5`
* `5` is already in the map at index `0`
* return `[0,1]`

---

# Dry Run

## Example: `nums = [3,4,5,6]`, `target = 7`

| i | nums[i] | diff = target - nums[i] | prevMap before | Found? | Action         |
| - | ------: | ----------------------: | -------------- | ------ | -------------- |
| 0 |       3 |                       4 | {}             | No     | store `3 -> 0` |
| 1 |       4 |                       3 | {3:0}          | Yes    | return `[0,1]` |

So the answer is:

```text
[0, 1]
```

---

## Example: `nums = [5,5]`, `target = 10`

| i | nums[i] | diff | prevMap before | Found? | Action         |
| - | ------: | ---: | -------------- | ------ | -------------- |
| 0 |       5 |    5 | {}             | No     | store `5 -> 0` |
| 1 |       5 |    5 | {5:0}          | Yes    | return `[0,1]` |

---

# Why the Optimal Solution is Better

The brute force approach checks every pair.

The hashmap approach remembers what we have already seen, so each number is processed once.

That makes it much faster.

---

# Complexity

## Brute Force

* **Time:** `O(n^2)`
* **Space:** `O(1)`

## Hash Map

* **Time:** `O(n)`
* **Space:** `O(n)`

---

# Key Takeaways

* The problem is about finding a pair whose sum equals `target`.
* Use the complement:

```text
target - current number
```

* Store seen numbers in a hashmap with their indices.
* Check the complement before inserting the current value.

---

# Revision Template

```text
1. For each number, compute its complement
2. Check whether complement already exists in hashmap
3. If yes, return stored index and current index
4. Otherwise store current number with its index
```

---

# Final Intuition

**Instead of searching for two numbers directly, search for the complement of each number using a hashmap.**
