#include "player.h"

class LevelOne: public Player {
  string filename;
  LevelOne(bool playerNum, int level, Board &b, string filename);
  public:
    void newMove(Board &b, bool playerTurn) override; 

};
