# Postorder Traversal of Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, return its **Postorder Traversal**.

In **Postorder Traversal**, nodes are visited in the following order:

```text
Left → Right → Root
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
    3       6
     \     /
      9   8
     /
    1
```

**Output**

```text
[1,9,3,2,8,6,5,4]
```

---

## Example 2

**Input**

```text
        1
      /   \
     2     3
    / \   / \
   4   5 6   7
      /      / \
     8      9 10
```

**Output**

```text
[4,8,5,2,6,9,10,7,3,1]
```

> **Note:** The example output in the question appears incorrect. The correct postorder traversal for the given tree is **[4,8,5,2,6,9,10,7,3,1]**.

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

Right

↓

Root
```

The current node is visited **only after** both its left and right subtrees have been completely processed.

---

# Observation

For every node, follow the same rule:

```text
Go Left

↓

Go Right

↓

Visit Current Node
```

This recursive pattern is applied to every subtree.

Postorder is useful when a node depends on the results of its children.

---

# Approach — Recursive DFS

## Idea

Use recursion.

For every node:

1. Traverse the left subtree.
2. Traverse the right subtree.
3. Visit the current node.

---

## Algorithm

1. If node is `NULL`, return.
2. Traverse the left child.
3. Traverse the right child.
4. Store/print the current node.

---

## Code

```cpp
void postorder(TreeNode* root)
{
    if (root == nullptr)
        return;

    // Left
    postorder(root->left);

    // Right
    postorder(root->right);

    // Root
    cout << root->val << " ";
}
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

Visit 5

↓

Visit 2

↓

Visit 3

↓

Visit 1
```

Result

```text
4 5 2 3 1
```

---

## Recursive Call Flow

```text
postorder(1)

│
├── postorder(2)
│      │
│      ├── postorder(4)
│      │      │
│      │      ├── NULL
│      │      ├── NULL
│      │      └── Visit 4
│      │
│      ├── postorder(5)
│      │      │
│      │      ├── NULL
│      │      ├── NULL
│      │      └── Visit 5
│      │
│      └── Visit 2
│
├── postorder(3)
│      │
│      ├── NULL
│      ├── NULL
│      └── Visit 3
│
└── Visit 1
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

Reach

```text
2
```

Go Left.

---

### Step 3

Reach

```text
4
```

Left child is `NULL`.

Right child is `NULL`.

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

### Step 4

Back to

```text
2
```

Go Right.

Visit

```text
5
```

Result

```text
[4,5]
```

Return.

---

### Step 5

Both children of `2` are processed.

Visit

```text
2
```

Result

```text
[4,5,2]
```

Return.

---

### Step 6

Back to Root.

Go Right.

Visit

```text
3
```

Result

```text
[4,5,2,3]
```

Return.

---

### Step 7

Both subtrees of Root are complete.

Visit

```text
1
```

Result

```text
[4,5,2,3,1]
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
postorder(nullptr);

postorder(nullptr);
```

Without this condition,

```cpp
root->val
```

would access a null pointer, causing a runtime error.

So,

```cpp
root == nullptr
```

means:

> **"There is no node here. Stop recursion and return."**

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

- Postorder visits the **root last**.
- Both left and right subtrees are completely processed before visiting the current node.
- `root == nullptr` is the stopping condition.
- Every node is visited exactly once.
- Commonly used for **deleting trees**, **evaluating expression trees**, and **calculating subtree information**.

---

# Revision Template

1. If node is `NULL`, return.
2. Traverse the left subtree.
3. Traverse the right subtree.
4. Visit the current node.
5. Repeat recursively.

---

# Memory Trick

```text
POST

↓

Children First

↓

Parent Last
```

Or remember:

```text
Left

↓

Right

↓

Root
```

> **Think: "POST means Process the Parent After both Children."**

---

# Final Intuition

> In postorder traversal, recursively process the entire left subtree, then the right subtree, and visit the current node only after both children have been completely explored.