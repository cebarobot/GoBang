#include <stdio.h>
#include <stdbool.h>

#include "board.h"

// private
// The whole board
boardCell gobang_board[BOARD_WIDTH + 1][BOARD_WIDTH + 1];

// The order of placed man
boardCell order_of_man[BOARD_SIZE + 10];
int cnt_man = 0;

// public
// boardInit: initialize the board
void boardInit(void) {
    for (int i = 1; i <= BOARD_WIDTH; i++) {
        for (int j = 1; j <= BOARD_WIDTH; j++) {
            gobang_board[i][j].color = NOMAN;
            gobang_board[i][j].order = 0;
            gobang_board[i][j].x = i;
            gobang_board[i][j].y = j;
        }
    }
}

// public
// getCntMan: get the number of men on the board
int getCntMan(void) {
    return cnt_man;
}

// public
// getColor: get color of man at (x, y)
int getColor(int x, int y) {
    return gobang_board[x][y].color;
}

// public
// getOrder: get order of man at (x, y)
int getOrder(int x, int y) {
    return gobang_board[x][y].order;
}

// public
// getLastX: get the x of last man
int getLastX(void) {
    return order_of_man[cnt_man].x;
}

// public
// getLastY: get the y of last man
int getLastY(void) {
    return order_of_man[cnt_man].y;
}

// public
// getLastColor: get the color of last man
int getLastColor(void) {
    return order_of_man[cnt_man].color;
}

// private
// printBoardCell
void printBoardCell(int x, int y, int color, bool is_last) {
    // print the first character
    if (y == 1) {
        printf(" ");
    } else {
        printf("─");
    }

    // print the second character
    if (color == NOMAN) {
        if (x == 15) {
            if (y == 1) {
                printf("┌");
            } else if (y == 15) {
                printf("┐");
            } else {
                printf("┬");
            }
        } else if (x == 1) {
            if (y == 1) {
                printf("└");
            } else if (y == 15) {
                printf("┘");
            } else {
                printf("┴");
            }
        } else {
            if (y == 1) {
                printf("├");
            } else if (y == 15) {
                printf("┤");
            } else {
                printf("┼");
            }
        }
    } else if (color == BLACK) {
        if (is_last) {
            printf("▲");
        } else {
            printf("●");
        }
    } else if (color == WHITE) {
        if (is_last) {
            printf("△");
        } else {
            printf("○");
        }
    }
}

// public
// printBoard: print the whole board according to gobang_board
void printBoard(void) {
    printf("  ");
    for (int j = 1; j <= 15; j ++) {
        printf(" %c", 'A' - 1 + j);
    }
    printf("\n");
    for (int i = BOARD_WIDTH; i >= 1; i--) {
        printf("%2d", i);
        for (int j = 1; j <= BOARD_WIDTH; j++) {
            // bool is_last = (i == getLastX() && j == getLastY());
            bool is_last = (gobang_board[i][j].order == getCntMan());
            printBoardCell(i, j, gobang_board[i][j].color, is_last);
        }
        printf("\n");
    }
}

// public
// placeMan: place a man at (x, y) of color
void placeMan(int x, int y, int color) {
    if (gobang_board[x][y].color == NOMAN) {
        cnt_man++;
        gobang_board[x][y].color = color;
        gobang_board[x][y].order = cnt_man;
        order_of_man[cnt_man] = gobang_board[x][y];
    }
}

// public
// removeLastMan: remove the last man on the board
void removeLastMan(void) {
    if (cnt_man) {
        int x = getLastX();
        int y = getLastY();
        gobang_board[x][y].color = NOMAN;
        gobang_board[x][y].order = 0;
        cnt_man--;
    }
}

