#include "blockgenerator.h"

class LevelZero: public BlockGenerator{
  string filename;
  int counter = 0;
  LevelZero(bool playerNum, int level, Board &b, string filename);
  public:
    void newMove(Board &b, bool playerTurn) override; 
};
