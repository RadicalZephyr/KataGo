#include "../tests/tests.h"

#include "../search/asyncbot.h"
#include "../tests/testsearchcommon.h"

using namespace std;
using namespace TestSearchCommon;

void Tests::runWallSearchTests() {
  cout << "Running wall search tests" << endl;
  NeuralNet::globalInitialize();

  const bool logToStdout = false;
  const bool logToStderr = false;
  const bool logTime = false;
  Logger logger(nullptr, logToStdout, logToStderr, logTime);
  logger.addOStream(cout);

  string modelFile = "/dev/null";
  NNEvaluator* nnEval = startNNEval(modelFile,logger,"",NNPos::MAX_BOARD_LEN,NNPos::MAX_BOARD_LEN,0,true,false,false,true,false);

  SearchParams params;
  params.maxVisits = 10;
  Search* search = new Search(params, nnEval, &logger, "wallSearchSeed");

  Board board(5,5);
  vector<Loc> walls;
  walls.push_back(Location::getLoc(2,2,board.x_size));
  testAssert(board.setWallsFailIfNoLibs(walls));

  Player nextPla = P_BLACK;
  Rules rules = Rules::getTrompTaylorish();
  BoardHistory hist(board,nextPla,rules,0);
  hist.setInitialTurnNumber(board.numStonesOnBoard());

  search->setPosition(nextPla,board,hist);
  search->runWholeSearch(nextPla);

  delete search;
  delete nnEval;
  NeuralNet::globalCleanup();
}
