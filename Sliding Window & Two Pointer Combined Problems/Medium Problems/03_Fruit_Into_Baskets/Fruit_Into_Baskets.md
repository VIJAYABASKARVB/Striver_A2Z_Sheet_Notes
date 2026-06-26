# Fruit Into Baskets

## Problem Statement

There is a row of fruit trees. `fruits[i]` represents the type of fruit on the `i`-th tree.

You have **two baskets**:

* each basket can hold only **one type of fruit**
* each basket can hold **unlimited quantity** of that type

You may start from any tree and move only to the **right**, picking exactly one fruit from each tree until you meet a tree whose fruit type cannot fit in either basket.

Return the **maximum number of fruits** you can collect.

---

## Examples

### Example 1

**Input:** `fruits = [1, 2, 1]`
**Output:** `3`

**Explanation:**
Start from the first tree:

* basket 1 → type `1`
* basket 2 → type `2`
* third tree is again type `1`, which fits basket 1

So we collect all 3 fruits.

### Example 2

**Input:** `fruits = [1, 2, 3, 2, 2]`
**Output:** `4`

**Explanation:**
The best window is `[2, 3, 2, 2]`.
It contains only 2 fruit types, so we can collect 4 fruits.

---

## Core Idea

This is the same as:

> Find the **longest subarray with at most 2 distinct values**

That means we want the longest window containing no more than **two fruit types**.

This is a classic **sliding window + hashmap** problem.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int maxFruits = 0;

        for (int start = 0; start < fruits.size(); ++start) {
            unordered_map<int, int> basket;
            int currentCount = 0;

            for (int end = start; end < fruits.size(); ++end) {
                basket[fruits[end]]++;

                if (basket.size() > 2) {
                    break;
                }

                currentCount++;
            }

            maxFruits = max(maxFruits, currentCount);
        }

        return maxFruits;
    }
};
```

## How It Works

* Fix a starting index `start`.
* Expand to the right using `end`.
* Keep count of fruit types in a hashmap.
* If more than 2 types appear, stop.
* Track the longest valid subarray.

## Complexity

* **Time:** `O(n^2)`
* **Space:** `O(1)` in practice, because at most 3 types are being tracked before break

---

# 2) Optimal Approach — Sliding Window

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        unordered_map<int, int> basket;
        int maxFruits = 0;
        int left = 0;

        for (int right = 0; right < fruits.size(); right++) {
            basket[fruits[right]]++;

            while (basket.size() > 2) {
                basket[fruits[left]]--;

                if (basket[fruits[left]] == 0) {
                    basket.erase(fruits[left]);
                }

                left++;
            }

            maxFruits = max(maxFruits, right - left + 1);
        }

        return maxFruits;
    }
};
```

## Main Observation

A valid window is one that contains **at most 2 distinct fruit types**.

So we:

1. Expand the window with `right`
2. Add the fruit type into the hashmap
3. If there are more than 2 types, shrink from the left
4. Update the answer with the current valid window size

---

## Window Visualization

```text
left                               right
|-----------------------------------|
current window
```

* `right` expands the window
* `left` shrinks the window when there are too many fruit types
* the hashmap stores how many of each fruit type are inside the window

---

# Dry Run

## Dry Run for `fruits = [1, 2, 1, 2, 3]`

We track:

* `left`
* `right`
* `basket`
* `window size`
* `maxFruits`

| right | fruit | basket        | distinct types | left | window      | valid? | maxFruits |
| ----: | ----: | ------------- | -------------- | ---: | ----------- | ------ | --------: |
|     0 |     1 | {1:1}         | 1              |    0 | `[1]`       | Yes    |         1 |
|     1 |     2 | {1:1,2:1}     | 2              |    0 | `[1,2]`     | Yes    |         2 |
|     2 |     1 | {1:2,2:1}     | 2              |    0 | `[1,2,1]`   | Yes    |         3 |
|     3 |     2 | {1:2,2:2}     | 2              |    0 | `[1,2,1,2]` | Yes    |         4 |
|     4 |     3 | {1:2,2:2,3:1} | 3              |    0 | invalid     | No     |         4 |

### Shrinking step at `right = 4`

Window becomes invalid because we now have 3 fruit types.

We move `left` forward until only 2 types remain.

After shrinking, the valid window becomes:

```text
[2, 1, 2, 3]
```

or after further shrink depending on counts, the map is reduced to 2 types and the algorithm continues.

---

# Why the Sliding Window Works

The key is that the problem asks for a **contiguous subarray**.

Once the window has more than 2 fruit types:

* it cannot be extended further in a valid way
* so we must shrink from the left

This ensures the current window is always the best valid window ending at `right`.

---

# Important Invariant

At any moment, the window `[left ... right]` contains **at most 2 distinct fruit types**.

That is the only rule needed to maintain correctness.

---

# Complexity

## Brute Force

* **Time:** `O(n^2)`
* **Space:** `O(1)`

## Sliding Window

* **Time:** `O(n)`
* **Space:** `O(1)` or `O(2)` in practice, since the window keeps at most 2 types

---

# Key Takeaways

* The problem is really about the **longest subarray with at most 2 distinct values**.
* Use a hashmap to count fruit types in the current window.
* Expand `right`, shrink `left` when distinct types exceed 2.
* Update the answer using the current valid window size.

---

# Revision Template

```text
1. Expand right pointer
2. Count fruit types in hashmap
3. If distinct types > 2, shrink from left
4. Remove fruit type from map when count becomes 0
5. Update answer with current window length
```

---

# Final Intuition

**Keep the largest window that contains at most 2 fruit types, because only two baskets are available.**
