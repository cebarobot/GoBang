#ifndef __ANALYSIS__
#define __ANALYSIS__

// kinds of stones
#define MAX_KIND 13

#define LONG        1   // 长连
#define FIVE        2   // 连五
#define FOUR        3   // 活四
#define FOUR_B      4   // 冲四
#define THREE       5   // 活三
#define THREE_B     6   // 眠三
#define TWO         7   // 活二
#define TWO_B       8   // 眠二
#define FOUR_D      9   // 双四
#define FOUR_THREE  10  // 四-三
#define THREE_D     11  // 双活三

// directions
#define MAX_FULL_DIR 8
#define MAX_DIR 4

extern const int dx[MAX_FULL_DIR];
extern const int dy[MAX_FULL_DIR];

// public
// printAnalysisResult: print the array analysis_result
void printAnalysisResult(int analysis_result[MAX_KIND], int role);

// analysisPoint: analysis the number of different kind of stone patterns
void analysisPoint(int analysis_result[MAX_KIND], int x, int y);

// checkWin: check whether the player of the role win by checking the analysis_result
// return 1 for win, 0 for not win
int checkWin(int analysis_result[MAX_KIND], int role);

// checkForbiddenMove: check whether the player make a forbidden move
// return 0 for ok, 1 for forbidden
int checkForbiddenMove(int analysis_result[MAX_KIND], int role);

// public
// analysisBoard: analysis the Board and count the number of stone patterns
void analysisBoard(int role, int analysis_result[MAX_KIND], int analysis_result_2[MAX_KIND]);

#endif