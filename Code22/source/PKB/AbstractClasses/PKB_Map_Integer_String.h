#pragma once

#include "PKB_Map_Base.h"

#include <unordered_set>
#include <string>

class PKB_Map_Integer_String :
    public PKB_Map_Base<int, std::string> {
protected:
    PKB_Map_Integer_String() {};

    void insertThing(int key, std::string value, std::unordered_map<int, std::string>& table) {
        if (table.count(key) == 0) {
            table[key] = value;
        }
    }

    void updateThing(int key, std::string value, std::unordered_map<int, std::string>& table) {
        if (table.count(key) != 0) {
            table[key] += value;
        }
    }

    std::string getThing(int key, std::unordered_map<int, std::string> table) {
        std::unordered_map<int, std::string>::const_iterator thing_iterator = table.find(key);
        if (thing_iterator != table.end()) {
            return thing_iterator->second;
        }
        else {
            return "";
        }
    }

    bool isThing(int key, std::string value, std::unordered_map<int, std::string> table) {
        if (table.find(key) != table.end()) {
            return table[key] == value;
        }
        else {
            return false;
        }
    }
};

