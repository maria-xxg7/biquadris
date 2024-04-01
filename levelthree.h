#include "player.h"

class LevelThree: public Player {
  bool random = true;
  string filename;
  int counter = 0;
  LevelThree(bool playerNum, int level, Board &b, string filename = "");
  public:
    void newMove(Board &b, bool playerTurn) override; 
};
