#include "PKB_Map_While.h"

PKB_Map_While::PKB_Map_While() {}

void PKB_Map_While::insertWhile(int lineNumber, std::string condition) {
    if (!PKB_Map_While::hasKeyWhile(lineNumber)) {
        PKB_Map_Integer_String::insertThing(lineNumber, condition, whileTable);
    }
    else {
        PKB_Map_Integer_String::updateThing(lineNumber, condition, whileTable);
    }
}

std::string PKB_Map_While::getWhile(int lineNumber) {
    return PKB_Map_Integer_String::getThing(lineNumber, whileTable);
}

std::unordered_set<int> PKB_Map_While::getWhileKeys(std::string condition) {
    return PKB_Map_Integer_String::getTableKeys(condition, whileTable);
}

int PKB_Map_While::getSizeWhile() {
    return getSize(whileTable);
}

bool PKB_Map_While::hasKeyWhile(int lineNumber) {
    return hasKey(lineNumber, whileTable);
}

std::vector<int> PKB_Map_While::getAllKeysWhile() {
    return getAllKeys(whileTable);
}

std::vector<std::string> PKB_Map_While::getAllValuesWhile() {
    return getAllValues(whileTable);
}

void PKB_Map_While::clearAll() {
    PKB_Map_Integer_String::clear(whileTable);
}