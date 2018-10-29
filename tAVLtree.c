#include "tAVLtree.h"
#include <string.h>

#define max(x, y) (x > y) ? x : y
#define min(x, y) (x <= y) ? x : y

/**
 * @fn tAVLtree_hight
 * @param T
 * @return int
 */
int tAVLtree_hight(position_t T)
{
	return (!T) ? -1 : T->hight;
}

int tAVLtree_hight_calculate(position_t T1, position_t T2)
{
	if (T1 && T2)
		return max(T1->hight, T2->hight);
	else if(T1 && !T2)
		return T1->hight;
	else if (!T1 && T2)
		return T2->hight;
	else
		return -1;
}

/**
 * @fn tAVLtree_findMin
 * @param tree 
 * @return position_t 
 */
position_t tAVLtree_findMin(avltree_t T)
{
	if (!T)
		return NULL;
	else if (!T->left)
		return T;
	else
		return tAVLtree_findMin(T->left);
	
}

/**
 * @fn tAVLtree_findMax
 * @param tree
 * @return position_t
 */
position_t tAVLtree_findMax(avltree_t T)
{
	if (T) {
		while (T->right) {
			T = T->right;
		}
	}

	return T;
}

/**
 * @fn tAVLtree_singleRotateWithLeft
 * @param k2
 * @return position_t
 */
position_t tAVLtree_singleRotateWithLeft(position_t k2)
{
	position_t k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->hight = max(tAVLtree_hight(k2->left), tAVLtree_hight(k2->right)) + 1;
	k1->hight = max(tAVLtree_hight(k1->left), k2->hight) + 1;

	return k1;
}

/**
 * @fn tAVLtree_singleRotateWithRight
 * @param k2 
 * @return position_t 
 */
position_t tAVLtree_singleRotateWithRight(position_t k2)
{
	position_t k1;

	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;

	k2->hight = max(tAVLtree_hight(k2->left), tAVLtree_hight(k2->right)) + 1;
	k1->hight = max(tAVLtree_hight(k1->right), k2->hight) + 1;

	return k1;
}

/**
 * @fn tAVLtree_doubleRotateWithLeft
 * @param k3
 * @return position_t
 */
position_t tAVLtree_doubleRotateWithLeft(position_t k3)
{
	k3->left = tAVLtree_singleRotateWithRight(k3->left);

	return tAVLtree_singleRotateWithLeft(k3);
}

/**
 * @fn tAVLtree_doubleRotateWithRight
 * @param k3
 * @return position_t
 */
position_t tAVLtree_doubleRotateWithRight(position_t k3)
{
	k3->right = tAVLtree_singleRotateWithLeft(k3->right);

	return tAVLtree_singleRotateWithRight(k3);
}

/**
 * @fn tAVLtree_insert
 * @brief insert node to the avl tree structure
 * @param T main avl tree structure
 * @param node the inserted node
 * @return avltree_t the avltree after node is inserted
 */
avltree_t tAVLtree_insert(avltree_t T, char node)
{
	if (!T) {
		if ((T = (avltree_t)malloc(1))) {
			T->node = node;
			T->hight = 0;
			T->left = NULL;
			T->right =NULL;
		}
	} else {
		if (T->node > node) {
			T->left = tAVLtree_insert(T->left, node);
			if ((tAVLtree_hight(T->left) - tAVLtree_hight(T->right)) == 2) {
				if (T->left->node > node) {
					T = tAVLtree_singleRotateWithLeft(T);
				} else {
					T = tAVLtree_doubleRotateWithLeft(T);
				}
			}
		} else {
			T->right = tAVLtree_insert(T->right, node);
			if ((tAVLtree_hight(T->right) - tAVLtree_hight(T->left)) == 2) {
				if (T->right->node < node) {
					T = tAVLtree_singleRotateWithRight(T);
				} else {
					T = tAVLtree_doubleRotateWithRight(T);
				}
			}
		}
	}
	T->hight = tAVLtree_hight_calculate(T->left, T->right) + 1;
	return T; 
}

/**
 * @fn tAVLtree_search
 * @brief search node in AVL tree
 * @param T avl tree structure
 * @param node the searched node
 * @return position_t the address of the searched node
 */
position_t tAVLtree_search(avltree_t T, char node)
{
	if (!T)
		return NULL;
	else if (T->node == node)
		return T;
	else
		return tAVLtree_search((T->node > node) ?
							   T->left : T->right,
							   node);
}

/**
 * @fn tAVLtree_delete
 * @brief delete node in avl tree
 * @param T 
 * @param node 
 * @return avltree_t 
 */
avltree_t tAVLtree_delete(avltree_t T, char node)
{
	position_t cell;

	if (!T) {
		return NULL;
	} else if (T->node > node){
		T->left = tAVLtree_delete(T->left, node);
	} else if (T->node < node){
		T->right = tAVLtree_delete(T->right, node);
	} else if (T->left && T->right){
		cell = tAVLtree_findMin(T->right);
		T->node = cell->node;
		T->right = tAVLtree_delete(T->right, node);
	} else {
		cell = T;
		if (!T->left)
			T = T->right;
		else if(!T->right)
			T = T->left;

		free(cell);
	}
	return T;
}

/**
 * @fn tAVLtree_eraseAll
 * @brief erase avl tree struture
 * @param T avl tree structure
 * @return avltree_t NULL
 */
avltree_t tAVLtree_eraseAll(avltree_t T)
{
	if (T) {
		tAVLtree_eraseAll(T->left);
		tAVLtree_eraseAll(T->right);
		free(T);
	}
	return NULL;
}
