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
  // grid
  vector<vector<Cell>> theBoard;
  TextDisplay *td;
  GraphicsDisplay *gd;
  int level, curScore, highScore, blockScore;
  BlockType curBlock, nextBlock;
  bool lose = false;

  // move/drop block
  vector<vector<char>> lastConfig;
  vector<vector<int>> coords;
  vector<int> colHeights;
  int totalShift = 0; int totalDown = 0;
  int cellLevel = 0;
  RotateCW lastRotation;
  bool clear = true;
  bool heavyDrop = false;

  // special actions
  bool specialAction = false;
  bool isHeavy = false;
  bool isBlind = false;
  bool isObstacle = false;
  int numBlocksDropped = 0;

  int numMultiDrop = 0;

  // checks if the move is valid
  bool validMove(vector<vector<char>> *blockBlock, int shift, int down, bool place);

  // checks for lowest height cell can be dropped
  int findNextHeight(int row, int col);

  // check if any of the head cells are being removed
  bool checkHeads(int row);

  // reassign the block's head cell
  void reassignHead(int row);
  
  bool checkBlindCell(Cell &c);
  // create blocks
  class BlockFactory {
    public:
      static shared_ptr<Block> buildBlock(BlockType b);
  };

  public:
    Board(); // constructor
    ~Board(); // destructor

    void init(Xwindow &wd); // initializes board
    void clearBoard(); // reset the board
    bool isLose();
    
    // blocks
    BlockType getBlockType(); // get block type
    void setBlockType(BlockType b); // set block type
    string getNextType(); // TEMP FUNCTION FOR TESTING ONLY!!!!
    void setCurBlock(BlockType b);
    BlockType getCurBlockB();
    string getCurBlock(); // TEMP FUNCTION FOR TESTING ONLY!!!!
    bool finishedMove();
    void setBlind(bool isOn); 

    // levels
    int getLevel() const;
    void setLevel(int newLevel);

    // special actions:
    bool getSpecial();
    void setSpecial(bool isOn);
    bool getHeavy();
    void setHeavy(bool heavy);
    bool getObstacle();
    void setObstacle(bool obstacle);

    int getNumMultiDrop();
    void setNumMultiDrop(int n);
    
    // places/moves block based on move command
    void moveBlock(string move);

    void clearPlaced();

    // must be called after finishing moving a block, checks lose cond if exceeds height
    // before actually putting it down 
    void dropBlock();

    // given row, checks if that line should be cleared
    bool checkLineClear(int row);

    // clears specified row, updates high and cur score and checks if blocks are cleared
    void lineClear(int row);

    // blinds/unblinds player's board
    void blinding(bool blind);

    // updates current & high score
    void updateScore();
    
    friend ostream &operator<<(ostream &out, const Board &b);
};

#endif
