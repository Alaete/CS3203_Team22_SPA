#include "PKB_Map_Node.h"

PKB_Map_Node::PKB_Map_Node() {}

void PKB_Map_Node::insertNode(int nodeNumber, int lineNumber) {
    if (PKB_Map_Integer_Integer::getThing(nodeNumber, nodeTable) == -1) {
        PKB_Map_Integer_Integer::insertThing(nodeNumber, lineNumber, nodeTable);
    }
    else {
        throw PKB_Util::duplicateEntryError(nodeNumber);
    }

    PKB_Map_Node::insertNodeReverse(lineNumber, nodeNumber);
}
int PKB_Map_Node::getNode(int nodeNumber) {
    return PKB_Map_Integer_Integer::getThing(nodeNumber, nodeTable);
}
bool PKB_Map_Node::isNode(int nodeNumber, int lineNumber) {
    return PKB_Map_Integer_Integer::isThing(nodeNumber, lineNumber, nodeTable);
}

void PKB_Map_Node::insertNodeReverse(int lineNumber, int nodeNumber) {
    PKB_Map_Integer_SetInteger::insertThing(lineNumber, { nodeNumber }, nodeReverseTable);
}
std::unordered_set<int> PKB_Map_Node::getNodeReverse(int lineNumber) {
    return PKB_Map_Integer_SetInteger::getThing(lineNumber, nodeReverseTable);
}
bool PKB_Map_Node::isNodeReverse(int lineNumber, int nodeNumber) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, nodeNumber, nodeReverseTable);
}
bool PKB_Map_Node::isNodeReverse(int lineNumber, std::unordered_set<int> nodeNumbers) {
    return PKB_Map_Integer_SetInteger::isThing(lineNumber, nodeNumbers, nodeReverseTable);
}

int PKB_Map_Node::getSizeNode() {
    return PKB_Map_Integer_Integer::getSize(nodeTable);
}
bool PKB_Map_Node::hasKeyNode(int nodeNumber) {
    return PKB_Map_Integer_Integer::hasKey(nodeNumber, nodeTable);
}
std::vector<int> PKB_Map_Node::getAllKeysNode() {
    return PKB_Map_Integer_Integer::getAllKeys(nodeTable);
}
std::vector<int> PKB_Map_Node::getAllValuesNode() {
    return PKB_Map_Integer_Integer::getAllValues(nodeTable);
}

int PKB_Map_Node::getSizeNodeReverse() {
    return PKB_Map_Integer_SetInteger::getSize(nodeReverseTable);
}
bool PKB_Map_Node::hasKeyNodeReverse(int lineNumber) {
    return PKB_Map_Integer_SetInteger::hasKey(lineNumber, nodeReverseTable);
}
std::vector<int> PKB_Map_Node::getAllKeysNodeReverse() {
    return PKB_Map_Integer_SetInteger::getAllKeys(nodeReverseTable);
}
std::vector<std::unordered_set<int>> PKB_Map_Node::getAllValuesNodeReverse() {
    return PKB_Map_Integer_SetInteger::getAllValues(nodeReverseTable);
}

void PKB_Map_Node::clear() {
    PKB_Map_Integer_Integer::clear(nodeTable);
    PKB_Map_Integer_SetInteger::clear(nodeReverseTable);
}

