#ifndef __blockGenerator_H__
#define __blockGenerator_H__
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include "PRNG.h"
#include "board.h"

class BlockGenerator {
    bool playerNum;
    int level;
    BlockType nextBlock;
  protected:
    BlockGenerator(bool playerNum, int level, Board &b);
    ~BlockGenerator();
    BlockType stringToBlock(char blockChar);

  public:
    virtual void newMove(Board &b, bool playerTurn) = 0;
    void levelUp(Board &b, bool playerTurn);
    void levelDown(Board &b, bool playerTurn);
};

#endif
