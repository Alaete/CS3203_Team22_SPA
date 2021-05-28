#pragma once

#include "PKB_Map_Base.h"

#include <unordered_set>

template <typename K, typename V>

class PKB_Map_Any_SetAny :
    public PKB_Map_Base<K, std::unordered_set<V>> {
private:
    int area = -1;
protected:
    PKB_Map_Any_SetAny() {}

    void insertThing(K key, std::unordered_set<V> values, std::unordered_map<K, std::unordered_set<V>>& table) {
        if (table.count(key) == 0) {
            table[key] = values;
        }
        else {
            auto pos = table[key].begin();
            for (auto it = values.begin(); it != values.end(); ++it) {
                pos = table[key].insert(pos, *it);
            }
        }
        area = -1;
    }

    std::unordered_set<V> getThing(K key, std::unordered_map<K, std::unordered_set<V>> table) {
        std::unordered_map<K, std::unordered_set<V>>::const_iterator thing_iterator = table.find(key);
        if (thing_iterator != table.end()) {
            return thing_iterator->second;
        }
        else {
            return {};
        }
    }

    bool isThing(K key, V value, std::unordered_map<K, std::unordered_set<V>> table) {
        return table[key].count(value);
    }

    bool isThing(K key, std::unordered_set<V> values, std::unordered_map<K, std::unordered_set<V>> table) {
        for (V value : values) {
            if (!table[key].count(value)) {
                return false;
            }
        }
        return true;
    }

    int getArea(std::unordered_map<K, std::unordered_set<V>> table) {
        if (area == -1) {
            int tempArea = 0;
            for (auto rhs : table) {
                tempArea += rhs.second.size();
            }

            area = tempArea;
        }
        return area;
    }
};

