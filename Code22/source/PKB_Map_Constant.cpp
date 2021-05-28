#include "PKB_Map_Constant.h"

PKB_Map_Constant::PKB_Map_Constant() {}

//Insert constant with its corresponding value to constantTable
void PKB_Map_Constant::insertConstant(int lineNumber, std::unordered_set<int> constantValues) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, constantValues, constantTable);
}

//Get the value of the given constant
std::unordered_set<int> PKB_Map_Constant::getConstant(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, constantTable);
}

bool PKB_Map_Constant::isConstant(int lineNumber, std::unordered_set<int> constantValues) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, constantValues, constantTable);
}

bool PKB_Map_Constant::isConstant(int lineNumber, int constantValue) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, constantValue, constantTable);
}

int PKB_Map_Constant::getSizeConstant() {
    return getSize(constantTable);
}

//Searches the constantTable if a key exists 
bool PKB_Map_Constant::hasKeyConstant(int lineNumber) {
    return hasKey(lineNumber, constantTable);
}

std::vector<int> PKB_Map_Constant::getAllKeysConstant() {
    return getAllKeys(constantTable);
}

std::vector<std::unordered_set<int>> PKB_Map_Constant::getAllValuesConstant() {
    return getAllValues(constantTable);
}

void PKB_Map_Constant::clearAll() {
    PKB_Map_Integer_SetInteger::clear(constantTable);
}