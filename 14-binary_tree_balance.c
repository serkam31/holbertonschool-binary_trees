#include "binary_trees.h"
/**
 * get_height - Measures the height of a binary tree
 * @tree: Pointer to the root node
 *
 * Return: Height of the tree, or -1 if tree is NULL
 */
/*Fonction helper pour calculer la hauteur */
int get_height(const binary_tree_t *tree)
{
	int left_height, right_height;

	/* Cas 1 : Si tree est NULL */
	if (tree == NULL)
		return (-1);

	/* Cas 2 : Calculer récursivement les hauteurs */
	left_height = get_height(tree->left);
	right_height = get_height(tree->right);

	/* Cas 3 : Retourner la plus grande hauteur + 1 */
	if (left_height > right_height)
		return (left_height + 1);
	else
		return (right_height + 1);
}

/**
 * binary_tree_balance - Measures the balance factor of a binary tree
 * @tree: Pointer to the root node of the tree to measure the balance factor
 *
 * Return: Balance factor, or 0 if tree is NULL
 */
/* Fonction principale */
int binary_tree_balance(const binary_tree_t *tree)
{
	int left_height, right_height;

	if (tree == NULL)
		return (0);

	/* Ligne 1 : Calculer la hauteur du sous-arbre gauche */
	left_height = get_height(tree->left);

	/* Ligne 2 : Calculer la hauteur du sous-arbre droit */
	right_height = get_height(tree->right);

	/* Ligne 3 : Retourner la différence */
	return (left_height - right_height);
}
