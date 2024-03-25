#include "iblock.h"

IBlock::IBlock() : Block() {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '}, 
              {'I', 'I', 'I', 'I'}};
}

void IBlock::rotateBlockCW() {
    if(curRotation == RotateCW::Degree90 || curRotation == RotateCW::Degree270) {
        config = {{' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '}, 
                  {'I', 'I', 'I', 'I'}};
        curRotation == RotateCW::Degree90 ? curRotation = RotateCW::Degree180 : curRotation = RotateCW::Degree0;
    } else {
        config = {{'I', ' ', ' ', ' '},
                  {'I', ' ', ' ', ' '},
                  {'I', ' ', ' ', ' '}, 
                  {'I', ' ', ' ', ' '}};
        curRotation == RotateCW::Degree0 ? curRotation = RotateCW::Degree90 : curRotation = RotateCW::Degree270;
    }
}    
void IBlock::rotateBlockCCW() {
    if(curRotation == RotateCW::Degree90 || curRotation == RotateCW::Degree270) {
        config = {{' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '},
                  {' ', ' ', ' ', ' '}, 
                  {'I', 'I', 'I', 'I'}};
        curRotation == RotateCW::Degree90 ? curRotation = RotateCW::Degree0 : curRotation = RotateCW::Degree180;
    } else {
        config = {{'I', ' ', ' ', ' '},
                  {'I', ' ', ' ', ' '},
                  {'I', ' ', ' ', ' '}, 
                  {'I', ' ', ' ', ' '}};
        curRotation == RotateCW::Degree0 ? curRotation = RotateCW::Degree270 : curRotation = RotateCW::Degree90;
    }
}
