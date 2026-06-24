# Implement Stack using Array

## Problem Statement

Design a **Stack** data structure using a **fixed-size array**.

Implement the following operations:

- `push(x)` – Insert element `x` at the top of the stack.
- `pop()` – Remove the element from the top.
- `peek()` – Return the top element without removing it.
- `isEmpty()` – Check if the stack is empty.
- `isFull()` – Check if the stack is full.

---

## Visual Representation

### Stack as an Array

```text
Stack (size = 5) initially empty:
Index:  0   1   2   3   4
       [ ] [ ] [ ] [ ] [ ]
        top = -1

After push(10), push(20), push(30):
Index:  0   1   2   3   4
       [10][20][30][ ] [ ]
                ↑
               top = 2

After pop():
Index:  0   1   2   3   4
       [10][20][ ] [ ] [ ]
            ↑
           top = 1

After peek(): returns 20 (top element)
```

### Operations Overview

```text
push(x):   if not full → top++; arr[top] = x
pop():     if not empty → top--
peek():    if not empty → return arr[top]
isEmpty(): top == -1
isFull():  top == size - 1
```

---

## Code Implementation (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

class myStack {
private:
    int* arr;   // pointer to array
    int size;   // maximum capacity
    int top;    // index of top element (-1 if empty)

public:
    // Constructor
    myStack(int n) {
        size = n;
        arr = new int[size];
        top = -1;
    }

    // Destructor
    ~myStack() {
        delete[] arr;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == size - 1;
    }

    void push(int x) {
        if (isFull()) return;   // stack overflow
        arr[++top] = x;
    }

    void pop() {
        if (isEmpty()) return;  // stack underflow
        top--;
    }

    int peek() {
        if (isEmpty()) return -1;
        return arr[top];
    }
};
```

### Usage Example

```cpp
int main() {
    myStack st(5);

    st.push(10);
    st.push(20);
    st.push(30);

    cout << st.peek() << endl;    // 30

    st.pop();

    cout << st.peek() << endl;    // 20
    cout << st.isEmpty() << endl;  // 0 (false)

    return 0;
}
```

---

## Dry Run

### Push Operations

| Operation | top (before) | top (after) | Array State |
|----------|----------|----------|----------|
| push(10) | -1 | 0 | `[10, _, _, _, _]` |
| push(20) | 0 | 1 | `[10, 20, _, _, _]` |
| push(30) | 1 | 2 | `[10, 20, 30, _, _]` |

### Pop & Peek

| Operation | top (before) | top (after) | Return | Array State |
|----------|----------|----------|----------|----------|
| peek() | 2 | 2 | 30 | `[10, 20, 30, _, _]` |
| pop() | 2 | 1 | – | `[10, 20, _, _, _]` |
| peek() | 1 | 1 | 20 | `[10, 20, _, _, _]` |

---

## Complexity Analysis

| Operation | Time | Space |
|----------|----------|----------|
| push | O(1) | O(1) |
| pop | O(1) | O(1) |
| peek | O(1) | O(1) |
| isEmpty | O(1) | O(1) |
| isFull | O(1) | O(1) |

- **Space:** O(n) for storing `n` elements.

---

## Key Takeaways

- Fixed capacity is defined at creation.
- Stack follows **LIFO** (Last In First Out) behavior.
- Array-based implementation is simple and fast.
- Limitation: size is fixed and cannot grow dynamically.
- Always check `isFull()` before `push()` and `isEmpty()` before `pop()`.
- `top` starts at `-1` and increments on push.

---

## Edge Cases

| Case | Operation | Result |
|----------|----------|----------|
| Stack empty | `pop()` | No change (underflow avoided) |
| Stack full | `push()` | No change (overflow avoided) |
| Stack empty | `peek()` | Returns `-1` |
| Stack with one element | `pop()` | `top` becomes `-1` |

---

## Quick Revision Points

1. Constructor: allocate array, set `top = -1`.
2. `push`: `arr[++top] = x`.
3. `pop`: `top--`.
4. `peek`: `return arr[top]`.
5. `isEmpty`: `top == -1`.
6. `isFull`: `top == size - 1`.
7. Use `new` and `delete[]` for dynamic memory.
8. All operations are O(1).