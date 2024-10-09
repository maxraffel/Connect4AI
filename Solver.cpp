#include <iostream>
#include "Position.h"
#include "Solver.h"
#include <cstring>
#include <cstdint>

using namespace std;

#ifndef SOLVER_H
#define SOLVER_H

int Solver::negamax(Position &pos, int alpha, int beta) {
    nodesVisited++;
    // return 0 if draw
    if (pos.turns() == pos.mheight*pos.mwidth) return 0;

    

    // return this turn if it is a winning move (ie win on 3rd turn, would be 2nd play hence +1 for round up)
    for (int i = 0; i < pos.mwidth; i++) {
        if (pos.canPlay(i) && pos.isWinningMove(i)) {
            return (pos.mwidth*pos.mheight - pos.turns() +1)/2; // round down turn
        }
    }

    int maxScore = (pos.mwidth*pos.mheight - pos.turns() - 1)/2; // win on next turn, this time round score down
    if (beta > maxScore) beta = maxScore;
    if (alpha >= beta) {
        return beta;
    }

    // after all the fast ways to get a score are done, see if we stored key in lookup table
    
    uint64_t key = pos.getKey();
    int value = ttable.get(key);
    
    if (value) {
        return value;
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
    ttable.set(key, alpha);
    return alpha;
}

bool trashtalked = false;

void Solver::negamaxStart(Position &pos) {
    nodesVisited = 0;
    for (int i = 0; i < pos.mwidth; i++) {
        if (pos.canPlay(i) && pos.isWinningMove(i)) {
            pos.play(i);
            return;
        }
    }

    int move;
    //int max = (pos.mwidth*pos.mheight - pos.turns() + 1)/2;
    int min = -(pos.mwidth*pos.mheight - pos.turns())/2;
    
    for (int i = 0; i < pos.mwidth; i++) {
        Position pos2(pos);
        if (pos.canPlay(i)) {
            pos2.play(i);
            int score = -negamax(pos2, -1, 1);
            if (trashtalked == false && score > 0) {
                cout << "An obvious blunder. This game is a forgone conclusion. The end is nigh, Nollan." << endl;
                trashtalked = true;
            }
            if (score > min) {
                min = score;
                move = i;
            }
        }
    }
    cout << endl;
    pos.play(move);
}

#endif