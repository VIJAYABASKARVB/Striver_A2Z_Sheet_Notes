# Length of the Longest Subarray with Zero Sum

---

# Problem Statement

Given an integer array containing **both positive and negative numbers**, find the **length of the longest contiguous subarray** whose sum is exactly **0**.

You only need to return the **maximum length**, not the subarray itself.

### Constraints

- Array may contain:
  - Positive numbers
  - Negative numbers
  - Zero
- The array is **not sorted**.
- A brute-force approach is possible, but there exists a much more efficient solution using **Prefix Sum + HashMap**.

---

# Examples

## Example 1

**Input**

```
N = 6

arr = [9, -3, 3, -1, 6, -5]
```

**Output**

```
5
```

**Explanation**

Zero sum subarrays are

```
[-3, 3]

[-1, 6, -5]

[-3, 3, -1, 6, -5]
```

The longest one has length **5**.

---

## Example 2

**Input**

```
N = 8

arr = [6, -2, 2, -8, 1, 7, 4, -10]
```

**Output**

```
8
```

**Explanation**

Zero sum subarrays are

```
[-2, 2]

[-8, 1, 7]

[-2, 2, -8, 1, 7]

[6, -2, 2, -8, 1, 7, 4, -10]
```

The entire array sums to zero.

---

# Core Idea / Pattern Recognition

**Pattern**

```
Prefix Sum + HashMap
```

### Why this pattern?

Whenever we need to find a subarray with a particular sum efficiently, **Prefix Sum** is usually involved.

Instead of calculating every subarray sum repeatedly, we maintain a running prefix sum.

The important observation is:

```
If the same prefix sum appears twice,

the elements between those two indices
must sum to zero.
```

This allows us to find zero-sum subarrays in **O(N)** time.

---

# Observation

Suppose

```
Array

2   3   -2   5   -5
```

Prefix sums

```
2
5
3
8
3
```

Notice

```
Prefix Sum = 3

appears at

index 2

and

index 4
```

That means

```
Sum(3...4)

=

Prefix(4) - Prefix(2)

=

3 - 3

=

0
```

Therefore,

```
[5, -5]
```

has sum zero.

This observation is the entire foundation of the optimal solution.

---

# Approach 1 — Brute Force

## Idea

Compute the running prefix sum while traversing the array.

Maintain a HashMap storing the **first occurrence** of every prefix sum.

Whenever the same prefix sum appears again, the elements between the two indices have a sum of zero.

Although labeled as the "brute" approach in the prompt, this implementation is actually the efficient Prefix Sum + HashMap solution.

---

## Algorithm

1. Initialize

```
sum = 0

maxLen = 0
```

2. Traverse the array.

3. Add current element to prefix sum.

4. If prefix sum becomes zero,

```
maxLen = i + 1
```

5. If prefix sum already exists

```
length = currentIndex - firstOccurrence
```

Update answer.

6. Otherwise store the prefix sum.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// compute length of the longest subarray with sum 0
int solve(vector<int>& a) {
    // store best length found so far
    int maxLen = 0;
    // map prefix sum -> first index seen
    unordered_map<int, int> sumIndexMap;
    // running prefix sum
    int sum = 0;

    // iterate through the array
    for (int i = 0; i < (int)a.size(); i++) {
        // update running sum
        sum += a[i];

        // if sum is zero, subarray [0..i] has zero sum
        if (sum == 0) {
            // update best length
            maxLen = i + 1;
        }
        // if this sum seen before, subarray (prevIndex..i] has zero sum
        else if (sumIndexMap.find(sum) != sumIndexMap.end()) {
            // maximize length using previous index
            maxLen = max(maxLen, i - sumIndexMap[sum]);
        }
        // first time seeing this sum, store its index
        else {
            sumIndexMap[sum] = i;
        }
    }

    // return best length
    return maxLen;
}

// program entry
int main() {
    // sample input
    vector<int> a = {9, -3, 3, -1, 6, -5};
    // print result
    cout << solve(a) << endl;
    // exit
    return 0;
}
```

---

## Visualization

```
Array

9  -3   3  -1   6  -5
```

Prefix Sum

```
9
6
9
8
14
9
```

Observe

```
Prefix Sum = 9

appears

Index 0

Index 2

Index 5
```

So

```
Between

0 -> 2

[-3, 3]

sum = 0

length = 2
```

Again

```
Between

0 -> 5

[-3,3,-1,6,-5]

sum = 0

length = 5
```

Longest = 5

---

## Dry Run

```
sum = 0
maxLen = 0
map = {}
```

### i = 0

```
sum = 9

store

9 -> 0
```

Map

```
9 : 0
```

---

### i = 1

```
sum = 6

store

6 -> 1
```

Map

```
9 : 0

6 : 1
```

---

### i = 2

```
sum = 9

already exists

previous index = 0

length = 2

maxLen = 2
```

---

### i = 3

```
sum = 8

store

8 -> 3
```

---

### i = 4

```
sum = 14

store

14 -> 4
```

---

### i = 5

```
sum = 9

already exists

previous index = 0

length = 5

maxLen = 5
```

Answer

```
5
```

---

## Complexity

### Time

```
O(N)
```

Each element is processed once.

### Space

```
O(N)
```

HashMap may store every prefix sum.

---

# Approach 2 — Optimal Approach

This is the same Prefix Sum + HashMap idea presented separately.

---

## Main Idea

Maintain a running prefix sum.

Store only the **first occurrence** of each prefix sum.

Whenever the same prefix sum appears again,

```
Subarray Sum

=

Current Prefix

-

Previous Prefix

=

0
```

Hence,

```
length = currentIndex - firstOccurrence
```

Keep the maximum.

---

## Why It Works

Suppose

```
Prefix(i)

=

15
```

Later,

```
Prefix(j)

=

15
```

Then

```
Subarray(i+1 ... j)

=

15 - 15

=

0
```

The repeated prefix sum guarantees that everything between them sums to zero.

### Why store only the first occurrence?

Suppose

```
Sum 10

appears at

index 2

then

index 5

then

index 9
```

If we overwrite

```
10 -> 5
```

Later,

```
length = 9 - 5 = 4
```

But using the first occurrence,

```
length = 9 - 2 = 7
```

which is longer.

Hence,

**always keep the first occurrence.**

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// compute length of the longest subarray with sum 0
int maxLen(int A[], int n) {
  // map prefix sum -> first index seen
  unordered_map<int, int> mpp;
  // best length so far
  int maxi = 0;
  // running prefix sum
  int sum = 0;

  // iterate over the array
  for (int i = 0; i < n; i++) {
    // update running sum
    sum += A[i];

    // if sum is zero, subarray [0..i] has zero sum
    if (sum == 0) {
      // update best length
      maxi = i + 1;
    }
    // otherwise check if this sum was seen before
    else {
      // when seen, zero-sum segment between previous index + 1 and i
      if (mpp.find(sum) != mpp.end()) {
        // maximize length
        maxi = max(maxi, i - mpp[sum]);
      }
      // first time seeing this sum
      else {
        // record index
        mpp[sum] = i;
      }
    }
  }

  // return best length
  return maxi;
}

// program entry
int main() {
  // sample input
  int A[] = {9, -3, 3, -1, 6, -5};
  // compute size
  int n = sizeof(A) / sizeof(A[0]);
  // print result
  cout << maxLen(A, n) << endl;
  // exit
  return 0;
}
```

---

## Visualization

### Step 1

```
Array

Index

0   1   2   3   4   5

9  -3   3  -1   6  -5
```

---

### Step 2

Build Prefix Sum

```
Index

0   1   2   3   4   5

9   6   9   8   14   9
```

---

### Step 3

Repeated Prefix Sum

```
9

↓

Index 0 ---------------------- Index 5

         -3  3  -1  6  -5

Sum = 0
```

Length

```
5 - 0 = 5
```

---

### Prefix Sum Timeline

```
Index

0     1     2     3     4      5

9 → 6 → 9 → 8 → 14 → 9
      ↑               ↑

Repeated Prefix Sum
```

---

## Pointer Placement Visualization

**Not Applicable**

This algorithm does **not** use sliding window or two pointers.

Instead, it relies on:

```
Current Index

↓

0   1   2   3   4   5
9  -3   3  -1   6  -5

Running Prefix Sum

↓

9
6
9
8
14
9
```

The important "movement" is the traversal of the current index while comparing prefix sums against the HashMap.

---

## Detailed Dry Run

```
Input

9 -3 3 -1 6 -5
```

Initially

```
sum = 0

maxi = 0

map = {}
```

---

### Iteration 1

```
i = 0

value = 9

sum = 9
```

Not seen before.

Store

```
9 -> 0
```

Map

```
9 : 0
```

---

### Iteration 2

```
i = 1

value = -3

sum = 6
```

Store

```
6 -> 1
```

Map

```
9 : 0

6 : 1
```

---

### Iteration 3

```
i = 2

value = 3

sum = 9
```

Already exists.

```
Previous Index = 0

Length = 2
```

```
maxi = 2
```

---

### Iteration 4

```
i = 3

value = -1

sum = 8
```

Store

```
8 -> 3
```

---

### Iteration 5

```
i = 4

value = 6

sum = 14
```

Store

```
14 -> 4
```

---

### Iteration 6

```
i = 5

value = -5

sum = 9
```

Already exists.

```
Previous Index = 0

Length = 5
```

Update

```
maxi = 5
```

Final Answer

```
5
```

---

## Edge Cases

### Empty Array

```
Answer = 0
```

---

### Entire Array Sums to Zero

```
Return N
```

---

### No Zero Sum Subarray

```
Return 0
```

---

### Single Element Zero

```
[0]

Answer = 1
```

---

### Multiple Repeated Prefix Sums

Always use the **first occurrence**.

---

## Complexity

### Time

```
O(N)
```

- Each element is visited exactly once.
- Every HashMap lookup and insertion is **O(1)** on average.

### Space

```
O(N)
```

- In the worst case, every prefix sum is unique and stored in the HashMap.

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|--------|------|
| Prefix Sum + HashMap (Implementation 1) | O(N) | O(N) | Stores first occurrence of prefix sums |
| Prefix Sum + HashMap (Implementation 2) | O(N) | O(N) | Same algorithm with different function signature |

---

# Key Takeaways

- Prefix Sum converts subarray problems into prefix comparisons.
- Equal prefix sums imply the subarray between them has sum **0**.
- Store only the **first occurrence** of a prefix sum.
- Never overwrite an existing prefix sum in the HashMap.
- If the running sum becomes zero, the entire prefix is a valid zero-sum subarray.
- HashMap enables O(1) average-time lookups, giving an overall O(N) solution.

---

# Revision Template

1. Initialize `sum = 0` and `maxLen = 0`.
2. Create a HashMap to store the first index of each prefix sum.
3. Traverse the array while updating the running prefix sum.
4. If `sum == 0`, update `maxLen = i + 1`.
5. If the prefix sum has been seen before, compute the subarray length.
6. Update the maximum length if needed.
7. If the prefix sum is new, store its index.
8. Return `maxLen`.

---

# Memory Trick

Think:

```
Same Prefix Sum

↓

Everything in between cancels out

↓

Subarray Sum = 0
```

Even easier to remember:

```
Repeat Prefix

↓

Zero Sum

↓

Longest Distance
```

---

# Final Intuition

> Keep a running prefix sum, remember the first time each sum appears, and whenever the same sum reappears, the elements between those two indices must form a zero-sum subarray.