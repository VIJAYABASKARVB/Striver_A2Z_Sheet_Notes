# Majority Elements (> N/3 Times)

## Problem Statement

Given an integer array `nums` of size `n`, return **all elements** that appear **more than `n/3` times**.

The output can be returned in any order.

---

## Examples

### Example 1

**Input:** `nums = [1, 2, 1, 1, 3, 2]`
**Output:** `[1]`

**Explanation:**

* `n = 6`
* `n / 3 = 2`
* An element must appear **more than 2 times**
* `1` appears 3 times, so it is valid

### Example 2

**Input:** `nums = [1, 2, 1, 1, 3, 2, 2]`
**Output:** `[1, 2]`

**Explanation:**

* `n = 7`
* `n / 3 = 2`
* An element must appear **more than 2 times**
* `1` appears 3 times
* `2` appears 3 times

---

## Core Idea

For the `> n/3` version:

* there can be **at most 2 valid elements**
* because if there were 3 elements appearing more than `n/3` times each, the total count would exceed `n`

So the answer can contain only:

* 0 elements
* 1 element
* 2 elements

This is why the Boyer–Moore extension uses **two candidates**.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> majorityElementTwo(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        
        for (int i = 0; i < n; i++) {
            if (result.size() == 0 || result[0] != nums[i]) {
                int cnt = 0;
                
                for (int j = 0; j < n; j++) {
                    if (nums[j] == nums[i]) {
                        cnt++;
                    }
                }

                if (cnt > (n / 3))
                    result.push_back(nums[i]);
            }
            
            if (result.size() == 2) break;
        }
        
        return result;
    }
};
```

## How It Works

* For each element, count how many times it appears in the entire array.
* If the count is greater than `n/3`, add it to the answer.
* Stop after finding 2 such elements.

## Complexity

* **Time:** `O(n^2)`
* **Space:** `O(1)`

---

# 2) Better Approach — Hash Map

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> majorityElementTwo(vector<int>& nums) {
        int n = nums.size();
        vector<int> result;
        unordered_map<int, int> mpp;
        
        int mini = int(n / 3) + 1;
        
        for (int i = 0; i < n; i++) {
            mpp[nums[i]]++;
            
            if (mpp[nums[i]] == mini) {
                result.push_back(nums[i]);
            }
            
            if (result.size() == 2) {
                break;
            }
        }
        
        return result;
    }
};
```

## How It Works

* Use a hashmap to count frequencies.
* Once an element reaches the threshold `mini = n/3 + 1`, store it.
* Stop after collecting 2 answers.

## Complexity

* **Time:** `O(n)`
* **Space:** `O(n)`

---

# 3) Optimal Approach — Boyer–Moore Voting (Extended)

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> majorityElementTwo(vector<int>& nums) {
        int n = nums.size();

        int cnt1 = 0, cnt2 = 0;
        int el1 = INT_MIN, el2 = INT_MIN;

        for (int i = 0; i < n; i++) {
            if (cnt1 == 0 && el2 != nums[i]) {
                cnt1 = 1;
                el1 = nums[i];
            }
            else if (cnt2 == 0 && el1 != nums[i]) {
                cnt2 = 1;
                el2 = nums[i];
            }
            else if (nums[i] == el1) {
                cnt1++;
            }
            else if (nums[i] == el2) {
                cnt2++;
            }
            else {
                cnt1--;
                cnt2--;
            }
        }

        cnt1 = 0, cnt2 = 0;
        
        for (int i = 0; i < n; i++) {
            if (nums[i] == el1) cnt1++;
            if (nums[i] == el2) cnt2++;
        }

        int mini = n / 3 + 1;
        vector<int> result;

        if (cnt1 >= mini) {
            result.push_back(el1);
        }
        if (cnt2 >= mini && el1 != el2) {
            result.push_back(el2);
        }

        return result;
    }
};
```

---

## Main Idea

Since the answer can contain at most **2 elements**, we maintain **2 candidates** and their counts.

The logic is a generalized version of Boyer–Moore voting:

* same candidate → increment its count
* new valid empty slot → store candidate
* different from both candidates → decrement both counts

This works because elements that are not frequent enough cancel out the candidates.

---

## Why At Most Two Answers?

If three different elements each appeared more than `n/3` times, then together they would appear more than:

```text
n/3 + n/3 + n/3 = n
```

which is impossible.

So the answer can never contain more than 2 elements.

---

## Why a Second Pass is Needed

The first pass only finds **potential candidates**.

It does **not guarantee** they actually appear more than `n/3` times.

So we verify them in a second pass by counting their real frequencies.

---

## Visualization of the Cancellation Idea

Suppose the array has many different numbers:

```text
1, 2, 3, 1, 2, 1, 2, 1
```

The frequent values `1` and `2` keep surviving, while less frequent values get cancelled out.

The final candidates after voting are the only possible answers.

---

# Dry Run

## Input

```text
nums = [1, 2, 1, 1, 3, 2, 2]
```

We track:

* `el1`, `cnt1`
* `el2`, `cnt2`

Initial:

```text
el1 = -∞, cnt1 = 0
el2 = -∞, cnt2 = 0
```

| i | nums[i] | Action                               | el1 | cnt1 | el2 | cnt2 |
| - | ------: | ------------------------------------ | --: | ---: | --: | ---: |
| 0 |       1 | cnt1 = 0 → el1 = 1                   |   1 |    1 |  -∞ |    0 |
| 1 |       2 | cnt2 = 0 → el2 = 2                   |   1 |    1 |   2 |    1 |
| 2 |       1 | matches el1                          |   1 |    2 |   2 |    1 |
| 3 |       1 | matches el1                          |   1 |    3 |   2 |    1 |
| 4 |       3 | different from both → decrement both |   1 |    2 |   2 |    0 |
| 5 |       2 | cnt2 = 0 → el2 = 2                   |   1 |    2 |   2 |    1 |
| 6 |       2 | matches el2                          |   1 |    2 |   2 |    2 |

Now validate:

* `1` appears 3 times → valid
* `2` appears 3 times → valid

Final answer:

```text
[1, 2]
```

---

# Why the Optimal Approach is Better

The brute force approach counts every element repeatedly.

The hashmap approach counts frequencies directly but uses extra space.

The Boyer–Moore extension is the best because it:

* uses only constant extra space
* finds the possible candidates in one pass
* verifies them in a second pass

---

# Complexity

## Brute Force

* **Time:** `O(n^2)`
* **Space:** `O(1)`

## Better Approach

* **Time:** `O(n)`
* **Space:** `O(n)`

## Optimal Approach

* **Time:** `O(n)`
* **Space:** `O(1)`

---

# Key Takeaways

* For `> n/3`, there can be at most **2 majority elements**.
* Use two candidates and two counters.
* Different elements cancel out.
* Always verify candidates in a second pass.

---

# Revision Template

```text
1. Realize that at most 2 elements can appear more than n/3 times
2. Maintain 2 candidates and 2 counters
3. Apply Boyer–Moore style cancellation
4. Verify the final candidates in a second pass
5. Return the valid ones
```

---

# Final Intuition

> When the threshold is n/3, only two elements can survive as frequent enough candidates. Use two votes, cancel the rest, then verify.

```
```
