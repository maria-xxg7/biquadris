#include "jblock.h"

JBlock::JBlock() : Block() {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {'J', ' ', ' ', ' '}, 
              {'J', 'J', 'J', ' '}};
}

void IBlock::rotateBlockCW() {
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
    } else if (curRotation == RotateCW::Degree180)
}    
void IBlock::rotateBlockCCW() {
    if(curRotation == RotateCW::Degree90 || curRotation == RotateCW::Degree270) {
        config = {{'I', ' ', ' ', ' '},
                  {'I', ' ', ' ', ' '},
                  {'I', ' ', ' ', ' '}, 
                  {'I', ' ', ' ', ' '}};
    } else {
        config = {{' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '}, 
                  {'I', 'I', 'I', 'I'}};
    }
}
