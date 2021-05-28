#pragma once

#include "PKB_Map_Integer_String.h"
#include <unordered_set>

class PKB_Map_Read :
    public PKB_Map_Integer_String
{
protected:
    std::unordered_map<int, std::string> readTable;
public:
    PKB_Map_Read();

    void insertRead(int lineNumber, std::string varName);
    std::string getRead(int lineNumber);
    std::unordered_set<int> getReadKeys(std::string varName);

    int getSizeRead();
    bool hasKeyRead(int lineNumber);
    std::vector<int> getAllKeysRead();
    std::vector<std::string> getAllValuesRead();

    void clearAll();
};