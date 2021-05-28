#pragma once

#include "../AbstractClasses/PKB_Map_Integer_SetString.h"
#include <unordered_set>

class PKB_Map_IfWhile :
    public PKB_Map_Integer_SetString {
private:
    std::unordered_map<int, std::unordered_set<std::string>> table;
public:
    PKB_Map_IfWhile();

    void insertThing(int lineNumber, std::unordered_set<std::string> conditions);
    std::unordered_set<std::string> getThing(int lineNumber);
    bool isThing(int lineNumber, std::string condition);
    bool isThing(int lineNumber, std::unordered_set<std::string> conditions);

    int getSize();
    int getArea();
    bool hasKey(int lineNumber);
    std::vector<int> getAllKeys();
    std::vector<std::unordered_set<std::string>> getAllValues();

    void clear();
};

