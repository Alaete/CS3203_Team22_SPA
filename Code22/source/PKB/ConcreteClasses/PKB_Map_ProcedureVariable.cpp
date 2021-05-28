#include "PKB_Map_ProcedureVariable.h"

PKB_Map_ProcedureVariable::PKB_Map_ProcedureVariable() {}

int PKB_Map_ProcedureVariable::insertThing(std::string name) {
    auto item = reverseTable.find(name);
    if (item != reverseTable.end()) {
        return item->second;
    }

    reverseTable.insert({ name, currentIndex });
    PKB_Map_Integer_String::insertThing(currentIndex, name, table);
    ++currentIndex;
    return currentIndex - 1;
}

std::string PKB_Map_ProcedureVariable::getThing(int index) {
    return PKB_Map_Integer_String::getThing(index, table);
}

int PKB_Map_ProcedureVariable::getKey(std::string name) {
    auto item = reverseTable.find(name);
    if (item != reverseTable.end()) {
        return item->second;
    }
    else {
        return -1;
    }
}

int PKB_Map_ProcedureVariable::getSize() {
    return PKB_Map_Integer_String::getSize(table);
}

bool PKB_Map_ProcedureVariable::hasKey(int index) {
    return PKB_Map_Integer_String::hasKey(index, table);
}

std::vector<int> PKB_Map_ProcedureVariable::getAllKeys() {
    return PKB_Map_Integer_String::getAllKeys(table);
}

std::vector<std::string> PKB_Map_ProcedureVariable::getAllValues() {
    return PKB_Map_Integer_String::getAllValues(table);
}

void PKB_Map_ProcedureVariable::clear() {
    currentIndex = 0;
    PKB_Map_Integer_String::clear(table);
    reverseTable.clear();
}

