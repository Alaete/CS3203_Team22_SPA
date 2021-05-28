#include "stdafx.h"
#include "QueryEvaluatorUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestQueryEvaluator)
    {
    public:

        TEST_METHOD(TEST_GET_SYNONYM_TYPE) {

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "a1" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["a1"] = Query::DesignEntityType::ASSIGN;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::SELECT;
            clauses.push_back(c);
            q.addClauses(clauses);


            QueryEvaluator::getInstance().synTable = synonym_table;
            Query::DesignEntityType det = QueryEvaluator::getInstance().getSynonymType(q.getSelectedSynonyms()[0].synonymString);


            Assert::IsTrue(det == Query::DesignEntityType::ASSIGN);
            Assert::IsFalse(det == Query::DesignEntityType::CALL);
            Assert::IsFalse(det == Query::DesignEntityType::CONSTANT);
            Assert::IsFalse(det == Query::DesignEntityType::IF);
            Assert::IsFalse(det == Query::DesignEntityType::NONE);
            Assert::IsFalse(det == Query::DesignEntityType::PRINT);
            Assert::IsFalse(det == Query::DesignEntityType::PROCEDURE);
            Assert::IsFalse(det == Query::DesignEntityType::READ);
            Assert::IsFalse(det == Query::DesignEntityType::STMT);
            Assert::IsFalse(det == Query::DesignEntityType::WHILE);
            Assert::IsFalse(det == Query::DesignEntityType::WILDCARD);

        }

        TEST_METHOD(TEST_FORMAT_ANSWER) {			

            std::vector<Query::Element> selectedSyn = { {Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "a"} };
            std::unordered_map<std::string, std::unordered_set<std::string>> dummy;

            QueryEvaluator::getInstance().answerTable["a"]["1"] = dummy;
            QueryEvaluator::getInstance().answerTable["a"]["2"] = dummy;
            QueryEvaluator::getInstance().answerTable["a"]["5"] = dummy;
            QueryEvaluator::getInstance().answerTable["a"]["6"] = dummy;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveSelectClause(selectedSyn, true, false);

            std::list<std::string>::iterator it;
            //List contains "1"
            it = std::find(answer.begin(), answer.end(), "1");
            Assert::IsTrue(it != answer.end());
            //List contains "2"
            it = std::find(answer.begin(), answer.end(), "2");
            Assert::IsTrue(it != answer.end());
            //List contains "5"
            it = std::find(answer.begin(), answer.end(), "5");
            Assert::IsTrue(it != answer.end());
            //List contains "6"
            it = std::find(answer.begin(), answer.end(), "6");
            Assert::IsTrue(it != answer.end());
            //List does not contains "3"
            it = std::find(answer.begin(), answer.end(), "3");
            Assert::IsFalse(it != answer.end());

        }

        TEST_METHOD(TEST_CLEAN_REMOVE) {
            std::vector<Query::Element> selectedSyn = { {Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE,"a"} };
            std::unordered_map<std::string, std::unordered_set<std::string>> dummy;

            QueryEvaluator::getInstance().answerTable["a"]["1"] = dummy;
            QueryEvaluator::getInstance().answerTable["a"]["2"] = dummy;
            QueryEvaluator::getInstance().answerTable["a"]["5"]["b"].insert("9");
            QueryEvaluator::getInstance().answerTable["a"]["6"]["b"].insert("9");


            QueryEvaluator::getInstance().answerTableCleanRemove("a", "5", "b", "9");
            QueryEvaluator::getInstance().answerTableCleanRemove("a", "6", "b", "9");

            std::list<std::string> answer = QueryEvaluator::getInstance().solveSelectClause(selectedSyn, true, false);

            std::list<std::string>::iterator it;
            //List contains "1"
            it = std::find(answer.begin(), answer.end(), "1");
            Assert::IsTrue(it != answer.end());
            //List contains "2"
            it = std::find(answer.begin(), answer.end(), "2");
            Assert::IsTrue(it != answer.end());
            //List contains "5"
            it = std::find(answer.begin(), answer.end(), "5");
            Assert::IsFalse(it != answer.end());
            //List contains "6"
            it = std::find(answer.begin(), answer.end(), "6");
            Assert::IsFalse(it != answer.end());
            //List does not contains "3"
            it = std::find(answer.begin(), answer.end(), "3");
            Assert::IsFalse(it != answer.end());

        }

        TEST_METHOD(TEST_SOLVE_WITH_STMTNUM_STMTNUM) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });
            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            synonym_table["s2"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "s.stmt#";
            r2.synonym = "s2";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_STMTNUM_VALUE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });
            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::VALUE;
            r2.refDentityType = Query::DesignEntityType::CONSTANT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "c.value";
            r2.synonym = "c";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VALUE_VALUE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });
            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            synonym_table["c2"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VALUE;
            r.refDentityType = Query::DesignEntityType::CONSTANT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "c.value";
            r.synonym = "c";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::VALUE;
            r2.refDentityType = Query::DesignEntityType::CONSTANT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "c2.value";
            r2.synonym = "c2";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VALUE_STMTNUM) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });
            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VALUE;
            r.refDentityType = Query::DesignEntityType::CONSTANT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "c.value";
            r.synonym = "c";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "s.stmt#";
            r2.synonym = "s";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROCNAME_PROCNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("main");
            PKB::getInstance().insertProcedure("bird");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            synonym_table["p2"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r2.refDentityType = Query::DesignEntityType::PROCEDURE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "p2.procName";
            r2.synonym = "p2";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROCNAME_VARNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("main");
            PKB::getInstance().insertVariable("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r2.refDentityType = Query::DesignEntityType::VARIABLE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "v.varName";
            r2.synonym = "v";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VARNAME_VARNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("main");
            PKB::getInstance().insertVariable("bird");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            synonym_table["v2"] = Query::DesignEntityType::VARIABLE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r2.refDentityType = Query::DesignEntityType::VARIABLE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "v2.varName";
            r2.synonym = "v2";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VARNAME_PROCNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("main");
            PKB::getInstance().insertProcedure("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r2.refDentityType = Query::DesignEntityType::PROCEDURE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "p.procName";
            r2.synonym = "p";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_STMTNUM_STMTNUM_NO_PKB) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            synonym_table["s2"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "s.stmt#";
            r2.synonym = "s2";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_STMTNUM_VARNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");
            PKB::getInstance().insertVariable("Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r2.refDentityType = Query::DesignEntityType::VARIABLE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "v.varName";
            r2.synonym = "v";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_STMTNUM_PROCNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");
            PKB::getInstance().insertProcedure("Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r2.refDentityType = Query::DesignEntityType::PROCEDURE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "p.procName";
            r2.synonym = "p";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VALUE_VARNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });
            PKB::getInstance().insertVariable("Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VALUE;
            r.refDentityType = Query::DesignEntityType::CONSTANT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "c.value";
            r.synonym = "c";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r2.refDentityType = Query::DesignEntityType::VARIABLE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "v.varName";
            r2.synonym = "v";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VALUE_PROCNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });
            PKB::getInstance().insertProcedure("Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VALUE;
            r.refDentityType = Query::DesignEntityType::CONSTANT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "c.value";
            r.synonym = "c";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r2.refDentityType = Query::DesignEntityType::PROCEDURE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "p.procName";
            r2.synonym = "p";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROCNAME_STMTNUM) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("main");
            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "s.stmt#";
            r2.synonym = "s";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROCNAME_VALUE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("main");
            PKB::getInstance().insertConstant(3, { 1 });

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::VALUE;
            r2.refDentityType = Query::DesignEntityType::CONSTANT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "c.value";
            r2.synonym = "c";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VARNAME_STMTNUM) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("main");
            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "s.stmt#";
            r2.synonym = "s";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VARNAME_VALUE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("main");
            PKB::getInstance().insertConstant(3, { 1 });

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.leftRef = r;
            Query::Reference r2;
            r2.refAttribType = Query::ReferenceAttributeType::VALUE;
            r2.refDentityType = Query::DesignEntityType::CONSTANT;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.refString = "c.value";
            r2.synonym = "c";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_STMTNUM_PROGLINE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::INTEGER;
            r.refString = "1";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.leftRef = r2;

            Query::Clause c2;
            c2.clauseType = Query::ClauseType::WITH;
            Query::Reference r3;
            r3.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r3.refDentityType = Query::DesignEntityType::STMT;
            r3.refType = Query::ReferenceType::SYNONYM;
            r3.refString = "s.stmt#";
            r3.synonym = "s";
            c2.leftRef = r3;
            Query::Reference r4;
            r4.refDentityType = Query::DesignEntityType::PROG_LINE;
            r4.refType = Query::ReferenceType::SYNONYM;
            r4.refString = "n";
            c2.rightRef = r4;

            clauses.push_back(c);
            clauses.push_back(c2);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VALUE_PROGLINE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "c" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::INTEGER;
            r.refString = "1";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.leftRef = r2;

            Query::Clause c2;
            c2.clauseType = Query::ClauseType::WITH;
            Query::Reference r3;
            r3.refAttribType = Query::ReferenceAttributeType::VALUE;
            r3.refDentityType = Query::DesignEntityType::CONSTANT;
            r3.refType = Query::ReferenceType::SYNONYM;
            r3.refString = "c.value";
            r3.synonym = "c";
            c2.leftRef = r3;
            Query::Reference r4;
            r4.refDentityType = Query::DesignEntityType::PROG_LINE;
            r4.refType = Query::ReferenceType::SYNONYM;
            r4.refString = "n";
            c2.rightRef = r4;

            clauses.push_back(c);
            clauses.push_back(c2);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROCNAME_PROGLINE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VARNAME_PROGLINE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROGLINE_INTEGER) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::INTEGER;
            r.refString = "1";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROGLINE_STMTNUM) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::INTEGER;
            r.refString = "1";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.leftRef = r2;
            
            Query::Clause c2;
            c2.clauseType = Query::ClauseType::WITH;
            Query::Reference r3;
            r3.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r3.refDentityType = Query::DesignEntityType::STMT;
            r3.refType = Query::ReferenceType::SYNONYM;
            r3.refString = "s.stmt#";
            r3.synonym = "s";
            c2.rightRef = r3;
            Query::Reference r4;
            r4.refDentityType = Query::DesignEntityType::PROG_LINE;
            r4.refType = Query::ReferenceType::SYNONYM;
            r4.refString = "n";
            c2.leftRef = r4;

            clauses.push_back(c);
            clauses.push_back(c2);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROGLINE_VALUE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "c" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::INTEGER;
            r.refString = "1";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.leftRef = r2;

            Query::Clause c2;
            c2.clauseType = Query::ClauseType::WITH;
            Query::Reference r3;
            r3.refAttribType = Query::ReferenceAttributeType::VALUE;
            r3.refDentityType = Query::DesignEntityType::CONSTANT;
            r3.refType = Query::ReferenceType::SYNONYM;
            r3.refString = "c.value";
            r3.synonym = "c";
            c2.rightRef = r3;
            Query::Reference r4;
            r4.refDentityType = Query::DesignEntityType::PROG_LINE;
            r4.refType = Query::ReferenceType::SYNONYM;
            r4.refString = "n";
            c2.leftRef = r4;

            clauses.push_back(c);
            clauses.push_back(c2);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROGLINE_PROCNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROGLINE_VARNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "n" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::PROG_LINE;
            r2.refType = Query::ReferenceType::SYNONYM;
            r2.synonym = "n";
            r2.refString = "n";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_STMTNUM_INTEGER) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VALUE_INTEGER) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "c" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VALUE;
            r.refDentityType = Query::DesignEntityType::CONSTANT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "c.value";
            r.synonym = "c";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROCNAME_INTEGER) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VARNAME_INTEGER) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_INTEGER_STMTNUM) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_INTEGER_VALUE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "c" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VALUE;
            r.refDentityType = Query::DesignEntityType::CONSTANT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "c.value";
            r.synonym = "c";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_INTEGER_PROCNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_INTEGER_VARNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("main");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_STMTNUM_QUOTATION) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VALUE_QUOTATION) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "c" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VALUE;
            r.refDentityType = Query::DesignEntityType::CONSTANT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "c.value";
            r.synonym = "c";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_PROCNAME_QUOTATION) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("bird");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_VARNAME_QUOTATION) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("bird");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.leftRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.rightRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_QUOTATION_STMTNUM) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertStatement(1, "Read");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "s" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["s"] = Query::DesignEntityType::STMT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::STMTNUM;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "s.stmt#";
            r.synonym = "s";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_QUOTATION_VALUE) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertConstant(3, { 1 });

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "c" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["c"] = Query::DesignEntityType::CONSTANT;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VALUE;
            r.refDentityType = Query::DesignEntityType::CONSTANT;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "c.value";
            r.synonym = "c";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "FALSE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_QUOTATION_PROCNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertProcedure("bird");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "p" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["p"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::PROCNAME;
            r.refDentityType = Query::DesignEntityType::PROCEDURE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "p.procName";
            r.synonym = "p";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_QUOTATION_VARNAME) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            PKB::getInstance().insertVariable("bird");

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::PROCEDURE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refAttribType = Query::ReferenceAttributeType::VARNAME;
            r.refDentityType = Query::DesignEntityType::VARIABLE;
            r.refType = Query::ReferenceType::SYNONYM;
            r.refString = "v.varName";
            r.synonym = "v";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }

        TEST_METHOD(TEST_SOLVE_WITH_INTEGER_INTEGER) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refDentityType = Query::DesignEntityType::STMT;
            r.refType = Query::ReferenceType::INTEGER;
            r.refString = "1";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::STMT;
            r2.refType = Query::ReferenceType::INTEGER;
            r2.refString = "1";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }
        
        TEST_METHOD(TEST_SOLVE_WITH_QUOTATION_QUOTATION) {
            // REDIRECT STD STREAM
            std::streambuf* backup;
            backup = std::cout.rdbuf();
            std::stringstream ss;
            std::cout.rdbuf(ss.rdbuf());

            //Query Set-up
            Query q = Query();
            std::vector<Query::Element> selected_synonym;
            selected_synonym.push_back(Query::Element{ Query::ElementType::SYNONYM, Query::ReferenceAttributeType::NONE, "v" });
            q.addSelectedSynonyms(selected_synonym);

            std::unordered_map<std::string, Query::DesignEntityType> synonym_table;
            synonym_table["v"] = Query::DesignEntityType::VARIABLE;
            q.addSynonymTable(synonym_table);

            std::vector<Query::Clause> clauses;
            Query::Clause c;
            c.clauseType = Query::ClauseType::WITH;
            Query::Reference r;
            r.refDentityType = Query::DesignEntityType::NONE;
            r.refType = Query::ReferenceType::QUOTATION;
            r.refString = "bird";
            c.rightRef = r;
            Query::Reference r2;
            r2.refDentityType = Query::DesignEntityType::NONE;
            r2.refType = Query::ReferenceType::QUOTATION;
            r2.refString = "bird";
            c.leftRef = r2;
            clauses.push_back(c);
            q.addClauses(clauses);

            QueryEvaluator::getInstance().synTable = synonym_table;

            std::list<std::string> answer = QueryEvaluator::getInstance().solveQuery(q);

            // PRINT STREAM TO LOGGER
            Logger::WriteMessage(ss.str().c_str());

            // ASSIGN COUT BACK TO STDOUT
            std::cout.rdbuf(backup);

            Assert::AreEqual(std::string{ "TRUE" }, answer.front());

            PKB::getInstance().clear();
        }
    };
}
