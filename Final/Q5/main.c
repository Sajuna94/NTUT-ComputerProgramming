// time 38:58

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node_s {
    char val;
    struct node_s *left, *right;
} Node;

Node* DFS(char* traTree, int* traLeft, int* traRight, char* inTree, int inLeft, int inRight, bool isPre) {
    if (inLeft > inRight)
        return NULL;

    char current = traTree[(isPre ? *traLeft : *traRight)];

    Node* root = (Node*)malloc(sizeof(Node));
    root->val = current;

    int split = strchr(inTree, current) - inTree;

    if (isPre) {
        (*traLeft)++;
        root->left = DFS(traTree, traLeft, traRight, inTree, inLeft, split - 1, isPre);
        root->right = DFS(traTree, traLeft, traRight, inTree, split + 1, inRight, isPre);
    } else {
        (*traRight)--;
        root->right = DFS(traTree, traLeft, traRight, inTree, split + 1, inRight, isPre);
        root->left = DFS(traTree, traLeft, traRight, inTree, inLeft, split - 1, isPre);
    }
    return root;
}

int main(void) {
    int numNode; scanf("%d", &numNode);

    char treeTypeA, treeTypeB;
    char treeStrA[numNode], treeStrB[numNode];
    scanf(" %c", &treeTypeA);
    scanf(" %[^\n]", treeStrA);
    scanf(" %c", &treeTypeB);
    scanf(" %[^\n]", treeStrB);

    int left = 0, right = numNode - 1;
    Node* root = NULL;

    if (treeTypeA == 'P' && treeTypeB == 'I') {
        root = DFS(treeStrA, &left, &right, treeStrB, left, right, true);
    } 
    else if (treeTypeA == 'I' && treeTypeB == 'P') {
        root = DFS(treeStrB, &left, &right, treeStrA, left, right, true);
    } 
    else if (treeTypeA == 'I' && treeTypeB == 'O') {
        root = DFS(treeStrB, &left, &right, treeStrA, left, right, false);
    }
    else if (treeTypeA == 'O' && treeTypeB == 'I') {
        root = DFS(treeStrA, &left, &right, treeStrB, left, right, false);
    } 

    // print
    Node* queue[numNode];
    int front = 0, back = 0;

    queue[back++] = root;
    
    while (front < back)
    {
        Node* current = queue[front++];
        printf("%c", current->val);

        if (current->left != NULL) queue[back++] = current->left;
        if (current->right != NULL) queue[back++] = current->right;
    }
}
