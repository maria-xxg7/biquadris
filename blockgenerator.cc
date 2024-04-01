#include "blockgenerator.h"

BlockGenerator::BlockGenerator(bool playerNum, int level, Board &b) : playerNum{playerNum}, level{level}, 
      nextBlock{BlockType::empty} {}

BlockType BlockGenerator::stringToBlock(char blockChar) {
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


