#include "binary_trees.h"
/**
 * get_height - Measures the height of a binary tree
 * @tree: Pointer to the root node
 *
 * Return: Height of the tree, or -1 if tree is NULL
 */
int get_height(const binary_tree_t *tree)
{
	int left_height, right_height;

	if (tree == NULL)
		return (-1);

	left_height = get_height(tree->left);
	right_height = get_height(tree->right);

	if (left_height > right_height)
		return (left_height + 1);
	else
		return (right_height + 1);
}

/**
 * binary_tree_is_perfect - Checks if a binary tree is perfect
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if tree is perfect, 0 otherwise
 */
int binary_tree_is_perfect(const binary_tree_t *tree)
{
	int left_height, right_height;

	if (tree == NULL)
		return (0);

	if (tree->left == NULL && tree->right == NULL)
		return (1);

	left_height = get_height(tree->left);
	right_height = get_height(tree->right);

	if (left_height != right_height)
		return (0);

	return (binary_tree_is_perfect(tree->left) &&
			binary_tree_is_perfect(tree->right));
}
