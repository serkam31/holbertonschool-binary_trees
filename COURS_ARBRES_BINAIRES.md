# Cours Complet : Les Arbres Binaires en C

## Table des Matières

1. [Introduction aux Arbres Binaires](#1-introduction-aux-arbres-binaires)
2. [Structure de Données](#2-structure-de-données)
3. [Opérations de Base](#3-opérations-de-base)
4. [Parcours d'Arbres](#4-parcours-darbres)
5. [Propriétés et Mesures](#5-propriétés-et-mesures)
6. [Types d'Arbres Binaires](#6-types-darbres-binaires)
7. [Relations Familiales](#7-relations-familiales)
8. [Exercices Pratiques](#8-exercices-pratiques)
9. [Complexité et Performance](#9-complexité-et-performance)
10. [Conseils et Pièges à Éviter](#10-conseils-et-pièges-à-éviter)

---

## 1. Introduction aux Arbres Binaires

### Qu'est-ce qu'un arbre binaire?

Un **arbre binaire** est une structure de données hiérarchique composée de nœuds. Chaque nœud peut avoir au maximum **deux enfants** : un enfant gauche et un enfant droit.

### Vocabulaire de base

```
         A          ← Racine (root)
        / \
       B   C        ← Enfants de A
      / \   \
     D   E   F      ← Feuilles (leaves)
```

- **Racine (root)** : Le nœud au sommet de l'arbre (A)
- **Parent** : Un nœud qui a des enfants (A est parent de B et C)
- **Enfant (child)** : Un nœud descendant direct (B et C sont enfants de A)
- **Feuille (leaf)** : Un nœud sans enfants (D, E, F)
- **Nœud interne** : Un nœud avec au moins un enfant (A, B, C)
- **Frère (sibling)** : Nœuds qui partagent le même parent (B et C)
- **Oncle (uncle)** : Le frère du parent (C est l'oncle de D et E)

### Hauteur et Profondeur

- **Hauteur d'un nœud** : Le nombre d'arêtes sur le plus long chemin du nœud vers une feuille
- **Profondeur d'un nœud** : Le nombre d'arêtes depuis la racine jusqu'au nœud
- **Hauteur de l'arbre** : La hauteur de la racine

```
         A          ← Profondeur 0, Hauteur 2
        / \
       B   C        ← Profondeur 1, Hauteur 1 (B), Hauteur 0 (C)
      / \
     D   E          ← Profondeur 2, Hauteur 0
```

---

## 2. Structure de Données

### Définition de la structure

```c
typedef struct binary_tree_s
{
    int n;                          /* Valeur stockée dans le nœud */
    struct binary_tree_s *parent;   /* Pointeur vers le parent */
    struct binary_tree_s *left;     /* Pointeur vers l'enfant gauche */
    struct binary_tree_s *right;    /* Pointeur vers l'enfant droit */
} binary_tree_t;
```

### Explication des champs

1. **`int n`** : La valeur entière stockée dans le nœud
2. **`parent`** : Permet de remonter dans l'arbre (utile pour certains algorithmes)
3. **`left`** : Pointe vers le sous-arbre gauche
4. **`right`** : Pointe vers le sous-arbre droit

### Pourquoi utiliser un pointeur parent?

Le pointeur `parent` permet de :
- Remonter facilement dans l'arbre
- Trouver les frères et oncles plus facilement
- Simplifier certaines opérations de suppression

---

## 3. Opérations de Base

### 3.1 Créer un nœud

**Fichier : [0-binary_tree_node.c](0-binary_tree_node.c)**

```c
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
    binary_tree_t *new_node;

    /* Allouer la mémoire pour le nouveau nœud */
    new_node = malloc(sizeof(binary_tree_t));
    if (new_node == NULL)
        return (NULL);

    /* Initialiser les champs */
    new_node->n = value;
    new_node->parent = parent;
    new_node->left = NULL;
    new_node->right = NULL;

    return (new_node);
}
```

**Points clés :**
- Toujours vérifier si `malloc` réussit
- Initialiser tous les pointeurs à `NULL`
- Le parent peut être `NULL` pour la racine

**Exemple d'utilisation :**
```c
binary_tree_t *root = binary_tree_node(NULL, 98);  /* Créer la racine */
```

---

### 3.2 Insérer à gauche

**Fichier : [1-binary_tree_insert_left.c](1-binary_tree_insert_left.c)**

Cette fonction insère un nouveau nœud comme enfant gauche. Si un enfant gauche existe déjà, le nouveau nœud prend sa place et l'ancien devient l'enfant gauche du nouveau.

```c
binary_tree_t *binary_tree_insert_left(binary_tree_t *parent, int value)
{
    binary_tree_t *new_node;

    if (parent == NULL)
        return (NULL);

    new_node = binary_tree_node(parent, value);
    if (new_node == NULL)
        return (NULL);

    /* Si un enfant gauche existe déjà */
    if (parent->left != NULL)
    {
        new_node->left = parent->left;      /* Le nouveau prend l'ancien */
        parent->left->parent = new_node;    /* Mettre à jour le parent */
    }

    parent->left = new_node;  /* Attacher le nouveau nœud */

    return (new_node);
}
```

**Visualisation :**
```
Avant :                  Après insertion de 54 à gauche de 98 :
    98                          98
   /                           /
  12                          54
                             /
                            12
```

---

### 3.3 Insérer à droite

**Fichier : [2-binary_tree_insert_right.c](2-binary_tree_insert_right.c)**

Même principe que l'insertion à gauche, mais pour l'enfant droit.

```c
binary_tree_t *binary_tree_insert_right(binary_tree_t *parent, int value)
{
    binary_tree_t *new_node;
    binary_tree_t *old_right;

    if (parent == NULL)
        return (NULL);

    new_node = malloc(sizeof(binary_tree_t));
    if (new_node == NULL)
        return (NULL);

    old_right = parent->right;

    if (old_right != NULL)
        old_right->parent = new_node;

    new_node->n = value;
    new_node->right = old_right;
    new_node->parent = parent;
    new_node->left = NULL;

    parent->right = new_node;

    return (new_node);
}
```

---

### 3.4 Supprimer un arbre

**Fichier : [3-binary_tree_delete.c](3-binary_tree_delete.c)**

Pour supprimer un arbre, on doit libérer tous les nœuds. On utilise la **récursion** avec un parcours post-ordre (enfants avant parent).

```c
void binary_tree_delete(binary_tree_t *tree)
{
    if (tree == NULL)
        return;

    /* Supprimer récursivement les sous-arbres */
    binary_tree_delete(tree->left);
    binary_tree_delete(tree->right);

    /* Libérer le nœud courant */
    free(tree);
}
```

**Ordre de suppression :**
```
       1
      / \
     2   3
    /
   4

Ordre : 4 → 2 → 3 → 1
```

**Pourquoi cet ordre ?** Si on supprime le parent avant les enfants, on perd l'accès aux enfants !

---

## 4. Parcours d'Arbres

Les parcours permettent de visiter tous les nœuds d'un arbre dans un ordre spécifique.

### 4.1 Parcours Préfixe (Pre-order)

**Ordre : Racine → Gauche → Droite**

**Fichier : [6-binary_tree_preorder.c](6-binary_tree_preorder.c)**

```c
void binary_tree_preorder(const binary_tree_t *tree, void (*func)(int))
{
    if (tree == NULL || func == NULL)
        return;

    func(tree->n);                          /* 1. Traiter la racine */
    binary_tree_preorder(tree->left, func); /* 2. Sous-arbre gauche */
    binary_tree_preorder(tree->right, func);/* 3. Sous-arbre droit */
}
```

**Exemple :**
```
       1
      / \
     2   3
    / \
   4   5

Parcours préfixe : 1 → 2 → 4 → 5 → 3
```

**Utilisation :** Copier un arbre, créer une représentation préfixée.

---

### 4.2 Parcours Infixe (In-order)

**Ordre : Gauche → Racine → Droite**

**Fichier : [7-binary_tree_inorder.c](7-binary_tree_inorder.c)**

```c
void binary_tree_inorder(const binary_tree_t *tree, void (*func)(int))
{
    if (tree == NULL || func == NULL)
        return;

    binary_tree_inorder(tree->left, func);  /* 1. Sous-arbre gauche */
    func(tree->n);                          /* 2. Traiter la racine */
    binary_tree_inorder(tree->right, func); /* 3. Sous-arbre droit */
}
```

**Exemple :**
```
       1
      / \
     2   3
    / \
   4   5

Parcours infixe : 4 → 2 → 5 → 1 → 3
```

**Utilisation :** Pour les arbres binaires de recherche (BST), ce parcours donne les valeurs **triées**.

---

### 4.3 Parcours Postfixe (Post-order)

**Ordre : Gauche → Droite → Racine**

**Fichier : [8-binary_tree_postorder.c](8-binary_tree_postorder.c)**

```c
void binary_tree_postorder(const binary_tree_t *tree, void (*func)(int))
{
    if (tree == NULL || func == NULL)
        return;

    binary_tree_postorder(tree->left, func); /* 1. Sous-arbre gauche */
    binary_tree_postorder(tree->right, func);/* 2. Sous-arbre droit */
    func(tree->n);                           /* 3. Traiter la racine */
}
```

**Exemple :**
```
       1
      / \
     2   3
    / \
   4   5

Parcours postfixe : 4 → 5 → 2 → 3 → 1
```

**Utilisation :** Supprimer un arbre, calculer la taille, évaluer des expressions.

---

### 4.4 Tableau comparatif des parcours

| Parcours | Ordre | Utilisation typique |
|----------|-------|---------------------|
| **Préfixe** | Racine → G → D | Copier l'arbre, expressions préfixées |
| **Infixe** | G → Racine → D | BST triés, expressions algébriques |
| **Postfixe** | G → D → Racine | Supprimer l'arbre, expressions postfixées |

---

## 5. Propriétés et Mesures

### 5.1 Vérifier si c'est une feuille

**Fichier : [4-binary_tree_is_leaf.c](4-binary_tree_is_leaf.c)**

Une feuille est un nœud **sans enfants**.

```c
int binary_tree_is_leaf(const binary_tree_t *node)
{
    if (node == NULL)
        return (0);

    /* Une feuille n'a ni enfant gauche ni enfant droit */
    if (node->left == NULL && node->right == NULL)
        return (1);

    return (0);
}
```

---

### 5.2 Vérifier si c'est la racine

**Fichier : [5-binary_tree_is_root.c](5-binary_tree_is_root.c)**

La racine est le seul nœud **sans parent**.

```c
int binary_tree_is_root(const binary_tree_t *node)
{
    if (node == NULL)
        return (0);

    /* La racine n'a pas de parent */
    if (node->parent == NULL)
        return (1);

    return (0);
}
```

---

### 5.3 Calculer la hauteur

**Fichier : [9-binary_tree_height.c](9-binary_tree_height.c)**

La hauteur est le nombre d'arêtes sur le plus long chemin vers une feuille.

```c
size_t binary_tree_height(const binary_tree_t *tree)
{
    size_t left_height, right_height;

    if (tree == NULL)
        return (0);

    /* Si c'est une feuille, hauteur = 0 */
    if (tree->left == NULL && tree->right == NULL)
        return (0);

    /* Calculer récursivement les hauteurs */
    left_height = binary_tree_height(tree->left);
    right_height = binary_tree_height(tree->right);

    /* Retourner la plus grande hauteur + 1 */
    if (left_height > right_height)
        return (left_height + 1);
    else
        return (right_height + 1);
}
```

**Exemple :**
```
       1          Hauteur = 2
      / \
     2   3        Hauteur = 1 (pour 2)
    /
   4              Hauteur = 0 (pour 4, feuille)
```

---

### 5.4 Calculer la profondeur

**Fichier : [10-binary_tree_depth.c](10-binary_tree_depth.c)**

La profondeur est le nombre d'arêtes depuis la racine.

```c
size_t binary_tree_depth(const binary_tree_t *tree)
{
    size_t depth = 0;

    if (tree == NULL)
        return (0);

    /* Remonter vers la racine en comptant */
    while (tree->parent != NULL)
    {
        depth++;
        tree = tree->parent;
    }

    return (depth);
}
```

**Astuce :** On remonte avec le pointeur `parent` jusqu'à la racine.

---

### 5.5 Compter le nombre de nœuds

**Fichier : [11-binary_tree_size.c](11-binary_tree_size.c)**

```c
size_t binary_tree_size(const binary_tree_t *tree)
{
    if (tree == NULL)
        return (0);

    /* 1 (nœud courant) + taille gauche + taille droite */
    return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}
```

---

### 5.6 Compter les feuilles

**Fichier : [12-binary_tree_leaves.c](12-binary_tree_leaves.c)**

```c
size_t binary_tree_leaves(const binary_tree_t *tree)
{
    if (tree == NULL)
        return (0);

    /* Si c'est une feuille */
    if (tree->left == NULL && tree->right == NULL)
        return (1);

    /* Sinon, compter dans les sous-arbres */
    return (binary_tree_leaves(tree->left) + binary_tree_leaves(tree->right));
}
```

---

### 5.7 Compter les nœuds internes

**Fichier : [13-binary_tree_nodes.c](13-binary_tree_nodes.c)**

Un nœud interne a au moins un enfant.

```c
size_t binary_tree_nodes(const binary_tree_t *tree)
{
    if (tree == NULL)
        return (0);

    /* Si le nœud a au moins un enfant */
    if (tree->left != NULL || tree->right != NULL)
        return (1 + binary_tree_nodes(tree->left) + binary_tree_nodes(tree->right));

    return (0);
}
```

---

### 5.8 Facteur d'équilibre

**Fichier : [14-binary_tree_balance.c](14-binary_tree_balance.c)**

Le facteur d'équilibre = hauteur du sous-arbre gauche - hauteur du sous-arbre droit.

```c
int binary_tree_balance(const binary_tree_t *tree)
{
    int left_height, right_height;

    if (tree == NULL)
        return (0);

    left_height = height(tree->left);
    right_height = height(tree->right);

    return (left_height - right_height);
}
```

**Interprétation :**
- Balance = 0 : Parfaitement équilibré
- Balance > 0 : Plus lourd à gauche
- Balance < 0 : Plus lourd à droite

---

## 6. Types d'Arbres Binaires

### 6.1 Arbre Complet (Full Binary Tree)

Chaque nœud a **0 ou 2 enfants** (jamais 1 seul).

**Fichier : [15-binary_tree_is_full.c](15-binary_tree_is_full.c)**

```c
int binary_tree_is_full(const binary_tree_t *tree)
{
    if (tree == NULL)
        return (0);

    /* Si c'est une feuille, c'est complet */
    if (tree->left == NULL && tree->right == NULL)
        return (1);

    /* Si les deux enfants existent, vérifier récursivement */
    if (tree->left != NULL && tree->right != NULL)
        return (binary_tree_is_full(tree->left) &&
                binary_tree_is_full(tree->right));

    /* Si un seul enfant existe, pas complet */
    return (0);
}
```

**Exemples :**
```
Complet :          Pas complet :
    1                  1
   / \                / \
  2   3              2   3
 / \                /
4   5              4
```

---

### 6.2 Arbre Parfait (Perfect Binary Tree)

Toutes les feuilles sont au **même niveau** et tous les nœuds internes ont **2 enfants**.

**Fichier : [16-binary_tree_is_perfect.c](16-binary_tree_is_perfect.c)**

```c
int binary_tree_is_perfect(const binary_tree_t *tree)
{
    int left_height, right_height;

    if (tree == NULL)
        return (0);

    if (tree->left == NULL && tree->right == NULL)
        return (1);

    left_height = get_height(tree->left);
    right_height = get_height(tree->right);

    /* Les hauteurs doivent être égales */
    if (left_height != right_height)
        return (0);

    /* Et les sous-arbres doivent être parfaits */
    return (binary_tree_is_perfect(tree->left) &&
            binary_tree_is_perfect(tree->right));
}
```

**Exemples :**
```
Parfait :          Pas parfait :
    1                  1
   / \                / \
  2   3              2   3
 / \ / \            /
4  5 6  7          4
```

**Propriété :** Un arbre parfait de hauteur h a exactement **2^(h+1) - 1** nœuds.

---

## 7. Relations Familiales

### 7.1 Trouver le frère (sibling)

**Fichier : [17-binary_tree_sibling.c](17-binary_tree_sibling.c)**

Le frère est l'autre enfant du parent.

```c
binary_tree_t *binary_tree_sibling(binary_tree_t *node)
{
    if (node == NULL || node->parent == NULL)
        return (NULL);

    /* Si le nœud est l'enfant gauche, retourner l'enfant droit */
    if (node->parent->left == node)
        return (node->parent->right);

    /* Sinon, retourner l'enfant gauche */
    return (node->parent->left);
}
```

**Exemple :**
```
    1
   / \
  2   3    ← 2 et 3 sont frères
```

---

### 7.2 Trouver l'oncle (uncle)

**Fichier : [18-binary_tree_uncle.c](18-binary_tree_uncle.c)**

L'oncle est le frère du parent.

```c
binary_tree_t *binary_tree_uncle(binary_tree_t *node)
{
    if (node == NULL || node->parent == NULL || node->parent->parent == NULL)
        return (NULL);

    /* L'oncle est le frère du parent */
    return (binary_tree_sibling(node->parent));
}
```

**Exemple :**
```
       1
      / \
     2   3    ← 3 est l'oncle de 4 et 5
    / \
   4   5
```

---

## 8. Exercices Pratiques

### Exercice 1 : Construire un arbre

Créez l'arbre suivant :
```
       98
      /  \
    12    402
   /  \
  6    16
```

**Solution :**
```c
binary_tree_t *root = binary_tree_node(NULL, 98);
binary_tree_insert_left(root, 12);
binary_tree_insert_right(root, 402);
binary_tree_insert_left(root->left, 6);
binary_tree_insert_right(root->left, 16);
```

---

### Exercice 2 : Parcours

Pour l'arbre ci-dessus, donnez les parcours :

**Réponses :**
- Préfixe : 98, 12, 6, 16, 402
- Infixe : 6, 12, 16, 98, 402
- Postfixe : 6, 16, 12, 402, 98

---

### Exercice 3 : Propriétés

Pour le même arbre :
- Hauteur : **2**
- Nombre de nœuds : **5**
- Nombre de feuilles : **3** (6, 16, 402)
- Est-il complet ? **Non** (402 n'a qu'un parent sans frère complet)
- Est-il parfait ? **Non** (les feuilles ne sont pas au même niveau)

---

## 9. Complexité et Performance

### Complexités temporelles

| Opération | Complexité | Explication |
|-----------|------------|-------------|
| Création d'un nœud | O(1) | Allocation simple |
| Insertion | O(1) | Si on a le parent |
| Suppression totale | O(n) | Visiter tous les nœuds |
| Recherche | O(n) | Pire cas : parcourir tout l'arbre |
| Parcours | O(n) | Visiter chaque nœud une fois |
| Hauteur | O(n) | Visiter tous les nœuds |
| Taille | O(n) | Compter tous les nœuds |

### Complexités spatiales

- Stockage : **O(n)** où n = nombre de nœuds
- Pile de récursion : **O(h)** où h = hauteur de l'arbre

---

## 10. Conseils et Pièges à Éviter

### Gestion de la mémoire

1. **Toujours vérifier malloc**
```c
new_node = malloc(sizeof(binary_tree_t));
if (new_node == NULL)
    return (NULL);
```

2. **Libérer dans le bon ordre**
```c
/* MAUVAIS : perte de pointeurs */
free(tree);
binary_tree_delete(tree->left);  /* tree est déjà libéré ! */

/* BON : enfants d'abord */
binary_tree_delete(tree->left);
binary_tree_delete(tree->right);
free(tree);
```

### Cas limites à tester

1. **Arbre NULL**
```c
if (tree == NULL)
    return (0);  /* ou valeur appropriée */
```

2. **Feuille (nœud sans enfants)**
```c
if (tree->left == NULL && tree->right == NULL)
    return (valeur_pour_feuille);
```

3. **Racine sans parent**
```c
if (node->parent == NULL)
    /* C'est la racine */
```

### Erreurs courantes

1. **Oublier de mettre à jour le parent**
```c
/* MAUVAIS */
parent->left = new_node;

/* BON */
parent->left = new_node;
new_node->parent = parent;
```

2. **Ne pas gérer l'enfant existant**
```c
/* Dans insert_left, si un enfant existe déjà */
if (parent->left != NULL)
{
    new_node->left = parent->left;
    parent->left->parent = new_node;  /* Important ! */
}
```

3. **Confusion hauteur vs profondeur**
- Hauteur : On descend vers les feuilles
- Profondeur : On monte vers la racine

### Récursion : attention à la pile

Pour les très grands arbres, la récursion peut causer un débordement de pile. Mais pour les exercices académiques, c'est parfait !

---

## Conclusion

Les arbres binaires sont une structure fondamentale en informatique. Ils servent de base pour :
- Les arbres binaires de recherche (BST)
- Les tas (heaps)
- Les arbres AVL et red-black (auto-équilibrés)
- Les arbres de syntaxe abstraite (AST) en compilation

Maîtriser les arbres binaires simples est essentiel avant d'aborder ces structures plus avancées.

---

## Ressources supplémentaires

- [Visualgo](https://visualgo.net/en/bst) - Visualisation interactive d'arbres
- [GeeksforGeeks - Binary Tree](https://www.geeksforgeeks.org/binary-tree-data-structure/)
- [Wikipedia - Binary Tree](https://en.wikipedia.org/wiki/Binary_tree)

---

**Bon courage dans ton apprentissage des arbres binaires !** 🌳
