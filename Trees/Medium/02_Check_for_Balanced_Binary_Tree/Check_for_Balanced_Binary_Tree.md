# Check if the Binary Tree is Balanced Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, determine whether it is a **Balanced Binary Tree**.

A Binary Tree is **balanced** if, for **every node**,

```text
| Height of Left Subtree − Height of Right Subtree | ≤ 1
```

Return:

- `true` if the tree is balanced.
- `false` otherwise.

---

# Examples

## Example 1

**Input**

```text
        3
      /   \
     9     20
          /  \
         15   7
```

**Output**

```text
true
```

Every node satisfies

```text
|Left Height - Right Height| ≤ 1
```

---

## Example 2

**Input**

```text
      1
     /
    2
   /
  3
```

**Output**

```text
false
```

Node `1` has

```text
Left Height = 2

Right Height = 0

Difference = 2
```

Tree is not balanced.

---

# Core Idea / Pattern Recognition

**Pattern**

```text
Postorder DFS
```

### Why?

Before checking whether a node is balanced,

we must already know

- Left subtree height
- Right subtree height

So we compute heights **from the bottom upwards**.

---

# Observation

For every node

```text
Balanced ?

↓

Need Left Height

+

Need Right Height
```

Then

```text
Difference ≤ 1 ?

↓

Balanced

Otherwise

Unbalanced
```

---

# Approach 1 — Brute Force

## Idea

For every node,

1. Compute left height.
2. Compute right height.
3. Check the difference.
4. Recursively check both subtrees.

The problem is that the same heights are computed repeatedly.

---

## Algorithm

1. Compute left subtree height.
2. Compute right subtree height.
3. If difference > 1 return false.
4. Recursively check left subtree.
5. Recursively check right subtree.

---

## Code

```cpp
class Solution {
public:

    int height(TreeNode* root){
        if(root == nullptr){
            return 0;
        }

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        return 1 + max(leftHeight,rightHeight);
    }

    bool isBalanced(TreeNode* root) {

        if(root == nullptr){
            return true;
        }

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if(abs(leftHeight-rightHeight)>1){
            return false;
        }

        return isBalanced(root->left)
            && isBalanced(root->right);
    }
};
```

---

## Visualization

```text
        1
       /
      2
     /
    3
```

For node

```text
1
```

Need

```text
Height(2)

+

Height(NULL)
```

Then again

```
Height(3)
```

is recomputed while checking node `2`.

Many heights are calculated multiple times.

---

## Dry Run

Tree

```text
      1
     /
    2
   /
  3
```

Height

```
3 = 1

↓

2 = 2

↓

1 = 3
```

Difference at Root

```text
2 - 0

=

2
```

Not Balanced.

---

## Complexity

### Time

```text
O(N²)
```

Height is recomputed for many nodes.

### Space

```text
O(H)
```

Recursive stack.

---

# Approach 2 — Optimal Approach

## Main Idea

Compute

```text
Height

+

Balance
```

in **one recursion**.

Instead of returning only height,

return

```text
-1
```

whenever an unbalanced subtree is found.

---

## Why It Works

Every recursive call returns either

```text
Height
```

or

```text
-1
```

Meaning

```text
Already Unbalanced
```

Once

```text
-1
```

appears,

we immediately stop further computation.

This avoids repeated height calculations.

---

## Code

```cpp
class Solution {
public:

    int height(TreeNode* root)
    {
        if(root == nullptr)
            return 0;

        int left = height(root->left);

        if(left == -1)
            return -1;

        int right = height(root->right);

        if(right == -1)
            return -1;

        if(abs(left-right)>1)
            return -1;

        return max(left,right)+1;
    }

    bool isBalanced(TreeNode* root)
    {
        return height(root)!=-1;
    }
};
```

---

## Visualization

Tree

```text
        1
       /
      2
     /
    3
```

Bottom-up

```text
Node 3

↓

Height = 1

↓

Node 2

Left = 1

Right = 0

Height = 2

↓

Node 1

Left = 2

Right = 0

Difference = 2

↓

Return -1
```

Immediately stop.

---

## Dry Run

Tree

```text
      1
     /
    2
   /
  3
```

### Step 1

```
height(3)

=

1
```

---

### Step 2

```
height(2)

Left = 1

Right = 0

Difference = 1

Return 2
```

---

### Step 3

```
height(1)

Left = 2

Right = 0

Difference = 2
```

Return

```text
-1
```

Final

```text
height(root)

=

-1
```

Tree

```text
Not Balanced
```

---

# Why Return `-1`?

Normally,

height is always

```text
0

1

2

3...
```

So

```text
-1
```

can safely represent

```text
Tree is already unbalanced
```

Whenever we receive

```text
-1
```

we simply propagate it upwards.

No further calculations are needed.

---

# Complexity

### Time

```text
O(N)
```

Every node is visited only once.

### Space

```text
O(H)
```

Recursive stack.

---

# Comparison Table

| Approach | Time | Space | Notes |
|----------|------|-------|------|
| Brute Force | `O(N²)` | `O(H)` | Recomputes heights repeatedly |
| Optimal | `O(N)` | `O(H)` | Computes height and balance together |

---

# Key Takeaways

- A balanced tree requires every node to satisfy `|leftHeight - rightHeight| ≤ 1`.
- Brute force repeatedly computes subtree heights.
- The optimal solution combines height calculation and balance checking.
- Returning `-1` immediately indicates an unbalanced subtree.
- Each node is processed only once in the optimal approach.

---

# Revision Template

### Brute

1. Find left height.
2. Find right height.
3. Check difference.
4. Repeat for left and right subtrees.

### Optimal

1. Compute left height.
2. If `-1`, return `-1`.
3. Compute right height.
4. If `-1`, return `-1`.
5. If difference > 1, return `-1`.
6. Else return `1 + max(left, right)`.

---

# Memory Trick

```text
Height

↓

Check Difference

↓

Difference > 1 ?

↓

YES

Return -1

↓

NO

Return Height
```

Remember:

> **"Use `-1` as a signal that the subtree is already unbalanced, and stop further computation."**

---

# Final Intuition

> Traverse the tree in postorder so that each node receives the heights of its left and right subtrees, immediately returning `-1` whenever an imbalance is detected to avoid unnecessary recalculations.
