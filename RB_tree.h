#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_LENGTH 200
#define RED 1
#define BLACK 0
#define ERR 1
#define SUC 0
#define ID 5

typedef struct node {
	float *key;
	int *number_of_proc;
	short *color;
	char *name;
	struct node *left;
	struct node *right;
	struct node *parent;
} node;

int ex_free(int flag, char* name, float* key, node* root);

node* create_node(void);
int mc_ch(void* ptr);
int add_node(node* n, float* key, char* name);
int init_node(node* n, float* key, char* name);
void print_tree(node* root);
int free_tree(node* root);
void write_nodes(node* root);
int free_node(node *n);

node* get_Grand(node* N);
node* get_Uncle(node* N);
int right_rotate(node* N);
int left_rotate(node* N);
void print_tree(node* root);
int balance(node* z);
