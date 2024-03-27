#include "block.h"

Block::Block() : curRotation {RotateCW::Degree0}, config {} {}

vector<vector<char>> Block::getConfig() const {
    return config;
}

// shared_ptr<Cell> Block::getBlock() const {
//   return theBlock;
// }

/*
ostream &operator<<(ostream &out, const Block &b) {
  for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        out << b.config[i][j];
      }
      cout << endl;
    }
  return out;
}
*/

