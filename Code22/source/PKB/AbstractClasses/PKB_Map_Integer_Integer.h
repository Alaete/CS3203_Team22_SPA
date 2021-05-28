#pragma once

#include "PKB_Map_Base.h"

class PKB_Map_Integer_Integer :
    public PKB_Map_Base<int, int> {
protected:
    PKB_Map_Integer_Integer() {}

    void insertThing(int lineNumber, int entityLine, std::unordered_map<int, int>& table) {
        if (table.count(lineNumber) == 0) {
            table[lineNumber] = entityLine;
        }
    }

    int getThing(int lineNumber, std::unordered_map<int, int> table) {
        std::unordered_map<int, int>::const_iterator thing_iterator = table.find(lineNumber);
        if (thing_iterator != table.end()) {
            return thing_iterator->second;
        }
        else {
            return -1;
        }
    }

    bool isThing(int lineNumber, int entityLine, std::unordered_map<int, int> table) {
        if (table.find(lineNumber) != table.end()) {
            return table[lineNumber] == entityLine;
        }
        else {
            return false;
        }
    }
};

