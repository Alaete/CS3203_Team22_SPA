#include "PKB_Map_CallPrintReadStatement.h"

PKB_Map_CallPrintReadStatement::PKB_Map_CallPrintReadStatement() {}

void PKB_Map_CallPrintReadStatement::insertThing(int lineNumber, std::string name) {
    PKB_Map_Integer_String::insertThing(lineNumber, name, table);
    PKB_Map_String_SetInteger::insertThing(name, { lineNumber }, reverseTable);
}

std::string PKB_Map_CallPrintReadStatement::getThing(int lineNumber) {
    return PKB_Map_Integer_String::getThing(lineNumber, table);
}

bool PKB_Map_CallPrintReadStatement::isThing(int lineNumber, std::string name) {
    return PKB_Map_Integer_String::isThing(lineNumber, name, table);
}

std::unordered_set<int> PKB_Map_CallPrintReadStatement::getKeys(std::string name) {
    if (reverseTable.count(name) != 0) {
        return reverseTable.at(name);
    }
    else {
        return {};
    }
}

int PKB_Map_CallPrintReadStatement::getSize() {
    return PKB_Map_Integer_String::getSize(table);
}

bool PKB_Map_CallPrintReadStatement::hasKey(int lineNumber) {
    return PKB_Map_Integer_String::hasKey(lineNumber, table);
}

std::vector<int> PKB_Map_CallPrintReadStatement::getAllKeys() {
    return PKB_Map_Integer_String::getAllKeys(table);
}

std::vector<std::string> PKB_Map_CallPrintReadStatement::getAllValues() {
    return PKB_Map_Integer_String::getAllValues(table);
}

void PKB_Map_CallPrintReadStatement::clear() {
    PKB_Map_Integer_String::clear(table);
    PKB_Map_String_SetInteger::clear(reverseTable);
}

