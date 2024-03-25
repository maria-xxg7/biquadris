#include "oblock.h"

OBlock::OBlock() : Block() {
    config = {{' ', ' ', ' ', ' '},
              {' ', ' ', ' ', ' '},
              {'O', 'O', ' ', ' '}, 
              {'O', 'O', ' ', ' '}};
}

void OBlock::rotateBlockCW() {
    return;
}    
void OBlock::rotateBlockCCW() {
    return;
}
