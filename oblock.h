#ifndef __OBLOCK_H__
#define __OBLOCK_H__
#include "block.h"

class OBlock : public Block {
  public:
    BlockType bType() override;
    void rotateBlock(bool clockwise) override;
    void shiftBlock(string dir) override;
};

#endif
