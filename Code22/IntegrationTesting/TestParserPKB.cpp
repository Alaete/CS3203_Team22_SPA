#include "CppUnitTest.h"
#include "stdafx.h"
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "../source/Parser.h"
#include "../source/PKB/PKB.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting {
    TEST_CLASS(TestParserPKB) {
    private:
        bool testParseProgramString(std::string filestring) {
            bool noError = true;
            std::string filename("SIMPLE_source.txt");
            std::ofstream filestream(filename);
            filestream << filestring << std::endl;
            try {
                Parser::getInstance().parseProgram(filename);
            }
            catch (Parser::ParserException& error) {
                Logger::WriteMessage(error.what());
                PKB::getInstance().clear();
                noError = false;
            }
            catch (const std::string e) {
                Logger::WriteMessage(e.c_str());
                PKB::getInstance().clear();
                noError = false;
            }
            filestream.close();
            std::remove(filename.c_str());
            return noError;
        }

    public:
        // Procedure
        TEST_METHOD(insertProcedure) {
            if (testParseProgramString("procedure ABC { a = b; }")) {
                std::vector<std::string> procedureNames = PKB::getInstance().getAllValuesProcedure();
                std::vector<std::string> actualProcedureNames = { "ABC" };
                PKB::getInstance().clear();
                Assert::IsTrue(procedureNames == actualProcedureNames);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Multiple Procedures
        TEST_METHOD(insertMultipleProcedures) {
            if (testParseProgramString("procedure ABC { a = b; } procedure BCD { print a; } procedure CDE { read b; }")) {
                std::vector<std::string> procedureNames = PKB::getInstance().getAllValuesProcedure();
                std::vector<std::string> actualProcedureNames = { "ABC", "BCD", "CDE" };
                PKB::getInstance().clear();
                Assert::IsTrue(procedureNames == actualProcedureNames);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Parent
        TEST_METHOD(insertParent) {
            if (testParseProgramString("procedure ABC { if (x == y) then { a = b; b = c; } else { c = d; } d = e; }")) {
                std::unordered_set<int> childOf1 = PKB::getInstance().getChild(1);
                std::vector<int> parents = PKB::getInstance().getAllKeysChild();
                std::unordered_set<int> actualChildOf1 = { 2, 3, 4 };
                std::vector<int> actualParents = { 1 };
                PKB::getInstance().clear();
                Assert::IsTrue(childOf1 == actualChildOf1);
                Assert::IsTrue(parents == actualParents);
            } 
            else {
                Assert::IsFalse(false);
            }
        }

        // Statement
        TEST_METHOD(insertStatement) {
            if (testParseProgramString("procedure ABC { if (x == y) then { a = b; b = c; } else { c = d; } d = e; }")) {
                std::vector<int> statementKeys = PKB::getInstance().getAllKeysStatement();
                std::vector<std::string> statementValues = PKB::getInstance().getAllValuesStatement();
                std::unordered_set<int> assignStatements = PKB::getInstance().getKeysStatement("assign");
                std::unordered_set<int> ifStatements = PKB::getInstance().getKeysStatement("if");
                std::vector<int> actualStatementKeys = { 1, 2, 3, 4, 5 };
                std::vector <std::string> actualStatementValues = { "if", "assign", "assign", "assign", "assign" };
                std::unordered_set<int> actualAssignStatements = { 2, 3, 4, 5 };
                std::unordered_set<int> actualIfStatements = { 1 };
                PKB::getInstance().clear();
                Assert::IsTrue(statementKeys == actualStatementKeys);
                Assert::IsTrue(statementValues == actualStatementValues);
                Assert::IsTrue(ifStatements == actualIfStatements);
                Assert::IsTrue(assignStatements == actualAssignStatements);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Statement List
        TEST_METHOD(insertStatementList) {
            if (testParseProgramString("procedure ABC { if (x == y) then { a = b; b = c; } else { c = d; } d = e; }")) {
                std::vector<int> statementListKeys = PKB::getInstance().getAllKeysStatementList();
                std::unordered_set<int> statementList2 = PKB::getInstance().getStatementList(2);
                std::unordered_set<int> statementList4 = PKB::getInstance().getStatementList(4);
                std::vector<int> actualStatementListKeys = { 2, 4 };
                std::unordered_set<int> actualStatementList2 = { 2, 3 };
                std::unordered_set<int> actualStatementList4 = { 4, 4 };
                PKB::getInstance().clear();
                Assert::IsTrue(statementListKeys == actualStatementListKeys);
                Assert::IsTrue(statementList2 == actualStatementList2);
                Assert::IsTrue(statementList4 == actualStatementList4);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Procedure Statement List
        TEST_METHOD(insertProcedureStatementList) { 
            if (testParseProgramString("procedure ABC { if (x == y) then { a = b; b = c; } else { c = d; } d = e; } procedure DEF { call ABC; e = f; }")) {
                std::vector<int> statementListKeys = PKB::getInstance().getAllKeysProcedureStatementList();
                std::unordered_set<int> statementList0 = PKB::getInstance().getProcedureStatementList(0);
                std::unordered_set<int> statementList1 = PKB::getInstance().getProcedureStatementList(1);
                std::vector<int> actualStatementListKeys = { 0, 1 };
                std::unordered_set<int> actualStatementList0 = { 1, 2, 3, 4, 5 };
                std::unordered_set<int> actualStatementList1 = { 6, 7 };
                PKB::getInstance().clear();
                Assert::IsTrue(statementListKeys == actualStatementListKeys);
                Assert::IsTrue(statementList0 == actualStatementList0);
                Assert::IsTrue(statementList1 == actualStatementList1);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Follows
        TEST_METHOD(insertFollows) {
            if (testParseProgramString("procedure ABC { if (x == y) then { a = b; b = c; } else { c = d; } d = e; }")) {
                int followedBy3 = PKB::getInstance().getFollows(3);
                int followedBy5 = PKB::getInstance().getFollows(5);
                std::vector<int> followers = PKB::getInstance().getAllKeysFollows();
                int actualFollowedBy3 = 2;
                int actualFollowedBy5 = 1;
                std::vector<int> actualFollowers = { 3, 5 };
                PKB::getInstance().clear();
                Assert::IsTrue(followedBy3 == actualFollowedBy3);
                Assert::IsTrue(followedBy5 == actualFollowedBy5);
                Assert::IsTrue(followers == actualFollowers);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Read
        TEST_METHOD(insertRead) {
            if (testParseProgramString("procedure ABC { read def; read ghi; }")) {
                std::vector<std::string> valuesRead = PKB::getInstance().getAllValuesRead();
                std::vector<std::string> actualValuesRead = { "def", "ghi" };
                std::string valueReadAt1 = PKB::getInstance().getRead(1);
                std::string valueReadAt2 = PKB::getInstance().getRead(2);
                std::string actualValueReadAt1 = "def";
                std::string actualValueReadAt2 = "ghi";
                PKB::getInstance().clear();
                Assert::IsTrue(valueReadAt1 == actualValueReadAt1);
                Assert::IsTrue(valueReadAt2 == actualValueReadAt2);
                Assert::IsTrue(valuesRead == actualValuesRead);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Print
        TEST_METHOD(insertPrint) {
            if (testParseProgramString("procedure ABC { print def; print ghi; }")) {
                std::vector<std::string> valuesPrint = PKB::getInstance().getAllValuesPrint();
                std::vector<std::string> actualValuesPrint = { "def", "ghi" };
                std::string valuePrintAt1 = PKB::getInstance().getPrint(1);
                std::string valuePrintAt2 = PKB::getInstance().getPrint(2);
                std::string actualValuePrintAt1 = "def";
                std::string actualValuePrintAt2 = "ghi";
                PKB::getInstance().clear();
                Assert::IsTrue(valuePrintAt1 == actualValuePrintAt1);
                Assert::IsTrue(valuePrintAt2 == actualValuePrintAt2);
                Assert::IsTrue(valuesPrint == actualValuesPrint);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Call
        TEST_METHOD(insertCall) {
            if (testParseProgramString("procedure ABC { if (x == y) then { a = b; b = c; } else { c = d; } call GHI; } procedure DEF { call ABC; } procedure GHI { a = b; }")) {
                std::vector<std::string> valuesCall = PKB::getInstance().getAllValuesCall();
                std::vector<std::string> actualValuesCall = { "GHI", "ABC" };
                std::string valueCallAt5 = PKB::getInstance().getCall(5);
                std::string valueCallAt6 = PKB::getInstance().getCall(6);
                std::string actualValueCallAt5 = "GHI";
                std::string actualValueCallAt6 = "ABC";
                PKB::getInstance().clear();
                Assert::IsTrue(valueCallAt5 == actualValueCallAt5);
                Assert::IsTrue(valueCallAt6 == actualValueCallAt6);
                Assert::IsTrue(valuesCall == actualValuesCall);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Variable
        TEST_METHOD(insertVariable) {
            if (testParseProgramString("procedure ABC { if (x == y) then { a = b; } else { c = d; } read e; print f; g = i + j / k * (l % m); }")) {
                std::vector<std::string> variables = PKB::getInstance().getAllValuesVariable();
                std::vector<std::string> actualVariables = { "x", "y", "a", "b", "c", "d", "e", "f", "g", "i", "j", "k", "l", "m" };
                PKB::getInstance().clear();
                Assert::IsTrue(variables == actualVariables);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Constant
        TEST_METHOD(insertConstant) {
            if (testParseProgramString("procedure ABC { if (x == 0) then { a = 1; } else { c = 2 - 3 + 4 / 5 * (6 % 7); } read e; print f; g = (((8 + 9))); }")) {
                std::vector<std::unordered_set<int>> constants = PKB::getInstance().getAllValuesConstant();
                std::vector<std::unordered_set<int>> actualConstants = { { 0 }, { 1 }, { 2, 3, 4, 5, 6, 7 }, { 8, 9 } };
                PKB::getInstance().clear();
                Assert::IsTrue(constants == actualConstants);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // If
        TEST_METHOD(insertIf) {
            if (testParseProgramString("procedure ABC { if ((x >= (b + c) % d) && (!(a < (c - d) / e)) || (d == e)) then { a = 1; } else { c = 2 - 3 + 4 / 5 * (6 % 7); } while (!(c > e - (f * g))) { print f; } read e; g = (((8 + 9))); }")) {
                std::vector<int> headerLineNumbers = PKB::getInstance().getAllKeysIf();
                std::vector<std::unordered_set<std::string>> conditions = PKB::getInstance().getAllValuesIf();
                std::vector<int> actualHeaderLineNumbers = { 1 };
                std::vector<std::unordered_set<std::string>> actualConditions = { { "x", "b", "c", "d", "a", "e" } };
                PKB::getInstance().clear();
                Assert::IsTrue(headerLineNumbers == actualHeaderLineNumbers);
                Assert::IsTrue(conditions == actualConditions);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        TEST_METHOD(insertIfConstant) {
            if (testParseProgramString("procedure ABC { if (800 > 900) then { a = 1; } else { c = 2 - 3 + 4 / 5 * (6 % 7); } }")) {
                std::vector<int> headerLineNumbers = PKB::getInstance().getAllKeysIf();
                std::vector<std::unordered_set<std::string>> conditions = PKB::getInstance().getAllValuesIf();
                std::vector<int> actualHeaderLineNumbers = { 1 };
                std::vector<std::unordered_set<std::string>> actualConditions = { { } };
                PKB::getInstance().clear();
                Assert::IsTrue(headerLineNumbers == actualHeaderLineNumbers);
                Assert::IsTrue(conditions == actualConditions);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // While
        TEST_METHOD(insertWhile) {
            if (testParseProgramString("procedure ABC { if ((x >= (b + c) % d) && (!(a < (c - d) / e)) || (d == e)) then { a = 1; } else { c = 2 - 3 + 4 / 5 * (6 % 7); } while (!(c > e - (f * g))) { print f; } read e; g = 8 + 9; }")) {
                std::vector<int> headerLineNumbers = PKB::getInstance().getAllKeysWhile();
                std::vector<std::unordered_set<std::string>> conditions = PKB::getInstance().getAllValuesWhile();
                std::vector<int> actualHeaderLineNumbers = { 4 };
                std::vector<std::unordered_set<std::string>> actualConditions = { { "c", "e", "f", "g" } };
                PKB::getInstance().clear();
                Assert::IsTrue(headerLineNumbers == actualHeaderLineNumbers);
                Assert::IsTrue(conditions == actualConditions);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        TEST_METHOD(insertWhileConstant) {
            if (testParseProgramString("procedure ABC { while (700 > 600) { print f; } read e; g = 8 + 9; }")) {
                std::vector<int> headerLineNumbers = PKB::getInstance().getAllKeysWhile();
                std::vector<std::unordered_set<std::string>> conditions = PKB::getInstance().getAllValuesWhile();
                std::vector<int> actualHeaderLineNumbers = { 1 };
                std::vector<std::unordered_set<std::string>> actualConditions = { { } };
                PKB::getInstance().clear();
                Assert::IsTrue(headerLineNumbers == actualHeaderLineNumbers);
                Assert::IsTrue(conditions == actualConditions);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Assign
        TEST_METHOD(insertAssign) {
            if (testParseProgramString("procedure ABC { if (x == y) then { a = b; } else { c = d; } read e; print f; g = i * j + (k - l % m) / n; }")) {
                std::vector<std::pair<std::string, std::string>> valuesAssign = PKB::getInstance().getAllValuesAssign();
                std::vector<std::pair<std::string, std::string>> actualValuesAssign = { { "a", "b" }, { "c", "d" }, { "g", "i j * k l m % - n / +" } };
                PKB::getInstance().clear();
                Assert::IsTrue(valuesAssign == actualValuesAssign);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Calls
        TEST_METHOD(insertCalls) {
            if (testParseProgramString("procedure ABC { call EFG; } procedure BCD { call ABC; call CDE; call DEF; call EFG; } procedure CDE { call ABC; } procedure DEF { call ABC; } procedure EFG { a = b; }")) {
                std::vector<int> keysCalling = { 0, 1, 2, 3 };
                std::vector<int> actualKeysCalling = PKB::getInstance().getAllKeysCalls();
                std::unordered_set<int> calledBy0 = PKB::getInstance().getCalls(0);
                std::unordered_set<int> calledBy1 = PKB::getInstance().getCalls(1);
                std::unordered_set<int> calledBy2 = PKB::getInstance().getCalls(2);
                std::unordered_set<int> calledBy3 = PKB::getInstance().getCalls(3);
                std::unordered_set<int> actualCalledBy0 = { 4 };
                std::unordered_set<int> actualCalledBy1 = { 0, 2, 3, 4 };
                std::unordered_set<int> actualCalledBy2 = { 0 };
                std::unordered_set<int> actualCalledBy3 = { 0 };
                PKB::getInstance().clear();
                Assert::IsTrue(keysCalling == actualKeysCalling);
                Assert::IsTrue(calledBy0 == actualCalledBy0);
                Assert::IsTrue(calledBy1 == actualCalledBy1);
                Assert::IsTrue(calledBy2 == actualCalledBy2);
                Assert::IsTrue(calledBy3 == actualCalledBy3);
            }
            else {
                Assert::IsFalse(false);
            }
        }

        // Calls Star
        TEST_METHOD(insertCallsStar) {
            if (testParseProgramString("procedure ABC { call EFG; call FGH; } procedure BCD { call CDE; } procedure CDE { call DEF; } procedure DEF { call ABC; } procedure EFG { a = b; } procedure FGH { b = c; }")) {
                std::unordered_set<int> calledBy0 = PKB::getInstance().getCallsStar(0);
                std::unordered_set<int> calledBy1 = PKB::getInstance().getCallsStar(1);
                std::unordered_set<int> calledBy2 = PKB::getInstance().getCallsStar(2);
                std::unordered_set<int> calledBy3 = PKB::getInstance().getCallsStar(3);
                std::unordered_set<int> calledBy4 = PKB::getInstance().getCallsStar(4);
                std::unordered_set<int> calledBy5 = PKB::getInstance().getCallsStar(5);
                std::unordered_set<int> actualCalledBy0 = { 4, 5 };
                std::unordered_set<int> actualCalledBy1 = { 0, 2, 3, 4, 5 };
                std::unordered_set<int> actualCalledBy2 = { 0, 3, 4, 5 };
                std::unordered_set<int> actualCalledBy3 = { 0, 4, 5 };
                std::unordered_set<int> actualCalledBy4 = { };
                std::unordered_set<int> actualCalledBy5 = { };
                PKB::getInstance().clear();
                Assert::IsTrue(calledBy0 == actualCalledBy0);
                Assert::IsTrue(calledBy1 == actualCalledBy1);
                Assert::IsTrue(calledBy2 == actualCalledBy2);
                Assert::IsTrue(calledBy3 == actualCalledBy3);
                Assert::IsTrue(calledBy4 == actualCalledBy4);
                Assert::IsTrue(calledBy5 == actualCalledBy5);
            }
            else {
                Assert::IsFalse(false);
            }
        }
    };
}