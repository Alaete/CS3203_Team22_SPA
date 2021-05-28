#include "PKB_Map_String_Integer.h"

PKB_Map_String_Integer::PKB_Map_String_Integer() {}

void PKB_Map_String_Integer::insertThing(std::string constant, int value, std::unordered_map<std::string, int> &table) {
    table[constant] = value;
}

int PKB_Map_String_Integer::getThing(std::string constant, std::unordered_map<std::string, int> &table) {
    std::unordered_map<std::string, int>::const_iterator thing_iterator = table.find(constant);
    if (thing_iterator != table.end()) {
        return thing_iterator->second;
    }
    else {
        throw SyntaxErrorException("Item could not be found");
    }
}