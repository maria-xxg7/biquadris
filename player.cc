#include "player.h"

Player::Player(bool playerNum, int level, Board &b) : playerNum{playerNum}, level{level}, 
      nextBlock{BlockType::empty}, playerBoard{new Board{b}} {}
      
Player::~Player() {
  delete playerBoard;
}

BlockType Player::stringToBlock(char blockChar) {
 if (blockChar == 'O') {
  return BlockType::OBlock;
 } else if (blockChar == 'I') {
  return BlockType::IBlock;
 } else if (blockChar == 'J') {
  return BlockType::JBlock;
 } else if (blockChar == 'L') {
  return BlockType::LBlock;
 } else if (blockChar == 'S') {
  return BlockType::SBlock;
 } else if (blockChar == 'Z') {
  return BlockType::ZBlock;
 } else if (blockChar == 'T') {
  return BlockType::TBlock;
 } else {
  return BlockType::empty;
 }
}


