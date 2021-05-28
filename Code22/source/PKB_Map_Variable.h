#pragma once

#include "PKB_Map_Integer_String.h"

class PKB_Map_Variable :
    public PKB_Map_Integer_String 
{
protected:
    std::unordered_map<int, std::string> variableTable;
public:
    PKB_Map_Variable();

    int insertVariable(std::string varName);
    std::string getVariable(int index);
    int getVariableKey(std::string varName);

    int getSizeVariable();
    bool hasKeyVariable(int index);
    std::vector<int> getAllKeysVariable();
    std::vector<std::string> getAllValuesVariable();

    void clearAll();
};
