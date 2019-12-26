// Constant
#define BOARD_WIDTH 15
#define BOARD_SIZE 225

#define WALL -1
#define NOSTONE 0
#define BLACK 1
#define WHITE 2

// Data structure
typedef struct boardCell {
    int color;          // 0 for none, 1 for black, 2 for white
    int order;
    int x, y;
} boardCell;

// boardInit: initialize the board
void boardInit(void);

// inBoard: check whether the coordinate is in the board
int inBoard(int x, int y);

// getCntStone: get the number of men on the board
int getCntStone(void);

// getColor: get color of stone at (x, y)
int getColor(int x, int y);

// getOrder: get order of stone at (x, y)
int getOrder(int x, int y);

// getLastX: get the x of last stone
int getLastX(void);

// getLastY: get the y of last stone
int getLastY(void);

// getLastColor: get the color of last stone
int getLastColor(void);

// printBoard: print the whole board according to gobang_board
void printBoard(void);

// placeStone: place a stone at (x, y) of color
void placeStone(int x, int y, int color);

// removeLastStone: remove the last stone on the board
void removeLastStone(void);