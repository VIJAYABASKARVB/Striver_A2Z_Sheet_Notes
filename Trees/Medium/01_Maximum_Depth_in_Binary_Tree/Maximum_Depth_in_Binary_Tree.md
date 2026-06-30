# Maximum Depth of a Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, return its **maximum depth (height)**.

The **height** of a binary tree is the **number of nodes on the longest path from the root to any leaf node**.

---

# Examples

## Example 1

**Input**

```text
        1
      /   \
     2     5
          /
         4
        /
       5
```

**Output**

```text
4
```

**Explanation**

Longest path

```text
1 → 5 → 4 → 5
```

contains **4 nodes**.

---

## Example 2

**Input**

```text
    3
   / \
  1   2
```

**Output**

```text
2
```

---

# Core Idea / Pattern Recognition

**Patterns**

- Recursive DFS
- Level Order Traversal (BFS)

### Why?

There are two common ways to compute height:

- **DFS:** Compute the height of left and right subtrees recursively.
- **BFS:** Count how many levels exist in the tree.

---

# Observation

For every node,

```text
Height

=

1 + max(Left Height, Right Height)
```

The longest path always comes from the taller subtree.

---

# Approach 1 — Recursive DFS

## Idea

Compute the height of the left subtree and the right subtree.

The current node's height is

```text
1 + max(leftHeight, rightHeight)
```

---

## Algorithm

1. If node is `NULL`, return `0`.
2. Compute left height.
3. Compute right height.
4. Return `1 + max(leftHeight, rightHeight)`.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution{
public:
    int maxDepth(Node* root){

        if(root == NULL){
            return 0;
        }

        int lh = maxDepth(root->left);

        int rh = maxDepth(root->right);

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
          /
         4
        /
       5
```

Height Calculation

```text
Node 5

↓

1

↓

Node 4

↓

1+1 = 2

↓

Node 3

↓

1+2 = 3

↓

Node 1

↓

1+max(1,3)

=

4
```

---

## Dry Run

Tree

```text
        1
      /   \
     2     3
          /
         4
        /
       5
```

Compute

```
Height(5)=1
```

↓

```
Height(4)=2
```

↓

```
Height(3)=3
```

↓

```
Height(2)=1
```

↓

```
Height(1)

=

1+max(1,3)

=

4
```

Return

```text
4
```

---

## Complexity

### Time

```text
O(N)
```

Every node is visited once.

### Space

```text
O(H)
```

Recursive call stack.

- Balanced Tree → `O(log N)`
- Skewed Tree → `O(N)`

---

# Approach 2 — Level Order Traversal (BFS)

## Idea

Every iteration of BFS processes **one complete level**.

Simply count how many levels are processed.

That count equals the tree height.

---

## Algorithm

1. If root is `NULL`, return `0`.
2. Push root into a queue.
3. Process one level at a time.
4. Increase depth after every level.
5. Return depth.

---

## Code

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {

        if (root == nullptr)
            return 0;

        queue<TreeNode*> q;
        q.push(root);

        int depth = 0;

        while (!q.empty()) {

            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {

                TreeNode* node = q.front();
                q.pop();

                if (node->left)
                    q.push(node->left);

                if (node->right)
                    q.push(node->right);
            }

            depth++;
        }

        return depth;
    }
};
```

---

## Queue Visualization

Tree

```text
        1
      /   \
     2     3
          /
         4
        /
       5
```

Initially

```text
Queue

[1]
```

---

### Level 1

Process

```text
1
```

Push

```text
2

3
```

Depth

```text
1
```

---

### Level 2

Process

```text
2

3
```

Push

```text
4
```

Depth

```text
2
```

---

### Level 3

Process

```text
4
```

Push

```text
5
```

Depth

```text
3
```

---

### Level 4

Process

```text
5
```

Queue becomes empty.

Depth

```text
4
```

Return

```text
4
```

---

## Dry Run

Initially

```text
Queue=[1]

Depth=0
```

---

After Level 1

```text
Queue=[2,3]

Depth=1
```

---

After Level 2

```text
Queue=[4]

Depth=2
```

---

After Level 3

```text
Queue=[5]

Depth=3
```

---

After Level 4

```text
Queue=[]

Depth=4
```

Traversal Complete.

---

# Why Does DFS Formula Work?

For every node,

```text
Height

=

Longest Path Below It
```

Suppose

```text
        1
      /   \
     2     3
          /
         4
```

Left Height

```text
1
```

Right Height

```text
2
```

Current Height

```text
1 + max(1,2)

=

3
```

We always choose the **deeper subtree**.

---

# Complexity

### DFS

- **Time:** `O(N)`
- **Space:** `O(H)`

### BFS

- **Time:** `O(N)`
- **Space:** `O(N)` (queue may contain an entire level)

---

# Comparison Table

| Approach | Time | Space | Idea |
|----------|------|-------|------|
| Recursive DFS | `O(N)` | `O(H)` | Height = `1 + max(left, right)` |
| Level Order BFS | `O(N)` | `O(N)` | Count the number of levels |

---

# Key Takeaways

- Height = number of nodes on the longest root-to-leaf path.
- DFS computes height from the bottom up.
- BFS computes height level by level.
- DFS is more common in interviews.
- BFS is useful when level-wise processing is already required.

---

# Revision Template

### DFS

1. If node is `NULL`, return `0`.
2. Find left height.
3. Find right height.
4. Return `1 + max(left, right)`.

### BFS

1. Push root into queue.
2. Process one level.
3. Increment depth.
4. Repeat until queue becomes empty.

---

# Memory Trick

### DFS

```text
Height

=

1

+

Maximum Child Height
```

### BFS

```text
One Queue

↓

One Level

↓

Depth++
```

Remember:

> **"DFS measures the tallest branch, while BFS counts the total levels."**

---

# Final Intuition

> The maximum depth of a binary tree is the longest root-to-leaf path, which can be found either recursively by taking the maximum height of the two subtrees or iteratively by counting the levels during a breadth-first traversal.
