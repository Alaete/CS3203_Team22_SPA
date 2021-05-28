#include "PKB_Map_Integer_SetString.h"

PKB_Map_Integer_SetString::PKB_Map_Integer_SetString() {}

void PKB_Map_Integer_SetString::insertThing(int lineNumber, std::unordered_set<std::string> entities, std::unordered_map<int, std::unordered_set<std::string>>& table) {
    if (table.count(lineNumber) == 0) {
        table[lineNumber] = entities;
    }
    else {
        auto pos = table[lineNumber].begin();
        for (auto it = entities.begin(); it != entities.end(); ++it) {
            pos = table[lineNumber].insert(pos, *it);
        }
    }
}

std::unordered_set<std::string> PKB_Map_Integer_SetString::getThing(int lineNumber, std::unordered_map<int, std::unordered_set<std::string>> table) {
    std::unordered_map<int, std::unordered_set<std::string>>::const_iterator thing_iterator = table.find(lineNumber);
    if (thing_iterator != table.end()) {
        return thing_iterator->second;
    }
    else {
        return {};
    }
}

bool PKB_Map_Integer_SetString::isThing(int lineNumber, std::string name, std::unordered_map<int, std::unordered_set<std::string>> table) {
    return table[lineNumber].count(name);
}

bool PKB_Map_Integer_SetString::isThing(int lineNumber, std::unordered_set<std::string> names, std::unordered_map<int, std::unordered_set<std::string>> table) {
    for (std::string entityNames : names) {
        if (!table[lineNumber].count(entityNames)) {
            return false;
        }
    }
    return true;
}
