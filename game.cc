#include "game.h"
using namespace std;

// adding textdisplay and graphics display to this

Game::Game(Xwindow &wd1, Xwindow &wd2) : playerTurn {0} {
  shared_ptr<Board> boardPlayer1 = make_shared<Board>();
  shared_ptr<Board> boardPlayer2 = make_shared<Board>();

  shared_ptr<BlockGenerator> levelPlayer1 = make_shared<LevelZero>("sequence1.txt");
  shared_ptr<BlockGenerator> levelPlayer2 = make_shared<LevelZero>("sequence2.txt");
  
  playerBoards.emplace_back(boardPlayer1);
  playerBoards.emplace_back(boardPlayer2);
  playerBoards[0]->init(wd1);
  playerBoards[1]->init(wd2);

  playerLevels.emplace_back(levelPlayer1);
  playerLevels.emplace_back(levelPlayer2);
}

void Game::restartGame() {
  // reset game how to reset textdisplay
  playerBoards[0]->clearBoard();
  playerBoards[1]->clearBoard();

  playerTurn = 0;
}

void Game::startGame() {
  // init player 1 board
  playerLevels[0]->newMove(playerBoards[0]);
  playerBoards[0]->setCurBlock(playerBoards[0]->getBlockType());
  playerBoards[0]->moveBlock("");
  playerLevels[0]->newMove(playerBoards[0]);

  // cout << "Cur: " << playerBoards[0]->getCurBlock() << endl;
  // cout << "Next: " << playerBoards[0]->getNextType() << endl;
  cout << "PLAYER 1: " << endl;
  cout << *playerBoards[0] << endl;

  // init player 2 board
  playerLevels[1]->newMove(playerBoards[1]);
  playerBoards[1]->setCurBlock(playerBoards[1]->getBlockType());
  playerBoards[1]->moveBlock("");
  playerLevels[1]->newMove(playerBoards[1]);
  cout << "PLAYER 2: " << endl;
  cout << *playerBoards[1] << endl;
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
      playerBoards[playerTurn]->setHeavy(true);
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
        playerLevels[playerTurn] = make_shared<LevelZero>("sequence2.txt");
      } else {
        playerLevels[playerTurn] = make_shared<LevelZero>("sequence1.txt");
      } 
    } else if (playerLevel == 2) {
       playerLevels[playerTurn] = make_shared<LevelOne>();
    } else if (playerLevel == 3) {
      playerLevels[playerTurn] = make_shared<LevelTwo>();
      playerBoards[playerTurn]->setHeavy(false);
      // turn off heavy
    } else {
      playerLevels[playerTurn] = make_shared<LevelHard>(3);
      playerBoards[playerTurn]->setObstacle(false);
      // turn off * function;
    }
  }
  playerBoards[playerTurn]->setLevel(playerLevel - 1);
}

void Game::noRandom(string filename) {
  int playerLevel = playerBoards[playerTurn]->getLevel();
  playerLevels[playerTurn] = make_shared<LevelHard>(playerLevel, filename);
}

void Game::random() {
  // change so it checks if it's alr random plz
  int playerLevel = playerBoards[playerTurn]->getLevel();
  playerLevels[playerTurn] = make_shared<LevelHard>(playerLevel);
}

void Game::playerPlay(bool player) {
  playerTurn = player;
  string playerNumber;
  if (player) {
    playerNumber = "2 ";
  } else {
    playerNumber = "1 ";
  }
  cout << "Player " << playerNumber << "enter your moves: " << endl;
  // cin.exceptions(ios::eofbit|ios::failbit);
  shared_ptr<Board> bInPlay = playerBoards[playerTurn];
  string cmd;
  // Xwindow wd;
  // try {
    while (cin >> cmd) {  
        // cout << "reading commands" << endl;
        if (bInPlay->isLose()) {
            cout << playerNumber << "LOST! END GAME!" << endl;
            restartGame();
        } else if (cmd == "left") {
          bInPlay->moveBlock(cmd);
          cout << *bInPlay;
          cout << "Player " << playerNumber << "enter your moves: " << endl;
        } else if (cmd == "right") {
          // cout << "Cur: " << playerBoards[0]->getCurBlock() << endl;
          // cout << "Next: " << playerBoards[0]->getNextType() << endl;
          bInPlay->moveBlock(cmd);
          // cout << "after move" << endl;
          // cout << "Cur: " << playerBoards[0]->getCurBlock() << endl;
          // cout << "Next: " << playerBoards[0]->getNextType() << endl;
          cout << *bInPlay;
          cout << "Player " << playerNumber << "enter your moves: " << endl;
        } else if (cmd == "down") {
          bInPlay->moveBlock(cmd);
          cout << *bInPlay;
          cout << "Player " << playerNumber << "enter your moves: " << endl;
        } else if (cmd == "clockwise") {
          bInPlay->moveBlock(cmd);
          cout << *bInPlay;
          cout << "Player " << playerNumber << "enter your moves: " << endl;
        } else if (cmd == "counterclockwise") {
          bInPlay->moveBlock(cmd);
          cout << *bInPlay;
          cout << "Player " << playerNumber << "enter your moves: " << endl;
        } else if (cmd == "drop") {
          bInPlay->moveBlock("save");
          bInPlay->dropBlock();
          if (bInPlay->isLose()) {
            cout << "Player " << playerNumber << "LOST! END GAME!" << endl;
            restartGame();
          }
          bInPlay->updateScore();
          playerBoards[playerTurn]->moveBlock("");
          playerLevels[playerTurn]->newMove(bInPlay);
          cout << *bInPlay;
          cout << "Turn ended. Next player's turn" << endl;
          return;
        } else if (cmd == "levelup") {
          levelUp();
          cout << "Player " << playerNumber << "leveled up! Enter your moves: " << endl;
        } else if (cmd == "leveldown") {
          levelDown();
          cout << "Player " << playerNumber << "leveled down! Enter your moves: " << endl;
        } else if (cmd == "norandom") {
          string filename;
          cin >> filename;
          noRandom(filename);
          cout << "Player " << playerNumber << "enter your moves: " << endl;
        } else if (cmd == "random") {
          random();
          cout << "Player " << playerNumber << "enter your moves: " << endl;
        } else if (cmd == "reset") {
          restartGame();
          cout << *bInPlay;
          cout << "Reset game! Start again!" << endl;
        } else {
          break;
        } // if
      } // while
  // } catch (ios::failure&) {}
}

