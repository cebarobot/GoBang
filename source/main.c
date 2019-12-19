#include <stdio.h>

#include "board.h"
#include "front.h"

#define HUMAN 1
#define AI 2

int player_role[3];

int main() {
    printf("Welcome to DeltaBang, a GoBang AI.\n");
    printf("Built by ceba.\n");

    int ok_flg = 0;
    while (!ok_flg) {
        printf("\n");

        player_role[BLACK] = inputYesNo("Is the first player (black) an AI?", NO) ? AI : HUMAN;
        player_role[WHITE] = inputYesNo("Is the second player (white) an AI?", NO) ? AI : HUMAN;

        printf("\n");
        printf("The first player (black) will be %s\n", player_role[BLACK] == HUMAN ? "a hunam" : "an AI");
        printf("The seconde player (white) will be %s.\n", player_role[WHITE] == HUMAN ? "a hunam" : "an AI");

        ok_flg = inputYesNo("Are you sure about that?", YES);
    }

    printf("\n");
    printf("Now the game start.\n");

    boardInit();

    int turn_now = BLACK;
    while (1) {
        printf("\n");
        printf("Step %d:\n", getCntPiece());
        printBoard();

        printf("\n");
        printf("%s's turn.\n", turn_now == BLACK? "Black" : "White");

        int next_xx, next_yy;
        if(player_role[turn_now] == AI) {

        } else {
            // human player
            printf("\n");
            while (1) {
                inputPiece("Please enter the coordinate of the next piece", &next_xx, &next_yy);
                if (getColor(next_xx, next_yy) == NOPIECE) {
                    break;
                } else {
                    printf("There has been a piece at %d%c, ", next_yy + 'A' - 1, next_xx);
                    printf("please choose another place.\n");
                }
            }
        }

        printf("\n");
        printf("%s placed a piece at %c%d.\n", turn_now == BLACK ? "Black" : "White", next_yy + 'A' - 1, next_xx);

        placePiece(next_xx, next_yy, turn_now);
        
        if (turn_now == BLACK) {
            turn_now = WHITE;
        } else {
            turn_now = BLACK;
        }
    }
    return 0;
}