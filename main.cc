#include <iostream>
#include <string>
#include <sstream>
#include "game.h"
#include "board.h"
#include "window.h"
#include "command.h"
using namespace std;

int main( int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  Xwindow wd1;
  Xwindow wd2;

  try {
    string filename1 = "";
    string filename2 = "";
    bool start = false;
    string levelStart;
    bool seed = false;
    int seedSet = 0;
    bool text = false;

    for (int i = 1; i <= argc - 1; ++i) { // since first argument is the executable 
      string s = argv[i];
      if (s == "-scriptfile1") {
        filename1 = argv[i + 1];
      }
      if (s == "-scriptfile2") {
        filename2 = argv[i + 1];
      }
      if (s == "-startlevel") {
        cout << "Started Level" << endl;
        start = true;
        levelStart = argv[i + 1];
      } 
      if (s == "-seed") {
      }
      if (s == "-text") {
        text = true;
      }
    }
    Game theGame = Game(wd1, wd2, text);
    theGame.setUpGame(filename1, filename2, start, levelStart, seed, seedSet);
    theGame.startGame();

    while (true) {
      if (theGame.getTesting()) {
        break;
        ifstream file {theGame.getFilename()};
        theGame.playerPlay(file);
        break;
        if (!theGame.getTesting()) {
          break;
        }
      } else if (!theGame.getTesting()) {
        theGame.playerPlay(cin);
        break;
      }
    }
  } catch(ios::failure&) {}
}
