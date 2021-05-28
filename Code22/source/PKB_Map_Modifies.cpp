#include "PKB_Map_Modifies.h"

PKB_Map_Modifies::PKB_Map_Modifies() {}

void PKB_Map_Modifies::insertModifies(int lineNumber, std::unordered_set<std::string> modifiedName) {
    PKB_Map_Integer_SetString::insertThing(lineNumber, modifiedName, modifiesTable);

    for (std::string element : modifiedName) {
        PKB_Map_Modifies::insertModifiedBy(element, { lineNumber });
    }
}
std::unordered_set<std::string> PKB_Map_Modifies::getModifies(int lineNumber) {
    return PKB_Map_Integer_SetString::getThing(lineNumber, modifiesTable);
}
bool PKB_Map_Modifies::isModifies(int lineNumber, std::string usedName) {
    return PKB_Map_Integer_SetString::isThing(lineNumber, usedName, modifiesTable);
}
bool PKB_Map_Modifies::isModifies(int lineNumber, std::unordered_set<std::string> modifiedName) {
    return PKB_Map_Integer_SetString::isThing(lineNumber, modifiedName, modifiesTable);
}

void PKB_Map_Modifies::insertModifiedBy(std::string name, std::unordered_set<int> modifiedByLines) {
    PKB_Map_String_SetInteger::insertThing(name, modifiedByLines, modifiedByTable);
}
std::unordered_set<int> PKB_Map_Modifies::getModifiedBy(std::string name) {
    return PKB_Map_String_SetInteger::getThing(name, modifiedByTable);
}
bool PKB_Map_Modifies::isModifiedBy(std::string name, int modifiedByLine) {
    return PKB_Map_String_SetInteger::isThing(name, modifiedByLine, modifiedByTable);
}
bool PKB_Map_Modifies::isModifiedBy(std::string name, std::unordered_set<int> modifiedByLines) {
    return PKB_Map_String_SetInteger::isThing(name, modifiedByLines, modifiedByTable);
}

int PKB_Map_Modifies::getSizeModifies() {
    return PKB_Map_Integer_SetString::getSize(modifiesTable);
}
bool PKB_Map_Modifies::hasKeyModifies(int lineNumber) {
    return PKB_Map_Integer_SetString::hasKey(lineNumber, modifiesTable);
}
std::vector<int> PKB_Map_Modifies::getAllKeysModifies() {
    return PKB_Map_Integer_SetString::getAllKeys(modifiesTable);
}
std::vector<std::unordered_set<std::string>> PKB_Map_Modifies::getAllValuesModifies() {
    return PKB_Map_Integer_SetString::getAllValues(modifiesTable);
}

int PKB_Map_Modifies::getSizeModifiedBy() {
    return PKB_Map_String_SetInteger::getSize(modifiedByTable);
}
bool PKB_Map_Modifies::hasKeyModifiedBy(std::string name) {
    return PKB_Map_String_SetInteger::hasKey(name, modifiedByTable);
}
std::vector<std::string> PKB_Map_Modifies::getAllKeysModifiedBy() {
    return PKB_Map_String_SetInteger::getAllKeys(modifiedByTable);
}
std::vector<std::unordered_set<int>> PKB_Map_Modifies::getAllValuesModifiedBy() {
    return PKB_Map_String_SetInteger::getAllValues(modifiedByTable);
}

void PKB_Map_Modifies::clearAll() {
    PKB_Map_Integer_SetString::clear(modifiesTable);
    PKB_Map_String_SetInteger::clear(modifiedByTable);
}