#pragma once

#include "PKB_Map_Integer_String.h"
#include <unordered_set>

class PKB_Map_Call :
    public PKB_Map_Integer_String
{
protected:
    std::unordered_map<int, std::string> callTable;
public:
    PKB_Map_Call();

    void insertCall(int lineNumber, std::string procName);
    std::string getCall(int lineNumber);
    std::unordered_set<int> getCallKeys(std::string procName);

    int getSizeCall();
    bool hasKeyCall(int lineNumber);
    std::vector<int> getAllKeysCall();
    std::vector<std::string> getAllValuesCall();

    void clearAll();
};

