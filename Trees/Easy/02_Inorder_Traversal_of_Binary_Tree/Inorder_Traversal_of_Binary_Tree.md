# Inorder Traversal of Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, return its **Inorder Traversal**.

In **Inorder Traversal**, nodes are visited in the following order:

```text
Left → Root → Right
```

---

# Examples

## Example 1

**Input**

```text
        1
       /
      4
     / \
    4   2
```

**Output**

```text
[4,4,2,1]
```

---

## Example 2

**Input**

```text
    1
     \
      2
     /
    3
```

**Output**

```text
[1,3,2]
```

---

# Core Idea / Pattern Recognition

**Pattern**

```text
Depth First Search (DFS)
```

### Traversal Order

```text
Left

↓

Root

↓

Right
```

Unlike Preorder, we first explore the **entire left subtree**, then visit the current node, and finally explore the right subtree.

---

# Observation

For every node, apply the same rule:

```text
Go Left

↓

Visit Current Node

↓

Go Right
```

This rule is recursively applied to every subtree.

> **Important:** In a **Binary Search Tree (BST)**, Inorder Traversal always produces the nodes in **sorted order**.

---

# Approach — Recursive DFS

## Idea

Use recursion.

For every node:

1. Traverse the left subtree.
2. Visit the current node.
3. Traverse the right subtree.

---

## Algorithm

1. If the node is `NULL`, return.
2. Traverse the left child.
3. Store the current node.
4. Traverse the right child.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

// TreeNode structure for the binary tree
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution{
private:
    void recursiveInorder(TreeNode* root, vector<int> &arr){

        // Base Case
        if(root == nullptr){
            return;
        }

        // Left
        recursiveInorder(root->left, arr);

        // Root
        arr.push_back(root->data);

        // Right
        recursiveInorder(root->right, arr);
    }

public:
    vector<int> inorder(TreeNode* root){

        vector<int> arr;

        recursiveInorder(root, arr);

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
Go Left

↓

Visit 4

↓

Backtrack

↓

Visit 2

↓

Visit 5

↓

Backtrack

↓

Visit 1

↓

Visit 3
```

Result

```text
4 2 5 1 3
```

---

## Recursive Call Flow

```text
inorder(1)

│
├── inorder(2)
│      │
│      ├── inorder(4)
│      │      │
│      │      ├── NULL
│      │      ├── Visit 4
│      │      └── NULL
│      │
│      ├── Visit 2
│      │
│      └── inorder(5)
│             │
│             ├── NULL
│             ├── Visit 5
│             └── NULL
│
├── Visit 1
│
└── inorder(3)
       │
       ├── NULL
       ├── Visit 3
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

Start at

```text
1
```

Go Left.

---

### Step 2

Go Left again.

Reach

```text
4
```

Left child is `NULL`.

Visit

```text
4
```

Result

```text
[4]
```

Return.

---

### Step 3

Back to

```text
2
```

Visit

```text
2
```

Result

```text
[4,2]
```

Go Right.

Visit

```text
5
```

Result

```text
[4,2,5]
```

Return.

---

### Step 4

Back to Root

Visit

```text
1
```

Result

```text
[4,2,5,1]
```

Go Right.

Visit

```text
3
```

Result

```text
[4,2,5,1,3]
```

Traversal Complete.

---

## Why Do We Check `root == nullptr`?

```cpp
if(root == nullptr)
    return;
```

This is the **base case** of recursion.

When recursion reaches beyond a leaf node,

```text
        4
       / \
    NULL NULL
```

The recursive calls become

```cpp
recursiveInorder(nullptr);

recursiveInorder(nullptr);
```

Without this condition,

```cpp
root->data
```

would try to access a null pointer, causing a runtime error.

So,

```cpp
root == nullptr
```

means:

> **"There is no node to visit. Stop recursion and return."**

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

Where `H` is the height of the tree.

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

- Inorder visits the **left subtree before the root**.
- The current node is processed **between** its left and right subtrees.
- The same rule is recursively applied to every subtree.
- `root == nullptr` is the recursion's stopping condition.
- Inorder traversal of a **BST** always returns elements in **sorted order**.

---

# Revision Template

1. If node is `NULL`, return.
2. Traverse the left subtree.
3. Visit the current node.
4. Traverse the right subtree.
5. Repeat recursively.

---

# Memory Trick

```text
IN

↓

Inside

↓

Left

↓

Node

↓

Right
```

or simply remember:

```text
L

↓

R

↓

R

(Left → Root → Right)
```

> **Think: "The Root comes IN between the Left and Right subtrees."**

---

# Final Intuition

> Inorder traversal recursively explores the entire left subtree first, then processes the current node, and finally traverses the right subtree, producing sorted order for a Binary Search Tree.