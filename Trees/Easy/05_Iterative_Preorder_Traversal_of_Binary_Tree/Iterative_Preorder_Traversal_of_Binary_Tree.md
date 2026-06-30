# Iterative Preorder Traversal of Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, return its **Preorder Traversal** using an **iterative approach** (without recursion).

The traversal order is:

```text
Root → Left → Right
```

Use a **stack** to simulate the recursive calls.

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
   4   5 6   7
      /      / \
     8      9 10
```

**Output**

```text
[1,2,4,5,8,3,6,7,9,10]
```

---

# Core Idea / Pattern Recognition

**Pattern**

```text
Depth First Search (DFS) + Stack
```

### Why?

Recursive preorder uses the **function call stack**.

In the iterative version, we **explicitly use our own stack** to store the nodes that still need to be visited.

---

# Observation

Preorder order is

```text
Root

↓

Left

↓

Right
```

Since a **stack is LIFO (Last In, First Out)**:

- Push **Right child first**
- Push **Left child second**

This ensures the **Left child is processed before the Right child**.

---

# Approach — Iterative DFS

## Idea

1. Push the root into the stack.
2. Pop the top node.
3. Visit it.
4. Push its **right child first**, then **left child**.
5. Repeat until the stack is empty.

---

## Algorithm

1. If root is `NULL`, return.
2. Push root into the stack.
3. While stack is not empty:
   - Pop the top node.
   - Visit it.
   - Push right child.
   - Push left child.
4. Return the traversal.

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {

        vector<int> preorder;

        if(root == nullptr)
            return preorder;

        stack<TreeNode*> st;

        st.push(root);

        while(!st.empty()) {

            root = st.top();
            st.pop();

            preorder.push_back(root->val);

            if(root->right != nullptr)
                st.push(root->right);

            if(root->left != nullptr)
                st.push(root->left);
        }

        return preorder;
    }
};
```

---

# Visualization

Tree

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

Visit 5

↓

Visit 3
```

Result

```text
1 2 4 5 3
```

---

# Stack Visualization

### Initial

```text
Stack

Top

↓

[1]
```

---

### Pop 1

Visit

```text
1
```

Push

```text
Right → 3

Left → 2
```

Stack

```text
Top

↓

2

3
```

---

### Pop 2

Visit

```text
2
```

Push

```text
Right → 5

Left → 4
```

Stack

```text
Top

↓

4

5

3
```

---

### Pop 4

Visit

```text
4
```

No children.

Stack

```text
Top

↓

5

3
```

---

### Pop 5

Visit

```text
5
```

Stack

```text
Top

↓

3
```

---

### Pop 3

Visit

```text
3
```

Stack becomes empty.

Traversal Complete.

---

# Why Push Right Before Left?

Suppose

```text
      1
     / \
    2   3
```

If we push

```text
Left First

↓

Right Second
```

Stack

```text
Top

↓

3

2
```

The stack pops

```text
3
```

first.

Traversal becomes

```text
1 3 2
```

which is incorrect.

---

Instead,

push

```text
Right First

↓

Left Second
```

Stack

```text
Top

↓

2

3
```

Now

```text
2
```

is processed first.

Correct traversal

```text
1 2 3
```

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
Stack

[1]
```

Answer

```text
[]
```

---

### Step 1

Pop

```text
1
```

Answer

```text
[1]
```

Push

```text
3

2
```

Stack

```text
Top

↓

2

3
```

---

### Step 2

Pop

```text
2
```

Answer

```text
[1,2]
```

Push

```text
5

4
```

Stack

```text
Top

↓

4

5

3
```

---

### Step 3

Pop

```text
4
```

Answer

```text
[1,2,4]
```

---

### Step 4

Pop

```text
5
```

Answer

```text
[1,2,4,5]
```

---

### Step 5

Pop

```text
3
```

Answer

```text
[1,2,4,5,3]
```

Traversal Complete.

---

# Complexity

### Time

```text
O(N)
```

Every node is pushed and popped exactly once.

### Space

```text
O(H)
```

Where `H` is the height of the tree.

Worst case (skewed tree):

```text
O(N)
```

Balanced tree:

```text
O(log N)
```

---

# Comparison Table

| Method | Data Structure | Order |
|----------|---------------|-------|
| Recursive Preorder | Function Call Stack | Root → Left → Right |
| Iterative Preorder | Explicit Stack | Root → Left → Right |

---

# Key Takeaways

- Iterative preorder uses a **stack** instead of recursion.
- Visit the node immediately after popping it.
- Push the **right child first**, then the **left child**.
- Stack's LIFO property ensures the left subtree is processed first.
- Every node is pushed and popped exactly once.

---

# Revision Template

1. If root is `NULL`, return.
2. Push root into the stack.
3. While stack is not empty:
   - Pop node.
   - Visit it.
   - Push right child.
   - Push left child.
4. Return the answer.

---

# Memory Trick

```text
Visit

↓

Push Right

↓

Push Left

↓

Repeat
```

Remember:

> **"Right goes in first so Left comes out first."**

---

# Final Intuition

> Simulate recursive preorder using a stack by visiting each node immediately after popping it, then pushing its right child before its left child so that the left subtree is processed first.
