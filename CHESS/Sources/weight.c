#include "../Headers/weight.h"

int calcLiveWeight(Chess* chess, Piece piece, Point position) {
    bool DIE_3 = false, DIE_4 = false;
    bool LIVE_3 = false, LIVE_4 = false;

    for (int i = 0; i < 8; i += 2) {
        LiveHelper liveA = { .length = 0, .IS_LIVE = false };
        LiveHelper liveB = { .length = 0, .IS_LIVE = false };

        LiveDFS(chess, piece, dirPts[i], position.X + dirPts[i].X, position.Y + dirPts[i].Y, &liveA);
        LiveDFS(chess, piece, dirPts[i + 1], position.X + dirPts[i + 1].X, position.Y + dirPts[i + 1].Y, &liveB);

        LiveHelper liveResult = { .length = liveA.length + liveB.length, .IS_LIVE = liveA.IS_LIVE && liveB.IS_LIVE };

        // 可能造成長連?
        if (piece == BLACK && liveResult.length > 3) {
            return 1; // 長連對黑旗沒有權值效益?
        }
        else if (liveResult.length >= 3) {
            if (liveResult.IS_LIVE)
                LIVE_4 = true;
            if (liveA.IS_LIVE || liveB.IS_LIVE) // 被圍住的會不算die4
                DIE_4 = true;
        }
        else if (liveResult.length == 2) {
            if (liveResult.IS_LIVE)
                LIVE_3 = true;
            if (liveA.IS_LIVE || liveB.IS_LIVE)
                DIE_3 = true;
        }
    }

    int total = 1, combo = 1;

    if (LIVE_4) { printf("live4, "); total += 20 * combo++; }
    if (LIVE_3) { printf("live3, ");total +=  10 * combo++; }
    if (DIE_4) { total += 2 * combo++; }
    if (DIE_3) { total += 1 * combo++; }
    
    return total;
}

LiveHelper* LiveDFS(Chess* chess, Piece piece, Point dirPt, int x, int y, LiveHelper* liveHelper) {
    if (!isSafe(x, y))
        return liveHelper;

    if (chess->board[y][x] != piece) {
        // 最後一格為空
        if (chess->board[y][x] == EMPTY)
            liveHelper->IS_LIVE = true;

        return liveHelper;
    }
    liveHelper->length++;

    return LiveDFS(chess, piece, dirPt, x + dirPt.X, y + dirPt.Y, liveHelper);
}