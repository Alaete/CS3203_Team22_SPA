#pragma once

#include "PKB_Map_Integer_String.h"
#include <unordered_set>

class PKB_Map_If :
    public PKB_Map_Integer_String
{
protected:
    std::unordered_map<int, std::string> ifTable;
public:
    PKB_Map_If();

    void insertIf(int lineNumber, std::string condition);
    std::string getIf(int lineNumber);
    std::unordered_set<int> getIfKeys(std::string condition);

    int getSizeIf();
    bool hasKeyIf(int lineNumber);
    std::vector<int> getAllKeysIf();
    std::vector<std::string> getAllValuesIf();

    void clearAll();
};

