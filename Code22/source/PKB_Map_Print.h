#pragma once

#include "PKB_Map_Integer_String.h"
#include <unordered_set>

class PKB_Map_Print :
    public PKB_Map_Integer_String
{
protected:
    std::unordered_map<int, std::string> printTable;
public:
    PKB_Map_Print();

    void insertPrint(int lineNumber, std::string varName);
    std::string getPrint(int lineNumber);
    std::unordered_set<int> getPrintKeys(std::string varName);

    int getSizePrint();
    bool hasKeyPrint(int lineNumber);
    std::vector<int> getAllKeysPrint();
    std::vector<std::string> getAllValuesPrint();

    void clearAll();
};
