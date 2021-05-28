#pragma once

#include "PKB_Map_Any_SetAny.h"

class PKB_Map_String_SetInteger :
    public PKB_Map_Any_SetAny<std::string, int> {
protected:
    PKB_Map_String_SetInteger() {}
};

