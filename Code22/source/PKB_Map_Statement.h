#pragma once

#include "PKB_Map_Integer_String.h"
#include <unordered_set>

class PKB_Map_Statement:
    public PKB_Map_Integer_String
{
protected:
    std::unordered_map<int, std::string> statementTable;
public:
    PKB_Map_Statement();

    void insertStatement(int lineNumber, std::string statementType);
    std::string getStatement(int lineNumber);
    bool isStatementType(int lineNumber, std::string statementType);
    std::unordered_set<int> getStatementKeys(std::string statementType);

    int getSizeStatement();
    bool hasKeyStatement(int lineNumber);
    std::vector<int> getAllKeysStatement();
    std::vector<std::string> getAllValuesStatement();

    void clearAll();
};
