# Merge Overlapping Sub-Intervals

---

# Problem Statement

You are given an array of intervals where each interval is represented as:

```
[start, end]
```

Each interval represents a range of numbers from **start** to **end** (both inclusive).

Some intervals may **overlap**, meaning they share one or more common values.

Your task is to **merge all overlapping intervals** and return a list of intervals such that:

- No two intervals overlap.
- Every number covered by the original intervals is still covered.
- The intervals in the answer represent the same ranges as the original input, just merged wherever possible.

---

## What is an Overlapping Interval?

Two intervals overlap if

```
current.start <= previous.end
```

Example:

```
[1,3]

[2,6]
```

Visual Representation

```
1 2 3 4 5 6

[-----]

  [---------]
```

They share numbers **2 and 3**, so they can be merged into

```
[1,6]
```

---

Another example

```
[1,4]

[4,5]
```

Visual Representation

```
1 2 3 4 5

[-------]

      [---]
```

Even though they only touch at **4**, they are still considered overlapping.

Merged interval

```
[1,5]
```

---

A non-overlapping example

```
[1,3]

[5,7]
```

```
1 2 3 4 5 6 7

[-----]

        [-----]
```

There is a gap between them.

They remain separate.

---

# Examples

## Example 1

### Input

```
intervals =

[
 [1,3],
 [2,6],
 [8,10],
 [15,18]
]
```

### Output

```
[
 [1,6],
 [8,10],
 [15,18]
]
```

### Explanation

The first two intervals overlap.

```
[1,3]

[2,6]
```

Merge them

```
[1,6]
```

The remaining intervals don't overlap.

Final Answer

```
[
 [1,6],
 [8,10],
 [15,18]
]
```

---

## Example 2

### Input

```
[
 [1,4],
 [4,5]
]
```

### Output

```
[
 [1,5]
]
```

### Explanation

The intervals touch at **4**.

Since

```
4 <= 4
```

they overlap.

Merged interval

```
[1,5]
```

---

# Core Idea / Pattern Recognition

## Pattern

```
Sorting
+
Interval Processing
+
Greedy
```

---

## Why Sorting?

Suppose the intervals are

```
[8,10]

[1,3]

[2,6]
```

Without sorting,

you don't know which intervals should be merged first.

After sorting,

```
[1,3]

[2,6]

[8,10]
```

Now every possible overlapping interval will appear **next to each other**.

This makes merging very easy.

---

## Why Greedy?

Whenever we find an overlapping interval,

we immediately merge it with the current interval.

We never need to reconsider previous decisions.

That is exactly what a **Greedy algorithm** does.

---

# Observation

Imagine these intervals.

```
[1,3]

[2,4]

[3,5]

[7,9]
```

Draw them on a number line.

```
1 2 3 4 5 6 7 8 9

[-----]

  [-----]

    [-----]

            [-----]
```

Notice something important.

The first three intervals are connected.

Instead of storing

```
[1,3]

[2,4]

[3,5]
```

we can simply store

```
[1,5]
```

because together they cover exactly the same numbers.

Only when we encounter

```
[7,9]
```

do we need to start a new interval.

---

Another observation

Suppose our current merged interval is

```
[2,8]
```

Now we receive

```
[5,9]
```

Since

```
5 <= 8
```

they overlap.

The new merged interval becomes

```
Start

minimum start

=

2

End

maximum end

=

9
```

Result

```
[2,9]
```

Notice that

**the start never changes**

Only the end may increase.

This observation is the basis of the optimal solution.

---

# Approach 1 — Brute Force

## Idea

First, sort all intervals based on their starting point.

After sorting,

pick one interval and continuously merge every interval that overlaps with it.

Once merging stops,

store the merged interval in the answer.

Repeat this process for the next unprocessed interval.

Although this solution is already efficient after sorting, it explicitly scans forward from each interval to merge all overlapping intervals before moving on.

---

## Algorithm

### Step 1

Sort intervals.

Example

Before

```
[8,10]

[2,6]

[1,3]

[15,18]
```

After

```
[1,3]

[2,6]

[8,10]

[15,18]
```

---

### Step 2

Take the first interval.

```
start = 1

end = 3
```

---

### Step 3

Keep checking the next interval.

If

```
next.start <= end
```

merge it.

Update

```
end = max(end,next.end)
```

---

### Step 4

Continue until no overlap exists.

Store the merged interval.

---

### Step 5

Repeat from the next unvisited interval.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to merge overlapping intervals using brute force
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        // Sort intervals based on start time
        sort(intervals.begin(), intervals.end());

        // Result array to store merged intervals
        vector<vector<int>> ans;

        // Loop through each interval
        int n = intervals.size();
        for (int i = 0; i < n; ) {

            // Start of current merged interval
            int start = intervals[i][0];
            int end = intervals[i][1];

            // Merge with all overlapping intervals
            int j = i + 1;
            while (j < n && intervals[j][0] <= end) {
                // Update end to the maximum of current end and overlapping interval's end
                end = max(end, intervals[j][1]);
                j++;
            }

            // Add the merged interval to result
            ans.push_back({start, end});

            // Move to the next non-overlapping interval
            i = j;
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1,3}, {2,6}, {8,10}, {15,18}};
    vector<vector<int>> result = sol.merge(intervals);

    for (auto interval : result) {
        cout << "[" << interval[0] << "," << interval[1] << "] ";
    }
    return 0;
}
```

---

## Visualization

### Step 1

Sorted intervals

```
[1,3]

[2,6]

[8,10]

[15,18]
```

---

### Step 2

Current interval

```
[1,3]
```

```
1 2 3 4 5 6

[-----]
```

---

### Step 3

Next interval

```
[2,6]
```

```
1 2 3 4 5 6

[-----]

  [---------]
```

Since

```
2 <= 3
```

they overlap.

Merge

```
[1,6]
```

Visualization

```
1 2 3 4 5 6

[---------------]
```

---

### Step 4

Next interval

```
[8,10]
```

```
1 2 3 4 5 6 7 8 9 10

[-----------]

              [-----]
```

No overlap.

Store

```
[1,6]
```

Start a new interval.

---

### Step 5

Current interval

```
[8,10]
```

Next

```
[15,18]
```

```
8 9 10 11 12 13 14 15 16 17 18

[------]

                      [---------]
```

No overlap.

Store

```
[8,10]
```

Finally

Store

```
[15,18]
```

Answer

```
[
 [1,6],
 [8,10],
 [15,18]
]
```

---

## Detailed Dry Run

Input

```
[
 [1,3],
 [2,6],
 [8,10],
 [15,18]
]
```

Already sorted.

---

### Iteration 1

```
i = 0

start = 1

end = 3
```

Initialize

```
j = 1
```

---

Check

```
interval[1]

[2,6]
```

Condition

```
2 <= 3

True
```

Merge

```
end = max(3,6)

= 6
```

Current merged interval

```
[1,6]
```

Move

```
j = 2
```

---

Check

```
interval[2]

[8,10]
```

Condition

```
8 <= 6

False
```

Stop merging.

Store

```
[1,6]
```

Move

```
i = 2
```

Answer

```
[
 [1,6]
]
```

---

### Iteration 2

```
start = 8

end = 10
```

```
j = 3
```

Check

```
[15,18]
```

Condition

```
15 <= 10

False
```

Store

```
[8,10]
```

Move

```
i = 3
```

Answer

```
[
 [1,6],

 [8,10]
]
```

---

### Iteration 3

```
start = 15

end = 18
```

```
j = 4
```

No intervals remain.

Store

```
[15,18]
```

Answer

```
[
 [1,6],

 [8,10],

 [15,18]
]
```

Loop ends.

---

## Complexity

### Time Complexity

```
Sorting : O(N log N)

Scanning : O(N)

Overall

O(N log N)
```

The sorting step dominates the running time.

---

### Space Complexity

```
O(N)
```

Reason:

- The answer vector may contain up to **N** intervals in the worst case (when no intervals overlap).
- Apart from the output, only a few variables are used.

---

# Approach 2 — Optimal Approach

The optimal solution is based on the same initial idea:

```
Sort the intervals first.
```

However, instead of explicitly looking ahead with another pointer (`j`) to merge all future intervals, we build the answer **on the fly**.

Whenever we process a new interval, we compare it only with the **last merged interval**.

If they overlap, we simply extend the last merged interval.

Otherwise, we start a new interval.

This makes the code much cleaner while maintaining the same time complexity.

---

# Main Idea

Think of the merged intervals as a growing answer.

Initially,

```
merged = []
```

Process every interval one by one.

For every interval there are only **two possibilities**.

## Case 1 — No Overlap

Current merged interval

```
[1,4]
```

New interval

```
[7,9]
```

Visualization

```
1 2 3 4 5 6 7 8 9

[-------]

            [-----]
```

There is a gap.

They cannot be merged.

Simply add it.

```
merged

↓

[1,4]

[7,9]
```

---

## Case 2 — Overlap

Current merged interval

```
[1,4]
```

Incoming interval

```
[3,7]
```

Visualization

```
1 2 3 4 5 6 7

[-------]

    [---------]
```

They overlap.

Instead of creating another interval,

extend the existing one.

```
Old

[1,4]

↓

New

[1,7]
```

Notice

```
Start

remains

1

End

changes to

max(4,7)

=

7
```

---

# Why It Works

Suppose after sorting we have

```
[1,3]

[2,5]

[4,6]

[8,10]
```

Because the intervals are sorted,

once an interval overlaps with the current merged interval,

every merged interval before it has already been finalized.

There is **no need to revisit previous intervals.**

This is the Greedy property.

---

Imagine

```
Merged

[1,6]
```

Now we receive

```
[4,8]
```

Since

```
4 <= 6
```

the two intervals overlap.

Everything covered is simply

```
1 ............. 8
```

So extending the end is sufficient.

---

Another important observation

After sorting,

suppose

```
Current merged interval

[2,9]
```

Incoming interval

```
[4,5]
```

Visualization

```
2 3 4 5 6 7 8 9

[----------------]

    [-----]
```

The new interval is already inside.

Nothing changes.

The merged interval remains

```
[2,9]
```

because

```
max(9,5)

=

9
```

---

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to merge overlapping intervals
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // Sort intervals based on starting time
        sort(intervals.begin(), intervals.end());

        // Vector to store final merged intervals
        vector<vector<int>> merged;

        // Traverse each interval
        for (auto interval : intervals) {
            // If merged is empty or current interval does not overlap
            if (merged.empty() || merged.back()[1] < interval[0]) {
                // Add current interval as a new non-overlapping block
                merged.push_back(interval);
            } else {
                // Overlapping: merge by extending the end time
                merged.back()[1] = max(
                    merged.back()[1],
                    interval[1]
                );
            }
        }

        return merged;
    }
};
```

---

# Visualization

## Step 1

Sort intervals

```
Input

[1,3]

[2,6]

[8,10]

[15,18]
```

Already sorted.

---

## Step 2

Start Answer

```
merged

[
]
```

Process first interval

```
[1,3]
```

Answer

```
[
 [1,3]
]
```

---

## Step 3

Current interval

```
[2,6]
```

Current merged interval

```
[1,3]
```

Visualization

```
1 2 3 4 5 6

[-----]

  [---------]
```

They overlap.

Merge

```
1 2 3 4 5 6

[---------------]
```

Answer

```
[
 [1,6]
]
```

---

## Step 4

Current interval

```
[8,10]
```

Visualization

```
1 2 3 4 5 6 7 8 9 10

[-----------]

              [-----]
```

No overlap.

Answer

```
[
 [1,6],

 [8,10]
]
```

---

## Step 5

Current interval

```
[15,18]
```

Visualization

```
8 9 10 11 12 13 14 15 16 17 18

[------]

                      [---------]
```

No overlap.

Final Answer

```
[
 [1,6],

 [8,10],

 [15,18]
]
```

---

# Pointer Placement Visualization

Although this algorithm doesn't use the traditional **left** and **right** pointers,

it still maintains two important references.

```
Current Interval

↓

[2,6]
```

and

```
Last Merged Interval

↓

merged.back()

↓

[1,3]
```

Every iteration compares only these two intervals.

---

### Iteration 1

```
Current

[1,3]

Merged

[]
```

Merged is empty.

Push.

```
[
 [1,3]
]
```

---

### Iteration 2

```
Current

[2,6]

Last Merged

[1,3]
```

Compare

```
2 <= 3

Yes
```

Merge.

```
[1,6]
```

---

### Iteration 3

```
Current

[8,10]

Last Merged

[1,6]
```

Compare

```
8 <= 6

No
```

Push.

```
[
 [1,6],

 [8,10]
]
```

---

### Iteration 4

```
Current

[15,18]

Last Merged

[8,10]
```

Compare

```
15 <= 10

No
```

Push.

```
[
 [1,6],

 [8,10],

 [15,18]
]
```

---

# Large ASCII Interval Animation

Initial

```
[1,3]
[2,6]
[8,10]
[15,18]
```

Number Line

```
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18

[-----]

  [---------]

              [------]

                              [---------]
```

Merge First Two

```
1 2 3 4 5 6

[----------------]
```

Now

```
Merged

↓

[1,6]
```

Next Interval

```
[8,10]
```

```
1 2 3 4 5 6 7 8 9 10

[-----------]

              [------]
```

Gap exists.

Cannot merge.

Finally

```
[
 [1,6],

 [8,10],

 [15,18]
]
```

---

# Detailed Dry Run

Input

```
[
 [1,3],
 [2,6],
 [8,10],
 [15,18]
]
```

Initially

```
merged = []
```

---

## Iteration 1

Current Interval

```
[1,3]
```

Merged is empty.

Action

```
Push
```

merged

```
[
 [1,3]
]
```

---

## Iteration 2

Current

```
[2,6]
```

Last merged

```
[1,3]
```

Condition

```
merged.back().end

=

3

Current.start

=

2

3 >= 2

Overlap
```

Update

```
End

=

max(3,6)

=

6
```

merged

```
[
 [1,6]
]
```

---

## Iteration 3

Current

```
[8,10]
```

Last merged

```
[1,6]
```

Check

```
6 < 8

No overlap
```

Push

```
[
 [1,6],

 [8,10]
]
```

---

## Iteration 4

Current

```
[15,18]
```

Last merged

```
[8,10]
```

Check

```
10 < 15

No overlap
```

Push

```
[
 [1,6],

 [8,10],

 [15,18]
]
```

Loop finishes.

Return answer.

---

# Special Cases Visualization

## Case 1

Interval completely inside another

```
[1,10]

[3,5]
```

```
1 2 3 4 5 6 7 8 9 10

[-----------------------]

    [-------]
```

Answer remains

```
[1,10]
```

---

## Case 2

Touching Intervals

```
[1,4]

[4,7]
```

```
1 2 3 4 5 6 7

[-------]

      [---------]
```

Since

```
4 <= 4
```

Merge

```
[1,7]
```

---

## Case 3

Chain Overlap

```
[1,2]

[2,4]

[4,6]

[6,9]
```

```
1 2 3 4 5 6 7 8 9

[--]

  [------]

      [------]

          [---------]
```

Everything becomes

```
[1,9]
```

---

# Edge Cases

### Empty Input

```
[]
```

Answer

```
[]
```

---

### Single Interval

```
[
 [5,8]
]
```

Answer

```
[
 [5,8]
]
```

---

### No Overlap

```
[1,2]

[4,5]

[7,9]
```

Nothing merges.

---

### Entire Array Becomes One Interval

```
[1,2]

[2,3]

[3,5]

[5,9]
```

Answer

```
[1,9]
```

---

### Nested Intervals

```
[1,10]

[2,5]

[3,4]
```

Answer

```
[1,10]
```

---

# Complexity

## Time Complexity

```
Sorting

O(N log N)

Traversal

O(N)
```

Overall

```
O(N log N)
```

The sorting step dominates the running time.

---

## Space Complexity

```
O(N)
```

Reason:

- The output vector may contain up to **N** intervals if no intervals overlap.
- Aside from the output, the algorithm uses only constant extra variables (`merged.back()` and the current interval reference).

---

# Comparison Table

| Approach | Time Complexity | Space Complexity | Notes |
|-----------|-----------------|------------------|-------|
| Brute (Sort + Scan Forward) | **O(N log N)** | **O(N)** | Sort the intervals, then explicitly keep scanning forward (`j`) to merge all overlapping intervals before moving to the next block. |
| Optimal (Greedy Merge) | **O(N log N)** | **O(N)** | Sort once and compare each interval only with the **last merged interval**. Simpler and cleaner implementation. |

> **Note:** In this problem, both implementations have the same asymptotic complexity. The "optimal" solution is preferred because it is more elegant, easier to understand, and performs fewer unnecessary comparisons.

---

# Brute vs Optimal Visualization

## Brute Approach

```
Intervals

[1,3]
[2,6]
[3,8]
[9,11]
```

For every interval, keep moving `j` forward until there is no overlap.

```
i
↓

[1,3]

      j
      ↓

[2,6]

           j
           ↓

[3,8]

                 j
                 ↓

[9,11]
```

Merge repeatedly

```
[1,3]

↓

[1,6]

↓

[1,8]
```

Store

```
[1,8]
```

Then continue from

```
[9,11]
```

---

## Optimal Approach

Maintain only one merged interval.

```
Merged

[]

↓

Push

[1,3]

↓

Merge

[1,6]

↓

Merge

[1,8]

↓

Push

[9,11]
```

Only compare with

```
merged.back()
```

No inner scanning loop.

---

# Why Sorting is Mandatory

Imagine the intervals are

```
[8,10]

[1,3]

[2,6]
```

Without sorting

```
Process

[8,10]

↓

Store

[8,10]

↓

Process

[1,3]
```

Now we have already separated

```
[8,10]
```

before even seeing

```
[2,6]
```

The algorithm loses the natural ordering.

---

After sorting

```
[1,3]

[2,6]

[8,10]
```

Now every overlapping interval appears **next to each other**.

That is why sorting is the first step.

---

# Key Observations to Remember

### Observation 1

After sorting,

every interval that can overlap with the current interval will appear immediately after it.

---

### Observation 2

The merged interval's **start never changes**.

Only the **end** may increase.

Example

```
Current

[2,7]

Incoming

[5,9]
```

Result

```
[2,9]
```

---

### Observation 3

If

```
Current End

<

Next Start
```

there is definitely no overlap.

Start a new interval.

---

### Observation 4

If

```
Current End

>=

Next Start
```

they overlap.

Merge them.

---

# Common Mistakes

## Mistake 1

Not sorting first.

Example

```
[5,7]

[1,4]

[3,6]
```

Without sorting,

you may never merge

```
[1,4]

and

[3,6]
```

correctly.

---

## Mistake 2

Using

```
>
```

instead of

```
>=
```

or equivalently checking the wrong condition.

Remember,

```
[1,4]

[4,5]
```

are considered overlapping.

Since

```
4 <= 4
```

they must be merged.

---

## Mistake 3

Updating the start.

Incorrect

```
start = current.start
```

The start should remain unchanged because the intervals are already sorted.

Only update

```
end = max(end, current.end)
```

---

## Mistake 4

Comparing with the previous original interval.

Always compare with

```
merged.back()
```

because it already represents the merged block.

---

# Dry Run Summary

Input

```
[
 [1,3],
 [2,6],
 [8,10],
 [15,18]
]
```

| Current Interval | Last Merged | Action | Result |
|------------------|-------------|--------|--------|
| [1,3] | None | Push | [[1,3]] |
| [2,6] | [1,3] | Merge | [[1,6]] |
| [8,10] | [1,6] | Push | [[1,6],[8,10]] |
| [15,18] | [8,10] | Push | [[1,6],[8,10],[15,18]] |

Final Answer

```
[
 [1,6],
 [8,10],
 [15,18]
]
```

---

# Interview Intuition

Imagine painting a wall.

Initially

```
Painted

[1,3]
```

Now another painter paints

```
[2,6]
```

Instead of remembering both painted regions,

you simply remember

```
[1,6]
```

because together they cover exactly the same wall.

Every new interval either

- extends the painted region, or
- starts a brand new painted region.

That is exactly how the greedy algorithm works.

---

# Key Takeaways

- Sort intervals by **starting time**.
- After sorting, overlapping intervals become adjacent.
- Compare every interval with the **last merged interval**.
- If they overlap, extend only the **ending point**.
- If they don't overlap, create a new interval.
- Never modify the starting point of a merged interval.
- Touching intervals (`end == start`) are also overlapping.
- The greedy solution works because once an interval is merged, it never needs to be revisited.

---

# Revision Template

```
1. Sort intervals by start time.

2. Create an empty answer vector.

3. Traverse every interval.

4. If answer is empty,
      push interval.

5. Else compare

      merged.back().end

      with

      current.start

6. If overlap

      merged.back().end =
      max(current.end, merged.back().end)

7. Else

      push current interval.

8. Return merged.
```

---

# Memory Trick

Think of the problem as **drawing continuous lines on a number line**.

```
Start Drawing

↓

Touches Previous?

↓

YES

Extend the Line

↓

NO

Start New Line
```

Or remember this interview formula:

```
Sort

↓

Compare with Last Merged

↓

Overlap ?

      YES → Extend End

      NO  → Push New Interval
```

A shorter memory phrase:

```
Sort

↓

Touch?

↓

Merge

Else

Push
```

---

# Final Intuition

> Sort the intervals first, then greedily merge every interval that overlaps with the last merged interval, otherwise start a new interval.