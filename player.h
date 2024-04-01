#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <fstream>
#include <sstream>
#include "block.h"
#include "board.h"

class Player {
    bool playerNum;
    int level;
    BlockType nextBlock;
    Board *playerBoard;
  protected:
    Player(bool playerNum, int level, Board &b);
    ~Player();
    BlockType stringToBlock(char blockChar);

  public:
    virtual void newMove(Board &b, bool playerTurn) = 0;
    void levelUp(Board &b, bool playerTurn);
    void levelDown(Board &b, bool playerTurn);
};

#endif
