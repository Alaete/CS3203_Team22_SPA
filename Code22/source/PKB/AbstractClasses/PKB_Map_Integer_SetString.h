#pragma once

#include "PKB_Map_Any_SetAny.h"

class PKB_Map_Integer_SetString :
    public PKB_Map_Any_SetAny<int, std::string> {
protected:
    PKB_Map_Integer_SetString() {}
};

