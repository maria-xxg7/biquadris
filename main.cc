#include <iostream>
#include <string>
#include <sstream>
#include "game.h"
#include "board.h"
#include "window.h"
using namespace std;

int main( int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  Xwindow wd1;
  Xwindow wd2;

  int countFile = 0;
  string filename1 = "";
  string filename2 = "";
  bool start = false;
  string levelStart = 0;
  bool seed = false;
  string seedSet = "";
  bool text = false;

  for (int i = 1; i <= argc - 1; ++i) { // since first argument is the executable 
		string s = argv[i];
    if (s == "-scriptfile1") {
      ++countFile;
      filename1 = argv[i + 1];
    }
    if (s == "-scriptfile2") {
      ++countFile;
      filename2 = argv[i + 1];
    }
    if (s == "-startlevel") {
      start = true;
      levelStart = argv[i + 1];
    } 
    if (s == "-seed") {
      seed = true;
      seedSet = argv[i + 1];
    }
    if (s == "text") {
      text = true;
    }
	}

  Game theGame = Game(wd1, wd2);
  theGame.startGame();

  while (true) {
    if (theGame.getTesting()) {
      ifstream file {theGame.getFilename()};
      theGame.playerPlay(file);
      if (!theGame.getTesting()) {
        break;
      }
    } else if (!theGame.getTesting()) {
      theGame.playerPlay(cin);
    }
  }
  // int numLineclears = 0;


  // KEEP TEST HARNESS FOR TESTING 
  
  // Board b;
  // Xwindow wd;
  // string cmd;

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
  //         if (b.finishedMove()) {
  //           b.moveBlock("save");
  //           b.dropBlock();
  //           if (b.isLose()) {
  //             cout << "LOSE! END GAME!" << endl;
  //           }
  //           b.updateScore();
  //         }
  //         cout << b;
  //       } else if (cmd == "right") {
  //         b.moveBlock(cmd);
  //         if (b.finishedMove()) {
  //           b.moveBlock("save");
  //           b.dropBlock();
  //           if (b.isLose()) {
  //             cout << "LOSE! END GAME!" << endl;
  //           }
  //           b.updateScore();
  //         }
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
  //       } else if (cmd == "blind") {
  //         b.setBlind(true);
  //         b.blinding(true);
  //         cout << b;
  //       } else if (cmd == "drop") {
  //        b.moveBlock("save");
  //         b.dropBlock();
  //         if (b.isLose()) {
  //           cout << "LOSE! END GAME!" << endl;
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
