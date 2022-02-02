#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct dag_node {
    struct dag_node *left, *right;
    void *data;
} dag_node;

typedef struct node {
	struct dag_node *dn;
	struct node* next;
} node;

bool visited;
node* list_end;

void addNode(struct node* list_end, struct dag_node* dn) {
	list_end->next = malloc(sizeof(node));
	if (!list_end->next) {
		fprintf(stderr, "memory allocation problem\n");
		return;
	}

	list_end->next->dn = dn;
	list_end->next->next = NULL;
}

void dfs(struct dag_node* dn) {
	if (!dn || dn->data == &visited) {
		return;
	}

	dn->data = &visited;
	addNode(list_end, dn);
	list_end = list_end->next;
	dfs(dn->left);
	dfs(dn->right);
}

void free_daglist(struct node* list_node) {
	if (!list_node) {
		return;
	}

	free_daglist(list_node->next);
	free(list_node->dn);
	free(list_node);
}

void free_dag(struct dag_node* root) {
	if (!root) {
		return;
	}

	list_end = malloc(sizeof(node));
	list_end->dn = NULL;
	list_end->next = NULL;
	node* list_head = list_end;

	dfs(root);
	free_daglist(list_head->next);

	free(list_head);
}