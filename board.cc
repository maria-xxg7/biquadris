#include "board.h"
#include <memory>

Board::Board() : theBoard {}, level {0}, curScore {0}, highScore {0}, 
  nextBlock{BlockType::empty}, td{new TextDisplay{}} // gd{nullptr}
  {}

Board::~Board() {
  delete td;
  // delete gd;
}

void Board::clearBoard() {
  theBoard.clear();
  curScore = 0;
  nextBlock = BlockType::empty;
}

void Board::init() {
  delete td;
  //delete gd;
  td = new TextDisplay();
  nextBlock = BlockType::empty;
  lastRotation = RotateCW::Degree0;
  
  vector<int> colRow (boardWidth, boardHeight + reserved);
  colHeights = colRow;

  // gd = new GraphicsDisplay(graphics, gridSize); 

  vector<Cell> new_row (boardWidth, Cell());
  for (int grid_r = 0; grid_r < boardHeight + reserved; ++grid_r) {
    theBoard.emplace_back(new_row);
  }

  vector<shared_ptr<Cell>> sharedRow (boardWidth, make_shared<Cell>());
  for (int shared_r = 0; shared_r < boardHeight + reserved; ++shared_r) {
    allBlocks.emplace_back(sharedRow);
  }
  for (int row = 0; row < boardHeight + reserved; ++row) {
    for (int col = 0; col < boardWidth; ++col) {
      allBlocks[row][col].reset();
      theBoard[row][col].setType(BlockType::empty);
      theBoard[row][col].setCoords(row, col);
      theBoard[row][col].attach(td);
      allBlocks[row][col] = make_shared<Cell>(theBoard[row][col]);
      //theBoard[row][col].attach(gd);
      
      for (int ob = 0; ob < boardWidth; ++ob) {
        if (ob != col) {
          theBoard[row][col].attach(&theBoard[row][ob]);
        }
      }
    }
  }
  // cout << "in use: " << allBlocks[0][0].use_count() << endl;
  // allBlocks[0][0] = allBlocks[1][1];
  // cout << "in use: " << allBlocks[0][0].use_count() << endl;
  // cout << "in use: " << allBlocks[1][1].use_count() << endl;

  // cout << (*allBlocks[1][1]).getRow() << "," << (*allBlocks[1][1]).getCol() << endl;

}

unique_ptr<Block> Board::BlockFactory::buildBlock(BlockType bType) {
  switch(bType) {
    case BlockType::IBlock: 
      return make_unique<IBlock>();
    case BlockType::JBlock:
      return make_unique<JBlock>();
    case BlockType::LBlock:
      return make_unique<LBlock>();
    case BlockType::OBlock:
      return make_unique<OBlock>();
    case BlockType::SBlock:
      return make_unique<SBlock>();
    case BlockType::ZBlock:
      return make_unique<ZBlock>();
    case BlockType::TBlock:
      return make_unique<TBlock>();
    default:
      return nullptr;
  }
}

void Board::setBlockType(BlockType b) {
  nextBlock = b;
}

bool Board::validMove(vector<vector<char>> *blockBlock, int shift, int down, bool placing) {
  bool isSafe = true;
  for (int i = 0; i < blockDim; ++i) {
    for (int j = 0; j < blockDim; ++j) {
      if ((*blockBlock)[i][j] != ' ') {
        if (i + totalDown + down > boardHeight + reserved - 1) { 
          isSafe = false; 
        } else if (j + totalShift + shift < 0 || j + totalShift + shift > 10) {
          isSafe = false;
        } else if (theBoard[i + totalDown + down][j + totalShift + shift].bType() != BlockType::empty) { 
          isSafe = false; // no longer safe to place block
        }
      }
    }
  }
  return isSafe;
}

void Board::moveBlock(string move) {
  unique_ptr<BlockFactory> makeBlock;
  unique_ptr<Block> newBlock = makeBlock->buildBlock(nextBlock);
  int shift = 0; int down = 0;
  bool save = false;
  bool isSafe = true;
  bool placing = false;

  move == "" ? placing = true : placing = false;

  if (move == "") {
    while (newBlock->getRotation() != RotateCW::Degree0) {
      newBlock->rotateBlockCW();
    }
  } else if (move != "") {
    while (lastRotation != newBlock->getRotation()) {
      newBlock->rotateBlockCW();
    }
  }

  if (move == "") {
    shift = 0;
    down = 0;
  } else if (move == "left") {
    shift = -1;
    down = 0;
  } else if (move == "right") {
    shift = 1;
    down = 0;
  } else if (move == "down") {
    down = 1;
    shift = 0;
  } else if (move == "clockwise") {
    newBlock->rotateBlockCW();
  } else if (move == "counterclockwise") {
    newBlock->rotateBlockCCW();
  } else if (move == "save") {
    save = true;
  }

  vector<vector<char>> blockBlock = newBlock->getConfig();

  if (placing) { // check if the block can be placed
    for (int i = 0; i < blockDim; ++i) {
      for (int j = 0; j < blockDim; ++j) {
        if ((blockBlock)[i][j] != ' ') {
          if (theBoard[i][j].bType() != BlockType::empty) { 
            lose = true;
          }
        }
      }
    }
  } 
  if (lose) {
    return;
  } else {
    if (!clear) {
        for (int i = 0; i < blockDim; ++i) {
          for (int j = 0; j < blockDim; ++j) {
            if (lastConfig[i][j] != ' ') {
              theBoard[i + totalDown][j + totalShift].setType(BlockType::empty);
              theBoard[i + totalDown][j + totalShift].setUnfilled();
            }
          }
        }
      }

      isSafe = validMove(&blockBlock, shift, down, placing);

      if (isSafe) {
        for (int i = 0; i < blockDim; ++i) {
          for (int j = 0; j < blockDim; ++j) {
            if (blockBlock[i][j] != ' ') {
              if (move != "") {
                theBoard[i + totalDown + down][j + totalShift + shift].setType(nextBlock);
                theBoard[i + totalDown + down][j + totalShift + shift].setFilled();
                if (save) {
                  vector<int> point {i + totalDown + down, j + totalShift + shift};
                  coords.emplace_back(point);
                }
              } else {
                theBoard[i][j].setType(nextBlock);
                theBoard[i][j].setFilled();
              }
            }
          }
        }

        if (move == "") {
          clear = false; 
          lastConfig = blockBlock;
        } else {
          if (save) {
            totalShift = 0;
            totalDown = 0;
            lastRotation = RotateCW::Degree0;
          } else {
            lastRotation = newBlock->getRotation();
            totalShift += shift;
            totalDown += down;
            lastConfig = blockBlock;
          }
        }
      } else {
        for (int i = 0; i < blockDim; ++i) {
          for (int j = 0; j < blockDim; ++j) {
            if (lastConfig[i][j] != ' ') {
              theBoard[i + totalDown][j + totalShift].setType(nextBlock);
              theBoard[i + totalDown][j + totalShift].setFilled();
            }
          }
        }
      }
  } 
}

// checks for lowest height cell can be dropped
int Board::findNextHeight(int row, int col) {
  for (int i = boardHeight + reserved - 1; i > row + 1; --i) {
    cout << "Position checking " << i << endl;
    if (theBoard[i][col].getState()) {
      cout << "LOWEST POSSIBLE" << i << endl;
      return i;
    }
  }
  return boardHeight + reserved - 1;
}

void Board::dropBlock() {
  // erase block
  for (int i = 0; i < blockDim; ++i) {
    // cout << "(" << coords[i][0] + maxDist << "," << coords[i][1] << ")" << endl;
    theBoard[coords[i][0]][coords[i][1]].setType(BlockType::empty);
    theBoard[coords[i][0]][coords[i][1]].setUnfilled();
  }

  // running max of the most amount dropped, since in tetris there could be muliple
  // we want lowest possible that it can go based on all blocks max distance
  int maxDist =  0;
  bool below = false; // if block is placed below maxHeight
  int validNum = 0;

  // iterate throught each block, calculate the different for that one column,
  // and check if dropping all blocks by that distance will work
  for (int i = 0; i < blockDim; ++i) {
    // cout << "STARTING POINT: " << colHeights[coords[i][1]] << " and " << coords[i][0] << endl;
    int tempDist = 0;
    bool validFit = true; // indicator that this dist did not work
    // placed below maxHeight - since move checks this is valid
    if (coords[i][0] > colHeights[coords[i][1]]) {
      // cout << "cond less than" << endl;
      below = true;
      tempDist = findNextHeight(coords[i][0], coords[i][1]) - coords[i][0] - 1;
      // cout << tempDist << endl;
    } else {
      // tempDist = colHeights[coords[i][1]] - coords[i][0] - 1;
      tempDist = colHeights[coords[i][1]] - coords[i][0] - 1;
    }

    //checking all other blocks with this tempDist
    // cout << "Checking dist wrt this point" << "(" << coords[i][0] << "," << coords[i][1] << ")" << endl;
    for (int j = 0; j < blockDim; ++j) {
      // cout << "NEW POINT: " << "(" << coords[j][0] << "," << coords[j][1] << ")" << endl;
      if (((coords[j][0] + tempDist) >= 18) || ((coords[j][0] + tempDist) < 3)) { // out of bounds
        // cout << "Out of Bounds 1: " << coords[j][0] << "and " << tempDist << endl;
        validFit = false; 
        break;
      } else if (theBoard[coords[j][0] + tempDist][coords[j][1]].getState()) { // alr filled by another block
        // cout << "Out of Bounds 2: " << coords[j][0] << "and " << tempDist << endl;
        validFit = false;
         break;   
        // iterate through to next height
      } else if (coords[j][0] + tempDist > colHeights[coords[j][1]] && !below) {
        // cout << "Out of Bounds 3: " << coords[j][0] << "and " << tempDist << endl;
        validFit = false;
      } 
      // cout << "Good: " << coords[j][0] << " and " << tempDist << endl;
    } // exit this for loop by either breaking since one of the blocks didnt fit or we exit
      // after all the blocks are checked and fit

    // if all the blocks fit and it's distance is the current max, we update variable
    if (validFit) {
      ++validNum;
      if (tempDist > maxDist) {
      // cout << "Valid last dist" << tempDist << endl;
      // cout << "Point with max dist" << "(" << coords[i][0] << "," << coords[i][1] << ")" << endl;
        maxDist = tempDist;
      }
    }
  } // after this for is exited, we've checked that blocks col height distance 
    // and checked if each block fits based on this difference
  // once we know which distance is the most suitable, we set the board
  // cout << "Max distance " << maxDist << endl;
  if (validNum == 0) {
    lose = true;
    return;
  }
  
  // shared_ptr<Cell> headCell = allBlocks[coords[0][0] + maxDist][coords[0][1]];
  for (int i = 1; i < blockDim; ++i) {
    allBlocks[coords[i][0] + maxDist][coords[i][1]] = allBlocks[coords[0][0] + maxDist][coords[0][1]];
  }
  // allBlocks[coords[1][0] + maxDist][coords[1][1]] = allBlocks[coords[0][0] + maxDist][coords[0][1]];
  for (int i = 0; i < blockDim; ++i) {
    // cout << "(" << coords[i][0] + maxDist << "," << coords[i][1] << ")" << endl;
    theBoard[coords[i][0] + maxDist][coords[i][1]].setType(nextBlock);
    theBoard[coords[i][0] + maxDist][coords[i][1]].setFilled();

    if (colHeights[coords[i][1]] > maxDist + coords[i][0]) {
      colHeights[coords[i][1]] = maxDist + coords[i][0];
    }
    // cout << "Height of " << coords[i][1] << " is: " << colHeights[coords[i][1]] << endl;
  }
  cout << "cells in block: " << allBlocks[coords[1][0] + maxDist][coords[1][1]].use_count() << endl;
  for (int i = 0; i < blockDim; ++i) {
    cout << "(" << (*allBlocks[coords[i][0] + maxDist][coords[i][1]]).getRow() << "," << 
                   (*allBlocks[coords[i][0] + maxDist][coords[i][1]]).getCol() << ")" << endl; 
  }
  coords.clear();
}

bool Board::checkLineClear(int row) {
  for (int i = 0; i < boardWidth; ++i) {
    if (theBoard[row][i].bType() == BlockType::empty) {
      return false;
    }
  }
  return true;
}

void Board::lineClear(int row) { // add lose condition, and check block type disappear
  // update score
  curScore += (level + 1) * (level + 1);
  if (curScore > highScore) {
    highScore = curScore;
  }
  // update colHeights since moving everything down
  for (int i = 0; i < boardWidth; ++i) {
    --colHeights[i];
  }

  for (int i = 0; i < boardWidth; ++i) {
    cout << "Count before at col " << i << ": " << allBlocks[16][i].use_count() << endl;
  }

  // delete the row that is cleared
  vector<vector<Cell>>::iterator it = theBoard.begin();
  theBoard.erase(it + row);
  vector<vector<shared_ptr<Cell>>>::iterator sit = allBlocks.begin();
  allBlocks.erase(sit + row);
  // input a new empty row at the top
  vector<Cell> newRow(boardWidth, Cell());
  theBoard.insert(theBoard.begin(), newRow);
  vector<shared_ptr<Cell>> newSRow(boardWidth, make_shared<Cell>());
  allBlocks.insert(allBlocks.begin(), newSRow);

  for (int col = 0; col < boardWidth; ++col) {
    theBoard[0][col].setType(BlockType::empty);
    theBoard[0][col].setCoords(0, col);
    allBlocks[0][col].reset();
    allBlocks[0][col] = make_shared<Cell>(theBoard[0][col]);
  }

  for (int i = 0; i < boardWidth; ++i) {
    cout << "Count after at col " << i << ": " << allBlocks[17][i].use_count() << endl;
  }

  // update td
  for (int i = row; i >= 0; --i) {
    for (int col = 0; col < boardWidth; ++col) {
        theBoard[i][col].attach(td);
        theBoard[i][col].setCoords(i, col);

        if (theBoard[i][col].bType() == BlockType::empty) {
          theBoard[i][col].setUnfilled();
          // cout << theBoard[i][col].getState() << " ";
        } else {
          theBoard[i][col].setFilled();
        }
    }
    // cout << endl;
  }
}

bool Board::isLose() const {
  return lose;
}

ostream &operator<<(ostream &out, const Board &b) {
  //print level and score (move to board class)
  string level = "Level: ";
  string score = "Score: ";
  string hiScore = "Hi Score: ";
  out << level << b.level << endl;
  out << score << b.curScore << endl;
  out << hiScore << b.highScore << endl;
  out << *b.td;
  return out;
}
