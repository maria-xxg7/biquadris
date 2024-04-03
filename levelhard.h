#include "blockgenerator.h"

class LevelHard: public BlockGenerator {
  bool random = true;
  string filename;
  int counter = 0;
  public:
    LevelHard(int level, string filename = "");
    void newMove(shared_ptr<Board> b) override; 
};
