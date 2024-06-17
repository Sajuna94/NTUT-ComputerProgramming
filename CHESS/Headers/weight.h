#ifndef WEIGHT_H
#define WEIGHT_H

// #include <stdbool.h>
#include "../Tools/point.h"
#include "game.h"

// typedef struct {
//     Chess* chess;
// } WeightMap;

// typedef struct
// {
//     int X, Y;
//     int weight;

// } WeightPoint;

typedef struct
{
    int length;
    bool IS_LIVE;
} LiveHelper;

int calcLiveWeight(Chess* chess, Piece piece, Point position);

LiveHelper* LiveDFS(Chess* chess, Piece piece, Point dirPt, int x, int y, LiveHelper* liveHelper);


#endif