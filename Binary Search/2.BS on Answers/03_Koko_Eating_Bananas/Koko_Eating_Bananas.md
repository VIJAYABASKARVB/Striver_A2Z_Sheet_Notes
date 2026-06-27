# Koko Eating Bananas

---

# Problem Statement

Koko has `N` piles of bananas.

- `piles[i]` represents the number of bananas in the `iᵗʰ` pile.
- Every hour, Koko chooses **one pile** and eats **k bananas**.
- If a pile has fewer than `k` bananas, Koko finishes that pile and waits until the next hour to choose another pile.

Given `h` hours, find the **minimum eating speed `k` (bananas/hour)** so that Koko can finish all the bananas within `h` hours.

---

# Examples

## Example 1

**Input**

```text
piles = [7,15,6,3]
h = 8
```

**Output**

```text
5
```

**Explanation**

```
Speed = 5

7  → 2 hrs

15 → 3 hrs

6  → 2 hrs

3  → 1 hr

Total = 8 hrs
```

---

## Example 2

**Input**

```text
piles = [25,12,8,14,19]
h = 5
```

**Output**

```text
25
```

Every pile must be finished in one hour, so the speed must be at least the largest pile.

---

# Core Idea / Pattern Recognition

**Pattern**

```
Binary Search on Answer
```

### Why?

We are searching for the **minimum valid eating speed**.

Possible speeds are

```
1 2 3 ... maxPile
```

If a speed works, every larger speed also works.

This forms a **monotonic search space**, making Binary Search applicable.

---

# Observation

Suppose

```
Speed = 3
```

Hours required

```
12 bananas

↓

12 / 3 = 4 hrs
```

Suppose

```
Speed = 6
```

```
12 / 6 = 2 hrs
```

Increasing the speed **never increases** the required hours.

```
Speed ↑

↓

Hours ↓
```

This monotonic relationship is why Binary Search works.

---

# Approach 1 — Brute Force

## Idea

Try every possible eating speed from `1` to the largest pile.

The first speed that finishes all bananas within `h` hours is the answer.

---

## Algorithm

1. Find the maximum pile.
2. Try every speed from `1` to `maxPile`.
3. Calculate total hours required.
4. Return the first valid speed.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to calculate total hours for given speed
    int calculateTotalHours(vector<int>& a, int hourly) {
        int totalHours = 0;
        for (int pile : a) {
            totalHours += (pile + hourly - 1) / hourly;
        }
        return totalHours;
    }

    int minEatingSpeed(vector<int>& a, int h) {
        int maxVal = *max_element(a.begin(), a.end());

        for (int i = 1; i <= maxVal; i++) {
            int hours = calculateTotalHours(a, i);

            if (hours <= h) {
                return i;
            }
        }
        return maxVal;
    }
};
```

---

## Visualization

```
Try Speed

1

↓

2

↓

3

↓

4

↓

5 ✅
```

The first valid speed is the answer.

---

## Dry Run

```
Speed = 1

Hours = 31

Too Slow

↓

Speed = 2

Hours = 17

↓

...

↓

Speed = 5

Hours = 8

Answer
```

---

## Complexity

**Time:** `O(N × maxPile)`

**Space:** `O(1)`

---

# Approach 2 — Optimal Approach

## Main Idea

Instead of checking every speed,

Binary Search the answer.

Search Space

```
1 ........ maxPile
```

For every speed,

calculate total hours.

- If it finishes within `h` hours, try a **smaller** speed.
- Otherwise, try a **larger** speed.

---

## Why It Works

The answer space is monotonic.

Example

```
Hours Allowed = 8
```

| Speed | Hours |
|------:|------:|
| 2 | 17 |
| 3 | 12 |
| 4 | 10 |
| 5 | 8 ✅ |
| 6 | 7 ✅ |
| 7 | 6 ✅ |

Notice

```
Invalid

↓

Invalid

↓

Valid

↓

Valid

↓

Valid
```

Once a speed becomes valid,

every larger speed is also valid.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calculateTotalHours(vector<int>& piles, int speed) {
        int totalH = 0;
        for (int bananas : piles) {
            totalH += ceil((double)bananas / speed);
        }
        return totalH;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int maxPile = *max_element(piles.begin(), piles.end());

        int low = 1, high = maxPile;
        int ans = maxPile;

        while (low <= high) {
            int mid = (low + high) / 2;
            int totalH = calculateTotalHours(piles, mid);

            if (totalH <= h) {
                ans = mid;
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        return ans;
    }
};
```

---

## Pointer Placement Visualization

Example

```
piles = [7,15,6,3]

h = 8
```

Search Space

```
1 --------------------15

         M
```

Suppose

```
mid = 8

Hours = 5
```

Valid

```
Answer = 8

Search Left
```

```
1 --------7

    M
```

Suppose

```
mid = 4

Hours = 9
```

Too Slow

```
Search Right
```

Eventually

```
Speed = 5
```

---

## Dry Run

```
piles

7 15 6 3

h = 8
```

### Iteration 1

```
low=1

high=15

mid=8
```

Hours

```
1+2+1+1

=

5
```

Valid

```
ans=8

high=7
```

---

### Iteration 2

```
low=1

high=7

mid=4
```

Hours

```
2+4+2+1

=

9
```

Too Slow

```
low=5
```

---

### Iteration 3

```
low=5

high=7

mid=6
```

Hours

```
2+3+1+1

=

7
```

Valid

```
ans=6

high=5
```

---

### Iteration 4

```
low=5

high=5

mid=5
```

Hours

```
2+3+2+1

=

8
```

Valid

```
ans=5

high=4
```

Loop ends.

Return

```
5
```

---

## Why Do We Use Ceiling?

Suppose

```
Pile = 7

Speed = 3
```

```
7 / 3

=

2.33
```

Koko needs **3 full hours**.

Using integer division

```
7 / 3

=

2
```

is incorrect.

Correct calculation

```cpp
ceil((double)7 / 3)

=

3
```

or the faster integer formula

```cpp
(pile + speed - 1) / speed
```

Example

```
(7+3-1)/3

=

9/3

=

3
```

---

## Edge Cases

- Single pile
- `h == number of piles`
- `h` very large
- Largest pile equals answer
- Very large pile values (use `long long` if needed for total hours)

---

## Complexity

### Time

```
O(N × log(maxPile))
```

- Binary Search runs `log(maxPile)` times.
- Each iteration scans all piles.

### Space

```
O(1)
```

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Linear Search | `O(N × maxPile)` | `O(1)` | Try every speed |
| Binary Search | `O(N × log(maxPile))` | `O(1)` | Search on the answer |

---

# Key Takeaways

- Search on the **answer**, not the piles.
- Search space is `1` to `maxPile`.
- If a speed works, every larger speed also works.
- Use **ceiling division** to compute hours.
- Keep searching left to find the minimum valid speed.

---

# Revision Template

1. Search space = `1` to `maxPile`.
2. Find `mid` speed.
3. Compute total hours.
4. If `hours <= h`, save answer and search left.
5. Else search right.
6. Return minimum valid speed.

---

# Memory Trick

```
Speed

↓

Calculate Hours

↓

Hours <= h ?

↓

YES

Save Answer

Go Left

↓

NO

Go Right
```

Remember:

> **"Find the first eating speed that finishes all bananas within the given hours."**

---

# Final Intuition

> Binary search the eating speed and use the total hours required at each speed to decide whether to search for a slower or faster valid speed.