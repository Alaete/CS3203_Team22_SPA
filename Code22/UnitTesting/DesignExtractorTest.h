#pragma once

#include "SimulatedPKB.h"
#include "DesignExtractorBase.h"

class DesignExtractorTest : 
	public DesignExtractorBase<SimulatedPKB> {
private:
    DesignExtractorTest() {};
};