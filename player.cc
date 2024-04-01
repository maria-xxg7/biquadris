// #include "player.h"

// Player::Player(bool playerNum, int level, Board &b) : playerNum{playerNum}, level{level}, 
//       nextBlock{BlockType::empty}, playerBoard{new Board{b}} {}
      
// Player::~Player() {
//   delete playerBoard;
// }

// BlockType Player::stringToBlock(char blockChar) {
//  if (blockChar == 'O') {
//   return BlockType::OBlock;
//  } else if (blockChar == 'I') {
//   return BlockType::IBlock;
//  } else if (blockChar == 'J') {
//   return BlockType::JBlock;
//  } else if (blockChar == 'L') {
//   return BlockType::LBlock;
//  } else if (blockChar == 'S') {
//   return BlockType::SBlock;
//  } else if (blockChar == 'Z') {
//   return BlockType::ZBlock;
//  } else if (blockChar == 'T') {
//   return BlockType::TBlock;
//  } else {
//   return BlockType::empty;
//  }
// }

// // implement a level factory plz, and board or player has to have
// // a factory field so each tetris board will have a factory
// // which then is called such that nextBlock = factory.newMove should
// // produce new enum types (do not need to pass in board, or could be a
// // part of player that contains board)
// // need a reset function for when loses and then play again;
// // turn heavy on inside the new factory or in the level up and down??
// void Player::levelUp(Board &b, bool playerTurn) {
//   if (b.getLevel() == 4) {
//     return;
//   } else {
//     if (b.getLevel() == 0) {
//       levelFactory = new levelonefactory;
//     } else if (b.getLevel() == 1) {
//       levelFactory = new leveltwofactory;
//     } else if (b.getLevel() == 2) {
//       levelFactory = new levelthreefactory;
//      // turn on heavy
//     } else {
//      // turn on * function
//       levelFactory = new levelfourfactory;
//     }
//   }
//   setLevel(b.getLevel() + 1);
// }

// // implement a level factory plz, and board or player has to have
// // a factory field
// void Player::levelDown(Board &b, bool playerTurn) {
//   if (b.getLevel() == 0) {
//     return;
//   } else {
//     if (b.getLevel() == 1) {
//       levelFactory = new levelzerofactory;
//     } else if (b.getLevel() == 2) {
//       levelFactory = new levelonefactory;
//     } else if (b.getLevel() == 3) {
//       levelFactory = new leveltwofactory;
//       // turn off heavy
//     } else {
//       levelFactory = new levelthreefactory;
//       // turn off * function;
//     }
//   }
//   setLevel(b.getLevel() - 1);
// }


