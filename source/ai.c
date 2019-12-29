#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ai.h"
#include "board.h"
#include "analysis.h"

#define DFS_MAX_DEPTH 4

#define MAX_SCORE 100000000

int AIDfs(int depth, int role, int * p_next_xx, int * p_next_yy, int alpha, int beta);
int countScore(int analysis_result[MAX_KIND], int analysis_result_2[MAX_KIND]);
int genSearchSequence(int sequence_x[], int sequence_y[]);

// public
// AIMain: the main function of ai program
int AIMain(int role, int * p_next_xx, int * p_next_yy) {
    int next_xx = 8, next_yy = 8;
    if (getCntStone() == 1) {
        time_t t;
        srand((unsigned) time(&t));
        do {
            next_xx = rand() % 3 + 7;
            next_yy = rand() % 3 + 7;
        } while (getColor(next_xx, next_yy) != NOSTONE);
    } else if (getCntStone() == 2) {
        time_t t;
        srand((unsigned) time(&t));
        do {
            next_xx = rand() % 5 + 6;
            next_yy = rand() % 5 + 6;
        } while (getColor(next_xx, next_yy) != NOSTONE);
    } else if (getCntStone() > 2) {
        AIDfs(0, role, &next_xx, &next_yy, -MAX_SCORE, MAX_SCORE);
        printf("!!!!!!!\n");
    }

    // return value s
    *p_next_xx = next_xx;
    *p_next_yy = next_yy;
    return 0;
}

// private
// AIDfs:
int AIDfs(int depth, int role, int * p_next_xx, int * p_next_yy, int alpha, int beta) {
    // printBoard();
    // if (getCntStone() >=10) {
    //     printf("=====================depth %d", depth);
    //     printCoordinate(getLastX(), getLastY());
    //     printf("\n");
    // }
    if (depth >= DFS_MAX_DEPTH) {
        int analysis_result[MAX_KIND];
        int analysis_result_2[MAX_KIND];
        memset(analysis_result, 0, sizeof(analysis_result));
        memset(analysis_result_2, 0, sizeof(analysis_result_2));
        // printf("!!!!!!!!!!in!!!!!!!\n");
        analysisBoard(role, analysis_result, analysis_result_2);
        // printf("~~~~~~~~out~~~~~~~~~~~~\n");
        int status_score = countScore(analysis_result, analysis_result_2);
        // printf("~~~~~~~~awerfqwrf~~~~~~~~~~~~\n");

        return status_score;
    }
    int sequence_x[BOARD_SIZE];
    int sequence_y[BOARD_SIZE];
    int sequence_cnt = genSearchSequence(sequence_x, sequence_y);

    int mx_score = -MAX_SCORE;
    int mx_id = 0;

    int role_2 = roleReverse(role);
    
    int analysis_result[MAX_KIND];

    for (int i = 0; i < sequence_cnt; i++) {
        if (getColor(sequence_x[i], sequence_y[i]) != NOSTONE) {
            // printf("\e[43m\e[30m try to place a bad stone %d \e[0m \n", getColor(sequence_x[i], sequence_y[i]));
            continue;
        }
        placeStone(sequence_x[i], sequence_y[i], role); 

        memset(analysis_result, 0, sizeof(analysis_result));
        // printf("\e[43m\e[30m in analysisPoint %d \e[0m \n", depth);
        analysisPoint(analysis_result, sequence_x[i], sequence_y[i]);
        // printf("\e[43m\e[30m out analysisPoint %d \e[0m \n", depth);

        if (checkWin(analysis_result, role)) {
            // if (getLastX() != sequence_x[i] || getLastY() != sequence_y[i]) {
            //     printf("\e[43m\e[30m remove a not placed stone \e[0m \n");
            // }
            removeLastStone();
            mx_score = MAX_SCORE;
            mx_id = i;
            break;
        } else if (checkForbiddenMove(analysis_result, role)) {
            // if (getLastX() != sequence_x[i] || getLastY() != sequence_y[i]) {
            //     printf("\e[43m\e[30m remove a not placed stone \e[0m \n");
            // }
            removeLastStone();
            continue;
        } else {
            int nx, ny;
            int tmp = -AIDfs(depth + 1, role_2, &nx, &ny, -beta, -alpha);
            // if (getLastX() != sequence_x[i] || getLastY() != sequence_y[i]) {
            //     printf("\e[43m\e[30m remove a not placed stone \e[0m \n");
            // }
            removeLastStone();
            if (tmp > mx_score) {
                mx_score = tmp;
                mx_id = i;
            }
            if (mx_score > alpha) {
                alpha = mx_score;
            }
            if (mx_score >= beta) {
                break;
            }
        }
    }
    
    *p_next_xx = sequence_x[mx_id];
    *p_next_yy = sequence_y[mx_id];
    return mx_score;
}


// private
// AIDfsStupid: depth first search but it is too stupid
int AIDfsStupid(int depth, int role, int * p_next_xx, int * p_next_yy) {
    // printf("==================depth: %d\n", depth);
    int role_2 = roleReverse(role);
    int analysis_result[MAX_KIND];
    int analysis_result_2[MAX_KIND];
    int point_analysis_result[MAX_KIND];
    memset(analysis_result, 0, sizeof(analysis_result));
    memset(analysis_result_2, 0, sizeof(analysis_result_2));
    memset(point_analysis_result, 0, sizeof(point_analysis_result));

    analysisBoard(role, analysis_result, analysis_result_2);

    int status_score = countScore(analysis_result, analysis_result_2);

    if (depth >= DFS_MAX_DEPTH) {
        return status_score;
    }

    int sequence_x[BOARD_SIZE];
    int sequence_y[BOARD_SIZE];
    int sequence_cnt = genSearchSequence(sequence_x, sequence_y);

    int mn_id_array[BOARD_SIZE];
    int mn_score = 0;
    int mn_id_cnt = 0;

    // int score_map[BOARD_WIDTH + 1][BOARD_WIDTH + 1];

    for (int i = 0; i < sequence_cnt; i++) {
        placeStone(sequence_x[i], sequence_y[i], role); 
        int nx, ny;
        int tmp = AIDfsStupid(depth + 1, role_2, &nx, &ny);
        if (tmp < mn_score || mn_id_cnt == 0) {
            mn_score = tmp;
            mn_id_array[0] = i;
            mn_id_cnt = 1;
        } else if (tmp == mn_score) {
            mn_id_array[mn_id_cnt++] = i;
        }

        removeLastStone();
    }

    // printf("sequence_cnt : %d\n", sequence_cnt);
    
    *p_next_xx = sequence_x[mn_id_array[0]];
    *p_next_yy = sequence_y[mn_id_array[0]];
    // printf("!!!!!!!\n");
    return 0 - mn_score;
}

// private
// genSearchSequence: generate search sequence of points.
int genSearchSequence(int sequence_x[], int sequence_y[]) {
    int cnt = 0;
    int last_x = getLastX();
    int last_y = getLastY();

    if (!inBoard(last_x, last_y)) {
        printf("\e[42m\e[30m out of board in genSearchSequence \e[0m\n");
        return 0;
    }

    for (int i = -3; i <= 3; i++) {
        for (int j = -3; j <= 3; j++) {
            if (getColor(last_x + i, last_y + j) == NOSTONE) {
                sequence_x[cnt] = last_x + i;
                sequence_y[cnt] = last_y + j;
                cnt ++;
                // printf("\e[42m\e[30m cnt of sequence %d \e[0m\n", cnt);
            }
        }
    }

    return cnt;
}

// private
// countScore: count the score of the current board. the current player has advantage.
int countScore(int analysis_result[MAX_KIND], int analysis_result_2[MAX_KIND]) {
    int score = 0;
    int score_2 = 0;
    score += analysis_result[TWO]           * 100;
    score += analysis_result[THREE_B]       * 100;
    score += analysis_result[THREE]         * 10000;
    score += analysis_result[FOUR_B]        * 10000;
    score += analysis_result[FOUR]          * 1000000;
    score += analysis_result[THREE_D]       * 1000000;
    score += analysis_result[FOUR_THREE]    * 1000000;
    score += analysis_result[FOUR_D]        * 1000000;
    score += analysis_result[FIVE]          * 10000000;

    score_2 += analysis_result_2[TWO]           * 100;
    score_2 += analysis_result_2[THREE_B]       * 100;
    score_2 += analysis_result_2[THREE]         * 10000;
    score_2 += analysis_result_2[FOUR_B]        * 10000;
    score_2 += analysis_result_2[FOUR]          * 1000000;
    score_2 += analysis_result_2[THREE_D]       * 1000000;
    score_2 += analysis_result_2[FOUR_THREE]    * 1000000;
    score_2 += analysis_result_2[FOUR_D]        * 1000000;
    score_2 += analysis_result_2[FIVE]          * 10000000;

    return score - score_2;
}



// AIMainRandom: This ai placed a stone randomly.
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

// AIMainStupid: This ai placed a stone near the last stone.
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