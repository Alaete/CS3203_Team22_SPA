#include "PKB_Map_Call.h"

PKB_Map_Call::PKB_Map_Call() {}

void PKB_Map_Call::insertCall(int lineNumber, std::string procName) {
    PKB_Map_Integer_String::insertThing(lineNumber, procName, callTable);
}

std::string PKB_Map_Call::getCall(int lineNumber) {
    return PKB_Map_Integer_String::getThing(lineNumber, callTable);
}

std::unordered_set<int> PKB_Map_Call::getCallKeys(std::string procName) {
    return PKB_Map_Integer_String::getTableKeys(procName, callTable);
}

int PKB_Map_Call::getSizeCall() {
    return getSize(callTable);
}

bool PKB_Map_Call::hasKeyCall(int lineNumber) {
    return hasKey(lineNumber, callTable);
}

std::vector<int> PKB_Map_Call::getAllKeysCall() {
    return getAllKeys(callTable);
}

std::vector<std::string> PKB_Map_Call::getAllValuesCall() {
    return getAllValues(callTable);
}

void PKB_Map_Call::clearAll() {
    PKB_Map_Integer_String::clear(callTable);
}