#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Cell;

enum class BlockType { IBlock, JBlock, LBlock, OBlock, SBlock, ZBlock, TBlock, empty };

class Observer {
  public:
    // c is a cell that called the notify method so we can get its position
    virtual void notify(Cell &c) = 0;
    virtual BlockType bType() = 0;
    virtual ~Observer() = default;
};

#endif
