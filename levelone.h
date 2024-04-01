#include "blockgenerator.h"

class LevelOne: public BlockGenerator {
  LevelOne(bool playerNum, int level, Board &b);
  public:
    void newMove(Board &b, bool playerTurn) override; 
};
