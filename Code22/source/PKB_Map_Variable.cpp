#include "PKB_Map_Variable.h"

PKB_Map_Variable::PKB_Map_Variable() {}

int PKB_Map_Variable::insertVariable(std::string varName) {
    
    std::unordered_map<int, std::string>::const_iterator table_iterator = variableTable.begin();
    
    while (table_iterator != variableTable.end()) {
        if (table_iterator->second == varName) {
            return table_iterator->first;
        }

        table_iterator++;
    }
    int tableSize = variableTable.size();
    PKB_Map_Integer_String::insertThing(tableSize, varName, variableTable);
    return variableTable.size() - 1;
}

std::string PKB_Map_Variable::getVariable(int index) {
    return PKB_Map_Integer_String::getThing(index, variableTable);
}

int PKB_Map_Variable::getVariableKey(std::string varName) {

    std::unordered_set<int> results = PKB_Map_Integer_String::getTableKeys(varName, variableTable);

    if (results.empty() == true) {
        return -1;
    }
    else {
        return *results.begin();
    }

}

int PKB_Map_Variable::getSizeVariable() {
    return getSize(variableTable);
}

bool PKB_Map_Variable::hasKeyVariable(int key) {
    return hasKey(key, variableTable);
}

std::vector<int> PKB_Map_Variable::getAllKeysVariable() {
    return getAllKeys(variableTable);
}

std::vector<std::string> PKB_Map_Variable::getAllValuesVariable() {
    return getAllValues(variableTable);
}

void PKB_Map_Variable::clearAll() {
    PKB_Map_Integer_String::clear(variableTable);
}