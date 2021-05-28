#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>

#include "../source/ShuntingYard.h"

#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TestShuntingYard) 
    {
    public:
        TEST_METHOD(CorrectnessOfCharVariables) {
            std::string expr1 = "a + b";
            std::string expr2 = "a * b + c";
            std::string expr3 = "a * (b + c / d) - e";
 

            std::string ans1 = "a b +";
            std::string ans2 = "a b * c +";
            std::string ans3 = "a b c d / + * e -";
            
            std::string shuntedExpr1 = ShuntingYard::shuntingYard(expr1);
            std::string shuntedExpr2 = ShuntingYard::shuntingYard(expr2);
            std::string shuntedExpr3 = ShuntingYard::shuntingYard(expr3);

            Assert::AreEqual(ans1, shuntedExpr1);
            Assert::AreEqual(ans2, shuntedExpr2);
            Assert::AreEqual(ans3, shuntedExpr3);
            
        }

        TEST_METHOD(CorrectnessOfConstants) {
            std::string expr1 = "4 % 2";
            std::string expr2 = "4 * 2 + 3 - 20 / 5";
            std::string expr3 = "100 * 3 + (70 - 200 / 10) / 2";

            std::string shuntedExpr1 = ShuntingYard::shuntingYard(expr1);
            std::string shuntedExpr2 = ShuntingYard::shuntingYard(expr2);
            std::string shuntedExpr3 = ShuntingYard::shuntingYard(expr3);

            std::string ans1 = "4 2 %";
            std::string ans2 = "4 2 * 3 + 20 5 / -";
            std::string ans3 = "100 3 * 70 200 10 / - 2 / +";

            Assert::AreEqual(ans1, shuntedExpr1);
            Assert::AreEqual(ans2, shuntedExpr2);
            Assert::AreEqual(ans3, shuntedExpr3);

        }

        TEST_METHOD(CorrectnessOfStringVariables) {
            std::string expr1 = "variable1 * variable2";
            std::string expr2 = "var1 * var2 + var3 - var4 / var5";
            std::string expr3 = "var1 * var2 + (var3 - var4 / var5) / var6";

            std::string shuntedExpr1 = ShuntingYard::shuntingYard(expr1);
            std::string shuntedExpr2 = ShuntingYard::shuntingYard(expr2);
            std::string shuntedExpr3 = ShuntingYard::shuntingYard(expr3);

            std::string ans1 = "variable1 variable2 *";
            std::string ans2 = "var1 var2 * var3 + var4 var5 / -";
            std::string ans3 = "var1 var2 * var3 var4 var5 / - var6 / +";

            Assert::AreEqual(ans1, shuntedExpr1);
            Assert::AreEqual(ans2, shuntedExpr2);
            Assert::AreEqual(ans3, shuntedExpr3);
        }

        TEST_METHOD(CombinationOfAllTypesOfVariables) {
            std::string expr1 = "variable1 * 2 + c";
            std::string expr2 = "var1 * 2 + c - someVar4 / variable5c";
            std::string expr3 = "var1 * b + (variable3 - 400 / var5) / variableWithAReallyLongName";

            std::string shuntedExpr1 = ShuntingYard::shuntingYard(expr1);
            std::string shuntedExpr2 = ShuntingYard::shuntingYard(expr2);
            std::string shuntedExpr3 = ShuntingYard::shuntingYard(expr3);

            std::string ans1 = "variable1 2 * c +";
            std::string ans2 = "var1 2 * c + someVar4 variable5c / -";
            std::string ans3 = "var1 b * variable3 400 var5 / - variableWithAReallyLongName / +";

            Assert::AreEqual(ans1, shuntedExpr1);
            Assert::AreEqual(ans2, shuntedExpr2);
            Assert::AreEqual(ans3, shuntedExpr3);
        }

    };
}