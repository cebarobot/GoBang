/**********************************************
 * file: wuziqi.cpp
 * author: ceba(xuzefan)
 * student ID: 2018K8009929037
 * mail: xuzefan18@mails.ucas.ac.cn
**********************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BOARD_WIDTH 17
#define BOARD_SIZE 1

// data structure

struct GBcell {
    int color;          // 0 for none, 1 for black, 2 for white
    int id;
    int x, y;
};

int computerFirst = 0;
struct GBcell GBboard[BOARD_WIDTH][BOARD_WIDTH];
int moveCnt = 1;

// Funcitons

void printBoard();
void GBmove(int color, int x, int y);
void playerMove();
void computerMove();

int main() {
    char tmpStr[50];
    printf("Hello, welcome to ceba's gobang!\n");
    printf("Which color of pieces do you want to use, black or white? (b/w):");
    scanf("%s", tmpStr);
    if (tmpStr[0] == 'b' || tmpStr[0] == 'B') {
        computerFirst = 0;
        printf("You will use black pieces and move first.\n");
    } else {
        computerFirst = 1;
        printf("You will use white pieces and move second.\n");
    }
    printf("Now the game start.\n");
    printBoard();
    // if (computerFirst) {
    //     while (moveCnt <= BOARD_SIZE) {
    //         computerMove();
    //         moveCnt ++;
    //         printBoard();
    //         playerMove();
    //         moveCnt ++;
    //         printBoard();
    //     }
    // } else {
    //     while (moveCnt <= BOARD_SIZE) {
    //         playerMove();
    //         moveCnt ++;
    //         printBoard();
    //         computerMove();
    //         moveCnt ++;
    //         printBoard();
    //     }
    // }
    GBmove(1, 'H' - 'A' + 1, 8);
    printBoard();
    GBmove(2, 'H' - 'A' + 1, 9);
    printBoard();
    GBmove(1, 'H' - 'A' + 1, 7);
    printBoard();
    GBmove(2, 'G' - 'A' + 1, 9);
    printBoard();
    GBmove(1, 'I' - 'A' + 1, 8);
    printBoard();
    GBmove(2, 'E' - 'A' + 1, 9);
    printBoard();
    return 0;
}

void GBmove(int color, int x, int y) {
    if (GBboard[x][y].color){
        return;
    }
    GBboard[x][y].color = color;
    GBboard[x][y].id = moveCnt;
    moveCnt ++;
}

void printBoard() {
    printf("  ");
    for (int i = 1; i <= 15; i ++) {
        printf(" %c", 'A' - 1 + i);
    }
    printf("\n");
    for (int j = 15; j >= 1; j --) {
        printf("%2d", j);
        for (int i = 1; i <= 15 ; i ++) {
            if (i == 1) {
                printf(" ");
            } else {
                printf("─");
            }
            if (GBboard[i][j].color == 1) {
                if (GBboard[i][j].id == moveCnt - 1) {
                    printf("▲");
                } else {
                    printf("●");
                }
            } else if (GBboard[i][j].color == 2) {
                if (GBboard[i][j].id == moveCnt - 1) {
                    printf("△");
                } else {
                    printf("○");
                }
            } else {
                if (j == 15) {
                    if (i == 1) {
                        printf("┌");
                    } else if (i == 15) {
                        printf("┐");
                    } else {
                        printf("┬");
                    }
                } else if (j == 1) {
                    if (i == 1) {
                        printf("└");
                    } else if (i == 15) {
                        printf("┘");
                    } else {
                        printf("┴");
                    }
                } else {
                    if (i == 1) {
                        printf("├");
                    } else if (i == 15) {
                        printf("┤");
                    } else {
                        printf("┼");
                    }
                }
            }
            
        }
        printf("\n");
    }
    return;
}

void playerMove() {
    
}
void computerMove() {
}