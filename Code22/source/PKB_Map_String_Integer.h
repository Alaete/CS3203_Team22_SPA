#pragma once

#include "PKB_Map_Base.h"

#include <string>
#include <stdexcept>

class PKB_Map_String_Integer : 
    public PKB_Map_Base<std::string, int> 
{
public:
    struct SyntaxErrorException : public std::exception {
        std::string errorMessage;
        SyntaxErrorException(std::string error) : errorMessage(error) {}
        ~SyntaxErrorException() throw () {}
        const char* what() const throw () {return errorMessage.c_str();}
    };
protected:
    PKB_Map_String_Integer();

    void insertThing(std::string constant, int value, std::unordered_map<std::string, int> &table);
    int getThing(std::string constant, std::unordered_map<std::string, int> &table);
};
