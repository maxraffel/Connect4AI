#include <iostream>
#include "Position.h"
#include <bitset>
#include <cstdint>
using namespace std;

#ifndef POSITION_H
#define POSITION_H

// bitboard where each column counts up consecutively, ie column 0 starts at 0, then col 1 at height + 1, etc
// starting from (0,0) in bottom left corner, each coordinate (w, h) corresponds to an int (mheight+1)*w + h

void Position::printPosition() { //figure out static
    // can redo with shift but speed of this function is pretty inconsequential
    bitset<64> maskBitset = bitset<64>(mask);
    bitset<64> currentPlayerBitset = bitset<64>(currentPlayerMask);
    //cout << maskBitset << endl;
    for (int h = mheight - 1; h >= 0; h--) {
        for (int w = 0; w < mwidth; w++) {
            if (currentPlayerBitset[(mheight+1)*w + h]) {
                if (turnsPassed % 2 == 0) {
                    cout << "🔴";
                } else {
                    cout << "🟡";
                }
            } else if (maskBitset[(mheight+1)*w + h]) { // first player to move is red
                if (turnsPassed % 2 == 0) {
                    cout << "🟡";
                } else {
                    cout << "🔴";
                }
            } else {
                cout << "⚫";
            }
        }
        cout << endl;
    }
    cout << endl;
}
void Position::printBitmap(uint64_t bitmapInt) { //figure out static
    // can redo with shift but speed of this function is pretty inconsequential
    bitset<64>bitmap = bitset<64>(bitmapInt);
    //cout << maskBitset << endl;

    for (int h = mheight - 1; h >= 0; h--) {
        for (int w = 0; w < mwidth; w++) {
            cout << bitmap[(mheight+1)*w + h] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

constexpr static uint64_t bottom(int width, int height) {
    return width == 0 ? 0 : bottom(width-1, height) | 1LL << (width-1)*(height+1);
}


bool Position::canPlay(int x) {
    return !(mask & (1ULL << (mheight-1 + (mheight+1)*x)));
}

void Position::play(int x) {
    currentPlayerMask ^= mask; //swap which player is in current player mask (so now mask represents old player)
    //cout << "mheight: " << mheight << " mheight + 1: " << mheight + 1 << " x: " << x << " " << (mheight + 1)*x << endl;
    mask |= mask + (1ULL << ((mheight + 1)*x));
    turnsPassed++;
}

bool Position::hasWon(uint64_t playerMask) {
    //checks each by isolating when you can shift over twice (ie two horizontals or two diagonals), match, then shift once and match
    //(should eliminate everything but 4+ matches)

    // check horizontal
    uint64_t temp = (playerMask << (mheight+1)*2) & playerMask;
    if (temp & (temp << (mheight+1))) {
        return true;
    }
    // check vertical
    temp = (playerMask << 2) & playerMask;
    if (temp & (temp << 1)) {
        return true;
    }
    //check ++ diagonal (shift by mheight+1 + 1 for one diagonal)
    temp = (playerMask << (mheight+2)*2) & playerMask;
    if (temp & (temp << (mheight+2))) {
        return true;
    }

    //check +- diagonal (shift by mheight + 1 - 1)
    temp = (playerMask << (mheight*2)) & playerMask;
    if (temp & (temp << mheight)) {
        return true;
    }

    return false;
}

bool Position::hasWon() {
    //cout << "hasWon: " << mask << ", " << currentPlayerMask << endl;
    //cout << "hasWon mask: " << (currentPlayerMask^mask) << endl;
    return hasWon(currentPlayerMask^mask);
}

bool Position::isWinningMove(int x) {
    uint64_t tempPlayerMask = mask^currentPlayerMask;
    uint64_t tempMask = mask;
    tempMask |= tempMask + (1ULL << ((mheight + 1)*x));
    //cout << "isWinningMove: " << tempMask << ", " << tempPlayerMask << endl;
    //cout << "isWinningMove mask: " << (tempMask ^ tempPlayerMask) << endl;
    return hasWon(tempMask ^ tempPlayerMask);
}

int Position::turns() const {
    return turnsPassed;
}

uint64_t Position::getKey() {
    return mask + currentPlayerMask;
}

#endif