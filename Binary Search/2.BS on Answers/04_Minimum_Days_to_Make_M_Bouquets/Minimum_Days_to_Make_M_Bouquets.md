# Minimum Days to Make M Bouquets

---

# Problem Statement

You are given an array `bloomDay` where `bloomDay[i]` represents the day the `iᵗʰ` flower blooms.

You need to make exactly **`m` bouquets**, and **each bouquet must contain `k` adjacent bloomed flowers**.

Find the **minimum day** on which it is possible to make at least `m` bouquets.

If it is impossible, return **-1**.

---

# Examples

## Example 1

**Input**

```text
bloomDay = [7,7,7,7,13,11,12,7]
m = 2
k = 3
```

**Output**

```text
12
```

---

## Example 2

**Input**

```text
bloomDay = [1,10,3,10,2]
m = 3
k = 2
```

**Output**

```text
-1
```

**Explanation**

Need

```
3 × 2 = 6 flowers
```

Only

```
5 flowers
```

Impossible.

---

# Core Idea / Pattern Recognition

**Pattern**

```
Binary Search on Answer
```

### Why?

We're searching for the **minimum valid day**.

If bouquets can be made on day `d`, then they can also be made on **every later day**.

```
Day ↑

↓

More flowers bloom

↓

More bouquets possible
```

This monotonic property makes Binary Search applicable.

---

# Observation

Suppose

```
Day = 7

Bloomed

✓ ✓ ✓ ✓ ✗ ✗ ✗ ✓
```

Not enough adjacent flowers.

Now

```
Day = 12

✓ ✓ ✓ ✓ ✗ ✓ ✓ ✓
```

Now we can make

```
[✓✓✓]

and

[✓✓✓]
```

As the day increases, the number of bloomed flowers never decreases.

---

# Approach 1 — Brute Force

## Idea

Try every day from the minimum bloom day to the maximum bloom day.

For each day, check whether at least `m` bouquets can be formed.

Return the first valid day.

---

## Algorithm

1. If `m × k > n`, return `-1`.
2. Try every day.
3. Count consecutive bloomed flowers.
4. Form bouquets whenever `k` adjacent flowers are available.
5. Return the first valid day.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class RoseGarden {
public:
    bool isPossible(vector<int>& bloomDays, int day, int m, int k) {
        int count = 0;
        int bouquets = 0;

        for (int bloom : bloomDays) {
            if (bloom <= day) {
                count++;
                if (count == k) {
                    bouquets++;
                    count = 0;
                }
            } else {
                count = 0;
            }
        }

        return bouquets >= m;
    }

    int minDaysToMakeBouquets(vector<int>& bloomDays, int m, int k) {
        long long totalFlowers = 1LL * m * k;
        if (totalFlowers > bloomDays.size()) return -1;

        int low = *min_element(bloomDays.begin(), bloomDays.end());
        int high = *max_element(bloomDays.begin(), bloomDays.end());

        for (int day = low; day <= high; ++day) {
            if (isPossible(bloomDays, day, m, k)) {
                return day;
            }
        }

        return -1;
    }
};
```

---

## Visualization

Day = 12

```
7 7 7 7 13 11 12 7

✓ ✓ ✓ ✓ ✗ ✓ ✓ ✓

Bouquet 1

[✓ ✓ ✓]

Bouquet 2

        [✓ ✓ ✓]
```

Answer

```
12
```

---

## Dry Run

```
Day = 7

Bouquets = 1

Not Enough

↓

Day = 8

Still 1

↓

...

↓

Day = 12

Bouquets = 2

Answer
```

---

## Complexity

**Time:** `O((maxDay - minDay) × N)`

**Space:** `O(1)`

---

# Approach 2 — Optimal Approach

## Main Idea

Instead of checking every day,

Binary Search the answer.

Search Space

```
Minimum Bloom Day

↓

Maximum Bloom Day
```

For every day,

check if `m` bouquets can be formed.

- Possible → Try an earlier day.
- Not possible → Try a later day.

---

## Why It Works

As the day increases,

more flowers bloom.

```
Day

↓

Bloomed Flowers

↓

Bouquets
```

Once a particular day becomes valid,

every later day is also valid.

Example

| Day | Possible |
|----:|:--------:|
| 8 | ❌ |
| 9 | ❌ |
| 10 | ❌ |
| 11 | ❌ |
| 12 | ✅ |
| 13 | ✅ |

Binary Search finds the **first valid day**.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool possible(vector<int>& arr, int day, int m, int k) {
        int cnt = 0;
        int bouquets = 0;

        for (int bloom : arr) {
            if (bloom <= day) {
                cnt++;
                if (cnt == k) {
                    bouquets++;
                    cnt = 0;
                }
            } else {
                cnt = 0;
            }
        }

        return bouquets >= m;
    }

    int roseGarden(vector<int>& arr, int k, int m) {
        long long total = 1LL * k * m;

        if (total > arr.size()) return -1;

        int low = *min_element(arr.begin(), arr.end());
        int high = *max_element(arr.begin(), arr.end());
        int result = -1;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (possible(arr, mid, m, k)) {
                result = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return result;
    }
};
```

---

## Pointer Placement Visualization

Search Space

```
7 ----------------13

       M
```

Suppose

```
Day = 10
```

```
Only 1 bouquet
```

Not enough.

```
Search Right
```

---

Next

```
11 --------13

     M
```

Suppose

```
Day = 12
```

```
2 bouquets
```

Valid.

```
Save

Search Left
```

Eventually

```
Answer = 12
```

---

## Dry Run

Input

```
7 7 7 7 13 11 12 7

m=2

k=3
```

### Iteration 1

```
low=7

high=13

mid=10
```

Possible?

```
No
```

```
low=11
```

---

### Iteration 2

```
low=11

high=13

mid=12
```

Possible?

```
Yes
```

```
answer=12

high=11
```

---

### Iteration 3

```
low=11

high=11

mid=11
```

Possible?

```
No
```

```
low=12
```

Loop ends.

Return

```
12
```

---

## How Does `possible()` Work?

Suppose

```
Day = 12
```

Flowers

```
7 7 7 7 13 11 12 7

✓ ✓ ✓ ✓ ✗ ✓ ✓ ✓
```

Traverse

```
✓

count=1

↓

✓

count=2

↓

✓

count=3

Bouquet++

count=0

↓

✓

count=1

↓

✗

count=0

↓

✓

count=1

↓

✓

count=2

↓

✓

count=3

Bouquet++
```

Total

```
2 bouquets
```

---

## Edge Cases

- `m × k > n`
- Only one bouquet
- Every flower blooms on the same day
- Already possible on the minimum day
- Only possible on the maximum day

---

## Complexity

### Time

```
O(N × log(maxDay - minDay))
```

- Binary Search over the range of days.
- Each check scans the array once.

### Space

```
O(1)
```

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Brute Force | `O((maxDay-minDay) × N)` | `O(1)` | Try every day |
| Binary Search | `O(N × log(maxDay-minDay))` | `O(1)` | Search on the answer |

---

# Key Takeaways

- Search on the **day**, not on the flowers.
- If bouquets are possible on day `d`, they are possible on every day after `d`.
- Count only **adjacent bloomed flowers**.
- Reset the consecutive count whenever an unbloomed flower is encountered.
- Always check `m × k > n` first.

---

# Revision Template

1. If `m × k > n`, return `-1`.
2. Search from minimum to maximum bloom day.
3. Binary Search on days.
4. Count consecutive bloomed flowers.
5. Every `k` consecutive flowers form one bouquet.
6. If enough bouquets are formed, search left.
7. Otherwise, search right.

---

# Memory Trick

```
Day

↓

Bloomed Flowers

↓

Adjacent Count

↓

Bouquets

↓

Enough?

↓

YES → Search Left

NO → Search Right
```

Remember:

> **"Find the first day on which enough adjacent bloomed flowers can form the required bouquets."**

---

# Final Intuition

> Binary search the number of days and, for each candidate day, greedily count consecutive bloomed flowers to determine whether the required number of bouquets can be formed.