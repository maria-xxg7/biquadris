#include "player.h"

class LevelOne: public Player {
  string filename;
  int counter = 0;
  LevelOne(bool playerNum, int level, Board &b, string filename);
  public:
    void newMove(Board &b, bool playerTurn) override; 
};
