#pragma once

#include "PKB_Map_Base.h"

#include <unordered_set>

class PKB_Map_String_SetString :
    public PKB_Map_Base<std::string, std::unordered_set<std::string>>
{
protected:
    PKB_Map_String_SetString();

    void insertThing(std::string name, std::unordered_set<std::string> thingedNames, std::unordered_map<std::string, std::unordered_set<std::string>>& table);
    std::unordered_set<std::string> getThing(std::string name, std::unordered_map<std::string, std::unordered_set<std::string>> table);
    bool isThing(std::string name, std::string thingedName, std::unordered_map<std::string, std::unordered_set<std::string>> table);
    bool isThing(std::string name, std::unordered_set<std::string> thingedNames, std::unordered_map<std::string, std::unordered_set<std::string>> table);
};