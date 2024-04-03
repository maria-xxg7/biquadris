#include "board.h"
#include <memory>

Board::Board() : theBoard {}, level {0}, curScore {0}, highScore {0}, blockScore {0},
  nextBlock{BlockType::empty}, td{new TextDisplay{}} // gd{nullptr}
  {}

Board::~Board() {
  delete td;
  delete gd;
}

void Board::clearBoard() {
  theBoard.clear();
  curScore = 0;
  blockScore = 0;
  lose = true;
  nextBlock = BlockType::empty;
  clear = true;
  vector<int> colRow (BOARD_W, BOARD_H + RESERVED);
  colHeights = colRow;
}

void Board::init(Xwindow &wd) {
  td = new TextDisplay();
  nextBlock = BlockType::empty;
  lastRotation = RotateCW::Degree0;
  
  vector<int> colRow (BOARD_W, BOARD_H + RESERVED);
  colHeights = colRow;

  gd = new GraphicsDisplay(wd); 

  vector<Cell> new_row (BOARD_W, Cell());
  for (int grid_r = 0; grid_r < BOARD_H + RESERVED; ++grid_r) {
    theBoard.emplace_back(new_row);
  }

  for (int row = 0; row < BOARD_H + RESERVED; ++row) {
    for (int col = 0; col < BOARD_W; ++col) {
      theBoard[row][col].setType(BlockType::empty);
      theBoard[row][col].setCoords(row, col);
      theBoard[row][col].attach(td);
      theBoard[row][col].attach(gd);
      
      for (int ob = 0; ob < BOARD_W; ++ob) {
        if (ob != col) {
          theBoard[row][col].attach(&theBoard[row][ob]);
        }
      }
    }
  }
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

void Board::setBlockType(BlockType b) { nextBlock = b; }

int Board::getLevel() { return level; }

void Board::setLevel(int newLevel) { level = newLevel; }

bool Board::getHeavy() { return isHeavy; }

void Board::setHeavy(bool heavy) { isHeavy = heavy; }

bool Board::getObstacle() { return isObstacle; }

void Board::setObstacle(bool obstacle) { isObstacle = obstacle; }

bool Board::validMove(vector<vector<char>> *blockBlock, int shift, int down, bool placing) {
  bool isSafe = true;
  for (int i = 0; i < BLOCK_DIM; ++i) {
    for (int j = 0; j < BLOCK_DIM; ++j) {
      if ((*blockBlock)[i][j] != ' ') {
        if (i + totalDown + down > BOARD_H + RESERVED - 1) { 
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
  if (newBlock->getRotation() == RotateCW::Degree0) {
    cout << "degree 0" << endl;
  }
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
    cout << save << endl;
  }

  vector<vector<char>> blockBlock = newBlock->getConfig();
  cout << shift << endl;
  cout << down << endl;

  if (placing) { // check if the block can be placed
    for (int i = 0; i < BLOCK_DIM; ++i) {
      for (int j = 0; j < BLOCK_DIM; ++j) {
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
        for (int i = 0; i < BLOCK_DIM; ++i) {
          for (int j = 0; j < BLOCK_DIM; ++j) {
            if (lastConfig[i][j] != ' ') {
              theBoard[i + totalDown][j + totalShift].setType(BlockType::empty);
              theBoard[i + totalDown][j + totalShift].setUnfilled();
            }
          }
        }
      }

      isSafe = validMove(&blockBlock, shift, down, placing);

      if (isSafe) {
        for (int i = 0; i < BLOCK_DIM; ++i) {
          for (int j = 0; j < BLOCK_DIM; ++j) {
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
        for (int i = 0; i < BLOCK_DIM; ++i) {
          for (int j = 0; j < BLOCK_DIM; ++j) {
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
  for (int i = BOARD_H + RESERVED - 1; i > row + 1; --i) {
    // cout << "Position checking " << i << endl;
    if (theBoard[i][col].getState()) {
      // cout << "LOWEST POSSIBLE" << i << endl;
      return i;
    }
  }
  return BOARD_H + RESERVED - 1;
}

void Board::dropBlock() {
  // erase block
  for (int i = 0; i < BLOCK_DIM; ++i) {
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
  for (int i = 0; i < BLOCK_DIM; ++i) {
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
    for (int j = 0; j < BLOCK_DIM; ++j) {
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
      // cout << validFit << endl;
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
  if (validNum == 0 && !below) {
    lose = true;
    return;
  }
  
  for (int i = 0; i < BLOCK_DIM; ++i) {
    // cout << "(" << coords[i][0] + maxDist << "," << coords[i][1] << ")" << endl;
    theBoard[coords[i][0] + maxDist][coords[i][1]].setType(nextBlock);
    theBoard[coords[i][0] + maxDist][coords[i][1]].setFilled();
    if (i != 0) {
      theBoard[coords[0][0] + maxDist][coords[0][1]].attachBlock(&theBoard[coords[i][0] + maxDist][coords[i][1]]);
    }
    if (i != 1) {
      theBoard[coords[1][0] + maxDist][coords[1][1]].attachBlock(&theBoard[coords[i][0] + maxDist][coords[i][1]]);
    }
    if (i != 2) {
      theBoard[coords[2][0] + maxDist][coords[2][1]].attachBlock(&theBoard[coords[i][0] + maxDist][coords[i][1]]);
    }
    if (i != 3) {
      theBoard[coords[3][0] + maxDist][coords[3][1]].attachBlock(&theBoard[coords[i][0] + maxDist][coords[i][1]]);
    }
    // theBoard[0][0].setHead(0, 0);
    theBoard[coords[i][0] + maxDist][coords[i][1]].setHead(coords[0][0] + maxDist, coords[0][1]);

    if (colHeights[coords[i][1]] > maxDist + coords[i][0]) {
      colHeights[coords[i][1]] = maxDist + coords[i][0];
    }
    // cout << "Height of " << coords[i][1] << " is: " << colHeights[coords[i][1]] << endl;
  }

  cout << "drop" << endl;

  coords.clear();
}

bool Board::checkLineClear(int row) {
  for (int i = 0; i < BOARD_W; ++i) {
    if (theBoard[row][i].bType() == BlockType::empty) {
      return false;
    }
  }
  return true;
}

void Board::reassignHead(int row) {
  vector<vector<int>> heads; 
  vector<vector<int>> newHeads; 

  int headRow = theBoard[row][0].getHeadRow(); 
  int headCol = theBoard[row][0].getHeadCol();
  vector<int> headTemp = {headRow, headCol};
  heads.emplace_back(headTemp);

  for (int i = 0; i < BOARD_W; ++i) {  
      if (theBoard[row][i].getHeadRow() != headRow || theBoard[row][i].getHeadCol() != headCol) {
        headRow = theBoard[row][i].getHeadRow();
        headCol = theBoard[row][i].getHeadCol();
        vector<int> headTemp = {headRow, headCol};
        heads.emplace_back(headTemp);
      }
  } 

  // GET CELLS WITH HEADS BEING REMOVED

  int headLen = heads.size();
  vector<vector<int>>::iterator hit = heads.begin();
  for (int i = 0; i < headLen; ++i) {
      if (heads[i][0] != row) {
        heads.erase(hit);
        break;
      }
      ++hit;
  }

  headLen = heads.size();

  vector<bool> hasHead (headLen, false); 

  // REASSIGN HEAD

  int start = RESERVED;
  if (row - RESERVED > start) {
    start = row - RESERVED;
  }
  int end = BOARD_H + RESERVED;
  if (row + RESERVED < end) {
    end = row + RESERVED;
  }

  for (int i = start; i < end; ++i) {
    for (int j = 0; j < BOARD_W; ++j) {
      for (int h = 0; h < headLen; ++h) {
        if (theBoard[i][j].getHeadRow() == heads[h][0] && theBoard[i][j].getHeadCol() == heads[h][1]
            && i != heads[h][0] && !hasHead[h]) {
            vector<int> temp = {i, j};
            newHeads.emplace_back(temp);
            hasHead[h] = true;
        }
      }
    }
  }

  vector<vector<int>>::iterator hit2 = heads.begin();
  for (int i = 0; i < headLen; ++i) {
      if (!hasHead[i]) {
        heads.erase(hit2);
      }
      ++hit2;
  }

  headLen = heads.size();

  for (int i = start; i < end; ++i) {
    for (int j = 0; j < BOARD_W; ++j) {
      for (int h = 0; h < headLen; ++h) {
        if (theBoard[i][j].getHeadRow() == heads[h][0] && theBoard[i][j].getHeadCol() == heads[h][1]) {
          theBoard[i][j].setHead(newHeads[h][0], newHeads[h][1]);
        }
      }
    }
  }
}

bool Board::checkHeads(int row) {
  vector<vector<int>> heads; 

  int headRow = theBoard[row][0].getHeadRow(); 
  int headCol = theBoard[row][0].getHeadCol();
  vector<int> headTemp = {headRow, headCol};
  heads.emplace_back(headTemp);

  for (int i = 0; i < BOARD_W; ++i) {  
      if (theBoard[row][i].getHeadRow() != headRow || theBoard[row][i].getHeadCol() != headCol) {
        headRow = theBoard[row][i].getHeadRow();
        headCol = theBoard[row][i].getHeadCol();
        vector<int> headTemp = {headRow, headCol};
        heads.emplace_back(headTemp);
      }
  } 

  int headLen = heads.size();
  vector<vector<int>>::iterator hit = heads.begin();
  for (int i = 0; i < headLen; ++i) {
      if (heads[i][0] != row) {
        heads.erase(hit);
        break;
      }
      ++hit;
  }

  headLen = heads.size();

  bool reassign = false;
  
  for (int i = 0; i < BOARD_W; ++i) {
    for (int h = 0; h < headLen; ++h) {
      if (theBoard[row][i].cellsLeft() != 0 && theBoard[row][i].getHeadRow() == heads[h][0] &&
          theBoard[row][i].getHeadCol() == heads[h][1]) {
        reassign = true;
      }
    }
  }

  if (reassign) return true;
  return false;
}

void Board::lineClear(int row) { // add lose condition, and check block type disappear
  // update colHeights since moving everything down
  for (int i = 0; i < BOARD_W; ++i) {
    ++colHeights[i];
  }

  // UPDATE BLOCK OBSERVERS

  for (int i = 0; i < BOARD_W; ++i) { 
    for (int fwd = i; fwd < BOARD_W; ++fwd) {
      theBoard[row][i].detachBlock(&theBoard[row][fwd]); // detach block observers in front
    }
    for (int bwd = i; bwd >= 0; --bwd) {
      theBoard[row][i].detachBlock(&theBoard[row][bwd]); // detach block observers behind
    }
  } // update block observers in row being removed

  int start = RESERVED;
  if (row - RESERVED > start) {
    start = row - RESERVED;
  }
  int end = BOARD_H + RESERVED;
  if (row + RESERVED < end) {
    end = row + RESERVED;
  }

  for (int i = start; i < end; ++i) {
    for (int j = 0; j < BOARD_W; ++j) {
      for (int col = 0; col < BOARD_W; ++col) {
        theBoard[i][j].detachBlock(&theBoard[row][col]); // detach block observers
      }
    }
  } // update the remaining cells in the block (if any)

  // CHECK IF WHOLE BLOCK IS CLEARED
  // cout << checkHeads(row) << endl;
  // reassignHead(row);
  if (checkHeads(row)) { reassignHead(row); }

  vector<vector<int>> blocks; 

  // get head cell
  int curBlockRow = theBoard[row][0].getHeadRow(); 
  int curBlockCol = theBoard[row][0].getHeadCol(); 
  vector<int> temp {theBoard[row][0].getRow(), theBoard[row][0].getCol()};
  blocks.emplace_back(temp); // add to blocks


  for (int i = 0; i < BOARD_W; ++i) { 
    // check if different from the current block
    if (theBoard[row][i].getHeadRow() != curBlockRow || theBoard[row][i].getHeadCol() != curBlockCol) {
      // set current block to the next block
      curBlockRow = theBoard[row][i].getHeadRow();
      curBlockCol = theBoard[row][i].getHeadCol();
      vector<int> temp {theBoard[row][i].getRow(), theBoard[row][i].getCol()};
      blocks.emplace_back(temp); // add to blocks
    }
  } // add any distinct blocks in the row

  int numBlocks = blocks.size(); // number of blocks in the row
  for (int i = 0; i < numBlocks; ++i) {
    if (theBoard[blocks[i][0]][blocks[i][1]].cellsLeft() == 0) {
      cout << "block cleared" << endl;
      int sqrtBlock = theBoard[blocks[i][0]][blocks[i][1]].getLevel() + 1;
      blockScore += (sqrtBlock * sqrtBlock);
    }
  } // count how many blocks were fully cleared

  // delete the row that is cleared
  vector<vector<Cell>>::iterator it = theBoard.begin();
  theBoard.erase(it + row);

  // input a new empty row at the top
  vector<Cell> newRow(BOARD_W, Cell());
  theBoard.insert(theBoard.begin(), newRow);

  // init new row
  for (int col = 0; col < BOARD_W; ++col) {
    theBoard[0][col].setType(BlockType::empty);
    theBoard[0][col].setCoords(0, col);
  }
  int max = colHeights[0];
  for (int i = 1; i < BOARD_W; ++i) {
    if (colHeights[i] < max) {
      max = colHeights[i];
    }
  }

  // update td
  for (int i = row; i >= max - 1; --i) {
    for (int col = 0; col < BOARD_W; ++col) {
    // theBoard[row][i].detach(td); // detach the text display from the cells being removed
        theBoard[i][col].setCoords(i, col);
        theBoard[i][col].attach(td); // reattach the cells to the text display
        theBoard[i][col].attach(gd); // reattach the cells to the text display

        if (theBoard[i][col].bType() == BlockType::empty) {
          theBoard[i][col].setUnfilled();
        } else {
          theBoard[i][col].setFilled();
        }
    }
  }

  cout << "final" << endl;
  for (int row = 0; row < BOARD_H + RESERVED; ++row) {
    for (int col = 0; col < BOARD_W; ++col) {
      cout << theBoard[row][col].cellsLeft();
    }
    cout << endl;
  }
}

void Board::updateScore() {
  int numCleared = 0;
  for (int i = 17; i <= 0; --i) {
    if (checkLineClear(i)) {
      ++numCleared;
      lineClear(i);
    }
  }
  int sqrtScore = numCleared + level;
  cout << "Before square " << sqrtScore << endl;
  curScore += (sqrtScore * sqrtScore);
  curScore += blockScore;
  // gd.setScore(curScore);
  if (curScore > highScore) {
    highScore = curScore;
  }
  blockScore = 0;
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
  out << "Next: " << endl;
  shared_ptr<Block> newBlock = make_shared<IBlock>();
  switch(b.nextBlock) {
      case BlockType::IBlock:
        *newBlock = IBlock();
        b.gd->updateNext(newBlock, b.nextBlock);
        break;
      case BlockType::JBlock:
        *newBlock = JBlock();
         b.gd->updateNext(newBlock, b.nextBlock);
        break;
      case BlockType::LBlock:
        *newBlock = LBlock();
        b.gd->updateNext(newBlock, b.nextBlock);
        break;
      case BlockType::OBlock:
        *newBlock = OBlock();
        b.gd->updateNext(newBlock, b.nextBlock);
        break;
      case BlockType::SBlock:
        *newBlock = SBlock();
        b.gd->updateNext(newBlock, b.nextBlock);
        break;
      case BlockType::ZBlock:
        *newBlock = ZBlock();
        b.gd->updateNext(newBlock, b.nextBlock);
        break;
      case BlockType::TBlock:
        *newBlock = TBlock();
        b.gd->updateNext(newBlock, b.nextBlock);
        break;
      case BlockType::empty:
        break;
    }
  out << *newBlock;
  return out;
}
