# Binary Trees

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![Holberton School](https://img.shields.io/badge/Holberton-School-red)

## Description

This project explores **binary trees**, a fundamental data structure in computer science. A binary tree is a hierarchical structure where each node can have at most two children: a left child and a right child.

This repository contains a complete implementation in C, featuring various operations and properties of binary trees.

---

## Data Structure

The following structure is used for binary tree nodes:

```c
/**
 * struct binary_tree_s - Binary tree node
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 */
struct binary_tree_s
{
    int n;
    struct binary_tree_s *parent;
    struct binary_tree_s *left;
    struct binary_tree_s *right;
};

typedef struct binary_tree_s binary_tree_t;
```

---

## File Directory & Explanations

### Header and Utilities

| File | Description |
| --- | --- |
| [binary_trees.h](binary_trees.h) | Header file containing all structure definitions and function prototypes. |
| [binary_tree_print.c](binary_tree_print.c) | A helper function that prints a binary tree in a pretty, visual format. |
| [COURS_ARBRES_BINAIRES.md](COURS_ARBRES_BINAIRES.md) | Comprehensive course notes on binary trees (in French). |

### Mandatory Tasks

| File | Function | Description |
| --- | --- | --- |
| [0-binary_tree_node.c](0-binary_tree_node.c) | `binary_tree_node` | Creates a new binary tree node. |
| [1-binary_tree_insert_left.c](1-binary_tree_insert_left.c) | `binary_tree_insert_left` | Inserts a node as the left-child of another node. |
| [2-binary_tree_insert_right.c](2-binary_tree_insert_right.c) | `binary_tree_insert_right` | Inserts a node as the right-child of another node. |
| [3-binary_tree_delete.c](3-binary_tree_delete.c) | `binary_tree_delete` | Deletes an entire binary tree. |
| [4-binary_tree_is_leaf.c](4-binary_tree_is_leaf.c) | `binary_tree_is_leaf` | Checks if a node is a leaf (no children). |
| [5-binary_tree_is_root.c](5-binary_tree_is_root.c) | `binary_tree_is_root` | Checks if a node is a root (no parent). |
| [6-binary_tree_preorder.c](6-binary_tree_preorder.c) | `binary_tree_preorder` | Traverses a tree using pre-order traversal (Root -> Left -> Right). |
| [7-binary_tree_inorder.c](7-binary_tree_inorder.c) | `binary_tree_inorder` | Traverses a tree using in-order traversal (Left -> Root -> Right). |
| [8-binary_tree_postorder.c](8-binary_tree_postorder.c) | `binary_tree_postorder` | Traverses a tree using post-order traversal (Left -> Right -> Root). |
| [9-binary_tree_height.c](9-binary_tree_height.c) | `binary_tree_height` | Measures the height of a binary tree. |
| [10-binary_tree_depth.c](10-binary_tree_depth.c) | `binary_tree_depth` | Measures the depth of a node in a binary tree. |
| [11-binary_tree_size.c](11-binary_tree_size.c) | `binary_tree_size` | Measures the size (total nodes) of a binary tree. |
| [12-binary_tree_leaves.c](12-binary_tree_leaves.c) | `binary_tree_leaves` | Counts the number of leaves in a binary tree. |
| [13-binary_tree_nodes.c](13-binary_tree_nodes.c) | `binary_tree_nodes` | Counts the nodes with at least 1 child in a binary tree. |
| [14-binary_tree_balance.c](14-binary_tree_balance.c) | `binary_tree_balance` | Measures the balance factor of a binary tree. |
| [15-binary_tree_is_full.c](15-binary_tree_is_full.c) | `binary_tree_is_full` | Checks if a binary tree is full (every node has 0 or 2 children). |
| [16-binary_tree_is_perfect.c](16-binary_tree_is_perfect.c) | `binary_tree_is_perfect` | Checks if a binary tree is perfect (all levels are completely filled). |
| [17-binary_tree_sibling.c](17-binary_tree_sibling.c) | `binary_tree_sibling` | Finds the sibling of a node. |
| [18-binary_tree_uncle.c](18-binary_tree_uncle.c) | `binary_tree_uncle` | Finds the uncle of a node. |

### Test Files

The files ending in `-main.c` (e.g., `0-main.c`, `1-main.c`, etc.) are provided for testing purposes. They demonstrate how to use each corresponding function and can be used to verify correctness.

---

## Compilation & Usage

To compile all files, use `gcc` with the following flags:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o binary_trees
```

### Example: Compiling a specific task

To test the node creation function:

```bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 0-main.c 0-binary_tree_node.c binary_tree_print.c -o 0-node
./0-node
```

---

## Key Concepts

-   **Full Binary Tree**: A tree where every node has either 0 or 2 children.
-   **Perfect Binary Tree**: A tree where all internal nodes have two children and all leaves are at the same level.
-   **Height**: The number of edges on the longest path from the node to a leaf.
-   **Depth**: The number of edges from the node to the tree's root node.

---

## Author

- **CERQUEIRA Loïc** - *Student at Holberton School*
- **MARQUES Matéo** - *Student at Holberton School*
