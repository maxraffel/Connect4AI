#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>

using namespace std;

class TranspositionTable {
    public:
        TranspositionTable(int size);
        int_fast8_t get(uint64_t key) const;
        void set(uint64_t key, unsigned int value);
    private:
        struct TableEntry {
            uint64_t key : 48;
            unsigned int value:3; //unset 0, 1 for -1, 2 for 0, and 3 for 1
        };

        vector<TableEntry> contents;
};
