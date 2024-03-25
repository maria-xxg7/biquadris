#ifndef __SBLOCK_H__
#define __SBLOCK_H__
#include "block.h"

class SBlock : public Block {
  public:
    SBlock(); // constructor
    void rotateBlockCW() override;
    void rotateBlockCCW() override;
};

#endif
