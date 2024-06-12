#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
    int coefficient; // 係數
    struct node_s *next;
} node_t;
typedef node_t *node_pt;

typedef struct polynomial_s {
    node_pt head; // 最小次方
} Polynomial;



