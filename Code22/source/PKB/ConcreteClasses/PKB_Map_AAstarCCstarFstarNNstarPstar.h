#pragma once

#include "../AbstractClasses/PKB_Map_Integer_SetInteger.h"

class PKB_Map_AAstarCCstarFstarNNstarPstar :
    public PKB_Map_Integer_SetInteger {
private:
    std::unordered_map<int, std::unordered_set<int>> table;
    std::unordered_map<int, std::unordered_set<int>> reverseTable;
protected:
    void insertThingReverse(int key, std::unordered_set<int> reverseValues);
public:
    PKB_Map_AAstarCCstarFstarNNstarPstar();

    void insertThing(int key, std::unordered_set<int> values);
    void insertThingNoReverse(int key, std::unordered_set<int> values);
    std::unordered_set<int> getThing(int key);
    bool isThing(int key, int value);
    bool isThing(int key, std::unordered_set<int> values);

    std::unordered_set<int> getThingReverse(int key);
    bool isThingReverse(int key, int reverseValue);
    bool isThingReverse(int key, std::unordered_set<int> reverseValues);

    int getSize();
    int getArea();
    bool hasKey(int key);
    std::vector<int> getAllKeys();
    std::vector<std::unordered_set<int>> getAllValues();

    int getSizeReverse();
    bool hasKeyReverse(int key);
    std::vector<int> getAllKeysReverse();
    std::vector<std::unordered_set<int>> getAllValuesReverse();

    void clear();
};

