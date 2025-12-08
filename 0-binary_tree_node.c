#include "binary_trees.h"

binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
	binary_tree_t *new_node;

	/* Step 1: Allocate memory */
	new_node = (binary_tree_t *)malloc(sizeof(binary_tree_t));

	/* Step 2: Check if allocation failed */
	if (new_node == NULL)
		return (NULL);

	/* Step 3: Initialize all fields */
	new_node->n = value;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	/* Step 4: Return the new node */
	return (new_node);
}
