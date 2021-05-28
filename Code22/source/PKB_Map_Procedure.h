#pragma once

#include "PKB_Map_Integer_String.h"

class PKB_Map_Procedure :
    public PKB_Map_Integer_String
{
protected:
    std::unordered_map<int, std::string> procedureTable;
public:
    PKB_Map_Procedure();

    void insertProcedure(std::string procName);
    std::string getProcedure(int procIndex);

    int getSizeProcedure();
    bool hasKeyProcedure(int procIndex);
    std::vector<int> getAllKeysProcedure();
    std::vector<std::string> getAllValuesProcedure();

    void clearAll();
};
