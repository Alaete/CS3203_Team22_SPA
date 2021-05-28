#pragma once

#include "PKB_Map_AAstarCCstarFstarNNstarPstar.h"

class PKB_Map_Affects :
    public PKB_Map_AAstarCCstarFstarNNstarPstar {
public:
    PKB_Map_Affects();

    void insertAffects(int lineNumber, std::unordered_set<int> affectsLines);
    std::unordered_set<int> getAffects(int lineNumber);
    bool isAffects(int lineNumber, int affectsLine);
    bool isAffects(int lineNumber, std::unordered_set<int> affectsLines);

    void insertAffectedBy(int lineNumber, std::unordered_set<int> affectedByLines);
    std::unordered_set<int> getAffectedBy(int lineNumber);
    bool isAffectedBy(int lineNumber, int affectedByLine);
    bool isAffectedBy(int lineNumber, std::unordered_set<int> affectedByLines);

    int getSizeAffects();
    int getAreaAffects();
    bool hasKeyAffects(int lineNumber);
    std::vector<int> getAllKeysAffects();
    std::vector<std::unordered_set<int>> getAllValuesAffects();

    int getSizeAffectedBy();
    bool hasKeyAffectedBy(int lineNumber);
    std::vector<int> getAllKeysAffectedBy();
    std::vector<std::unordered_set<int>> getAllValuesAffectedBy();
};

