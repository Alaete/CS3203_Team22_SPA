#pragma once

#include "PKB_Map_AAstarCCstarFstarNNstarPstar.h"

class PKB_Map_AffectsStar :
    public PKB_Map_AAstarCCstarFstarNNstarPstar {
public:
    PKB_Map_AffectsStar();

    void insertAffectsStar(int lineNumber, std::unordered_set<int> AffectsStarLines);
    std::unordered_set<int> getAffectsStar(int lineNumber);
    bool isAffectsStar(int lineNumber, int AffectsStarLine);
    bool isAffectsStar(int lineNumber, std::unordered_set<int> AffectsStarLines);

    void insertAffectedByStar(int lineNumber, std::unordered_set<int> AffectedByStarLines);
    std::unordered_set<int> getAffectedByStar(int lineNumber);
    bool isAffectedByStar(int lineNumber, int AffectedByStarLine);
    bool isAffectedByStar(int lineNumber, std::unordered_set<int> AffectedByStarLines);

    int getSizeAffectsStar();
    int getAreaAffectsStar();
    bool hasKeyAffectsStar(int lineNumber);
    std::vector<int> getAllKeysAffectsStar();
    std::vector<std::unordered_set<int>> getAllValuesAffectsStar();

    int getSizeAffectedByStar();
    bool hasKeyAffectedByStar(int lineNumber);
    std::vector<int> getAllKeysAffectedByStar();
    std::vector<std::unordered_set<int>> getAllValuesAffectedByStar();
};
