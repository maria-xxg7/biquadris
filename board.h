#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <memory>
#include "cell.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "textdisplay.h"
using namespace std;

class Board {
  vector<vector<Cell>> theBoard;
  vector<vector<shared_ptr<Cell>>> allBlocks;
  const int boardWidth = 11, boardHeight = 15, reserved = 3, blockDim = 4;
  int level, curScore, highScore;
  bool lose = false;
  BlockType nextBlock;
  TextDisplay *td;
  //GraphicsDisplay *gd;
  vector<vector<char>> lastConfig;
  vector<vector<int>> coords;
  int totalShift = 0; int totalDown = 0;
  bool clear = true;
  vector<int> colHeights;
  RotateCW lastRotation;

  void clearBoard();
  
  int findNextHeight(int row, int col);
  
  class BlockFactory {
    public:
      static unique_ptr<Block> buildBlock(BlockType b);
  };

  public:
    Board();
    ~Board();

    void init(); // initializes board

    // based on level, will decide next block and update field as well as
    // display in the next block region (maybe update text display, and 
    // update the block level based on cur level)
    void getNext(); 
    

    // TEMP FUNCTION FOR TESTING ONLY!!!!
    void setBlockType(BlockType b);

    bool validMove(vector<vector<char>> *blockBlock, int shift, int down, bool place);

    // places block at the top left hand corner, checks loose cond if
    // cannot fit
    void moveBlock(string move);
    // for each move in command, will update the block before moving 
    // void moveBlock(string move); 
    // must be called to make each move, checks lose cond if exceeds height
    // before actually putting it down 
    void dropBlock();

    // given row, checks if that line should be cleared
    bool checkLineClear(int row);
    // clears specified row, updates high and cur score and checks if 
    // blocks are cleards 
    void lineClear(int row);
    
    friend ostream &operator<<(ostream &out, const Board &b);
};

#endif
