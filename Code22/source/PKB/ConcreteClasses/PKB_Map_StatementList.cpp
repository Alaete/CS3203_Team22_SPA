#include "PKB_Map_StatementList.h"

PKB_Map_StatementList::PKB_Map_StatementList() {}

void PKB_Map_StatementList::insertStatementList(int index, std::unordered_set<int> statementLines) {
    PKB_Map_Integer_SetInteger::insertThing(index, statementLines, statementListTable);
    for (auto statementLine : statementLines) {
        statementListReverseTable.insert({ statementLine, index });
    }
}
std::unordered_set<int> PKB_Map_StatementList::getStatementList(int index) {
    return PKB_Map_Integer_SetInteger::getThing(index, statementListTable);
}
int PKB_Map_StatementList::getKeyStatementList(int statementLine) {
    auto item = statementListReverseTable.find(statementLine);
    if (item != statementListReverseTable.end()) {
        return item->second;
    }
    else {
        return -1;
    }
}

int PKB_Map_StatementList::getSizeStatementList() {
    return PKB_Map_Integer_SetInteger::getSize(statementListTable);
}
bool PKB_Map_StatementList::hasKeyStatementList(int index) {
    return PKB_Map_Integer_SetInteger::hasKey(index, statementListTable);
}
std::vector<int> PKB_Map_StatementList::getAllKeysStatementList() {
    return PKB_Map_Integer_SetInteger::getAllKeys(statementListTable);
}
std::vector<std::unordered_set<int>> PKB_Map_StatementList::getAllValuesStatementList() {
    return PKB_Map_Integer_SetInteger::getAllValues(statementListTable);
}

void PKB_Map_StatementList::clear() {
    statementListReverseTable.clear();
    PKB_Map_Integer_SetInteger::clear(statementListTable);
}

