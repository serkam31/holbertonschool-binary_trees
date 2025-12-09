#include "binary_trees.h"

/**
 * binary_tree_insert_right - Inserts a node as the right-child of another node
 * @parent: Pointer to the node to insert the right-child in
 * @value: Value to store in the new node
 *
 * Return: Pointer to the created node, or NULL on failure or if parent is NULL
 */
binary_tree_t *binary_tree_insert_right(binary_tree_t *parent, int value)
{
	binary_tree_t *new_node;
	binary_tree_t *old_right;

	/* Check if parent is NULL */
	if (parent == NULL)
		return (NULL);

	/* Allocate memory for the new node */
	new_node = (binary_tree_t *)(malloc(sizeof(binary_tree_t)));

	if (new_node == NULL)
		return (NULL);

	/* Save the old right child before modifying parent->right */
	old_right = parent->right;

	/* If parent had a right child, update its parent pointer */
	if (old_right != NULL)
		old_right->parent = new_node;

	/* Initialize the new node's fields */
	new_node->n = value;
	new_node->right = old_right; /* Link to old right child (or NULL) */
	new_node->parent = parent;
	new_node->left = NULL;

	/* Attach the new node to the parent */
	parent->right = new_node;

	return (new_node);
}
