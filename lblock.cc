#include "lblock.h"

LBlock::LBlock() : Block() {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {' ', ' ', 'L', ' '}, 
              {'L', 'L', 'L', ' '}};
}

void LBlock::rotateBlockCW() {
    if(curRotation == RotateCW::Degree0) {
        config = {{' ', ' ', ' ', ' '},
                  {'L', ' ', ' ', ' '},
                  {'L', ' ', ' ', ' '}, 
                  {'L', 'L', ' ', ' '}};
        curRotation = RotateCW::Degree90;
    } else if (curRotation == RotateCW::Degree90) {
        config = {{' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '},
                  {'L', 'L', 'L', ' '}, 
                  {'L', ' ', ' ', ' '}};
        curRotation = RotateCW::Degree180;
    } else if (curRotation == RotateCW::Degree180) {
        config = {{' ', ' ', ' ', ' '},
                  {'L', 'L', ' ', ' '},
                  {' ', 'L', ' ', ' '}, 
                  {' ', 'L', ' ', ' '}};
        curRotation = RotateCW::Degree270;
    } else {
        config = {{' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '},
                  {' ', ' ', 'L', ' '}, 
                  {'L', 'L', 'L', ' '}};
        curRotation = RotateCW::Degree0;
    }
}    
void LBlock::rotateBlockCCW() {
    for (int i = 0; i < 3; ++i) {
        rotateBlockCW();
    }
}
