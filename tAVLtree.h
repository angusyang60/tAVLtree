#include <stdio.h>
#include <stdlib.h>

typedef struct AVLTree* avltree_t;
typedef struct AVLTree* position_t;

struct AVLTree{
	char 		node;	///avl tree node
	int 		hight;	///avl tree node hight
	avltree_t 	left;	///avl tree left child
	avltree_t 	right;	///avl tree right child
};

avltree_t tAVLtree_insert(avltree_t T, char node);
avltree_t tAVLtree_delete(avltree_t T, char node);
avltree_t tAVLtree_search(avltree_t T, char node);
avltree_t tAVLtree_eraseAll(avltree_t avltree);
int tAVLtree_hight(position_t T);
