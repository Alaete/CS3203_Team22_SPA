#pragma once

#include "../AbstractClasses/PKB_Map_Integer_SetString.h"
#include "../AbstractClasses/PKB_Map_String_SetInteger.h"

class PKB_Map_ModifiesUses :
    public PKB_Map_Integer_SetString,
    public PKB_Map_String_SetInteger {
protected:
    std::unordered_map<int, std::unordered_set<std::string>> table;
    std::unordered_map<std::string, std::unordered_set<int>> reverseTable;
    void insertThingReverse(std::string name, std::unordered_set<int> reverseLines);
public:
    PKB_Map_ModifiesUses();

    void insertThing(int lineNumber, std::unordered_set<std::string> names);
    std::unordered_set<std::string> getThing(int lineNumber);
    bool isThing(int lineNumber, std::string name);
    bool isThing(int lineNumber, std::unordered_set<std::string> names);

    std::unordered_set<int> getThingReverse(std::string name);
    bool isThingReverse(std::string name, int reverseLine);
    bool isThingReverse(std::string name, std::unordered_set<int> reverseLines);

    int getSize();
    int getArea();
    bool hasKey(int lineNumber);
    std::vector<int> getAllKeys();
    std::vector<std::unordered_set<std::string>> getAllValues();

    int getSizeReverse();
    bool hasKeyReverse(std::string name);
    std::vector<std::string> getAllKeysReverse();
    std::vector<std::unordered_set<int>> getAllValuesReverse();

    void clear();
};

