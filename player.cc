#include "player.h"

Player::Player(bool playerNum, int level, Board &b) : playerNum{playerNum}, level{level}, 
      nextBlock{BlockType::empty}, playerBoard{new Board{b}} {}
Player::~Player() {
  delete playerBoard;
}

bool Player::validMove(Board &b, bool playerTurn, string move) {
  if (playerTurn != playerNum) {
    cout << "Not your turn" << endl;
  } 
  if ((move != "clockwise") && (move != "counterclockwise") && (move != "left")
     && (move != "right") && (move != "down")) {
    cout << "Invalid moce" << endl;
  }
  return true;
}


