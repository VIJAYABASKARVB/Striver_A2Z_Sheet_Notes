# Longest Subarray with Sum K (Positive Numbers)

## Problem Statement

Given an array `nums` of size `n` and an integer `k`, find the length of the **longest subarray** whose sum is exactly `k`.

If no such subarray exists, return `0`.

---

## Examples

### Example 1

**Input**

```text
nums = [10, 5, 2, 7, 1, 9]
k = 15
```

**Output**

```text
4
```

**Explanation**

```text
Subarray = [5, 2, 7, 1]

5 + 2 + 7 + 1 = 15

Length = 4
```

---

### Example 2

**Input**

```text
nums = [-3, 2, 1]
k = 6
```

**Output**

```text
0
```

**Explanation**

```text
No subarray has sum = 6
```

---

## Visual Representation

### Sliding Window Concept

```text
nums = [10, 5, 2, 7, 1, 9]
k = 15

Window expands →
[10]

[10,5] = 15 ✓

[10,5,2] = 17 ✗

Shrink from left

[5,2] = 7

Expand again

[5,2,7,1] = 15 ✓

Length = 4
```

---

## Important Note

### When Sliding Window Works

✅ Positive Numbers

```text
[1,2,3,4,5]
```

✅ Non-Negative Numbers

```text
[1,0,2,0,3]
```

---

### When Sliding Window Fails

❌ Negative Numbers

```text
[2, -1, 3]
```

Reason:

```text
Removing elements from left
does not guarantee
the sum decreases.

Negative numbers break
the window property.
```

For arrays with negatives, use:

```text
Prefix Sum + HashMap
```

---

## Approach Comparison

| Approach | Time | Space |
|-----------|-----------|-----------|
| Brute Force | O(n³) | O(1) |
| Better (Prefix Sum in Loop) | O(n²) | O(1) |
| Sliding Window | O(n) | O(1) |

---

# 🔴 Brute Force Approach

## Idea

Generate every possible subarray.

For each subarray:

- Calculate its sum.
- If sum equals `k`, update answer.

---

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int longestSubarray(vector<int>& nums, int k) {

        int n = nums.size();

        int maxLength = 0;

        for(int start = 0; start < n; start++) {

            for(int end = start; end < n; end++) {

                int currentSum = 0;

                for(int i = start; i <= end; i++) {
                    currentSum += nums[i];
                }

                if(currentSum == k) {
                    maxLength =
                    max(maxLength,
                        end - start + 1);
                }
            }
        }

        return maxLength;
    }
};
```

---

## Complexity

```text
Time  = O(n³)

Space = O(1)
```

---

# 🟡 Better Approach (O(n²))

## Idea

Avoid recalculating the subarray sum.

Keep extending the subarray and update the sum on the fly.

---

## C++ Code

```cpp
int longestSubarray(vector<int>& nums, int k) {

    int n = nums.size();

    int maxLen = 0;

    for(int i = 0; i < n; i++) {

        long long sum = 0;

        for(int j = i; j < n; j++) {

            sum += nums[j];

            if(sum == k) {
                maxLen =
                max(maxLen, j - i + 1);
            }
        }
    }

    return maxLen;
}
```

---

## Complexity

```text
Time  = O(n²)

Space = O(1)
```

---

# 🟢 Optimal Approach (Sliding Window)

## Idea

Maintain:

```text
left
right
current sum
```

Rules:

```text
If sum < k
    Expand Window

If sum > k
    Shrink Window

If sum == k
    Update Answer
```

---

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int longestSubarray(vector<int>& nums, int k) {

        int n = nums.size();

        int left = 0;
        int right = 0;

        long long sum = nums[0];

        int maxLen = 0;

        while(right < n) {

            while(left <= right &&
                  sum > k) {

                sum -= nums[left];
                left++;
            }

            if(sum == k) {

                maxLen =
                max(maxLen,
                    right - left + 1);
            }

            right++;

            if(right < n)
                sum += nums[right];
        }

        return maxLen;
    }
};
```

---

## Sliding Window Dry Run

### Input

```text
nums = [10, 5, 2, 7, 1, 9]

k = 15
```

---

### Step 1

```text
Window = [10]

sum = 10

10 < 15

Expand
```

---

### Step 2

```text
Window = [10,5]

sum = 15

Found

Length = 2

maxLen = 2
```

---

### Step 3

```text
Window = [10,5,2]

sum = 17

17 > 15

Shrink
```

Remove:

```text
10

sum = 7

left = 1
```

---

### Step 4

```text
Window = [5,2,7]

sum = 14

Expand
```

---

### Step 5

```text
Window = [5,2,7,1]

sum = 15

Found

Length = 4

maxLen = 4
```

---

### Step 6

```text
Window = [5,2,7,1,9]

sum = 24

Shrink
```

Remove:

```text
5 → sum = 19

2 → sum = 17

7 → sum = 10
```

End.

---

### Final Answer

```text
4
```

---

## Dry Run Table

| Left | Right | Window | Sum | Max Length |
|--------|--------|--------|--------|--------|
| 0 | 0 | [10] | 10 | 0 |
| 0 | 1 | [10,5] | 15 | 2 |
| 1 | 2 | [5,2] | 7 | 2 |
| 1 | 3 | [5,2,7] | 14 | 2 |
| 1 | 4 | [5,2,7,1] | 15 | 4 |
| 4 | 5 | [1,9] | 10 | 4 |

---

## Prefix Sum + HashMap (For Negatives)

When negatives exist:

```text
Sliding Window ❌

Prefix Sum + HashMap ✅
```

---

### Idea

If:

```text
prefixSum - k
```

already exists,

then a subarray with sum `k` exists.

---

### C++ Code

```cpp
int longestSubarray(vector<int>& nums, int k) {

    unordered_map<long long,int> mp;

    long long prefixSum = 0;

    int maxLen = 0;

    for(int i = 0; i < nums.size(); i++) {

        prefixSum += nums[i];

        if(prefixSum == k) {
            maxLen = i + 1;
        }

        long long rem = prefixSum - k;

        if(mp.find(rem) != mp.end()) {

            maxLen =
            max(maxLen,
                i - mp[rem]);
        }

        if(mp.find(prefixSum) == mp.end()) {
            mp[prefixSum] = i;
        }
    }

    return maxLen;
}
```

---

## Complexity Comparison

| Approach | Time | Space |
|-----------|-----------|-----------|
| Brute Force | O(n³) | O(1) |
| Better | O(n²) | O(1) |
| Sliding Window | O(n) | O(1) |
| Prefix Sum + Map | O(n) | O(n) |

---

## Edge Cases

| Input | k | Output |
|---------|---------|---------|
| [] | 5 | 0 |
| [5] | 5 | 1 |
| [5] | 2 | 0 |
| [1,2,3] | 10 | 0 |
| [0,0,0] | 0 | 3 |
| [15] | 15 | 1 |

---

## Key Takeaways

- Sliding Window is optimal for positive/non-negative arrays.
- Negative numbers break the sliding window property.
- Prefix Sum + HashMap works for all integers.
- Store the first occurrence of a prefix sum.
- Longest subarray problems often involve:
  - Sliding Window
  - Prefix Sum
  - HashMap

---

## Quick Revision

### Positive Numbers

```text
Sliding Window
```

### Negative Numbers

```text
Prefix Sum + HashMap
```

### Sliding Window Rules

```text
sum < k → Expand

sum > k → Shrink

sum == k → Update Answer
```

### Prefix Sum Formula

```text
prefixSum - k
```

If found earlier:

```text
Subarray Sum = k
```

---

## Visual Memory Aid

```text
Positive Array

[10,5,2,7,1,9]

      ← shrink
[10,5,2]

          expand →

[5,2,7,1]

Sum = 15

Length = 4
```

### Interview Shortcut

```text
Positive Only?
    → Sliding Window

Contains Negatives?
    → Prefix Sum + HashMap
```