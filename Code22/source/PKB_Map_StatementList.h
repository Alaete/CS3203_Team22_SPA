#pragma once

#include "PKB_Map_Integer_SetInteger.h"

class PKB_Map_StatementList :
    public PKB_Map_Integer_SetInteger
{
protected:
    std::unordered_map<int, std::unordered_set<int>> statementListTable;
public:
    PKB_Map_StatementList();

    void insertStatementList(int lineNumber, std::unordered_set<int> statementLines);
    std::unordered_set<int> getStatementList(int lineNumber);

    int getSizeStatementList();
    bool hasKeyStatementList(int lineNumber);
    std::vector<int> getAllKeysStatementList();
    std::vector<std::unordered_set<int>> getAllValuesStatementList();

    void clearAll();
};