#include <cstdint>
#include <iostream>
#include <bitset>

using namespace std;

#ifndef POSITION_H
#define POSITION_H
class Position {
    public:
        void printPosition();
        bool canPlay(int x);
        void play(int x);
        bool hasWon(uint64_t playerMask);
        bool hasWon();
        bool isWinningMove(int x);
        bool isDraw();
        static const int mwidth = 6;  // width of the board have to manually adjust here
        static const int mheight = 6;
        int turns() const;
        uint64_t getKey();
        static void printBitmap(uint64_t bitmapInt);
    private:
        uint64_t mask = 0;
        uint64_t currentPlayerMask = 0; // current player is the player moving next
        int turnsPassed = 0;
        
};

#endif // POSITION_H