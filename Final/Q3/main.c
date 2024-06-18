#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node_s{
    int val;
    struct node_s *next;
} Node;

typedef struct list_s {
    struct node_s *head;
} List;

// my tools
Node* createNode(int val) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->next = NULL;
    new->val = val;
    return new;
}
void push(List* list, int val) {
    Node* new = createNode(val);
    new->next = list->head;
    list->head = new;
}
Node* getNodeOfVal(List* list, int val) {
    for (Node* current = list->head; current; current = current->next) {
        if (current->val == val)
            return current;
    }
    return NULL;
}

// case func
void addBack(List* list, int val) {
    Node* new = createNode(val);

    if (list->head == NULL)
        list->head = new;
    else {
        Node* current = list->head;
        while (current->next != NULL) 
            current = current->next;
        current->next = new;
    }
}
void delFront(List* list) {
    if (list->head == NULL)
        return;
    list->head = list->head->next;
}
void delBack(List* list) {
    if (list->head == NULL)
        return;
    if (list->head->next == NULL) {
        list->head = NULL;
        return;
    }
    for (Node* prev = list->head; prev->next; prev = prev->next) {
        if (prev->next->next == NULL) {
            prev->next = NULL;
            return;
        }
    }
}
void delXNode(List* list, int val) {
    for (Node* prev = list->head; prev->next; prev = prev->next) {
        if (prev->next->val == val) {
            prev->next = prev->next->next;
            break;
        }
    }
}
void insert(List* list, int val, int newVal) {
    Node* current = list->head;
    for (; current; current = current->next) {
        if (current->val == val)
            break;
    }
    if (current == NULL)
        return;
    
    Node* new = createNode(newVal);
    if (current->next != NULL)
        new->next = current->next;
    current->next = new;
}
void reverse(List* list) {
    Node* current = list->head;
    list->head = NULL;
    for (; current; current = current->next) {
        push(list, current->val);
    }
}
void convert(List* list, int x, int y) {
    Node* nodeX = getNodeOfVal(list, x);
    Node* nodeY = getNodeOfVal(list, y);
    
    if (nodeX == NULL || nodeY == NULL)
        return;

    int tmp = nodeX->val;
    nodeX->val = nodeY->val;
    nodeY->val = tmp;
}

void printList(List* list) {
    printf("print: ");
    for (Node* current = list->head; current; current = current->next) {
        printf("%d ", current->val);
    }
    printf("\n");
}

int main(void) {
    // init list
    char input[100]; scanf("%[^\n]", input);
    List list = {.head = NULL};

    char* token = strtok(input, " ");
    while (token != NULL)
    {
        addBack(&list, atoi(token));
        token = strtok(NULL, " ");
    }
    printList(&list);
    
    // solve
    int numCommand; scanf("%d", &numCommand);
    for (int i = 0; i < numCommand; i++){
        int command; scanf("%d", &command);

        switch (command)
        {
        case 1:
        {
            int x; scanf("%d", &x);
            addBack(&list, x);
            break;
        }
        case 2: { delFront(&list); break; }
        case 3: { delBack(&list); break; }
        case 4: 
        {
            int x; scanf("%d", &x);
            delXNode(&list, x);
            break;
        }
        case 5: 
        {
            int x, y; scanf("%d %d", &x, &y);
            insert(&list, x, y);
            break;
        }
        case 6: { reverse(&list); break; }
        case 7: 
        {
            int x, y; scanf("%d %d", &x, &y);
            convert(&list, x, y);
            break;
        }
        }
        printList(&list);
    }

    // printList(&list);
}
