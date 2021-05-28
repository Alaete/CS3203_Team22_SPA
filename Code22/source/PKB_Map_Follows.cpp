#include "PKB_Map_Follows.h"

PKB_Map_Follows::PKB_Map_Follows() {}

void PKB_Map_Follows::insertFollows(int lineNumber, int leaderLine) {
    if (PKB_Map_Integer_Integer::getThing(lineNumber, followsTable) == -1) {
        PKB_Map_Integer_Integer::insertThing(lineNumber, leaderLine, followsTable);
    }
    else {
        throw PKB_Util::duplicateEntryError(lineNumber);
    }

    PKB_Map_Follows::insertFollowedBy(leaderLine, { lineNumber });
}
int PKB_Map_Follows::getFollows(int lineNumber) {
    return PKB_Map_Integer_Integer::getThing(lineNumber, followsTable);
}
bool PKB_Map_Follows::isFollows(int lineNumber, int leaderLine) {
    return PKB_Map_Integer_Integer::isThing(lineNumber, leaderLine, followsTable);
}

void PKB_Map_Follows::insertFollowedBy(int lineNumber, int followerLine) {
    if (PKB_Map_Integer_Integer::getThing(lineNumber, followedByTable) == -1) {
        PKB_Map_Integer_Integer::insertThing(lineNumber, followerLine, followedByTable);
    }
    else {
        throw PKB_Util::duplicateEntryError(lineNumber);
    }
}
int PKB_Map_Follows::getFollowedBy(int lineNumber) {
    return PKB_Map_Integer_Integer::getThing(lineNumber, followedByTable);
}
bool PKB_Map_Follows::isFollowedBy(int lineNumber, int followerLine) {
    return PKB_Map_Integer_Integer::isThing(lineNumber, followerLine, followedByTable);
}

int PKB_Map_Follows::getSizeFollows() {
    return PKB_Map_Integer_Integer::getSize(followsTable);
}
bool PKB_Map_Follows::hasKeyFollows(int lineNumber) {
    return PKB_Map_Integer_Integer::hasKey(lineNumber, followsTable);
}
std::vector<int> PKB_Map_Follows::getAllKeysFollows() {
    return PKB_Map_Integer_Integer::getAllKeys(followsTable);
}
std::vector<int> PKB_Map_Follows::getAllValuesFollows() {
    return PKB_Map_Integer_Integer::getAllValues(followsTable);
}

int PKB_Map_Follows::getSizeFollowedBy() {
    return PKB_Map_Integer_Integer::getSize(followedByTable);
}
bool PKB_Map_Follows::hasKeyFollowedBy(int lineNumber) {
    return PKB_Map_Integer_Integer::hasKey(lineNumber, followedByTable);
}
std::vector<int> PKB_Map_Follows::getAllKeysFollowedBy() {
    return PKB_Map_Integer_Integer::getAllKeys(followedByTable);
}
std::vector<int> PKB_Map_Follows::getAllValuesFollowedBy() {
    return PKB_Map_Integer_Integer::getAllValues(followedByTable);
}

void PKB_Map_Follows::clearAll() {
    PKB_Map_Integer_Integer::clear(followsTable);
    PKB_Map_Integer_Integer::clear(followedByTable);
}