#include "PKB_Map_If.h"

PKB_Map_If::PKB_Map_If() {}

void PKB_Map_If::insertIf(int lineNumber, std::string condition) {
    if (!PKB_Map_If::hasKeyIf(lineNumber)) {
        PKB_Map_Integer_String::insertThing(lineNumber, condition, ifTable);
    }
    else {
        PKB_Map_Integer_String::updateThing(lineNumber, condition, ifTable);
    }
}

std::string PKB_Map_If::getIf(int lineNumber) {
    return PKB_Map_Integer_String::getThing(lineNumber, ifTable);
}

std::unordered_set<int> PKB_Map_If::getIfKeys(std::string condition) {
    return PKB_Map_Integer_String::getTableKeys(condition, ifTable);
}

int PKB_Map_If::getSizeIf() {
    return getSize(ifTable);
}

bool PKB_Map_If::hasKeyIf(int lineNumber) {
    return hasKey(lineNumber, ifTable);
}

std::vector<int> PKB_Map_If::getAllKeysIf() {
    return getAllKeys(ifTable);
}

std::vector<std::string> PKB_Map_If::getAllValuesIf() {
    return getAllValues(ifTable);
}

void PKB_Map_If::clearAll() {
    PKB_Map_Integer_String::clear(ifTable);
}