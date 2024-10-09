#include <iostream>
#include <cstring>
#include <cstdint>
#include "TranspositionTable.h"
#include <vector>

using namespace std;

#ifndef TRANSPOSITIONTABLE_H
#define TRANSPOSITIONTABLE_H

TranspositionTable::TranspositionTable(int size) {
    contents.resize(size);
    memset(&contents[0], 0, contents.size()*sizeof(TableEntry));
}

int_fast8_t TranspositionTable::get(uint64_t key) const {
    TableEntry entry = contents[key % contents.size()];
    if (entry.key == key) return entry.value - 2;
    return 0;
}

void TranspositionTable::set(uint64_t key, unsigned int value) {
    TableEntry entry;
    entry.value = value + 2;
    entry.key = key;
    contents[key % contents.size()] = entry;
}

#endif