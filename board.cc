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
  nextBlock = BlockType::IBlock;

  // gd = new GraphicsDisplay(graphics, gridSize); 

  vector<Cell> new_row (boardWidth, Cell());
  for (int grid_r = 0; grid_r < boardHeight + reserved; ++grid_r) {
    theBoard.emplace_back(new_row);
  }

  for (int row = 0; row < boardHeight + reserved; ++row) {
    for (int col = 0; col < boardWidth; ++col) {

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

void Board::moveBlock(string move) {
  unique_ptr<BlockFactory> makeBlock;
  unique_ptr<Block> newBlock = makeBlock->buildBlock(nextBlock);
  int shift = 0; int down = 0;

  while (lastRotation != newBlock->getRotation()) {
    newBlock->rotateBlockCW();
  }

  if (move == "left") {
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
  } else if (move == "") {
    shift = 0;
    down = 0;
  } else {
    newBlock->rotateBlockCCW();
  }

  cout << clear << endl;
  int blockDim = 4;

  if (!clear) {
    for (int i = 0; i < blockDim; ++i) {
      for (int j = 0; j < blockDim; ++j) {
        if (lastConfig[i][j] != ' ') {
          theBoard[i + totalDown][j + totalShift].setUnfilled();
          theBoard[i + totalDown][j + totalShift].setType(BlockType::empty);
        }
      }
    }
  }

  vector<vector<char>> blockBlock = newBlock->getConfig();

  for (int i = 0; i < blockDim; ++i) {
    for (int j = 0; j < blockDim; ++j) {
      if (blockBlock[i][j] != ' ') {
      //     // cout << "(" << i + totalDown + down << "," << j + totalShift + shift << ")" << endl;
      //     // cout << i << " & " << j << endl;

        if (move != "") {
          theBoard[i + totalDown + down][j + totalShift + shift].setFilled();
          theBoard[i + totalDown + down][j + totalShift + shift].setType(BlockType::JBlock);
        } else {
          theBoard[i][j].setFilled();
          theBoard[i][j].setType(BlockType::JBlock);
        }

      }
    }
  }

  if (move == "") {
    clear = false; 
    lastConfig = blockBlock;
  } else {
    totalShift += shift;
    totalDown += down;
    lastConfig = blockBlock;
    lastRotation = newBlock->getRotation();
  }
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
