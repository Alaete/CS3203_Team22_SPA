#pragma once

#include "PKB_Map_Integer_SetInteger.h"

class PKB_Map_Calls :
    public PKB_Map_Integer_SetInteger
{
protected:
    std::unordered_map<int, std::unordered_set<int>> callsTable;
    std::unordered_map<int, std::unordered_set<int>> calledByTable;
    void insertCalledBy(int procedureIndex, std::unordered_set<int> calledByProcedures);
public:
    PKB_Map_Calls();

    void insertCalls(int procedureIndex, std::unordered_set<int> calledProcedures);
    std::unordered_set<int> getCalls(int procedureIndex);
    bool isCalls(int procedureIndex, int calledLine);
    bool isCalls(int procedureIndex, std::unordered_set<int> calledProcedures);

    std::unordered_set<int> getCalledBy(int procedureIndex);
    bool isCalledBy(int procedureIndex, int calledByLine);
    bool isCalledBy(int procedureIndex, std::unordered_set<int> calledByProcedures);

    int getSizeCalls();
    bool hasKeyCalls(int procedureIndex);
    std::vector<int> getAllKeysCalls();
    std::vector<std::unordered_set<int>> getAllValuesCalls();

    int getSizeCalledBy();
    bool hasKeyCalledBy(int procedureIndex);
    std::vector<int> getAllKeysCalledBy();
    std::vector<std::unordered_set<int>> getAllValuesCalledBy();

    void clearAll();
};

