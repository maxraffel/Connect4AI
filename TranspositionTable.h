#include <iostream>
#include <cstring>
#include <cstdint>
#include <vector>

using namespace std;

class TranspositionTable {
    public:
        TranspositionTable(int size);
        int_fast8_t get(uint64_t key) const;
        void set(uint64_t key, int_fast8_t value);
    private:
        struct TableEntry {
            uint64_t key : 56;
            int_fast8_t value;
        };

        vector<TableEntry> contents;
};
