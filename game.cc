#include "game.h"
using namespace std;

// adding textdisplay and graphics display to this

Game::Game(Xwindow &wd1, Xwindow &wd2, bool txt, string file1, string file2) : playerTurn {0}, isRandom{true}, testing {false}, onSpecialActions{false},
  file1{file1}, file2{file2}, seedValue{8} {

  int len = commands.size();
  for (int i = 0; i < len; ++i) {
    tempCmd->addCommand(commands[i]); // add commands
  }

  shared_ptr<Board> boardPlayer1 = make_shared<Board>();
  shared_ptr<Board> boardPlayer2 = make_shared<Board>();

  shared_ptr<BlockGenerator> levelPlayer1 = make_shared<LevelZero>(file1);
  shared_ptr<BlockGenerator> levelPlayer2 = make_shared<LevelZero>(file2);
  
  playerBoards.emplace_back(boardPlayer1);
  playerBoards.emplace_back(boardPlayer2);
  if (txt) {
    playerBoards[0]->setWindow(false);
    playerBoards[1]->setWindow(false);
  } else {
    playerBoards[0]->setWindow(true);
    playerBoards[1]->setWindow(true);
  }
  playerBoards[0]->init(wd1);
  playerBoards[1]->init(wd2);

  playerLevels.emplace_back(levelPlayer1);
  playerLevels.emplace_back(levelPlayer2);
}

void Game::setUpGame(string filename1, string filename2, bool start, string levelStart, 
                   bool seed, unsigned int seedSet) {
  if (start) {
    int i;
    istringstream levelInt{levelStart};
    levelInt >> i;
    setLevel(i);
    startLevel = i;
  } 
  
  if (seed) {
    seedValue = seedSet;
  }

  if (filename1 != "") {
    setFile(0, filename1);
  } else {
    setFile(0, "sequence1.txt");
  }
  if (filename2 != "") {
    setFile(1, filename2);
  } else {
    setFile(1, "sequence2.txt");
  }
}

void Game::startGame() {
  // init player 1 board
  playerLevels[0]->newMove(playerBoards[0]);
  playerBoards[0]->setCurBlock(playerBoards[0]->getBlockType());
  playerBoards[0]->moveBlock("");
  playerLevels[0]->newMove(playerBoards[0]);
  playerBoards[0]->setNumMultiDrop(0);

  cout << "PLAYER 1: " << endl;
  cout << *playerBoards[0] << endl;

  // init player 2 board
  playerLevels[1]->newMove(playerBoards[1]);
  playerBoards[1]->setCurBlock(playerBoards[1]->getBlockType());
  playerBoards[1]->moveBlock("");
  playerLevels[1]->newMove(playerBoards[1]);
  playerBoards[1]->setNumMultiDrop(0);

  cout << "PLAYER 2: " << endl;
  cout << *playerBoards[1] << endl;
}

void Game::restartGame() {
  // reset game how to reset textdisplay
  playerBoards[0]->clearBoard();
  playerBoards[1]->clearBoard();

  playerLevels[0] = make_shared<LevelZero>(file1);
  playerLevels[1] = make_shared<LevelZero>(file2);
  if (startLevel != 0) {
    string setLevelTo = to_string(startLevel);
    while (playerBoards[0]->getLevel() != startLevel && playerBoards[0]->getLevel() != startLevel) {
      levelUp();
      playerTurn = !playerTurn;
      levelUp();
    }
  }
  startGame();
  playerTurn = 0;
  isRandom = true;
}

void Game::levelUp() {
  int playerLevel = playerBoards[playerTurn]->getLevel();
  if ( playerLevel == 4) {
    return;
  } else {
    if (playerLevel == 0) {
      playerLevels[playerTurn] = make_shared<LevelOne>();
    } else if (playerLevel == 1) {
      playerLevels[playerTurn] = make_shared<LevelTwo>();
    } else if (playerLevel == 2) {
      playerLevels[playerTurn] = make_shared<LevelHard>(3);
    } else {
      playerLevels[playerTurn] = make_shared<LevelHard>(4);
      playerBoards[playerTurn]->setObstacle(true);
    }
  }
  playerBoards[playerTurn]->setLevel(playerLevel + 1);
}

// implement a level factory plz, and board or player has to have
// a factory field
void Game::levelDown() {
  int playerLevel = playerBoards[playerTurn]->getLevel();
  if (playerLevel == 0) {
    return;
  } else {
    if (playerLevel == 1) {
      if (playerTurn) {
        playerLevels[playerTurn] = make_shared<LevelZero>(file2);
      } else {
        playerLevels[playerTurn] = make_shared<LevelZero>(file1); 
      }
    } else if (playerLevel == 2) {
       playerLevels[playerTurn] = make_shared<LevelOne>();
    } else if (playerLevel == 3) {
      playerLevels[playerTurn] = make_shared<LevelTwo>();
    } else {
      playerLevels[playerTurn] = make_shared<LevelHard>(3);
      playerBoards[playerTurn]->setObstacle(false);
    }
  }
  playerBoards[playerTurn]->setLevel(playerLevel - 1);
}

void Game::setLevel(int level) {
  while (playerBoards[playerTurn]->getLevel() != level) {
    levelUp();
  }
  playerTurn = !playerTurn;
  while (playerBoards[playerTurn]->getLevel() != level) {
    levelUp();
  }
  playerTurn = 0;
}

void Game::setFile(bool whichPlayer, string fileGiven) {
  if (whichPlayer) {
    file2 = fileGiven;
  } else {
    file1 = fileGiven;
  }
  if (playerBoards[whichPlayer]->getLevel() == 0) {
   playerLevels[whichPlayer] = make_shared<LevelZero>(fileGiven);
  }
}

void Game::setSpecialActions(bool setOn) { onSpecialActions = setOn; }

bool Game::getSpecialActions() { return onSpecialActions; }

bool Game::getTesting() { return testing; }

string Game::getFilename() { return testingFilename; }

void Game::noRandom(string filename) {
  int playerLevel = playerBoards[playerTurn]->getLevel();
  playerLevels[playerTurn] = make_shared<LevelHard>(playerLevel, filename);
  isRandom = false;
}

void Game::random() {
  if (isRandom) {
    return;
  }
  int playerLevel = playerBoards[playerTurn]->getLevel();
  playerLevels[playerTurn] = make_shared<LevelHard>(playerLevel);
  isRandom = true;
}

BlockType Game::stringToBlock(string blockChar) {
 if (blockChar == "O") {
  return BlockType::OBlock;
 } else if (blockChar == "I") {
  return BlockType::IBlock;
 } else if (blockChar == "J") {
  return BlockType::JBlock;
 } else if (blockChar == "L") {
  return BlockType::LBlock;
 } else if (blockChar == "S") {
  return BlockType::SBlock;
 } else if (blockChar == "Z") {
  return BlockType::ZBlock;
 } else if (blockChar == "T") {
  return BlockType::TBlock;
 } else {
  return BlockType::empty;
 }
}

void Game::dropSequence(istream& input) {
  shared_ptr<Board> bInPlay = playerBoards[playerTurn];
  int playerNumber = playerTurn + 1;
  bInPlay->moveBlock("save");
      bInPlay->dropBlock();
      if (bInPlay->isLose()) {
        cout << "Player " << playerNumber << "LOST! END GAME!" << endl;
        restartGame();
        playerTurn = 0;
        cout << "Player " << playerTurn + 1 << " enter your moves: " << endl;
      }
      bInPlay->updateScore();
      playerBoards[playerTurn]->moveBlock("");
      playerLevels[playerTurn]->newMove(bInPlay);
      cout << *bInPlay;
      if (playerBoards[playerTurn]->getSpecial() && getSpecialActions()) {
        cout << "Special action triggered (chose from the following special actions): " << endl;
        cout << "1. Blind 2. Heavy 3. Force" << endl;
        cout << "Enter action name here: " << endl;
        string action;
        input >> action;
        if (action == "Blind") {
          playerBoards[!playerTurn]->setBlind(true);
          playerBoards[!playerTurn]->blinding(true);
        } else if (action == "Heavy") {
          playerBoards[!playerTurn]->setHeavy(true);
        } else if (action == "Force") {
          string blockForced;
          cout << "Enter block type: " << endl;
          input >> blockForced;
          playerBoards[!playerTurn]->clearPlaced();
          playerBoards[!playerTurn]->setCurBlock(stringToBlock(blockForced));
          playerBoards[!playerTurn]->moveBlock("");
          cout << *playerBoards[!playerTurn];
        }
      }
      if (playerBoards[playerTurn]->getNumMultiDrop() == 0) {
        cout << "Turn ended. Next player's turn" << endl;
        playerTurn = !playerTurn;
        cout << "Player " << playerTurn + 1 << " enter your moves: " << endl;
      }

}


void Game::playerPlay(istream& input) {
  string rawCmd; 
  cout << "Player " << playerTurn + 1 << " enter your moves: " << endl;
  shared_ptr<Board> bInPlay = make_shared<Board>();
  bool notFound = false;
  while (input >> rawCmd) { 
    string rawCmdStr = "";
    int repeat = 0; // how mnay times to call the command
    if (isdigit(rawCmd[0])) {
      istringstream iss(rawCmd);  // handle numbers in front of cmd
      iss >> repeat;
      for (char c : rawCmd) {
        if (!isdigit(c)) {
          rawCmdStr += c;
        }
      }
    }

    string cmd;
    isdigit(rawCmd[0]) ? cmd = tempCmd->getCommand(rawCmdStr) : cmd = tempCmd->getCommand(rawCmd);

    if (cmd == "") {
      cout << "Invalid command. Please enter a valid command" << endl;
      notFound = true;
    } else {
      notFound = false;
    }

    if (!isdigit(rawCmd[0]) || cmd == "restart" || cmd == "hint" || cmd == "random" || cmd == "norandom") {
      repeat = 1;
    }

    int playerNumber = playerTurn + 1;
    bInPlay = playerBoards[playerTurn];

    while(repeat > 0 && !notFound) {
      --repeat;
      playerBoards[playerTurn]->setNumMultiDrop(repeat);
    if (bInPlay->isLose()) {
        cout << playerNumber << "LOST! END GAME!" << endl;
        restartGame();
    } else if (cmd == "left") {
      bInPlay->moveBlock(cmd);
      if (bInPlay->finishedMove()) {
        dropSequence(input);
      }
      cout << *bInPlay << endl;
    } else if (cmd == "right") {
      bInPlay->moveBlock(cmd);
      if (bInPlay->finishedMove()) {
        dropSequence(input);
      }
      cout << *bInPlay << endl;
    } else if (cmd == "down") {
      bInPlay->moveBlock(cmd);
      if (bInPlay->finishedMove()) {
        dropSequence(input);
      }
      cout << *bInPlay << endl;
    } else if (cmd == "clockwise") {
      bInPlay->moveBlock(cmd);
      if (bInPlay->finishedMove()) {
        dropSequence(input);
      }
      cout << *bInPlay << endl;
    } else if (cmd == "counterclockwise") {
      bInPlay->moveBlock(cmd);
      if (bInPlay->finishedMove()) {
        dropSequence(input);
      }
      cout << *bInPlay << endl;
    } else if (cmd == "drop") {
      dropSequence(input);
      cout << *bInPlay << endl;
    } else if (cmd == "levelup") {
      levelUp();
      cout << *bInPlay;
      cout << "Player " << playerNumber << " leveled up! Enter your moves: " << endl;
    } else if (cmd == "leveldown") {
      levelDown();
      cout << *bInPlay;
      cout << "Player " << playerNumber << " leveled down! Enter your moves: " << endl;
    } else if (cmd == "norandom") {
      string filename;
      input >> filename;
      noRandom(filename);
      cout << "Player " << playerNumber << " enter your moves: " << endl;
    } else if (cmd == "random") {
      random();
      cout << "Player " << playerNumber << " enter your moves: " << endl;
    } else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" || cmd == "Z" 
              || cmd == "S" || cmd == "T") {
        playerBoards[playerTurn]->clearPlaced();
        playerBoards[playerTurn]->setCurBlock(stringToBlock(cmd));
        playerBoards[playerTurn]->moveBlock("");
        cout << "Player " << playerNumber << " enter your moves: " << endl;
    } else if (cmd == "sequence") {
      string filename;
      input >> filename;
      testingFilename = filename;
      testing = true;
      cout << "Player " << playerNumber << " enter your moves: " << endl;
      return;
    } else if (cmd == "demo") {
      string set;
      input >> set;
      if (set == "on") {
        setSpecialActions(true);
        cout << "You've turned on the special enhancements, please enjoy!" << endl;
      } else {
        cout << "You've turned off the special enhancements!" << endl;
        setSpecialActions(false);
      }
    } else if (cmd == "restart") {
      restartGame();
      cout << "Reset game! Start again!" << endl;
      playerTurn = 0;
    } else {
      break;
    } // if
    }
  } // while
  
  if (input.eof() && testing) {
    cout << "Testing file done reading! End of file met!" << endl; 
    cout << "You can chose to continue playing with another testing suit by calling the sequence command again or play normally" << endl; 
    testing = false;
    return;
  }
}

