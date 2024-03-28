#include "tblock.h"

TBlock::TBlock() : Block() {
  config = {{' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {'T', 'T', 'T', ' '},
            {' ', 'T', ' ', ' '}};
}

void TBlock::rotateBlockCW() {
  if (curRotation == RotateCW::Degree0) {
    config = {{' ', ' ', ' ', ' '},
              {' ', 'T', ' ', ' '},
              {'T', 'T', ' ', ' '},
              {' ', 'T', ' ', ' '}};
    curRotation = RotateCW::Degree90;
  } else if (curRotation == RotateCW::Degree90) {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {' ', 'T', ' ', ' '},
              {'T', 'T', 'T', ' '}};
    curRotation = RotateCW::Degree180;
  } else if (curRotation == RotateCW::Degree180) {
    config = {{' ', ' ', ' ', ' '},
              {'T', ' ', ' ', ' '},
              {'T', 'T', ' ', ' '},
              {'T', ' ', ' ', ' '}};
    curRotation = RotateCW::Degree270;
  } else {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {'T', 'T', 'T', ' '},
              {' ', 'T', ' ', ' '}};
    curRotation = RotateCW::Degree0;
  }
}

void TBlock::rotateBlockCCW() {
  for (int i = 0; i < 3; ++i) {
    rotateBlockCW();
  }
}

vector<int> TBlock::getLeftCorner() {
    return vector<int> {3, 1};
}
