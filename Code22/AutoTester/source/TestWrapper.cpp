#include "TestWrapper.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
    // call your parser to do the parsing
    // ...rest of your code...s
   
    bool isExtension = true; // Set this to true/false to enable/disable extractions for extensions.
    Parser::getInstance().parseProgram(filename);
    DesignExtractor::getInstance().extractAllDesigns();
    if (isExtension) {
        DesignExtractor::getInstance().extractExtensions();
    }
    PKB::getInstance().precompute();
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
    QueryEvaluator::getInstance().isOptimize = true; //Set this to false to disable optimizations. Set this to true to enable optimizations
    Query pq;
    try {
		pq = QueryParser::getInstance().parseQuery(query);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
    results = QueryEvaluator::getInstance().solveQuery(pq);

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
