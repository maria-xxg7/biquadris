#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include <vector>
using namespace std;

enum class RotateCW { Degree0, Degree90, Degree180, Degree270 };

class Block {
  protected:
    RotateCW curRotation;
    vector<vector<char>> config;

  public:
    Block(); // constructor

    vector<vector<char>> getConfig(); 
    virtual void rotateBlockCW() = 0;    
    virtual void rotateBlockCCW() = 0; 

    friend ostream &operator<<(ostream &out, const Block &b);
};

#endif
