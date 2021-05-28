#include "PKB_Map_Constant.h"

PKB_Map_Constant::PKB_Map_Constant() {}

void PKB_Map_Constant::insertConstant(int lineNumber, std::unordered_set<int> constantValues) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, constantValues, constantTable);
}

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
    return PKB_Map_Integer_SetInteger::getSize(constantTable);
}

bool PKB_Map_Constant::hasKeyConstant(int lineNumber) {
    return PKB_Map_Integer_SetInteger::hasKey(lineNumber, constantTable);
}

std::vector<int> PKB_Map_Constant::getAllKeysConstant() {
    return PKB_Map_Integer_SetInteger::getAllKeys(constantTable);
}

std::vector<std::unordered_set<int>> PKB_Map_Constant::getAllValuesConstant() {
    return PKB_Map_Integer_SetInteger::getAllValues(constantTable);
}

void PKB_Map_Constant::clear() {
    PKB_Map_Integer_SetInteger::clear(constantTable);
}

