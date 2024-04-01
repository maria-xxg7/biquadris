#include "player.h"

class LevelFour: public Player {
  bool random = true;
  string filename;
  int counter = 0;
  LevelFour(bool playerNum, int level, Board &b, string filename = "");
  public:
    void newMove(Board &b, bool playerTurn) override; 
};

