#pragma once

#include "PKB_Map_Integer_SetString.h"
#include "PKB_Map_String_SetInteger.h"

class PKB_Map_Uses :
    public PKB_Map_Integer_SetString,
    public PKB_Map_String_SetInteger
{
protected:
    std::unordered_map<int, std::unordered_set<std::string>> usesTable;
    std::unordered_map<std::string, std::unordered_set<int>> usedByTable;
    void insertUsedBy(std::string name, std::unordered_set<int> usedByLines);
public:
    PKB_Map_Uses();

    void insertUses(int lineNumber, std::unordered_set<std::string> usedNames);
    std::unordered_set<std::string> getUses(int lineNumber);
    bool isUses(int lineNumber, std::string usedName);
    bool isUses(int lineNumber, std::unordered_set<std::string> usedNames);

    std::unordered_set<int> getUsedBy(std::string name);
    bool isUsedBy(std::string name, int usedByLine);
    bool isUsedBy(std::string name, std::unordered_set<int> usedByLines);

    int getSizeUses();
    bool hasKeyUses(int lineNumber);
    std::vector<int> getAllKeysUses();
    std::vector<std::unordered_set<std::string>> getAllValuesUses();

    int getSizeUsedBy();
    bool hasKeyUsedBy(std::string name);
    std::vector<std::string> getAllKeysUsedBy();
    std::vector<std::unordered_set<int>> getAllValuesUsedBy();

    void clearAll();
};