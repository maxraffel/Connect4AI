#include <iostream>
#include <cstring>
#include <cstdint>
#include "WeakTTable.h"
#include <vector>

using namespace std;

#ifndef WEAKTRANSPOSITIONTABLE_H
#define WEAKTRANSPOSITIONTABLE_H

WeakTTable::WeakTTable(int size) {
    contents.resize(size);
    memset(&contents[0], 0, contents.size()*sizeof(TableEntry));
}

int_fast8_t WeakTTable::get(uint64_t key) const {
    TableEntry entry = contents[key % contents.size()];
    if (entry.key == key) return entry.value - 2;
    return 0;
}

void WeakTTable::set(uint64_t key, unsigned int value) {
    TableEntry entry;
    entry.value = value + 2;
    entry.key = key;
    contents[key % contents.size()] = entry;
}

#endif