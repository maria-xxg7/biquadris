#include "block.h"

Block::Block() : curRotation {RotateCW::Degree0}, config {} {}

vector<vector<char>> Block::getConfig() const {
    return config;
}

RotateCW Block::getRotation() const {
    return curRotation;
}

vector<int> Block::getLeftCorner() {
    return vector<int> {3, 0};
}

string Block::getRotationString() const {
  if (curRotation == RotateCW::Degree0) {
    return "Degree0";
  } else if (curRotation == RotateCW::Degree90) {
    return "Degree90";
  } else if (curRotation == RotateCW::Degree180) {
    return "Degree180";
  } else {
    return "Degree270";
  }
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

