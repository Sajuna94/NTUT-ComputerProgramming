#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NODE_COUNT 100

typedef struct node_s {
    int val, time;
    struct node_s *next;

    int numNext;
    int nextList[NODE_COUNT];
} Node;

Node* createNode(int val, int time) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->next = NULL;
    new->val = val;
    new->time = time;
    return new;
}

void push(Node** node, Node* new) {
    if (*node == NULL) {
        *node = new;
    } else {
        new->next = *node;
        *node = new;
    }
}
void pop(Node** node) {
    *node = (*node)->next;
}

typedef struct graph_s {
    Node *map[NODE_COUNT];

    int pathCount;
    Node **paths;
} Graph;

void DFS(Graph* graph, Node* path, int now, int time)
{
    Node* current = graph->map[now];
    // push path
    push(&path, createNode(now, time));

    // find end
    if (current->numNext == 0) {
        graph->paths = realloc(graph->paths, (graph->pathCount + 1) * sizeof(Node*));
        graph->paths[graph->pathCount] = path;
        graph->pathCount++;
    }

    // go next
    for (int i = 0; i < current->numNext; i++) {
        DFS(graph, path, current->nextList[i], time + graph->map[current->nextList[i]]->time);
    }
    // pop path
    pop(&path);
}

int main(void) {
    int M; scanf("%d", &M);
    int numCommand; scanf("%d", &numCommand);

    Graph graph = {.paths = NULL, .pathCount = 0};
    for (int i = 0; i < NODE_COUNT; i++)
        graph.map[i] = NULL;

    // process input
    for (int i = 0; i < numCommand; i++) {
        int hour, numNext; scanf("%d %d", &hour, &numNext); 

        graph.map[i] = createNode(i, hour);
        graph.map[i]->numNext = numNext;

        for (int t = 0; t < numNext; t++) {
            int next; scanf("%d", &next);

            graph.map[i]->nextList[t] = (next - 1);
        }
    }

    // get start
    bool visits[numCommand];
    for (int i = 0; i < numCommand; i++) 
        visits[i] = false;

    for (int i = 0; i < numCommand; i++) {
        for (int t = 0; t < graph.map[i]->numNext; t++) {
            visits[graph.map[i]->nextList[t]] = true;
        }
    }

    // start dfs
    for (int i = 0; i < numCommand; i++) {
        Node* path = NULL;
        if (!visits[i]) {
            DFS(&graph, path, i, graph.map[i]->time);
        }
    }

    // print result
    for (int i = 0; i < graph.pathCount; i++) {
        printf("find path[%d]:", graph.paths[i]->time);
        for (Node* cur = graph.paths[i]; cur; cur = cur->next) {
            printf("%d ", cur->val + 1);
        }
        printf("\n");
    }
}
