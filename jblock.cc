#include "jblock.h"

JBlock::JBlock() : Block() {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {'J', ' ', ' ', ' '}, 
              {'J', 'J', 'J', ' '}};
}

void JBlock::rotateBlockCW() {
    if(curRotation == RotateCW::Degree0) {
        config = {{' ', ' ', ' ', ' '},
                  {'J', 'J', ' ', ' '},
                  {'J', ' ', ' ', ' '}, 
                  {'J', ' ', ' ', ' '}};
        curRotation = RotateCW::Degree90;
    } else if (curRotation == RotateCW::Degree90) {
        config = {{' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '},
                  {'J', 'J', 'J', ' '}, 
                  {' ', ' ', 'J', ' '}};
        curRotation = RotateCW::Degree180;
    } else if (curRotation == RotateCW::Degree180) {
        config = {{' ', ' ', ' ', ' '},
                  {' ', 'J', ' ', ' '},
                  {' ', 'J', ' ', ' '}, 
                  {'J', 'J', ' ', ' '}};
        curRotation = RotateCW::Degree270;
    } else {
        config = {{' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '},
                  {'J', ' ', ' ', ' '}, 
                  {'J', 'J', 'J', ' '}};
        curRotation = RotateCW::Degree0;
    }
}    
void JBlock::rotateBlockCCW() {
    for (int i = 0; i < 3; ++i) {
        rotateBlockCW();
    }
}
