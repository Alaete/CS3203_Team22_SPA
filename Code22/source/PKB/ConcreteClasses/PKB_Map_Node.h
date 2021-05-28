#pragma once

#include "../AbstractClasses/PKB_Map_Integer_Integer.h"
#include "../AbstractClasses/PKB_Map_Integer_SetInteger.h"

class PKB_Map_Node :
    public PKB_Map_Integer_Integer,
    public PKB_Map_Integer_SetInteger {
private:
    std::unordered_map<int, int> nodeTable;
    std::unordered_map<int, std::unordered_set<int>> nodeReverseTable;
    void insertNodeReverse(int lineNumber, int nodeNumber);
public:
    PKB_Map_Node();

    void insertNode(int nodeNumber, int lineNumber);
    int getNode(int nodeNumber);
    bool isNode(int nodeNumber, int lineNumber);

    std::unordered_set<int> getNodeReverse(int lineNumber);
    bool isNodeReverse(int lineNumber, int nodeNumber);
    bool isNodeReverse(int lineNumber, std::unordered_set<int> nodeNumbers);

    int getSizeNode();
    bool hasKeyNode(int nodeNumber);
    std::vector<int> getAllKeysNode();
    std::vector<int> getAllValuesNode();

    int getSizeNodeReverse();
    bool hasKeyNodeReverse(int lineNumber);
    std::vector<int> getAllKeysNodeReverse();
    std::vector<std::unordered_set<int>> getAllValuesNodeReverse();

    void clear();
};

