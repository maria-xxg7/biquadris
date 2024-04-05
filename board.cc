#include "board.h"
#include <memory>

Board::Board() : theBoard {}, td{new TextDisplay{}}, gd{nullptr}, level {0}, 
  curScore {0}, highScore {0}, blockScore {0}, curBlock{BlockType::empty}, 
  nextBlock{BlockType::empty} {}

Board::~Board() {
  delete td;
  delete gd;
}

void Board::clearBoard() {
  theBoard.clear();
  curScore = 0;
  blockScore = 0;
  level = 0;
  totalShift = 0;
  totalDown = 0;
  gd->setLevel(level);
  gd->setScore(curScore);

  curBlock = BlockType::empty;
  nextBlock = BlockType::empty;
  lastRotation = RotateCW::Degree0;

  lose = false;
  clear = true;
  specialAction = false;
  isHeavy = false;
  isBlind = false;
  isObstacle = false;

  vector<int> colRow (BOARD_W, BOARD_H + RESERVED);
  colHeights = colRow;

  lastConfig.clear();
  coords.clear();

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
      theBoard[row][col].setUnfilled();
      if (theBoard[row][col].bType() == BlockType::empty) {
        cout << "empty" << endl;
      }
    }
  }
}

void Board::init(Xwindow &wd) {
  gd = new GraphicsDisplay(wd); 
  curBlock = BlockType::empty;
  nextBlock = BlockType::empty;
  lastRotation = RotateCW::Degree0;
  
  vector<int> colRow (BOARD_W, BOARD_H + RESERVED);
  colHeights = colRow;

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
    }
  }
}

bool Board::isLose() { return lose; }

shared_ptr<Block> Board::BlockFactory::buildBlock(BlockType bType) {
  switch(bType) {
    case BlockType::IBlock: 
      return make_shared<IBlock>();
    case BlockType::JBlock:
      return make_shared<JBlock>();
    case BlockType::LBlock:
      return make_shared<LBlock>();
    case BlockType::OBlock:
      return make_shared<OBlock>();
    case BlockType::SBlock:
      return make_shared<SBlock>();
    case BlockType::ZBlock:
      return make_shared<ZBlock>();
    case BlockType::TBlock:
      return make_shared<TBlock>();
    default:
      return make_shared<IBlock>();
  }
}

void Board::setBlockType(BlockType b) { nextBlock = b; }

BlockType Board::getBlockType() { return nextBlock; }

string Board::getNextType() {
  switch(nextBlock) {
    case BlockType::IBlock: 
      return "I Block";
    case BlockType::JBlock:
      return "J Block";
    case BlockType::LBlock:
      return "L Block";
    case BlockType::OBlock:
      return "O Block";
    case BlockType::SBlock:
      return "S Block";
    case BlockType::ZBlock:
      return "Z Block";
    case BlockType::TBlock:
      return "T Block";
    default:
      return "I Block";
  }
}

void Board::setCurBlock(BlockType b) { curBlock = b; }

BlockType Board::getCurBlockB() { return curBlock; }

string Board::getCurBlock() { 
  switch(curBlock) {
    case BlockType::IBlock: 
      return "I Block";
    case BlockType::JBlock:
      return "J Block";
    case BlockType::LBlock:
      return "L Block";
    case BlockType::OBlock:
      return "O Block";
    case BlockType::SBlock:
      return "S Block";
    case BlockType::ZBlock:
      return "Z Block";
    case BlockType::TBlock:
      return "T Block";
    default:
      return "I Block";
  }
}

int Board::getLevel() const { return level; }

void Board::setLevel(int newLevel) { level = newLevel; }

bool Board::getHeavy() { return isHeavy; }

void Board::setHeavy(bool heavy) { isHeavy = heavy; }

bool Board::getObstacle() { return isObstacle; }

void Board::setObstacle(bool obstacle) { isObstacle = obstacle; }

bool Board::finishedMove() { return heavyDrop; }

void Board::setBlind(bool isOn) { isBlind = isOn; }

bool Board::getSpecial() { return specialAction; }

void Board::setSpecial(bool isOn) { specialAction = isOn; }

bool Board::validMove(vector<vector<char>> *blockBlock, int shift, int down, bool placing) {
  bool isSafe = true; // temp indicator for if it is safe to place a block
  for (int i = 0; i < BLOCK_DIM; ++i) {
    for (int j = 0; j < BLOCK_DIM; ++j) {
      if ((*blockBlock)[i][j] != ' ') {
        if (i + totalDown + down > BOARD_H + RESERVED - 1) { // check if moves goes past the bottom border
          isSafe = false; 
        } else if (j + totalShift + shift < 0 || j + totalShift + shift > 10) {  // check if move goes past left/right border
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
  shared_ptr<BlockFactory> makeBlock = make_shared<BlockFactory>(); // create block factory
  shared_ptr<Block> newBlock = makeBlock->buildBlock(nextBlock); // make a pointer to the current block

  int shift = 0; int down = 0; // block moves
  bool save = false; // save block coords
  bool isSafe = true; // indicates if it is safe to place the block
  bool placing = false; // if the block is being placed not moved

  move == "" ? placing = true : placing = false; // check if block is being placed

  if (placing) { // if placing the block
    while (newBlock->getRotation() != RotateCW::Degree0) { 
      newBlock->rotateBlockCW(); // rotate to starting rotation (degree 0)
    }
  } else if (!placing) {
    while (lastRotation != newBlock->getRotation()) {
      newBlock->rotateBlockCW(); // rotate to previous rotation
    }
  }

  if (placing) { // no movement
    shift = 0; 
    down = 0;
    cellLevel = level;
  } else if (move == "left") { // move left
    shift = -1;
    down = 0;
  } else if (move == "right") { // move right
    shift = 1;
    down = 0;
  } else if (move == "down") { // move down
    down = 1;
    shift = 0;
  } else if (move == "clockwise") { // rotate clockwise
    newBlock->rotateBlockCW();
  } else if (move == "counterclockwise") { // rotate counterclockwise
    newBlock->rotateBlockCCW();
  } else if (move == "save") { // save the block
    save = true;
  }

  vector<vector<char>> blockBlock = newBlock->getConfig(); // get configuration

  if (placing) { // check if the block can be placed
    for (int i = 0; i < BLOCK_DIM; ++i) {
      for (int j = 0; j < BLOCK_DIM; ++j) {
        if ((blockBlock)[i][j] != ' ') {
          if (theBoard[i][j].bType() != BlockType::empty) { // check if the cells are filled
            lose = true; // block cannot be place => lose the game
          }
        }
      }
    }
  } 

  if (lose) { return; } // if lost, exit moveBlock

  if (!clear) { // check if the board isn't clear of the previous block
      for (int i = 0; i < BLOCK_DIM; ++i) {
        for (int j = 0; j < BLOCK_DIM; ++j) {
          if (lastConfig[i][j] != ' ') {
            // clear the filled cells
            theBoard[i + totalDown][j + totalShift].setType(BlockType::empty);
            theBoard[i + totalDown][j + totalShift].setUnfilled();
          }
        }
      }
    }

    isSafe = validMove(&blockBlock, shift, down, placing); // check if safe to make the move

    if (level >= 3 && !isHeavy && isSafe) {
      bool oneDown = validMove(&blockBlock, shift, down + 1, placing);
      if (oneDown) { ++down; }
      else { heavyDrop = true; }
    }

    // special action: check if isHeavy is enabled and the move made was horizontal & legal
    if (isSafe && isHeavy && (move == "left" || move == "right")) { 
      bool oneDown = validMove(&blockBlock, shift, down + 1, placing);
      bool doubleDown = validMove(&blockBlock, shift, down + 2, placing);

      if (oneDown && doubleDown) { // check if can move down 2 (in addition to the left/right move)
        down += 2;
      } else {
        heavyDrop = true;
      }
    }

    // safe to place
    if (isSafe) {
      for (int i = 0; i < BLOCK_DIM; ++i) {
        for (int j = 0; j < BLOCK_DIM; ++j) {
          if (blockBlock[i][j] != ' ') {
            if (!placing) { // check if moving (not placing)
              // set cells on in new block position
              theBoard[i + totalDown + down][j + totalShift + shift].setType(curBlock);

              if (isBlind && checkBlindCell(theBoard[i + totalDown + down][j + totalShift + shift])) {
                theBoard[i + totalDown + down][j + totalShift + shift].setUnfilled();
              } else {
                theBoard[i + totalDown + down][j + totalShift + shift].setFilled();
              }
              if (save) { // check if final move
                // save coordinates of final block position
                vector<int> point {i + totalDown + down, j + totalShift + shift};
                coords.emplace_back(point);
              }
            } else { // if placing block
              // set cells on in starting block config position
              theBoard[i][j].setType(curBlock);
              theBoard[i][j].setFilled();
            }
          }
        }
      }

      if (placing) { // check if placing block
        clear = false; // board no longer clear
        lastConfig = blockBlock; // save last config
      } else {
        if (save) { // check if saving block 
          // reset state of block
          totalShift = 0;
          totalDown = 0;
          lastRotation = RotateCW::Degree0;
          heavyDrop = false;
        } else { // check if still moving block
          // save state of previous block & update total movements
          lastRotation = newBlock->getRotation();
          lastConfig = blockBlock;
          totalShift += shift;
          totalDown += down;
        }
      }
    } else { // if not safe to move
      for (int i = 0; i < BLOCK_DIM; ++i) {
        for (int j = 0; j < BLOCK_DIM; ++j) {
          if (lastConfig[i][j] != ' ') { 
            // set the block back to where it used to be (no movement)
            theBoard[i + totalDown][j + totalShift].setType(curBlock);
            theBoard[i + totalDown][j + totalShift].setFilled();
          }
        }
      }
    }
}

void Board::clearPlaced() {
  for (int i = 0; i < BLOCK_DIM; ++i) {
    for (int j = 0; j < BLOCK_DIM; ++j) {
      if (lastConfig[i][j] != ' ') {
        // clear the filled cells
        theBoard[i + totalDown][j + totalShift].setType(BlockType::empty);
        theBoard[i + totalDown][j + totalShift].setUnfilled();
      }
    }
  }
}

int Board::findNextHeight(int row, int col) {
  for (int i = BOARD_H + RESERVED - 1; i > row + 1; --i) {
    if (theBoard[i][col].getState()) {
      return i;
    }
  }
  return BOARD_H + RESERVED - 1;
}

void Board::dropBlock() {
  ++numBlocksDropped;
  // erase block
  for (int i = 0; i < BLOCK_DIM; ++i) {
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
    int tempDist = 0;
    bool validFit = true; // indicator that this dist did not work

    // placed below maxHeight - since move checks this is valid
    if (coords[i][0] > colHeights[coords[i][1]]) {
      below = true;
      tempDist = findNextHeight(coords[i][0], coords[i][1]) - coords[i][0] - 1;
    } else {
      tempDist = colHeights[coords[i][1]] - coords[i][0] - 1;
    }

    //checking all other blocks with this tempDist
    for (int j = 0; j < BLOCK_DIM; ++j) {
      if (((coords[j][0] + tempDist) >= 18) || ((coords[j][0] + tempDist) < 3)) { // out of bounds
        validFit = false; 
        break;
      } else if (theBoard[coords[j][0] + tempDist][coords[j][1]].bType() != BlockType::empty) { // alr filled by another block
        validFit = false;
         break;   
        // iterate through to next height
      } else if (coords[j][0] + tempDist > colHeights[coords[j][1]] && !below) {
        validFit = false;
      }
    } // exit this for loop by either breaking since one of the blocks didnt fit or we exit
      // after all the blocks are checked and fit

    // if all the blocks fit and it's distance is the current max, we update variable
    if (validFit) {
      ++validNum;
      if (tempDist > maxDist) {
        maxDist = tempDist;
      }
    }
  } // after this for is exited, we've checked that blocks col height distance 
    // and checked if each block fits based on this difference

  // once we know which distance is the most suitable, we set the board
  if (validNum == 0 && !below) {
    lose = true;
    return;
  }
  
  for (int i = 0; i < BLOCK_DIM; ++i) {
    theBoard[coords[i][0] + maxDist][coords[i][1]].setType(curBlock);
    theBoard[coords[i][0] + maxDist][coords[i][1]].setLevel(cellLevel);
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
    theBoard[coords[i][0] + maxDist][coords[i][1]].setHead(coords[0][0] + maxDist, coords[0][1]);

    if (colHeights[coords[i][1]] > maxDist + coords[i][0]) {
      colHeights[coords[i][1]] = maxDist + coords[i][0];
    }
  }

  // reset states:
  coords.clear();
  cout << "cell level: " << cellLevel << endl;
  cellLevel = 0;
  curBlock = nextBlock;
  isHeavy = false;
  if (isBlind) {
    blinding(false); // turn off blind
    isBlind = false;
  }
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

bool Board::checkBlindCell(Cell &c) {
  for (int i = 5; i < BOARD_H; ++i) {
    for (int j = 2; j < 9; ++j) {
      if (c.getRow() == i && c.getCol() == j) {
        return true;
      }
    }
  }
  return false;
}

void Board::blinding(bool blind) {
  // hide columns 3-9, and from rows 3-12
  if (blind) {
    for (int i = 5; i < BOARD_H; ++i) {
      for (int j = 2; j < 9; ++j) {
        theBoard[i][j].hide();
        theBoard[i][j].setUnfilled();
      }
    }
  } else {
     for (int i = 5; i < BOARD_H; ++i) {
      for (int j = 2; j < 9; ++j) {
        theBoard[i][j].show();
        theBoard[i][j].setFilled();
      }
    }   
  }
}

void Board::updateScore() {
  int numCleared = 0;
  for (int i = RESERVED; i < BOARD_H + RESERVED; ++i) {
    if (checkLineClear(i)) {
      ++numCleared;
      lineClear(i);
    }
  }

  numCleared >= 2 ? specialAction = true : specialAction = false;

  if (numCleared != 0) {
    int max = colHeights[0];
    for (int i = 1; i < BOARD_W; ++i) {
      if (colHeights[i] < max) {
        max = colHeights[i];
      }
    }

    // update td
    for (int i = max - 1; i >= 0; --i) {
      for (int col = 0; col < BOARD_W; ++col) {
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
    int sqrtScore = numCleared + level;
    curScore += (sqrtScore * sqrtScore);
    curScore += blockScore;

    if (curScore > highScore) {
      highScore = curScore;
    }
    gd->setScore(curScore);
    gd->setHiScore(highScore);
    blockScore = 0;
  } else {
    if (numBlocksDropped == 5 && level == 4) {
      if (theBoard[3][5].bType() != BlockType::empty) {
        // lose = true;
        // return;
        cout << "cannot place shit anymore :(" << endl;
      } else {
        theBoard[colHeights[5] - 1][5].setType(BlockType::SHIT);
        theBoard[colHeights[5] - 1][5].setFilled();
        --colHeights[5];
      }
      numBlocksDropped = 0;
    }
  }
}

ostream &operator<<(ostream &out, const Board &b) {
  //print level and score (move to board class)
  string level = "Level: ";
  string score = "Score: ";
  string hiScore = "Hi Score: ";
  b.gd->setLevel(b.getLevel());
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
      case BlockType::SHIT:
        break;
    }
  out << *newBlock;
  return out;
}
