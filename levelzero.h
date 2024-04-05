#include "blockgenerator.h"

class LevelZero: public BlockGenerator{
  string filename;
  int counter = 0;
  public:
    LevelZero(string filename, int level = 0, int counter = 0);
    void newMove(shared_ptr<Board> b) override; 
};
