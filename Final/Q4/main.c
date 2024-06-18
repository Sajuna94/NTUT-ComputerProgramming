// time 59:03

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node_s {
    int coef; // 係數
    int exp; // 指數
    struct node_s * next;
} Node;

typedef struct pol_s {
    struct node_s *root;
} Pol;

Node* createNode(int coef, int exp) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->coef = coef;
    new->exp = exp;
    return new;
}
void push(Pol* pol, int coef, int exp) {
    Node* new = createNode(coef, exp);
    new->next = pol->root;
    pol->root = new;
}

Pol* createPol(char* string) {
    Pol* pol = (Pol*)malloc(sizeof(Pol));
    pol->root = NULL;
    char* token = strtok(string, " ");

    while (token != NULL)
    {
        push(pol, atoi(token), 0);
        token = strtok(NULL, " ");
    }
    int idx = 0;
    for (Node* cur = pol->root; cur; cur = cur->next) {
        cur->exp = idx++;
    }
    return pol;
}

void add(Pol* X, Pol* Y, Pol* Z) {
    Node* curX = X->root, *curY = Y->root;

    while (curX || curY)
    {
        int coef = 0, exp = 0;
        if (curX != NULL) {
            coef += curX->coef;
            exp = curX->exp;
            curX = curX->next;
        }
        if (curY != NULL) {
            coef += curY->coef;
            exp = curY->exp;
            curY = curY->next;
        }
        push(Z, coef, exp);
    }
};
//兩個多項式 X, Y 相加,Z 是結果
void sub(Pol* X, Pol* Y, Pol* Z) {
    Node* curX = X->root, *curY = Y->root;

    while (curX || curY)
    {
        int coef = 0, exp = 0;
        if (curX != NULL) {
            coef += curX->coef;
            exp = curX->exp;
            curX = curX->next;
        }
        if (curY != NULL) {
            coef -= curY->coef;
            exp = curY->exp;
            curY = curY->next;
        }
        push(Z, coef, exp);
    }
}
//兩個多項式 X, Y 相減,Z 是結果
void mul(Pol* X, Pol* Y, Pol* Z) {
    int lenX = 0, lenY = 0;
    for (Node* curX = X->root; curX; curX = curX->next) {
        lenX++;
    }
    for (Node* curY = Y->root; curY; curY = curY->next) {
        lenY++;
    }
    int len = lenX + lenY - 1;
    int arr[len];
    for (int i = 0; i < len; i++) arr[i] = 0;

    for (Node* curX = X->root; curX; curX = curX->next) {
        for (Node* curY = Y->root; curY; curY = curY->next) {
            arr[curX->exp + curY->exp] += curX->coef * curY->coef;
        }
    }

    for (int i = 0; i < len; i++) {
        push(Z, arr[i], i);
    }
}

int main(void) {
    for (int i = 0; i < 3; i++) {
        char inputA[100], inputB[100];
        scanf(" %[^\n]", inputA);
        scanf(" %[^\n]", inputB);

        printf("dd%s\n");

        Pol* polA = createPol(inputA); 
        Pol* polB = createPol(inputB);
        Pol result = { .root = NULL };

        char command; scanf(" %c", &command);
        switch (command)
        {
        case '+': add(polA, polB, &result); break;
        case '-': sub(polA, polB, &result); break;
        case '*': mul(polA, polB, &result); break;
        }

        for (Node* cur = result.root; cur; cur = cur->next) {
            printf("%d %d ", cur->coef, cur->exp);
        }
        printf("\n");
    }
    
}
