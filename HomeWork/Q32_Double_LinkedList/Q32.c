#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node_s {
    int val;
    struct node_s *prev, *next;
} Node;

typedef struct list_s {
    int length;
    struct node_s *head;
} List;

bool isEmpty(List *list) {
    if (list->head == NULL) {
        printf("Double link list is empty\n");
        return true;
    }
    return false;
}

void printList(List *list) {
    if (isEmpty(list))
        return;

    Node *current = list->head;
    while (current != NULL)
    {
        printf("%d\n", current->val);
        current = current->next;
    }
}

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void addFront(List *list, int val) {
    Node* new = createNode(val);

    new->next = list->head;
    if (list->head != NULL) list->head->prev = new;
    list->head = new;

    list->length++;
}

void addBack(List *list, int val) {
    Node* new = createNode(val);

    if (list->head == NULL) {
        list->head = new;
        return;
    }
    // find back
    Node *back = list->head;
    while (back->next != NULL) back = back->next;
    
    new->prev = back;
    back->next = new;

    list->length++;
}

void removeNode(List *list, int n) {
    if (list->length < n) {
        printf("Invalid command\n");
        return;
    }
    // find N node
    Node *current = list->head;
    for (int i = 1; i < n; i++) current = current->next;
    
    if (n == 1)
        list->head = list->head->next;

    // current?.prev <-> current?.next
    if (current->prev != NULL) current->prev->next = current->next;
    if (current->next != NULL) current->next->prev = current->prev;

    free(current);
    list->length--;
}

void insert(List *list, int n, int val) {
    if (list->length < n) {
        printf("Invalid command\n");
        return;
    }
    // find N node
    Node *current = list->head;
    for (int i = 1; i < n; i++) current = current->next;

    Node* new = createNode(val);
    // current <- n <- current.next
    new->prev = current;
    new->next = current->next;
    // current -> new, new <- ?
    current->next = new;
    if (new->next != NULL) new->next->prev = new;

    list->length++;
}

void removeFront(List *list) {
    if (isEmpty(list))
        return;
    removeNode(list, 1);
}

void removeBack(List *list) {
    if (isEmpty(list))
        return;
    removeNode(list, list->length);
}

void clearList(List *list) {
    if (isEmpty(list))
        return;
    list->head = NULL;
    list->length = 0;
}

int main(void) {
    List *list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->length = 0;

    int N = 0; scanf("%d", &N);
    char command[40];
    for (int i = 0; i < N; i++) {
        scanf("%s", command);
        int val = 0, index = 0;
        if (!strcmp(command, "addFront")) {
            scanf("%d", &val);
            addFront(list, val);
        }
        else if (!strcmp(command, "addBack")) {
            scanf("%d", &val);
            addBack(list, val);
        }
        else if (!strcmp(command, "removeFront")) {
            removeFront(list);
        }
        else if (!strcmp(command, "removeBack")) {
            removeBack(list);
        }
        else if (!strcmp(command, "empty")) {
            clearList(list);
        }
        else if (!strcmp(command, "insert")) {
            scanf("%d %d", &index, &val);
            insert(list, index, val);
        }
        else if (!strcmp(command, "remove")) {
            scanf("%d", &index);
            removeNode(list, index);
        }
        else if (!strcmp(command, "print")) {
            printList(list);
        }
    }
}
