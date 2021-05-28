#ifndef TESTWRAPPER_H
#define TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>

// include your other headers here
#include "AbstractWrapper.h"
#include "Parser.h"
#include "DesignExtractor.h"
#include "PKB/PKB.h"
#include "QueryPreprocessor/Query.h"
#include "QueryPreprocessor/QueryParser.h"
#include "QueryEvaluator/QueryEvaluator.h"
#include "QueryEvaluator/QueryPKBInterface.h"

class TestWrapper : public AbstractWrapper {
private: 
	Query qr;
 public:
  // default constructor
  TestWrapper();
  
  // destructor
  ~TestWrapper();
  
  // method for parsing the SIMPLE source
  virtual void parse(std::string filename);
  
  // method for evaluating a query
  virtual void evaluate(std::string query, std::list<std::string>& results);
};

#endif
