#include "board.h"

Board::Board() : theBoard {}, level {0}, curScore {0}, highScore {0}, 
  nextBlock{BlockType::JBlock}, curBlock{}, td{new TextDisplay{}} //, gd{nullptr}
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
  
  unique_ptr<Block> newBlock = makeBlock->buildBlock(BlockType::JBlock);
  int shift = 0; int down = 0;

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

  // for (i)
  // cout << prevX << " & " << prevY << endl;
  if (!clear) {
    cout << "not clear" << endl;
    for (int i = prevY + blockDim - 1; i >= prevY; --i) {
      for (int j = prevX; j < prevX + blockDim; ++j) {

        if (lastConfig[i][j] != ' ') {
          cout << "(" << i << "," << j << ")" << endl;

          theBoard[i][j].setUnfilled();
          theBoard[i][j].setType(BlockType::empty);
        }
      }
    }
  }
  // cout << "new block" << endl;
  vector<vector<char>> blockBlock = newBlock->getConfig();

  for (int i = 0; i < blockDim; ++i) {
    for (int j = 0; j < blockDim; ++j) {
      if (blockBlock[i][j] != ' ') {
        if (move != "") {
          theBoard[i + prevY + down][j + prevX + shift].setFilled();
          theBoard[i + prevY + down][j + prevX + shift].setType(BlockType::JBlock);
        } else {
          theBoard[i][j].setFilled();
          theBoard[i][j].setType(BlockType::JBlock);
        }

      }
    }
  }

  if (move == "") {
    cout << "place block" << endl;
    clear = false; 
    prevX = newBlock->getLeftCorner()[0];
    prevY = newBlock->getLeftCorner()[1];
    cout << prevX << " & " << prevY << endl;
    lastConfig = blockBlock;
  } else {
    prevX += shift;
    prevY += down;
    lastConfig = blockBlock;
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
