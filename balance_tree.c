#include "RB_tree.h"

#define COLOR_RED "\x1b[31m"
#define COLOR_BLACK "\x1b[37m"
#define RESET "\x1b[0m"

int case1(node* n);
int case2(node* n);
int case3(node* n);
int case4(node* n);
int case5(node* n);
void _print_tree(node* pNode, int level);


node* get_Grand(node* N) {

	if (mc_ch(N))
		return NULL;
	if (N->parent == NULL)
		return NULL;
	return N->parent->parent;	
}

node* get_Uncle(node* N) {

	node* G = get_Grand(N);
	if (G == NULL)
		return NULL;

	if ((G->left == NULL) || (G->right == NULL))
		return NULL;

	if (G->left == N->parent)
		return G->right;
	return G->left;
}

int right_rotate(node* ptr) {
	
	if (mc_ch(ptr)) 
		return ERR;
	if (mc_ch(ptr->left))
		return ERR;

	node temp = *ptr;
	*ptr = *ptr->left;
	*temp.left = temp;

	if (ptr->left != NULL)
		ptr->left->parent = ptr;

	temp.left->left = ptr->right;

	ptr->right = temp.left;
	ptr->parent = temp.left->parent;
	temp.left->parent = ptr;

	if (temp.right != NULL)
		temp.left->right->parent = temp.left;

	return SUC;	
}

int left_rotate(node* ptr) {
	
	if (mc_ch(ptr)) 
		return ERR;
	if (mc_ch(ptr->right))
		return ERR;

	node temp = *ptr;
	*ptr = *ptr->right;
	*temp.right = temp;

	if (ptr->right != NULL)
		ptr->right->parent = ptr;

	temp.right->right = ptr->left;

	ptr->left = temp.right;
	ptr->parent = temp.right->parent;
	temp.right->parent = ptr;

	if (temp.left != NULL)
		temp.right->left->parent = temp.right;

	return SUC;	
}

void print_tree(node* root) {
	
	if(mc_ch(root)) {
		printf("Empty root\n");
		return;
	}

	printf("\n\n");
	_print_tree(root, 0);
	printf(RESET "\n\n");
}


void _print_tree(node *pNode, int n) {


	if (pNode->right)
		_print_tree(pNode->right, n+1);

	for (int i = 0; i < n; i++)
		printf("\t");

	if (*pNode->color == RED)
		printf(COLOR_RED "%s\n", pNode->name);
	else
		printf(COLOR_BLACK "%s\n", pNode->name);

	if (pNode->left)
		 _print_tree(pNode->left, n+1);
}

int balance(node* n) {
	if (mc_ch(n))
		return ERR;
	else
		return case1(n);
}

int case1(node *n) {
	if (n->parent == NULL) {
		*n->color = BLACK;
		return SUC;
	}
	else
		return case2(n);
}

int case2(node *n) {
	if (*n->parent->color == BLACK)
		return SUC;
	else 
		return case3(n);
}

int case3(node *n) {
		
	node* U = get_Uncle(n);
	node* G = get_Grand(n);
	node* P = n->parent;
	
	if ((U != NULL) && (*U->color == RED) && (*P->color == RED)) {
		*U->color = BLACK;
		*G->color = RED;
		*P->color = BLACK;
		
		return case1(G);
	}
	
	return case4(n);
}

int case4(node *n) {

	node* U = get_Uncle(n);
	node* G = get_Grand(n);
	node* P = n->parent;
 
	if ((U == NULL || *U->color == BLACK) && (*P->color == RED)) {
		if ((P->right == n) && (G->left == P)) {
			if (left_rotate(G->left))
				return ERR;
			n = G->left->left;
		}
		if ((P->left == n) && (G->right == P)) {
			if (right_rotate(G->right))
				return ERR;
			n = G->right->right;
		}
	}
	return case5(n);
}
int case5(node *n) {

	node* U = get_Uncle(n);
	node* G = get_Grand(n);
	node* P = n->parent;

	if ((U == NULL || *U->color == BLACK) && (*P->color == RED)) {

		*G->color = RED;
		*P->color = BLACK;

		if ((P->left == n) && (G->left == P))
			if (right_rotate(n->parent->parent))

				return ERR;
		if ((P->right == n) && (G->right == P))
			if (left_rotate(n->parent->parent))
				return ERR;
	}
	return SUC;
}
