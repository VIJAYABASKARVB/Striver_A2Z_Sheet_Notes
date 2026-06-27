# Maximum Point You Can Obtain from Cards

## Problem Statement

You are given `N` cards arranged in a row, and each card has a score given by `cardPoints`.

You must choose exactly `k` cards.

At each step, you can choose only from:

- the **beginning** of the row
- the **end** of the row

Return the **maximum possible score**.

---

## Examples

### Example 1

**Input**

```text
cardScore = [1, 2, 3, 4, 5, 6], k = 3
```

**Output**

```text
15
```

**Explanation**

Take the rightmost 3 cards:

```text
4 + 5 + 6 = 15
```

---

### Example 2

**Input**

```text
cardScore = [5, 4, 1, 8, 7, 1, 3], k = 3
```

**Output**

```text
12
```

**Explanation**

One optimal choice is:

- take `5` from the beginning
- take `4` from the beginning
- take `3` from the end

Total:

```text
5 + 4 + 3 = 12
```

---

## Core Idea

You must choose exactly `k` cards from the two ends.

That means every valid selection looks like:

- some cards from the **left**
- the remaining cards from the **right**

So we can try all splits:

```text
0 from left, k from right
1 from left, k-1 from right
2 from left, k-2 from right
...
k from left, 0 from right
```

This gives the brute force solution.

The optimal idea is to start with the first `k` cards from the left and then gradually replace left cards with right cards.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        int maxSum = 0;

        for (int i = 0; i <= k; i++) {
            int tempSum = 0;

            for (int j = 0; j < i; j++) {
                tempSum += cardPoints[j];
            }

            for (int j = 0; j < k - i; j++) {
                tempSum += cardPoints[n - 1 - j];
            }

            maxSum = max(maxSum, tempSum);
        }

        return maxSum;
    }
};
```

---

## How It Works

For every possible split:

- take `i` cards from the left
- take `k - i` cards from the right

Compute the total score and keep the maximum.

---

## Visualization

Suppose:

```text
[1, 2, 3, 4, 5, 6], k = 3
```

Try all splits:

- `0` from left, `3` from right → `4 + 5 + 6 = 15`
- `1` from left, `2` from right → `1 + 5 + 6 = 12`
- `2` from left, `1` from right → `1 + 2 + 6 = 9`
- `3` from left, `0` from right → `1 + 2 + 3 = 6`

Maximum is `15`.

---

## Complexity

- **Time:** `O(k^2)`
- **Space:** `O(1)`

---

# 2) Optimal Approach

## Code

```cpp
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int lSum = 0, rSum = 0, maxSum = 0;
        int n = cardPoints.size();

        for (int i = 0; i < k; i++) {
            lSum += cardPoints[i];
        }

        maxSum = lSum;
        int rIndex = n - 1;

        for (int i = k - 1; i >= 0; i--) {
            lSum = lSum - cardPoints[i];
            rSum = rSum + cardPoints[rIndex];
            rIndex--;

            maxSum = max(maxSum, lSum + rSum);
        }

        return maxSum;
    }
};
```

---

## Main Idea

Instead of recalculating every split from scratch, we:

1. start by taking the first `k` cards from the left
2. then one by one:
   - remove one card from the left side
   - add one card from the right side

This way, we explore all possible left-right splits efficiently.

---

## Why This Works

If you choose exactly `k` cards from the ends, then the chosen cards are always a combination of:

- some prefix from the left
- some suffix from the right

So we only need to check all such combinations.

---

## Step-by-Step Intuition

Suppose:

```text
cardPoints = [1, 2, 3, 4, 5, 6]
k = 3
```

### Initial choice
Take first `k` cards from the left:

```text
1 + 2 + 3 = 6
```

This means:

- left taken = 3
- right taken = 0

Now we start moving cards from left to right.

---

### Step 1
Remove `3` from the left part and add `6` from the right.

```text
1 + 2 + 6 = 9
```

---

### Step 2
Remove `2` and add `5`.

```text
1 + 5 + 6 = 12
```

---

### Step 3
Remove `1` and add `4`.

```text
4 + 5 + 6 = 15
```

Maximum score becomes `15`.

---

# Dry Run

## Input

```text
cardPoints = [1, 2, 3, 4, 5, 6]
k = 3
```

### Step 1: Take first `k` cards from the left

```text
lSum = 1 + 2 + 3 = 6
maxSum = 6
rSum = 0
rIndex = 5
```

---

### Iteration 1
Remove `cardPoints[2] = 3` from left part

```text
lSum = 6 - 3 = 3
```

Add `cardPoints[5] = 6` from right part

```text
rSum = 0 + 6 = 6
```

Total:

```text
3 + 6 = 9
```

Update:

```text
maxSum = 9
```

---

### Iteration 2
Remove `cardPoints[1] = 2`

```text
lSum = 3 - 2 = 1
```

Add `cardPoints[4] = 5`

```text
rSum = 6 + 5 = 11
```

Total:

```text
1 + 11 = 12
```

Update:

```text
maxSum = 12
```

---

### Iteration 3
Remove `cardPoints[0] = 1`

```text
lSum = 1 - 1 = 0
```

Add `cardPoints[3] = 4`

```text
rSum = 11 + 4 = 15
```

Total:

```text
0 + 15 = 15
```

Update:

```text
maxSum = 15
```

Final answer:

```text
15
```

---

# Why This Is Better

The brute force solution recomputes sums for every split.

The optimal solution reuses previous work:

- subtract one left card
- add one right card

So it checks all splits in linear time.

---

# Complexity

## Brute Force
- **Time:** `O(k^2)`
- **Space:** `O(1)`

## Optimal Approach
- **Time:** `O(k)`
- **Space:** `O(1)`

---

# Key Takeaways

- You can only take cards from the two ends.
- So every valid choice is a split between left and right picks.
- Start with all `k` cards from the left.
- Shift one card at a time from left selection to right selection.
- Keep the maximum sum.

---

# Revision Template

```text
1. Sum first k cards from the left
2. Treat that as the initial answer
3. For each i from k-1 down to 0:
      remove cardPoints[i] from left sum
      add one card from the right
      update the maximum
4. Return the maximum
```

---

# Final Intuition

> Choose cards from the ends by trying every possible split between left and right picks, but do it efficiently by shifting one card at a time.