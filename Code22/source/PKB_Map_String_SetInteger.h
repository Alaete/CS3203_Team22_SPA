#pragma once

#include "PKB_Map_Base.h"

#include <unordered_set>

class PKB_Map_String_SetInteger :
    public PKB_Map_Base<std::string, std::unordered_set<int>>
{
protected:
    PKB_Map_String_SetInteger();

    void insertThing(std::string name, std::unordered_set<int> thingedLines, std::unordered_map<std::string, std::unordered_set<int>>& table);
    std::unordered_set<int> getThing(std::string name, std::unordered_map<std::string, std::unordered_set<int>> table);
    bool isThing(std::string name, int thingedLine, std::unordered_map<std::string, std::unordered_set<int>> table);
    bool isThing(std::string name, std::unordered_set<int> thingedLine, std::unordered_map<std::string, std::unordered_set<int>> table);
};

