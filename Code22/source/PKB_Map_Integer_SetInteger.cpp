#include "PKB_Map_Integer_SetInteger.h"

PKB_Map_Integer_SetInteger::PKB_Map_Integer_SetInteger() {}

void PKB_Map_Integer_SetInteger::insertThing(int lineNumber, std::unordered_set<int> entityLines, std::unordered_map<int, std::unordered_set<int>>& table) {
    if (table.count(lineNumber) == 0) {
        table[lineNumber] = entityLines;
    }
    else {
        auto pos = table[lineNumber].begin();
        for (auto it = entityLines.begin(); it != entityLines.end(); ++it) {
            pos = table[lineNumber].insert(pos, *it);
        }
    }
}

std::unordered_set<int> PKB_Map_Integer_SetInteger::getThing(int lineNumber, std::unordered_map<int, std::unordered_set<int>> table) {
    std::unordered_map<int, std::unordered_set<int>>::const_iterator thing_iterator = table.find(lineNumber);
    if (thing_iterator != table.end()) {
        return thing_iterator->second;
    }
    else {
        return {};
    }
}

bool PKB_Map_Integer_SetInteger::isThing(int lineNumber, int entityLine, std::unordered_map<int, std::unordered_set<int>> table) {
    return table[lineNumber].count(entityLine);
}

bool PKB_Map_Integer_SetInteger::isThing(int lineNumber, std::unordered_set<int> entityLines, std::unordered_map<int, std::unordered_set<int>> table) {
    for (int entityLine : entityLines) {
        if (!table[lineNumber].count(entityLine)) {
            return false;
        }
    }
    return true;
}
