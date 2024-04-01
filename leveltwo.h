#include "player.h"

class LevelTwo: public Player {
  LevelTwo(bool playerNum, int level, Board &b);
  public:
    void newMove(Board &b, bool playerTurn) override; 
};
