#include "blockgenerator.h"

class LevelOne: public BlockGenerator {
  public:
    LevelOne(int level = 1);
    void newMove(shared_ptr<Board> b) override; 
};
