#include "PKB_Map_StatementList.h"

PKB_Map_StatementList::PKB_Map_StatementList() {}

void PKB_Map_StatementList::insertStatementList(int lineNumber, std::unordered_set<int> statementLines) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, statementLines, statementListTable);
}
std::unordered_set<int> PKB_Map_StatementList::getStatementList(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, statementListTable);
}

int PKB_Map_StatementList::getSizeStatementList() {
    return getSize(statementListTable);
}
bool PKB_Map_StatementList::hasKeyStatementList(int lineNumber) {
    return hasKey(lineNumber, statementListTable);
}
std::vector<int> PKB_Map_StatementList::getAllKeysStatementList() {
    return getAllKeys(statementListTable);
}
std::vector<std::unordered_set<int>> PKB_Map_StatementList::getAllValuesStatementList() {
    return getAllValues(statementListTable);
}

void PKB_Map_StatementList::clearAll() {
    PKB_Map_Integer_SetInteger::clear(statementListTable);
}