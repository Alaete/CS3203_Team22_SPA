#include "PKB_Map_Read.h"

PKB_Map_Read::PKB_Map_Read() {}

void PKB_Map_Read::insertRead(int lineNumber,std::string varName) {
    PKB_Map_Integer_String::insertThing(lineNumber, varName, readTable);
    
}
std::string PKB_Map_Read::getRead(int lineNumber) {
    return PKB_Map_Integer_String::getThing(lineNumber, readTable);
}

std::unordered_set<int> PKB_Map_Read::getReadKeys(std::string varName) {
    return PKB_Map_Integer_String::getTableKeys(varName, readTable);
}

int PKB_Map_Read::getSizeRead() {
    return getSize(readTable);
}
bool PKB_Map_Read::hasKeyRead(int lineNumber) {
    return hasKey(lineNumber, readTable);
}
std::vector<int> PKB_Map_Read::getAllKeysRead() {
    return getAllKeys(readTable);
}
std::vector<std::string> PKB_Map_Read::getAllValuesRead() {
    return getAllValues(readTable);
}

void PKB_Map_Read::clearAll() {
    PKB_Map_Integer_String::clear(readTable);
}