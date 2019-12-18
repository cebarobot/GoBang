// Constant
#define BOARD_WIDTH 15
#define BOARD_SIZE 225

#define NOMAN 0
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

// getCntMan: get the number of men on the board
int getCntMan(void);

// getColor: get color of man at (x, y)
int getColor(int x, int y);

// getOrder: get order of man at (x, y)
int getOrder(int x, int y);

// getLastX: get the x of last man
int getLastX(void);

// getLastY: get the y of last man
int getLastY(void);

// getLastColor: get the color of last man
int getLastColor(void);

// printBoard: print the whole board according to gobang_board
void printBoard(void);

// placeMan: place a man at (x, y) of color
void placeMan(int x, int y, int color);

// removeLastMan: remove the last man on the board
void removeLastMan(void);