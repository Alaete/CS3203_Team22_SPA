#pragma once

#include "../AbstractClasses/PKB_Map_Integer_Integer.h"

class PKB_Map_Follows :
    public PKB_Map_Integer_Integer {
private:
    std::unordered_map<int, int> followsTable;
    std::unordered_map<int, int> followedByTable;
    void insertFollowedBy(int lineNumber, int followerLine);
public:
    PKB_Map_Follows();

    void insertFollows(int lineNumber, int leaderLine);
    int getFollows(int lineNumber);
    bool isFollows(int lineNumber, int leaderLine);

    int getFollowedBy(int lineNumber);
    bool isFollowedBy(int lineNumber, int followerLine);

    int getSizeFollows();
    bool hasKeyFollows(int lineNumber);
    std::vector<int> getAllKeysFollows();
    std::vector<int> getAllValuesFollows();

    int getSizeFollowedBy();
    bool hasKeyFollowedBy(int lineNumber);
    std::vector<int> getAllKeysFollowedBy();
    std::vector<int> getAllValuesFollowedBy();

    void clear();
};

