#ifndef __blockGenerator_H__
#define __blockGenerator_H__
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include "board.h"

class BlockGenerator {
  int level;
  protected:
    BlockGenerator(int level);
    BlockType stringToBlock(char blockChar);

  public:
    virtual void newMove(shared_ptr<Board> b) = 0;
};

#endif
