#include "binary_trees.h"

/**
 * binary_tree_uncle - Finds the uncle of a node
 * @node: Pointer to the node to find the uncle
 *
 * Description: The uncle is the sibling of the node's parent.
 * To find it: get parent, get grandparent, return the other child of grandparent.
 *
 * Return: Pointer to the uncle node, or NULL if no uncle exists
 */
binary_tree_t *binary_tree_uncle(binary_tree_t *node)
{
	binary_tree_t *parent, *grandparent;

	/* Si node est NULL, retourne NULL */
	if (node == NULL)
		return (NULL);

	/* Si node n'a pas de parent, pas d'oncle */
	if (node->parent == NULL)
		return (NULL);

	parent = node->parent;

	/* Si le parent n'a pas de parent (grandparent), pas d'oncle */
	if (parent->parent == NULL)
		return (NULL);

	grandparent = parent->parent;

	/* L'oncle est l'autre enfant du grandparent */
	/* Si le parent est l'enfant gauche, l'oncle est l'enfant droit */
	if (grandparent->left == parent)
		return (grandparent->right);

	/* Sinon, l'oncle est l'enfant gauche */
	return (grandparent->left);
}
