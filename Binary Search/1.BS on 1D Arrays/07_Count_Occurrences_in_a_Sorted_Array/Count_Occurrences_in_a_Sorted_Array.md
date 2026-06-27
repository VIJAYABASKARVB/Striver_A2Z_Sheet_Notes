# Count Occurrences in Sorted Array

## Problem Statement

Given a **sorted array** of `N` integers and a target value `X`, return the **number of times** `X` appears in the array.

---

## Examples

### Example 1

**Input**

```text
arr = [2,2,3,3,3,3,4]

x = 3
```

**Output**

```text
4
```

**Explanation**

```text
3 appears at indices

2,3,4,5

Total = 4
```

---

### Example 2

**Input**

```text
arr = [1,1,2,2,2,2,2,3]

x = 2
```

**Output**

```text
5
```

---

# Core Idea

This problem is a direct extension of

> **Leetcode 34 - Find First and Last Position**

Instead of returning

```text
[first,last]
```

we only need the

```text
count
```

Since the array is sorted,

all occurrences of the target appear together in one continuous block.

```
1 2 2 2 2 2 3

    <----->
     Target Block
```

The size of this block is

```text
Upper Bound - Lower Bound
```

---

# Pattern

```text
Binary Search
```

---

# Key Observation

Suppose

```text
Array

1 2 2 2 3 4 5
```

Target

```text
2
```

Lower Bound

```text
First element >=2

↓

Index 1
```

Upper Bound

```text
First element >2

↓

Index 4
```

Number of occurrences

```text
4-1

=

3
```

---

# Formula

```text
Count

=

Upper Bound

-

Lower Bound
```

This is the entire solution.

---

# Brute Force Approach

## Idea

Traverse the array.

Increase the counter whenever

```text
arr[i]==target
```

---

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int count(vector<int>& arr, int n, int x) {

    int cnt = 0;

    for(int i=0;i<n;i++){

        if(arr[i]==x)
            cnt++;
    }

    return cnt;
}
```

---

## Dry Run

```text
Array

2 4 6 8 8 8 11 13

Target=8
```

```
2 ❌

4 ❌

6 ❌

8 ✅

cnt=1

8 ✅

cnt=2

8 ✅

cnt=3

11 ❌

13 ❌
```

Answer

```text
3
```

---

## Complexity

### Time

```text
O(N)
```

### Space

```text
O(1)
```

---

# Optimal Approach (Binary Search)

## Idea

Instead of counting manually,

find

- Lower Bound
- Upper Bound

Then

```text
Count

=

UB-LB
```

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Returns first index >= target
int lowerBound(vector<int>& arr, int target) {

    int low=0;
    int high=arr.size()-1;
    int ans=arr.size();

    while(low<=high){

        int mid=low+(high-low)/2;

        if(arr[mid]>=target){

            ans=mid;

            high=mid-1;
        }
        else{

            low=mid+1;
        }
    }

    return ans;
}

// Returns first index > target
int upperBound(vector<int>& arr, int target){

    int low=0;
    int high=arr.size()-1;
    int ans=arr.size();

    while(low<=high){

        int mid=low+(high-low)/2;

        if(arr[mid]>target){

            ans=mid;

            high=mid-1;
        }
        else{

            low=mid+1;
        }
    }

    return ans;
}

int countOccurrences(vector<int>& arr,int target){

    int lb=lowerBound(arr,target);

    int ub=upperBound(arr,target);

    return ub-lb;
}
```

---

# Why Does UB − LB Work?

Suppose

```text
Index

0 1 2 3 4 5 6

Value

1 2 2 2 3 4 5
```

Lower Bound

```text
↓

1
```

Upper Bound

```text
↓

4
```

The target occupies

```text
Indices

1

2

3
```

How many indices?

```
4-1

=

3
```

Exactly the number of occurrences.

---

# Complete Visualization

```
Index

0 1 2 3 4 5 6

Value

1 2 2 2 3 4 5

  LB      UB
   ↓       ↓

1 2 2 2 3 4 5

  <----->

Target Block

Size

=

UB-LB
```

---

# Pointer Placement (Lower Bound)

Need

```text
First element >=2
```

Initial

```text
1 2 2 2 3 4 5

L     M     H
```

```
mid=3

arr[mid]=2
```

Possible answer

```text
lb=3
```

Move LEFT

---

Next

```text
1 2 2 2 3 4 5

L M H
```

```
mid=1

arr[mid]=2
```

Better answer

```text
lb=1
```

Move LEFT

Loop Ends

```text
LB=1
```

---

# Pointer Placement (Upper Bound)

Need

```text
First element >2
```

Initial

```text
1 2 2 2 3 4 5

L     M     H
```

```
mid=3

2<=2
```

Move RIGHT

---

Next

```text
1 2 2 2 3 4 5

        L M H
```

```
mid=5

4>2
```

Possible answer

```text
ub=5
```

Move LEFT

---

Next

```text
1 2 2 2 3 4 5

        L
        M
        H
```

```
mid=4

3>2
```

Better answer

```text
ub=4
```

Loop Ends

Upper Bound

```text
4
```

---

# Dry Run

Input

```text
arr=[1,2,2,2,3,4,5]

target=2
```

---

## Lower Bound

Initial

```text
low=0

high=6

lb=7
```

---

Iteration 1

```text
mid=3

arr[mid]=2
```

Store

```text
lb=3
```

Move Left

---

Iteration 2

```text
mid=1

arr[mid]=2
```

Store

```text
lb=1
```

Move Left

---

Iteration 3

```text
mid=0

arr[mid]=1
```

Move Right

Stop

```text
LB=1
```

---

## Upper Bound

Initial

```text
low=0

high=6

ub=7
```

---

Iteration 1

```text
mid=3

2<=2
```

Move Right

---

Iteration 2

```text
mid=5

4>2
```

Store

```text
ub=5
```

Move Left

---

Iteration 3

```text
mid=4

3>2
```

Store

```text
ub=4
```

Move Left

Stop

```text
UB=4
```

---

Answer

```text
Count

=

4-1

=

3
```

---

# Dry Run (Target Missing)

Input

```text
arr=[1,2,2,2,3]

target=5
```

Lower Bound

```text
5
```

Upper Bound

```text
5
```

Count

```text
5-5

=

0
```

Correct.

---

# Relationship with Previous Problems

| Problem | Formula |
|----------|---------|
| Lower Bound | First index ≥ target |
| Upper Bound | First index > target |
| First Occurrence | Lower Bound |
| Last Occurrence | Upper Bound − 1 |
| Count Occurrences | Upper Bound − Lower Bound |

---

# Binary Search Flow

```
            Target

               │

       Lower Bound

               │

 First Occurrence

               │

       Upper Bound

               │

 First Index After Target

               │

 UB - LB

               │

 Count
```

---

# Edge Cases

## Empty Array

```text
[]

↓

Count=0
```

---

## Single Element

```text
[5]

Target=5

↓

Count=1
```

---

## All Elements Same

```text
[3,3,3,3]

↓

Count=4
```

---

## Target Missing

```text
[1,2,3]

Target=6

↓

0
```

---

# Complexity

## Brute Force

### Time

```text
O(N)
```

### Space

```text
O(1)
```

---

## Optimal

Lower Bound

```text
O(logN)
```

Upper Bound

```text
O(logN)
```

Overall

```text
O(logN)
```

---

### Space

```text
O(1)
```

---

# Revision Template

```text
1. Find Lower Bound

↓

First occurrence

2. Find Upper Bound

↓

First element after target

3. Count

=

UB-LB
```

---

# Memory Trick

```text
Target Block

<------->

LB        UB

Size

=

UB-LB
```

Think of the target values as one continuous block. The count is simply the width of that block.

---

# Key Takeaways

- All occurrences of a target in a sorted array form one continuous block.
- **Lower Bound** points to the start of the block.
- **Upper Bound** points to the first element after the block.
- The number of occurrences is simply:
  ```text
  Upper Bound - Lower Bound
  ```
- This solution runs in **O(log N)** time with **O(1)** extra space.

---

# Final Intuition

> In a sorted array, duplicate values are contiguous. Binary Search can locate the **start** of the target block (Lower Bound) and the **end boundary** of the block (Upper Bound). The distance between these two boundaries is exactly the number of occurrences.