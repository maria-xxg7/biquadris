#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include "block.h"
#include "board.h"

class Player {
    bool playerNum;
    int level;
    BlockType nextBlock;
    Board *playerBoard;
    Player(bool playerNum, int level, Board &b);
    ~Player();

  public:
    bool validMove(Board &b, bool playerTurn, string move);
    virtual bool newMove(Board &b, bool playerTurn) = 0;
    // level up and level down be decalred here i think
};

#endif
