#include "PKB_Map_Affects.h"

PKB_Map_Affects::PKB_Map_Affects() {}

void PKB_Map_Affects::insertAffects(int lineNumber, std::unordered_set<int> affectsLines) {
    PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingNoReverse(lineNumber, affectsLines);
}
std::unordered_set<int> PKB_Map_Affects::getAffects(int lineNumber) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getThing(lineNumber);
}
bool PKB_Map_Affects::isAffects(int lineNumber, int affectsLine) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThing(lineNumber, affectsLine);
}
bool PKB_Map_Affects::isAffects(int lineNumber, std::unordered_set<int> affectsLines) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThing(lineNumber, affectsLines);
}

void PKB_Map_Affects::insertAffectedBy(int lineNumber, std::unordered_set<int> affectedByLines) {
    PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingReverse(lineNumber, affectedByLines);
}
std::unordered_set<int> PKB_Map_Affects::getAffectedBy(int lineNumber) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getThingReverse(lineNumber);
}
bool PKB_Map_Affects::isAffectedBy(int lineNumber, int affectedByLine) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThingReverse(lineNumber, affectedByLine);
}
bool PKB_Map_Affects::isAffectedBy(int lineNumber, std::unordered_set<int> affectedByLines) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThingReverse(lineNumber, affectedByLines);
}

int PKB_Map_Affects::getSizeAffects() {
    return getSize();
}
int PKB_Map_Affects::getAreaAffects() {
    return getArea();
}
bool PKB_Map_Affects::hasKeyAffects(int lineNumber) {
    return hasKey(lineNumber);
}
std::vector<int> PKB_Map_Affects::getAllKeysAffects() {
    return getAllKeys();
}
std::vector<std::unordered_set<int>> PKB_Map_Affects::getAllValuesAffects() {
    return getAllValues();
}

int PKB_Map_Affects::getSizeAffectedBy() {
    return getSizeReverse();
}
bool PKB_Map_Affects::hasKeyAffectedBy(int lineNumber) {
    return hasKeyReverse(lineNumber);
}
std::vector<int> PKB_Map_Affects::getAllKeysAffectedBy() {
    return getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB_Map_Affects::getAllValuesAffectedBy() {
    return getAllValuesReverse();
}