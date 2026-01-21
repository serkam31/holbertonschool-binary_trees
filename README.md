# Arbres Binaires (Binary Trees)

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![Holberton School](https://img.shields.io/badge/Holberton-School-red)

## Description

Ce projet explore les **arbres binaires**, une structure de données fondamentale en informatique. Un arbre binaire est une structure hiérarchique où chaque nœud peut avoir au maximum deux enfants : un enfant gauche et un enfant droit.

Ce repository contient une implémentation complète en C avec toutes les opérations de base et avancées sur les arbres binaires.

---

## Structure du Projet

### Fichier d'en-tête

- [binary_trees.h](binary_trees.h) : Contient toutes les définitions de structures et prototypes de fonctions

### Structure de données

```c
typedef struct binary_tree_s
{
    int n;                          /* Valeur stockée dans le nœud */
    struct binary_tree_s *parent;   /* Pointeur vers le parent */
    struct binary_tree_s *left;     /* Pointeur vers l'enfant gauche */
    struct binary_tree_s *right;    /* Pointeur vers l'enfant droit */
} binary_tree_t;
```

---

## Fonctions Implémentées

### 1. Opérations de Base

| Fonction | Fichier | Description |
|----------|---------|-------------|
| `binary_tree_node` | [0-binary_tree_node.c](0-binary_tree_node.c) | Crée un nouveau nœud |
| `binary_tree_insert_left` | [1-binary_tree_insert_left.c](1-binary_tree_insert_left.c) | Insère un nœud à gauche |
| `binary_tree_insert_right` | [2-binary_tree_insert_right.c](2-binary_tree_insert_right.c) | Insère un nœud à droite |
| `binary_tree_delete` | [3-binary_tree_delete.c](3-binary_tree_delete.c) | Supprime un arbre entier |

### 2. Vérifications

| Fonction | Fichier | Description |
|----------|---------|-------------|
| `binary_tree_is_leaf` | [4-binary_tree_is_leaf.c](4-binary_tree_is_leaf.c) | Vérifie si un nœud est une feuille |
| `binary_tree_is_root` | [5-binary_tree_is_root.c](5-binary_tree_is_root.c) | Vérifie si un nœud est la racine |
| `binary_tree_is_full` | [15-binary_tree_is_full.c](15-binary_tree_is_full.c) | Vérifie si l'arbre est complet |
| `binary_tree_is_perfect` | [16-binary_tree_is_perfect.c](16-binary_tree_is_perfect.c) | Vérifie si l'arbre est parfait |

### 3. Parcours (Traversal)

| Fonction | Fichier | Description |
|----------|---------|-------------|
| `binary_tree_preorder` | [6-binary_tree_preorder.c](6-binary_tree_preorder.c) | Parcours préfixe (racine → gauche → droite) |
| `binary_tree_inorder` | [7-binary_tree_inorder.c](7-binary_tree_inorder.c) | Parcours infixe (gauche → racine → droite) |
| `binary_tree_postorder` | [8-binary_tree_postorder.c](8-binary_tree_postorder.c) | Parcours postfixe (gauche → droite → racine) |

### 4. Mesures et Propriétés

| Fonction | Fichier | Description |
|----------|---------|-------------|
| `binary_tree_height` | [9-binary_tree_height.c](9-binary_tree_height.c) | Calcule la hauteur de l'arbre |
| `binary_tree_depth` | [10-binary_tree_depth.c](10-binary_tree_depth.c) | Calcule la profondeur d'un nœud |
| `binary_tree_size` | [11-binary_tree_size.c](11-binary_tree_size.c) | Compte le nombre total de nœuds |
| `binary_tree_leaves` | [12-binary_tree_leaves.c](12-binary_tree_leaves.c) | Compte le nombre de feuilles |
| `binary_tree_nodes` | [13-binary_tree_nodes.c](13-binary_tree_nodes.c) | Compte les nœuds avec au moins un enfant |
| `binary_tree_balance` | [14-binary_tree_balance.c](14-binary_tree_balance.c) | Calcule le facteur d'équilibre |

### 5. Relations Familiales

| Fonction | Fichier | Description |
|----------|---------|-------------|
| `binary_tree_sibling` | [17-binary_tree_sibling.c](17-binary_tree_sibling.c) | Trouve le frère d'un nœud |
| `binary_tree_uncle` | [18-binary_tree_uncle.c](18-binary_tree_uncle.c) | Trouve l'oncle d'un nœud |

### 6. Utilitaires

| Fonction | Fichier | Description |
|----------|---------|-------------|
| `binary_tree_print` | [binary_tree_print.c](binary_tree_print.c) | Affiche l'arbre de manière visuelle |

---

## Compilation

Pour compiler les fichiers, utilisez `gcc` avec les options suivantes :

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o binary_trees
```

### Exemple de compilation pour un exercice spécifique

```bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 0-main.c 0-binary_tree_node.c binary_tree_print.c -o 0-node
```

---

## Utilisation

### Exemple 1 : Créer un arbre simple

```c
#include "binary_trees.h"

int main(void)
{
    binary_tree_t *root;

    root = binary_tree_node(NULL, 98);
    root->left = binary_tree_node(root, 12);
    root->right = binary_tree_node(root, 402);

    binary_tree_print(root);
    binary_tree_delete(root);

    return (0);
}
```

**Sortie :**
```
  .-------(098)-------.
(012)              (402)
```

### Exemple 2 : Parcours d'un arbre

```c
void print_num(int n)
{
    printf("%d\n", n);
}

int main(void)
{
    binary_tree_t *root;

    root = binary_tree_node(NULL, 98);
    root->left = binary_tree_node(root, 12);
    root->right = binary_tree_node(root, 402);

    printf("Parcours préfixe :\n");
    binary_tree_preorder(root, &print_num);

    printf("\nParcours infixe :\n");
    binary_tree_inorder(root, &print_num);

    binary_tree_delete(root);
    return (0);
}
```

---

## Concepts Clés

### Types d'arbres binaires

1. **Arbre Complet (Full Binary Tree)** : Chaque nœud a soit 0 soit 2 enfants
2. **Arbre Parfait (Perfect Binary Tree)** : Toutes les feuilles sont au même niveau
3. **Arbre Équilibré (Balanced Binary Tree)** : La différence de hauteur entre les sous-arbres est ≤ 1

### Complexité Temporelle

| Opération | Complexité |
|-----------|------------|
| Insertion | O(1) pour insertion directe |
| Recherche | O(n) pour arbre non ordonné |
| Suppression | O(n) pour supprimer tout l'arbre |
| Parcours | O(n) |
| Hauteur | O(n) |

---

## Ressources Utiles

- [Cours complet sur les arbres binaires](COURS_ARBRES_BINAIRES.md)
- [Binary Tree - Wikipedia](https://en.wikipedia.org/wiki/Binary_tree)
- [Tree Traversal Techniques](https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/)

---

## Auteur

Étudiant à Holberton School - MARQUES Matéo

---

