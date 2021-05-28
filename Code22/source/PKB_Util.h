#pragma once

#include <sstream>

class PKB_Util
{
public:
    static std::string duplicateEntryError(int index) {
        std::stringstream err;
        err << "Entry already exists at lineNumber " << index << "!";
        return err.str();
    }
    static std::string noEntryError(int index) {
        std::stringstream err;
        err << "No entry exists at lineNumber " << index << "!";
        return err.str();
    }
    static std::string noIfWhileEntryError(int index) {
        std::stringstream err;
        err << "No if or while table entry exists at lineNumber " << index << "!";
        return err.str();
    }
};