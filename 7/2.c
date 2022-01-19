#include <stdio.h>
#include <stdlib.h>



typedef struct Node {
	int value;
	int count;
	struct Node* next;
	struct Node* prev;
} Node;	

/*
Node* initList() {
    Node* head = malloc(sizeof(Node));
    head->value = 0;
    head->count = 0;
    head->next = NULL;
    head->prev = NULL;
    return head;
}*/

Node* initList(int value, int count) {
    Node* head = malloc(sizeof(Node));
    head->value = value;
    head->count = count;
    head->next = NULL;
    head->prev = NULL;
    return head;
}

Node* addNodeToHead(Node* head, int value, int count) {
	if (head == NULL) {
		return initList(value, count);
	}
	Node* new_head = initList(value, count);
    new_head->next = head;
    head->prev = new_head;
    return new_head;
}

Node* eraseNode(Node* node) { // not head
	Node* next_node = node->next;

	if (node->prev) {
		node->prev->next = next_node;
	}
	if (next_node) {
		next_node->prev = node->prev;
	}

	free(node);
	return next_node;
}

void freeList(Node* node) {
    if (!node) {
        return;
    }

    if (node->next) {
        freeList(node->next);
    }

    free(node);
}

Node* findNode(Node* node, int value) {
	if (!node) {
		return NULL;
	}

	if (node->value == value) {
		return node;
	} else {
		return findNode(node->next, value);
	}
}

Node* readList(FILE* in) {
    int value = 0, count = 0;
    Node* head;
    Node* node;

    if (fscanf(in, "%d", &value) > 0) {
        head = initList(value, 1);
    } else {
        return NULL;
    }

    while (fscanf(in, "%d", &value) > 0) {
    	if ((node = findNode(head, value)) != NULL) {
    		count = node->count + 1;

    		if (node == head) {
    			head = eraseNode(node);
    		} else {
    			node = eraseNode(node);
    		}
    		
    		head = addNodeToHead(head, value, count);
    	} else {
        	head = addNodeToHead(head, value, 1);
    	}
    }

    return head;
}

void printReverseList(FILE* out, Node* node) {
    if (!node) {
        return;
    }
    if (node->next) {
        printReverseList(out, node->next);
    }

    printf("%d %d\n", node->value, node->count);
}

int main() {
	FILE* in = stdin; //fopen("input.txt", "r");
	FILE* out = stdout;
    Node* head = readList(in);
    printReverseList(out, head);
    freeList(head);
}
