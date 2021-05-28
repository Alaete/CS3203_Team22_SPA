#include "CppUnitTest.h"
#include "stdafx.h"
#include <cstdio>
#include <fstream>
#include <iostream>

#include "../source/Parser.h"
#include "../source/PKB/PKB.h"
#include "../source/ShuntingYard.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
    TEST_CLASS(TestParser) {
    private:
            bool testParseProgram(std::string filename) {
                try {
                    Parser::getInstance().parseProgram(filename);
                } catch (Parser::ParserException& error) {
                    Logger::WriteMessage(error.what());
                    return false;
                }
                return true;
            }
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
                    noError = false;
                }
                filestream.close();
                std::remove(filename.c_str());
                PKB::getInstance().clear();
                return noError;
            }

        public:
            // Procedure
            TEST_METHOD(emptyProcedure) {
                Assert::IsFalse(testParseProgramString("procedure ABC { }"));
            }
            TEST_METHOD(invalidProcedureKeyword) {
                Assert::IsFalse(testParseProgramString("Procedure ABC { a = b; }"));
            }
            TEST_METHOD(missingProcedureKeyword) {
                Assert::IsFalse(testParseProgramString("ABC { a = b; }"));
            }
            TEST_METHOD(invalidProcedureName) {
                Assert::IsFalse(testParseProgramString("procedure 1ABC { a = b; }"));
            }
            TEST_METHOD(missingProcedureName) {
                Assert::IsFalse(testParseProgramString("procedure { a = b; }"));
            }
            TEST_METHOD(duplicateProcedureName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b; } procedure ABC { b = c; }"));
            }
            TEST_METHOD(incorrectProcedureBracketType) {
                Assert::IsFalse(testParseProgramString("procedure ABC ( a = b; )"));
            }
            TEST_METHOD(invalidToken) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = \"b\"; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a = #b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a = $b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a = 'b'; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a, = b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a. = b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a : b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a? = b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a = @b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC [ a = b; ]"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b; \\ }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a^ = b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a_ = b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { a` = b; }"));
                Assert::IsFalse(testParseProgramString("procedure ABC { ~a = b; }"));
            }
            TEST_METHOD(invalidSemicolon) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b;; }"));
            }
            TEST_METHOD(validSpacing) {
                Assert::IsTrue(testParseProgramString("procedure ABC{a   = b; }       "));
            }
            
            // Statement List
            TEST_METHOD(missingOpeningBrace) {
                Assert::IsFalse(testParseProgramString("procedure ABC a = b; }"));
            }
            TEST_METHOD(missingClosingBrace) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b;"));
            }
            TEST_METHOD(invalidStatementType) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if_else { a = b; } }"));
            }
            TEST_METHOD(emptyStatementList) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x == y) { } }"));
            }

            // Read Statement
            TEST_METHOD(validReadStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { read x; }"));
            }
            TEST_METHOD(invalidReadKeyword) {
                Assert::IsFalse(testParseProgramString("procedure ABC { Read x; }"));
            }
            TEST_METHOD(invalidReadVarName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { read 1; }"));
            }
            TEST_METHOD(missingReadVarName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { read ; }"));
            }
            TEST_METHOD(missingReadSemicolon) {
                Assert::IsFalse(testParseProgramString("procedure ABC { read x }"));
            }

            // Print Statement
            TEST_METHOD(validPrintStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { print x; }"));
            }
            TEST_METHOD(invalidPrintKeyword) {
                Assert::IsFalse(testParseProgramString("procedure ABC { Print x; }"));
            }
            TEST_METHOD(invalidPrintVarName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { print 1; }"));
            }
            TEST_METHOD(missingPrintVarName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { print ; }"));
            }
            TEST_METHOD(missingPrintSemicolon) {
                Assert::IsFalse(testParseProgramString("procedure ABC { print x }"));
            }

            // Call Statement
            TEST_METHOD(invalidCallProcName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { call 1; }"));
            }
            TEST_METHOD(invalidCallKeyword) {
                Assert::IsFalse(testParseProgramString("procedure ABC { Call x; }"));
            }
            TEST_METHOD(missingCallProcName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { call ; }"));
            }
            TEST_METHOD(recursiveCall) {
                Assert::IsFalse(testParseProgramString("procedure ABC { call ABC; }"));
            }
            TEST_METHOD(callToNonExistingProcedure) {
                Assert::IsFalse(testParseProgramString("procedure ABC { call BCD; call BCD; call BCD; }"));
            }
            TEST_METHOD(cyclicCall) {
                Assert::IsFalse(testParseProgramString("procedure ABC { call BCD; } procedure BCD { call CDE; } procedure CDE { call ABC; }"));
            }
            TEST_METHOD(validMultipleCalls) {
                Assert::IsTrue(testParseProgramString("procedure ABC { call BCD; } procedure BCD { call CDE; } procedure CDE { a = b; } procedure DEF { a = b; call ABC; }"));
            }
            TEST_METHOD(missingCallSemicolon) {
                Assert::IsFalse(testParseProgramString("procedure ABC { call x }"));
            }

            // Assign Statement
            TEST_METHOD(validAssignStatementVariableOnly) {
                Assert::IsTrue(testParseProgramString("procedure ABC { a = b; }"));
            }
            TEST_METHOD(validAssignStatementConstantOnly) {
                Assert::IsTrue(testParseProgramString("procedure ABC { a = 1; }"));
            }
            TEST_METHOD(validAssignStatementVariablesAndConstants) {
                Assert::IsTrue(testParseProgramString("procedure ABC { a = b + 1 - c / 2 * e % 3; }"));
            }
            TEST_METHOD(validAssignStatementBracketedVariablesAndConstants) {
                Assert::IsTrue(testParseProgramString("procedure ABC { a = (b + 1 - c) / 2 * (e % 3); }"));
            }
            TEST_METHOD(validComplexAssignStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { a = ((b + 1 - (c % 4)) / 2 * (e % 3)) / ((a / b) + d) * c; }"));
            }
            TEST_METHOD(invalidAssignVarName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { 1 = b; }"));
            }
            TEST_METHOD(multipleAssignVarName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a + b = c; }"));
            }
            TEST_METHOD(invalidAssignExprVarName) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = 1b; }"));
            }
            TEST_METHOD(missingAssignVarName) {
                Assert::IsFalse(testParseProgramString("procedure ABC {  = b; }"));
            }
            TEST_METHOD(missingAssignExpr) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = ; }"));
            }
            TEST_METHOD(missingAssignSemicolon) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b }"));
            }
            TEST_METHOD(missingAssignEquals) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a b; }"));
            }

            // Expression
            TEST_METHOD(validComplexExpr) {
                Assert::IsTrue(testParseProgramString("procedure ABC { x = (((a + b) / c * (e % f)) - (g + h - i / j)) / k; }"));
            }
            TEST_METHOD(missingExprOpeningParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = (b + c) / d) + e; }"));
            }
            TEST_METHOD(missingExprClosingParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = ((b + c) / d + e; }"));
            }
            TEST_METHOD(invalidExprOrderOfVariables) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b c; }"));
            }
            TEST_METHOD(invalidExprNegativeSign) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = -b; }"));
            }
            TEST_METHOD(invalidExprOrderOfOperators) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b++; }"));
            }
            TEST_METHOD(invalidExprOrderOfParenthesisAndVariable) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b (c) / d; }"));
            }
            TEST_METHOD(invalidExprOrderOfVariableAndParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = (b) c / d; }"));
            }
            TEST_METHOD(invalidExprOrderOfCloseParenthesisAndOpenParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = (b)(c) / d; }"));
            }
            TEST_METHOD(invalidExprOrderOfOpenParenthesisAndCloseParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = ()b + c / d; }"));
            }
            TEST_METHOD(invalidExprOrderOfParenthesisAndOperator) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = b (+ c) / d; }"));
            }
            TEST_METHOD(invalidExprOrderOfOperatorAndParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { a = (b + c /) d; }"));
            }

            // If Statement
            TEST_METHOD(validIfStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { if (x == y) then { a = b; } else { c = d; } }"));
            }
            TEST_METHOD(validIfNestedIfStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { if (x == y) then { if (p == q) then { a = b; } else { c = d; } } else { e = f; } }"));
            }
            TEST_METHOD(validElseNestedIfStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { if (x == y) then { a = b; } else { if (p == q) then { a = b; } else { c = d; } } }"));
            }
            TEST_METHOD(validWhileNestedIfStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while (x == y) { if (p == q) then { a = b; } else { c = d; } } }"));
            }
            TEST_METHOD(invalidIfKeyword) {
                Assert::IsFalse(testParseProgramString("procedure ABC { If (x == y) { a = b; } else { c = d; } }"));
            }
            TEST_METHOD(missingThenKeyword) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if (x == y) { a = b; } else { c = d; } }"));
            }
            TEST_METHOD(missingElseKeyword) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if (x == y) then { a = b; } { c = d; } }"));
            }
            TEST_METHOD(emptyIfCondition) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if () then { a = b; } else { c = d; } }"));
            }
            TEST_METHOD(missingIfClosingBrace) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if (x == y) then { a = b; else { c = d; } }"));
            }
            TEST_METHOD(missingIfOpeningBrace) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if (x == y) then a = b; } else { c = d; } }"));
            }
            TEST_METHOD(missingIfConditionParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if x == y then { a = b; } else { c = d; } }"));
            }
            TEST_METHOD(emptyIfStatementList) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if (x == y) then { } else { c = d; } }"));
            }
            TEST_METHOD(emptyElseStatementList) {
                Assert::IsFalse(testParseProgramString("procedure ABC { if (x == y) then { a = b; } else { } }"));
            }

            // While Statement
            TEST_METHOD(validWhileStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while (x == y) { a = b; } }"));
            }
            TEST_METHOD(validWhileNestedWhileStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while (x == y) { while (p == q) { a = b; } } }"));
            }
            TEST_METHOD(validIfNestedWhileStatement) {
                Assert::IsTrue(testParseProgramString("procedure ABC { if (x == y) then { while (p == q) { a = b; } } else { c = d; } }"));
            }
            TEST_METHOD(invalidWhileKeyword) {
                Assert::IsFalse(testParseProgramString("procedure ABC { While (x == y) { a = b; } }"));
            }
            TEST_METHOD(emptyWhileCondition) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while () { a = b; } }"));
            }
            TEST_METHOD(missingWhileClosingBrace) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x == y) { a = b;  }"));
            }
            TEST_METHOD(missingWhileOpeningBrace) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x == y)  a = b; } }"));
            }
            TEST_METHOD(missingWhileConditionParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while x == y { a = b; } }"));
            }
            TEST_METHOD(emptyWhileStatementList) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x == y) { } }"));
            }

            // Conditional Expression
            TEST_METHOD(validComplexCondExpr) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((!(x == y)) || (z + a - (b / c) >= d) && (e % f * g <= h) && (a != (b + 1)) && (a < 5) && ((a % (b - c)) > b)) { a = b; } }"));
            }
            TEST_METHOD(validCondExprNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while (!(c <= d)) { a = b; } }"));
            }
            TEST_METHOD(validCondExprAndOr) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((a >= b) && (c <= d) || (e != f)) { a = b; } }"));
            }
            TEST_METHOD(validCondExprAndAnd) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((a >= b) && (c <= d) && (e != f)) { a = b; } }"));
            }
            TEST_METHOD(validCondExprOrOr) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((a >= b) || (c <= d) || (e != f)) { a = b; } }"));
            }
            TEST_METHOD(validCondExprAndNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((a >= b) && (!(c <= d))) { a = b; } }"));
            }
            TEST_METHOD(validCondExprOrNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((a >= b) || (!(c <= d))) { a = b; } }"));
            }
            TEST_METHOD(validCondExprNotAndNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((!(a >= b)) && (!(c <= d))) { a = b; } }"));
            }
            TEST_METHOD(validCondExprNotOrNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((!(a >= b)) || (!(c <= d))) { a = b; } }"));
            }
            TEST_METHOD(validCondExprNotAndNotAndNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((!(a >= b)) && (!(c <= d)) && (!(e <= f))) { a = b; } }"));
            }
            TEST_METHOD(validCondExprNotOrNotOrNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((!(a >= b)) || (!(c <= d)) || (!(e <= f))) { a = b; } }"));
            }
            TEST_METHOD(validCondExprNotAndNotOrNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((!(a >= b)) && (!(c <= d)) || (!(e <= f))) { a = b; } }"));
            }
            TEST_METHOD(validCondExprNotOrNotAndNot) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while ((!(a >= b)) || (!(c <= d)) && (!(e <= f))) { a = b; } }"));
            }
            TEST_METHOD(validRelExprWithExpressions) {
                Assert::IsTrue(testParseProgramString("procedure ABC { while (a + b > c + d) { a = b; } }"));
            }
            TEST_METHOD(invalidRelExprBrackets) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while ((x >= y)) { a = b; } }"));
            }
            TEST_METHOD(invalidRelExprTriple) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x >= y >= z) { a = b; } }"));
            }
            TEST_METHOD(invalidExprCondExpr) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x + y) { a = b; } }"));
            }
            TEST_METHOD(invalidVarCondExpr) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x) { a = b; } }"));
            }
            TEST_METHOD(invalidCondExprPunctuation) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x ! y) { a = b; } }"));
            }
            TEST_METHOD(missingCondExprOpeningParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while x >= y) { a = b; } }"));
            }
            TEST_METHOD(missingCondExprClosingParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x <= y { a = b; } }"));
            }
            TEST_METHOD(invalidCondExprOrderOfVariables) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x == y z) { a = b; } }"));
            }
            TEST_METHOD(invalidCondExprOrderOfOperators) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x > y - - z) { a = b; } }"));
            }
            TEST_METHOD(invalidCondExprOrderOfParenthesisAndOperator) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x < y (- z) / p) { a = b; } }"));
            }
            TEST_METHOD(invalidCondExprOrderOfOperatorAndParenthesis) {
                Assert::IsFalse(testParseProgramString("procedure ABC { while (x < (y - z*) p) { a = b; } }"));
            }
            
            // Shunting Yard
            TEST_METHOD(charVariableExpression) {
                Assert::IsTrue(ShuntingYard::shuntingYard("a*(b+c/d)-e") == "a b c d / + * e -");
            }
            TEST_METHOD(constantVariableExpression) {
                Assert::IsTrue(ShuntingYard::shuntingYard("100*3+(70-200/10)/2") == "100 3 * 70 200 10 / - 2 / +");
            }
            TEST_METHOD(stringVariableExpression) {
                Assert::IsTrue(ShuntingYard::shuntingYard("var1*var2+(var3-var4/var5)/var6") == "var1 var2 * var3 var4 var5 / - var6 / +");
            }
            TEST_METHOD(complexExpression) {
                Assert::IsTrue(ShuntingYard::shuntingYard("var1*b+(variable3-400/var5)/variableWithAReallyLongName") == "var1 b * variable3 400 var5 / - variableWithAReallyLongName / +");
            }
    };
}
