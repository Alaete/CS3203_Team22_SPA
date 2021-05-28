#pragma once

#include "../AbstractClasses/PKB_Map_Integer_SetInteger.h"

class PKB_Map_StatementList :
    public PKB_Map_Integer_SetInteger {
private:
    std::unordered_map<int, int> statementListReverseTable;
    std::unordered_map<int, std::unordered_set<int>> statementListTable;
public:
    PKB_Map_StatementList();

    void insertStatementList(int index, std::unordered_set<int> statementLines);
    std::unordered_set<int> getStatementList(int index);
    int getKeyStatementList(int statementLine);

    int getSizeStatementList();
    bool hasKeyStatementList(int index);
    std::vector<int> getAllKeysStatementList();
    std::vector<std::unordered_set<int>> getAllValuesStatementList();

    void clear();
};

