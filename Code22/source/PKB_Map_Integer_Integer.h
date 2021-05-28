#pragma once

#include "PKB_Map_Base.h"

class PKB_Map_Integer_Integer :
    public PKB_Map_Base<int, int>
{
protected:
    PKB_Map_Integer_Integer();

    void insertThing(int lineNumber, int entityLine, std::unordered_map<int, int>& table);
    int getThing(int lineNumber, std::unordered_map<int, int> table);
    bool isThing(int lineNumber, int entityLine, std::unordered_map<int, int> table);
};