#ifndef CHESS_H
#define CHESS_H

#define BOARD_SIZE 15

typedef enum { EMPTY = 2, BLACK = 0, WHITE = 1, BAN = 3 } Piece;

static const int dirX[] = { -1, 1,   0,  0,   -1,  1,    1, -1  };
static const int dirY[] = {  0, 0,   1, -1,   -1,  1,   -1,  1  };

static const Point dirPts[8] = {
    {-1, 0}, {1, 0},
    {0, 1}, {0, -1},
    {-1, -1}, {1, 1},
    {1, -1}, {-1, 1}  
};

typedef struct Chess
{
    Piece board[BOARD_SIZE][BOARD_SIZE];

    int distanceMaps[2][BOARD_SIZE][BOARD_SIZE];
    int floodMap[BOARD_SIZE][BOARD_SIZE];
} Chess;


void displayChess(Chess* chess);

void displayDistance(Chess* chess, Piece piece);

Chess newChess();

void setChessPiece(Chess* chess, Piece piece, Point position);

bool checkWin(Chess* chess, Piece piece, Point position);

bool isSafe(int x, int y);

#endif