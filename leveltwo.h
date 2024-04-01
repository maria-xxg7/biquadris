#include "blockgenerator.h"

class LevelTwo: public BlockGenerator {
  LevelTwo(bool playerNum, int level, Board &b);
  public:
    void newMove(Board &b, bool playerTurn) override; 
};
