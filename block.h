#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include <vector>
#include "observer.h"

class Block : public Observer {
    int row;
    int col;
  public:
    // add methods
    // add public method/accessor for getting the block type, 
    // similar to getState in the example
};

#endif
