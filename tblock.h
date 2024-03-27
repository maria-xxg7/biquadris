#ifndef __TBLOCK_H__
#define __TBLOCK_H__
#include "block.h"

class TBlock : public Block {
  public:
    TBlock(); // constructor
    void rotateBlockCW() override;
    void rotateBlockCCW() override;
    vector<int> getLeftCorner() override;
};

#endif
