#ifndef __IBLOCK_H__
#define __IBLOCK_H__
#include "block.h"

class IBlock : public Block {
    public:
    IBlock(); // ctor
    void rotateBlockCW() override;    
    void rotateBlockCCW() override; 
};

#endif
