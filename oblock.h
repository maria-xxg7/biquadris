#ifndef __OBLOCK_H__
#define __OBLOCK_H__
#include "block.h"

class OBlock : public Block {
  public:
    OBlock(); // ctor
    void rotateBlockCW() override;    
    void rotateBlockCCW() override; 
};

#endif
