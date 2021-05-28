#pragma once

#include "../AbstractClasses/PKB_Map_Integer_String.h"

class PKB_Map_ProcedureVariable :
    public PKB_Map_Integer_String {
private:
    std::unordered_map<std::string, int> reverseTable;
    std::unordered_map<int, std::string> table;
    int currentIndex = 0;
public:
    PKB_Map_ProcedureVariable();

    int insertThing(std::string procName);
    std::string getThing(int procIndex);
    int getKey(std::string procName);

    int getSize();
    bool hasKey(int procIndex);
    std::vector<int> getAllKeys();
    std::vector<std::string> getAllValues();

    void clear();
};

