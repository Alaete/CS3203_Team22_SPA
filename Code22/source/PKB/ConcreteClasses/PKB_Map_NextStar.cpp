#include "PKB_Map_NextStar.h"

PKB_Map_NextStar::PKB_Map_NextStar() {}

void PKB_Map_NextStar::insertNextStar(int key, std::unordered_set<int> values){
    PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingNoReverse(key, values);
}
std::unordered_set<int> PKB_Map_NextStar::getNextStar(int key){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getThing(key);
}
bool PKB_Map_NextStar::isNextStar(int key, int value){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThing(key, value);
}
bool PKB_Map_NextStar::isNextStar(int key, std::unordered_set<int> values){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThing(key, values);
}

void PKB_Map_NextStar::insertPreviousStar(int key, std::unordered_set<int> values) {
    PKB_Map_AAstarCCstarFstarNNstarPstar::insertThingReverse(key, values);
}
std::unordered_set<int> PKB_Map_NextStar::getPreviousStar(int key){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getThingReverse(key);
}
bool PKB_Map_NextStar::isPreviousStar(int key, int reverseValue){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThingReverse(key, reverseValue);
}
bool PKB_Map_NextStar::isPreviousStar(int key, std::unordered_set<int> reverseValues){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::isThingReverse(key, reverseValues);
}

int PKB_Map_NextStar::getSizeNextStar(){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getSize();
}
int PKB_Map_NextStar::getAreaNextStar() {
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getArea();
}
bool PKB_Map_NextStar::hasKeyNextStar(int key){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::hasKey(key);
}
std::vector<int> PKB_Map_NextStar::getAllKeysNextStar(){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getAllKeys();
}
std::vector<std::unordered_set<int>> PKB_Map_NextStar::getAllValuesNextStar(){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getAllValues();
}

int PKB_Map_NextStar::getSizePreviousStar(){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getSizeReverse();
}
bool PKB_Map_NextStar::hasKeyPreviousStar(int key){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::hasKeyReverse(key);
}
std::vector<int> PKB_Map_NextStar::getAllKeysPreviousStar(){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB_Map_NextStar::getAllValuesPreviousStar(){
    return PKB_Map_AAstarCCstarFstarNNstarPstar::getAllValuesReverse();
}