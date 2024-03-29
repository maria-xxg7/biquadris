#include "board.h"
#include <memory>

Board::Board() : theBoard {}, level {0}, curScore {0}, highScore {0}, 
  nextBlock{BlockType::empty}, curBlock{}, td{new TextDisplay{}} //, gd{nullptr}
  {}

Board::~Board() {
  delete td;
  // delete gd;
}

void Board::clearBoard() {
  theBoard.clear();
  curScore = 0;
  nextBlock = BlockType::empty;
  curBlock = BlockType::empty;
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

  for (int row = 0; row < boardHeight + reserved; ++row) {
    for (int col = 0; col < boardWidth; ++col) {

      theBoard[row][col].setType(BlockType::empty);
      theBoard[row][col].setCoords(row, col);
      theBoard[row][col].attach(td);
      //theBoard[row][col].attach(gd);
      
      for (int ob = 0; ob < boardWidth; ++ob) {
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

void Board::setBlockType(BlockType b) {
  nextBlock = b;
}

void Board::moveBlock(string move) {
  unique_ptr<BlockFactory> makeBlock;
  unique_ptr<Block> newBlock = makeBlock->buildBlock(nextBlock);
  int shift = 0; int down = 0;
  bool save = false;

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
}

void Board::dropBlock() {
  // cout << "Drop" << endl;
  // if (nextBlock == BlockType::OBlock) {cout << "oblock" << endl;}
  // for (int i = 0; i < 4; ++i) {
  //   cout << "(" << coords[i][0] << "," << coords[i][1] << ")" << endl;
  // }

  // running max of the most amount dropped, since in tetris there could be muliple
  // we want lowest possible that it can go
  int maxDist =  0;
  // iterate throught each block, calculate the different for that one column,
  // and check if dropping all blocks by that distance will work
  for (int i = 0; i < blockDim; ++i) {
    // cout << colHeights[coords[i][1]] << " and " << coords[i][0] << endl;
    bool validFit = true; // indicator that this dist did not work
    int tempDist = colHeights[coords[i][1]] - coords[i][0] - 1;

    //checking all other blocks with this tempDist
    // cout << "Checking dist wrt this point" << "(" << coords[i][0] << "," << coords[i][1] << ")" << endl;
    for (int j = 0; j < blockDim; ++j) {
      // cout << "NEW POINT: " << "(" << coords[j][0] << "," << coords[j][1] << ")" << endl;
      if (coords[j][0] + tempDist >= 18) { // out of bounds

        // cout << "Out of Bounds: " << coords[j][0] << "and " << tempDist << endl;
        validFit = false; 
        break;
      } else if (theBoard[coords[j][0] + tempDist][coords[j][1]].getState() == true) { // alr filled by another block
        validFit = false;
         break;  
      }
    } // exit this for loop by either breaking since one of the blocks didnt fit or we exit
      // after all the blocks are checked and fit

    // if all the blocks fit and it's distance is the current max, we update variable
    if (validFit && (tempDist > maxDist)) {
      // cout << "Point with max dist" << "(" << coords[i][0] << "," << coords[i][1] << ")" << endl;
      maxDist = tempDist;
    }
  } // after this for is exited, we've checked that blocks col height distance 
    // and checked if each block fits based on this difference

  // once we know which distance is the most suitable, we set the board
  for (int i = 0; i < blockDim; ++i) {
    // cout << "(" << coords[i][0] + maxDist << "," << coords[i][1] << ")" << endl;
    theBoard[coords[i][0]][coords[i][1]].setType(BlockType::empty);
    theBoard[coords[i][0]][coords[i][1]].setUnfilled();
    theBoard[coords[i][0] + maxDist][coords[i][1]].setType(nextBlock);
    theBoard[coords[i][0] + maxDist][coords[i][1]].setFilled();
    if (colHeights[coords[i][1]] > maxDist + coords[i][0]) {
      colHeights[coords[i][1]] = maxDist + coords[i][0];
    };
    // cout << "Height of " << coords[i][1] << " is: " << colHeights[coords[i][1]] << endl;
  }
  coords.clear();
}

ostream &operator<<(ostream &out, const Board &b) {
  //print level and score (move to board class)
  string level = "Level:";
  string score = "Score:";
  out << level << endl;
  out << score << endl;
  out << *b.td;
  return out;
}
