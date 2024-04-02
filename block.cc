#include "block.h"

Block::Block() : curRotation {RotateCW::Degree0}, config {} {}

vector<vector<char>> Block::getConfig() {
    return config;
}

RotateCW Block::getRotation() const {
    return RotateCW::Degree0;
}

vector<int> Block::getLeftCorner() {
    return vector<int> {3, 0};
}

void Block::setConfig(vector<vector<char>> cf) {
  config = cf;
}

void Block::setRotation(RotateCW rotation) {
  curRotation = rotation;
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

ostream &operator<<(ostream &out, Block &b) {
  vector<vector<char>> blockConfig = b.getConfig();
  for (int i = 2; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        out << blockConfig[i][j];
      }
      cout << endl;
    }
  return out;
}


