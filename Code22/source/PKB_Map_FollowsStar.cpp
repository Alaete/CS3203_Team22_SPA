#include "PKB_Map_FollowsStar.h"

PKB_Map_FollowsStar::PKB_Map_FollowsStar() {}

void PKB_Map_FollowsStar::insertFollowsStar(int lineNumber, std::unordered_set<int> leaderLines) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, leaderLines, followsStarTable);

    for (int element : leaderLines) {
        PKB_Map_FollowsStar::insertFollowedByStar(element, { lineNumber });
    }
}
std::unordered_set<int> PKB_Map_FollowsStar::getFollowsStar(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, followsStarTable);
}
bool PKB_Map_FollowsStar::isFollowsStar(int lineNumber, int leaderLine) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, leaderLine, followsStarTable);
}
bool PKB_Map_FollowsStar::isFollowsStar(int lineNumber, std::unordered_set<int> leaderLines) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, leaderLines, followsStarTable);
}

void PKB_Map_FollowsStar::insertFollowedByStar(int lineNumber, std::unordered_set<int> followerLines) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, followerLines, followedByStarTable);
}
std::unordered_set<int> PKB_Map_FollowsStar::getFollowedByStar(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, followedByStarTable);
}
bool PKB_Map_FollowsStar::isFollowedByStar(int lineNumber, int followerLine) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, followerLine, followedByStarTable);
}
bool PKB_Map_FollowsStar::isFollowedByStar(int lineNumber, std::unordered_set<int> followerLines) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, followerLines, followedByStarTable);
}

int PKB_Map_FollowsStar::getSizeFollowsStar() {
    return PKB_Map_Integer_SetInteger::getSize(followsStarTable);
}
bool PKB_Map_FollowsStar::hasKeyFollowsStar(int lineNumber) {
    return PKB_Map_Integer_SetInteger::hasKey(lineNumber, followsStarTable);
}
std::vector<int> PKB_Map_FollowsStar::getAllKeysFollowsStar() {
    return PKB_Map_Integer_SetInteger::getAllKeys(followsStarTable);
}
std::vector<std::unordered_set<int>> PKB_Map_FollowsStar::getAllValuesFollowsStar() {
    return PKB_Map_Integer_SetInteger::getAllValues(followsStarTable);
}

int PKB_Map_FollowsStar::getSizeFollowedByStar() {
    return PKB_Map_Integer_SetInteger::getSize(followedByStarTable);
}
bool PKB_Map_FollowsStar::hasKeyFollowedByStar(int lineNumber) {
    return PKB_Map_Integer_SetInteger::hasKey(lineNumber, followedByStarTable);
}
std::vector<int> PKB_Map_FollowsStar::getAllKeysFollowedByStar() {
    return PKB_Map_Integer_SetInteger::getAllKeys(followedByStarTable);
}
std::vector<std::unordered_set<int>> PKB_Map_FollowsStar::getAllValuesFollowedByStar() {
    return PKB_Map_Integer_SetInteger::getAllValues(followedByStarTable);
}

void PKB_Map_FollowsStar::clearAll() {
    PKB_Map_Integer_SetInteger::clear(followsStarTable);
    PKB_Map_Integer_SetInteger::clear(followedByStarTable);
}