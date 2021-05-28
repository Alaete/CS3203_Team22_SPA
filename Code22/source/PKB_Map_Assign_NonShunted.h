#pragma once

#include "PKB_Map_Integer_String.h"
#include <unordered_set>

class PKB_Map_Assign_NonShunted :
    public PKB_Map_Integer_String
{
protected:
    std::unordered_map<int, std::string> assignNonShuntedTable;
public:
    PKB_Map_Assign_NonShunted();

    void insertAssign(int lineNumber, std::string assignStmt);
    std::string getAssign(int lineNumber);

    int getSizeAssign();
    bool hasKeyAssign(int lineNumber);
    std::vector<int> getAllKeysAssign();
    std::vector<std::string> getAllValuesAssign();

    void clearAll();
};

