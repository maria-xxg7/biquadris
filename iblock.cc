#include "iblock.h"

IBlock::IBlock() : Block() {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '}, 
              {'I', 'I', 'I', 'I'}};
}

void IBlock::rotateBlockCW() {
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
