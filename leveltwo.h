#include "blockgenerator.h"

class LevelTwo: public BlockGenerator {
  public:
    LevelTwo(int level = 2);
    void newMove(shared_ptr<Board> b) override; 
};
