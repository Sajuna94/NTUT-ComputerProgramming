// not a good question
// but is classic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100

typedef struct tree_node_s {
    char val;
    struct tree_node_s *left, *right;
} TreeNode;

TreeNode* newNode(char val) {
    TreeNode* new = (TreeNode*)malloc(sizeof(TreeNode));
    new->val = val;
    new->left = new->right = NULL;
    return new;
}

TreeNode* DFS(char* traversal, char* inOrder, int *travLeft, int *travRight, int inLeft, int inRight, bool isPreOrder) {
    if (inLeft > inRight)
        return NULL;

    TreeNode* root = newNode(traversal[isPreOrder ? *travLeft : *travRight]);
    int splitIndex = strchr(inOrder, root->val) - inOrder;

    if (isPreOrder) {
        (*travLeft)++;
        root->left = DFS(traversal, inOrder, travLeft, travRight, inLeft, splitIndex - 1, isPreOrder);
        root->right = DFS(traversal, inOrder, travLeft, travRight, splitIndex + 1, inRight, isPreOrder);
    } 
    else {
        (*travRight)--;
        root->right = DFS(traversal, inOrder, travLeft, travRight, splitIndex + 1, inRight, isPreOrder);
        root->left = DFS(traversal, inOrder, travLeft, travRight, inLeft, splitIndex - 1, isPreOrder);
    }
    return root;
}

int main(void) {
    char inputA[100] = "ABC", inputB[100] = "BAC";
    char treeA[100], treeB[100];
    char A = 'P', B = 'I';

    scanf(" %c", &A);
    scanf("%s", inputA);
    scanf(" %c", &B);
    scanf("%s", inputB);

    if (A == 'I') {
        strcpy(treeB, inputA);
        strcpy(treeA, inputB);
    }
    else {
        strcpy(treeA, inputA);
        strcpy(treeB, inputB);
    }
    // solve
    int travLeft = 0, travRight = strlen(inputA) - 1;
    TreeNode* root = DFS(treeA, treeB, &travLeft, &travRight, travLeft, travRight, (A == 'P' || B == 'P'));

    // BFS
    TreeNode *queue[20];
    int front = 0, back = 0;

    queue[back++] = root;
    while (front < back)
    {
        TreeNode *current = queue[front++];
        printf("%c", current->val);
        if (current->left != NULL) queue[back++] = current->left;
        if (current->right != NULL) queue[back++] = current->right;
    }
}
