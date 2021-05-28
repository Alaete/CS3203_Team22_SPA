#pragma once

#include "PKB_Map_Integer_SetInteger.h"

class PKB_Map_CallsStar :
    public PKB_Map_Integer_SetInteger
{
protected:
    std::unordered_map<int, std::unordered_set<int>> callsStarTable;
    std::unordered_map<int, std::unordered_set<int>> calledByStarTable;
    void insertCalledByStar(int procedureIndex, std::unordered_set<int> calledByProcedures);
public:
    PKB_Map_CallsStar();

    void insertCallsStar(int procedureIndex, std::unordered_set<int> calledProcedures);
    std::unordered_set<int> getCallsStar(int procedureIndex);
    bool isCallsStar(int procedureIndex, int calledProcedure);
    bool isCallsStar(int procedureIndex, std::unordered_set<int> calledProcedures);

    std::unordered_set<int> getCalledByStar(int procedureIndex);
    bool isCalledByStar(int procedureIndex, int calledByStarLine);
    bool isCalledByStar(int procedureIndex, std::unordered_set<int> calledByProcedures);

    int getSizeCallsStar();
    bool hasKeyCallsStar(int procedureIndex);
    std::vector<int> getAllKeysCallsStar();
    std::vector<std::unordered_set<int>> getAllValuesCallsStar();

    int getSizeCalledByStar();
    bool hasKeyCalledByStar(int procedureIndex);
    std::vector<int> getAllKeysCalledByStar();
    std::vector<std::unordered_set<int>> getAllValuesCalledByStar();

    void clearAll();
};

