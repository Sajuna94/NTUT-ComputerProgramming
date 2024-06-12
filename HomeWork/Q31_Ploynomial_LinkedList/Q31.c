#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct node_s {
    int coefficient; // 係數
    // int exponent; // 指數
    struct node_s *next;
} node_t;
typedef node_t *node_pt;

typedef struct polynomial_s {
    node_pt head; // 最小次方
    int length;
} Polynomial;

node_pt newNode(int coefficient) {
    node_pt new = (node_pt)malloc(sizeof(node_t));

    new->coefficient = coefficient;
    new->next = NULL;

    return new;
}

void printPolynomial(Polynomial *poly) {
    node_pt current = poly->head;

    bool NONE_ZERO = true;
    for (node_pt tmp = poly->head; tmp != NULL; tmp = tmp->next)  {
        if (NONE_ZERO && tmp->coefficient != 0)
            NONE_ZERO = false;
    }
    if (NONE_ZERO) {
        printf("0\n");
        return;
    }

    if (current->coefficient < 0) printf("-");

    int count = 0;
    while (current != NULL)
    {
        if (current->coefficient != 0) {
            int exponent = poly->length - count - 1; // 指數
            int coefficient = abs(current->coefficient); // 係數

            // 前項(+/-)
            if (count > 0) printf("%c", current->coefficient < 0 ? '-' : '+');
            // 係數
            if (coefficient != 1 || exponent == 0) printf("%d", coefficient);
            // x
            if (exponent > 0) printf("x");
            // 次方項
            if (exponent > 1) printf("^%d", exponent);
        }
        count++;
        current = current->next;
    }
    printf("\n");
}

Polynomial* stringToPolynomial(char* string) {
    int length = 0;

    int *data = NULL;
    char* token = strtok(string, " ");

    while (token != NULL)
    {
        data = realloc(data, (length + 1) * sizeof(int));
        data[length++] = atoi(token);
        token = strtok(NULL, " "); 
    }

    // init polynomial
    Polynomial *poly = (Polynomial*)malloc(sizeof(Polynomial));
    poly->head = NULL;
    poly->length = length;

    for (int i = 0; i < length; i++) {
        node_pt new = newNode(data[i]);
        new->next = poly->head;
        poly->head = new;
    }
    return poly;
}

Polynomial* add(Polynomial *polyA, Polynomial *polyB) {
    Polynomial *poly = (Polynomial*)malloc(sizeof(Polynomial)); 
    poly->head = NULL;
    poly->length = MAX(polyA->length, polyB->length);

    node_pt tmpA = polyA->head, tmpB = polyB->head;

    while (tmpA != NULL || tmpB != NULL)
    {
        int coefficient = 0;
        if (tmpA != NULL) {
            coefficient += tmpA->coefficient;
            tmpA = tmpA->next;
        }
        if (tmpB != NULL) {
            coefficient += tmpB->coefficient;
            tmpB = tmpB->next;
        }
        
        node_pt new = newNode(coefficient);
        new->next = poly->head;
        poly->head = new;
    }
    return poly;
}

Polynomial* sub(Polynomial *polyA, Polynomial *polyB) {
    Polynomial *poly = (Polynomial*)malloc(sizeof(Polynomial)); 
    poly->head = NULL;
    poly->length = MAX(polyA->length, polyB->length);

    node_pt tmpA = polyA->head, tmpB = polyB->head;

    while (tmpA != NULL || tmpB != NULL)
    {
        int coefficient = 0;
        if (tmpA != NULL) {
            coefficient += tmpA->coefficient;
            tmpA = tmpA->next;
        }
        if (tmpB != NULL) {
            coefficient -= tmpB->coefficient;
            tmpB = tmpB->next;
        }
        
        node_pt new = newNode(coefficient);
        new->next = poly->head;
        poly->head = new;
    }
    return poly;
}

Polynomial* mut(Polynomial *polyA, Polynomial *polyB) {
    Polynomial *poly = (Polynomial*)malloc(sizeof(Polynomial)); 
    poly->head = NULL;
    poly->length = polyA->length + polyB->length - 1;

    int data[poly->length]; memset(data, 0, poly->length * sizeof(int));

    int powA = 0, powB = 0;
    for (node_pt tmpA = polyA->head; tmpA != NULL; tmpA = tmpA->next, powA++) {
        powB = 0;
        for (node_pt tmpB = polyB->head; tmpB != NULL; tmpB = tmpB->next, powB++) {
            data[powA + powB] += tmpA->coefficient * tmpB->coefficient;
        }
    }
    for (int i = 0; i < poly->length; i++) {
        node_pt new = newNode(data[i]);
        new->next = poly->head;
        poly->head = new;
    }
    return poly;
}

int main(void) {
    char input[1000];

    fgets(input, sizeof(input), stdin);
    Polynomial *polyA = stringToPolynomial(input);
    fgets(input, sizeof(input), stdin);
    Polynomial *polyB = stringToPolynomial(input);

    printPolynomial(add(polyA, polyB));
    printPolynomial(sub(polyA, polyB));
    printPolynomial(mut(polyA, polyB));
}