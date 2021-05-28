#pragma once

#include "../AbstractClasses/PKB_Map_Integer_SetInteger.h"

class PKB_Map_Constant :
    public PKB_Map_Integer_SetInteger {
private:
    std::unordered_map<int, std::unordered_set<int>> constantTable;
public:
    PKB_Map_Constant();

    void insertConstant(int lineNumber, std::unordered_set<int> constantValues);
    std::unordered_set<int> getConstant(int lineNumber);
    bool isConstant(int lineNumber, std::unordered_set<int> constantValues);
    bool isConstant(int lineNumber, int constantValue);

    int getSizeConstant();
    bool hasKeyConstant(int lineNumber);
    std::vector<int> getAllKeysConstant();
    std::vector<std::unordered_set<int>> getAllValuesConstant();

    void clear();
};

