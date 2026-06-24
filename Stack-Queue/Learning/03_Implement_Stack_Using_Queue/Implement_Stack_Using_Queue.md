# Implement Stack using Single Queue

## Problem Statement

Implement a **Last-In-First-Out (LIFO)** stack using **one queue**.

The stack must support:

- `push(x)` – Push element `x` onto the stack.
- `pop()` – Remove and return the top element.
- `top()` – Return the top element without removing it.
- `isEmpty()` – Return `true` if the stack is empty, else `false`.

---

## Examples

### Example 1

**Input:**

```text
["QueueStack", "push", "push", "pop", "top", "isEmpty"]
[[], [4], [8], [], [], []]
```

**Output:**

```text
[null, null, null, 8, 4, false]
```

**Explanation:**

```text
push(4) → [4]
push(8) → [4, 8]
pop()   → 8, stack becomes [4]
top()   → 4
isEmpty() → false
```

### Example 2

**Input:**

```text
["QueueStack", "isEmpty"]
[[]]
```

**Output:**

```text
[null, true]
```

---

## Visual Representation

### Core Trick

After every `push(x)`, rotate the queue so that the newly inserted element comes to the front.

```text
push(x):
1. Insert x at the rear.
2. Rotate the queue size-1 times.
3. Now x becomes the front, which acts like the top of the stack.
```

---

### Example: push(4), push(8)

```text
Step 1: push(4)

Queue:
[4]
front = 4
top   = 4

Step 2: push(8)

Before rotation:
[4, 8]

Rotate once:
pop 4 → push 4

After rotation:
[8, 4]

Now:
front = 8
top   = 8
```

### Example: push(2)

```text
Current queue:
[8, 4]

push(2) → [8, 4, 2]

Rotate twice:
1. pop 8 → push 8 → [4, 2, 8]
2. pop 4 → push 4 → [2, 8, 4]

Final:
[2, 8, 4]

front = 2
top   = 2
```

---

## Approach

### Algorithm

#### push(x)

1. Store current queue size `s`.
2. Push `x` to the queue.
3. Rotate the queue `s` times:
   - take front element,
   - remove it,
   - push it back.
4. After rotation, `x` becomes the front.

#### pop()

- Remove and return the front element.

#### top()

- Return the front element without removing it.

#### isEmpty()

- Return `q.empty()`.

---

## Code Implementation (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

class QueueStack {
    queue<int> q;   // single queue

public:
    void push(int x) {
        int s = q.size();   // number of existing elements
        q.push(x);          // insert new element at rear

        // Rotate all previous elements behind x
        for (int i = 0; i < s; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int front = q.front();
        q.pop();
        return front;
    }

    int top() {
        return q.front();
    }

    bool isEmpty() {
        return q.empty();
    }
};

int main() {
    QueueStack st;

    vector<string> commands = {
        "QueueStack", "push", "push", "pop", "top", "isEmpty"
    };

    vector<vector<int>> inputs = {
        {}, {4}, {8}, {}, {}, {}
    };

    for (int i = 0; i < commands.size(); i++) {
        if (commands[i] == "QueueStack") {
            cout << "null ";
        }
        else if (commands[i] == "push") {
            st.push(inputs[i][0]);
            cout << "null ";
        }
        else if (commands[i] == "pop") {
            cout << st.pop() << " ";
        }
        else if (commands[i] == "top") {
            cout << st.top() << " ";
        }
        else if (commands[i] == "isEmpty") {
            cout << (st.isEmpty() ? "true" : "false") << " ";
        }
    }

    return 0;
}
```

---

## Dry Run

### Input Sequence

```text
push(4), push(8), pop(), top(), isEmpty()
```

| Operation | Before Queue | Action | After Queue | Result |
|----------|----------|----------|----------|----------|
| push(4) | `[]` | push 4 | `[4]` | - |
| push(8) | `[4]` | push 8, rotate 1 time | `[8, 4]` | - |
| pop() | `[8, 4]` | remove front | `[4]` | 8 |
| top() | `[4]` | read front | `[4]` | 4 |
| isEmpty() | `[4]` | check empty | `[4]` | false |

---

## Complexity Analysis

| Operation | Time | Space |
|----------|----------|----------|
| `push(x)` | O(n) | O(1) |
| `pop()` | O(1) | O(1) |
| `top()` | O(1) | O(1) |
| `isEmpty()` | O(1) | O(1) |

- **Space:** `O(n)` for storing the stack elements in the queue.

---

## Key Takeaways

- A single queue can simulate a stack by rotating elements after each push.
- `push()` is expensive because it rotates the queue.
- `pop()`, `top()`, and `isEmpty()` are all constant time.
- The front of the queue always represents the top of the stack.
- This is a clean LIFO simulation using FIFO structure.

---

## Edge Cases

| Case | Operation | Result |
|----------|----------|----------|
| Empty stack | `isEmpty()` | `true` |
| Empty stack | `pop()` / `top()` | Undefined, should not be called |
| Single element | `push(5)`, `pop()` | returns `5`, stack becomes empty |
| Multiple pushes | order preserved | latest pushed element stays at front |

---

## Quick Revision Points

1. Push element to the rear.
2. Rotate the queue `size-1` times.
3. After rotation, new element becomes the front.
4. `pop()` removes the front.
5. `top()` returns the front.
6. `isEmpty()` checks `q.empty()`.
7. `push()` = O(n), others = O(1).

---

## Visual Memory Aid

```text
After push(x):

[old elements ..., x]
        ↓ rotate
[x, old elements ...]
```

### Mental Model

```text
Queue front = Stack top
```

```text
push → rotate → front becomes newest element
pop  → remove front
top  → read front
```