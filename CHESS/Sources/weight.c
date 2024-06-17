#include "../Headers/weight.h"

int calcLiveWeight(Chess *chess, Piece piece, Point position)
{
    bool LIVE_5 = false;
    bool LIVE_4 = false, DOUBLE_DIE_4 = false, DIE_4_LIVE_3 = false;
    bool DOUBLE_LIVE_3 = false, DIE_3_LIVE_3_HIGH = false;
    bool DIE_4 = false, LOW_DIE_4 = false;
    bool LIVE_3 = false, JUMP_LIVE_3 = false;
    bool DOUBLE_LIVE_2 = false, LIVE_2 = false, LOW_LIVE_2 = false;
    bool DIE_3 = false, DIE_2 = false;

    for (int i = 0; i < 8; i += 2) {
        LiveHelper liveA = { .length = 0, .IS_LIVE = false };
        LiveHelper liveB = { .length = 0, .IS_LIVE = false };

        LiveDFS(chess, piece, dirPts[i], position.X + dirPts[i].X, position.Y + dirPts[i].Y, &liveA);
        LiveDFS(chess, piece, dirPts[i + 1], position.X + dirPts[i + 1].X, position.Y + dirPts[i + 1].Y, &liveB);

        LiveHelper liveResult = { .length = liveA.length + liveB.length, .IS_LIVE = liveA.IS_LIVE && liveB.IS_LIVE };

        if (liveResult.length >= 4 && liveResult.IS_LIVE) {
            LIVE_5 = true;
        } else if (liveResult.length == 4) {
            if (liveResult.IS_LIVE) {
                LIVE_4 = true;
            } else if (liveA.IS_LIVE || liveB.IS_LIVE) {
                DIE_4 = true;
            } else {
                LOW_DIE_4 = true;
            }
        } else if (liveResult.length == 3) {
            if (liveResult.IS_LIVE) {
                if (liveA.length == 3 || liveB.length == 3) {
                    JUMP_LIVE_3 = true;
                } else {
                    LIVE_3 = true;
                }
            } else if (liveA.IS_LIVE || liveB.IS_LIVE) {
                DIE_3_LIVE_3_HIGH = true;
            } else {
                DIE_3 = true;
            }
        } else if (liveResult.length == 2) {
            if (liveResult.IS_LIVE) {
                LIVE_2 = true;
            } else if (liveA.IS_LIVE || liveB.IS_LIVE) {
                LOW_LIVE_2 = true;
            } else {
                DIE_2 = true;
            }
        }
    }

    int total = 1;

    if (LIVE_5) total = 14;
    else if (LIVE_4 || (DIE_4 && LIVE_3) || DOUBLE_DIE_4) total = 13;
    else if (DOUBLE_LIVE_3) total = 12;
    else if (DIE_3_LIVE_3_HIGH) total = 11;
    else if (DIE_4) total = 10;
    else if (LOW_DIE_4) total = 9;
    else if (LIVE_3) total = 8;
    else if (JUMP_LIVE_3) total = 7;
    else if (DOUBLE_LIVE_2) total = 6;
    else if (LIVE_2) total = 5;
    else if (LOW_LIVE_2) total = 4;
    else if (DIE_3) total = 3;
    else if (DIE_2) total = 2;

    return total;
}

LiveHelper *LiveDFS(Chess *chess, Piece piece, Point dirPt, int x, int y, LiveHelper *liveHelper)
{
    if (!isSafe(x, y))
        return liveHelper;

    if (chess->board[y][x] != piece)
    {
        if (chess->board[y][x] == EMPTY)
            liveHelper->IS_LIVE = true;
        return liveHelper;
    }
    liveHelper->length++;
    return LiveDFS(chess, piece, dirPt, x + dirPt.X, y + dirPt.Y, liveHelper);
}
