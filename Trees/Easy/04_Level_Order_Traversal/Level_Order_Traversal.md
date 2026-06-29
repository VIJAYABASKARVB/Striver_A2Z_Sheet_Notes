# Level Order Traversal of a Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, return the **Level Order Traversal** of the tree.

In Level Order Traversal, nodes are visited:

```text
Level by Level

↓

From Left to Right
```

The answer should be returned as a **2D vector**, where each inner vector contains the nodes of one level.

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
[
 [3],
 [9,20],
 [15,7]
]
```

---

## Example 2

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
[
 [1],
 [4],
 [4,2]
]
```

---

# Core Idea / Pattern Recognition

**Pattern**

```text
Breadth First Search (BFS)
```

### Why?

Unlike DFS (Preorder, Inorder, Postorder), Level Order Traversal processes nodes **level by level**.

A **Queue** naturally follows **First In First Out (FIFO)**, making it ideal for BFS.

---

# Observation

Suppose

```text
        1
      /   \
     2     3
    / \   / \
   4  5  6   7
```

Traversal order

```text
Level 0

1

↓

Level 1

2 3

↓

Level 2

4 5 6 7
```

Notice that all nodes of one level are processed before moving to the next.

---

# Approach — Breadth First Search (Queue)

## Idea

Use a queue.

1. Push the root into the queue.
2. Process all nodes currently in the queue (one level).
3. Push their children into the queue.
4. Repeat until the queue becomes empty.

---

## Algorithm

1. If the tree is empty, return an empty answer.
2. Push the root into the queue.
3. While the queue is not empty:
   - Store the current queue size.
   - Process exactly that many nodes (one level).
   - Push their children into the queue.
4. Store each level in the answer.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {

        vector<vector<int>> ans;

        if (root == nullptr)
            return ans;

        queue<TreeNode*> q;

        q.push(root);

        while (!q.empty()) {

            int size = q.size();

            vector<int> level;

            for (int i = 0; i < size; i++) {

                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->data);

                if (node->left != nullptr)
                    q.push(node->left);

                if (node->right != nullptr)
                    q.push(node->right);
            }

            ans.push_back(level);
        }

        return ans;
    }
};
```

---

# Visualization

Tree

```text
          1
       /     \
      2       3
     / \     / \
    4   5   6   7
```

Queue Movement

```text
Queue

[1]

↓

Process 1

Queue

[2,3]

↓

Process 2 3

Queue

[4,5,6,7]

↓

Process 4 5 6 7

Queue

[]
```

Result

```text
[
 [1],
 [2,3],
 [4,5,6,7]
]
```

---

# Queue Visualization

### Initial

```text
Queue

Front

↓

[1]

Rear
```

---

### After Processing 1

```text
Pop

1

Push

2

Push

3

Queue

Front

↓

[2,3]

Rear
```

---

### After Processing 2

```text
Pop

2

Push

4

Push

5

Queue

[3,4,5]
```

---

### After Processing 3

```text
Pop

3

Push

6

Push

7

Queue

[4,5,6,7]
```

Every iteration processes **one complete level**.

---

# Dry Run

Tree

```text
        1
      /   \
     2     3
    / \
   4   5
```

Initially

```text
Queue

[1]
```

Answer

```text
[]
```

---

### Level 0

Queue Size

```text
1
```

Process

```text
1
```

Push

```text
2

3
```

Queue

```text
[2,3]
```

Answer

```text
[
 [1]
]
```

---

### Level 1

Queue Size

```text
2
```

Process

```text
2

3
```

Push

```text
4

5
```

Queue

```text
[4,5]
```

Answer

```text
[
 [1],
 [2,3]
]
```

---

### Level 2

Queue Size

```text
2
```

Process

```text
4

5
```

Queue

```text
[]
```

Answer

```text
[
 [1],
 [2,3],
 [4,5]
]
```

Traversal Complete.

---

# Why Do We Store `size = q.size()`?

Suppose the queue contains

```text
[2,3]
```

These two nodes belong to the **same level**.

If we keep processing until the queue is empty,

while processing `2` and `3`, we'll also push

```text
4

5

6

7
```

Then the queue becomes

```text
[4,5,6,7]
```

These belong to the **next level**, but they'll also be processed immediately.

The level boundaries would be lost.

So we first save

```cpp
int size = q.size();
```

Then process **exactly `size` nodes**.

This guarantees that only one level is processed in each iteration.

---

# Complexity

### Time

```text
O(N)
```

Every node enters and leaves the queue exactly once.

### Space

```text
O(N)
```

In the worst case, the queue stores an entire level of the tree.

---

# Comparison Table

| Traversal | Technique | Data Structure | Order |
|-----------|-----------|----------------|-------|
| Preorder | DFS | Recursion / Stack | Root → Left → Right |
| Inorder | DFS | Recursion / Stack | Left → Root → Right |
| Postorder | DFS | Recursion / Stack | Left → Right → Root |
| Level Order | BFS | Queue | Level by Level |

---

# Key Takeaways

- Level Order Traversal uses **Breadth First Search (BFS)**.
- A **Queue** is used because of its FIFO property.
- Store `q.size()` before processing a level.
- Push left child before right child.
- Every node is visited exactly once.

---

# Revision Template

1. If root is `NULL`, return.
2. Push root into the queue.
3. While queue is not empty:
   - Store `size = q.size()`.
   - Process exactly `size` nodes.
   - Push left child.
   - Push right child.
   - Store current level.
4. Return the answer.

---

# Memory Trick

```text
Queue

↓

One Level

↓

Children

↓

Repeat
```

Or simply remember:

```text
FIFO

↓

Level by Level

↓

BFS
```

> **Think: "Queue processes one complete level before moving to the next."**

---

# Final Intuition

> Level Order Traversal uses a queue to perform Breadth First Search, processing all nodes at the current level before moving to the next level from left to right.
