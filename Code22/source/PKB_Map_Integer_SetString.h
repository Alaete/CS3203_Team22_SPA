#pragma once

#include "PKB_Map_Base.h"

#include <unordered_set>

class PKB_Map_Integer_SetString :
    public PKB_Map_Base<int, std::unordered_set<std::string>>
{
protected:
    PKB_Map_Integer_SetString();

    void insertThing(int lineNumber, std::unordered_set<std::string> entites, std::unordered_map<int, std::unordered_set<std::string>>& table);
    std::unordered_set<std::string> getThing(int lineNumber, std::unordered_map<int, std::unordered_set<std::string>> table);
    bool PKB_Map_Integer_SetString::isThing(int lineNumber, std::string name, std::unordered_map<int, std::unordered_set<std::string>> table);
    bool PKB_Map_Integer_SetString::isThing(int lineNumber, std::unordered_set<std::string> names, std::unordered_map<int, std::unordered_set<std::string>> table);
};