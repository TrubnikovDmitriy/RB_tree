#include "RB_tree.h"

void _free_tree(node* n);
void _free_node(node* n);
int _add_node(node *n, float *key, char *name);

int mc_ch(void *ptr) {
	if (ptr == NULL) {
		printf ("Something wrong...\n");
		return ERR;
	}
	return SUC;
}


node *create_node(void) {

	node *n = (node *)malloc(sizeof(node));
	if (mc_ch(n))
		return NULL;

	n->key = NULL;
	n->name = NULL;
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;

	n->number_of_proc = NULL;
	n->number_of_proc = (int *)malloc(sizeof(int));
	if (mc_ch(n->number_of_proc))
		return NULL;
	*(n->number_of_proc) = 0;

	n->color = NULL;
	n->color = (short *)malloc(sizeof(short));
	if (mc_ch(n->color))
		return NULL;
	*(n->color) = RED;

	return n;
}

int init_node(node *n, float *key, char *name) {
	
		n->key = (float *)malloc(sizeof(float));
		if (mc_ch(n->key))
			return ERR;
		*(n->key) = *key;
		
		n->name = (char *)malloc(MAX_LENGTH*sizeof(char));
		if (mc_ch(n->name))
			return ERR;
		strcpy(n->name, name);
		
		++(*n->number_of_proc);

		return SUC;
}

int add_node(node *n, float *key, char *name) {

	if (mc_ch(key) || mc_ch(n) || mc_ch(name))
		return ERR;
	return (_add_node(n, key, name));
}

int _add_node(node *n, float *key, char *name) {

	if (n->key == NULL) {
		if (init_node(n, key, name))
			return ERR;
		return balance (n);
	}


	if (*(n->key) == *key) {
		++(*n->number_of_proc);
		return SUC;
	}

	if (*(n->key) > *key) {
		if (n->left == NULL) {
			n->left = create_node();
			n->left->parent = n;
		}
		if (_add_node(n->left, key, name))
			return ERR;
		return SUC;
	}
	
	if (*(n->key) < *key) {
		if (n->right == NULL) {
			n->right = create_node();
			n->right->parent = n;
		}
		if (_add_node(n->right, key, name))
			return ERR;
		return SUC;
	}

	return ERR;
}

int free_tree (node* root) {
	if (mc_ch(root))
		return ERR;
	_free_tree(root);
	return SUC;
}

void _free_tree(node *n) {

	if (n->right != NULL)
		_free_tree(n->right);

	if (n->left != NULL)
		_free_tree(n->left);

	_free_node(n);
}

int free_node(node *n) {
	if (mc_ch(n))
		return ERR;
	_free_node(n);
	return SUC;
}

void _free_node(node *n) {

	free(n->color);
	free(n->key);
	free(n->name);
	free(n->number_of_proc);
	free(n);
}

void write_nodes(node* root) {

	if (mc_ch(root)) {
		printf("Empty root!\n");
		return;
	}
        
	if (root->right != NULL)
                write_nodes(root->right);
        printf ("Mem: %.2f,\tNumber: %d,\tName: %s", *(root->key), *root->number_of_proc, root->name);
        if (root->left != NULL)
                write_nodes(root->left);
}
