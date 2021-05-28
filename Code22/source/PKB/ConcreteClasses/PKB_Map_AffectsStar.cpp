#include "PKB_Map_AffectsStar.h"

PKB_Map_AffectsStar::PKB_Map_AffectsStar() {}

void PKB_Map_AffectsStar::insertAffectsStar(int lineNumber, std::unordered_set<int> AffectsStarLines) {
    PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingNoReverse(lineNumber, AffectsStarLines);
}
std::unordered_set<int> PKB_Map_AffectsStar::getAffectsStar(int lineNumber) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getThing(lineNumber);
}
bool PKB_Map_AffectsStar::isAffectsStar(int lineNumber, int AffectsStarLine) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThing(lineNumber, AffectsStarLine);
}
bool PKB_Map_AffectsStar::isAffectsStar(int lineNumber, std::unordered_set<int> AffectsStarLines) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThing(lineNumber, AffectsStarLines);
}

void PKB_Map_AffectsStar::insertAffectedByStar(int lineNumber, std::unordered_set<int> AffectedByStarLines) {
    PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingReverse(lineNumber, AffectedByStarLines);
}
std::unordered_set<int> PKB_Map_AffectsStar::getAffectedByStar(int lineNumber) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getThingReverse(lineNumber);
}
bool PKB_Map_AffectsStar::isAffectedByStar(int lineNumber, int AffectedByStarLine) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThingReverse(lineNumber, AffectedByStarLine);
}
bool PKB_Map_AffectsStar::isAffectedByStar(int lineNumber, std::unordered_set<int> AffectedByStarLines) {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThingReverse(lineNumber, AffectedByStarLines);
}

int PKB_Map_AffectsStar::getSizeAffectsStar() {
    return getSize();
}
int PKB_Map_AffectsStar::getAreaAffectsStar() {
    return getArea();
}
bool PKB_Map_AffectsStar::hasKeyAffectsStar(int lineNumber) {
    return hasKey(lineNumber);
}
std::vector<int> PKB_Map_AffectsStar::getAllKeysAffectsStar() {
    return getAllKeys();
}
std::vector<std::unordered_set<int>> PKB_Map_AffectsStar::getAllValuesAffectsStar() {
    return getAllValues();
}

int PKB_Map_AffectsStar::getSizeAffectedByStar() {
    return getSizeReverse();
}
bool PKB_Map_AffectsStar::hasKeyAffectedByStar(int lineNumber) {
    return hasKeyReverse(lineNumber);
}
std::vector<int> PKB_Map_AffectsStar::getAllKeysAffectedByStar() {
    return getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB_Map_AffectsStar::getAllValuesAffectedByStar() {
    return getAllValuesReverse();
}