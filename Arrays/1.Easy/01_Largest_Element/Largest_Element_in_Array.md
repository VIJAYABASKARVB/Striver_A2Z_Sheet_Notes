# Largest Element in an Array

## Optimal Solution

### Approach

- Traverse the array from start to end.
- Initialize `maxi` with the first element of the array:

```cpp
int maxi = arr[0];
```

- For every element, check:

```cpp
if (arr[i] > maxi) {
    maxi = arr[i];
}
```

- After completing the traversal, `maxi` will contain the largest element in the array.

### Algorithm

1. Initialize `maxi = arr[0]`.
2. Traverse the array from index `0` to `n - 1`.
3. If `arr[i] > maxi`, update `maxi = arr[i]`.
4. Return `maxi`.

### Time Complexity

- **O(n)** — We traverse the array once.

### Space Complexity

- **O(1)** — No extra space is used.
