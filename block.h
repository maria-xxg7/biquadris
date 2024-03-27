#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include <vector>
#include <memory>
#include "cell.h"
using namespace std;

enum class RotateCW { Degree0, Degree90, Degree180, Degree270 };

class Block {
  protected:
    RotateCW curRotation;
    vector<vector<char>> config;
    shared_ptr<Cell> theBlock;

  public:
    Block(); // constructor

    vector<vector<char>> getConfig() const; 
    vector<shared_ptr<Cell>> getBlock() const;
    virtual void rotateBlockCW() = 0;    
    virtual void rotateBlockCCW() = 0; 

    //friend ostream &operator<<(ostream &out, const Block &b);
};

#endif
