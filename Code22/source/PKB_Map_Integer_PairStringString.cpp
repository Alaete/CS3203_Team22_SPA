#include "PKB_Map_Integer_PairStringString.h"

PKB_Map_Integer_PairStringString::PKB_Map_Integer_PairStringString() {}

void PKB_Map_Integer_PairStringString::insertThing(int lineNumber, std::pair<std::string, std::string> entityLines, std::unordered_map<int, std::pair<std::string, std::string>>& table) {
    if (table.count(lineNumber) == 0) {
        table[lineNumber] = entityLines;
    }
}

void PKB_Map_Integer_PairStringString::updateThingSecond(int lineNumber, std::string secondString, std::unordered_map<int, std::pair<std::string, std::string>>& table) {
    if (table.count(lineNumber) != 0) {
        std::pair<std::string, std::string> value = PKB_Map_Integer_PairStringString::getThing(lineNumber, table);
        value.second = secondString;
        table[lineNumber] = value;
    }
}

std::pair<std::string, std::string> PKB_Map_Integer_PairStringString::getThing(int lineNumber, std::unordered_map<int, std::pair<std::string, std::string>> table) {
    std::unordered_map<int, std::pair<std::string, std::string>>::const_iterator thing_iterator = table.find(lineNumber);
    if (thing_iterator != table.end()) {
        return thing_iterator->second;
    }
    else {
        return { "","" };
    }
}