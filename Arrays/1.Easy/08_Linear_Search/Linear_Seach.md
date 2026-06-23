# Linear Search in C

## Problem Statement

Given an array and an element `num`, the task is to find whether `num` is present in the array or not.

- If present, return the **index** of the element.
- If not present, return **-1**.

---

## Examples

### Example 1

**Input:** `arr[] = {1, 2, 3, 4, 5}, num = 3`

**Output:** `2`

**Explanation:** `3` is present at index `2` (0-based indexing).

### Example 2

**Input:** `arr[] = {5, 4, 3, 2, 1}, num = 5`

**Output:** `0`

**Explanation:** `5` is present at index `0`.

---

## Visual Representation

### How Linear Search Works

```text
Array: [1, 2, 3, 4, 5]
Search For: 3

Step 1:
[1, 2, 3, 4, 5]
 ↑
1 != 3

Step 2:
[1, 2, 3, 4, 5]
    ↑
2 != 3

Step 3:
[1, 2, 3, 4, 5]
       ↑
3 == 3

Found at index 2
```

### Worst Case (Element Not Found)

```text
Array: [1, 2, 3, 4, 5]
Search For: 6

[1, 2, 3, 4, 5]
 ↑  ↑  ↑  ↑  ↑

Checked all elements.
No match found.

Return -1
```

---

## Algorithm

### Step 1

Start traversing the array from index `0`.

### Step 2

Compare each element with the target value `num`.

### Step 3

If a match is found:

```c
return index;
```

### Step 4

If the entire array is traversed and no match is found:

```c
return -1;
```

---

## C Implementation

```c
#include <stdio.h>

// Function to perform linear search
int search(int arr[], int n, int num) {

    for (int i = 0; i < n; i++) {

        // Element found
        if (arr[i] == num) {
            return i;
        }
    }

    // Element not found
    return -1;
}

int main() {

    int arr[] = {1, 2, 3, 4, 5};
    int num = 4;

    int n = sizeof(arr) / sizeof(arr[0]);

    int index = search(arr, n, num);

    printf("%d", index);

    return 0;
}
```

### Output

```text
3
```

Because `4` is present at index `3`.

---

## Dry Run

### Input

```text
arr = [1, 2, 3, 4, 5]
num = 4
```

| Iteration | Index | Value | Compare | Result |
| ---------- | ---------- | ---------- | ---------- | ---------- |
| 1 | 0 | 1 | 1 == 4 ? | No |
| 2 | 1 | 2 | 2 == 4 ? | No |
| 3 | 2 | 3 | 3 == 4 ? | No |
| 4 | 3 | 4 | 4 == 4 ? | Yes |

Return:

```text
3
```

---

## Complexity Analysis

| Operation | Complexity |
| ---------- | ---------- |
| Best Case | O(1) |
| Average Case | O(n) |
| Worst Case | O(n) |
| Space Complexity | O(1) |

### Best Case

```text
Target found at first index.
```

Example:

```text
[5, 1, 2, 3]
 ^
Found immediately
```

Time Complexity:

```text
O(1)
```

### Worst Case

```text
Target at last index
or
Target not present
```

Example:

```text
[1, 2, 3, 4, 5]
             ^
```

Time Complexity:

```text
O(n)
```

---

## Edge Cases

| Case | Input | Output |
| ---------- | ---------- | ---------- |
| Empty Array | `[]` | `-1` |
| Single Element Found | `[7]` | `0` |
| Single Element Not Found | `[7]` | `-1` |
| Duplicate Elements | `[2,2,2]` | `0` |
| Element At End | `[1,2,3,4,5]` | `4` |

---

## Key Takeaways

- Linear Search checks elements **one by one**.
- Works on both **sorted** and **unsorted** arrays.
- Returns the **first occurrence** of the target.
- Simple and easy to implement.
- No extra memory is required.
- Efficient only for small datasets.

---

## Quick Revision

1. Traverse the array.
2. Compare each element with the target.
3. If found, return index.
4. Otherwise return `-1`.
5. Best Case = `O(1)`
6. Worst Case = `O(n)`
7. Space Complexity = `O(1)`

---

## Visual Memory Aid

### Core Logic

```c
for (int i = 0; i < n; i++) {

    if (arr[i] == num) {
        return i;
    }
}

return -1;
```

### Mental Model

```text
Start
  ↓
Check Current Element
  ↓
Match?
 ├── Yes → Return Index
 │
 └── No
       ↓
   Move Next
       ↓
 End of Array?
 ├── No → Continue
 └── Yes → Return -1
```

### Remember

```text
Linear Search = Traverse + Compare

Found  → Return Index
Not Found → Return -1
```