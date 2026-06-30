# Iterative Postorder Traversal of Binary Tree (Using One Stack)

---

# Problem Statement

Given the root of a Binary Tree, return its **Postorder Traversal** using an **iterative approach with one stack**.

The traversal order is:

```text
Left → Right → Root
```

Unlike the two-stack solution, use only **one stack**.

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

> **Note:** The output shown in the question is incorrect. The correct postorder traversal is **[4,8,5,2,6,9,10,7,3,1]**.

---

# Core Idea / Pattern Recognition

**Pattern**

```text
Depth First Search (DFS) + One Stack
```

### Why?

Postorder requires

```text
Left

↓

Right

↓

Root
```

A node **cannot be visited immediately** after reaching it.

We must first ensure **both children have already been processed**.

To know whether the right subtree has already been visited, we maintain a pointer called:

```cpp
lastVisited
```

---

# Observation

For every node,

before visiting it,

we must answer one question:

```text
Has the Right Subtree already been processed?
```

If

```text
NO
```

Go Right.

If

```text
YES
```

Visit the node.

---

# Approach — One Stack

## Idea

- Keep moving left while pushing nodes.
- When left ends:
  - Look at the top node.
  - If its right subtree is unvisited, move right.
  - Otherwise, visit the node.
- Use `lastVisited` to remember the last processed node.

---

## Algorithm

1. Push all left nodes.
2. Peek the top node.
3. If right child exists and is not processed, go right.
4. Otherwise:
   - Visit the node.
   - Mark it as `lastVisited`.
   - Pop it.
5. Repeat.

---

## Code

```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {

        vector<int> ans;

        stack<TreeNode*> st;

        TreeNode* curr = root;
        TreeNode* lastVisited = nullptr;

        while (curr != nullptr || !st.empty()) {

            if (curr != nullptr) {

                st.push(curr);
                curr = curr->left;
            }
            else {

                TreeNode* node = st.top();

                if (node->right != nullptr &&
                    lastVisited != node->right) {

                    curr = node->right;
                }
                else {

                    ans.push_back(node->val);

                    lastVisited = node;

                    st.pop();
                }
            }
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

# Stack Visualization

Initially

```text
curr

↓

1

Stack

[]
```

Move Left

```text
Push 1

↓

Push 2

↓

Push 4
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

Pop?

No.

First,

check

```text
Does 4 have Right Child?
```

No.

Visit

```text
4
```

Stack

```text
Top

↓

2

1
```

---

Top

```text
2
```

Check

```text
Right Child = 5

Visited?

No
```

Move Right.

Push

```text
5
```

Visit

```text
5
```

Return.

---

Again Top

```text
2
```

Now

```text
lastVisited == 5
```

Both children processed.

Visit

```text
2
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
curr=1

Stack=[]

Answer=[]
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

Top

```text
4
```

Right child?

```text
NULL
```

Visit

```text
4
```

Answer

```text
[4]
```

lastVisited

```text
4
```

---

### Step 3

Top

```text
2
```

Right child?

```text
5
```

Not visited.

Move Right.

Push

```text
5
```

Visit

```text
5
```

Answer

```text
[4,5]
```

lastVisited

```text
5
```

---

### Step 4

Top

```text
2
```

Right child already visited.

Visit

```text
2
```

Answer

```text
[4,5,2]
```

---

### Step 5

Visit

```text
3
```

Answer

```text
[4,5,2,3]
```

---

### Step 6

Visit

```text
1
```

Answer

```text
[4,5,2,3,1]
```

Traversal Complete.

---

# Why Do We Need `lastVisited`?

Suppose

```text
      1
     / \
    2   3
```

After finishing

```text
2
```

we return to

```text
1
```

Now,

how do we know whether

```text
3
```

has already been processed?

Without

```cpp
lastVisited
```

we cannot distinguish between

```text
Need to visit Right

OR

Already visited Right
```

`lastVisited` remembers the last processed node.

```cpp
if(lastVisited != node->right)
```

means

```text
Right subtree still pending.
```

Otherwise,

```text
Visit current node.
```

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

| Method | Data Structure | Extra Space | Order |
|----------|---------------|------------|-------|
| Recursive | Function Call Stack | `O(H)` | Left → Right → Root |
| Iterative (2 Stacks) | Two Stacks | `O(N)` | Left → Right → Root |
| Iterative (1 Stack) | One Stack + `lastVisited` | `O(H)` | Left → Right → Root |

---

# Key Takeaways

- One-stack postorder is more space-efficient than the two-stack approach.
- Always move left first.
- Before visiting a node, check whether its right subtree has been processed.
- `lastVisited` prevents revisiting the right subtree.
- Visit a node only after both children are complete.

---

# Revision Template

1. Push all left nodes.
2. Peek the top node.
3. If the right child is unvisited, move right.
4. Otherwise, visit the node.
5. Update `lastVisited`.
6. Pop the node.
7. Repeat.

---

# Memory Trick

```text
Go Left

↓

Check Right

↓

Right Done?

↓

YES

Visit Root

↓

NO

Go Right
```

Remember:

> **"In one-stack postorder, a node is visited only after its right subtree is finished, tracked using `lastVisited`."**

---

# Final Intuition

> Simulate recursive postorder with one stack by always exploring the left subtree first, visiting the right subtree only when necessary, and processing a node only after both of its children have already been visited.
