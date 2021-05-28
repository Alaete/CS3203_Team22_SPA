#include "PKB_Map_Statement.h"

PKB_Map_Statement::PKB_Map_Statement() {}

void PKB_Map_Statement::insertStatement(int lineNumber, std::string statementType) {
    PKB_Map_Integer_String::insertThing(lineNumber, statementType, statementTable);
}

std::string PKB_Map_Statement::getStatement(int lineNumber) {
    return PKB_Map_Integer_String::getThing(lineNumber, statementTable);
}

bool PKB_Map_Statement::isStatementType(int lineNumber, std::string statementType) {
    return PKB_Map_Integer_String::isTableType(lineNumber, statementType, statementTable);
}

std::unordered_set<int> PKB_Map_Statement::getStatementKeys(std::string statementType) {
    return PKB_Map_Integer_String::getTableKeys(statementType, statementTable);
}

int PKB_Map_Statement::getSizeStatement() {
    return getSize(statementTable);
}

bool PKB_Map_Statement::hasKeyStatement(int lineNumber) {
    return hasKey(lineNumber, statementTable);
}

std::vector<int> PKB_Map_Statement::getAllKeysStatement() {
    return getAllKeys(statementTable);
}

std::vector<std::string> PKB_Map_Statement::getAllValuesStatement() {
    return getAllValues(statementTable);
}

void PKB_Map_Statement::clearAll() {
    PKB_Map_Integer_String::clear(statementTable);
}