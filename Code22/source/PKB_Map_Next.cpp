#include "PKB_Map_Next.h"

PKB_Map_Next::PKB_Map_Next() {}

void PKB_Map_Next::insertNext(int lineNumber, std::unordered_set<int> nextLines) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, nextLines, nextTable);

    for (int element : nextLines) {
        PKB_Map_Next::insertPrevious(element, { lineNumber });
    }
}
std::unordered_set<int> PKB_Map_Next::getNext(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, nextTable);
}
bool PKB_Map_Next::isNext(int lineNumber, int nextLine) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, nextLine, nextTable);
}
bool PKB_Map_Next::isNext(int lineNumber, std::unordered_set<int> nextLines) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, nextLines, nextTable);
}

void PKB_Map_Next::insertPrevious(int lineNumber, std::unordered_set<int> previousLines) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, previousLines, previousTable);
}
std::unordered_set<int> PKB_Map_Next::getPrevious(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, previousTable);
}
bool PKB_Map_Next::isPrevious(int lineNumber, int previousLine) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, previousLine, previousTable);
}
bool PKB_Map_Next::isPrevious(int lineNumber, std::unordered_set<int> previousLines) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, previousLines, previousTable);
}

int PKB_Map_Next::getSizeNext() {
    return getSize(nextTable);
}
bool PKB_Map_Next::hasKeyNext(int lineNumber) {
    return hasKey(lineNumber, nextTable);
}
std::vector<int> PKB_Map_Next::getAllKeysNext() {
    return getAllKeys(nextTable);
}
std::vector<std::unordered_set<int>> PKB_Map_Next::getAllValuesNext() {
    return getAllValues(nextTable);
}

int PKB_Map_Next::getSizePrevious() {
    return getSize(previousTable);
}
bool PKB_Map_Next::hasKeyPrevious(int lineNumber) {
    return hasKey(lineNumber, previousTable);
}
std::vector<int> PKB_Map_Next::getAllKeysPrevious() {
    return getAllKeys(previousTable);
}
std::vector<std::unordered_set<int>> PKB_Map_Next::getAllValuesPrevious() {
    return getAllValues(previousTable);
}

void PKB_Map_Next::clearAll() {
    PKB_Map_Integer_SetInteger::clear(nextTable);
    PKB_Map_Integer_SetInteger::clear(previousTable);
}

