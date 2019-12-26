#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "front.h"

// public
// inputYesNo: add an Yes/No checker
int inputYesNo(char * msg_str, int dflt_value) {
    while (1) {
        printf("%s ", msg_str);
        if (dflt_value == YES) {
            printf("(Y/n): ");
        } else if (dflt_value == NO) {
            printf("(y/N): ");
        } else {
            printf("(y/n): ");
        }

        char buff_str[100];
        char * buff = fgets(buff_str, sizeof(buff), stdin);
        int len = strlen(buff);
        if (len <= 1) {
            if (dflt_value == YES) {
                return YES;
            } else if (dflt_value == NO) {
                return NO;
            }
        } else if (buff[0] == 'Y' || buff[0] == 'y') {
            return YES;
        } else if (buff[0] == 'N' || buff[0] == 'n') {
            return NO;
        }

        printf("I can't understand your input, please try again.\n");
    }
}

// inputStone: get the coordinate of a stone from the standard input
void inputStone(char * msg_str, int * xx, int * yy) {
    while (1) {
        printf("%s: ", msg_str);
        char buff_str[100];
        char * buff = fgets(buff_str, sizeof(buff), stdin);
        int len = strlen(buff);

        int flg_x = 0, flg_y = 0;
        int xn = 0, yn = 0;
        for (int i = 0; i < len; i++) {
            if (flg_x != 2 && isdigit(buff[i])) {
                if (flg_x == 0) {
                    flg_x = 1;
                }
                xn = xn * 10 + buff[i] - '0';
            } else if (flg_y != 2 && buff[i] >= 'a' && buff[i] <= 'o') {
                if (flg_x == 1) {
                    flg_x = 2;
                }
                if (flg_y == 0) {
                    flg_y = 2;
                }
                yn = buff[i] - 'a' + 1;
            } else if (flg_y != 2 && buff[i] >= 'A' && buff[i] <= 'O') {
                if (flg_x == 1) {
                    flg_x = 2;
                }
                if (flg_y == 0) {
                    flg_y = 2;
                }
                yn = buff[i] - 'A' + 1;
            } else if (isspace(buff[i])) {
                continue;
            } else {
                break;
            }
        }
        if (xn >= 1 && xn <= 15 && yn >= 1 && yn <= 15) {
            (* xx) = xn;
            (* yy) = yn;
            return;
        }
        
        printf("I can't understand your input, please try again.\n");
    }
}