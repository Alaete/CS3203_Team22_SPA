#pragma once

#include "PKB_Map_Integer_SetInteger.h"

class PKB_Map_Next :
    public PKB_Map_Integer_SetInteger
{
protected:
    std::unordered_map<int, std::unordered_set<int>> nextTable;
    std::unordered_map<int, std::unordered_set<int>> previousTable;
    void insertPrevious(int lineNumber, std::unordered_set<int> previousLines);
public:
    PKB_Map_Next();

    void insertNext(int lineNumber, std::unordered_set<int> nextLines);
    std::unordered_set<int> getNext(int lineNumber);
    bool isNext(int lineNumber, int nextLine);
    bool isNext(int lineNumber, std::unordered_set<int> nextLines);

    std::unordered_set<int> getPrevious(int lineNumber);
    bool isPrevious(int lineNumber, int previousLine);
    bool isPrevious(int lineNumber, std::unordered_set<int> previousLines);

    int getSizeNext();
    bool hasKeyNext(int lineNumber);
    std::vector<int> getAllKeysNext();
    std::vector<std::unordered_set<int>> getAllValuesNext();

    int getSizePrevious();
    bool hasKeyPrevious(int lineNumber);
    std::vector<int> getAllKeysPrevious();
    std::vector<std::unordered_set<int>> getAllValuesPrevious();

    void clearAll();
};

