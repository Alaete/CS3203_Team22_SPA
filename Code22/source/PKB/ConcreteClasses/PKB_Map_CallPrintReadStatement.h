#pragma once

#include "../AbstractClasses/PKB_Map_Integer_String.h"
#include "../AbstractClasses/PKB_Map_String_SetInteger.h"

#include <unordered_set>

class PKB_Map_CallPrintReadStatement :
    public PKB_Map_Integer_String, 
    public PKB_Map_String_SetInteger {
private:
    std::unordered_map<std::string, std::unordered_set<int>> reverseTable;
    std::unordered_map<int, std::string> table;
public:
    PKB_Map_CallPrintReadStatement();

    void insertThing(int lineNumber, std::string name);
    std::string getThing(int lineNumber);
    bool isThing(int lineNumber, std::string name);
    std::unordered_set<int> getKeys(std::string name);

    int getSize();
    bool hasKey(int lineNumber);
    std::vector<int> getAllKeys();
    std::vector<std::string> getAllValues();

    void clear();
};

