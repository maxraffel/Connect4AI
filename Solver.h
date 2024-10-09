#include "TranspositionTable.h"


class Solver {
    public:
        void negamaxStart(Position &pos);
        int nodesVisited = 0;
    private:
        int negamax(Position &pos, int alpha, int beta);
        TranspositionTable ttable = TranspositionTable(8000000);
        int columnOrder[6] = {2, 3, 1, 4, 0, 5};
        uint64_t winningPositions(uint64_t playerMask, uint64_t mask);
        uint64_t allowedMoves(uint64_t playerMask, uint64_t mask);
        int moveScore(uint64_t moves);
};