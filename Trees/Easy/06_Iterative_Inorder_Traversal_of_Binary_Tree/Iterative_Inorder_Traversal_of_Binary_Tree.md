# Iterative Inorder Traversal of Binary Tree

---

# Problem Statement

Given the root of a Binary Tree, return its **Inorder Traversal** using an **iterative approach** (without recursion).

The traversal order is:

```text
Left → Root → Right
```

Use a **stack** to simulate the recursive call stack.

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

> **Note:** The explanation in the question incorrectly mentions preorder. The correct traversal is **Inorder (Left → Root → Right).**

---

# Core Idea / Pattern Recognition

**Pattern**

```text
Depth First Search (DFS) + Stack
```

### Why?

Recursive inorder uses the **function call stack**.

In the iterative approach, we use an **explicit stack** to remember the nodes whose left subtree is still being explored.

---

# Observation

For inorder,

```text
Left

↓

Root

↓

Right
```

So we:

1. Keep moving left while pushing nodes onto the stack.
2. When no left child exists, process the node.
3. Move to its right child.
4. Repeat.

---

# Approach — Iterative DFS

## Idea

Maintain two things:

- A **stack** to store nodes.
- A pointer `curr` to traverse the tree.

Continue until:

- `curr == NULL`
- and the stack becomes empty.

---

## Algorithm

1. Initialize `curr = root`.
2. Push all left nodes into the stack.
3. Pop the top node.
4. Visit it.
5. Move to its right child.
6. Repeat until both the stack is empty and `curr` is `NULL`.

---

## Code

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {

        vector<int> ans;
        stack<TreeNode*> st;

        TreeNode* curr = root;

        while(curr != nullptr || !st.empty()){

            while(curr != nullptr){
                st.push(curr);
                curr = curr->left;
            }

            curr = st.top();
            st.pop();

            ans.push_back(curr->val);

            curr = curr->right;
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

Visit 2

↓

Visit 5

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

# Stack Visualization

### Initial

```text
curr

↓

1

Stack

[]
```

---

### Move Left

Push

```text
1
```

Stack

```text
[1]
```

Move Left

```
2
```

Push

```text
2
```

Stack

```text
Top

↓

2

1
```

Move Left

```
4
```

Push

```text
4
```

Stack

```text
Top

↓

4

2

1
```

---

### Left Finished

Now

```text
curr = NULL
```

Pop

```text
4
```

Visit

```text
4
```

Move Right

```text
NULL
```

---

### Next Pop

Pop

```text
2
```

Visit

```text
2
```

Move Right

```text
5
```

Push

```text
5
```

Visit

```text
5
```

Continue similarly.

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
curr = 1

Stack = []

Answer = []
```

---

### Step 1

Push

```text
1

2

4
```

Stack

```text
Top

↓

4

2

1
```

---

### Step 2

Pop

```text
4
```

Answer

```text
[4]
```

Right child

```text
NULL
```

---

### Step 3

Pop

```text
2
```

Answer

```text
[4,2]
```

Move Right

```text
5
```

Push

```text
5
```

Pop

```text
5
```

Answer

```text
[4,2,5]
```

---

### Step 4

Pop

```text
1
```

Answer

```text
[4,2,5,1]
```

Move Right

```text
3
```

Visit

```text
3
```

Answer

```text
[4,2,5,1,3]
```

Traversal Complete.

---

# Why Do We Keep Going Left?

Inorder requires

```text
Left

↓

Root

↓

Right
```

So before visiting any node,

we must completely explore its left subtree.

That's why we repeatedly do

```cpp
while(curr != nullptr){
    st.push(curr);
    curr = curr->left;
}
```

Only when there is **no more left child** do we process the node.

---

# Why Is the Outer Loop

```cpp
while(curr != nullptr || !st.empty())
```

?

Traversal ends only when:

- there are **no more nodes to visit (`curr == NULL`)**, and
- there are **no stored ancestors in the stack**.

If either condition is still true, traversal must continue.

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

- Balanced Tree → `O(log N)`
- Skewed Tree → `O(N)`

---

# Comparison Table

| Method | Data Structure | Order |
|----------|---------------|-------|
| Recursive Inorder | Function Call Stack | Left → Root → Right |
| Iterative Inorder | Explicit Stack | Left → Root → Right |

---

# Key Takeaways

- Iterative inorder uses a **stack** instead of recursion.
- Keep moving left while pushing nodes.
- Visit a node only after its left subtree is processed.
- After visiting a node, move to its right subtree.
- Every node is pushed and popped exactly once.

---

# Revision Template

1. Initialize `curr = root`.
2. Push all left nodes.
3. Pop the top node.
4. Visit it.
5. Move to its right child.
6. Repeat until both the stack is empty and `curr` is `NULL`.

---

# Memory Trick

```text
Go Left

↓

Visit

↓

Go Right

↓

Repeat
```

Remember:

> **"Push while going Left, Pop to Visit, then move Right."**

---

# Final Intuition

> Simulate recursive inorder traversal using a stack by continuously moving left, visiting the deepest unprocessed node, and then exploring its right subtree until the entire tree is traversed.
