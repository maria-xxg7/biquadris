#include "oblock.h"

OBlock::OBlock() : Block() {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {'O', 'O', ' ', ' '}, 
              {'O', 'O', ' ', ' '}};
}

void OBlock::rotateBlockCW() {
    if (curRotation == RotateCW::Degree0) {
        curRotation = RotateCW::Degree90;
    } else if (curRotation == RotateCW::Degree90) {
        curRotation = RotateCW::Degree180;
    } else if (curRotation == RotateCW::Degree180) {
        curRotation = RotateCW::Degree270;
    } else {
        curRotation = RotateCW::Degree0;
    }
}    
void OBlock::rotateBlockCCW() {
    if (curRotation == RotateCW::Degree0) {
        curRotation = RotateCW::Degree270;
    } else if (curRotation == RotateCW::Degree90) {
        curRotation = RotateCW::Degree0;
    } else if (curRotation == RotateCW::Degree180) {
        curRotation = RotateCW::Degree90;
    } else {
        curRotation = RotateCW::Degree180;
    }
}
