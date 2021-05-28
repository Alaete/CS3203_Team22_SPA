#pragma once

#include "PKB_Map_Integer_SetInteger.h"

class PKB_Map_FollowsStar :
    public PKB_Map_Integer_SetInteger
{
protected:
    std::unordered_map<int, std::unordered_set<int>> followsStarTable;
    std::unordered_map<int, std::unordered_set<int>> followedByStarTable;
    void insertFollowedByStar(int lineNumber, std::unordered_set<int> followerLines);
public:
    PKB_Map_FollowsStar();

    void insertFollowsStar(int lineNumber, std::unordered_set<int> leaderLines);
    std::unordered_set<int> getFollowsStar(int lineNumber);
    bool isFollowsStar(int lineNumber, int leaderLine);
    bool isFollowsStar(int lineNumber, std::unordered_set<int> leaderLines);

    std::unordered_set<int> getFollowedByStar(int lineNumber);
    bool isFollowedByStar(int lineNumber, int followerLine);
    bool isFollowedByStar(int lineNumber, std::unordered_set<int> followerLines);

    int getSizeFollowsStar();
    bool hasKeyFollowsStar(int lineNumber);
    std::vector<int> getAllKeysFollowsStar();
    std::vector<std::unordered_set<int>> getAllValuesFollowsStar();

    int getSizeFollowedByStar();
    bool hasKeyFollowedByStar(int lineNumber);
    std::vector<int> getAllKeysFollowedByStar();
    std::vector<std::unordered_set<int>> getAllValuesFollowedByStar();

    void clearAll();
};