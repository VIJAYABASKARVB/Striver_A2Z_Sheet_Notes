# Implement Queue using Stack

## Problem Statement

Implement a **First-In-First-Out (FIFO)** queue using **two stacks**.

The queue must support:

- `push(x)` – Add element `x` to the end of the queue.
- `pop()` – Remove and return the front element.
- `peek()` – Return the front element without removing it.
- `isEmpty()` – Return `true` if the queue is empty, else `false`.

---

## Examples

### Example 1

**Input:**

```text
["StackQueue", "push", "push", "pop", "peek", "isEmpty"]
[[], [4], [8], [], [], []]
```

**Output:**

```text
[null, null, null, 4, 8, false]
```

**Explanation:**

```text
push(4) → queue: [4]
push(8) → queue: [4, 8]
pop()   → returns 4, queue: [8]
peek()  → returns 8
isEmpty() → false
```

### Example 2

**Input:**

```text
["StackQueue", "isEmpty"]
[[]]
```

**Output:**

```text
[null, true]
```

---

## Visual Representation

### Two-Stack Approach

We use two stacks:

- `input` → used for `push`
- `output` → used for `pop` and `peek`

```text
push(x):
   input.push(x)

pop() / peek():
   If output is empty:
       transfer all elements from input to output
       (this reverses the order)

   Then pop/peek from output
```

---

### Example Sequence

Operations:

```text
push(4), push(8), pop(), push(5), peek()
```

#### Step 1: push(4)

```text
input : [4]
output: []
```

#### Step 2: push(8)

```text
input : [4, 8]
output: []
```

#### Step 3: pop()

`output` is empty, so transfer everything from `input` to `output`.

```text
Transfer:
input  → []
output → [8, 4]
```

Now pop from `output`:

```text
pop() returns 4
output → [8]
```

#### Step 4: push(5)

```text
input : [5]
output: [8]
```

#### Step 5: peek()

`output` is not empty, so return `output.top()`:

```text
peek() returns 8
```

---

## Approach Comparison

| Aspect | Method 1 (Push O(N)) | Method 2 (Push O(1)) |
|--------|----------------------|----------------------|
| push | O(N) | O(1) |
| pop | O(1) | Amortized O(1) |
| peek | O(1) | Amortized O(1) |
| space | O(N) | O(N) |
| best use | Simpler logic | More efficient overall |

---

# 🟡 Method 1: Push is O(N)

## Idea

Always keep the front element at the top of `st1`.

When pushing:

1. Move all elements from `st1` to `st2`
2. Push new element into `st1`
3. Move all elements back from `st2` to `st1`

---

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class StackQueue {
    stack<int> st1, st2;

public:
    void push(int x) {
        while (!st1.empty()) {
            st2.push(st1.top());
            st1.pop();
        }

        st1.push(x);

        while (!st2.empty()) {
            st1.push(st2.top());
            st2.pop();
        }
    }

    int pop() {
        if (st1.empty()) return -1;
        int val = st1.top();
        st1.pop();
        return val;
    }

    int peek() {
        if (st1.empty()) return -1;
        return st1.top();
    }

    bool isEmpty() {
        return st1.empty();
    }
};
```

### Complexity

- `push` = O(N)
- `pop` = O(1)
- `peek` = O(1)
- `isEmpty` = O(1)

---

# 🟢 Method 2: Push is O(1) (Preferred)

## Idea

Use:

- `input` stack for `push`
- `output` stack for `pop` and `peek`

Rules:

- `push(x)` → push directly into `input`
- `pop()` / `peek()`:
  - if `output` is empty, move all elements from `input` to `output`
  - then operate on `output`
- `isEmpty()` → both stacks must be empty

This gives **amortized O(1)** for `pop` and `peek`.

---

## C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class StackQueue {
    stack<int> input, output;

public:
    void push(int x) {
        input.push(x);
    }

    int pop() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }

        if (output.empty()) return -1;

        int val = output.top();
        output.pop();
        return val;
    }

    int peek() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }

        if (output.empty()) return -1;

        return output.top();
    }

    bool isEmpty() {
        return input.empty() && output.empty();
    }
};
```

---

## Dry Run (Method 2)

### Operations

```text
push(4), push(8), pop(), push(5), peek()
```

| Step | Operation | input | output | Result |
|------|----------|-------|--------|--------|
| 0 | Start | [] | [] | – |
| 1 | push(4) | [4] | [] | – |
| 2 | push(8) | [4, 8] | [] | – |
| 3 | pop() | [] | [8, 4] | 4 |
| 4 | push(5) | [5] | [8] | – |
| 5 | peek() | [5] | [8] | 8 |

---

## Complexity Analysis (Method 2)

| Operation | Time | Space |
|----------|----------|----------|
| push | O(1) | O(1) |
| pop | Amortized O(1) | O(1) |
| peek | Amortized O(1) | O(1) |
| isEmpty | O(1) | O(1) |

### Why amortized O(1)?

Each element:

- is pushed into `input` once
- moved to `output` at most once
- popped from `output` once

So over many operations, total work is linear.

---

## Key Takeaways

- Two stacks can simulate a queue.
- The **transfer** from `input` to `output` reverses order.
- `output` always represents the front side when it is non-empty.
- Method 2 is preferred because `push` is O(1).
- `pop` and `peek` become amortized O(1).

---

## Edge Cases

| Case | Operation | Result |
|------|-----------|--------|
| Empty queue | `pop()` / `peek()` | `-1` |
| Empty queue | `isEmpty()` | `true` |
| Many pushes before pop | Works correctly | Queue order preserved |
| Multiple transfers | Still correct | Each element transferred once |

---

## Quick Revision Points

1. Use two stacks: `input` and `output`.
2. `push(x)` → `input.push(x)`.
3. For `pop()` / `peek()`, transfer only when `output` is empty.
4. `pop()` removes `output.top()`.
5. `peek()` returns `output.top()`.
6. `isEmpty()` checks both stacks.
7. Preferred complexity: `push = O(1)`, `pop/peek = amortized O(1)`.

---

## Visual Memory Aid

```text
push(x) → input stack

pop/peek:
if output empty
    move all input → output
then use output.top()
```

```text
input  : [newer elements]
output : [older elements, front on top]
```