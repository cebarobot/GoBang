// Constant
#define BOARD_WIDTH 15
#define BOARD_SIZE 225

#define NOPIECE 0
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

// getCntPiece: get the number of men on the board
int getCntPiece(void);

// getColor: get color of piece at (x, y)
int getColor(int x, int y);

// getOrder: get order of piece at (x, y)
int getOrder(int x, int y);

// getLastX: get the x of last piece
int getLastX(void);

// getLastY: get the y of last piece
int getLastY(void);

// getLastColor: get the color of last piece
int getLastColor(void);

// printBoard: print the whole board according to gobang_board
void printBoard(void);

// placePiece: place a piece at (x, y) of color
void placePiece(int x, int y, int color);

// removeLastPiece: remove the last piece on the board
void removeLastPiece(void);