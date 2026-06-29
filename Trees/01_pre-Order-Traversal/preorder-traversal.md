# Preorder Traversal of Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, return its **Preorder Traversal**.

In **Preorder Traversal**, nodes are visited in the following order:

```text
Root → Left → Right
```

---

# Examples

## Example 1

**Input**

```text
        4
       / \
      2   5
     /     \
    3       7
     \     /
      9   6
     /   /
    1   8
```

**Output**

```text
[4,2,3,9,1,5,7,6,8]
```

---

## Example 2

**Input**

```text
        1
      /   \
     2     3
    / \   / \
   4  5  6   7
      /      / \
     8      9  10
```

**Output**

```text
[1,2,4,5,8,3,6,7,9,10]
```

---

# Core Idea / Pattern Recognition

**Pattern**

```
Depth First Search (DFS)
```

### Traversal Order

```
Root

↓

Left Subtree

↓

Right Subtree
```

Always process the **current node first**, then recursively visit its children.

---

# Observation

For every node, follow the same rule:

```text
Visit Current Node

↓

Go Left

↓

Go Right
```

This rule repeats recursively for every subtree.

---

# Approach — Recursive DFS

## Idea

Use recursion.

For every node:

1. Visit the node.
2. Traverse its left subtree.
3. Traverse its right subtree.

---

## Algorithm

1. If node is `NULL`, return.
2. Store current node.
3. Traverse left child.
4. Traverse right child.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// Node structure for
// the binary tree
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // Function to perform preorder traversal
    void preorder(Node* root, vector<int> &arr){

        // Base Case
        if(root == nullptr){
            return;
        }

        // Root
        arr.push_back(root->data);

        // Left
        preorder(root->left, arr);

        // Right
        preorder(root->right, arr);
    }

    vector<int> preOrder(Node* root){

        vector<int> arr;

        preorder(root, arr);

        return arr;
    }
};
```

---

## Visualization

Consider

```text
        1
      /   \
     2     3
    / \
   4   5
```

Traversal

```text
Visit 1

↓

Visit 2

↓

Visit 4

↓

Backtrack

↓

Visit 5

↓

Backtrack

↓

Visit 3
```

Result

```text
1 2 4 5 3
```

---

## Recursive Call Flow

```text
preorder(1)

│
├── Visit 1
│
├── preorder(2)
│     │
│     ├── Visit 2
│     │
│     ├── preorder(4)
│     │      │
│     │      ├── Visit 4
│     │      ├── NULL
│     │      └── NULL
│     │
│     └── preorder(5)
│            │
│            ├── Visit 5
│            ├── NULL
│            └── NULL
│
└── preorder(3)
       │
       ├── Visit 3
       ├── NULL
       └── NULL
```

---

## Dry Run

Tree

```text
        1
      /   \
     2     3
    / \
   4   5
```

### Step 1

Visit Root

```text
1
```

Result

```text
[1]
```

---

### Step 2

Go Left

Visit

```text
2
```

Result

```text
[1,2]
```

---

### Step 3

Go Left

Visit

```text
4
```

Result

```text
[1,2,4]
```

Left child is `NULL`.

Return.

Right child is `NULL`.

Return.

---

### Step 4

Back to Node 2

Go Right

Visit

```text
5
```

Result

```text
[1,2,4,5]
```

Return.

---

### Step 5

Back to Root

Go Right

Visit

```text
3
```

Result

```text
[1,2,4,5,3]
```

Traversal Complete.

---

## Why Do We Check `root == nullptr`?

```cpp
if(root == nullptr)
    return;
```

This is the **base case**.

When recursion reaches beyond a leaf node,

```text
        4
       / \
    NULL NULL
```

The recursive calls become

```cpp
preorder(nullptr);
preorder(nullptr);
```

Without this condition, the next line

```cpp
root->data
```

would try to access a null pointer, causing a runtime error.

So,

```cpp
root == nullptr
```

simply means:

> **"There is no node here. Stop recursion and return to the previous call."**

---

## Complexity

### Time

```text
O(N)
```

Every node is visited exactly once.

### Space

```text
O(H)
```

Where `H` is the height of the tree (recursive call stack).

- Balanced Tree → `O(log N)`
- Skewed Tree → `O(N)`

---

# Comparison Table

| Traversal | Order |
|-----------|-------|
| Preorder | Root → Left → Right |
| Inorder | Left → Root → Right |
| Postorder | Left → Right → Root |

---

# Key Takeaways

- Preorder always visits the **root first**.
- The same rule (`Root → Left → Right`) is applied recursively to every subtree.
- `root == nullptr` is the recursion's stopping condition.
- Every node is visited exactly once.
- Preorder is commonly used for **copying trees**, **serialization**, and **expression trees**.

---

# Revision Template

1. If node is `NULL`, return.
2. Visit the current node.
3. Traverse the left subtree.
4. Traverse the right subtree.
5. Repeat recursively.

---

# Memory Trick

```text
PRE

↓

Parent First

↓

Left

↓

Right
```

Remember:

> **"PRE means Process the Parent Before its Children."**

---

# Final Intuition

> In preorder traversal, always process the current node first, then recursively explore the left subtree followed by the right subtree.