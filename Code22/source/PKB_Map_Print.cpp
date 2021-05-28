#include "PKB_Map_Print.h"

PKB_Map_Print::PKB_Map_Print() {}

void PKB_Map_Print::insertPrint(int lineNumber, std::string varName) {
    PKB_Map_Integer_String::insertThing(lineNumber, varName, printTable);
}

std::string PKB_Map_Print::getPrint(int lineNumber) {
   return PKB_Map_Integer_String::getThing(lineNumber, printTable);
}

std::unordered_set<int> PKB_Map_Print::getPrintKeys(std::string varName) {
    return PKB_Map_Integer_String::getTableKeys(varName, printTable);
}

int PKB_Map_Print::getSizePrint() {
    return getSize(printTable);
}

bool PKB_Map_Print::hasKeyPrint(int lineNumber) {
    return hasKey(lineNumber, printTable);
}

std::vector<int> PKB_Map_Print::getAllKeysPrint() {
    return getAllKeys(printTable);
}

std::vector<std::string> PKB_Map_Print::getAllValuesPrint() {
    return getAllValues(printTable);
}

void PKB_Map_Print::clearAll() {
    PKB_Map_Integer_String::clear(printTable);
}