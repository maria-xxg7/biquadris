#include "block.h"

Block::Block() : curRotation {RotateCW::Degree0}, config {} {}

vector<vector<char>> Block::getConfig() {
    return config;
}
