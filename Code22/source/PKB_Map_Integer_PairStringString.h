#pragma once

#include "PKB_Map_Base.h"

#include <string>

class PKB_Map_Integer_PairStringString :
    public PKB_Map_Base<int, std::pair<std::string, std::string>>
{
protected:
    PKB_Map_Integer_PairStringString();

    void insertThing(int lineNumber, std::pair<std::string, std::string> assignShunted, std::unordered_map<int, std::pair<std::string, std::string>>& table);
    void updateThingSecond(int lineNumber, std::string secondString, std::unordered_map<int, std::pair<std::string, std::string>>& table);
    std::pair<std::string, std::string> getThing(int lineNumber, std::unordered_map<int, std::pair<std::string, std::string>> table);
};