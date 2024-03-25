#ifndef __ZBLOCK_H__
#define __ZBLOCK_H__
#include "block.h"

class ZBlock : public Block {
  public:
    ZBlock(); // constructor
    void rotateBlockCW() override;
    void rotateBlockCCW() override;
};

#endif
