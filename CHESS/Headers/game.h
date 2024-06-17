#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <windows.h>
#include <conio.h>
#include <limits.h>

#include "../Tools/point.h"
#include "chess.h"
#include "weight.h"

typedef struct {
    int x, y;
    int player;
} Coordinate;

typedef struct Game
{
    Coordinate *cord;
    int size;

    Piece me, enemy;
    Chess chess;
} Game;


Game* newGame(Piece myPiece, Piece enemyPiece);
Piece startGame(Game* game);
void endGame(Game* game);

#endif