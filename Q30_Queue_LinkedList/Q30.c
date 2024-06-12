#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node_s
{
    int data;
    struct node_s *next;
} node_t;
typedef node_t *node_pt;

typedef struct queue_s
{
    node_pt front, back;
} Queue;


bool isEmpty(Queue *queue) {
    if (queue->front == NULL)
        return true;
    return false;
}

void enqueue(Queue *queue) {
    node_pt new = (node_pt)malloc(sizeof(node_pt));
    scanf("%d", &new->data);
    new->next = NULL;

    if (queue->front == NULL)
        queue->front = new;
    else
        queue->back->next = new;

    queue->back = new;
}

node_pt dequeue(Queue *queue) {
    if (queue->front == NULL)
        return NULL;

    node_pt tmp = queue->front;
    queue->front = tmp->next;

    return tmp;
}

void clear(Queue *queue) {
    node_pt current = queue->front, tmp;

    while (current != NULL)
    {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    queue->front = NULL;
    queue->back = NULL;
}

void printQueue(Queue *queue) {
    node_pt current = queue->front;

    while (current != NULL)
    {
        // printf("%d->", current->data);
        printf("%d\n", current->data);
        current = current->next;
    }
    // printf("NULL\n");
}

int main() {
    // init queue
    Queue queue_new = {
        .back = NULL,
        .front = NULL,
    };
    Queue *queue = &queue_new;

    // solve
    int N; scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        char command[8]; scanf("%s", command);

        if (strcmp(command, "push") == 0) {
            enqueue(queue);
        }
        // empty check
        else if (isEmpty(queue)) {
            printf("Queue is empty\n");
            continue;
        }
        // when not empty
        else if (strcmp(command, "pop") == 0) {
            node_pt current = dequeue(queue);
            printf("%d\n", current->data);
            free(current);
        }
        else if (strcmp(command, "front") == 0)
            printf("%d\n", queue->front->data);
        else if (strcmp(command, "empty") == 0)
            clear(queue);
        else if (strcmp(command, "print") == 0)
            printQueue(queue);
    }
    return 0;
}