#pragma once

#include "PKB_Map_Base.h"
#include <unordered_set>

#include <string>

class PKB_Map_Integer_String :
    public PKB_Map_Base<int, std::string>
{
protected:
    PKB_Map_Integer_String();

    void insertThing(int key, std::string value, std::unordered_map<int, std::string>& table);
    void updateThing(int key, std::string value, std::unordered_map<int, std::string>& table);
    std::string getThing(int key, std::unordered_map<int, std::string> table);
    bool isTableType(int key, std::string value, std::unordered_map<int, std::string>& table);
    std::unordered_set<int> getTableKeys(std::string value, std::unordered_map<int, std::string>& table);
};
