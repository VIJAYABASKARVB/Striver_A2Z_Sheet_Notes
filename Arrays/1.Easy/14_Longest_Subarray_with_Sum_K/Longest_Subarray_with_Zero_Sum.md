# Length of the Longest Subarray with Zero Sum

## Problem Statement

Given an array containing both **positive and negative** integers, find the length of the **longest subarray** whose sum is `0`.

---

## Examples

### Example 1

**Input:** `N = 6, array[] = {9, -3, 3, -1, 6, -5}`  
**Output:** `5`

**Explanation:**

Subarrays with sum `0`:

- `{-3, 3}`
- `{-1, 6, -5}`
- `{-3, 3, -1, 6, -5}` → length `5`

### Example 2

**Input:** `N = 8, array[] = {6, -2, 2, -8, 1, 7, 4, -10}`  
**Output:** `8`

**Explanation:**

Subarrays with sum `0`:

- `{-2, 2}`
- `{-8, 1, 7}`
- `{-2, 2, -8, 1, 7}`
- `{6, -2, 2, -8, 1, 7, 4, -10}` → length `8`

---

## Visual Representation

### Prefix Sum Concept

If the prefix sum at two indices is the same, then the elements between them sum to `0`.

```text
Array:   [a0, a1, a2, ..., ai, ..., aj, ...]
Prefix:  P0, P1, P2, ..., Pi, ..., Pj, ...

If Pi == Pj,
then sum(i+1 ... j) = Pj - Pi = 0
```

### Example Walkthrough

```text
arr = [9, -3, 3, -1, 6, -5]

Prefix sums:
i=0: sum=9   → store (9,0)
i=1: sum=6   → store (6,1)
i=2: sum=9   → seen at index 0
              → zero-sum subarray (1..2) = [-3, 3]
              → length 2

i=3: sum=8   → store (8,3)
i=4: sum=14  → store (14,4)
i=5: sum=9   → seen at index 0
              → zero-sum subarray (1..5) = [-3, 3, -1, 6, -5]
              → length 5

Answer = 5
```

---

## Approach Comparison

| Aspect | Brute Force | Optimal (Prefix Sum + HashMap) |
|--------|-------------|--------------------------------|
| Time | O(n²) | O(n) |
| Space | O(1) | O(n) |
| Works for | All integers | All integers |
| Best For | Small arrays | Large arrays |

---

## Brute Force Approach

### Idea

Generate all subarrays, compute their sum, and track the maximum length where the sum is `0`.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int longestZeroSumSubarray(vector<int>& arr) {
    int n = arr.size();
    int maxLen = 0;

    for (int start = 0; start < n; start++) {
        int sum = 0;
        for (int end = start; end < n; end++) {
            sum += arr[end];
            if (sum == 0) {
                maxLen = max(maxLen, end - start + 1);
            }
        }
    }

    return maxLen;
}

int main() {
    vector<int> arr = {9, -3, 3, -1, 6, -5};
    cout << longestZeroSumSubarray(arr) << endl; // 5
    return 0;
}
```

### Time Complexity

`O(n²)`

### Space Complexity

`O(1)`

---

## Optimal Approach (Prefix Sum + HashMap)

### Idea

Maintain a running prefix sum and store the **first index** where each prefix sum occurred.

If the same prefix sum appears again, the subarray between the two indices has sum `0`.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int longestZeroSumSubarray(vector<int>& arr) {
    int n = arr.size();
    unordered_map<int, int> prefixIndex; // prefix sum -> first index
    int sum = 0;
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (sum == 0) {
            maxLen = i + 1; // subarray from 0 to i
        }
        else if (prefixIndex.find(sum) != prefixIndex.end()) {
            maxLen = max(maxLen, i - prefixIndex[sum]);
        }
        else {
            prefixIndex[sum] = i; // store first occurrence only
        }
    }

    return maxLen;
}

int main() {
    vector<int> arr = {9, -3, 3, -1, 6, -5};
    cout << longestZeroSumSubarray(arr) << endl; // 5
    return 0;
}
```

### Time Complexity

`O(n)`

### Space Complexity

`O(n)`

---

## Dry Run (Optimal)

### Input

```text
[9, -3, 3, -1, 6, -5]
```

| i | arr[i] | sum | prefixIndex | maxLen | Action |
|---|--------|-----|-------------|--------|--------|
| 0 | 9 | 9 | { } | 0 | store 9→0 |
| 1 | -3 | 6 | {9:0} | 0 | store 6→1 |
| 2 | 3 | 9 | {9:0, 6:1} | 2 | sum 9 exists → length 2 |
| 3 | -1 | 8 | {9:0, 6:1} | 2 | store 8→3 |
| 4 | 6 | 14 | {9:0, 6:1, 8:3} | 2 | store 14→4 |
| 5 | -5 | 9 | {9:0, 6:1, 8:3, 14:4} | 5 | sum 9 exists → length 5 |

### Final Answer

```text
5
```

---

## Key Takeaways

- The optimal solution uses **prefix sum + hashmap**.
- Two equal prefix sums imply a **zero-sum subarray** between them.
- Store only the **first occurrence** of each prefix sum to get the **longest** subarray.
- If prefix sum becomes `0`, the subarray from index `0` to `i` is valid.
- Works for both positive and negative numbers.

---

## Edge Cases

| Case | Input | Output |
|------|-------|--------|
| Empty array | `[]` | `0` |
| All zeros | `[0,0,0]` | `3` |
| No zero-sum subarray | `[1,2,3]` | `0` |
| Single element zero | `[0]` | `1` |
| Single element non-zero | `[5]` | `0` |

---

## Quick Revision Points

1. Prefix sum + hashmap is the classic `O(n)` solution.
2. If `sum == 0`, length is `i + 1`.
3. If `sum` was seen before, length is `i - previousIndex[sum]`.
4. Store only the first occurrence of each prefix sum.
5. Works with positive and negative numbers.
6. Space complexity is `O(n)` for the map.

---

## Visual Memory Aid

```text
Prefix Sums:
[9, -3, 3, -1, 6, -5]
 ↓   ↓   ↓   ↓   ↓   ↓
 9   6   9   8  14   9

      └──────────┘
      sum 9 repeats

Zero-sum subarray = indices 1 to 5
Length = 5
```