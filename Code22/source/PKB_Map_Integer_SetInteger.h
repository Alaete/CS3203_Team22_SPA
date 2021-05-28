#pragma once

#include "PKB_Map_Base.h"

#include <unordered_set>

class PKB_Map_Integer_SetInteger :
    public PKB_Map_Base<int, std::unordered_set<int>> 
{
protected:
    PKB_Map_Integer_SetInteger();

    void insertThing(int lineNumber, std::unordered_set<int> entityLines, std::unordered_map<int, std::unordered_set<int>>& table);
    std::unordered_set<int> getThing(int lineNumber, std::unordered_map<int, std::unordered_set<int>> table);
    bool isThing(int lineNumber, int entityLine, std::unordered_map<int, std::unordered_set<int>> table);
    bool isThing(int lineNumber, std::unordered_set<int> entityLines, std::unordered_map<int, std::unordered_set<int>> table);
};