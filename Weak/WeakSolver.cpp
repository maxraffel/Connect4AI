#include <iostream>
#include "../Position.h"
#include "WeakSolver.h"
#include <cstring>
#include <cstdint>

using namespace std;

#ifndef SOLVER_H
#define SOLVER_H


int WeakSolver::negamax(Position &pos, int alpha, int beta) {
    nodesVisited++;
    // return 0 if draw
    if (pos.turns() == pos.mheight*pos.mwidth) return 2;

    // return 1 if it is a winning move
    for (int i = 0; i < pos.mwidth; i++) {
        if (pos.canPlay(i) && pos.isWinningMove(i)) {
            return 3;
        }
    }

    // after all the fast ways to get a score are done, see if we stored key in lookup table
    uint64_t key = pos.getKey();
    int value = ttable.get(key);
    if (value) {
        return value - 2;
    }
    
    // now start computing new stuff

    for (int k = 0; k < pos.mwidth; k++) {
        int i = columnOrder[k];

        if (!pos.canPlay(i)) continue;

        Position pos2(pos);
        pos2.play(i);
        int score = -negamax(pos2, -beta, -alpha);

        if (score >= beta) { // if it is an optimal score then we can stop
            return beta;
        } 
        if (score > alpha) alpha = score; // update new best
    }
    ttable.set(key, alpha + 2);
    return alpha;
}



void WeakSolver::negamaxStart(Position &pos) {
    nodesVisited = 0;

    for (int i = 0; i < pos.mwidth; i++) {
        if (pos.canPlay(i) && pos.isWinningMove(i)) {
            pos.play(i);
            return;
        }
    }

    int move;
    int min = -2;
    
    for (int i = 0; i < pos.mwidth; i++) {
        Position pos2(pos);
        if (pos.canPlay(i)) {
            pos2.play(i);
            int score = -negamax(pos2, -1, 1);
            if (score > min) {
                min = score;
                move = i;
                if (score == 1) break;
            }
        }
    }
    cout << endl;
    pos.play(move);
}

#endif