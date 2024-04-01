#include "blockgenerator.h"

class LevelHard: public BlockGenerator {
  bool random = true;
  string filename;
  int counter = 0;
  LevelHard(bool playerNum, int level, Board &b, string filename = "");
  public:
    void newMove(Board &b, bool playerTurn) override; 
};
