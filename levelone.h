#include "player.h"

class LevelOne: public Player {
  LevelOne(bool playerNum, int level, Board &b);
  public:
    void newMove(Board &b, bool playerTurn) override; 
};
