#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
	void* dagnode;
	int ref_count;
} Node;

void freeList(Node* node) {
    if (!node) {
        return;
    }

    if (node->next) {
        freeList(node->next);
    }

    free(node->token);
    free(node);
}

Node* addNodeToList(Node* head, void* dagnode) {
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) {
		return NULL;
	}

	new_node->dagnode = dagnode;
	new_node->next = head;
	return new_node;
}

Node* findNodeInList(Node* node, void* dagnode) {
	if (!node) {
		return NULL;
	}
	
	if (node->dagnode == dagnode) {
		return node;
	}

	Node* left_ans = findNodeInList(node->left, dagnode);
	if (left_ans) {
		return left_ans;
	}
	return findNodeInList(node->right, dagnode);
}

Node* makeNodeList(struct dag_node* root) {
	Node* 
}

void free_dag(struct dag_node* root) {
	Node* list_head = makeNodeList(root);
}