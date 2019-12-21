#include <stdio.h>
#include <stdbool.h>

#include "board.h"

// private
// The whole board
boardCell gobang_board[BOARD_WIDTH + 1][BOARD_WIDTH + 1];

// The order of placed stone
boardCell order_of_stone[BOARD_SIZE + 10];
int cnt_stone = 0;

// public
// boardInit: initialize the board
void boardInit(void) {
    for (int i = 1; i <= BOARD_WIDTH; i++) {
        for (int j = 1; j <= BOARD_WIDTH; j++) {
            gobang_board[i][j].color = NOSTONE;
            gobang_board[i][j].order = 0;
            gobang_board[i][j].x = i;
            gobang_board[i][j].y = j;
        }
    }
}

// public
// getCntStone: get the number of men on the board
int getCntStone(void) {
    return cnt_stone;
}

// public
// getColor: get color of stone at (x, y)
int getColor(int x, int y) {
    return gobang_board[x][y].color;
}

// public
// getOrder: get order of stone at (x, y)
int getOrder(int x, int y) {
    return gobang_board[x][y].order;
}

// public
// getLastX: get the x of last stone
int getLastX(void) {
    return order_of_stone[cnt_stone].x;
}

// public
// getLastY: get the y of last stone
int getLastY(void) {
    return order_of_stone[cnt_stone].y;
}

// public
// getLastColor: get the color of last stone
int getLastColor(void) {
    return order_of_stone[cnt_stone].color;
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
    if (color == NOSTONE) {
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
    for (int i = BOARD_WIDTH; i >= 1; i--) {
        printf("\e[47m\e[30m %2d", i);
        for (int j = 1; j <= BOARD_WIDTH; j++) {
            // bool is_last = (i == getLastX() && j == getLastY());
            bool is_last = (gobang_board[i][j].order == getCntStone());
            printBoardCell(i, j, gobang_board[i][j].color, is_last);
        }
        printf(" \e[0m\n");
    }
    printf("\e[47m\e[30m   ");
    for (int j = 1; j <= 15; j ++) {
        printf(" %c", 'A' - 1 + j);
    }
    printf(" \e[0m\n");
}

// public
// placeStone: place a stone at (x, y) of color
void placeStone(int x, int y, int color) {
    if (x < 1 || x > 15 || y < 1 || y > 15) {
        return;
    }
    if (gobang_board[x][y].color == NOSTONE) {
        cnt_stone++;
        gobang_board[x][y].color = color;
        gobang_board[x][y].order = cnt_stone;
        order_of_stone[cnt_stone] = gobang_board[x][y];
    }
}

// public
// removeLastStone: remove the last stone on the board
void removeLastStone(void) {
    if (cnt_stone) {
        int x = getLastX();
        int y = getLastY();
        gobang_board[x][y].color = NOSTONE;
        gobang_board[x][y].order = 0;
        cnt_stone--;
    }
}

