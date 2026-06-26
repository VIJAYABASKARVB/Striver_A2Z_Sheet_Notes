# Majority Element (> N/2 Times)

## Problem Statement

Given an integer array `nums` of size `n`, return the **majority element**.

A majority element is an element that appears **more than `n/2` times**.

The array is guaranteed to have a majority element.

---

## Examples

### Example 1

**Input:** `nums = [7, 0, 0, 1, 7, 7, 2, 7, 7]`
**Output:** `7`

### Example 2

**Input:** `nums = [1, 1, 1, 2, 1, 2]`
**Output:** `1`

---

## Core Idea

We need to find the element that appears **more than half the time**.

Two approaches:

1. **Brute force** — count frequency of every element.
2. **Optimal** — Boyer–Moore Voting Algorithm.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int cnt = 0;

            for (int j = 0; j < n; j++) {
                if (nums[j] == nums[i]) {
                    cnt++;
                }
            }

            if (cnt > (n / 2)) {
                return nums[i];
            }
        }

        return -1;
    }
};
```

## How It Works

* Pick each element one by one.
* Count how many times it appears in the whole array.
* If its count is greater than `n/2`, return it.

## Complexity

* **Time:** `O(n^2)`
* **Space:** `O(1)`

---

# 2) Optimal Approach — Boyer–Moore Voting Algorithm

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0;
        int el;

        for (int i = 0; i < n; i++) {
            if (cnt == 0) {
                cnt = 1;
                el = nums[i];
            } else if (el == nums[i]) {
                cnt++;
            } else {
                cnt--;
            }
        }

        int cnt1 = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] == el) {
                cnt1++;
            }
        }

        if (cnt1 > (n / 2)) {
            return el;
        }

        return -1;
    }
};
```

---

## Main Idea Behind Boyer–Moore

The majority element appears **more than half the time**, so it cannot be completely canceled out by all other elements.

Think of it as **vote cancellation**:

* same element = +1 vote
* different element = -1 vote

If a candidate loses all votes (`cnt == 0`), we choose a new candidate.

---

## Why This Works

Suppose the majority element is `7`.

Even if other elements keep canceling it out, there are still **more 7s than all other elements combined**.

So after all cancellations, the majority element survives as the final candidate.

---

## Visual Intuition

Imagine pairing different elements and removing them:

```text
7  7  7  1  2  7  7
-  -  -  -  -
```

The non-majority elements can cancel some majority votes, but not all of them.

That is why the majority element remains as the final candidate.

---

# Dry Run

## Example: `nums = [7, 0, 0, 1, 7, 7, 2, 7, 7]`

We track:

* `el` = current candidate
* `cnt` = vote count

| i | nums[i] | Action                     | el | cnt |
| - | ------: | -------------------------- | -: | --: |
| 0 |       7 | cnt = 0 → choose candidate |  7 |   1 |
| 1 |       0 | different → decrement      |  7 |   0 |
| 2 |       0 | cnt = 0 → choose candidate |  0 |   1 |
| 3 |       1 | different → decrement      |  0 |   0 |
| 4 |       7 | cnt = 0 → choose candidate |  7 |   1 |
| 5 |       7 | same → increment           |  7 |   2 |
| 6 |       2 | different → decrement      |  7 |   1 |
| 7 |       7 | same → increment           |  7 |   2 |
| 8 |       7 | same → increment           |  7 |   3 |

Final candidate: `7`

Then we do the second pass to verify that `7` appears more than `n/2` times.

---

# Why the Second Pass Is Needed

Boyer–Moore gives a **candidate**, not always a guaranteed majority in every variation of the problem.

In this problem, the array is guaranteed to have a majority element, so the candidate is correct, but verification is still a safe and standard step.

---

# Complexity

## Brute Force

* **Time:** `O(n^2)`
* **Space:** `O(1)`

## Boyer–Moore Voting

* **Time:** `O(n)`
* **Space:** `O(1)`

---

# Key Takeaways

* Majority element means **frequency > n/2**.
* Brute force counts every element.
* Boyer–Moore works by **cancelling different elements**.
* The final candidate is then verified with one more pass.

---

# Revision Template

```text
1. Use a candidate and a counter
2. If counter is 0, choose current element as candidate
3. If current element matches candidate, increment counter
4. Otherwise decrement counter
5. Verify candidate with one more pass
```

---

# Final Intuition

**The majority element survives vote cancellation because it appears more than all other elements combined.**
