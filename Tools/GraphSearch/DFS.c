#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NODE_COUNT 10

typedef struct node_s {
    int val;
    struct node_s *next;
} Node;

Node* createNode(int val) {
    Node *new = (Node*)malloc(sizeof(Node));
    new->val = val;
    new->next = NULL;
    return new;
}

void push(Node **stack, int val) {
    Node *new = createNode(val);
    new->next = *stack;
    *stack = new;
}

void pop(Node **stack) {
    Node *tmp = *stack;
    *stack = (*stack)->next;
    free(tmp);
}

void addEdge(Node *graph[], int A, int B) {
    push(&graph[A], B);
    push(&graph[B], A);
}

// DFS
typedef struct graph_s{
    Node **map;
    bool *visited;

    // short path
    int *shortestPath;
    int shortestLength;
} Graph;

Graph* createGraph(int nodeCount) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));

    graph->map = (Node**)malloc(nodeCount * sizeof(Node*));
    graph->visited = (bool*)malloc(nodeCount * sizeof(bool));
    graph->shortestPath = (int*)malloc(nodeCount * sizeof(int));
    graph->shortestLength = nodeCount;

    for (int i = 0; i < nodeCount; i++) {
        graph->map[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void DFS(Graph *graph, Node *path, int now, int end, int need_visit, int depth) {
    if (graph->visited[now])
        return;
    printf("visited: %d\n", now);
    if (now == end) {
        printf("found path: %d->", end);
        for (Node *current = path; current != NULL; current = current->next) {
            printf("%d->", current->val);
        }
        printf("NULL\n");

        // 如果(有檢測需求 && 且沒有經過)
        if (need_visit != -1 && !graph->visited[need_visit])
            return;
        if (depth >= graph->shortestLength)
            return;

        // update shortest data
        graph->shortestLength = depth;

        int index = 0;
        for (Node *current = path; current != NULL; current = current->next) {
            graph->shortestPath[index] = current->val;
            index++;
        }
    }

    graph->visited[now] = true;
    push(&path, now);

    Node *neighbor = graph->map[now];
    while (neighbor != NULL)
    {
        DFS(graph, path, neighbor->val, end, need_visit, depth + 1);
        neighbor = neighbor->next;
    }
    
    graph->visited[now] = false;
    pop(&path);
}

int main(void) {
    int start = 0, end = 3, need_visited = -1;
    
    Graph *graph = createGraph(NODE_COUNT);
    Node *stack = NULL;

    addEdge(graph->map, 0, 1);
    addEdge(graph->map, 0, 2);
    addEdge(graph->map, 1, 2);
    addEdge(graph->map, 2, 3);
    addEdge(graph->map, 2, 4);

    DFS(graph, stack, start, end, need_visited, 0);

    if (graph->shortestLength == NODE_COUNT)
        printf("Not found path\n");
    else {
        printf("Shortest Path: ");
        for (int i = graph->shortestLength - 1; i >= 0; i--) {
            printf("%d->", graph->shortestPath[i]);
        }
        printf("%d\n", end);
    }
}