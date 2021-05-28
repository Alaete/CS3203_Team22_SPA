#pragma once

#include "PKB_Map_Base.h"

#include <string>

class PKB_Map_Integer_PairStringString :
    public PKB_Map_Base<int, std::pair<std::string, std::string>> {
protected:
    PKB_Map_Integer_PairStringString() {}

    void insertThing(int lineNumber, std::pair<std::string, std::string> entityLines, std::unordered_map<int, std::pair<std::string, std::string>>& table) {
        if (table.count(lineNumber) == 0) {
            table[lineNumber] = entityLines;
        }
    }

    void updateThingSecond(int lineNumber, std::string secondString, std::unordered_map<int, std::pair<std::string, std::string>>& table) {
        if (table.count(lineNumber) != 0) {
            std::pair<std::string, std::string> value = getThing(lineNumber, table);
            value.second = secondString;
            table[lineNumber] = value;
        }
    }

    std::pair<std::string, std::string> getThing(int lineNumber, std::unordered_map<int, std::pair<std::string, std::string>> table) {
        std::unordered_map<int, std::pair<std::string, std::string>>::const_iterator thing_iterator = table.find(lineNumber);
        if (thing_iterator != table.end()) {
            return thing_iterator->second;
        }
        else {
            return { "","" };
        }
    }
};

