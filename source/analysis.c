#include <stdio.h>
#include <string.h>

#include "analysis.h"
#include "board.h"

typedef unsigned int uint;

const int dx[MAX_FULL_DIR] = { 1,  1,  0, -1, -1, -1,  0,  1};
const int dy[MAX_FULL_DIR] = { 0,  1,  1,  1,  0, -1, -1, -1};

// public
// printAnalysisResult: print the array analysis_result
void printAnalysisResult(int analysis_result[MAX_KIND]) {
    printf("------------------长连：%d\n", analysis_result[LONG]);
    printf("------------------连五：%d\n", analysis_result[FIVE]);
    printf("------------------活四：%d\n", analysis_result[FOUR]);
    printf("------------------冲四：%d\n", analysis_result[FOUR_B]);
    printf("------------------活三：%d\n", analysis_result[THREE]);
    printf("------------------眠三：%d\n", analysis_result[THREE_B]);
    printf("------------------活二：%d\n", analysis_result[TWO]);
    printf("------------------眠二：%d\n", analysis_result[TWO_B]);
}


/**
 * the hash code rule:
 * 2 bits for one stone
 * including the start stone
 * 00(0) for different color or wall
 * 01(1) for same color
 * 11(3) for nostone
**/

// private
// lineHash: cnt the hash value of one line start at (x, y), in direction dir
// return the length of hash value
uint lineHash(int x, int y, int dir, int role) {
    uint result = 0;
    for (int i = 0; i < 6; i++) {
        if (getColor(x, y) == role) {
            result = result + (1 << (2 * i));
        } else if (getColor(x, y) == NOSTONE) {
            result = result + (3 << (2 * i));
        }
        x += dx[dir];
        y += dy[dir];
    }
    return result;
}

// checkPattern* 

// private
// tryMove: try to place a stone at x, y
// return 1 for it is ok to make such a move
int tryMove(int x, int y, int role) {
    // printf("====tryMove=========%c%d.\n", y + 'A' - 1, x);
    if (getColor(x, y) != NOSTONE) {
        return 0;
    }
    placeStone(x, y, role);

    int analysis_result[MAX_KIND];
    memset(analysis_result, 0, sizeof(analysis_result));
    analysisPoint(analysis_result, x, y);
    int tmp = checkForbiddenMove(analysis_result, role);
    removeLastStone();
    if (tmp == 1) {
        return 0;
    }
    return 1;
}

// private
// checkPatternLong: check pattern of long 
// return 1 for 1 long Overline
int checkPatternLong(int hash_low, int hash_high) {
    // ******
    // |*|*****
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 12) == 1365) {
        return 1;
    }
    // *|*|****
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 10) == 341) {
        return 1;
    }
    // **|*|***
    if (hash_low % (1 << 6) == 21 && hash_high % (1 << 8) == 85) {
        return 1;
    }
    // ***|*|**
    if (hash_low % (1 << 8) == 85 && hash_high % (1 << 6) == 21) {
        return 1;
    }
    // ****|*|*
    if (hash_low % (1 << 10) == 341 && hash_high % (1 << 4) == 5) {
        return 1;
    }
    // *****|*|
    if (hash_low % (1 << 12) == 1365 && hash_high % (1 << 2) == 1) {
        return 1;
    }

    return 0;
}

// private
// checkPatternFive: check pattern of Five 
// return 1 for 1 Five
int checkPatternFive(int hash_low, int hash_high) {
    // ******
    // |*|****
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 10) == 341) {
        return 1;
    }
    // *|*|***
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 8) == 85) {
        return 1;
    }
    // **|*|**
    if (hash_low % (1 << 6) == 21 && hash_high % (1 << 6) == 21) {
        return 1;
    }
    // ***|*|*
    if (hash_low % (1 << 8) == 85 && hash_high % (1 << 4) == 5) {
        return 1;
    }
    // ****|*|
    if (hash_low % (1 << 10) == 341 && hash_high % (1 << 2) == 1) {
        return 1;
    }

    return 0;
}

// private
// checkPatternFour: check pattern of four
// return 0 for no four, 1 for 1 FOUR_B, 2 for FOUR, 3 for double FOUR_B
int checkPatternFour(int x, int y, int dir, int hash_low, int hash_high) {
    // a****b
    // a|*|***b
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 8) == 85) {
        int tmp = 0;
        tmp += tryMove(x + dx[dir], y + dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        tmp += tryMove(x + 4 * dx[dir + 4], y + 4 * dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // a*|*|**b
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 6) == 21) {
        int tmp = 0;
        // try a
        tmp += tryMove(x + 2 * dx[dir], y + 2 * dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        // try b
        tmp += tryMove(x + 3 * dx[dir + 4], y + 3 * dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // a**|*|*b
    if (hash_low % (1 << 6) == 21 && hash_high % (1 << 4) == 5) {
        int tmp = 0;
        // try a
        tmp += tryMove(x + 3 * dx[dir], y + 3 * dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        // try b
        tmp += tryMove(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // a***|*|b
    if (hash_low % (1 << 8) == 85 && hash_high % (1 << 2) == 1) {
        int tmp = 0;
        tmp += tryMove(x + 4 * dx[dir], y + 4 * dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        tmp += tryMove(x + dx[dir + 4], y + dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }

    // ***a*
    // |*|**a*
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 10) == 469) {
        int tmp = 0;
        tmp += tryMove(x + 3 * dx[dir + 4], y + 3 * dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // *|*|*a*
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 8) == 117) {
        int tmp = 0;
        tmp += tryMove(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // **|*|a*
    if (hash_low % (1 << 6) == 21 && hash_high % (1 << 6) == 29) {
        int tmp = 0;
        tmp += tryMove(x + dx[dir + 4], y + dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // ***a|*|
    if (hash_low % (1 << 10) == 349 && hash_high % (1 << 2) == 1) {
        int tmp = 0;
        tmp += tryMove(x + dx[dir], y + dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }

    // *a***
    // |*|a***
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 10) == 349) {
        int tmp = 0;
        tmp += tryMove(x + dx[dir + 4], y + dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // *a|*|**
    if (hash_low % (1 << 6) == 29 && hash_high % (1 << 6) == 21) {
        int tmp = 0;
        tmp += tryMove(x + dx[dir], y + dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // *a*|*|*
    if (hash_low % (1 << 8) == 117 && hash_high % (1 << 4) == 5) {
        int tmp = 0;
        tmp += tryMove(x + 2 * dx[dir], y + 2 * dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // *a**|*|
    if (hash_low % (1 << 10) == 469 && hash_high % (1 << 2) == 1) {
        int tmp = 0;
        tmp += tryMove(x + 3 * dx[dir], y + 3 * dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }

    // **a**
    // |*|*a**
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 10) == 373) {
        int tmp = 0;
        tmp += tryMove(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // *|*|a**
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 8) == 93) {
        int tmp = 0;
        tmp += tryMove(x + dx[dir + 4], y + dy[dir + 4], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // **a|*|*
    if (hash_low % (1 << 8) == 93 && hash_high % (1 << 4) == 5) {
        int tmp = 0;
        tmp += tryMove(x + dx[dir], y + dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }
    // **a*|*|
    if (hash_low % (1 << 10) == 373 && hash_high % (1 << 2) == 1) {
        int tmp = 0;
        tmp += tryMove(x + 2 * dx[dir], y + 2 * dy[dir], getColor(x, y));
        // printf("-----tmp::::::%d\n", tmp);
        return tmp;
    }

    return 0;
}

// private
// tryMakeMoveFour: try to make a move of FOUR
// return the result of checkPatternFour
int tryMakeMoveFour(int nx, int ny, int dir, int role) {
    // printf("====tryMakeMoveFour=========%c%d.\n", ny + 'A' - 1, nx);
    if (tryMove(nx, ny, role)) {
        // printf("!!!!!!!dir = %d\n", dir);
        placeStone(nx, ny, role);
        int hash_1 = lineHash(nx, ny, dir, role);
        int hash_2 = lineHash(nx, ny, dir + 4, role);
        int tmp_4 = checkPatternFour(nx, ny, dir, hash_1, hash_2);
        removeLastStone();
        if (tmp_4 == 2) {
            return 2;
        } else if (tmp_4 == 1) {
            return 1;
        }
    }
    return 0;
}

// private
// checkPatternThree: check pattern of three
// return 0 for no three, 1 for 1 THREE_B, 2 for THREE, 3 for double THREE_B
int checkPatternThree(int x, int y, int dir, int hash_low, int hash_high) {
    int role = getColor(x, y);
    // ?***?
    // ?x**?
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 6) == 21) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 3 * dx[dir + 4], y + 3 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // ?*x*?
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 4) == 5) {
        int tmp;
        tmp = tryMakeMoveFour(x + 2 * dx[dir], y + 2 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // ?**x?
    if (hash_low % (1 << 6) == 21 && hash_high % (1 << 2) == 1) {
        int tmp;
        tmp = tryMakeMoveFour(x + 3 * dx[dir], y + 3 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }

    // **?*
    // x*?*
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 8) == 117) {
        int tmp;
        tmp = tryMakeMoveFour(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // *x?*
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 6) == 29) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // **?x
    if (hash_low % (1 << 8) == 93 && hash_high % (1 << 2) == 1) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    
    // *?**
    // x?**
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 8) == 93) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // *?x*
    if (hash_low % (1 << 6) == 29 && hash_high % (1 << 4) == 5) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // *?*x
    if (hash_low % (1 << 8) == 117 && hash_high % (1 << 2) == 1) {
        int tmp;
        tmp = tryMakeMoveFour(x + 2 * dx[dir], y + 2 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
    }

    // **??*
    // x*??*
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 10) == 501) {
        int tmp;
        tmp = tryMakeMoveFour(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 3 * dx[dir + 4], y + 3 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // *x??*
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 8) == 125) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // **??x
    if (hash_low % (1 << 10) == 381 && hash_high % (1 << 2) == 1) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 2 * dx[dir], y + 2 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
    }

    // *??**
    // x??**
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 10) == 381) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // *??x*
    if (hash_low % (1 << 8) == 125 && hash_high % (1 << 4) == 5) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 2 * dx[dir], y + 2 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // *??*x
    if (hash_low % (1 << 10) == 501 && hash_high % (1 << 2) == 1) {
        int tmp;
        tmp = tryMakeMoveFour(x + 2 * dx[dir], y + 2 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 3 * dx[dir], y + 3 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
    }

    // *?*?*
    // x?*?*
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 10) == 477) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 3 * dx[dir + 4], y + 3 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // *?x?*
    if (hash_low % (1 << 6) == 29 && hash_high % (1 << 6) == 29) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // *?*?x
    if (hash_low % (1 << 10) == 477 && hash_high % (1 << 2) == 1) {
        int tmp;
        tmp = tryMakeMoveFour(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveFour(x + 3 * dx[dir], y + 3 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
    }

    return 0;
}

/*
// private
// tryMakeMoveThree: try to make a move of THREE
// return the result of checkPatternThree
int tryMakeMoveThree(int nx, int ny, int dir, int role) {
    // printf("====tryMakeMoveThree=========%c%d.\n", ny + 'A' - 1, nx);
    if (tryMove(nx, ny, role)) {
        // printf("!!!!!!!dir = %d\n", dir);
        placeStone(nx, ny, role);
        int hash_1 = lineHash(nx, ny, dir, role);
        int hash_2 = lineHash(nx, ny, dir + 4, role);
        int tmp_3 = checkPatternThree(nx, ny, dir, hash_1, hash_2);
        removeLastStone();
        if (tmp_3 == 2) {
            return 2;
        } else if (tmp_3 == 1) {
            return 1;
        }
    }
    return 0;
}

// private
// checkPatternTwo: check pattern of two
// return 0 for no two, 1 for 1 TWO_B, 2 for TWO
int checkPatternTwo(int x, int y, int dir, int hash_low, int hash_high) {
    int role = getColor(x, y);
    // ??**??
    // ??x*??
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 4) == 5) {
        int tmp;
        tmp = tryMakeMoveThree(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveThree(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveThree(x + 2 * dx[dir], y + 2 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveThree(x + 3 * dx[dir + 4], y + 3 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }
    // ??*x??
    if (hash_low % (1 << 4) == 5 && hash_high % (1 << 2) == 1) {
        int tmp;
        tmp = tryMakeMoveThree(x + 2 * dx[dir], y + 2 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveThree(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveThree(x + 3 * dx[dir], y + 3 * dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        tmp = tryMakeMoveThree(x + 2 * dx[dir + 4], y + 2 * dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
    }

    // ?*?*?
    // ?x?*?
    if (hash_low % (1 << 2) == 1 && hash_high % (1 << 6) == 29) {
        int tmp;
        tmp = tryMakeMoveThree(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        if (tmp) {
            return tmp;
        }
        // tmp = tryMakeMoveThree(x + dx[dir], y + dy[dir], dir, role);
        // if (tmp) {
        //     return tmp;
        // }
        // tmp = tryMakeMoveThree(x + 3 * dx[dir + 4], y + 3 * dy[dir + 4], dir, role);
        // if (tmp) {
        //     return tmp;
        // }
    }
    // ?*?x?
    if (hash_low % (1 << 6) == 29 && hash_high % (1 << 2) == 1) {
        int tmp;
        tmp = tryMakeMoveThree(x + dx[dir], y + dy[dir], dir, role);
        if (tmp) {
            return tmp;
        }
        // tmp = tryMakeMoveThree(x + dx[dir + 4], y + dy[dir + 4], dir, role);
        // if (tmp) {
        //     return tmp;
        // }
        // tmp = tryMakeMoveThree(x + 3 * dx[dir], y + 3 * dy[dir], dir, role);
        // if (tmp) {
        //     return tmp;
        // }
    }

    // *??*
    // x??*
    // *??x

    // *???*
    // x???*
    // *???x
    return 0;
}
*/


// private
// checkPatternTwo: check pattern of two, only check TWO
// return 0 for no two, 1 for 1 TWO_B, 2 for TWO
int checkPatternTwo(int hash_low, int hash_high) {
    // **
    // ?**???
    // ?x*???
    if (hash_low % (1 << 4) == 13 && hash_high % (1 << 10) == 1013) {
        return 2;
    }
    // ?*x???
    if (hash_low % (1 << 6) == 53 && hash_high % (1 << 8) == 253) {
        return 2;
    }
    // ??**??
    // ??x*??
    if (hash_low % (1 << 6) == 61 && hash_high % (1 << 8) == 245) {
        return 2;
    }
    // ??*x??
    if (hash_low % (1 << 8) == 245 && hash_high % (1 << 6) == 61) {
        return 2;
    }
    // ???**?
    if (hash_low % (1 << 10) == 1013 && hash_high % (1 << 4) == 13) {
        return 2;
    }
    // ?*x???
    if (hash_low % (1 << 8) == 253 && hash_high % (1 << 6) == 53) {
        return 2;
    }

    // *?*
    // ?*?*??
    // ?x?*??
    if (hash_low % (1 << 2) == 13 && hash_high % (1 << 10) == 989) {
        return 2;
    }
    // ?*?x??
    if (hash_low % (1 << 8) == 221 && hash_high % (1 << 6) == 61) {
        return 2;
    }

    // ??*?*?
    // ??x?*?
    if (hash_low % (1 << 6) == 61 && hash_high % (1 << 8) == 221) {
        return 2;
    }
    // ??*?x?
    if (hash_low % (1 << 10) == 989 && hash_high % (1 << 2) == 13) {
        return 2;
    }

    // *??*
    // ?*??*?
    // ?x??*?
    if (hash_low % (1 << 4) == 13 && hash_high % (1 << 10) == 893) {
        return 2;
    }
    // ?*??x?
    if (hash_low % (1 << 10) == 893 && hash_high % (1 << 4) == 13) {
        return 2;
    }

    return 0;
}

// analysisPoint: analysis the number of different kind of stone patterns
void analysisPoint(int analysis_result[MAX_KIND], int x, int y) {
    // check color of point
    int role = getColor(x, y);
    if (role <= NOSTONE) {
        return;
    }

    // clear the analysis_result array
    // memset(analysis_result, 0, sizeof(int) * MAX_KIND);

    // get the hash code of all directions
    uint hash_dir[MAX_FULL_DIR];
    for (int i = 0; i < MAX_FULL_DIR; i++) {
        hash_dir[i] = lineHash(x, y, i, role);
        // printf("----------hash_dir[%d] = %u\n", i, hash_dir[i]);
    }

    // count the number of all stone partten
    for (int i = 0; i < MAX_DIR; i++) {
        // 长连
        analysis_result[LONG] += checkPatternLong(hash_dir[i], hash_dir[i + 4]);
        if (analysis_result[LONG] > 0) {
            continue;
        }
        // 连五
        analysis_result[FIVE] += checkPatternFive(hash_dir[i], hash_dir[i + 4]);
        if (analysis_result[FIVE] > 0) {
            continue;
        }
        // 四
        int tmp_4 = checkPatternFour(x, y, i, hash_dir[i], hash_dir[i + 4]);
        if (tmp_4 == 1) {
            analysis_result[FOUR_B] += 1;
            continue;
        } else if (tmp_4 == 2) {
            analysis_result[FOUR] += 1;
            continue;
        } else if (tmp_4 == 3) {
            analysis_result[FOUR_B] += 2;
            continue;
        }

        // 三
        int tmp_3 = checkPatternThree(x, y, i, hash_dir[i], hash_dir[i + 4]);
        if (tmp_3 == 1) {
            analysis_result[THREE_B] += 1;
            continue;
        } else if (tmp_3 == 2) {
            analysis_result[THREE] += 1;
            continue;
        }

        // 二
        // int tmp_2 = checkPatternTwo(x, y, i, hash_dir[i], hash_dir[i + 4]);
        int tmp_2 = checkPatternTwo(hash_dir[i], hash_dir[i + 4]);
        if (tmp_2 == 1) {
            analysis_result[TWO_B] += 1;
            continue;
        } else if (tmp_2 == 2) {
            analysis_result[TWO] += 1;
            continue;
        }
    }
}

// checkWin: check whether the player of the role win by checking the analysis_result
// return 1 for win, 0 for not win
int checkWin(int analysis_result[MAX_KIND], int role) {
    if (analysis_result[FIVE] > 0) {
        return 1;
    }
    if (role == WHITE && analysis_result[LONG] > 0) {
        return 1;
    }
    return 0;
}

// checkForbiddenMove: check whether the player make a forbidden move
// return 0 for ok, 1 for forbidden
int checkForbiddenMove(int analysis_result[MAX_KIND], int role) {
    if (role == WHITE) {
        return 0;
    }
    if (analysis_result[LONG]) {
        return 1;
    }
    if (analysis_result[FOUR] + analysis_result[FOUR_B] >= 2) {
        return 1;
    }
    if (analysis_result[THREE] >= 2) {
        return 1;
    }
    return 0;
}