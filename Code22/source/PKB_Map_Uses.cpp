#include "PKB_Map_Uses.h"

PKB_Map_Uses::PKB_Map_Uses() {}

void PKB_Map_Uses::insertUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    PKB_Map_Integer_SetString::insertThing(lineNumber, usedNames, usesTable);

    for (std::string element : usedNames) {
        PKB_Map_Uses::insertUsedBy(element, { lineNumber });
    }
}
std::unordered_set<std::string> PKB_Map_Uses::getUses(int lineNumber) {
    return PKB_Map_Integer_SetString::getThing(lineNumber, usesTable);
}
bool PKB_Map_Uses::isUses(int lineNumber, std::string usedName) {
    return PKB_Map_Integer_SetString::isThing(lineNumber, usedName, usesTable);
}
bool PKB_Map_Uses::isUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    return PKB_Map_Integer_SetString::isThing(lineNumber, usedNames, usesTable);
}

void PKB_Map_Uses::insertUsedBy(std::string name, std::unordered_set<int> usedByLines) {
    PKB_Map_String_SetInteger::insertThing(name, usedByLines, usedByTable);
}
std::unordered_set<int> PKB_Map_Uses::getUsedBy(std::string name) {
    return PKB_Map_String_SetInteger::getThing(name, usedByTable);
}
bool PKB_Map_Uses::isUsedBy(std::string name, int usedByLine) {
    return PKB_Map_String_SetInteger::isThing(name, usedByLine, usedByTable);
}
bool PKB_Map_Uses::isUsedBy(std::string name, std::unordered_set<int> usedByLines) {
    return PKB_Map_String_SetInteger::isThing(name, usedByLines, usedByTable);
}

int PKB_Map_Uses::getSizeUses() {
    return PKB_Map_Integer_SetString::getSize(usesTable);
}
bool PKB_Map_Uses::hasKeyUses(int lineNumber) {
    return PKB_Map_Integer_SetString::hasKey(lineNumber, usesTable);
}
std::vector<int> PKB_Map_Uses::getAllKeysUses() {
    return PKB_Map_Integer_SetString::getAllKeys(usesTable);
}
std::vector<std::unordered_set<std::string>> PKB_Map_Uses::getAllValuesUses() {
    return PKB_Map_Integer_SetString::getAllValues(usesTable);
}

int PKB_Map_Uses::getSizeUsedBy() {
    return PKB_Map_String_SetInteger::getSize(usedByTable);
}
bool PKB_Map_Uses::hasKeyUsedBy(std::string name) {
    return PKB_Map_String_SetInteger::hasKey(name, usedByTable);
}
std::vector<std::string> PKB_Map_Uses::getAllKeysUsedBy() {
    return PKB_Map_String_SetInteger::getAllKeys(usedByTable);
}
std::vector<std::unordered_set<int>> PKB_Map_Uses::getAllValuesUsedBy() {
    return PKB_Map_String_SetInteger::getAllValues(usedByTable);
}

void PKB_Map_Uses::clearAll() {
    PKB_Map_Integer_SetString::clear(usesTable);
    PKB_Map_String_SetInteger::clear(usedByTable);
}