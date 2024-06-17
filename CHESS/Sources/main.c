
#include "../Headers/game.h"
#include <windows.h>

int main(void) {
    int a;
    scanf("%d", &a);
    for (int i = 0; i < 1; i++) {

        Game* game = newGame(BLACK, WHITE);
        Chess* chess = &game->chess;
        // setChessPiece(&game->chess, BLACK, newPoint(0, 0));

        Piece winner = startGame(game);
        // displayDistance(&game->chess, BLACK);


        free(game);
        // sleep(1);
    };
    
    // displayChess(&game->chess);
    // printf("=====================================\n");
    // displayDistance(chess, BLACK);

    // printf("\nWINNER: %d\n", winner);

    
}