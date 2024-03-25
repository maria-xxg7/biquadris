#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include <vector>
using namespace std;

enum class RotateCW { Degree0 = 0, Degree90 = 1, Deegree180 = 2, Degree270 = 3};

class Block {
    RotateCW curRotation;
    vector<vector<char>> config;

  public:
    Block(); // constructor
    ~Block(); // dtor

    vector<vector<char>> getConfig(); 
    virtual void rotateBlockCW() = 0;    
    virtual void rotateBlockCCW() = 0; 
};

#endif
