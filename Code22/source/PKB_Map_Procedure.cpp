#include "PKB_Map_Procedure.h"

PKB_Map_Procedure::PKB_Map_Procedure() {}

void PKB_Map_Procedure::insertProcedure(std::string procName) {

    std::unordered_map<int, std::string>::const_iterator table_iterator = procedureTable.begin();
    bool toAdd = true;

    while (table_iterator != procedureTable.end()) {
        if (table_iterator->second == procName) {
            toAdd = false;
        }

        table_iterator++;
    }
    int tableSize = procedureTable.size();
    if (toAdd == true) {
        PKB_Map_Integer_String::insertThing(tableSize, procName, procedureTable);
    }
}

std::string PKB_Map_Procedure::getProcedure(int procIndex) {
    return PKB_Map_Integer_String::getThing(procIndex, procedureTable);
}

int PKB_Map_Procedure::getSizeProcedure() {
    return getSize(procedureTable);
}

bool PKB_Map_Procedure::hasKeyProcedure(int procIndex) {
    return hasKey(procIndex, procedureTable);
}

std::vector<int> PKB_Map_Procedure::getAllKeysProcedure() {
    return getAllKeys(procedureTable);
}

std::vector<std::string> PKB_Map_Procedure::getAllValuesProcedure() {
    return getAllValues(procedureTable);
}

void PKB_Map_Procedure::clearAll() {
    PKB_Map_Integer_String::clear(procedureTable);
}
