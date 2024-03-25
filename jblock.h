#ifndef __JBLOCK_H__
#define __JBLOCK_H__
#include "block.h"

class JBlock : public Block {
    public:
    JBlock(); // ctor
    void rotateBlockCW() override;    
    void rotateBlockCCW() override; 
};

#endif
