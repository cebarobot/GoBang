#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ai.h"
#include "board.h"
#include "analysis.h"

// AIMain: the main function of ai program
int AIMain(int * p_next_xx, int * p_next_yy) {
    int next_xx, next_yy;

    next_xx = 1;
    next_yy = 1;

    // return value s
    *p_next_xx = next_xx;
    *p_next_yy = next_yy;
    return 0;
}

int AIMainRandom(int * p_next_xx, int * p_next_yy) {
    int next_xx, next_yy;

    time_t t;
    srand((unsigned) time(&t));

    do {
        next_xx = rand() % 15 + 1;
        next_yy = rand() % 15 + 1;
    } while (getColor(next_xx, next_yy) != NOSTONE);
    // printf("next_xx = %d; next_yy = %d.", next_xx, next_yy);

    // return value s
    *p_next_xx = next_xx;
    *p_next_yy = next_yy;
    return 0;
}

int AIMainStupid(int * p_next_xx, int * p_next_yy) {
    int next_xx, next_yy;
    int last_xx = getLastX();
    int last_yy = getLastY();

    next_xx = 8;
    next_yy = 8;
    time_t t;
    srand((unsigned) time(&t));

    if (inBoard(last_xx, last_yy)) {
        for (int i = 1; i <= 14; i++) {
            int flg = 0;
            int dir_base = rand() % MAX_FULL_DIR;
            for (int j = 0; j < MAX_FULL_DIR; j++) {
                int dir = (dir_base + j) % MAX_FULL_DIR;
                if (getColor(last_xx + i * dx[dir], last_yy + i * dy[dir]) == NOSTONE) {
                    next_xx = last_xx + i * dx[dir];
                    next_yy = last_yy + i * dy[dir];
                    flg = 1;
                    break;
                }
            }
            if (flg) {
                break;
            }
        }
    }

    // return value s
    *p_next_xx = next_xx;
    *p_next_yy = next_yy;
    return 0;
}