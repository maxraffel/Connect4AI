#include <iostream>
#include "Position.h"
#include "Weak/WeakSolver.h"
#include <chrono>
using namespace std;

int main() {

    Position pos1;
    WeakSolver bot;

    pos1.printPosition();

    int input;
    
    while (input != 'q') {
        cin >> input;
        if (input > Position::mwidth || input <= 0 || !pos1.canPlay(input - 1)) {
            cout << "Invalid input" << endl;
            continue;
        }
        pos1.play(input - 1);
        pos1.printPosition();
        if (pos1.hasWon()) {
            cout << "Player Victory" << endl;
            break;
        } else if (pos1.isDraw()) {
            cout << "Draw" << endl;
            break;
        }
        auto start = chrono::high_resolution_clock::now();
        bot.negamaxStart(pos1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Visited " << bot.nodesVisited << " nodes in " << duration.count() / 1000000.0 << " seconds." << endl;
        pos1.printPosition();
        if (pos1.hasWon()) {
            cout << "AI Victory" << endl;
            break;
        } else if (pos1.isDraw()) {
            cout << "Draw" << endl;
            break;
        }
    }

    return 0;
}