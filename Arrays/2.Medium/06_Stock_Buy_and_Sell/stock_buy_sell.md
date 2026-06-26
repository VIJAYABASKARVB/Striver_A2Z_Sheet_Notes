# Stock Buy and Sell

## Problem Statement

You are given an array `prices` where `prices[i]` represents the stock price on the `i`-th day.

You want to maximize your profit by performing **exactly one transaction**:

- Buy one stock on one day.
- Sell it on a **future** day.

Return the maximum profit you can achieve.

If no profit is possible, return `0`.

---

## Examples

### Example 1

**Input**

```text
prices = [7,1,5,3,6,4]
```

**Output**

```text
5
```

**Explanation**

Buy on **Day 2** (price = `1`) and sell on **Day 5** (price = `6`).

```text
Profit = 6 - 1 = 5
```

---

### Example 2

**Input**

```text
prices = [7,6,4,3,1]
```

**Output**

```text
0
```

**Explanation**

The prices continuously decrease, so no profitable transaction is possible.

---

# Core Idea

We need to maximize

```text
Selling Price - Buying Price
```

Since buying must happen **before** selling, while traversing the array we only need to know:

- the **minimum price seen so far** (best buying day)
- the **maximum profit seen so far**

This leads to a simple **single-pass greedy algorithm**.

---

# 1) Brute Force Approach

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to calculate max profit using brute force
    int stockbuySell(vector<int>& prices) {
        int maxProfit = 0;

        // Try every possible buy day
        for(int i = 0; i < prices.size(); i++) {

            // Try every possible sell day after buying
            for(int j = i + 1; j < prices.size(); j++) {

                int profit = prices[j] - prices[i];

                maxProfit = max(maxProfit, profit);
            }
        }

        return maxProfit;
    }
};
```

---

## How It Works

- Choose every day as the buying day.
- Choose every future day as the selling day.
- Calculate the profit.
- Store the maximum profit.

---

## Visualization

```
Buy Day

Day0  Day1  Day2  Day3 ...

 ↓

Try selling on every future day

        ↓
Day1 Day2 Day3 Day4 ...
```

Every possible pair is checked.

---

## Complexity

- **Time:** `O(n²)`
- **Space:** `O(1)`

---

# 2) Optimal Approach — Greedy (Single Pass)

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stockbuySell(vector<int>& prices) {

        int minPrice = INT_MAX;
        int maxProfit = 0;

        for (int price : prices) {

            // Better buying price found
            if (price < minPrice) {
                minPrice = price;
            }

            // Sell today
            else {
                maxProfit = max(maxProfit,
                                price - minPrice);
            }
        }

        return maxProfit;
    }
};
```

---

# Main Intuition

Imagine you are walking through the days one by one.

At every day, ask two questions:

### Question 1

> Is today's price the cheapest price I've ever seen?

If yes,

```
Update minPrice
```

because this becomes the best day to buy.

---

### Question 2

If I sell today,

```
How much profit do I make?
```

```
profit = current price - minPrice
```

If this profit is larger than the previous answer,

update

```
maxProfit
```

---

# Visual Understanding

Suppose

```
Prices

7   1   5   3   6   4
```

We continuously remember

```
Minimum Price Seen

7

↓

1

↓

1

↓

1

↓

1

↓

1
```

Now compute profits

```
Sell at 7

Profit = 0

Sell at 1

Profit = 0

Sell at 5

Profit = 5 - 1 = 4

Sell at 3

Profit = 3 - 1 = 2

Sell at 6

Profit = 6 - 1 = 5

Sell at 4

Profit = 4 - 1 = 3
```

Maximum profit is

```
5
```

---

# Dry Run

## Input

```text
prices = [7,1,5,3,6,4]
```

### Initial State

```
minPrice = +∞

maxProfit = 0
```

| Day | Price | minPrice | Profit Today | maxProfit |
|----:|------:|---------:|-------------:|----------:|
| 1 | 7 | 7 | 0 | 0 |
| 2 | 1 | 1 | 0 | 0 |
| 3 | 5 | 1 | 4 | 4 |
| 4 | 3 | 1 | 2 | 4 |
| 5 | 6 | 1 | 5 | 5 |
| 6 | 4 | 1 | 3 | 5 |

---

Final Answer

```
Maximum Profit = 5
```

---

# Why This Works

Suppose today's price is

```
6
```

To maximize profit, we should have bought at

```
the minimum price before today
```

There is **no reason** to buy at any higher price.

So remembering only

```
minimum price so far
```

is enough.

Every day gives us one possible selling opportunity.

---

# Why `maxProfit` Starts at 0

Suppose

```
prices = [7,6,5,4,3]
```

Every profit becomes

```
negative
```

Since we are allowed **not to trade**, the answer should be

```
0
```

---

# Complexity Analysis

## Brute Force

**Time**

```
O(n²)
```

**Space**

```
O(1)
```

---

## Optimal Greedy

**Time**

```
O(n)
```

**Space**

```
O(1)
```

---

# Key Takeaways

- Buying must happen **before** selling.
- Track the **minimum price seen so far**.
- Every new day represents a possible selling day.
- Compute today's profit using the cheapest buying day.
- Keep the maximum profit.

---

# Revision Template

```text
1. minPrice = INT_MAX

2. maxProfit = 0

3. Traverse every price

4. If current price is smaller
      update minPrice

5. Else
      profit = currentPrice - minPrice

6. Update maxProfit

7. Return maxProfit
```

---

# One-Line Intuition

> **Always remember the cheapest stock price seen so far, and treat every new day as a possible selling day.**