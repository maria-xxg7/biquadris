#include <memory>
#include <string>
#include "board.h"
#include "blockgenerator.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelhard.h"
#include "command.h"

class Game {
  vector<shared_ptr<Board>> playerBoards;
  vector<shared_ptr<BlockGenerator>> playerLevels;
  string testingFilename;
  bool playerTurn;
  bool isRandom;
  bool testing = false;
  bool onSpecialActions = false;
  bool displayText = true;
  int startLevel = 0;
  string file1;
  string file2;
  unsigned int seedValue;

  vector<string> commands = {"left", "right", "down", "clockwise", "counterclockwise",
    "drop", "levelup", "leveldown", "norandom", "random", "sequence", 
    "I", "J", "L", "O", "S", "Z", "T", "restart", "heavy", "blind", "force" };
  shared_ptr<Command> tempCmd = make_shared<Command>();
 
  public:
    Game(Xwindow &wd1, Xwindow &wd2, bool txt, string file1 = "sequence1.txt", string file2 = "sequence2.txt");
    void setUpGame(string filename1, string filename2, bool start, string levelStart, 
                   bool seed, unsigned int seedSet);
    void startGame();
    void restartGame();
    void levelUp();
    void levelDown();
    void setLevel(int level);
    void setFile(bool whichPlayer, string fileGiven);
    void setSpecialActions(bool setOn);
    bool getSpecialActions();
    bool getTesting();
    string getFilename();
    void noRandom(string filename);
    void random();
    BlockType stringToBlock(string blockChar);
    void dropSequence(istream& input); 
    void playerPlay(istream& input);
};
