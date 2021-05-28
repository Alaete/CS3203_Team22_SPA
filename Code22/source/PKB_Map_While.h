#pragma once

#include "PKB_Map_Integer_String.h"
#include <unordered_set>

class PKB_Map_While :
    public PKB_Map_Integer_String
{
protected:
    std::unordered_map<int, std::string> whileTable;
public:
    PKB_Map_While();

    void insertWhile(int lineNumber, std::string condition);
    std::string getWhile(int lineNumber);
    std::unordered_set<int> getWhileKeys(std::string condition);

    int getSizeWhile();
    bool hasKeyWhile(int lineNumber);
    std::vector<int> getAllKeysWhile();
    std::vector<std::string> getAllValuesWhile();

    void clearAll();
};

