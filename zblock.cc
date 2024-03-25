#include "zblock.h"

ZBlock::ZBlock() : Block() {
  config = {{' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {'Z', 'Z', ' ', ' '},
            {' ', 'Z', 'Z', ' '}};
}

void ZBlock::rotateBlockCW() {
  if (curRotation == RotateCW::Degree0 || curRotation == RotateCW::Degree180) {
    config = {{' ', ' ', ' ', ' '},
              {' ', 'Z', ' ', ' '},
              {'Z', 'Z', ' ', ' '},
              {'Z', ' ', ' ', ' '}};
    curRotation = RotateCW::Degree90;
  } else if (curRotation == RotateCW::Degree90 || curRotation == RotateCW::Degree270) {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {'Z', 'Z', ' ', ' '},
              {' ', 'Z', 'Z', ' '}};
    curRotation = RotateCW::Degree180;
  }
}

void ZBlock::rotateBlockCCW() {
  for (int i = 0; i < 3; ++i) {
    rotateBlockCW();
  }
}
