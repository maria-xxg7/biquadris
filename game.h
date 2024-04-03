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
  bool playerTurn;

  public:
    Game(Xwindow &wd1, Xwindow &wd2);
    void restartGame();
    void startGame();
    void levelUp();
    void levelDown();
    void playerPlay();
};
