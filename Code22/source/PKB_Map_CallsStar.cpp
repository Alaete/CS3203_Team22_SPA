#include "PKB_Map_CallsStar.h"

PKB_Map_CallsStar::PKB_Map_CallsStar() {}

void PKB_Map_CallsStar::insertCallsStar(int procedureIndex, std::unordered_set<int> calledProcedures) {
    PKB_Map_Integer_SetInteger::insertThing(procedureIndex, calledProcedures, callsStarTable);

    for (int element : calledProcedures) {
        PKB_Map_CallsStar::insertCalledByStar(element, { procedureIndex });
    }
}
std::unordered_set<int> PKB_Map_CallsStar::getCallsStar(int procedureIndex) {
    return PKB_Map_Integer_SetInteger::getThing(procedureIndex, callsStarTable);
}
bool PKB_Map_CallsStar::isCallsStar(int procedureIndex, int calledProcedure) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, calledProcedure, callsStarTable);
}
bool PKB_Map_CallsStar::isCallsStar(int procedureIndex, std::unordered_set<int> calledProcedures) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, calledProcedures, callsStarTable);
}

void PKB_Map_CallsStar::insertCalledByStar(int procedureIndex, std::unordered_set<int> calledByProcedures) {
    PKB_Map_Integer_SetInteger::insertThing(procedureIndex, calledByProcedures, calledByStarTable);
}
std::unordered_set<int> PKB_Map_CallsStar::getCalledByStar(int procedureIndex) {
    return PKB_Map_Integer_SetInteger::getThing(procedureIndex, calledByStarTable);
}
bool PKB_Map_CallsStar::isCalledByStar(int procedureIndex, int calledByProcedure) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, calledByProcedure, calledByStarTable);
}
bool PKB_Map_CallsStar::isCalledByStar(int procedureIndex, std::unordered_set<int> calledByProcedures) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, calledByProcedures, calledByStarTable);
}

int PKB_Map_CallsStar::getSizeCallsStar() {
    return getSize(callsStarTable);
}
bool PKB_Map_CallsStar::hasKeyCallsStar(int procedureIndex) {
    return hasKey(procedureIndex, callsStarTable);
}
std::vector<int> PKB_Map_CallsStar::getAllKeysCallsStar() {
    return getAllKeys(callsStarTable);
}
std::vector<std::unordered_set<int>> PKB_Map_CallsStar::getAllValuesCallsStar() {
    return getAllValues(callsStarTable);
}

int PKB_Map_CallsStar::getSizeCalledByStar() {
    return getSize(calledByStarTable);
}
bool PKB_Map_CallsStar::hasKeyCalledByStar(int procedureIndex) {
    return hasKey(procedureIndex, calledByStarTable);
}
std::vector<int> PKB_Map_CallsStar::getAllKeysCalledByStar() {
    return getAllKeys(calledByStarTable);
}
std::vector<std::unordered_set<int>> PKB_Map_CallsStar::getAllValuesCalledByStar() {
    return getAllValues(calledByStarTable);
}

void PKB_Map_CallsStar::clearAll() {
    PKB_Map_Integer_SetInteger::clear(callsStarTable);
    PKB_Map_Integer_SetInteger::clear(calledByStarTable);
}

