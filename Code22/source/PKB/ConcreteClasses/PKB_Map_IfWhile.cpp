#include "PKB_Map_IfWhile.h"

PKB_Map_IfWhile::PKB_Map_IfWhile() {}

void PKB_Map_IfWhile::insertThing(int lineNumber, std::unordered_set<std::string> conditions) {
    PKB_Map_Integer_SetString::insertThing(lineNumber, conditions, table);
}

std::unordered_set<std::string> PKB_Map_IfWhile::getThing(int lineNumber) {
    return PKB_Map_Integer_SetString::getThing(lineNumber, table);
}

bool PKB_Map_IfWhile::isThing(int lineNumber, std::string condition) {
    return PKB_Map_Integer_SetString::isThing(lineNumber, condition, table);
}
bool PKB_Map_IfWhile::isThing(int lineNumber, std::unordered_set<std::string> conditions) {
    return PKB_Map_Integer_SetString::isThing(lineNumber, conditions, table);
}

int PKB_Map_IfWhile::getSize() {
    return PKB_Map_Integer_SetString::getSize(table);
}

int PKB_Map_IfWhile::getArea() {
    return PKB_Map_Integer_SetString::getArea(table);
}

bool PKB_Map_IfWhile::hasKey(int lineNumber) {
    return PKB_Map_Integer_SetString::hasKey(lineNumber, table);
}

std::vector<int> PKB_Map_IfWhile::getAllKeys() {
    return PKB_Map_Integer_SetString::getAllKeys(table);
}

std::vector<std::unordered_set<std::string>> PKB_Map_IfWhile::getAllValues() {
    return PKB_Map_Integer_SetString::getAllValues(table);
}

void PKB_Map_IfWhile::clear() {
    PKB_Map_Integer_SetString::clear(table);
}

