#include "PKB_Map_Integer_String.h"

PKB_Map_Integer_String::PKB_Map_Integer_String() {};

void PKB_Map_Integer_String::insertThing(int key, std::string value, std::unordered_map<int, std::string> &table) {
    if (table.count(key) == 0) {
        table[key] = value;
    }
}

void PKB_Map_Integer_String::updateThing(int key, std::string value, std::unordered_map<int, std::string>& table) {
    if (table.count(key) != 0) {
        table[key] += value;
    }
}

std::string PKB_Map_Integer_String::getThing(int key, std::unordered_map<int, std::string> table) {
    std::unordered_map<int, std::string>::const_iterator thing_iterator = table.find(key);
    if (thing_iterator != table.end()) {
        return thing_iterator->second;
    }
    else {
        return "";
    }
}

//Returns true if key is an existing key in table with the given value. Else returns false
bool PKB_Map_Integer_String::isTableType(int key, std::string value, std::unordered_map<int, std::string>& table) {
    std::unordered_map<int, std::string>::const_iterator found_iterator = table.find(key);

    if (found_iterator != table.end()) {
        if (found_iterator->second == value) {
            return true;
        }

    }
    return false;
}

//Returns a set of keys that contain the same value
std::unordered_set<int> PKB_Map_Integer_String::getTableKeys(std::string value, std::unordered_map<int, std::string>& table) {
    std::unordered_set<int> results;

    for (auto it = table.begin(); it != table.end(); ++it) {
        if (it->second == value) {
            results.insert(it->first);
        }
    }
    return results;
}
