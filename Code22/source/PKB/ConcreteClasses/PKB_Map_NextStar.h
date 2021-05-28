#pragma once

#include "PKB_Map_AAstarCCstarFstarNNstarPstar.h"

class PKB_Map_NextStar :
    public PKB_Map_AAstarCCstarFstarNNstarPstar {
public:
    PKB_Map_NextStar();

    void insertNextStar(int key, std::unordered_set<int> values);
    std::unordered_set<int> getNextStar(int key);
    bool isNextStar(int key, int value);
    bool isNextStar(int key, std::unordered_set<int> values);

    void insertPreviousStar(int key, std::unordered_set<int> values);
    std::unordered_set<int> getPreviousStar(int key);
    bool isPreviousStar(int key, int reverseValue);
    bool isPreviousStar(int key, std::unordered_set<int> reverseValues);

    int getSizeNextStar();
    int getAreaNextStar();
    bool hasKeyNextStar(int key);
    std::vector<int> getAllKeysNextStar();
    std::vector<std::unordered_set<int>> getAllValuesNextStar();

    int getSizePreviousStar();
    bool hasKeyPreviousStar(int key);
    std::vector<int> getAllKeysPreviousStar();
    std::vector<std::unordered_set<int>> getAllValuesPreviousStar();
};

