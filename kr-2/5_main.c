#include <stdio.h>
#include "5.c"

int main() {
	struct dag_node* root = malloc(sizeof(dag_node));
	struct dag_node* A = malloc(sizeof(dag_node));
	struct dag_node* B = malloc(sizeof(dag_node));
	struct dag_node* C = malloc(sizeof(dag_node));
	struct dag_node* D = malloc(sizeof(dag_node));

	root->left = A;
	root->right = NULL;

	A->left = B;
	A->right = C;

	B->left = NULL;
	B->right = D;

	C->left = D;
	C->right = NULL;

	D->left = NULL;
	D->right = NULL;

	free_dag(root);
}