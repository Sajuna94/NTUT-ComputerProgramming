#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NODE_COUNT 100

typedef struct node_s {
    int val;
    struct node_s *next;
} Node;

typedef struct dfs_s {
    Node* map[NODE_COUNT];
    bool visited[NODE_COUNT];

    int start, end;

    bool NEED_VISITED;
    int need_visit_val;

    int shortestLength;
    int shortestPath[NODE_COUNT];
} Graph;

Node* newNode(int val) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->val = val;
    new->next = NULL;
    return new;
}

void push(Node** node, int val) {
    Node* new = newNode(val);
    new->next = *node;
    *node = new;
}

void pop(Node** node) {
    Node* tmp = *node;
    *node = (*node)->next;
    free(tmp);
}

// Graph
void addEdge(Graph* graph, int A, int B) {
    push(&graph->map[A], B);
    push(&graph->map[B], A);
}

int* splitToIntArray(char* string, int *length) {
    int* result = NULL;
    char* token = strtok(string, " ");

    while (token != NULL)
    {
        result = realloc(result, ((*length) + 1) * sizeof(int));
        result[(*length)++] = atoi(token);
        token = strtok(NULL, " ");
    }
    return result;
}

void DFS(Graph* graph, Node* path, int now, int depth) {
    if (graph->visited[now])
        return;
    
    if (now == graph->end) {
        if (graph->NEED_VISITED && !graph->visited[graph->need_visit_val])
            return;
        if (depth >= graph->shortestLength)
            return;
        
        // package DFS
        graph->shortestLength = depth;
        int index = 0;
        for (Node* current = path; current != NULL; current = current->next) {
            graph->shortestPath[index++] = current->val;
        }
        return;
    }

    push(&path, now);
    graph->visited[now] = true;

    Node* neighbor = graph->map[now];
    while (neighbor != NULL)
    {
        DFS(graph, path, neighbor->val, depth + 1);
        neighbor = neighbor->next;
    }
    
    pop(&path);
    graph->visited[now] = false;
}

int main() {
    char input[100]; 
    scanf("%[^\n]", input);

    int input_length = 0; 
    int* input_data = splitToIntArray(input, &input_length);

    // init graph
    Graph graph = {
        .start = input_data[1],
        .end = input_data[2],
        .shortestLength = NODE_COUNT,
    };
    for (int i = 0; i < NODE_COUNT; i++) {
        graph.map[i] = NULL;
        graph.visited[i] = false;
        graph.shortestPath[i] = 0;
    }
    if (input_length == 4) {
        graph.NEED_VISITED = true;
        graph.need_visit_val = input_data[3];
    }

    // add edge
    int A = 0, B = 0;
    for (int i = 0; i < input_data[0]; i++) {
        scanf("%d %d", &A, &B);
        addEdge(&graph, A, B);
    }

    // DFS
    Node* path = NULL;
    DFS(&graph, path, graph.start, 0);

    // print result
    if (graph.shortestLength == NODE_COUNT)
        printf("NO\n");
    else {
        printf("%d\n", graph.shortestLength);
        for (int i = graph.shortestLength - 1; i >= 0; i--) {
            printf("%d ", graph.shortestPath[i]);
        }
        printf("%d\n", graph.end);
    }
}
