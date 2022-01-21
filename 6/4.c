#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node_t;

Node_t* initList() {
    Node_t* head = malloc(sizeof(Node_t));
    if (head == NULL) {
        return NULL;
    }
    head->value = 0;
    head->next = NULL;
    return head;
}

Node_t* addNodeToList(Node_t* node, int value) {
    node->next = malloc(sizeof(Node_t));
    if (node->next == NULL) {
        return NULL;
    }
    node->next->value = value;
    node->next->next = NULL;
    return node->next;
}

void freeList(Node_t* node) {
    if (!node) {
        return;
    }

    if (node->next) {
        freeList(node->next);
    }

    free(node);
}

Node_t* readList() {
    int value = 0;
    Node_t* head;
    Node_t* node;

    if (scanf("%d", &value) > 0) {
        head = initList();
        if (head == NULL) {
            return NULL;
        }
        node = head;
        node->value = value;
    } else {
        return NULL;
    }

    while (scanf("%d", &value) > 0) {
        node = addNodeToList(node, value);
        if (node == NULL) {
            return NULL;
        }
    }

    return head;
}

void printReverseList(Node_t* node) {
    if (!node) {
        return;
    }
    if (node->next) {
        printReverseList(node->next);
    }

    printf("%d\n", node->value);
}

int main() {
    Node_t* head = readList();
    printReverseList(head);
    freeList(head);
}