#include <memory>
#include "board.h"
#include "blockgenerator.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelhard.h"


class Game {
  vector<shared_ptr<Board>> playerBoards;
  vector<shared_ptr<BlockGenerator>> playerLevels;
  string testingFilename;
  bool playerTurn;
  bool isRandom;
  bool testing = false;
  bool onSpecialActions = false;
  string file1;
  string file2;
 
  public:
    Game(Xwindow &wd1, Xwindow &wd2, string file1 = "sequence1.txt", string file2 = "sequence2.txt");
    void startGame();
    void restartGame();
    void levelUp();
    void levelDown();
    void setLevel();
    void setSpecialActions(bool setOn);
    bool getSpecialActions();
    bool getTesting();
    string getFilename();
    void noRandom(string filename);
    void random();
    BlockType stringToBlock(string blockChar);
    void playerPlay(istream& input);
};
