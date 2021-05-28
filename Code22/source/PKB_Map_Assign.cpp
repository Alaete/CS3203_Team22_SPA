#include "PKB_Map_Assign.h"

PKB_Map_Assign::PKB_Map_Assign() {}

void PKB_Map_Assign::insertAssignLHS(int lineNumber, std::string variableLHS) {
    if (!PKB_Map_Assign::hasKeyAssign(lineNumber)) {
        PKB_Map_Integer_PairStringString::insertThing(lineNumber, { variableLHS, ""}, assignTable);
    }
    else {
        throw PKB_Util::duplicateEntryError(lineNumber);
    }
}

void PKB_Map_Assign::insertAssignRHS(int lineNumber, std::string shuntedRHS) {
    if (PKB_Map_Assign::hasKeyAssign(lineNumber)) {
        PKB_Map_Integer_PairStringString::updateThingSecond(lineNumber, shuntedRHS, assignTable);
    }
    else {
        throw PKB_Util::noEntryError(lineNumber);
    }
}

std::pair<std::string, std::string> PKB_Map_Assign::getAssign(int lineNumber) {
    return PKB_Map_Integer_PairStringString::getThing(lineNumber, assignTable);
}

int PKB_Map_Assign::getSizeAssign() {
    return PKB_Map_Integer_PairStringString::getSize(assignTable);
}
bool PKB_Map_Assign::hasKeyAssign(int lineNumber) {
    return PKB_Map_Integer_PairStringString::hasKey(lineNumber, assignTable);
}
std::vector<int> PKB_Map_Assign::getAllKeysAssign() {
    return PKB_Map_Integer_PairStringString::getAllKeys(assignTable);
}
std::vector<std::pair<std::string, std::string>> PKB_Map_Assign::getAllValuesAssign() {
    return PKB_Map_Integer_PairStringString::getAllValues(assignTable);
}
void PKB_Map_Assign::clearAll() {
    PKB_Map_Integer_PairStringString::clear(assignTable);
}