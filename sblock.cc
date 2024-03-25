#include "sblock.h"

SBlock::SBlock() : Block() {
  config = {{' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', 'S', 'S', ' '},
            {'S', 'S', ' ', ' '}};
}

void SBlock::rotateBlockCW() {
  if (curRotation == RotateCW::Degree0 || curRotation == RotateCW::Degree180) {
    config = {{' ', ' ', ' ', ' '},
              {'S', ' ', ' ', ' '},
              {'S', 'S', ' ', ' '},
              {' ', 'S', ' ', ' '}};
    curRotation = RotateCW::Degree90;
  } else if (curRotation == RotateCW::Degree90 || curRotation == RotateCW::Degree270) {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {' ', 'S', 'S', ' '},
              {'S', 'S', ' ', ' '}};
    curRotation = RotateCW::Degree180;
  }
}

void SBlock::rotateBlockCCW() {
  for (int i = 0; i < 3; ++i) {
    rotateBlockCW();
  }
}
