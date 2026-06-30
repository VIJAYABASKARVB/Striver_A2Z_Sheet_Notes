# Iterative Postorder Traversal of Binary Tree (Using Two Stacks)

---

# Problem Statement

Given the root of a Binary Tree, return its **Postorder Traversal** using an **iterative approach with two stacks**.

The traversal order is:

```text
Left → Right → Root
```

Instead of recursion, use **two stacks** to simulate the traversal.

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

> **Note:** The example output in the question is incorrect. The correct postorder traversal is **[4,8,5,2,6,9,10,7,3,1]**.

---

# Core Idea / Pattern Recognition

**Pattern**

```text
Depth First Search (DFS) + Two Stacks
```

### Why?

Postorder is

```text
Left → Right → Root
```

which is difficult to generate directly using one stack.

Instead, we first generate a modified preorder:

```text
Root → Right → Left
```

and store it in the second stack.

When we pop the second stack, the order automatically becomes

```text
Left → Right → Root
```

---

# Observation

Normal Preorder

```text
Root

↓

Left

↓

Right
```

Modified Preorder

```text
Root

↓

Right

↓

Left
```

Reverse it

```text
Left

↓

Right

↓

Root
```

Exactly the Postorder traversal.

---

# Approach — Two Stacks

## Idea

- **Stack 1** is used for traversal.
- **Stack 2** stores nodes in reverse postorder.
- Finally, popping Stack 2 gives the required postorder sequence.

---

## Algorithm

1. Push the root into **Stack 1**.
2. While Stack 1 is not empty:
   - Pop a node.
   - Push it into **Stack 2**.
   - Push its left child into Stack 1.
   - Push its right child into Stack 1.
3. Pop every node from Stack 2 into the answer.

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

vector<int> postOrder(Node* root) {

    vector<int> postorder;

    if(root == NULL)
        return postorder;

    stack<Node*> st1, st2;

    st1.push(root);

    while(!st1.empty()) {

        root = st1.top();
        st1.pop();

        st2.push(root);

        if(root->left != NULL)
            st1.push(root->left);

        if(root->right != NULL)
            st1.push(root->right);
    }

    while(!st2.empty()) {

        postorder.push_back(st2.top()->data);

        st2.pop();
    }

    return postorder;
}
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

Generated order

```text
Stack 2

1

3

2

5

4
```

Reverse by popping

```text
4

5

2

3

1
```

Final Answer

```text
4 5 2 3 1
```

---

# Two Stack Visualization

### Initially

```text
Stack1

Top

↓

1

Stack2

[]
```

---

### Pop 1

Move to Stack2

```text
Stack2

Top

↓

1
```

Push children

```text
Left → 2

Right → 3
```

Stack1

```text
Top

↓

3

2
```

---

### Pop 3

Move to Stack2

```text
Stack2

Top

↓

3

1
```

---

### Pop 2

Move to Stack2

```text
Stack2

Top

↓

2

3

1
```

Push

```text
4

5
```

Stack1

```text
Top

↓

5

4
```

Continue until Stack1 becomes empty.

Finally

Pop Stack2.

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
Stack1

[1]

Stack2

[]
```

---

### Step 1

Pop

```text
1
```

Push into Stack2

```text
[1]
```

Push

```text
2

3
```

Stack1

```text
Top

↓

3

2
```

---

### Step 2

Pop

```text
3
```

Stack2

```text
3

1
```

---

### Step 3

Pop

```text
2
```

Stack2

```text
2

3

1
```

Push

```text
4

5
```

---

### Step 4

Pop

```text
5
```

Stack2

```text
5

2

3

1
```

---

### Step 5

Pop

```text
4
```

Stack2

```text
4

5

2

3

1
```

Now pop Stack2.

Answer

```text
4

5

2

3

1
```

Traversal Complete.

---

# Why Does This Work?

The first stack generates

```text
Root

↓

Right

↓

Left
```

because

- Left is pushed first.
- Right is pushed later.
- Due to **LIFO**, Right is processed first.

The second stack reverses this order.

```text
Root Right Left

↓

Reverse

↓

Left Right Root
```

which is exactly **Postorder**.

---

# Complexity

### Time

```text
O(N)
```

Every node is pushed and popped once from each stack.

### Space

```text
O(N)
```

Two stacks may together store all nodes.

---

# Comparison Table

| Method | Data Structure | Order |
|----------|---------------|-------|
| Recursive Postorder | Function Call Stack | Left → Right → Root |
| Iterative (2 Stacks) | Two Stacks | Left → Right → Root |

---

# Key Takeaways

- Two stacks make iterative postorder simple.
- Stack 1 performs a modified preorder traversal.
- Stack 2 reverses the traversal order.
- Push **left first**, then **right** into Stack 1.
- Popping Stack 2 directly gives postorder.

---

# Revision Template

1. Push root into Stack1.
2. Pop node from Stack1.
3. Push it into Stack2.
4. Push left child.
5. Push right child.
6. Repeat until Stack1 is empty.
7. Pop Stack2 to get postorder.

---

# Memory Trick

```text
Stack1

↓

Root Right Left

↓

Stack2 Reverses

↓

Left Right Root
```

Remember:

> **"Generate Root-Right-Left first, then reverse it to get Left-Right-Root."**

---

# Final Intuition

> Use the first stack to produce a reversed postorder sequence (Root → Right → Left), then reverse it using the second stack to obtain the required Left → Right → Root traversal.
