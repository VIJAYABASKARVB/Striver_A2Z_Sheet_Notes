# Queue Using Array (Circular)

## Problem Statement

Implement a **Queue** using a fixed-size array of size `n`.

The queue must support:

- `enqueue(x)` – Insert element `x` at the rear.
- `dequeue()` – Remove the front element.
- `getFront()` – Return the front element, or `-1` if empty.
- `getRear()` – Return the rear element, or `-1` if empty.
- `isEmpty()` – Return `true` if empty, else `false`.
- `isFull()` – Return `true` if full, else `false`.

---

## Examples

### Example 1

**Input:** `n = 3`, queries: `[[1,5], [1,3], [1,4], [3], [2], [5], [4]]`

**Output:** `[5, false, 4]`

**Explanation:**

- `enqueue(5)` → queue: `[5]`
- `enqueue(3)` → queue: `[5, 3]`
- `enqueue(4)` → queue: `[5, 3, 4]`
- `getFront()` → `5`
- `dequeue()` → removes `5`, queue: `[3, 4]`
- `isEmpty()` → `false`
- `getRear()` → `4`

### Example 2

**Input:** `n = 2`, queries: `[[4], [1,3], [1,7], [6]]`

**Output:** `[-1, true]`

**Explanation:**

- `getRear()` → empty → `-1`
- `enqueue(3)` → queue: `[3]`
- `enqueue(7)` → queue: `[3, 7]`
- `isFull()` → `true`

---

## Visual Representation

### Circular Array Concept

Using a circular array avoids shifting elements after dequeue.

```text
Initial: start = -1, end = -1, currSize = 0
         [ ] [ ] [ ] [ ] [ ]
         0   1   2   3   4

After enqueue(10), enqueue(20), enqueue(30):
         [10][20][30][ ] [ ]
          ↑        ↑
        start    end = 2

After dequeue() (removes 10):
         [ ] [20][30][ ] [ ]
              ↑    ↑
            start end = 2

After enqueue(40):
         [40][20][30][ ] [ ]
          ↑    ↑    ↑
        end  start  (circular wrap)
```

`end = (end + 1) % maxSize` wraps to index `0`.

---

## Code Implementation (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

class myQueue {
private:
    int* arr;
    int start;
    int end;
    int currSize;
    int maxSize;

public:
    myQueue(int n) {
        arr = new int[n];
        start = -1;
        end = -1;
        currSize = 0;
        maxSize = n;
    }

    ~myQueue() {
        delete[] arr;
    }

    bool isEmpty() {
        return start == -1;
    }

    bool isFull() {
        return currSize == maxSize;
    }

    void enqueue(int x) {
        if (isFull()) return;

        if (currSize == 0) {
            start = 0;
            end = 0;
        } else {
            end = (end + 1) % maxSize;
        }

        arr[end] = x;
        currSize++;
    }

    void dequeue() {
        if (isEmpty()) return;

        if (currSize == 1) {
            start = -1;
            end = -1;
        } else {
            start = (start + 1) % maxSize;
        }

        currSize--;
    }

    int getFront() {
        if (isEmpty()) return -1;
        return arr[start];
    }

    int getRear() {
        if (isEmpty()) return -1;
        return arr[end];
    }
};
```

---

## Dry Run

### Example 1: `n = 3`, queries:

`[enqueue(5), enqueue(3), enqueue(4), getFront(), dequeue(), isEmpty(), getRear()]`

| Operation | start | end | currSize | Array (circular) | Result |
|----------|----------|----------|----------|----------|----------|
| Initial | -1 | -1 | 0 | `[_, _, _]` | – |
| enqueue(5) | 0 | 0 | 1 | `[5, _, _]` | – |
| enqueue(3) | 0 | 1 | 2 | `[5, 3, _]` | – |
| enqueue(4) | 0 | 2 | 3 | `[5, 3, 4]` | – |
| getFront() | 0 | 2 | 3 | `[5, 3, 4]` | 5 |
| dequeue() | 1 | 2 | 2 | `[_, 3, 4]` (logical) | – |
| isEmpty() | 1 | 2 | 2 | – | false |
| getRear() | 1 | 2 | 2 | – | 4 |

### Example 2: `n = 2`, queries:

`[getRear(), enqueue(3), enqueue(7), isFull()]`

| Operation | start | end | currSize | Array | Result |
|----------|----------|----------|----------|----------|----------|
| Initial | -1 | -1 | 0 | `[_, _]` | – |
| getRear() | -1 | -1 | 0 | – | -1 |
| enqueue(3) | 0 | 0 | 1 | `[3, _]` | – |
| enqueue(7) | 0 | 1 | 2 | `[3, 7]` | – |
| isFull() | 0 | 1 | 2 | – | true |

---

## Complexity Analysis

| Operation | Time | Space |
|----------|----------|----------|
| enqueue | O(1) | O(1) |
| dequeue | O(1) | O(1) |
| getFront | O(1) | O(1) |
| getRear | O(1) | O(1) |
| isEmpty | O(1) | O(1) |
| isFull | O(1) | O(1) |

- **Space:** `O(n)` for storing `n` elements.

---

## Key Takeaways

- Circular array reuses empty slots, avoiding `O(n)` shifts.
- `start` and `end` move circularly using `(index + 1) % maxSize`.
- Track `currSize` to differentiate between full and empty.
- If `currSize == 0`, both `start` and `end` are `-1`.
- Always check `isFull()` before `enqueue()` and `isEmpty()` before `dequeue()` or access.
- The destructor frees the allocated array to prevent memory leaks.

---

## Edge Cases

| Case | Operation | Result |
|----------|----------|----------|
| Empty queue | `dequeue()` | No change |
| Full queue | `enqueue()` | No change |
| Empty queue | `getFront()` / `getRear()` | Returns `-1` |
| Single element | `dequeue()` | `start = end = -1`, empty |
| Circular wrap | Multiple enqueue/dequeue | Pointers wrap correctly |

---

## Quick Revision Points

1. Use a circular array.
2. `enqueue`: move `end` forward circularly.
3. `dequeue`: move `start` forward circularly.
4. Maintain `currSize`.
5. `isEmpty`: `start == -1`.
6. `isFull`: `currSize == maxSize`.
7. `getFront`: return `arr[start]`.
8. `getRear`: return `arr[end]`.