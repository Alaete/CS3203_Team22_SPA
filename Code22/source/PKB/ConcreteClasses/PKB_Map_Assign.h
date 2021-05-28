#pragma once

#include "../AbstractClasses/PKB_Map_Integer_PairStringString.h"

class PKB_Map_Assign :
    public PKB_Map_Integer_PairStringString {
private:
    std::unordered_map<int, std::pair<std::string, std::string>> assignTable;
public:
    PKB_Map_Assign();

    void insertAssignLHS(int lineNumber, std::string variableLHS);
    void insertAssignRHS(int lineNumber, std::string shuntedRHS);
    std::pair<std::string, std::string> getAssign(int lineNumber);

    int getSizeAssign();
    bool hasKeyAssign(int lineNumber);
    std::vector<int> getAllKeysAssign();
    std::vector<std::pair<std::string, std::string>> getAllValuesAssign();

    void clear();
};

