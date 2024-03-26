#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include "cell.h"
#include "block.h"
#include "textdisplay.h"
using namespace std;

class Board {
  vector<vector<Cell>> theBoard;
  const int boardWidth = 11, boardHeight = 15;
  int level, curScore, highScore;
  bool lose;
  BlockType nextBlock, curBlock;
  TextDisplay *td;
  //GraphicsDisplay *gd;

  void clearBoard();

  public:
    Board();
    ~Board();

    void init(); // initializes board

    // based on level, will decide next block and update field as well as
    // display in the next block region (maybe update text display, and 
    // update the block level based on cur level)
    void getNext(); 
    // places block at the top left hand corner, checks loose cond if
    // cannot fit
    void placeBlock();
    // for each move in command, will update the block before moving 
    void moveBlock(string move); 
    // must be called to make each move, checks lose cond if exceeds height
    // before actually putting it down 
    void dropBlock();

    // given row, checks if that line should be cleared
    bool checkLineClear(int row);
    // clears specified row, updates high and cur score and checks if 
    // blocks are cleards 
    void lineClear(int row);
    // called in place and drop
    bool isLose();
    
    friend ostream &operator<<(ostream &out, const Board &b);
};

#endif
