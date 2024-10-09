#include <iostream>
#include "Position.h"
#include "Solver.h"
#include <chrono>
using namespace std;

int main() {

    Position pos1;
    Solver bot;

    cout << "Nollan, your dastardly ways have gone on for too long. This grid shall be your last. Prepare yourself to face \"Nollan\'s Folly\"" << endl;
    pos1.printPosition();

    int input;
    
    while (input != 'q') {
        cin >> input;
        if (input > Position::mwidth || input <= 0) {
            cout << "Invalid input" << endl;
            continue;
        }
        pos1.play(input - 1);
        pos1.printPosition();
        if (pos1.hasWon()) {
            cout << "IM GONNA CRASH OUT" << endl;
            break;
        }
        auto start = chrono::high_resolution_clock::now();
        bot.negamaxStart(pos1);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "I have studied " << bot.nodesVisited << " realities in a mere " << duration.count() / 1000000.0 << " seconds." << endl;
        pos1.printPosition();
        if (pos1.hasWon()) {
            cout << "Judgement has passed. All is right in the world. Thank you for your participation but your time here on Earth has come to pass. Goodbye." << endl;
            break;
        }
    }

    return 0;
}