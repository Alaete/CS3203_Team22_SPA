#include "PKB_Map_Parent.h"

PKB_Map_Parent::PKB_Map_Parent() {}

void PKB_Map_Parent::insertParent(int lineNumber, int parentLine) {
    if (PKB_Map_Integer_Integer::getThing(lineNumber, parentTable) == -1) {
        PKB_Map_Integer_Integer::insertThing(lineNumber, parentLine, parentTable);
    }
    else {
        throw PKB_Util::duplicateEntryError(lineNumber);
    }

    PKB_Map_Parent::insertChild(parentLine, lineNumber);
}
int PKB_Map_Parent::getParent(int lineNumber) {
    return PKB_Map_Integer_Integer::getThing(lineNumber, parentTable);
}
bool PKB_Map_Parent::isParent(int lineNumber, int parentLine) {
    return PKB_Map_Integer_Integer::isThing(lineNumber, parentLine, parentTable);
}

void PKB_Map_Parent::insertChild(int lineNumber, int childLine) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, { childLine }, childTable);
}
std::unordered_set<int> PKB_Map_Parent::getChild(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, childTable);
}
bool PKB_Map_Parent::isChild(int lineNumber, int childLine) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, childLine, childTable);
}
bool PKB_Map_Parent::isChild(int lineNumber, std::unordered_set<int> childLines) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, childLines, childTable);
}

int PKB_Map_Parent::getSizeParent() {
    return PKB_Map_Integer_Integer::getSize(parentTable);
}
bool PKB_Map_Parent::hasKeyParent(int lineNumber) {
    return PKB_Map_Integer_Integer::hasKey(lineNumber, parentTable);
}
std::vector<int> PKB_Map_Parent::getAllKeysParent() {
    return PKB_Map_Integer_Integer::getAllKeys(parentTable);
}
std::vector<int> PKB_Map_Parent::getAllValuesParent() {
    return PKB_Map_Integer_Integer::getAllValues(parentTable);
}

int PKB_Map_Parent::getSizeChild() {
    return PKB_Map_Integer_SetInteger::getSize(childTable);
}
bool PKB_Map_Parent::hasKeyChild(int lineNumber) {
    return PKB_Map_Integer_SetInteger::hasKey(lineNumber, childTable);
}
std::vector<int> PKB_Map_Parent::getAllKeysChild() {
    return PKB_Map_Integer_SetInteger::getAllKeys(childTable);
}
std::vector<std::unordered_set<int>> PKB_Map_Parent::getAllValuesChild() {
    return PKB_Map_Integer_SetInteger::getAllValues(childTable);
}

void PKB_Map_Parent::clearAll() {
    PKB_Map_Integer_Integer::clear(parentTable);
    PKB_Map_Integer_SetInteger::clear(childTable);
}