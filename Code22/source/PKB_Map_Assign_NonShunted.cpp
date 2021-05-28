#include "PKB_Map_Assign_NonShunted.h"

PKB_Map_Assign_NonShunted::PKB_Map_Assign_NonShunted() {}

void PKB_Map_Assign_NonShunted::insertAssign(int lineNumber, std::string assignStmt) {
    PKB_Map_Integer_String::insertThing(lineNumber, assignStmt, assignNonShuntedTable);
}

std::string PKB_Map_Assign_NonShunted::getAssign(int lineNumber) {
    return PKB_Map_Integer_String::getThing(lineNumber, assignNonShuntedTable);
}

int PKB_Map_Assign_NonShunted::getSizeAssign() {
    return getSize(assignNonShuntedTable);
}

bool PKB_Map_Assign_NonShunted::hasKeyAssign(int lineNumber) {
    return hasKey(lineNumber, assignNonShuntedTable);
}

std::vector<int> PKB_Map_Assign_NonShunted::getAllKeysAssign() {
    return getAllKeys(assignNonShuntedTable);
}

std::vector<std::string> PKB_Map_Assign_NonShunted::getAllValuesAssign() {
    return getAllValues(assignNonShuntedTable);
}

void PKB_Map_Assign_NonShunted::clearAll() {
    PKB_Map_Integer_String::clear(assignNonShuntedTable);
}
