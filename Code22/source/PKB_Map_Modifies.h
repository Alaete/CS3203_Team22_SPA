#pragma once

#include "PKB_Map_Integer_SetString.h"
#include "PKB_Map_String_SetInteger.h"

class PKB_Map_Modifies :
    public PKB_Map_Integer_SetString,
    public PKB_Map_String_SetInteger
{
protected:
    std::unordered_map<int, std::unordered_set<std::string>> modifiesTable;
    std::unordered_map<std::string, std::unordered_set<int>> modifiedByTable;
    void insertModifiedBy(std::string name, std::unordered_set<int> modifiedByNames);
public:
    PKB_Map_Modifies();

    void insertModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    std::unordered_set<std::string> getModifies(int lineNumber);
    bool isModifies(int lineNumber, std::string modifiedName);
    bool isModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);

    std::unordered_set<int> getModifiedBy(std::string name);
    bool isModifiedBy(std::string name, int modifiedByLine);
    bool isModifiedBy(std::string name, std::unordered_set<int> modifiedByLines);

    int getSizeModifies();
    bool hasKeyModifies(int lineNumber);
    std::vector<int> getAllKeysModifies();
    std::vector<std::unordered_set<std::string>> getAllValuesModifies();

    int getSizeModifiedBy();
    bool hasKeyModifiedBy(std::string name);
    std::vector<std::string> getAllKeysModifiedBy();
    std::vector<std::unordered_set<int>> getAllValuesModifiedBy();

    void clearAll();
};