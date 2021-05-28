#pragma once

#include "PKB_Map_Integer_SetInteger.h"

class PKB_Map_ParentStar :
    public PKB_Map_Integer_SetInteger
{
protected:
    std::unordered_map<int, std::unordered_set<int>> parentStarTable;
    std::unordered_map<int, std::unordered_set<int>> childStarTable;
    void insertChildStar(int lineNumber, std::unordered_set<int> childLines);
public:
    PKB_Map_ParentStar();

    void insertParentStar(int lineNumber, std::unordered_set<int> parentLines);
    std::unordered_set<int> getParentStar(int lineNumber);
    bool isParentStar(int lineNumber, int parentLine);
    bool isParentStar(int lineNumber, std::unordered_set<int> parentLines);

    std::unordered_set<int> getChildStar(int lineNumber);
    bool isChildStar(int lineNumber, int childLine);
    bool isChildStar(int lineNumber, std::unordered_set<int> childLines);

    int getSizeParentStar();
    bool hasKeyParentStar(int lineNumber);
    std::vector<int> getAllKeysParentStar();
    std::vector<std::unordered_set<int>> getAllValuesParentStar();

    int getSizeChildStar();
    bool hasKeyChildStar(int lineNumber);
    std::vector<int> getAllKeysChildStar();
    std::vector<std::unordered_set<int>> getAllValuesChildStar();

    void clearAll();
};