#include "block.h"

// recheck if this constructor is enough, can make this level passed in as
// an argument or set default to zero and have a setter later
Block::Block() : row {0}, col {0}, level {0} {}

void Block::setCoords(int row, int col) {
    this->row = row;
    this->col = col;
}

int Block::getRow() const {
    return row;
}
int Block::getCol() const {
    return col;
}

// implementation ideas:
//  *field for checking for blocks remaining, notify that turn is being made, and turn with same amount
void Block::notify(Block &b) {
    
}

void Block::attatch(Observer *o) {
    observers.emplace_back(0);
}
