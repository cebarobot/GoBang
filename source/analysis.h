// kinds of stones
#define MAX_KIND 9

#define LONG    1   // 长连
#define FIVE    2   // 连五
#define FOUR    3   // 活四
#define FOUR_B  4   // 冲四
#define THREE   5   // 活三
#define THREE_B 6   // 眠三
#define TWO     7   // 活二
#define TWO_B   8   // 眠二

// directions
#define MAX_FULL_DIR 8
#define MAX_DIR 4

// public
// printAnalysisResult: print the array analysis_result
void printAnalysisResult(int analysis_result[MAX_KIND]);

// // analysisBoard: analysis the whole board and count the number of different kind of stones
// void analysisBoard(int analysis_result[MAX_KIND], int x, int y);

// analysisPoint: analysis the number of different kind of stone patterns
void analysisPoint(int analysis_result[MAX_KIND], int x, int y);

// checkWin: check whether the player of the role win by checking the analysis_result
// return 1 for win, 0 for not win
int checkWin(int analysis_result[MAX_KIND], int role);

// checkForbiddenMove: check whether the player make a forbidden move
// return 0 for ok, 1 for forbidden
int checkForbiddenMove(int analysis_result[MAX_KIND], int role);