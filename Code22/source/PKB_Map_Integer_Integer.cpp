#include "PKB_Map_Integer_Integer.h"

PKB_Map_Integer_Integer::PKB_Map_Integer_Integer() {}

void PKB_Map_Integer_Integer::insertThing(int lineNumber, int entityLine, std::unordered_map<int, int>& table) {
    if (table.count(lineNumber) == 0) {
        table[lineNumber] = entityLine;
    }
}

int PKB_Map_Integer_Integer::getThing(int lineNumber, std::unordered_map<int, int> table) {
    std::unordered_map<int, int>::const_iterator thing_iterator = table.find(lineNumber);
    if (thing_iterator != table.end()) {
        return thing_iterator->second;
    }
    else {
        return -1;
    }
}

bool PKB_Map_Integer_Integer::isThing(int lineNumber, int entityLine, std::unordered_map<int, int> table) {
    return table[lineNumber] == entityLine;
}

