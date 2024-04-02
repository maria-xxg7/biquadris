#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include <vector>
#include "cell.h"
using namespace std;

enum class RotateCW { Degree0, Degree90, Degree180, Degree270 };

class Block {
  RotateCW curRotation;
  vector<vector<char>> config;

  public:
    Block(); // constructor
    vector<vector<char>> getConfig(); 
    RotateCW getRotation() const;
    void setConfig(vector<vector<char>> cf);
    void setRotation(RotateCW rotation);
    string getRotationString() const;
    virtual vector<int> getLeftCorner();
    virtual void rotateBlockCW() = 0;    
    virtual void rotateBlockCCW() = 0; 

    friend ostream &operator<<(ostream &out, Block &b);
};

#endif
