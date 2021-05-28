#include "PKB_Map_AAstarCCstarFstarNNstarPstar.h"

PKB_Map_AAstarCCstarFstarNNstarPstar::PKB_Map_AAstarCCstarFstarNNstarPstar() {}

void PKB_Map_AAstarCCstarFstarNNstarPstar::insertThing(int procedureIndex, std::unordered_set<int> values) {
    PKB_Map_Integer_SetInteger::insertThing(procedureIndex, values, table);

    for (int element : values) {
        PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingReverse(element, { procedureIndex });
    }
}
void PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingNoReverse(int procedureIndex, std::unordered_set<int> values) {
    PKB_Map_Integer_SetInteger::insertThing(procedureIndex, values, table);
}
std::unordered_set<int> PKB_Map_AAstarCCstarFstarNNstarPstar::getThing(int procedureIndex) {
    return PKB_Map_Integer_SetInteger::getThing(procedureIndex, table);
}
bool PKB_Map_AAstarCCstarFstarNNstarPstar::isThing(int procedureIndex, int value) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, value, table);
}
bool PKB_Map_AAstarCCstarFstarNNstarPstar::isThing(int procedureIndex, std::unordered_set<int> values) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, values, table);
}

void PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingReverse(int procedureIndex, std::unordered_set<int> reverseValues) {
    PKB_Map_Integer_SetInteger::insertThing(procedureIndex, reverseValues, reverseTable);
}
std::unordered_set<int> PKB_Map_AAstarCCstarFstarNNstarPstar::getThingReverse(int procedureIndex) {
    return PKB_Map_Integer_SetInteger::getThing(procedureIndex, reverseTable);
}
bool PKB_Map_AAstarCCstarFstarNNstarPstar::isThingReverse(int procedureIndex, int reverseValue) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, reverseValue, reverseTable);
}
bool PKB_Map_AAstarCCstarFstarNNstarPstar::isThingReverse(int procedureIndex, std::unordered_set<int> reverseValues) {
    return PKB_Map_Integer_SetInteger::isThing(procedureIndex, reverseValues, reverseTable);
}

int PKB_Map_AAstarCCstarFstarNNstarPstar::getSize() {
    return PKB_Map_Integer_SetInteger::getSize(table);
}
int PKB_Map_AAstarCCstarFstarNNstarPstar::getArea() {
    return PKB_Map_Integer_SetInteger::getArea(table);
}
bool PKB_Map_AAstarCCstarFstarNNstarPstar::hasKey(int procedureIndex) {
    return PKB_Map_Integer_SetInteger::hasKey(procedureIndex, table);
}
std::vector<int> PKB_Map_AAstarCCstarFstarNNstarPstar::getAllKeys() {
    return PKB_Map_Integer_SetInteger::getAllKeys(table);
}
std::vector<std::unordered_set<int>> PKB_Map_AAstarCCstarFstarNNstarPstar::getAllValues() {
    return PKB_Map_Integer_SetInteger::getAllValues(table);
}

int PKB_Map_AAstarCCstarFstarNNstarPstar::getSizeReverse() {
    return PKB_Map_Integer_SetInteger::getSize(reverseTable);
}
bool PKB_Map_AAstarCCstarFstarNNstarPstar::hasKeyReverse(int procedureIndex) {
    return PKB_Map_Integer_SetInteger::hasKey(procedureIndex, reverseTable);
}
std::vector<int> PKB_Map_AAstarCCstarFstarNNstarPstar::getAllKeysReverse() {
    return PKB_Map_Integer_SetInteger::getAllKeys(reverseTable);
}
std::vector<std::unordered_set<int>> PKB_Map_AAstarCCstarFstarNNstarPstar::getAllValuesReverse() {
    return PKB_Map_Integer_SetInteger::getAllValues(reverseTable);
}

void PKB_Map_AAstarCCstarFstarNNstarPstar::clear() {
    PKB_Map_Integer_SetInteger::clear(table);
    PKB_Map_Integer_SetInteger::clear(reverseTable);
}

