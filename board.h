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
#include "graphicsdisplay.h"
using namespace std;

class Board {
  vector<vector<Cell>> theBoard;
  int level, curScore, highScore, blockScore;
  bool lose = false;
  BlockType nextBlock;
  TextDisplay *td;
  GraphicsDisplay *gd;
  vector<vector<char>> lastConfig;
  vector<vector<int>> coords;
  int totalShift = 0; int totalDown = 0;
  bool clear = true;
  vector<int> colHeights;
  RotateCW lastRotation;
  bool isHeavy = false;
  bool isObstacle = false;

  // checks if the move is valid
  bool validMove(vector<vector<char>> *blockBlock, int shift, int down, bool place);

  int findNextHeight(int row, int col);

  bool checkHeads(int row);

  void reassignHead(int row);
  
  class BlockFactory {
    public:
      static shared_ptr<Block> buildBlock(BlockType b);
  };

  public:
    Board();
    ~Board();

    void init(Xwindow &wd); // initializes board

    void clearBoard();
    
    // TEMP FUNCTION FOR TESTING ONLY!!!!
    void setBlockType(BlockType b);

    int getLevel();

    void setLevel(int newLevel);

    bool getHeavy();

    void setHeavy(bool heavy);

    bool getObstacle();

    void setObstacle(bool obstacle);

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

    void updateScore();

    bool isLose() const;
    
    friend ostream &operator<<(ostream &out, const Board &b);
};

#endif
