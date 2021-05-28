#include "PKB_Map_ModifiesUses.h"

PKB_Map_ModifiesUses::PKB_Map_ModifiesUses() {}

void PKB_Map_ModifiesUses::insertThing(int lineNumber, std::unordered_set<std::string> name) {
    PKB_Map_Integer_SetString::insertThing(lineNumber, name, table);

    for (std::string element : name) {
        PKB_Map_ModifiesUses::insertThingReverse(element, { lineNumber });
    }
}
std::unordered_set<std::string> PKB_Map_ModifiesUses::getThing(int lineNumber) {
    return PKB_Map_Integer_SetString::getThing(lineNumber, table);
}
bool PKB_Map_ModifiesUses::isThing(int lineNumber, std::string usedName) {
    return PKB_Map_Integer_SetString::isThing(lineNumber, usedName, table);
}
bool PKB_Map_ModifiesUses::isThing(int lineNumber, std::unordered_set<std::string> name) {
    return PKB_Map_Integer_SetString::isThing(lineNumber, name, table);
}

void PKB_Map_ModifiesUses::insertThingReverse(std::string name, std::unordered_set<int> reverseLines) {
    PKB_Map_String_SetInteger::insertThing(name, reverseLines, reverseTable);
}
std::unordered_set<int> PKB_Map_ModifiesUses::getThingReverse(std::string name) {
    return PKB_Map_String_SetInteger::getThing(name, reverseTable);
}
bool PKB_Map_ModifiesUses::isThingReverse(std::string name, int reverseLine) {
    return PKB_Map_String_SetInteger::isThing(name, reverseLine, reverseTable);
}
bool PKB_Map_ModifiesUses::isThingReverse(std::string name, std::unordered_set<int> reverseLines) {
    return PKB_Map_String_SetInteger::isThing(name, reverseLines, reverseTable);
}

int PKB_Map_ModifiesUses::getSize() {
    return PKB_Map_Integer_SetString::getSize(table);
}
int PKB_Map_ModifiesUses::getArea() {
    return PKB_Map_Integer_SetString::getArea(table);
}
bool PKB_Map_ModifiesUses::hasKey(int lineNumber) {
    return PKB_Map_Integer_SetString::hasKey(lineNumber, table);
}
std::vector<int> PKB_Map_ModifiesUses::getAllKeys() {
    return PKB_Map_Integer_SetString::getAllKeys(table);
}
std::vector<std::unordered_set<std::string>> PKB_Map_ModifiesUses::getAllValues() {
    return PKB_Map_Integer_SetString::getAllValues(table);
}

int PKB_Map_ModifiesUses::getSizeReverse() {
    return PKB_Map_String_SetInteger::getSize(reverseTable);
}
bool PKB_Map_ModifiesUses::hasKeyReverse(std::string name) {
    return PKB_Map_String_SetInteger::hasKey(name, reverseTable);
}
std::vector<std::string> PKB_Map_ModifiesUses::getAllKeysReverse() {
    return PKB_Map_String_SetInteger::getAllKeys(reverseTable);
}
std::vector<std::unordered_set<int>> PKB_Map_ModifiesUses::getAllValuesReverse() {
    return PKB_Map_String_SetInteger::getAllValues(reverseTable);
}

void PKB_Map_ModifiesUses::clear() {
    PKB_Map_Integer_SetString::clear(table);
    PKB_Map_String_SetInteger::clear(reverseTable);
}

