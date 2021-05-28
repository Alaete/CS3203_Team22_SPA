#include "stdafx.h"
#include "QueryParserUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestQueryParser)
    {
    public:
        TEST_METHOD(TEST_Assign_Valid) {
            std::string query = "assign a1; Select a1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsValidSyntax());
            Assert::IsFalse(!result.getIsValid() && !result.getIsValidSyntax());
        }

        TEST_METHOD(TEST_Assign_Invalid) {
            std::string query = "assign a1; Select c1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }

        TEST_METHOD(TEST_Print_Valid) {
            std::string query = "print pr; Select pr";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsValidSyntax());
            Assert::IsFalse(!result.getIsValid() && !result.getIsValidSyntax());
        }

        TEST_METHOD(TEST_Print_Invalid) {
            std::string query = "print pr, print ppppp; Select pp";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_Procedure_Valid) {
            std::string query = "procedure p1; Select p1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Procedure_Invalid) {
            std::string query = "procedure pp; Select p";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_Call_Valid) {
            std::string query = "call c; Select c";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSynonymsTable().size() == 1);
            Assert::IsFalse(!result.getIsValid() && result.getSynonymsTable().size() == 1);
        }
        TEST_METHOD(Test_Call_Invalid) {
            std::string query = "call c1, c2; Select t1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_While_Valid) {
            std::string query = "while w; Select w";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_While_Invalid) {
            std::string query = "while w; Select ww";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }

        TEST_METHOD(Test_Read_Valid) {
            std::string query = "read r, r12,r1; Select r1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSynonymsTable().size() == 3);
            Assert::IsFalse(!result.getIsValid() && result.getSynonymsTable().size() == 3);
        }
        TEST_METHOD(Test_Read_Invalid) {
            std::string query = "read r1; Select ww";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_Stmt_Valid) {
            std::string query = "stmt s, s1; Select s1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSynonymsTable().size() == 2);
            Assert::IsFalse(!result.getIsValid() && result.getSynonymsTable().size() == 2);
        }
        TEST_METHOD(Test_Stmt_Invalid) {
            std::string query = "stmt s; Select sssss";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_Variable_Valid) {
            std::string query = "variable v,   vvv  ; Select v";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSynonymsTable().size() == 2);
            Assert::IsFalse(!result.getIsValid() && result.getSynonymsTable().size() == 2);
        }
        TEST_METHOD(Test_Variable_Invalid) {
            std::string query = "variable v, vvv  ; Select v1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_If_Valid) {
            std::string query = "if ifs, if1 ; Select ifs";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSynonymsTable().size() == 2);
            Assert::IsFalse(!result.getIsValid() && result.getSynonymsTable().size() == 2);
        }
        TEST_METHOD(Test_If_Invalid) {
            std::string query = "if ifs,if1 ; Select fs11";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_Constant_Valid) {
            std::string query = "constant c, c2; Select c2";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSynonymsTable().size() == 2);
            Assert::IsFalse(!result.getIsValid() && result.getSynonymsTable().size() == 2);
        }
        TEST_METHOD(Test_Constant_Invalid) {
            std::string query = "constant c; Select fs11";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(TEST_Multiple_Assign_Valid) {
            std::string query = "assign a1,assign1,assign2; Select assign1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(
                result.getIsValid() && result.getSynonymsTable().size() == 3);
            Assert::IsFalse(!result.getIsValid() && result.getSynonymsTable().size() == 3);
        }
        TEST_METHOD(TEST_ParseQuery_Spacing_Valid) {
            std::string query = "      assign a1,a2,a3, a5 ,     a4      ; Select a1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(
                result.getIsValid() && result.getSynonymsTable().size() == 5);
        }
        TEST_METHOD(Test_Incomplete_Invalid) {
            std::string query = "      procedure p1,p2,p3,p4 ,    p5     ; stmt s; Select p such that";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_Empty_Select_Invalid) {
            std::string query = "stmt s";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_WildCard_Synonym_Invalid) {
            std::string query = "stmt _; Select _s";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_Empty_synonym_Invalid) {
            std::string query = "stmt s; assign; Select s";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_ParseQuery_Follows_Invalid) {
            std::string query = "assign a; stmt s; procedure p; Select s such that Follows(p, s)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid() && result.getIsValidSyntax());
        }
        TEST_METHOD(Test_ParseQuery_Follows_Stmt_Valid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Follows (s, 3)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && (result.getSynonymsTable().size() == 3) && result.getSelectedSynonyms().at(0).synonymString == "s"
            && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::FOLLOWS);
            Assert::IsFalse(!result.getIsValid() && (result.getSynonymsTable().size() == 3));
        }
        TEST_METHOD(Test_ParseQuery_Follows_Star_Stmt_Valid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Follows* (s, 3)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && (result.getSynonymsTable().size() == 3));
            Assert::IsFalse(!result.getIsValid() && (result.getSynonymsTable().size() == 3));
        }
        TEST_METHOD(Test_ParseQuery_Follows_Stmt_Int_Valid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Follows (1, s)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && (result.getSynonymsTable().size() == 3));
            Assert::IsFalse(!result.getIsValid() && (result.getSynonymsTable().size() == 3));
        }
        TEST_METHOD(Test_ParseQuery_Follows_Missing_Synonym_Invalid) {
            std::string query = "assign a; stmt s; variable v; Select  such that Follows (1, s)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Follows_Star_Valid) {
            std::string query = "stmt s; Select s such that Follows* (6, s)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Follows_Star_Invalid) {
            std::string query = "stmt s; Select s such that Follows* (!!, s)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Modifies_Valid) {
            std::string query = "variable v; procedure p; Select v such that Modifies (6, v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 1);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 1);
        }
        TEST_METHOD(Test_Modifies_Wildcard_Invalid) {
            std::string query = "variable v; procedure p; Select p such that Modifies(_, \"x\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Uses_Valid) {
            std::string query = "assign a; variable v; Select a such that Uses (a, \"x\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Uses_Constant_Invalid) {
            std::string query = "variable v; constant c; Select p such that Uses(p, c)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Uses_Wildcard_Invalid) {
            std::string query = "variable v; procedure p; Select p such that Uses(_, v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Uses_Design_abstract_Invalid) {
            std::string query = "variable v; procedure p; Select p such that Uses*(_, v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_ParseQuery_Parent_Valid) {
            std::string query = "stmt s1; Select s1 such that Parent(s1, 10)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 1 && result.getSynonymsTable().size() == 1);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 1 && result.getSynonymsTable().size() == 1);
        }
        TEST_METHOD(Test_ParseQuery_Parent_Star_stmt_Valid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Parent* (3, s)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 1 && result.getSynonymsTable().size() == 3);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 1 && result.getSynonymsTable().size() == 3);
        }
        TEST_METHOD(Test_ParseQuery_Parent_Cons_stmt_Valid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Parent* (s, 5)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 1 && result.getSynonymsTable().size() == 3);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 1 && result.getSynonymsTable().size() == 3);
        }
        TEST_METHOD(Test_ParseQuery_Parent_Var_Invalid) {
            std::string query = "stmt s1, variable v; Select s1 such that Parent(s1, v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Parent_Proc_Invalid) {
            std::string query = "stmt s1, procedure p; Select s1 such that Parent(s1, p)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Parent_Constant_Invalid) {
            std::string query = "constant c, procedure p; Select s1 such that Parent(c, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Pattern_Integer_Invalid) {
            std::string query = "assign a; Select a pattern a(\"v\", 1)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Pattern_Invalid) {
            std::string query = "assign a; Select a pattern a(__, \"x\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Pattern_Invalid_Synonym) {
            std::string query = "assign a, stmt s; Select a pattern s(__, \"x\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(TEST_ParseQuery_Pattern_Invalid_1) {
            std::string query = "assign a; Select a pattern a(_, \")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Pattern_Clause_Size_Valid) {
            std::string query = "assign a; Select a pattern a(\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 1);
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Incomplete_Stmt) {
            std::string query = "assign a; stmt s; Select s such that Uses(s,";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(TEST_ParseQuery_Modifies_Pattern_Valid) {
            std::string query = "assign a; variable v; procedure p; Select v such that Modifies(p, v) pattern a(\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 2);
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Modifies_Pattern_Longer_Invalid) {
            std::string query = "assign a; variable v; procedure p; Select v such that Modifies(p, v) pattern a(\"v\", _, a)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(TEST_ParseQuery_Modifies_Constant_Pattern_Invalid) {
            std::string query = "assign a; variable v; procedure p; Select v such that Modifies(p, 1) pattern a(\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Uses_Constant_Invalid) {
            std::string query = "assign a; variable v; procedure p; Select v such that Uses(p, 1) pattern a(\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Uses_Pattern_Invalid) {
            std::string query = "assign a; variable v; procedure p; Select v such that Uses(p, v) pattern (__, \"x\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Uses_Pattern_Procedure_Invalid) {
            std::string query = "assign a; variable v; procedure p; Select v such that Uses(p, p) pattern a (\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());

        }

        TEST_METHOD(Test_ParseQuery_Uses_Pattern_Valid) {
            std::string query = "assign a; variable v; procedure p; Select v such that Uses(p, v) pattern a (\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 3);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 3);
        }

        TEST_METHOD(Test_ParseQuery_Follows_Pattern_Valid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Follows (s, 3) pattern a(\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 3);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 3);
        }

        TEST_METHOD(Test_ParseQuery_Follows_Pattern_Invalid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Follows (s, 3) pattern a(\"v, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Follows_Star_Pattern_Valid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Follows*(s, 3) pattern a(\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 3);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 3);
        }

        TEST_METHOD(Test_ParseQuery_Follows_Star_Pattern_Invalid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Follows* (s, 3) pattern a(\"v, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Parent_Pattern_Valid) {
            std::string query = "assign a; stmt s1; Select s1 such that Parent(s1, 10) pattern a(\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 2);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 2);
        }
        TEST_METHOD(Test_ParseQuery_Parent_Star_Pattern_Valid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Parent* (3, s) pattern a(\"v\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 3);
            Assert::IsFalse(!result.getIsValid() && result.getClauses().size() == 2 && result.getSynonymsTable().size() == 3);
        }
        TEST_METHOD(Test_ParseQuery_Parent_Pattern_Invalid) {
            std::string query = "stmt s1; Select s1 such that Parent(s1, 10) pattern a(\"v\", _, a)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_ParseQuery_Parent_Star_Pattern_Invalid) {
            std::string query = "assign a; stmt s; variable v; Select s such that Parent* (3, s) pattern a(\"v\", _, a)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_ParseQuery_quotation) {
            std::string query = "variable v; Select v such that Uses(\"p\", v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_ParseQuery_test_design_abstract) {
            std::string query = "variable v; Select v such that Uses(3, v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::USES
                && result.getClauses().at(0).clauseType == Query::ClauseType::SUCH_THAT
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).leftRef.refString == "3"
                && result.getClauses().at(0).rightRef.refString == "v"
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::SYNONYM);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Select_Synonym_2_unknowns) {
            std::string query = "assign a; read rd; Select rd such that Follows (rd, a)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Select_Synonym_2_unknowns_1) {
            std::string query = "while w, w2; Select w such that Parent*(w, w2)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Parent_ValidQuery) {
            std::string query = "stmt s; Select s such that Parent*(s, 16)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_ValidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"1\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_simple_ValidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"(x+y)\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_simple_missing_paren_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"(x\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());

            query = "assign a; Select a pattern a(_, _\"x)\"_)";
            result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_simple_empty_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_complex_ValidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"(((a+b)/c*(e%f))-(g+h-i/j))/k\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_complex_operator_close_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"(((a+b)/c*(e%f))-(g+h-i/))/k\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_complex_missing_paren_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"((a+b)/c*(e%f))-(g+h-i/j))/k\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());

            query = "assign a; Select a pattern a(_, _\"(((a+b)/c*(e%f))-(g+h-i/j)/k\"_)";
            result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_complex_open_operator_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"(((a+b)/c*(e%f))-(g+h-i/j+))/k\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_complex_variable_open_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"(((a+b)/c*(e%f))-(g+h-i/j(e)))/k\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_complex_paren_paren_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"(((a+b)/c*())-(g+h-i/j))/k\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());

            query = "assign a; Select a pattern a(_, _\"(((a+b)/c*(e%f))(g+h-i/j))/k\"_)";
            result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_complex_operator_operator_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(_, _\"(((a+-b)/c*(e%f))-(g+h-i/j))/k\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_int_InvalidQuery) {
            std::string query = "assign a; Select a pattern a(\"1\",_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_Assign_Pattern_expression_lhs_ValidQuery) {
            std::string query = "assign a; variable v; Select a pattern a(v,_\"2\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Assign_Pattern_expression_lhs_quoted_num_ValidQuery) {
            std::string query = "assign a; stmt s; Select s pattern a(\"123\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_modifies_pro_ValidQuery) {
            std::string query = "procedure p; Select p such that Modifies(7, \"y\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_uses_pattern_ValidQuery) {
            std::string query = "stmt s1; variable v; assign a; Select s1 such that Uses(s1, v) pattern a(v, _\"4\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_uses_pattern_missing_assign_InvalidQuery) {
            std::string query = "stmt s1; variable v; assign a; Select s1 such that Uses(s1, v) pattern (v, _\"4\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_quotation_pattern_ValidQuery) {
            std::string query = "assign a; Select a pattern a(\"x\", \"y\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_missing_pattern_InvalidQuery) {
            std::string query = "assign a; variable v; Select v and pattern a(v, _\"a\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_negative_uses_InvalidQuery) {
            std::string query = "variable v; Select v such that Uses(-1, v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_follows1_pattern_validQuery) {
            std::string query = "assign a; variable v; read r, r1; Select r1 such that Follows* (r, a) pattern a(_, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_pattern_name_validQuery) {
            std::string query = "assign a; Select a pattern a(\"b3c\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).leftRef.refString == "a"
                && result.getClauses().at(0).expr.exprString == "_");
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_pattern_parent_wildcard1_validQuery) {
            std::string query = "assign a; variable v; stmt s; while w; Select a such that Parent(w, s) pattern a(_, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(1).rightRef.refString == "_"
                && result.getClauses().at(1).leftRef.refString == "a" && result.getClauses().at(1).expr.exprString == "_"
                && result.getClauses().at(0).leftRef.refString == "w" && result.getClauses().at(0).rightRef.refString == "s");
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_pattern_follows_partial_match_validQuery) {
            std::string query = "assign a, a1, a2; variable v; Select a1 such that Follows(a1, a) pattern a2(v, _\"pppc\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_pattern_follows_partial_1_match_validQuery) {
            std::string query = "assign a2; variable v; Select v such that Follows(11, a2) pattern a2(v, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_pattern_follows_star_no_common_validQuery) {
            std::string query = "assign a, a1; variable v; Select v such that Follows* (a, a1) pattern a1(v, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_pattern_parent_wildcard_validQuery) {
            std::string query = "call caaaall; Select caaaall such that Parent* (15, caaaall)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_uses_assign_variable_validQuery) {
            std::string query = "assign a; variable v; Select a such that Uses(a, v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Duplicate_InvalidQuery) {
            std::string query = "assign a1, a1; Select a1 pattern a1(_, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_modifies_pattern_validQuery) {
            std::string query = "assign a; variable v; read r; Select v such that Modifies(r, v) pattern a(_, _\"hello\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_modifies_pattern_invalidQuery) {
            std::string query = "assign a; variable v; read r; Select v such that Modifies(r, v) pattern a(_, _\"9dis\"_)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_pattern_suchthat_parent_validQuery) {
            std::string query = "if ifs; assign a; variable v; read r; Select ifs pattern a(v, _\"helloo\"_) such that Parent(10, r)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_pattern_suchthat_uses_validQuery) {
            std::string query = "stmt s; assign a; variable v; Select s pattern a(v, _\"6\"_) such that Uses(s, \"RAY\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Select_Boolean_validQuery) {
            std::string query = "Select BOOLEAN";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid() && !result.getIsSelectBoolean());
        }

        TEST_METHOD(Test_Select_Boolean_Next_validQuery) {
            std::string query = "Select BOOLEAN such that Next(2, 4)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXT
                && result.getClauses().at(0).leftRef.refString == "2" && result.getClauses().at(0).rightRef.refString == "4"
                && result.getIsSelectBoolean());

            Assert::IsFalse(!result.getIsValid() && !result.getIsSelectBoolean());
        }

        TEST_METHOD(Test_Select_Boolean_Next_RightWildCard_validQuery) {
            std::string query = "Select BOOLEAN such that Next(32, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXT
                && result.getClauses().at(0).leftRef.refString == "32" && result.getClauses().at(0).rightRef.refString == "_"
                && result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid() && !result.getIsSelectBoolean());
        }
        TEST_METHOD(Test_Select_Boolean_NextStar_validQuery) {
            std::string query = "Select BOOLEAN such that Next* (2, 9)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXT_STAR
                && result.getClauses().at(0).leftRef.refString == "2" && result.getClauses().at(0).rightRef.refString == "9"
                && result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Select_Boolean_Next_Right_STMT_validQuery) {
            std::string query = "Select BOOLEAN such that Next(2, 4)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXT
                && result.getClauses().at(0).leftRef.refString == "2" && result.getClauses().at(0).rightRef.refString == "4"
                && result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Select_Boolean_Next_Wildcards_validQuery) {
            std::string query = "Select BOOLEAN such that Next(_, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXT
                && result.getClauses().at(0).leftRef.refString == "_" && result.getClauses().at(0).rightRef.refString == "_"
                && result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Select_Boolean_Parent_validQuery) {
            std::string query = "stmt s1, s2; while w; Select BOOLEAN such that Parent(w, s2)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::PARENT
                && result.getClauses().at(0).leftRef.refString == "w" && result.getClauses().at(0).rightRef.refString == "s2"
                && result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Select_Boolean_Next_LeftWildcard_validQuery) {
            std::string query = "Select BOOLEAN such that Next(_, 5)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXT
                && result.getClauses().at(0).leftRef.refString == "_" && result.getClauses().at(0).rightRef.refString == "5"
                && result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Select_Stmt_calls_both_wildcard_validQuery) {
            std::string query = "stmt s; Select s.stmt# such that Calls(_, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().size() == 1
                && result.getSelectedSynonyms().at(0).elementType == Query::ElementType::ATTRIBUTE
                && result.getSelectedSynonyms().at(0).elementAttribType == Query::ReferenceAttributeType::STMTNUM
                && result.getClauses().at(0).clauseType == Query::ClauseType::SUCH_THAT
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::CALLS
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::WILDCARD
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::WILDCARD);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Select_Boolean_Calls_left_wildcard_validQuery) {
            std::string query = "Select BOOLEAN such that Calls(_, \"abc\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean()
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::CALLS
                && result.getClauses().at(0).leftRef.refString == "_"
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::WILDCARD
                && result.getClauses().at(0).rightRef.refString == "abc"
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::QUOTATION);
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Select_Boolean_Calls_procedure_validQuery) {
            std::string query = "while w; procedure p1, p2; Select w such that Calls(p1, p2)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Select_Boolean_Calls_left_quotation_validQuery) {
            std::string query = "if ifs; procedure p; Select ifs such that Calls(p, \"baa\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Select_two_tuple_uses_validQuery) {
            std::string query = "stmt s1; variable vv1;Select <s1, vv1> such that Uses(s1, vv1)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Select_two_tuple_parent_InvalidQuery) {
            std::string query = "while w; procedure p; Select <w.stmt#, p.varName> such that Parent(w, 4)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_Select_procName_Calls_validQuery) {
            std::string query = "procedure p, q; Select p.procName such that Calls(p, q)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Select_Two_Tuples_Calls_validQuery) {
            std::string query = "procedure p, q; Select <p, q> such that Calls(p, q)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_bOOlean_InvalidQuery) {
            std::string query = "Select bOOlean";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_s_Next_Right_stmt_validQuery) {
            std::string query = "stmt s; Select s such that Next(43, s)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Boolean_Uses_validQuery) {
            std::string query = "Select BOOLEAN such that Uses(16, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_and_suchthat_validQuery) {
            std::string query = "assign a; while w; Select a such that Parent* (w, a) and Modifies (a, \"x\") such that Next* (1, a)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getClauses().at(0).clauseType == Query::ClauseType::SUCH_THAT
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::PARENT_STAR
                && result.getClauses().at(0).leftRef.refString == "w"
                && result.getClauses().at(0).leftRef.refDentityType == Query::DesignEntityType::WHILE
                && result.getClauses().at(0).rightRef.refString == "a"
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::ASSIGN);
            Assert::IsTrue(result.getClauses().at(1).designAbstractionType == Query::DesignAbstractionType::MODIFIES
                && result.getClauses().at(1).leftRef.refString == "a"
                && result.getClauses().at(1).leftRef.refDentityType == Query::DesignEntityType::ASSIGN
                && result.getClauses().at(1).rightRef.refType == Query::ReferenceType::QUOTATION
                && result.getClauses().at(1).rightRef.refString == "x");
            Assert::IsTrue(result.getClauses().at(0).clauseType == Query::ClauseType::SUCH_THAT
                && result.getClauses().at(2).designAbstractionType == Query::DesignAbstractionType::NEXT_STAR
                && result.getClauses().at(2).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(2).rightRef.refString == "a"
                && result.getClauses().at(2).rightRef.refDentityType == Query::DesignEntityType::ASSIGN);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_NextStar_And_Parent_And_Modifies_validQuery) {
            std::string query = "assign a; while w; Select a such that Next* (1, a) and Parent* (w, a) and Modifies(a, \"x\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Next_Star_And_Parent_Pattern_validQuery) {
            std::string query = "assign a; while w; Select a such that Next* (1, a) and Parent* (w, a) pattern a (\"x\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Calls_Quotation_and_Modifies_validQuery) {
            std::string query = "procedure p; Select p such that Calls (p, \"Third\") and Modifies (p, \"i\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Parent_And_Parent_validQuery) {
            std::string query = "stmt s1, s2; Select s1 such that Parent(s1, 4) and Parent(s2, 5)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_MultipleClauses_validQuery) {
            std::string query = "assign a1, a2, a3; stmt s1, s2; variable v1, v2, v3; Select <s1, s2, v2> such that Uses(s2, v1) and Modifies(s1, \"x\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Follows_and_Uses_validQuery) {
            std::string query = "stmt s, s1; Select s1 such that Follows(s, s1) and Uses(s, \"while\")";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Tuple_variable_if_Parent_InvalidQuery) {
            std::string query = "while w; procedure p; variable v; if ifs; Select <v.procName, ifs.stmt#> such that Parent(w, 4)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_Two_Tuples_Parent_InvalidQuery) {
            std::string query = "while w; procedure p; Select <w.stmt#, p.varName> such that Parent(w, 4)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_Nextstar_Nextstar_validQuery) {
            std::string query = "Select BOOLEAN such that Next*(2, 8) and Next*(8, 9)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean() && result.getClauses().size() == 2);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_MultipleClauses_Pattern_and_such_that_parent_validQuery) {
            std::string query = "assign a1, a2; while w1, w2; Select a2 pattern a1(\"x\", _) and a2(\"x\", _\"x\"_) such that Parent* (w2, a2) and Parent* (w1, w2)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Pattern_parent_next_validQuery) {
            std::string query = "assign a; while w; Select a pattern a (\"x\", _) such that Parent* (w, a) such that Next* (1, a)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_calls_procedure_and_parent_validQuery) {
            std::string query = "procedure p; call c; while w; Select  p such that Calls(\"Second\", p) and Parent(w, c)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_ifs_pattern_invalidQuery) {
            std::string query = "if ifs; variable v; Select ifs pattern ifs(v, _, kk)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_ifs_patternt_validQuery) {
            std::string query = "if ifs; variable v; Select ifs pattern ifs(v, _, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_ifs_2_arguments_only_InvalidQuery) {
            std::string query = "while w; variable v; if ifs; Select <w, v> pattern ifs(v, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_ifs_quotation_wildcard_wildcard_validQuery) {
            std::string query = "if ifs; Select ifs pattern ifs(\"ppp\", _, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_with_stmtnum_pattern_right_wildcard_validQuery) {
            std::string query = "while w; variable v; Select w.stmt# pattern w(v, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid()
                && result.getClauses().at(0).clauseType == Query::ClauseType::PATTERN
                && result.getClauses().at(0).patternAbstractionType == Query::PatternAbstractionType::WHILE
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::SYNONYM
                && result.getSelectedSynonyms().at(0).elementAttribType == Query::ReferenceAttributeType::STMTNUM);
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_while_pattern_var_right_wildcard_validQuery) {
            std::string query = "while w; variable v; Select w pattern w(\"savemoi\", _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSynonymsTable().size() == 2
                && result.getClauses().at(0).clauseType == Query::ClauseType::PATTERN
                && result.getClauses().at(0).patternAbstractionType == Query::PatternAbstractionType::WHILE
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::SYNONYM
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::QUOTATION);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_while_pattern_two_wildcards_validQuery) {
            std::string query = "while w; Select w pattern w(_, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid()
                && result.getClauses().at(0).clauseType == Query::ClauseType::PATTERN
                && result.getClauses().at(0).patternAbstractionType == Query::PatternAbstractionType::WHILE
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::SYNONYM
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::WILDCARD);
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_while_pattern_int_wildcard_InvalidQuery) {
            std::string query = "while w; Select w pattern w(1, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_while_pattern_notdeclared_InvalidQuery) {
            std::string query = "while w; Select w pattern w(hello, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_First_IDENT_Second_attrRef_validQuery) {
            std::string query = "procedure p; Select p with \"first\" = p.procName";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid());
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_IDENT_Second_attrRef_validQuery) {
            std::string query = "print p; Select p.stmt# with p.varName = \"first\"";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSelectedSynonyms().at(0).elementType == Query::ElementType::ATTRIBUTE
            && result.getSelectedSynonyms().at(0).elementAttribType == Query::ReferenceAttributeType::STMTNUM
            && result.getClauses().at(0).clauseType == Query::ClauseType::WITH
                && result.getClauses().at(0).leftRef.refAttribType == Query::ReferenceAttributeType::VARNAME
                && result.getClauses().at(0).rightRef.refAttribType == Query::ReferenceAttributeType::NONE
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::QUOTATION);
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_Boolean_INT_INT_validQuery) {
            std::string query = "Select BOOLEAN with 1 = 1";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean() && result.getClauses().at(0).clauseType == Query::ClauseType::WITH
            && result.getClauses().at(0).leftRef.refAttribType == Query::ReferenceAttributeType::NONE
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::INTEGER);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_tuple_with_references_validQuery) {
            std::string query = "prog_line n; call c; Select <c, n> with c.stmt# = n";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSelectedSynonyms().at(0).synonymString == "c"
                && result.getSelectedSynonyms().at(1).synonymString == "n" && result.getClauses().at(0).clauseType == Query::ClauseType::WITH
                && result.getClauses().at(0).leftRef.refAttribType == Query::ReferenceAttributeType::STMTNUM
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::PROG_LINE);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_tuple__INT_validQuery) {
            std::string query = "prog_line n; Select BOOLEAN with n = 96";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean()
                && result.getClauses().at(0).leftRef.refDentityType == Query::DesignEntityType::PROG_LINE
                && result.getClauses().at(0).rightRef.refAttribType == Query::ReferenceAttributeType::NONE
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::INTEGER);
            Assert::IsFalse(!result.getIsValid());
        }
        TEST_METHOD(Test_attrib_stmtnum_validQuery) {
            std::string query = "read r; Select r.varName with 61 = r.stmt#";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getClauses().at(0).leftRef.refString == "61"
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER && result.getClauses().at(0).rightRef.refAttribType
                == Query::ReferenceAttributeType::STMTNUM && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::READ);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_BOOLEAN_SemanticError__invalidQuery) {
            std::string query = "procedure p; constant four; Select BOOLEAN such that Calls*(p, four)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && result.getIsValidSemantic());
            Assert::IsFalse(result.getIsValid());
        }
        TEST_METHOD(Test_boolean_rhs_notdeclared_SyntaxError_InvalidQuery) {
            std::string query = "procedure p; Select BOOLEAN such that Calls* (p, four)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_two_patterns_validQuery) {
            std::string query = "stmt s; assign a; while w; variable v; procedure p; Select v pattern a(v, _) and w(v, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSelectedSynonyms().at(0).synonymString == "v"
                && result.getClauses().at(0).clauseType == Query::ClauseType::PATTERN
                && result.getClauses().at(0).patternAbstractionType == Query::PatternAbstractionType::ASSIGN
                && result.getClauses().at(0).rightRef.refString == "v"
                && result.getClauses().at(0).expr.exprString == "_"
                && result.getClauses().at(1).rightRef.refString == "v"
                && result.getClauses().at(1).patternAbstractionType == Query::PatternAbstractionType::WHILE);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_arguments_Affects_InvalidQuery) {
            std::string query = "stmt s,s1; Select s such that Affects(_, _, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_Affects_fixed_syn_validQuery) {
            std::string query = "stmt s1; Select s1 such that Affects(1, s1)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getSelectedSynonyms().at(0).synonymString == "s1"
            && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTS
            && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
            && result.getClauses().at(0).rightRef.refString == "s1");
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Affect_syn_syn_boolean_validQuery) {
            std::string query = "prog_line n1; stmt s1; Select BOOLEAN such that Affects(n1, s1)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean()
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTS
                && result.getClauses().at(0).leftRef.refDentityType == Query::DesignEntityType::PROG_LINE
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(0).leftRef.refString == "n1"
                && result.getClauses().at(0).rightRef.refString == "s1");
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Affects_fixed_fixed_return_diff_validQuery) {
            std::string query = "procedure p; Select p such that Affects(12, 12)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "p"
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTS
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::INTEGER);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_Affects_fixed_fixed_validQuery) {
            std::string query = "read hihi; Select hihi such that Affects(11, 15)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "hihi"
                && result.getSynonymsTable().size() == 1
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTS
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::INTEGER);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_progline_next_validQuery) {
            std::string query = "prog_line n; Select n such that Next(4, n)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "n"
                && result.getSynonymsTable().size() == 1
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXT
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::PROG_LINE);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_progline_nextstar_parentstar_validQuery) {
            std::string query = "prog_line n; stmt s; Select s such that Next* (16, n) and Parent* (s, n)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "s"
                && result.getSynonymsTable().size() == 2
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXT_STAR
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::PROG_LINE
                && result.getClauses().at(1).designAbstractionType == Query::DesignAbstractionType::PARENT_STAR
                && result.getClauses().at(1).leftRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(1).rightRef.refDentityType == Query::DesignEntityType::PROG_LINE);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_progline_affectsstar_nextstar_validQuery) {
            std::string query = "prog_line n; assign a; Select a such that Affects* (a, n) and Next* (13, n)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "a"
                && result.getSynonymsTable().size() == 2
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTS_STAR
                && result.getClauses().at(0).leftRef.refDentityType == Query::DesignEntityType::ASSIGN
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::PROG_LINE
                && result.getClauses().at(1).designAbstractionType == Query::DesignAbstractionType::NEXT_STAR
                && result.getClauses().at(1).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(1).rightRef.refDentityType == Query::DesignEntityType::PROG_LINE);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_arguments_progline_uses_InvalidQuery) {
            std::string query = "stmt s; prog_line pl; Select s such that Uses(s, pl)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_arguments_progline_modifies_InvalidQuery) {
            std::string query = "stmt s; prog_line pl; Select s such that Modifies(s, pl)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_arguments_progline_pattern_InvalidQuery) {
            std::string query = "stmt s; prog_line n; assign a; Select a pattern a(n, _)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(!result.getIsValid() && !result.getIsValidSyntax());
            Assert::IsFalse(result.getIsValid());
        }

        TEST_METHOD(Test_multiple_clauses_validQuery) {
            std::string query = "assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3; Select <s1, s2, v2> such that Uses(s3, v1) "
                "and Modifies(s3, \"x\")"
                "and Follows(s1, s2) and Parent(s3, s1) and Uses(s2, v1) such that "
                "Uses (5, \"y\") and Follows (3, 4) pattern a1 (v2, _\"x+y\"_) "
                "such that Affects (a1, a2) with a2.stmt# = 20";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "s1"
                && result.getSelectedSynonyms().at(1).synonymString == "s2"
                && result.getSelectedSynonyms().at(2).synonymString == "v2"
                && result.getSynonymsTable().size() == 9
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::USES
                && result.getClauses().at(0).leftRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::VARIABLE
                && result.getClauses().at(1).designAbstractionType == Query::DesignAbstractionType::MODIFIES
                && result.getClauses().at(1).leftRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(1).rightRef.refType == Query::ReferenceType::QUOTATION
                && result.getClauses().at(2).designAbstractionType == Query::DesignAbstractionType::FOLLOWS
                && result.getClauses().at(2).leftRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(2).leftRef.refString == "s1"
                && result.getClauses().at(2).rightRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(2).rightRef.refString == "s2"
                && result.getClauses().at(3).designAbstractionType == Query::DesignAbstractionType::PARENT
                && result.getClauses().at(3).leftRef.refString == "s3"
                && result.getClauses().at(3).rightRef.refString == "s1"
                && result.getClauses().at(4).designAbstractionType == Query::DesignAbstractionType::USES
                && result.getClauses().at(4).leftRef.refString == "s2"
                && result.getClauses().at(4).rightRef.refString == "v1"
                && result.getClauses().at(5).designAbstractionType == Query::DesignAbstractionType::USES
                && result.getClauses().at(5).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(5).rightRef.refString == "y"
                && result.getClauses().at(6).designAbstractionType == Query::DesignAbstractionType::FOLLOWS
                && result.getClauses().at(6).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(6).rightRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(7).clauseType == Query::ClauseType::PATTERN
                && result.getClauses().at(7).patternAbstractionType == Query::PatternAbstractionType::ASSIGN
                && result.getClauses().at(7).leftRef.refString == "a1"
                && result.getClauses().at(7).rightRef.refString == "v2"
                && result.getClauses().at(7).expr.exprType == Query::ExpressionType::PARTIAL_MATCH
                && result.getClauses().at(8).designAbstractionType == Query::DesignAbstractionType::AFFECTS);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_s_affectsbip_validQuery) {
            std::string query = "stmt s; Select <s> such that AffectsBip(s, 10)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "s"
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTSBIP
                && result.getClauses().at(0).leftRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::INTEGER);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_a_affectsbip_validQuery) {
            std::string query = "assign a; Select a such that AffectsBip(4, a)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "a"
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTSBIP
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::ASSIGN);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_boolean_affectsbip_validQuery) {
            std::string query = "assign a; Select BOOLEAN such that AffectsBip(19, a)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean()
                && result.getIsValidSemantic()
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTSBIP
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::ASSIGN);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_boolean_tuple_affectsbip_validQuery) {
            std::string query = "stmt s1; stmt s2; Select <s1, s2> such that AffectsBip(s1, s2)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getSelectedSynonyms().at(0).synonymString == "s1"
                && result.getSelectedSynonyms().at(1).synonymString == "s2"
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::AFFECTSBIP
                && result.getClauses().at(0).leftRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(0).rightRef.refDentityType == Query::DesignEntityType::STMT);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_boolean_nextbip_validQuery) {
            std::string query = "Select BOOLEAN such that NextBip*(31, 32)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && result.getIsSelectBoolean()
                && result.getIsValidSemantic()
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXTBIP_STAR
                && result.getClauses().at(0).leftRef.refType == Query::ReferenceType::INTEGER
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::INTEGER);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_s_nextbip_validQuery) {
            std::string query = "stmt s; Select s such that NextBip(s, 24)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getClauses().at(0).designAbstractionType == Query::DesignAbstractionType::NEXTBIP
                && result.getClauses().at(0).leftRef.refDentityType == Query::DesignEntityType::STMT
                && result.getClauses().at(0).rightRef.refType == Query::ReferenceType::INTEGER);
            Assert::IsFalse(!result.getIsValid());
        }

        TEST_METHOD(Test_whitespaces_astmt_vvarname_validQuery) {
            std::string query = "while w; stmt s; if ifs, ifs1; assign a; variable v; Select < a.stmt#   , v.varName > with a.stmt# = s.stmt# such that Modifies(a, v)";
            Query result = QueryParser::getInstance().parseQuery(query);
            Assert::IsTrue(result.getIsValid() && !result.getIsSelectBoolean()
                && result.getClauses().at(0).clauseType == Query::ClauseType::WITH
                && result.getClauses().at(1).designAbstractionType == Query::DesignAbstractionType::MODIFIES
                && result.getClauses().at(1).leftRef.refDentityType == Query::DesignEntityType::ASSIGN
                && result.getClauses().at(1).rightRef.refDentityType == Query::DesignEntityType::VARIABLE);
            Assert::IsFalse(!result.getIsValid());
        }
    };
}
