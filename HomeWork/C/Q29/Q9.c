#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node_s {
    int data;
    struct node_s* next;
} Node;

typedef struct stack_s
{
    Node *top;
} Stack;

void push(Stack* stack) {
    Node* new = (Node*)malloc(sizeof(Node));

    scanf("%d", &new->data);
    new->next = stack->top;

    stack->top = new;
}
void pop(Stack* stack) {
    Node* new = stack->top->next;
    free(stack->top);

    stack->top = new;
}
void empty(Stack* stack) {
    Node* current = stack->top, * tmp = NULL;
    while (current != NULL)
    {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    stack->top = NULL;
}
void printStack(Stack* stack) {
    Node* current = stack->top;
    while (current != NULL)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main(void) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;

    // solve
    int commandCount; scanf("%d", &commandCount);
    char command[10] = "test";

    for (int i = 0; i < commandCount; i++) {
        scanf("%s", command);

        if (strcmp("push", command) == 0) {
            push(stack);
        }
        // check empty
        else if (stack->top == NULL) {
            printf("Stack is empty\n");
            continue;
        }
        else if (strcmp("top", command) == 0) {
            printf("%d\n", stack->top->data);
        }
        else if (strcmp("pop", command) == 0) {
            printf("%d\n", stack->top->data);
            pop(stack);
        }
        else if (strcmp("empty", command) == 0) {
            empty(stack);
        }
        else if (strcmp("print", command) == 0) {
            printStack(stack);
        }
    }
}
