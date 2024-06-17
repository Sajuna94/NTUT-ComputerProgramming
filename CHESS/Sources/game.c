#include "../Headers/game.h"


Game* newGame(Piece myPiece, Piece enemyPiece) {
    Game* game = (Game*)malloc(sizeof(Game));

    game->me = myPiece;
    game->enemy = enemyPiece;

    game->chess = newChess();
    game->cord = NULL;
    game->size = 0;

    return game;
}

Piece swapPlayer(Piece player) {
    return (player == BLACK) ? WHITE : BLACK;
}

int calcWeight(Game* game, Piece piece, Point position) {
    int multiplying = 50;
    int floodMut = multiplying * (0.05);

    int liveBonusME = calcLiveWeight(&game->chess, piece, position);
    int liveBonusENEMY = calcLiveWeight(&game->chess, swapPlayer(piece), position);
    return 
        (
            (game->chess.distanceMaps[piece][position.Y][position.X]) * liveBonusME +
            (game->chess.distanceMaps[swapPlayer(piece)][position.Y][position.X]) * liveBonusENEMY
        ) * multiplying
        +
        game->chess.floodMap[position.Y][position.X] * floodMut;
}

bool tryPutPiece(Game* game, Piece player, Point position) {
    Chess* chess = &game->chess;

    if (chess->board[position.Y][position.X] == BLACK || chess->board[position.Y][position.X] == WHITE)
        return false;
    if (player == BLACK && chess->board[position.Y][position.X] == BAN)
        return false;
    
    setChessPiece(chess, player, position);   

    // TODO: update weight
    // TODO: update banned 

    // update cord
    game->cord = realloc(game->cord, (game->size + 1) * sizeof(Coordinate));
    game->cord[game->size].x = position.X;
    game->cord[game->size].y = position.Y;
    game->cord[game->size].player = player;
    game->size++;

    return true;
}

Point getNextMove(Game* game, Piece piece) {
    // TODO: 取得下棋位置
    Chess* chess = &game->chess;
    Point targetPoint = { .X = rand() % BOARD_SIZE, .Y = rand() % BOARD_SIZE };

    int maxWeight = 0;
    for (int y = 0; y < BOARD_SIZE; y++)
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (chess->board[y][x] != EMPTY)
                continue;

            int weight = calcWeight(game, piece, newPoint(x, y)) + rand() % BOARD_SIZE;

            if (chess->distanceMaps[swapPlayer(piece)][y][x] >= 4)
                weight = INT_MAX - 1;
            if (chess->distanceMaps[piece][y][x] >= 4)
                weight = INT_MAX;

            if (weight > maxWeight) {
                targetPoint.X = x;
                targetPoint.Y=  y;
                maxWeight = weight;
            }
        }
    return targetPoint;
}

Piece startGame(Game* game) {
    srand(time(NULL));

    int maxMoves = BOARD_SIZE * BOARD_SIZE, moveCount = 0;

    Piece currentPlayer = BLACK;

    while (moveCount < maxMoves)
    {
        Point move = newPoint(0, 0); // 要下棋的位置

        if (currentPlayer == game->enemy) {
            // TODO: 取得對方下棋位置
            // move = newPoint(rand() % BOARD_SIZE, rand() % BOARD_SIZE);
            move = getNextMove(game, game->enemy);
        }
        else if (currentPlayer == game->me) {
            move = getNextMove(game, game->me);
        }

        if (!tryPutPiece(game, currentPlayer, move)) {
            // TODO: 下棋失敗處理 (可能不用做)
            printf("%s trying put (%d, %d)\n", (currentPlayer == BLACK) ? "BlACK(X)":"WHITE(O)", move.X, move.Y);
            break;;
        }

        if (checkWin(&game->chess, currentPlayer, move)) {
            displayChess(&game->chess);
            printf("\n(%d, %d) Winner is: %s\n", move.X, move.Y, (currentPlayer == BLACK) ? "BlACK(X)":"WHITE(O)");
            return currentPlayer;
        }

        currentPlayer = swapPlayer(currentPlayer);
        moveCount++;

        // print data
        displayChess(&game->chess);
        printf("[%d] %s target: (%d, %d)\n",moveCount, (currentPlayer == BLACK) ? "BlACK(X)":"WHITE(O)", move.X, move.Y);
        sleep(1);
        system("cls");
    }

    return EMPTY;
}

void endGame(Game* game) {
    free(game);
}