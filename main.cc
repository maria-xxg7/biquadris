#include <iostream>
#include <string>
#include <sstream>
#include "board.h"
#include "window.h"
using namespace std;

int main() {
  cout << "suffering" << endl;
  // cin.exceptions(ios::eofbit|ios::failbit);
  Board b;
  b.init();
  b.clearBoard();
  b.moveBlock("");
  // string cmd;
  // Xwindow wd;

  // try {
  //   while (cin >> cmd) {
  //       if (cmd == "commands") {
  //         cout << "-----" << endl;
  //         cout << "Commands:" << endl;
  //         cout << "init - initializes board" << endl;
  //         cout << "set - sets the block type & places new block" << endl;
  //         cout << "left/right/clockwise/counterclockwise" << endl;
  //         cout << "drop - drops the block" << endl;
  //         cout << "stop - ends the game" << endl;
  //         cout << "-----" << endl;
  //       } else if (cmd == "init") {
  //         b.init(wd);
  //         cout << "Initialized board." << endl;
  //         cout << b;
  //       } else if (cmd == "set") {
  //         char c;
  //         cin >> c;
  //         switch(c) {
  //           case 'I':
  //             b.setBlockType(BlockType::IBlock);
  //             break;
  //           case 'J':
  //             b.setBlockType(BlockType::JBlock);
  //             break;
  //           case 'L':
  //             b.setBlockType(BlockType::LBlock);
  //             break;
  //           case 'O':
  //             b.setBlockType(BlockType::OBlock);
  //             break;
  //           case 'S':
  //             b.setBlockType(BlockType::SBlock);
  //             break;
  //           case 'Z':
  //             b.setBlockType(BlockType::ZBlock);
  //             break;
  //           case 'T':
  //             b.setBlockType(BlockType::TBlock);
  //             break;
  //         }
  //         b.moveBlock("");
  //         if (b.isLose()) {
  //           cout << "LOSE! END GAME!" << endl;
  //         }
  //         cout << b;
  //       } else if (cmd == "left") {
  //         b.moveBlock(cmd);
  //         cout << b;
  //       } else if (cmd == "right") {
  //         b.moveBlock(cmd);
  //         cout << b;
  //       } else if (cmd == "down") {
  //         b.moveBlock(cmd);
  //         cout << b;
  //       } else if (cmd == "clockwise") {
  //         b.moveBlock(cmd);
  //         cout << b;
  //       } else if (cmd == "counterclockwise") {
  //         b.moveBlock(cmd);
  //         cout << b;
  //       } else if (cmd == "drop") {
  //         b.moveBlock("save");
  //         b.dropBlock();
  //         if (b.isLose()) {
  //           cout << "LOSE! END GAME!" << endl;
  //         }
  //         cout << "Calling update score" << endl;
  //         for (int i = RESERVED; i < BOARD_H + RESERVED; ++i) {
  //           if (b.checkLineClear(i)) {
  //             b.lineClear(i);
  //           }
  //         }
  //         b.updateScore();
  //         cout << b;
  //       } else if (cmd == "stop") {
  //         cout << "Thanks for playing :)" << endl;
  //         break;
  //       } else {
  //         break;
  //       } // if
  //     } // while
  // } catch (ios::failure&) {}
}
