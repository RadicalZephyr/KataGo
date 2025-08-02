#include "../tests/tests.h"

#include "../search/asyncbot.h"
#include "../tests/testsearchcommon.h"

using namespace std;
using namespace TestSearchCommon;

static void runWallPositions(NNEvaluator* nnEval, Logger& logger)
{
    SearchParams params;
    params.maxVisits = 200;

    Search* search = new Search(params, nnEval, &logger, getSearchRandSeed());

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
}

void Tests::runWallSearchTests(const string& modelFile, bool inputsNHWC, bool useNHWC, int symmetry, bool useFP16) {
  TestCommon::overrideForBackends(inputsNHWC, useNHWC);
  cout << "Running wall search tests" << endl;
  NeuralNet::globalInitialize();

  const bool logToStdout = false;
  const bool logToStderr = false;
  const bool logTime = false;
  Logger logger(nullptr, logToStdout, logToStderr, logTime);

  NNEvaluator* nnEval = startNNEval(modelFile,logger,"",NNPos::MAX_BOARD_LEN,NNPos::MAX_BOARD_LEN,symmetry,inputsNHWC,useNHWC,useFP16,false,false);

  runWallPositions(nnEval, logger);
  delete nnEval;

  NeuralNet::globalCleanup();
  cout << "Done" << endl;
}
