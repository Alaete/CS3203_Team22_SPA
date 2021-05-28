#include "PKB_Map_String_SetString.h"

PKB_Map_String_SetString::PKB_Map_String_SetString() {}

void PKB_Map_String_SetString::insertThing(std::string name, std::unordered_set<std::string> thingedNames, std::unordered_map<std::string, std::unordered_set<std::string>>& table) {
    if (table.count(name) == 0) {
        table[name] = thingedNames;
    }
    else {
        auto pos = table[name].begin();
        for (auto it = thingedNames.begin(); it != thingedNames.end(); ++it) {
            pos = table[name].insert(pos, *it);
        }
    }
}

std::unordered_set<std::string> PKB_Map_String_SetString::getThing(std::string name, std::unordered_map<std::string, std::unordered_set<std::string>> table) {
    std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator thing_iterator = table.find(name);
    if (thing_iterator != table.end()) {
        return thing_iterator->second;
    }
    else {
        return {};
    }
}

bool PKB_Map_String_SetString::isThing(std::string name, std::string thingedName, std::unordered_map<std::string, std::unordered_set<std::string>> table) {
    return table[name].count(thingedName);
}

bool PKB_Map_String_SetString::isThing(std::string name, std::unordered_set<std::string> thingedNames, std::unordered_map<std::string, std::unordered_set<std::string>> table) {
    for (std::string thingedName : thingedNames) {
        if (!table[name].count(thingedName)) {
            return false;
        }
    }
    return true;
}