#include "CppUnitTest.h"
#include "stdafx.h"
#include <string>
#include <iostream>
#include <list>

// include your other headers here
#include "../source/Parser.h"
#include "../source/QueryPreprocessor/Query.h"
#include "../source/QueryPreprocessor/QueryParser.h"
#include "../source/QueryEvaluator/QueryEvaluator.h"
#include "../source/QueryEvaluator/QueryPKBInterface.h"
#include "../source/PKB/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting {
    
    TEST_CLASS(TESTPQL){
        public:
            TEST_METHOD(TEST_PREPROCESSOR_AND_EVALUATOR_BOOLEAN) {
                std::string query = "stmt s; Select BOOLEAN such that Follows(s, s)";
                Query result = QueryParser::getInstance().parseQuery(query);
                Assert::IsTrue(result.getIsValid() &&
                    result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::FOLLOWS &&
                    result.getClauses().at(0).leftRef.refString == "s" &&
                    result.getClauses().at(0).rightRef.refString == "s" &&
                    result.getIsSelectBoolean());

                std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(result);
                std::list<std::string>::iterator it;
                it = std::find(answer.begin(), answer.end(), "TRUE");
                Assert::IsFalse(it != answer.end());
                it = std::find(answer.begin(), answer.end(), "FALSE");
                Assert::IsTrue(it != answer.end());
            }

            TEST_METHOD(TEST_PREPROCESSOR_AND_EVALUATOR_INVALID) {
                std::string query = "assign a; variable v; procedure p; Select v such that Uses(p, p) pattern a (\"v\", _)";
                Query result = QueryParser::getInstance().parseQuery(query);
                Assert::IsTrue(!result.getIsValid());

                std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(result);
                std::list<std::string>::iterator it;
                it = std::find(answer.begin(), answer.end(), "");
                Assert::IsTrue(it == answer.end());
                Assert::IsFalse(it != answer.end());
            }

            TEST_METHOD(TEST_PREPROCESSOR_AND_EVALUATOR_INVALID_1) {
                std::string query = "if ifs; variable v; Select ifs pattern ifs(v, _, kk)";
                Query result = QueryParser::getInstance().parseQuery(query);
                Assert::IsTrue(!result.getIsValid());

                std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(result);
                std::list<std::string>::iterator it;
                it = std::find(answer.begin(), answer.end(), "");
                Assert::IsTrue(it == answer.end());
                Assert::IsFalse(it != answer.end());
            }
            TEST_METHOD(TEST_PQL_AND_PKB) {
                PKB::getInstance().insertRead(2, "var1");
                std::string query = "variable v; read rd; Select rd";
                Query q = QueryParser::getInstance().parseQuery(query);
                Assert::IsTrue(q.getIsValid());

                std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);
                std::list<std::string>::iterator it;
                it = std::find(answer.begin(), answer.end(), "2");
                Assert::IsFalse(it == answer.end());
                Assert::IsTrue(it != answer.end());
                Assert::IsTrue(answer.size() == 1);
            }
            TEST_METHOD(TEST_PQL_AND_PKB_AND_FRONT_END) {}
            

    };
};