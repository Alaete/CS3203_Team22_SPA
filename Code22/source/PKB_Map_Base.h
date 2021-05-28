#pragma once

#include "PKB_Util.h"

#include <unordered_map>
#include <vector>

template <typename K, typename V>

class PKB_Map_Base {
protected:
    PKB_Map_Base() {}

    static int getSize(std::unordered_map<K, V> table) {
        return table.size();
    }
    static bool hasKey(K key, std::unordered_map<K, V> table) {
        return table.count(key);
    }
    static std::vector<K> getAllKeys(std::unordered_map<K, V> table) {
        std::vector<K> keys;
        for (auto const& element : table) {
            keys.push_back(element.first);
        }
        return keys;
    }
    static std::vector<V> getAllValues(std::unordered_map<K, V> table) {
        std::vector<V> values;
        for (auto const& element : table) {
            values.push_back(element.second);
        }
        return values;
    }
    static void clear(std::unordered_map<K, V>& table) {
        table.clear();
    }

    virtual void insertThing(K key, V value, std::unordered_map<K, V>& table) = 0;
    virtual V getThing(K key, std::unordered_map<K, V> table) = 0;
};