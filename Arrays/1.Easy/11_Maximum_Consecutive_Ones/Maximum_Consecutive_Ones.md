# Count Maximum Consecutive One's in the Array

## Problem Statement

Given a binary array containing only `0`s and `1`s, find the length of the **longest consecutive sequence of 1's**.

---

## Examples

### Example 1

**Input:** `nums = [1, 1, 0, 1, 1, 1]`

**Output:** `3`

**Explanation:**

```text
Consecutive 1's:

[1, 1]       -> Length = 2
[1, 1, 1]    -> Length = 3

Maximum = 3
```

### Example 2

**Input:** `nums = [1, 0, 1, 1, 0, 1]`

**Output:** `2`

**Explanation:**

```text
Longest streak = [1, 1]
Length = 2
```

---

## Visual Representation

### Example Walkthrough

```text
Array: [1, 1, 0, 1, 1, 1]

Index:  0  1  2  3  4  5
Value:  1  1  0  1  1  1

i=0 -> count=1, max=1
i=1 -> count=2, max=2
i=2 -> count=0, max=2
i=3 -> count=1, max=2
i=4 -> count=2, max=2
i=5 -> count=3, max=3

Answer = 3
```

### Reset on Zero

```text
[1, 1, 0, 1, 1, 1]
 ↑  ↑     ↑  ↑  ↑
 2 Ones  Reset  3 Ones
```

---

## Optimal Approach

### Idea

Maintain two variables:

- `cnt` → Current streak of consecutive `1`s.
- `maxi` → Maximum streak seen so far.

Rules:

```text
If current element == 1
    cnt++

Else
    cnt = 0

Update:
maxi = max(maxi, cnt)
```

---

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {

        int cnt = 0;
        int maxi = 0;

        for (int i = 0; i < nums.size(); i++) {

            if (nums[i] == 1) {
                cnt++;
            }
            else {
                cnt = 0;
            }

            maxi = max(maxi, cnt);
        }

        return maxi;
    }
};

int main() {

    vector<int> nums = {1, 1, 0, 1, 1, 1};

    Solution obj;

    int ans = obj.findMaxConsecutiveOnes(nums);

    cout << "Maximum Consecutive Ones = "
         << ans;

    return 0;
}
```

---

## Dry Run

### Input

```text
nums = [1, 1, 0, 1, 1, 1]
```

| Step | Index | Value | Count After | Max After |
|--------|--------|--------|--------|--------|
| 1 | 0 | 1 | 1 | 1 |
| 2 | 1 | 1 | 2 | 2 |
| 3 | 2 | 0 | 0 | 2 |
| 4 | 3 | 1 | 1 | 2 |
| 5 | 4 | 1 | 2 | 2 |
| 6 | 5 | 1 | 3 | 3 |

### Final Answer

```text
3
```

---

## Visual Trace

```text
nums = [1, 1, 0, 1, 1, 1]

count = 0
max   = 0

1 -> count = 1 -> max = 1

1 -> count = 2 -> max = 2

0 -> count = 0 -> max = 2

1 -> count = 1 -> max = 2

1 -> count = 2 -> max = 2

1 -> count = 3 -> max = 3
```

---

## Complexity Analysis

| Operation | Complexity |
|------------|------------|
| Time Complexity | O(n) |
| Space Complexity | O(1) |

### Why O(n)?

```text
Each element is visited exactly once.
```

### Why O(1)?

```text
Only two variables are used:

cnt
maxi
```

No extra data structure is required.

---

## Edge Cases

| Case | Input | Output |
|--------|--------|--------|
| No Ones | `[0,0,0]` | `0` |
| All Ones | `[1,1,1,1]` | `4` |
| Single One | `[1]` | `1` |
| Single Zero | `[0]` | `0` |
| Streak At Start | `[1,1,1,0,1]` | `3` |
| Streak At End | `[0,1,1,1]` | `3` |

---

## Key Takeaways

- Traverse the array only once.
- Increment count when encountering a `1`.
- Reset count when encountering a `0`.
- Keep track of the maximum count seen.
- Uses constant extra space.

---

## Quick Revision

### Algorithm

```text
Initialize:

count = 0
maxi = 0

For every element:

If element == 1
    count++

Else
    count = 0

maxi = max(maxi, count)

Return maxi
```

---

## Visual Memory Aid

```text
1 -> Increase Count

0 -> Reset Count
```

Example:

```text
[1, 1, 0, 1, 1, 1]

Count:
 1
 2
 0
 1
 2
 3

Maximum = 3
```

### Easy Way to Remember

```text
Count until you hit a 0.

When a 0 appears:
Reset.

Keep storing the best streak.
```

### Core Logic

```cpp
if(nums[i] == 1)
    cnt++;
else
    cnt = 0;

maxi = max(maxi, cnt);
```

---

## Pattern Recognition

This problem follows the:

```text
Array Traversal Pattern
```

Track:

```text
Current Streak
+
Best Streak
```

This same idea appears in:

- Longest Increasing Streak
- Consecutive Characters
- Maximum Consecutive Wins
- Continuous Subarray Counting