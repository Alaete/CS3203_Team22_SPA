#include "PKB_Map_Calls.h"

PKB_Map_Calls::PKB_Map_Calls() {}

void PKB_Map_Calls::insertCalls(int procedureIndex, std::unordered_set<int> calledProcedures) {
    PKB_Map_Integer_SetInteger::insertThing(procedureIndex, calledProcedures, callsTable);

    for (int element : calledProcedures) {
        PKB_Map_Calls::insertCalledBy(element, { procedureIndex });
    }
}
std::unordered_set<int> PKB_Map_Calls::getCalls(int procedureIndex) {
    return PKB_Map_Integer_SetInteger::getThing(procedureIndex, callsTable);
}
bool PKB_Map_Calls::isCalls(int procedureIndex, int calledProcedure) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, calledProcedure, callsTable);
}
bool PKB_Map_Calls::isCalls(int procedureIndex, std::unordered_set<int> calledProcedures) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, calledProcedures, callsTable);
}

void PKB_Map_Calls::insertCalledBy(int procedureIndex, std::unordered_set<int> calledByProcedures) {
    PKB_Map_Integer_SetInteger::insertThing(procedureIndex, calledByProcedures, calledByTable);
}
std::unordered_set<int> PKB_Map_Calls::getCalledBy(int procedureIndex) {
    return PKB_Map_Integer_SetInteger::getThing(procedureIndex, calledByTable);
}
bool PKB_Map_Calls::isCalledBy(int procedureIndex, int calledByProcedure) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, calledByProcedure, calledByTable);
}
bool PKB_Map_Calls::isCalledBy(int procedureIndex, std::unordered_set<int> calledByProcedures) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, calledByProcedures, calledByTable);
}

int PKB_Map_Calls::getSizeCalls() {
    return getSize(callsTable);
}
bool PKB_Map_Calls::hasKeyCalls(int procedureIndex) {
    return hasKey(procedureIndex, callsTable);
}
std::vector<int> PKB_Map_Calls::getAllKeysCalls() {
    return getAllKeys(callsTable);
}
std::vector<std::unordered_set<int>> PKB_Map_Calls::getAllValuesCalls() {
    return getAllValues(callsTable);
}

int PKB_Map_Calls::getSizeCalledBy() {
    return getSize(calledByTable);
}
bool PKB_Map_Calls::hasKeyCalledBy(int procedureIndex) {
    return hasKey(procedureIndex, calledByTable);
}
std::vector<int> PKB_Map_Calls::getAllKeysCalledBy() {
    return getAllKeys(calledByTable);
}
std::vector<std::unordered_set<int>> PKB_Map_Calls::getAllValuesCalledBy() {
    return getAllValues(calledByTable);
}

void PKB_Map_Calls::clearAll() {
    PKB_Map_Integer_SetInteger::clear(callsTable);
    PKB_Map_Integer_SetInteger::clear(calledByTable);
}

