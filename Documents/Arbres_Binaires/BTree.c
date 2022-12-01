#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BTree.h"
 

void errorB(char *s){
	fprintf(stderr, "%s", s);
	exit(EXIT_FAILURE);
}
// Type des arbres.
typedef Node *BTree;
//pile
typedef struct cell{
    Node *val;
	struct cell *suiv;
}cell;

//pile
void initPile(pile *p)
{
    p->top = -1;
    p->taille = 0;
}
int isempty(pile *p) {
   if (p->top == -1)
        return 1;
    else
        return 0;
}
int pilePleine(pile *s)
{
    if (s->top == MAX - 1)
        return 1;
    else
        return 0;
}
void push(pile *p, BTree bt) {
 
    if (pilePleine(p))
    {
        printf("la pile est pleine");
    }
    else
    {
        p->top++;
        p->items[p->top] = bt;
    }
    p->taille++;

}
BTree pop(pile *p) {
  if (isempty(p))
        return NULL;
    p->taille--;
    BTree val = p->items[p->top];
    p->top--;
    return val;
    }
//file
void initFile(file *f)
{
    f->tete = 0;
    f->queue = -1;
}
int isemptyfile(file *f) {
   if (f->tete>f->queue)
        return 1;
    else
        return 0;
}
int filePleine(file *f)
{
    if (f->tete == MAX && f->tete>f->queue)
        return 1;
    else
        return 0;
}
void enfiler(file *f, BTree bt){
  if(filePleine(f)) printf("la file est pleine"); else{
   f->queue=f->queue+1;
    f->items[f->queue]=bt;
  }
}
BTree defiler (file *f) {
  if(filePleine(f)) return NULL;
  else{ BTree X=f->items[f->tete];
    f->tete=f->tete+1;
    return X;
  }
}





/*****************************************************************************/
/**************************** fonctions de base ******************************/
/*****************************************************************************/

BTree makeEmptyBTree(void){
	return (BTree)NULL;	
}

BTree makeNode(Element e, BTree l,  BTree r){
	BTree new;
	if ((new=(BTree)malloc(sizeof(Node)))==NULL) errorB("Allocation ratée!");
	new->elem=e;
	new->left=l;
	new->right=r;
	return new;
}

BTree makeLeaf(Element e){
	return makeNode(e,makeEmptyBTree(),makeEmptyBTree());
}


int isEmptyBTree(BTree bt){
	return (bt==NULL);
}

Element root(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de noeud à la racine d'un arbre vide!!!");
	return bt->elem;
}


BTree leftChild(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de fils gauche dans un arbre vide!!!");
	return bt->left;
}

BTree rightChild(BTree bt){
	if(isEmptyBTree(bt)) errorB("Pas de fils droit dans un arbre vide!!!");
	return bt->right;
}

int isLeaf(BTree bt){
	return !isEmptyBTree(bt) && isEmptyBTree(leftChild(bt)) && isEmptyBTree(rightChild(bt));
}

void freeNode(Node *c){
	free(c);
}

/*****************************************************************************/
/*************************** fonctions bas niveau ****************************/
/*****************************************************************************/

void insertRight(Node *n, Element e){
	if(!isEmptyBTree(n) && isEmptyBTree(rightChild(n)))
		n->right=makeLeaf(e); 
	else errorB("insertRight impossible!");
}

void insertLeft(Node *n, Element e){
	if(!isEmptyBTree(n) && isEmptyBTree(leftChild(n)))
		n->left=makeLeaf(e);
	else errorB("insertLeft impossible!");
}

Element deleteRight(Node *n){
	if(isEmptyBTree(n) || !isLeaf(rightChild(n)))
		errorB("deleteRight imossible!");
		
	Element res=root(n->right);
	n->right=makeEmptyBTree();
	return res;
}

Element deleteLeft(Node *n){
	if(isEmptyBTree(n)  || !isLeaf(leftChild(n)))
		errorB("deleteLeft imossible!");
		
	Element res=root(n->left);
	n->left=makeEmptyBTree();
	return res;
}

void insertRightmostNode(BTree *bt, Element e){
	if(isEmptyBTree(*bt))
		*bt=makeLeaf(e);
	else{
		BTree tmp=*bt;
		while(!isEmptyBTree(rightChild(tmp)))
			tmp=rightChild(tmp);
		insertRight(tmp,e);
	}
}

Element deleteLeftmostNode(BTree *bt){
	Element res;
	if(isEmptyBTree(*bt))
		errorB("deleteLeftmostNode imossible!");
	if(isEmptyBTree(leftChild(*bt))){
		res=root(*bt);
		*bt=rightChild(*bt);
	}
	else{
		BTree tmp=*bt;
		while(!isEmptyBTree(leftChild(leftChild(tmp))))
			tmp=leftChild(tmp);
		res=root(leftChild(tmp));
		tmp->left=(tmp->left)->right;
	}
	return res;
}
/*******************Fonctions recursives********************/
//equalBTrees
int equalBTrees(BTree bt1, BTree bt2){
	if(bt1==NULL || bt2 == NULL){
		return (bt1==bt2);
	}
	return ( bt1->elem == bt2->elem
	&& equalBTrees(bt1->left,bt2->left)
	&& equalBTrees(bt1->right,bt2->right) 
	);
}
//subtree
int isSubBTree(BTree sbt, BTree bt){
	if (sbt==NULL){
		return 1;
	}
	if (bt==NULL){
		return 0;
	}
	if (equalBTrees(sbt,bt)){
		return 1;
	}
	return (equalBTrees(sbt,bt->left)||equalBTrees(sbt,bt->right));
	
}
//findElement
int findElem(BTree bt, Element e){
	if(bt == NULL){
		return 0;
	}
	if(bt->elem == e){
		return 1;
	}
	return(findElem(bt->left,e)||findElem(bt->right,e));
}
//findMin
Element findMin(BTree bt){
	if(bt==NULL){
		return 0;
	}
	Element min = root(bt); 
  if(bt->left!=NULL){
    Element left=findMin(bt->left);
    if (left<min){
		 min=left;
	}
   }
  if(bt->right!=NULL)  {
    Element right =findMin(bt->right);
	  if(right<min){
		min =right;
	  }
  }
	
	return min;
}
//parcours en largeur
// Fonction pour imprimer tous les nœuds d'un niveau donné de gauche à droite
int printLevel(Node* root, int level)
{
    if (root == NULL) {
        return 0;
    }
 
    if (level == 1)
    {
        printf("%d ",root->elem);
 
        // renvoie true si au moins un nœud est présent à un niveau donné
        return 1;
    }
 
    int left = printLevel(root->left, level - 1);
    int right = printLevel(root->right, level - 1);
 
    return left || right;
}
 
// Fonction pour imprimer le parcours d'ordre de niveau d'un arbre binaire donné
void printWidthOrder(Node* root)
{
    // commence au niveau 1 — jusqu'à la hauteur de l'arbre
    int level = 1;
 
    // exécuter jusqu'à ce que printLevel() renvoie false
    while (printLevel(root, level)) {
        level++;
    }
}

/*******************Fonctions iteratives********************/
//equalBTrees
int equalBTrees2(BTree bt1, BTree bt2){
	if(bt1==NULL || bt2 == NULL){
		return (bt1==bt2);
	}
	Element x1,x2;
	pile *p1;
	pile *p2;
	empiler(p1,bt1);
	empiler(p2,bt2);
	BTree v1= NULL;
	BTree v2= NULL;
	while(p1->sommet != NULL && p2->sommet != NULL){
		v1=depiler(p1);
		v2=depiler(p2);
		if(v1->elem != v2->elem){
			return 0;
		}
		if (v1->left && v2->left){
			empiler(p1,bt1->left);
		    empiler(p2,bt2->left);
		}
		
		if (v1->left==NULL || v2->left==NULL){
			return 0;
		}
		if (v1->right && v2->right){
			empiler(p1,bt1->left);
		    empiler(p2,bt2->left);
		}
		
		if (v1->right==NULL || v2->right==NULL){
			return 0;
		}
	}
	return 1;
}
int isSubBTree2(BTree sbt, BTree bt){
	pile *p;
	Node *tmp;
	empiler(p,bt);
	while(p->sommet!=NULL){
		tmp=depiler(p);
		if(tmp->elem==sbt->elem){
			if(equalBTrees2(sbt,tmp)) return 1;
		}
		if(tmp->right){
			empiler(p,tmp->right);
		}
		if(tmp->left){
			empiler(p,tmp->left);
		}
	}
	return 0;
}
//findElement
int findElem2(BTree bt, Element e){
	pile *p = (pile *)malloc(sizeof(pile));
  initPile(p);
	Node *k;
  if (bt!=NULL){
    push(p,bt);
  }
	
	while(!isempty(p)){
	 k=pop(p);
	 if(k->elem==e){
	 	return 1;
	 }
	 if(k->left != NULL){
	 	push(p,k->left);
	 }	
	 if(k->right != NULL){
	 	push(p,k->right);
	 }
	}
	return 0;
}
//findMIN
Element findMin2(BTree bt){
	pile *p = (pile *)malloc(sizeof(pile));
  initPile(p);
  Element min;
  Node *x;
  if(bt!=NULL){
    min = bt->elem;
    push(p,bt);
  }
	while(!isempty(p)){
		 x = pop(p);
		if(x->elem <= min){
			min = x->elem;
		}
		if(x->left!=NULL){
      	push(p,bt->left);
       }
	   if(x->right!=NULL){
	     push(p,bt->right);	
	    }
	}
	return min; 
}
//parcours en largeur
void printWidthOrder2(BTree bt){
	file *f = (file *)malloc(sizeof(file));
	initFile(f);
  if (bt == NULL){
    printf("l'arbre est vide");
  }
	enfiler(f,bt);
	while(!isemptyfile(f)){
		BTree x = defiler(f);
		printf("%d  ",x->elem);
		 if(x->left!=NULL){
          enfiler(f,x->left);
		}
		if(x->right!=NULL){
          enfiler(f,x->right);
		}
	}
}
int main(){
	int lengthBt1=12;
	int lengthBt2=12;
	BTree bt1 = makeEmptyBTree();
	BTree bt2 = makeEmptyBTree();
	//remplir arbre 1
	Node *e12=makeLeaf(31);
	Node *e11=makeNode(22,e12,NULL);
	Node *e10=makeLeaf(6);
	Node *e9=makeNode(2,NULL,e11);
	Node *e8=makeLeaf(10);
	Node *e7=makeLeaf(28);
	Node *e6=makeLeaf(12);
	Node *e5=makeNode(77,e10,NULL);
	Node *e4=makeNode(31,e8,e9);
	Node *e3=makeNode(100,e6,e7);
	Node *e2=makeNode(15,e4,e5);
	bt1=makeNode(18,e2,e3);
	//remplir arbre 2
	Node *n12=makeLeaf(30);
	Node *n8 = makeLeaf(0);
	Node *n10=makeLeaf(50);
	Node *n11=makeLeaf(110);
	Node *n6=makeLeaf(80);
	Node *n9=makeNode(20,NULL,n12);
	Node *n4 = makeNode(10,n8,n9);
	Node *n5 = makeNode(60,n10,NULL);
	Node *n7 = makeNode(100,NULL,n11);
	Node *n2 = makeNode(40,n4,n5);
	Node *n3 = makeNode(90,n6,n7);
	bt2=makeNode(70,n2,n3);
	printf("racine bt1:%d \n",root(bt1));
	printf("racine bt2:%d \n",root(bt2));
  /*printWidthOrder(bt1);
  Element e= findMin(bt1);
  printf("min = %d \n",e); 
  Element x = findElem(bt1,150);
  printf("%d",x); 
  if (x==1){
    printf("element existe dans l'arbre");
  }
  else{
    printf("element n'existe pas dans l'arbre");
  } */
  //printWidthOrder2(bt1);
  /* Element x = findElem2(bt1,2);
   printf("%d \n",x); 
  if (x==1){
    printf("element existe dans l'arbre");
  }
  else{
    printf("element n'existe pas dans l'arbre");
  }*/
  // Element e= findMin2(bt1);
  //printf("min = %d \n",e); 

	return 0;
}