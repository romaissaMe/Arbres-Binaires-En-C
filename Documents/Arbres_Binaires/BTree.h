#ifndef BTREE_H 
#define BTREE_H


#ifndef RLIST_H
#ifndef MLIST_H
#ifndef DLIST_H

typedef int Element;

#endif
#endif
#endif
#define MAX 100000
// Type des noeuds.
typedef struct node{
	Element elem;
  	struct node *left;
	struct node *right;
}Node;

// Type des arbres.
typedef Node *BTree;
//les piles
typedef struct pile
{
    BTree items[MAX];
    int top;
    int taille;
} pile;

//ltype les files
typedef struct file
{   BTree items[MAX];
    int queue;
    int tete;

}file;

/*****************************************************************************/
/**************************** fonctions de base ******************************/
/*****************************************************************************/

// Renvoie un arbre vide.
BTree makeEmptyBTree(void);

// Renvoie un arbre binaire dont la racine est e, le fils gauche est l et le fils droit r.
BTree makeNode(Element e, BTree l,  BTree r);

//  Renvoie un arbre binaire dont la racine est e et les fils gauche et droit sont vides.
BTree makeLeaf(Element e);

// Renvoie 0 si bt n'est pas vide.
int isEmptyBTree(BTree bt);

// Renvoie l'Ã©lÃ©ment Ã  la racine de bt s'il n'est pas vide.
// Provoque une erreur si bt est vide.
Element root(BTree bt);

// Renvoie le fils gauche de bt s'il n'est pas vide.
// Provoque une erreur si bt est vide.
BTree leftChild(BTree bt);

// Renvoie le fils droit de bt s'il n'est pas vide.
// Provoque une erreur si bt est vide.
BTree rightChild(BTree bt);

// Renvoie 0 si bt n'est pas une feuille.
int isLeaf(BTree bt);

// LibÃ¨re l'espace allouÃ© pour c.
void freeNode(Node *c);

/*****************************************************************************/
/*************************** fonctions bas niveau ****************************/
/*****************************************************************************/

// InsÃ¨re une feuille contenant e comme fils droit de n.
// Provoque une erreur si n est vide ou si son fils droit n'est pas vide.
void insertRight(Node *n, Element e);

// InsÃ¨re une feuille contenant e comme fils gauche de n.
// Provoque une erreur si n est vide ou si son fils gauche n'est pas vide.
void insertLeft(Node *n, Element e);


// Supprime (et renvoie sa racine) le fils droit de n si c'est une feuille.
// Provoque une erreur si n est vide ou si son fils droit n'est pas une feuille.
Element deleteRight(Node *n);

// Supprime (et renvoie sa racine) le fils gauche de n si c'est une feuille.
// Provoque une erreur si n est vide ou si son fils gauche n'est pas une feuille.
Element deleteLeft(Node *n);


// InsÃ¨re une feuille contenant e le plus Ã  droite possible dans l'arbre *bt.
// Si l'abre est vide, l'insertion se fait Ã  la racine.
void insertRightmostNode(BTree *bt, Element e);

// Supprime (et renvoie sa racine) le noeud le plus Ã  gauche possible dans l'arbre *bt.
// Provoque une erreur si *bt est vide. Peut supprimer la racine si elle est le noeud le plus Ã  gauche.
Element deleteLeftmostNode(BTree *bt);


#endif