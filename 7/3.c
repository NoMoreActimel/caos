#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node* left;
	struct Node* right;
} Node;

Node* initNode(int value) {
	Node* node = malloc(sizeof(Node));
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void freeTree(Node* node) {
	if (!node) {
		return;
	}

	freeTree(node->left);
	freeTree(node->right);
	free(node);
}

Node* addNodeToTree(Node* node, int value) {
	if (node == NULL) {
		return initNode(value);
	}

	if (node->value > value) {
		if (node->left) {
			return addNodeToTree(node->left, value);
		} else {
			node->left = initNode(value);
			return node->left;
		}
	} else if (node->value < value) {
		if (node->right) {
			return addNodeToTree(node->right, value);
		} else {
			node->right = initNode(value);
			return node->right;
		}
	}
	return NULL;
}

void printTreePart(FILE* out, Node* node) {
	if (!node) {
		return;
	}

	printTreePart(out, node->right);
	fprintf(out, "%d ", node->value);
	printTreePart(out, node->left);
}
void printTree(FILE* out, Node* root) {
	printTreePart(out, root);
	fprintf(out, "0 ");
}

int main() {
	FILE* in = stdin; // fopen("input.txt", "r");
	FILE* out = stdout;

	int value = 1;
	Node* root = NULL;

	while (fscanf(in, "%d", &value) > 0) {
		if (value == 0) {
			printTree(out, root);
			freeTree(root);
			root = NULL;
		} else {
			if (!root) {
				root = addNodeToTree(root, value);
			} else {
				addNodeToTree(root, value);
			}
		}
	}

	if (value && root) {
		printTree(out, root);
		freeTree(root);
	}

	fprintf(out, "\n");
}