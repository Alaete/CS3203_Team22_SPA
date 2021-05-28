#include "PKB_Map_ParentStar.h"

PKB_Map_ParentStar::PKB_Map_ParentStar() {}

void PKB_Map_ParentStar::insertParentStar(int lineNumber, std::unordered_set<int> parentLines) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, parentLines, parentStarTable);

    for (int element : parentLines) {
        PKB_Map_ParentStar::insertChildStar(element, { lineNumber });
    }
}
std::unordered_set<int> PKB_Map_ParentStar::getParentStar(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, parentStarTable);
}
bool PKB_Map_ParentStar::isParentStar(int lineNumber, int parentLine) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, parentLine, parentStarTable);
}
bool PKB_Map_ParentStar::isParentStar(int lineNumber, std::unordered_set<int> parentLines) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, parentLines, parentStarTable);
}

void PKB_Map_ParentStar::insertChildStar(int lineNumber, std::unordered_set<int> childLines) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, childLines, childStarTable);
}
std::unordered_set<int> PKB_Map_ParentStar::getChildStar(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, childStarTable);
}
bool PKB_Map_ParentStar::isChildStar(int lineNumber, int childLine) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, childLine, childStarTable);
}
bool PKB_Map_ParentStar::isChildStar(int lineNumber, std::unordered_set<int> childLines) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, childLines, childStarTable);
}

int PKB_Map_ParentStar::getSizeParentStar() {
    return getSize(parentStarTable);
}
bool PKB_Map_ParentStar::hasKeyParentStar(int lineNumber) {
    return hasKey(lineNumber, parentStarTable);
}
std::vector<int> PKB_Map_ParentStar::getAllKeysParentStar() {
    return getAllKeys(parentStarTable);
}
std::vector<std::unordered_set<int>> PKB_Map_ParentStar::getAllValuesParentStar() {
    return getAllValues(parentStarTable);
}

int PKB_Map_ParentStar::getSizeChildStar() {
    return getSize(childStarTable);
}
bool PKB_Map_ParentStar::hasKeyChildStar(int lineNumber) {
    return hasKey(lineNumber, childStarTable);
}
std::vector<int> PKB_Map_ParentStar::getAllKeysChildStar() {
    return getAllKeys(childStarTable);
}
std::vector<std::unordered_set<int>> PKB_Map_ParentStar::getAllValuesChildStar() {
    return getAllValues(childStarTable);
}

void PKB_Map_ParentStar::clearAll() {
    PKB_Map_Integer_SetInteger::clear(parentStarTable);
    PKB_Map_Integer_SetInteger::clear(childStarTable);
}