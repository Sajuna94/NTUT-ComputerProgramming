// When the node's value is between INT_MIN and INT_MAX,
// it's better to use a different array instead of 'visited'.
// This is because if the starting node's value equals the default value (indicating unvisited),
// it would lead the path tracing function into an infinite loop.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void addEdge(Node *nodeList[], int A, int B) {
    Node *edgeA = createNode(A), *edgeB = createNode(B);

    edgeA->next = nodeList[B]; // A -> [B]
    nodeList[B] = edgeA; // A = [B]
    edgeB->next = nodeList[A];
    nodeList[A] = edgeB;
}

Node* BFS(Node *graph[], int start, int end) {
    // create queue & visited
    int queue[NODE_COUNT];
    int front = 0, back = 0;

    int visited[NODE_COUNT]; 
    memset(visited, -1, NODE_COUNT * sizeof(int));

    // init data
    queue[back++] = start;
    visited[start] = start;

    // start BFS
    while (front != back)
    {
        // dequeue
        int now = queue[front++];

        if (now == end) {
            int tmp = now;
            Node *root = createNode(tmp);
            // package path
            while (tmp != start)
            {
                tmp = visited[tmp];

                Node *new = createNode(tmp);
                new->next = root;
                root = new;
            }
            return root;
        }

        // neighbor
        for (Node *neighbor = graph[now]; neighbor != NULL; neighbor = neighbor->next) {
            if (visited[neighbor->val] != -1)
                continue;
            // set visit
            visited[neighbor->val] = now;
            // enqueue
            queue[back++] = neighbor->val;
        }
    }
    // did not found path
    return NULL;
}

int main(void) {
    Node *graph[NODE_COUNT];
    for (int i = 0; i < NODE_COUNT; i++) {
        graph[i] = NULL;
    }
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 3, 2);
    addEdge(graph, 3, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 4, 5);
    addEdge(graph, 3, 5);

    Node *path = BFS(graph, 1, 5);

    if (path == NULL)
        printf("Path did not found!\n");
    else {
        Node *current = path;
        while (current != NULL)
        {
            printf("%d->", current->val);
            current = current->next;
        }
        printf("\n");
    }
}
