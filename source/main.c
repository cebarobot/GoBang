#include <stdio.h>
#include <string.h>

#include "board.h"
#include "front.h"
#include "analysis.h"

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
        printf("The first player (black) will be %s\n", player_role[BLACK] == HUMAN ? "a human" : "an AI");
        printf("The seconde player (white) will be %s.\n", player_role[WHITE] == HUMAN ? "a human" : "an AI");

        ok_flg = inputYesNo("Are you sure about that?", YES);
    }

    printf("\n");
    printf("Now the game start.\n");

    boardInit();

    int turn_now = BLACK;

    printf("\n");
    printf("Step %d:\n", getCntStone());
    printBoard();

    while (1) {


        printf("\n");
        printf("%s's turn.\n", turn_now == BLACK? "Black" : "White");

        int next_xx, next_yy;
        if(player_role[turn_now] == AI) {

        } else {
            // human player
            printf("\n");
            while (1) {
                inputStone("Please enter the coordinate of the next stone", &next_xx, &next_yy);
                if (getColor(next_xx, next_yy) == NOSTONE) {
                    break;
                } else {
                    printf("There has been a stone at %d%c, ", next_yy + 'A' - 1, next_xx);
                    printf("please choose another place.\n");
                }
            }
        }

        printf("\n");
        printf("%s placed a stone at %c%d.\n", turn_now == BLACK ? "Black" : "White", next_yy + 'A' - 1, next_xx);

        placeStone(next_xx, next_yy, turn_now);

        printf("\n");
        printf("Step %d:\n", getCntStone());
        printBoard();

        int analysis_result[MAX_KIND];
        memset(analysis_result, 0, sizeof(analysis_result));
        analysisPoint(analysis_result, next_xx, next_yy);
        printAnalysisResult(analysis_result);
        
        printf("\n");
        // check whether the player has Winned
        if (checkWin(analysis_result, turn_now)) {
            printf("%s wins and %s loses.\n", turn_now == BLACK? "Black" : "White", turn_now != BLACK? "Black" : "White");
            break;
        }
        // check whether there is a forbidden move
        if (checkForbiddenMove(analysis_result, turn_now)) {
            if (inputYesNo("There seems to be a forbidden move, wether to continue?", NO)) {
                printf("The game continues.\n");
            } else {
                printf("The game ended.\n");
                printf("%s wins and %s loses.\n", turn_now != BLACK? "Black" : "White", turn_now == BLACK? "Black" : "White");
                break;
            }
        }

        printf("\n");
        printf("Step %d:\n", getCntStone());
        printBoard();
        
        if (turn_now == BLACK) {
            turn_now = WHITE;
        } else {
            turn_now = BLACK;
        }
    }
    return 0;
}