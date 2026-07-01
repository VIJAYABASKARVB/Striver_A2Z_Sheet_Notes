# Calculate the Diameter of a Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, return its **diameter**.

The **diameter** is the **length (number of edges)** of the longest path between any two nodes in the tree.

> The longest path **may or may not pass through the root**.

---

# Examples

## Example 1

```text
        1
      /   \
     2     3
    / \
   4   5
```

**Output**

```text
3
```

Longest path

```text
4 → 2 → 1 → 3
```

contains **3 edges**.

---

## Example 2

```text
        1
      /   \
     2     3
    /
   4
  /
 5
```

**Output**

```text
4
```

Longest path

```text
5 → 4 → 2 → 1 → 3
```

contains **4 edges**.

---

# Core Idea / Pattern Recognition

**Pattern**

```text
Postorder DFS
```

### Why?

To calculate the diameter through a node, we first need

- Height of the left subtree
- Height of the right subtree

Both heights must be known **before** processing the current node.

---

# Observation

For every node

```text
Diameter Passing Through Node

=

Left Height + Right Height
```

The overall answer is the **maximum** of this value across all nodes.

---

# Approach 1 — Brute Force

## Idea

For every node,

1. Find the height of the left subtree.
2. Find the height of the right subtree.
3. Update the diameter.
4. Repeat recursively.

Since subtree heights are computed repeatedly, this approach is inefficient.

---

## Code

```cpp
class Solution {
public:
    int diameter = 0;

    int calculateHeight(Node* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        diameter = max(diameter, leftHeight + rightHeight);

        return 1 + max(leftHeight, rightHeight);
    }

    int diameterOfBinaryTree(Node* root) {
        calculateHeight(root);
        return diameter;
    }
};
```

---

## Visualization

```text
        1
      /   \
     2     3
    / \
   4   5
```

At node `1`

```text
Left Height = 2

Right Height = 1

Diameter

=

2 + 1

=

3
```

---

## Dry Run

```text
Height(4)=1

Height(5)=1

↓

Height(2)=2

↓

Height(3)=1

↓

Diameter at 1

=

2+1

=

3
```

Answer

```text
3
```

---

## Complexity

**Time:** `O(N²)`

**Space:** `O(H)`

---

# Approach 2 — Optimal Approach

## Main Idea

Compute **height** and **diameter** together in **one DFS**.

While returning the height,

also update

```text
diameter = max(diameter, leftHeight + rightHeight)
```

This avoids recalculating heights.

---

## Why It Works

Every node already computes

```text
Left Height

Right Height
```

So we can immediately calculate

```text
Diameter Through Current Node

=

Left Height + Right Height
```

Every node is visited only once.

---

## Code

```cpp
class Solution {
public:
    int diameterOfBinaryTree(Node* root) {

        int diameter = 0;

        height(root, diameter);

        return diameter;
    }

private:

    int height(Node* node, int& diameter) {

        if (!node)
            return 0;

        int lh = height(node->left, diameter);
        int rh = height(node->right, diameter);

        diameter = max(diameter, lh + rh);

        return 1 + max(lh, rh);
    }
};
```

---

## Visualization

Tree

```text
        1
      /   \
     2     3
    / \
   4   5
```

Bottom-up computation

```text
Node 4

Height = 1

↓

Node 5

Height = 1

↓

Node 2

Height = 2

Diameter = 1+1=2

↓

Node 3

Height = 1

↓

Node 1

Height = 3

Diameter = 2+1=3
```

Final Answer

```text
3
```

---

## Dry Run

```text
Height(4)=1

Diameter=0

↓

Height(5)=1

Diameter=0

↓

Node 2

lh=1

rh=1

Diameter=max(0,2)=2

Height=2

↓

Node 3

Height=1

↓

Node 1

lh=2

rh=1

Diameter=max(2,3)=3

Height=3
```

Return

```text
3
```

---

## Why Do We Calculate

```cpp
leftHeight + rightHeight
```

?

At every node,

the longest path passing through that node is

```text
Deepest Node

↓

Left Height

↓

Current Node

↓

Right Height

↓

Deepest Node
```

So

```text
Diameter Through Node

=

Left Height + Right Height
```

---

## Edge Cases

- Empty tree
- Single node (diameter = 0)
- Completely skewed tree
- Perfect binary tree

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

Recursive call stack.

- Balanced Tree → `O(log N)`
- Skewed Tree → `O(N)`

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Brute Force | `O(N²)` | `O(H)` | Heights are recalculated |
| Optimal DFS | `O(N)` | `O(H)` | Height and diameter computed together |

---

# Key Takeaways

- Diameter is the **longest path between any two nodes**.
- Diameter **does not have to pass through the root**.
- Diameter through a node = `leftHeight + rightHeight`.
- Use postorder DFS so subtree heights are already known.
- Compute height and diameter together in one traversal.

---

# Revision Template

1. Traverse using postorder DFS.
2. Compute left height.
3. Compute right height.
4. Update `diameter = max(diameter, left + right)`.
5. Return `1 + max(left, right)`.

---

# Memory Trick

```text
Left Height

+

Right Height

↓

Current Diameter

↓

Return Height
```

Remember:

> **"Every node asks: If I'm the bridge between the deepest nodes of my left and right subtrees, how long is that path?"**

---

# Final Intuition

> Traverse the tree bottom-up, compute the height of each subtree once, and at every node update the diameter using the sum of its left and right subtree heights.
