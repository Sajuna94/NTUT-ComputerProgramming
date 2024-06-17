#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <unistd.h>

typedef struct {
    int x;
    int y;
    int player;
} Coordinate;

typedef struct {
    Coordinate* cord;
    int size;
} Chess;

// process chess data
void initChess(Chess* chess) {
    chess->cord = NULL;
    chess->size = 0;
};

int setXY(Chess* chess, int x, int y, int player) {
    if (x == 0 || y == 0) {
        return 0;
    }

    for (int i = 0; i < chess->size; i++) {
        if (chess->cord[i].x == x && chess->cord[i].y == y) {
            return 0;
        }
    }

    chess->cord = (Coordinate*)realloc(chess->cord, (chess->size + 1) * sizeof(Coordinate));
    chess->cord[chess->size].x = x;
    chess->cord[chess->size].y = y;
    chess->cord[chess->size].player = player;
    chess->size++;

    return 1;
}

// write back
void writeChessBoard(Chess* chess, int player, int* x, int* y) {
    while (1) {
        *x = rand() % 20 + 1;
        *y = rand() % 20 + 1;
        if (setXY(chess, *x, *y, player) == 1) {
            return;
        }
    }
}