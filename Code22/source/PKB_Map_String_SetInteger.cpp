#include "PKB_Map_String_SetInteger.h"

PKB_Map_String_SetInteger::PKB_Map_String_SetInteger() {}

void PKB_Map_String_SetInteger::insertThing(std::string name, std::unordered_set<int> thingsLines, std::unordered_map<std::string, std::unordered_set<int>>& table) {
    if (table.count(name) == 0) {
        table[name] = thingsLines;
    }
    else {
        auto pos = table[name].begin();
        for (auto it = thingsLines.begin(); it != thingsLines.end(); ++it) {
            pos = table[name].insert(pos, *it);
        }
    }
}

std::unordered_set<int> PKB_Map_String_SetInteger::getThing(std::string name, std::unordered_map<std::string, std::unordered_set<int>> table) {
    std::unordered_map<std::string, std::unordered_set<int>>::const_iterator thing_iterator = table.find(name);
    if (thing_iterator != table.end()) {
        return thing_iterator->second;
    }
    else {
        return {};
    }
}

bool PKB_Map_String_SetInteger::isThing(std::string name, int thingsLine, std::unordered_map<std::string, std::unordered_set<int>> table) {
    return table[name].count(thingsLine);
}

bool PKB_Map_String_SetInteger::isThing(std::string name, std::unordered_set<int> thingsLines, std::unordered_map<std::string, std::unordered_set<int>> table) {
    for (int thingsLine : thingsLines) {
        if (!table[name].count(thingsLine)) {
            return false;
        }
    }
    return true;
}