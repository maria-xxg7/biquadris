#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Block;

enum class BlockType { IBlock, JBlock, LBlock, OBlock, SBlock, ZBlock, TBlock };

class Observer {
  public:
    // b is a Block that called the notify method so we can get its position
    virtual void notify(Block &b) = 0;
    // virtual BlockType bType() = 0;
    virtual ~Observer() = default;
};

#endif
