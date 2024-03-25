#ifndef __LBLOCK_H__
#define __LBLOCK_H__
#include "block.h"

class LBlock : public Block {
  public:
    LBlock(); // ctor
    void rotateBlockCW() override;    
    void rotateBlockCCW() override; 
};

#endif
