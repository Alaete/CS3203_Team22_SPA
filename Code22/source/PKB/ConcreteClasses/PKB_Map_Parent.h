#pragma once

#include "../AbstractClasses/PKB_Map_Integer_Integer.h"
#include "../AbstractClasses/PKB_Map_Integer_SetInteger.h"

class PKB_Map_Parent :
    public PKB_Map_Integer_Integer,
    public PKB_Map_Integer_SetInteger {
private:
    std::unordered_map<int, int> parentTable;
    std::unordered_map<int, std::unordered_set<int>> childTable;
    void insertChild(int lineNumber, int childLine);
public:
    PKB_Map_Parent();

    void insertParent(int lineNumber, int parentLine);
    int getParent(int lineNumber);
    bool isParent(int lineNumber, int parentLine);

    std::unordered_set<int> getChild(int lineNumber);
    bool isChild(int lineNumber, int childLine);
    bool isChild(int lineNumber, std::unordered_set<int> childLines);

    int getSizeParent();
    bool hasKeyParent(int lineNumber);
    std::vector<int> getAllKeysParent();
    std::vector<int> getAllValuesParent();

    int getSizeChild();
    bool hasKeyChild(int lineNumber);
    std::vector<int> getAllKeysChild();
    std::vector<std::unordered_set<int>> getAllValuesChild();

    void clear();
};

