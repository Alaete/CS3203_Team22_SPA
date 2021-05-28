#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <algorithm>

#include "../source/PKB/ConcreteClasses/PKB_Map_Assign.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_Follows.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_Parent.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_StatementList.h"

#include "../source/PKB/ConcreteClasses/PKB_Map_Constant.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_IfWhile.h"

#include "../source/PKB/ConcreteClasses/PKB_Map_CallPrintReadStatement.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_AAstarCCstarFstarNNstarPstar.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_ModifiesUses.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_ProcedureVariable.h"

#include "../source/PKB/PKB.h"

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <chrono>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
    TEST_CLASS(TestPKB_Map_Assign) {
public:
    TEST_METHOD(insertDuplicateKey) {
        bool errorThrown = false;
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignLHS(3, "y");
        }
        catch (std::string error) {
            Logger::WriteMessage(error.c_str());
            Assert::IsTrue(error == "Entry already exists at lineNumber 3!");
            errorThrown = true;
        }
        Assert::IsTrue(errorThrown);
    }

    TEST_METHOD(insertNonExistentRHS) {
        bool errorThrown = false;
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignRHS(4, "y");
        }
        catch (std::string error) {
            Logger::WriteMessage(error.c_str());
            Assert::IsTrue(error == "No entry exists at lineNumber 4!");
            errorThrown = true;
        }
        Assert::IsTrue(errorThrown);
    }

    TEST_METHOD(getNonExistentKey) {
        bool errorThrown = false;
        PKB_Map_Assign table;
        table.insertAssignLHS(3, "x");
        Assert::IsTrue(table.getAssign(4) == std::pair<std::string, std::string>{"", ""});
    }

    TEST_METHOD(insertGetLHS) {
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignLHS(4, "y");
            Assert::IsTrue(table.getAssign(3) == std::pair<std::string, std::string>{ "x", "" });
            Assert::IsFalse(table.getAssign(3) == std::pair<std::string, std::string>{ "x", "a + c" });
            Assert::IsFalse(table.getAssign(3) == std::pair<std::string, std::string>{ "y", "" });
        }
        catch (...) {
            Logger::WriteMessage("Error in test!");
            Assert::IsTrue(false);
        }
    }

    TEST_METHOD(insertGetRHS) {
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignRHS(3, "x + 1");
            table.insertAssignLHS(4, "x");
            table.insertAssignRHS(4, "x + x");

            Assert::IsTrue(table.getAssign(3) == std::pair<std::string, std::string>{ "x", "x + 1" });
            Assert::IsTrue(table.getAssign(4) == std::pair<std::string, std::string>{ "x", "x + x" });
            Assert::IsFalse(table.getAssign(3) == std::pair<std::string, std::string>{ "x", "x + x" });
            Assert::IsFalse(table.getAssign(3) == std::pair<std::string, std::string>{ "y", "a + b" });
        }
        catch (...) {
            Logger::WriteMessage("Error in test!");
            Assert::IsTrue(false);
        }
    }

    TEST_METHOD(getSize) {
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignRHS(3, "x + 1");
            table.insertAssignLHS(4, "x");
            table.insertAssignRHS(4, "x + x");
            Assert::IsTrue(table.getSizeAssign() == 2);
            Assert::IsFalse(table.getSizeAssign() == 3);
        }
        catch (...) {
            Logger::WriteMessage("Error in test!");
            Assert::IsTrue(false);
        }
    }

    TEST_METHOD(hasKey) {
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignLHS(4, "y");
            Assert::IsTrue(table.hasKeyAssign(3));
            Assert::IsFalse(table.hasKeyAssign(7));
        }
        catch (...) {
            Logger::WriteMessage("Error in test!");
            Assert::IsTrue(false);
        }
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignLHS(4, "y");
            Assert::IsTrue(table.getAllKeysAssign() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(table.getAllKeysAssign() == std::vector<int>{ 3, 5 });
        }
        catch (...) {
            Logger::WriteMessage("Error in test!");
            Assert::IsTrue(false);
        }
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignLHS(4, "y");
            table.insertAssignRHS(4, "a * c");

            Assert::IsTrue(table.getAllValuesAssign() == std::vector<std::pair<std::string, std::string>> { { "x", "" }, { "y", "a * c" }});
            Assert::IsFalse(table.getAllValuesAssign() == std::vector<std::pair<std::string, std::string>> { { "x", "a + b" }, { "y", "a * c" }, { "z", "a * c" }});
        }
        catch (...) {
            Logger::WriteMessage("Error in test!");
            Assert::IsTrue(false);
        }
    }

    TEST_METHOD(insert) {
        PKB_Map_Assign table;
        try {
            table.insertAssignLHS(3, "x");
            table.insertAssignLHS(4, "y");
            table.insertAssignLHS(99999, "z");
            table.insertAssignLHS(0, "x");
            table.insertAssignLHS(-3, "x");
            table.insertAssignLHS(55, "x");
            table.insertAssignLHS(60, "x");
            table.insertAssignRHS(3, "a + b");
            table.insertAssignRHS(4, "a * c");
            table.insertAssignRHS(99999, "a * b");
            table.insertAssignRHS(0, "a + b");
            table.insertAssignRHS(-3, "a + b");
            table.insertAssignRHS(55, "a + b");
            table.insertAssignRHS(60, "a + b");

            std::unordered_map<int, std::pair<std::string, std::string>> testTable = { {3, {"x", "a + b"}}, {4, { "y", "a * c" }},
                {99999, { "z", "a * b" }}, {0, { "x", "a + b" }}, {-3, { "x", "a + b" }}, {55, { "x", "a + b" }}, {60, { "x", "a + b" }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (table.getAssign(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { "d", "c / t" };

            testPassed = true;
            for (auto element : testTable) {
                if (table.getAssign(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }
        catch (...) {
            Logger::WriteMessage("Error in test!");
            Assert::IsTrue(false);
        }
    }
    };

    TEST_CLASS(TestPKB_Map_Follows) {
public:
    TEST_METHOD(insertDuplicateKey) {
        bool errorThrown = false;
        PKB_Map_Follows table;
        try {
            table.insertFollows(3, 4);
            table.insertFollows(3, 5);
        }
        catch (std::string error) {
            Logger::WriteMessage(error.c_str());
            Assert::IsTrue(error == "Entry already exists at lineNumber 3!");
            errorThrown = true;
        }
        Assert::IsTrue(errorThrown);
    }

    TEST_METHOD(getNonExistentKey) {
        bool errorThrown = false;
        PKB_Map_Follows table;
        table.insertFollows(3, 4);
        Assert::IsTrue(table.getFollows(4) == -1);
        Assert::IsTrue(table.getFollowedBy(77) == -1);
    }

    TEST_METHOD(insertGetBasic) {
        PKB_Map_Follows table;
        table.insertFollows(3, 4);

        Assert::IsTrue(table.getFollows(3) == 4);
        Assert::IsFalse(table.getFollows(3) == 5);
        Assert::IsTrue(table.getFollowedBy(4) == 3);
        Assert::IsFalse(table.getFollowedBy(4) == 5);
    }

    TEST_METHOD(getSize) {
        PKB_Map_Follows table;
        table.insertFollows(3, 4);
        table.insertFollows(4, 5);
        Assert::IsTrue(table.getSizeFollows() == 2);
        Assert::IsFalse(table.getSizeFollows() == 3);
        Assert::IsTrue(table.getSizeFollowedBy() == 2);
        Assert::IsFalse(table.getSizeFollowedBy() == 3);
    }

    TEST_METHOD(hasKey) {
        PKB_Map_Follows table;
        table.insertFollows(3, 4);
        table.insertFollows(4, 5);
        Assert::IsTrue(table.hasKeyFollows(3));
        Assert::IsFalse(table.hasKeyFollows(7));
        Assert::IsTrue(table.hasKeyFollowedBy(4));
        Assert::IsFalse(table.hasKeyFollowedBy(7));
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_Follows table;

        table.insertFollows(3, 4);
        table.insertFollows(4, 5);
        Assert::IsTrue(table.getAllKeysFollows() == std::vector<int>{ 3, 4 });
        Assert::IsFalse(table.getAllKeysFollows() == std::vector<int>{ 3, 5 });
        Assert::IsTrue(table.getAllKeysFollowedBy() == std::vector<int>{ 4, 5 });
        Assert::IsFalse(table.getAllKeysFollowedBy() == std::vector<int>{ 3, 5 });
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_Follows table;
        table.insertFollows(3, 4);
        table.insertFollows(4, 5);

        Assert::IsTrue(table.getAllValuesFollows() == std::vector<int>{ 4, 5 });
        Assert::IsFalse(table.getAllValuesFollows() == std::vector<int>{ 4, 7 });
        Assert::IsTrue(table.getAllValuesFollowedBy() == std::vector<int>{ 3, 4 });
        Assert::IsFalse(table.getAllValuesFollowedBy() == std::vector<int>{ 3, 5 });
    }

    TEST_METHOD(insert) {
        PKB_Map_Follows table;
        table.insertFollows(3, 4);
        table.insertFollows(4, 5);
        table.insertFollows(5, 99999);
        table.insertFollows(6, 13);
        table.insertFollows(7, 14);
        table.insertFollows(11111, 98);
        table.insertFollows(-3, 67);
        table.insertFollows(11, -5);

        std::unordered_map<int, int> testTable = { {3, 4}, {4, 5}, {5, 99999}, {6, 13}, {7, 14}, {11111, 98}, {-3, 67}, {11, -5} };

        bool testPassed = true;
        for (auto element : testTable) {
            if (table.getFollows(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[33] = 365;

        testPassed = true;
        for (auto element : testTable) {
            if (table.getFollows(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);

        testTable.clear();
        testTable = { {4, 3}, {5, 4}, {99999, 5}, {13, 6}, {14, 7}, {98, 11111}, {67, -3}, {-5, 11} };

        testPassed = true;
        for (auto element : testTable) {
            if (table.getFollowedBy(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[33] = { 365 };

        testPassed = true;
        for (auto element : testTable) {
            if (table.getFollowedBy(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);
    }

    TEST_METHOD(isFollows) {
        PKB_Map_Follows table;
        table.insertFollows(3, 5);
        table.insertFollows(4, 8);
        table.insertFollows(99999, 4);

        Assert::IsTrue(table.isFollows(3, 5));
        Assert::IsFalse(table.isFollows(3, 30));
        Assert::IsFalse(table.isFollows(30, 5));

        Assert::IsTrue(table.isFollowedBy(8, 4));
        Assert::IsFalse(table.isFollowedBy(8, 20));
        Assert::IsFalse(table.isFollowedBy(30, 4));
    }
    };

    TEST_CLASS(TestPKB_Map_Parent) {
public:
    TEST_METHOD(insertDuplicateKey) {
        bool errorThrown = false;
        PKB_Map_Parent table;
        try {
            table.insertParent(3, 4);
            table.insertParent(3, 5);
        }
        catch (std::string error) {
            Logger::WriteMessage(error.c_str());
            Assert::IsTrue(error == "Entry already exists at lineNumber 3!");
            errorThrown = true;
        }
        Assert::IsTrue(errorThrown);
    }

    TEST_METHOD(getNonExistentKey) {
        bool errorThrown = false;
        PKB_Map_Parent table;
        table.insertParent(3, 4);
        Assert::IsTrue(table.getParent(4) == -1);
        Assert::IsTrue(table.getChild(77) == std::unordered_set<int>{});
    }

    TEST_METHOD(insertGetBasic) {
        PKB_Map_Parent table;
        table.insertParent(3, 4);

        Assert::IsTrue(table.getParent(3) == 4);
        Assert::IsFalse(table.getParent(3) == 5);
        Assert::IsTrue(table.getChild(4) == std::unordered_set<int>{3});
        Assert::IsFalse(table.getChild(4) == std::unordered_set<int>{5});
    }

    TEST_METHOD(getSize) {
        PKB_Map_Parent table;
        table.insertParent(3, 4);
        table.insertParent(4, 5);
        Assert::IsTrue(table.getSizeParent() == 2);
        Assert::IsFalse(table.getSizeParent() == 3);
        Assert::IsTrue(table.getSizeChild() == 2);
        Assert::IsFalse(table.getSizeChild() == 3);
    }

    TEST_METHOD(hasKey) {
        PKB_Map_Parent table;
        table.insertParent(3, 4);
        table.insertParent(4, 5);
        Assert::IsTrue(table.hasKeyParent(3));
        Assert::IsFalse(table.hasKeyParent(7));
        Assert::IsTrue(table.hasKeyChild(4));
        Assert::IsFalse(table.hasKeyChild(7));
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_Parent table;

        table.insertParent(3, 4);
        table.insertParent(4, 5);
        Assert::IsTrue(table.getAllKeysParent() == std::vector<int>{ 3, 4 });
        Assert::IsFalse(table.getAllKeysParent() == std::vector<int>{ 3, 5 });
        Assert::IsTrue(table.getAllKeysChild() == std::vector<int>{ 4, 5 });
        Assert::IsFalse(table.getAllKeysChild() == std::vector<int>{ 3, 5 });
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_Parent table;
        table.insertParent(3, 4);
        table.insertParent(4, 5);
        table.insertParent(2, 5);

        Assert::IsTrue(table.getAllValuesParent() == std::vector<int>{ 4, 5, 5 });
        Assert::IsFalse(table.getAllValuesParent() == std::vector<int>{ 4, 7, 5 });
        Assert::IsTrue(table.getAllValuesChild() == std::vector<std::unordered_set<int>>{ {3}, { 4, 2 } });
        Assert::IsFalse(table.getAllValuesChild() == std::vector<std::unordered_set<int>>{ {3}, { 2, 5 } });
    }

    TEST_METHOD(insert) {
        PKB_Map_Parent table;
        table.insertParent(3, 4);
        table.insertParent(4, 5);
        table.insertParent(5, 99999);
        table.insertParent(6, 4);
        table.insertParent(7, 14);
        table.insertParent(11111, 4);
        table.insertParent(-3, 5);
        table.insertParent(11, -5);

        std::unordered_map<int, int> testTable = { {3, 4}, {4, 5}, {5, 99999}, {6, 4}, {7, 14}, {11111, 4}, {-3, 5}, {11, -5} };

        bool testPassed = true;
        for (auto element : testTable) {
            if (table.getParent(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[33] = 365;

        testPassed = true;
        for (auto element : testTable) {
            if (table.getParent(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);

        testTable.clear();
        std::unordered_map<int, std::unordered_set<int>> testTable2 = { {4, {3, 6, 11111}}, {5, {4, -3}}, {99999, {5}}, {14, {7}}, {-5, {11}} };

        testPassed = true;
        for (auto element : testTable2) {
            if (table.getChild(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable2[33] = { {365} };

        testPassed = true;
        for (auto element : testTable2) {
            if (table.getChild(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);
    }

    TEST_METHOD(isParent) {
        PKB_Map_Parent table;
        table.insertParent(3, 5);
        table.insertParent(4, 8);
        table.insertParent(99999, 4);

        Assert::IsTrue(table.isParent(3, 5));
        Assert::IsFalse(table.isParent(3, 30));
        Assert::IsFalse(table.isParent(30, 5));

        Assert::IsTrue(table.isChild(8, 4));
        Assert::IsFalse(table.isChild(8, 20));
        Assert::IsFalse(table.isChild(30, 4));
    }
    };

    TEST_CLASS(TestPKB_Map_StatementList) {
public:
    TEST_METHOD(insertDuplicateKey) {
        PKB_Map_StatementList table;

        table.insertStatementList(3, { 4, 5 });
        table.insertStatementList(3, { 4, 5 });

        Assert::IsTrue(table.getStatementList(3) == std::unordered_set<int>{4, 5});
        Assert::IsTrue(table.getSizeStatementList() == 1);
    }

    TEST_METHOD(getNonExistentKey) {
        PKB_Map_StatementList table;

        table.insertStatementList(3, { 4, 5 });

        Assert::IsTrue(table.getStatementList(4) == std::unordered_set<int>{});
    }

    TEST_METHOD(insertGetBasic) {
        PKB_Map_StatementList table;
        table.insertStatementList(3, { 4, 5 });

        Assert::IsTrue(table.getStatementList(3) == std::unordered_set<int>{4, 5});
        Assert::IsFalse(table.getStatementList(3) == std::unordered_set<int>{3, 5});
    }

    TEST_METHOD(insertGetKey) {
        PKB_Map_StatementList table;
        table.insertStatementList(3, { 4, 5 });

        Assert::IsTrue(table.getKeyStatementList(4) == 3);
        Assert::IsTrue(table.getKeyStatementList(5) == 3);
        Assert::IsFalse(table.getKeyStatementList(4) == 4);
        Assert::IsFalse(table.getKeyStatementList(3) == 4);
    }

    TEST_METHOD(getSize) {
        PKB_Map_StatementList table;
        table.insertStatementList(3, { 4, 5 });
        table.insertStatementList(4, { 5 });
        Assert::IsTrue(table.getSizeStatementList() == 2);
        Assert::IsFalse(table.getSizeStatementList() == 3);
    }

    TEST_METHOD(hasKey) {
        PKB_Map_StatementList table;
        table.insertStatementList(3, { 4, 5 });
        table.insertStatementList(4, { 5 });
        Assert::IsTrue(table.hasKeyStatementList(3));
        Assert::IsFalse(table.hasKeyStatementList(7));
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_StatementList table;

        table.insertStatementList(3, { 4, 5 });
        table.insertStatementList(4, { 5 });
        Assert::IsTrue(table.getAllKeysStatementList() == std::vector<int>{ 3, 4 });
        Assert::IsFalse(table.getAllKeysStatementList() == std::vector<int>{ 3, 5 });
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_StatementList table;
        table.insertStatementList(3, { 4, 5 });
        table.insertStatementList(4, { 5 });

        Assert::IsTrue(table.getAllValuesStatementList() == std::vector<std::unordered_set<int>>{ {4, 5}, { 5 } });
        Assert::IsFalse(table.getAllValuesStatementList() == std::vector<std::unordered_set<int>>{ {4, 6}, { 5 } });
    }

    TEST_METHOD(insert) {
        PKB_Map_StatementList table;
        table.insertStatementList(3, { 5, 6 });
        table.insertStatementList(3, { 4 });
        table.insertStatementList(4, { 5 });
        table.insertStatementList(99999, { 4 });
        table.insertStatementList(0, { 23 });
        table.insertStatementList(-3, { 25 });
        table.insertStatementList(55, { -99 });
        table.insertStatementList(60, { -3, 5 });

        std::unordered_map<int, std::unordered_set<int>> testTable = { {3, {4, 5, 6}}, {4, {5}}, {99999, {4}}, {0, {23}}, {-3, {25}}, {55, {-99}}, {60, { -3, 5 }} };

        bool testPassed = true;
        for (auto element : testTable) {
            if (table.getStatementList(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[33] = { 365, 77 };

        testPassed = true;
        for (auto element : testTable) {
            if (table.getStatementList(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);
    }
    };

    TEST_CLASS(TestPKB_Map_Constant) {
public:
    TEST_METHOD(insertDuplicateKey) {
        PKB_Map_Constant table;

        table.insertConstant(1, { 4, 5 });
        table.insertConstant(1, { 4, 5 });

        Assert::IsTrue(table.getConstant(1) == std::unordered_set<int>{ 4, 5 });
        Assert::IsTrue(table.getSizeConstant() == 1);
    }

    TEST_METHOD(getNonExistentKey) {
        PKB_Map_Constant table;

        table.insertConstant(1, { 4, 5 });

        Assert::IsTrue(table.getConstant(2) == std::unordered_set<int>{});
        Assert::IsTrue(table.getConstant(100) == std::unordered_set<int>{});
    }

    TEST_METHOD(insertGetBasic) {
        PKB_Map_Constant table;
        table.insertConstant(100, { 200, 300 });

        Assert::IsTrue(table.getConstant(100) == std::unordered_set<int>{ 200, 300 });
        Assert::IsFalse(table.getConstant(10) == std::unordered_set<int>{ 20, 50 });
    }

    TEST_METHOD(getSize) {
        PKB_Map_Constant table;
        table.insertConstant(3, { 4, 5 });
        Assert::IsFalse(table.getSizeConstant() == 2);
        Assert::IsTrue(table.getSizeConstant() == 1);

    }

    TEST_METHOD(hasKey) {
        PKB_Map_Constant table;
        table.insertConstant(3, { 4, 5 });
        Assert::IsTrue(table.hasKeyConstant(3));
        Assert::IsFalse(table.hasKeyConstant(10));
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_Constant table;

        table.insertConstant(3, { 4, 5 });
        table.insertConstant(4, { 6, 7 });
        Assert::IsTrue(table.getAllKeysConstant() == std::vector<int>{ 3, 4 });
        Assert::IsFalse(table.getAllKeysConstant() == std::vector<int>{ 3, 6 });
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_Constant table;
        table.insertConstant(3, { 4, 5, 6 });
        table.insertConstant(4, { 1, 2, 3 });

        Assert::IsTrue(table.getAllValuesConstant() == std::vector<std::unordered_set<int>>{ { 4, 5, 6 }, { 1, 2, 3 }});
        Assert::IsFalse(table.getAllValuesConstant() == std::vector<std::unordered_set<int>>{ { 5, 6, 7 }});
    }

    TEST_METHOD(insert) {
        PKB_Map_Constant table;

        table.insertConstant(3, { 1 });
        table.insertConstant(3, { 2 });
        table.insertConstant(4, { 5, 6 });
        table.insertConstant(100000, { 8 });
        table.insertConstant(0, { 10 });
        table.insertConstant(-1, { 100 });
        table.insertConstant(10, { 20 });
        table.insertConstant(50, { -30, -10 });

        std::unordered_map<int, std::unordered_set<int>> testTable = { {3, { 1, 2 }}, {4, { 5, 6 }}, {100000, { 8 }}, {0, { 10 }}, {-1, { 100 }}, {10, { 20 }}, {50, { -30, -10 }} };

        bool testPassed = true;
        for (auto element : testTable) {
            if (table.getConstant(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[66] = { 70, 100 };

        testPassed = true;
        for (auto element : testTable) {
            if (table.getConstant(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);

        testTable.clear();
    }

    TEST_METHOD(isConstantSet) {
        PKB_Map_Constant table;
        table.insertConstant(3, { 5, 6 });
        table.insertConstant(4, { 5 });
        table.insertConstant(99999, { 4 });

        Assert::IsTrue(table.isConstant(3, { 5, 6 }));
        Assert::IsTrue(table.isConstant(3, { 5 }));
        Assert::IsFalse(table.isConstant(3, { 4 }));
        Assert::IsFalse(table.isConstant(3, { 7 }));
        Assert::IsFalse(table.isConstant(9, { 4 }));
    }

    TEST_METHOD(isConstant) {
        PKB_Map_Constant table;
        table.insertConstant(3, { 5, 6 });
        table.insertConstant(4, { 5 });
        table.insertConstant(99999, { 4 });

        Assert::IsTrue(table.isConstant(3, 5));
        Assert::IsTrue(table.isConstant(3, 6));
        Assert::IsTrue(table.isConstant(4, 5));
        Assert::IsFalse(table.isConstant(3, 30));
        Assert::IsFalse(table.isConstant(30, 5));
    }

    };

    TEST_CLASS(TestPKB_Map_ProcedureVariable) {
public:
    TEST_METHOD(insertDuplicateProcedure) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        table.insertThing("procedure1");

        Assert::IsTrue(table.getThing(0) == "procedure1");
        Assert::IsTrue(table.getSize() == 1);
    }

    TEST_METHOD(getNonExistentKey) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        Assert::IsTrue(table.getThing(2) == "");
    }

    TEST_METHOD(insertGetBasic) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        table.insertThing("procedure2");
        table.insertThing("procedure3");

        Assert::IsTrue(table.getThing(0) == "procedure1");
        Assert::IsTrue(table.getThing(1) == "procedure2");
        Assert::IsTrue(table.getThing(2) == "procedure3");
        Assert::IsTrue(table.getThing(3) == "");
        Assert::IsTrue(table.getThing(4) == "");
    }

    TEST_METHOD(getKey) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        table.insertThing("procedure2");
        table.insertThing("procedure3");

        Assert::IsTrue(table.getKey("procedure1") == 0);
        Assert::IsTrue(table.getKey("procedure2") == 1);
        Assert::IsTrue(table.getKey("procedure3") == 2);
    }

    TEST_METHOD(getSize) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        table.insertThing("procedure2");

        Assert::IsTrue(table.getSize() == 2);
        Assert::IsFalse(table.getSize() == 3);
    }

    TEST_METHOD(hasKey) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        table.insertThing("procedure2");

        Assert::IsTrue(table.hasKey(0));
        Assert::IsFalse(table.hasKey(2));
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        table.insertThing("procedure2");

        Assert::IsTrue(table.getAllKeys() == std::vector<int>{ 0, 1 });
        Assert::IsFalse(table.getAllKeys() == std::vector<int>{ 1, 2 });
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        table.insertThing("procedure2");

        Assert::IsTrue(table.getAllValues() == std::vector <std::string> { "procedure1", "procedure2" });
        Assert::IsFalse(table.getAllValues() == std::vector<std::string>{ "procedure3", "procedure4" });
    }

    TEST_METHOD(insert) {
        PKB_Map_ProcedureVariable table;

        table.insertThing("procedure1");
        table.insertThing("procedure2");
        table.insertThing("x");
        table.insertThing("procedure1");
        table.insertThing("y");

        std::unordered_map<int, std::string> testTable = { {0, "procedure1"}, {1, "procedure2"}, {2, "x"}, {3, "y"} };

        bool testPassed = true;
        for (auto element : testTable) {
            if (table.getThing(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[5] = "z";

        testPassed = true;
        for (auto element : testTable) {
            if (table.getThing(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);
    }
    };

    TEST_CLASS(TestPKB_Map_CallPrintReadStatement) {
public:
    TEST_METHOD(insertDuplicateKey) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");
        table.insertThing(1, "proc2");

        Assert::IsTrue(table.getThing(1) == "proc1");
        Assert::IsTrue(table.getSize() == 1);

    }

    TEST_METHOD(getNonExistentKey) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");

        Assert::IsTrue(table.getThing(2) == "");
    }

    TEST_METHOD(insertGetBasic) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");
        table.insertThing(2, "proc2");
        table.insertThing(3, "proc3");

        Assert::IsTrue(table.getThing(1) == "proc1");
        Assert::IsTrue(table.getThing(2) == "proc2");
        Assert::IsTrue(table.getThing(3) == "proc3");
        Assert::IsTrue(table.getThing(4) == "");
        Assert::IsTrue(table.getThing(0) == "");
    }

    TEST_METHOD(getKeysCall) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");
        table.insertThing(2, "proc1");
        table.insertThing(3, "proc3");

        Assert::IsTrue(table.getKeys("proc1") == std::unordered_set<int>{ 1, 2 });
        Assert::IsTrue(table.getKeys("proc3") == std::unordered_set<int>{ 3 });
        Assert::IsTrue(table.getKeys("proc4") == std::unordered_set<int>{});
    }

    TEST_METHOD(getSize) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");
        table.insertThing(2, "proc2");

        Assert::IsTrue(table.getSize() == 2);
        Assert::IsFalse(table.getSize() == 3);
    }

    TEST_METHOD(hasKey) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");
        table.insertThing(2, "proc2");

        Assert::IsTrue(table.hasKey(1));
        Assert::IsFalse(table.hasKey(3));
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");
        table.insertThing(2, "proc2");

        Assert::IsTrue(table.getAllKeys() == std::vector<int>{ 1, 2 });
        Assert::IsFalse(table.getAllKeys() == std::vector<int>{ 3, 4 });
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");
        table.insertThing(2, "proc2");

        Assert::IsTrue(table.getAllValues() == std::vector <std::string> { "proc1", "proc2" });
        Assert::IsFalse(table.getAllValues() == std::vector<std::string>{ "proc2", "proc3" });
    }

    TEST_METHOD(insert) {
        PKB_Map_CallPrintReadStatement table;

        table.insertThing(1, "proc1");
        table.insertThing(2, "proc2");
        table.insertThing(3, "x");
        table.insertThing(1, "proc4");
        table.insertThing(4, "y");

        std::unordered_map<int, std::string> testTable = { {1, "proc1"}, {2, "proc2"}, {3, "x"}, {4, "y"} };

        bool testPassed = true;
        for (auto element : testTable) {
            if (table.getThing(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[5] = "z";

        testPassed = true;
        for (auto element : testTable) {
            if (table.getThing(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);
    }

    };

    TEST_CLASS(TestPKB_Map_IfWhile) {
public:
    TEST_METHOD(insertDuplicateKey) {
        PKB_Map_IfWhile table;

        table.insertThing(7, { "x", "flag" });
        table.insertThing(7, { "x", "flag" });

        Assert::IsTrue(table.getThing(7) == std::unordered_set<std::string>{ "x", "flag" });
        Assert::IsTrue(table.getSize() == 1);
    }

    TEST_METHOD(getNonExistentKey) {
        PKB_Map_IfWhile table;

        table.insertThing(7, { "x", "flag" });

        Assert::IsTrue(table.getThing(4) == std::unordered_set<std::string>{});
    }

    TEST_METHOD(insertGetBasic) {
        PKB_Map_IfWhile table;
        table.insertThing(7, { "x", "flag" });

        Assert::IsTrue(table.getThing(7) == std::unordered_set<std::string>{ "x", "flag" });
        Assert::IsFalse(table.getThing(7) == std::unordered_set<std::string>{"y", "flag"});
    }

    TEST_METHOD(getSize) {
        PKB_Map_IfWhile table;
        table.insertThing(7, { "x", "flag" });
        table.insertThing(10, { "count" });
        Assert::IsTrue(table.getSize() == 2);
        Assert::IsFalse(table.getSize() == 3);
    }

    TEST_METHOD(getArea) {
        PKB_Map_IfWhile table;

        table.insertThing(7, { "x", "flag" });
        table.insertThing(10, { "count" });
        Assert::IsTrue(table.getArea() == 3);
        Assert::IsFalse(table.getArea() == 2);
    }

    TEST_METHOD(hasKey) {
        PKB_Map_IfWhile table;
        table.insertThing(7, { "x", "flag" });
        table.insertThing(10, { "count" });
        Assert::IsTrue(table.hasKey(7));
        Assert::IsFalse(table.hasKey(6));
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_IfWhile table;

        table.insertThing(7, { "x", "flag" });
        table.insertThing(10, { "count" });
        Assert::IsTrue(table.getAllKeys() == std::vector<int>{ 7, 10 });
        Assert::IsFalse(table.getAllKeys() == std::vector<int>{ 7, 11 });
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_IfWhile table;
        table.insertThing(7, { "x", "flag" });
        table.insertThing(10, { "count" });

        Assert::IsTrue(table.getAllValues() == std::vector<std::unordered_set<std::string>>{ {"x", "flag"}, { "count" } });
        Assert::IsFalse(table.getAllValues() == std::vector<std::unordered_set<std::string>>{ {"x", "bird"}, { "count" }  });
    }

    TEST_METHOD(insert) {
        PKB_Map_IfWhile table;
        table.insertThing(7, { "x" });
        table.insertThing(10, { "count" });
        table.insertThing(10, { "cenX" });
        table.insertThing(3, { "count" });
        table.insertThing(-9, { "7", "flag" });
        table.insertThing(99999, { "-30" });

        std::unordered_map<int, std::unordered_set<std::string>> testTable =
        { {7, {"x"}}, {10, {"count", "cenX"}}, {3, {"count"}}, {-9, {"7","flag"}}, {99999, { "-30" }} };

        bool testPassed = true;
        for (auto element : testTable) {
            if (table.getThing(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[33] = { "365", "77" };

        testPassed = true;
        for (auto element : testTable) {
            if (table.getThing(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);

        testTable.clear();
    }

    TEST_METHOD(isIfSet) {
        PKB_Map_IfWhile table;
        table.insertThing(7, { "x", "y", "z" });
        table.insertThing(8, { "x", "z" });
        table.insertThing(17, { "x" });
        table.insertThing(10, { "count" });
        table.insertThing(10, { "cenX" });

        Assert::IsTrue(table.isThing(7, std::unordered_set<std::string>{ "x", "y", "z" }));
        Assert::IsTrue(table.isThing(7, std::unordered_set<std::string>{ "x", "z" }));
        Assert::IsTrue(table.isThing(7, std::unordered_set<std::string>{ "y" }));
        Assert::IsFalse(table.isThing(7, std::unordered_set<std::string>{ "a" }));
        Assert::IsFalse(table.isThing(9, std::unordered_set<std::string>{ "y" }));
    }

    TEST_METHOD(isIf) {
        PKB_Map_IfWhile table;
        table.insertThing(7, { "x", "y", "z" });
        table.insertThing(8, { "x", "z" });
        table.insertThing(17, { "x" });
        table.insertThing(10, { "count" });
        table.insertThing(10, { "cenX" });

        Assert::IsTrue(table.isThing(7, "x"));
        Assert::IsTrue(table.isThing(7, "y"));
        Assert::IsFalse(table.isThing(7, "a"));
        Assert::IsFalse(table.isThing(1, "x"));
    }
    };

    TEST_CLASS(TestPKB_Map_AAstarCCstarFstarNNstarPstar) {
public:
    TEST_METHOD(insertDuplicateKey) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;

        table.insertThing(3, { 4, 5 });
        table.insertThing(3, { 4, 5 });

        Assert::IsTrue(table.getThing(3) == std::unordered_set<int>{4, 5});
        Assert::IsTrue(table.getSize() == 1);
        Assert::IsTrue(table.getThingReverse(4) == std::unordered_set<int>{3});
        Assert::IsTrue(table.getSizeReverse() == 2);
    }

    TEST_METHOD(getNonExistentKey) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;

        table.insertThing(3, { 4, 5 });

        Assert::IsTrue(table.getThing(4) == std::unordered_set<int>{});
        Assert::IsTrue(table.getThingReverse(77) == std::unordered_set<int>{});
    }

    TEST_METHOD(insertGetBasic) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;
        table.insertThing(3, { 4, 5 });

        Assert::IsTrue(table.getThing(3) == std::unordered_set<int>{4, 5});
        Assert::IsFalse(table.getThing(3) == std::unordered_set<int>{3, 5});
        Assert::IsTrue(table.getThingReverse(4) == std::unordered_set<int>{3});
        Assert::IsTrue(table.getThingReverse(5) == std::unordered_set<int>{3});
        Assert::IsFalse(table.getThingReverse(5) == std::unordered_set<int>{3, 5});
    }

    TEST_METHOD(getSize) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;
        table.insertThing(3, { 4, 5 });
        table.insertThing(4, { 5 });
        Assert::IsTrue(table.getSize() == 2);
        Assert::IsFalse(table.getSize() == 3);
        Assert::IsTrue(table.getSizeReverse() == 2);
        Assert::IsFalse(table.getSizeReverse() == 3);
    }

    TEST_METHOD(getArea) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;
        table.insertThing(3, { 4, 5 });
        table.insertThing(4, { 5 });
        Assert::IsTrue(table.getArea() == 3);
        Assert::IsFalse(table.getArea() == 2);
    }

    TEST_METHOD(hasKey) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;
        table.insertThing(3, { 4, 5 });
        table.insertThing(4, { 5 });
        Assert::IsTrue(table.hasKey(3));
        Assert::IsFalse(table.hasKey(7));
        Assert::IsTrue(table.hasKeyReverse(4));
        Assert::IsTrue(table.hasKeyReverse(5));
        Assert::IsFalse(table.hasKeyReverse(7));
    }

    TEST_METHOD(getAllKeys) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;

        table.insertThing(3, { 4, 5 });
        table.insertThing(4, { 5 });
        Assert::IsTrue(table.getAllKeys() == std::vector<int>{ 3, 4 });
        Assert::IsFalse(table.getAllKeys() == std::vector<int>{ 3, 5 });
        Assert::IsTrue(table.getAllKeysReverse() == std::vector<int>{ 4, 5 });
        Assert::IsFalse(table.getAllKeysReverse() == std::vector<int>{ 3, 5 });
    }

    TEST_METHOD(getAllValues) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;
        table.insertThing(3, { 4, 5 });
        table.insertThing(4, { 5 });

        Assert::IsTrue(table.getAllValues() == std::vector<std::unordered_set<int>>{ {4, 5}, { 5 } });
        Assert::IsFalse(table.getAllValues() == std::vector<std::unordered_set<int>>{ {4, 6}, { 5 } });
        Assert::IsTrue(table.getAllValuesReverse() == std::vector<std::unordered_set<int>>{ {3}, { 3,4 } });
        Assert::IsFalse(table.getAllValuesReverse() == std::vector<std::unordered_set<int>>{ {4}, { 3,4 } });
    }

    TEST_METHOD(insert) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;
        table.insertThing(3, { 5, 6 });
        table.insertThing(3, { 4 });
        table.insertThing(4, { 5 });
        table.insertThing(99999, { 4 });
        table.insertThing(0, { 23 });
        table.insertThing(-3, { 25 });
        table.insertThing(55, { -99 });
        table.insertThing(60, { -3, 5 });

        std::unordered_map<int, std::unordered_set<int>> testTable = { {3, {4, 5, 6}}, {4, {5}}, {99999, {4}}, {0, {23}}, {-3, {25}}, {55, {-99}}, {60, { -3, 5 }} };

        bool testPassed = true;
        for (auto element : testTable) {
            if (table.getThing(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[33] = { 365, 77 };

        testPassed = true;
        for (auto element : testTable) {
            if (table.getThing(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);

        testTable.clear();
        testTable = { {5, {3,4,60}}, {6, {3}}, {4, {3,99999}}, {23, {0}}, {25, {-3}}, {-99, {55}}, {-3, {60}} };

        testPassed = true;
        for (auto element : testTable) {
            if (table.getThingReverse(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsTrue(testPassed);

        testTable[33] = { 365, 77 };

        testPassed = true;
        for (auto element : testTable) {
            if (table.getThingReverse(element.first) != element.second) {
                testPassed = false;
                break;
            }
        }
        Assert::IsFalse(testPassed);
    }

    TEST_METHOD(isCallsSet) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;
        table.insertThing(3, { 5, 6 });
        table.insertThing(3, { 4 });
        table.insertThing(4, { 5 });
        table.insertThing(99999, { 4 });

        Assert::IsTrue(table.isThing(3, { 4, 5, 6 }));
        Assert::IsTrue(table.isThing(3, { 4, 5 }));
        Assert::IsTrue(table.isThing(3, { 4 }));
        Assert::IsFalse(table.isThing(3, { 7 }));
        Assert::IsFalse(table.isThing(9, { 7 }));

        Assert::IsTrue(table.isThingReverse(5, { 3, 4 }));
        Assert::IsTrue(table.isThingReverse(6, { 3 }));
        Assert::IsTrue(table.isThingReverse(4, { 3,99999 }));
        Assert::IsFalse(table.isThingReverse(4, { 7 }));
        Assert::IsFalse(table.isThingReverse(9, { 7 }));
    }

    TEST_METHOD(isCalls) {
        PKB_Map_AAstarCCstarFstarNNstarPstar table;
        table.insertThing(3, { 5, 6 });
        table.insertThing(3, { 4 });
        table.insertThing(4, { 5 });
        table.insertThing(99999, { 4 });

        Assert::IsTrue(table.isThing(3, 5));
        Assert::IsFalse(table.isThing(3, 30));
        Assert::IsFalse(table.isThing(30, 5));

        Assert::IsTrue(table.isThingReverse(5, 3));
        Assert::IsFalse(table.isThingReverse(5, 20));
        Assert::IsFalse(table.isThingReverse(30, 5));
    }
    };

    TEST_CLASS(TestPKB_Map_ModifiesUses) {
        TEST_METHOD(PKB_class_insertDuplicateKey_Uses) {
            PKB_Map_ModifiesUses table;

            table.insertThing(7, { "x", "flag" });
            table.insertThing(7, { "x", "flag" });

            Assert::IsTrue(table.getThing(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsTrue(table.getSize() == 1);
            Assert::IsTrue(table.getThingReverse("x") == std::unordered_set<int>{7});
            Assert::IsTrue(table.getSizeReverse() == 2);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Uses) {
            PKB_Map_ModifiesUses table;

            table.insertThing(7, { "x", "flag" });

            Assert::IsTrue(table.getThing(4) == std::unordered_set<std::string>{});
            Assert::IsTrue(table.getThingReverse("j") == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_Uses) {
            PKB_Map_ModifiesUses table;

            table.insertThing(7, { "x", "flag" });

            Assert::IsTrue(table.getThing(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsFalse(table.getThing(7) == std::unordered_set<std::string>{"y", "flag"});
            Assert::IsTrue(table.getThingReverse("x") == std::unordered_set<int>{7});
            Assert::IsTrue(table.getThingReverse("flag") == std::unordered_set<int>{7});
            Assert::IsFalse(table.getThingReverse("flag") == std::unordered_set<int>{7, 9});
        }

        TEST_METHOD(PKB_class_getSize_Uses) {
            PKB_Map_ModifiesUses table;
            table.insertThing(7, { "x", "flag" });
            table.insertThing(10, { "count" });
            Assert::IsTrue(table.getSize() == 2);
            Assert::IsFalse(table.getSize() == 3);
            Assert::IsTrue(table.getSizeReverse() == 3);
            Assert::IsFalse(table.getSizeReverse() == 2);
        }

        TEST_METHOD(PKB_class_getArea_Uses) {
            PKB_Map_ModifiesUses table;
            table.insertThing(7, { "x", "flag" });
            table.insertThing(10, { "count" });
            Assert::IsTrue(table.getArea() == 3);
            Assert::IsFalse(table.getArea() == 2);
        }

        TEST_METHOD(PKB_class_hasKey_Uses) {
            PKB_Map_ModifiesUses table;
            table.insertThing(7, { "x", "flag" });
            table.insertThing(10, { "count" });
            Assert::IsTrue(table.hasKey(7));
            Assert::IsFalse(table.hasKey(6));
            Assert::IsTrue(table.hasKeyReverse("x"));
            Assert::IsTrue(table.hasKeyReverse("flag"));
            Assert::IsFalse(table.hasKeyReverse("10"));
        }

        TEST_METHOD(PKB_class_getAllKeys_Uses) {
            PKB_Map_ModifiesUses table;

            table.insertThing(7, { "x", "flag" });
            table.insertThing(10, { "count" });
            Assert::IsTrue(table.getAllKeys() == std::vector<int>{ 7, 10 });
            Assert::IsFalse(table.getAllKeys() == std::vector<int>{ 7, 11 });
            Assert::IsTrue(table.getAllKeysReverse() == std::vector<std::string>{ "flag", "x", "count" });
            Assert::IsFalse(table.getAllKeysReverse() == std::vector<std::string>{ "x", "flag", "bird" });
        }

        TEST_METHOD(PKB_class_getAllValues_Uses) {
            PKB_Map_ModifiesUses table;
            table.insertThing(7, { "x", "flag" });
            table.insertThing(10, { "count" });

            Assert::IsTrue(table.getAllValues() == std::vector<std::unordered_set<std::string>>{ {"x", "flag"}, { "count" } });
            Assert::IsFalse(table.getAllValues() == std::vector<std::unordered_set<std::string>>{ {"x", "bird"}, { "count" }  });
            Assert::IsTrue(table.getAllValuesReverse() == std::vector<std::unordered_set<int>>{ {7}, { 7 }, { 10 } });
            Assert::IsFalse(table.getAllValuesReverse() == std::vector<std::unordered_set<int>>{ {7}, { 4 }, { 10 } });
        }

        TEST_METHOD(PKB_class_insert_Uses) {
            PKB_Map_ModifiesUses table;
            table.insertThing(7, { "x" });
            table.insertThing(10, { "count" });
            table.insertThing(10, { "cenX" });
            table.insertThing(3, { "count" });
            table.insertThing(-9, { "7", "flag" });
            table.insertThing(99999, { "-30" });

            std::unordered_map<int, std::unordered_set<std::string>> testTable =
            { {7, {"x"}}, {10, {"count", "cenX"}}, {3, {"count"}}, {-9, {"7","flag"}}, {99999, { "-30" }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (table.getThing(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { "365", "77" };

            testPassed = true;
            for (auto element : testTable) {
                if (table.getThing(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            std::unordered_map<std::string, std::unordered_set<int>> testTable2 =
            { { "x", {7} }, { "count", {10, 3} }, { "cenX", {10} }, { "flag", {-9} }, { "7", {-9} }, { "-30", {99999} } };

            testPassed = true;
            for (auto element : testTable2) {
                if (table.getThingReverse(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable2["33"] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable2) {
                if (table.getThingReverse(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isUsesSet_Uses) {
            PKB_Map_ModifiesUses table;
            table.insertThing(7, { "x", "y", "z" });
            table.insertThing(8, { "x", "z" });
            table.insertThing(17, { "x" });
            table.insertThing(10, { "count" });
            table.insertThing(10, { "cenX" });

            Assert::IsTrue(table.isThing(7, std::unordered_set<std::string>{ "x", "y", "z" }));
            Assert::IsTrue(table.isThing(7, std::unordered_set<std::string>{ "x", "z" }));
            Assert::IsTrue(table.isThing(7, std::unordered_set<std::string>{ "y" }));
            Assert::IsFalse(table.isThing(7, std::unordered_set<std::string>{ "a" }));
            Assert::IsFalse(table.isThing(9, std::unordered_set<std::string>{ "y" }));

            Assert::IsTrue(table.isThingReverse("x", std::unordered_set<int>{ 7, 8, 17 }));
            Assert::IsTrue(table.isThingReverse("x", std::unordered_set<int>{ 7, 17 }));
            Assert::IsTrue(table.isThingReverse("x", std::unordered_set<int>{ 17 }));
            Assert::IsFalse(table.isThingReverse("cenX", std::unordered_set<int>{ 7 }));
            Assert::IsFalse(table.isThingReverse("7", std::unordered_set<int>{ 7 }));
        }

        TEST_METHOD(PKB_class_isUses_Uses) {
            PKB_Map_ModifiesUses table;
            table.insertThing(7, { "x", "y", "z" });
            table.insertThing(8, { "x", "z" });
            table.insertThing(17, { "x" });
            table.insertThing(10, { "count" });
            table.insertThing(10, { "cenX" });

            Assert::IsTrue(table.isThing(7, "x"));
            Assert::IsTrue(table.isThing(7, "y"));
            Assert::IsFalse(table.isThing(7, "a"));
            Assert::IsFalse(table.isThing(1, "x"));

            Assert::IsTrue(table.isThingReverse("x", 8));
            Assert::IsTrue(table.isThingReverse("x", 17));
            Assert::IsFalse(table.isThingReverse("x", 1));
            Assert::IsFalse(table.isThingReverse("a", 10));
        }
    };

    TEST_CLASS(TestPKB_PKB) {
    public:
        void testSize(std::unordered_map<std::string, int> sizeMap) {
            Assert::IsTrue(PKB::getInstance().getSizeProcedure() == sizeMap.at("Procedure"));
            Assert::IsTrue(PKB::getInstance().getSizeStatement() == sizeMap.at("Statement"));
            Assert::IsTrue(PKB::getInstance().getSizeStatementList() == sizeMap.at("StatementList"));
            Assert::IsTrue(PKB::getInstance().getSizeProcedureStatementList() == sizeMap.at("ProcedureStatementList"));
            Assert::IsTrue(PKB::getInstance().getSizeRead() == sizeMap.at("Read"));
            Assert::IsTrue(PKB::getInstance().getSizePrint() == sizeMap.at("Print"));
            Assert::IsTrue(PKB::getInstance().getSizeAssign() == sizeMap.at("Assign"));
            Assert::IsTrue(PKB::getInstance().getSizeCall() == sizeMap.at("Call"));
            Assert::IsTrue(PKB::getInstance().getSizeWhile() == sizeMap.at("While"));
            Assert::IsTrue(PKB::getInstance().getSizeIf() == sizeMap.at("If"));
            Assert::IsTrue(PKB::getInstance().getSizeVariable() == sizeMap.at("Variable"));
            Assert::IsTrue(PKB::getInstance().getSizeConstant() == sizeMap.at("Constant"));

            Assert::IsTrue(PKB::getInstance().getSizeFollows() == sizeMap.at("Follows"));
            Assert::IsTrue(PKB::getInstance().getSizeFollowedBy() == sizeMap.at("FollowedBy"));
            Assert::IsTrue(PKB::getInstance().getSizeFollowsStar() == sizeMap.at("FollowsStar"));
            Assert::IsTrue(PKB::getInstance().getSizeFollowedByStar() == sizeMap.at("FollowedByStar"));
            Assert::IsTrue(PKB::getInstance().getSizeParent() == sizeMap.at("Parent"));
            Assert::IsTrue(PKB::getInstance().getSizeChild() == sizeMap.at("Child"));
            Assert::IsTrue(PKB::getInstance().getSizeParentStar() == sizeMap.at("ParentStar"));
            Assert::IsTrue(PKB::getInstance().getSizeChildStar() == sizeMap.at("ChildStar"));
            Assert::IsTrue(PKB::getInstance().getSizeUses() == sizeMap.at("Uses"));
            Assert::IsTrue(PKB::getInstance().getSizeUsedBy() == sizeMap.at("UsedBy"));
            Assert::IsTrue(PKB::getInstance().getSizeModifies() == sizeMap.at("Modifies"));
            Assert::IsTrue(PKB::getInstance().getSizeModifiedBy() == sizeMap.at("ModifiedBy"));
            Assert::IsTrue(PKB::getInstance().getSizeProcedureUses() == sizeMap.at("ProcedureUses"));
            Assert::IsTrue(PKB::getInstance().getSizeProcedureUsedBy() == sizeMap.at("ProcedureUsedBy"));
            Assert::IsTrue(PKB::getInstance().getSizeProcedureModifies() == sizeMap.at("ProcedureModifies"));
            Assert::IsTrue(PKB::getInstance().getSizeProcedureModifiedBy() == sizeMap.at("ProcedureModifiedBy"));

            Assert::IsTrue(PKB::getInstance().getSizeCalls() == sizeMap.at("Calls"));
            Assert::IsTrue(PKB::getInstance().getSizeCalledBy() == sizeMap.at("CalledBy"));
            Assert::IsTrue(PKB::getInstance().getSizeCallsStar() == sizeMap.at("CallsStar"));
            Assert::IsTrue(PKB::getInstance().getSizeCalledByStar() == sizeMap.at("CalledByStar"));
            Assert::IsTrue(PKB::getInstance().getSizeNext() == sizeMap.at("Next"));
            Assert::IsTrue(PKB::getInstance().getSizePrevious() == sizeMap.at("Previous"));
        }

        TEST_METHOD(PKB_class_tableIndependence_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("a");
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 1},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "a");
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 1 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_StatementList) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatementList(1, { 1 });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 1 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_ProcedureStatementList) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedureStatementList(1, { 1 });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 1 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "s");
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 1 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "s");
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 1 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Assign) {
            PKB::getInstance().clear();

            PKB::getInstance().insertAssignLHS(1, "s");
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 1 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_While) {
            PKB::getInstance().clear();

            PKB::getInstance().insertWhile(1, { "s" });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 1 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_If) {
            PKB::getInstance().clear();

            PKB::getInstance().insertIf(1, { "s" });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 1 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("s");
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 1 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Constant) {
            PKB::getInstance().clear();

            PKB::getInstance().insertConstant(1, { 1 });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 1 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Follows) {
            PKB::getInstance().clear();

            PKB::getInstance().insertFollows(NULL, NULL);
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 1 },
                { "FollowedBy", 1 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_FollowsStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertFollowsStar(1, { 1 });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 1 },
                { "FollowedByStar", 1 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Parent) {
            PKB::getInstance().clear();

            PKB::getInstance().insertParent(1, { 1 });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 1 },
                { "Child", 1 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_ParentStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertParentStar(1, { 1 });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 1 },
                { "ChildStar", 1 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Uses) {
            PKB::getInstance().clear();

            PKB::getInstance().insertUses(1, { "a" });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 1 },
                { "UsedBy", 1 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Modifies) {
            PKB::getInstance().clear();

            PKB::getInstance().insertModifies(1, { "a" });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 1 },
                { "ModifiedBy", 1 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_ProcedureUses) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedureUses(1, { "a" });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 1 },
                { "ProcedureUsedBy", 1 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_ProcedureModifies) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedureModifies(1, { "a" });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 1 },
                { "ProcedureModifiedBy", 1 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Calls) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCalls(1, { 1 });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 1 },
                { "CalledBy", 1 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_CallsStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCallsStar(1, {1});
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 1 },
                { "CalledByStar", 1 },
                { "Next", 0 },
                { "Previous", 0 }});
        }

        TEST_METHOD(PKB_class_tableIndependence_Next) {
            PKB::getInstance().clear();

            PKB::getInstance().insertNext(1, { 1 });
            testSize(std::unordered_map<std::string, int>{ {"Procedure", 0},
                { "Statement", 0 },
                { "StatementList", 0 },
                { "ProcedureStatementList", 0 },
                { "Read", 0 },
                { "Print", 0 },
                { "Assign", 0 },
                { "Call", 0 },
                { "While", 0 },
                { "If", 0 },
                { "Variable", 0 },
                { "Constant", 0 },

                { "Follows", 0 },
                { "FollowedBy", 0 },
                { "FollowsStar", 0 },
                { "FollowedByStar", 0 },
                { "Parent", 0 },
                { "Child", 0 },
                { "ParentStar", 0 },
                { "ChildStar", 0 },
                { "Uses", 0 },
                { "UsedBy", 0 },
                { "Modifies", 0 },
                { "ModifiedBy", 0 },
                { "ProcedureUses", 0 },
                { "ProcedureUsedBy", 0 },
                { "ProcedureModifies", 0 },
                { "ProcedureModifiedBy", 0 },

                { "Calls", 0 },
                { "CalledBy", 0 },
                { "CallsStar", 0 },
                { "CalledByStar", 0 },
                { "Next", 1 },
                { "Previous", 1 }});
        }

        TEST_METHOD(PKB_class_insertNonExistentIfWhile) {
            PKB::getInstance().clear();
            bool errorThrown = false;

            try {
                PKB::getInstance().insertIfWhile(1, "statement2");
            }
            catch (std::string error) {
                Logger::WriteMessage(error.c_str());
                Assert::IsTrue(error == "No if or while table entry exists at lineNumber 1!");
                errorThrown = true;
            }
            Assert::IsTrue(errorThrown);

            PKB::getInstance().clear();
        }

        TEST_METHOD(PKB_class_insertIfWhile) {
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertWhile(1, { "statement1" });
                PKB::getInstance().insertIfWhile(1, { "statement2" });
            }
            catch (...) {
                Logger::WriteMessage("Error in test!");
                Assert::IsTrue(false);
            }
            Assert::IsTrue(PKB::getInstance().getIf(1) == std::unordered_set<std::string>{});
            Assert::IsTrue(PKB::getInstance().getSizeIf() == 0);
            Assert::IsTrue(PKB::getInstance().getWhile(1) == std::unordered_set<std::string>{"statement1", "statement2"});
            Assert::IsTrue(PKB::getInstance().getSizeWhile() == 1);

            PKB::getInstance().clear();
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Assign) {
            bool errorThrown = false;
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignLHS(3, "y");
            }
            catch (std::string error) {
                Logger::WriteMessage(error.c_str());
                Assert::IsTrue(error == "Entry already exists at lineNumber 3!");
                errorThrown = true;
            }
            Assert::IsTrue(errorThrown);
        }

        TEST_METHOD(PKB_class_insertNonExistentRHS_Assign) {
            bool errorThrown = false;
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignRHS(4, "y");
            }
            catch (std::string error) {
                Logger::WriteMessage(error.c_str());
                Assert::IsTrue(error == "No entry exists at lineNumber 4!");
                errorThrown = true;
            }
            Assert::IsTrue(errorThrown);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Assign) {
            bool errorThrown = false;
            PKB::getInstance().clear();
            PKB::getInstance().insertAssignLHS(3, "x");
            Assert::IsTrue(PKB::getInstance().getAssign(4) == std::pair<std::string, std::string>{"", ""});
        }

        TEST_METHOD(PKB_class_insertGetLHS_Assign) {
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignLHS(4, "y");
                Assert::IsTrue(PKB::getInstance().getAssign(3) == std::pair<std::string, std::string>{ "x", "" });
                Assert::IsFalse(PKB::getInstance().getAssign(3) == std::pair<std::string, std::string>{ "x", "a + c" });
                Assert::IsFalse(PKB::getInstance().getAssign(3) == std::pair<std::string, std::string>{ "y", "" });
            }
            catch (...) {
                Logger::WriteMessage("Error in test!");
                Assert::IsTrue(false);
            }
        }

        TEST_METHOD(PKB_class_insertGetRHS_Assign) {
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignRHS(3, "x + 1");
                PKB::getInstance().insertAssignLHS(4, "x");
                PKB::getInstance().insertAssignRHS(4, "x + x");

                Assert::IsTrue(PKB::getInstance().getAssign(3) == std::pair<std::string, std::string>{ "x", "x + 1" });
                Assert::IsTrue(PKB::getInstance().getAssign(4) == std::pair<std::string, std::string>{ "x", "x + x" });
                Assert::IsFalse(PKB::getInstance().getAssign(3) == std::pair<std::string, std::string>{ "x", "x + x" });
                Assert::IsFalse(PKB::getInstance().getAssign(3) == std::pair<std::string, std::string>{ "y", "a + b" });
            }
            catch (...) {
                Logger::WriteMessage("Error in test!");
                Assert::IsTrue(false);
            }
        }

        TEST_METHOD(PKB_class_getSize_Assign) {
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignRHS(3, "x + 1");
                PKB::getInstance().insertAssignLHS(4, "x");
                PKB::getInstance().insertAssignRHS(4, "x + x");
                Assert::IsTrue(PKB::getInstance().getSizeAssign() == 2);
                Assert::IsFalse(PKB::getInstance().getSizeAssign() == 3);
            }
            catch (...) {
                Logger::WriteMessage("Error in test!");
                Assert::IsTrue(false);
            }
        }

        TEST_METHOD(PKB_class_hasKey_Assign) {
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignLHS(4, "y");
                Assert::IsTrue(PKB::getInstance().hasKeyAssign(3));
                Assert::IsFalse(PKB::getInstance().hasKeyAssign(7));
            }
            catch (...) {
                Logger::WriteMessage("Error in test!");
                Assert::IsTrue(false);
            }
        }

        TEST_METHOD(PKB_class_getAllKeys_Assign) {
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignLHS(4, "y");
                Assert::IsTrue(PKB::getInstance().getAllKeysAssign() == std::vector<int>{ 3, 4 });
                Assert::IsFalse(PKB::getInstance().getAllKeysAssign() == std::vector<int>{ 3, 5 });
            }
            catch (...) {
                Logger::WriteMessage("Error in test!");
                Assert::IsTrue(false);
            }
        }

        TEST_METHOD(PKB_class_getAllValues_Assign) {
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignLHS(4, "y");
                PKB::getInstance().insertAssignRHS(4, "a * c");

                Assert::IsTrue(PKB::getInstance().getAllValuesAssign() == std::vector<std::pair<std::string, std::string>> { { "x", "" }, { "y", "a * c" }});
                Assert::IsFalse(PKB::getInstance().getAllValuesAssign() == std::vector<std::pair<std::string, std::string>> { { "x", "a + b" }, { "y", "a * c" }, { "z", "a * c" }});
            }
            catch (...) {
                Logger::WriteMessage("Error in test!");
                Assert::IsTrue(false);
            }
        }

        TEST_METHOD(PKB_class_insert_Assign) {
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertAssignLHS(3, "x");
                PKB::getInstance().insertAssignLHS(4, "y");
                PKB::getInstance().insertAssignLHS(99999, "z");
                PKB::getInstance().insertAssignLHS(0, "x");
                PKB::getInstance().insertAssignLHS(-3, "x");
                PKB::getInstance().insertAssignLHS(55, "x");
                PKB::getInstance().insertAssignLHS(60, "x");
                PKB::getInstance().insertAssignRHS(3, "a + b");
                PKB::getInstance().insertAssignRHS(4, "a * c");
                PKB::getInstance().insertAssignRHS(99999, "a * b");
                PKB::getInstance().insertAssignRHS(0, "a + b");
                PKB::getInstance().insertAssignRHS(-3, "a + b");
                PKB::getInstance().insertAssignRHS(55, "a + b");
                PKB::getInstance().insertAssignRHS(60, "a + b");

                std::unordered_map<int, std::pair<std::string, std::string>> testTable = { {3, {"x", "a + b"}}, {4, { "y", "a * c" }},
                    {99999, { "z", "a * b" }}, {0, { "x", "a + b" }}, {-3, { "x", "a + b" }}, {55, { "x", "a + b" }}, {60, { "x", "a + b" }} };

                bool testPassed = true;
                for (auto element : testTable) {
                    if (PKB::getInstance().getAssign(element.first) != element.second) {
                        testPassed = false;
                        break;
                    }
                }
                Assert::IsTrue(testPassed);

                testTable[33] = { "d", "c / t" };

                testPassed = true;
                for (auto element : testTable) {
                    if (PKB::getInstance().getAssign(element.first) != element.second) {
                        testPassed = false;
                        break;
                    }
                }
                Assert::IsFalse(testPassed);
            }
            catch (...) {
                Logger::WriteMessage("Error in test!");
                Assert::IsTrue(false);
            }
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Follows) {
            bool errorThrown = false;
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertFollows(3, 4);
                PKB::getInstance().insertFollows(3, 5);
            }
            catch (std::string error) {
                Logger::WriteMessage(error.c_str());
                Assert::IsTrue(error == "Entry already exists at lineNumber 3!");
                errorThrown = true;
            }
            Assert::IsTrue(errorThrown);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Follows) {
            bool errorThrown = false;
            PKB::getInstance().clear();
            PKB::getInstance().insertFollows(3, 4);
            Assert::IsTrue(PKB::getInstance().getFollows(4) == -1);
            Assert::IsTrue(PKB::getInstance().getFollowedBy(77) == -1);
        }

        TEST_METHOD(PKB_class_insertGetBasic_Follows) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollows(3, 4);

            Assert::IsTrue(PKB::getInstance().getFollows(3) == 4);
            Assert::IsFalse(PKB::getInstance().getFollows(3) == 5);
            Assert::IsTrue(PKB::getInstance().getFollowedBy(4) == 3);
            Assert::IsFalse(PKB::getInstance().getFollowedBy(4) == 5);
        }

        TEST_METHOD(PKB_class_getSize_Follows) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollows(3, 4);
            PKB::getInstance().insertFollows(4, 5);
            Assert::IsTrue(PKB::getInstance().getSizeFollows() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeFollows() == 3);
            Assert::IsTrue(PKB::getInstance().getSizeFollowedBy() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeFollowedBy() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Follows) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollows(3, 4);
            PKB::getInstance().insertFollows(4, 5);
            Assert::IsTrue(PKB::getInstance().hasKeyFollows(3));
            Assert::IsFalse(PKB::getInstance().hasKeyFollows(7));
            Assert::IsTrue(PKB::getInstance().hasKeyFollowedBy(4));
            Assert::IsFalse(PKB::getInstance().hasKeyFollowedBy(7));
        }

        TEST_METHOD(PKB_class_getAllKeys_Follows) {
            PKB::getInstance().clear();

            PKB::getInstance().insertFollows(3, 4);
            PKB::getInstance().insertFollows(4, 5);
            Assert::IsTrue(PKB::getInstance().getAllKeysFollows() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysFollows() == std::vector<int>{ 3, 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysFollowedBy() == std::vector<int>{ 4, 5 });
            Assert::IsFalse(PKB::getInstance().getAllKeysFollowedBy() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_getAllValues_Follows) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollows(3, 4);
            PKB::getInstance().insertFollows(4, 5);

            Assert::IsTrue(PKB::getInstance().getAllValuesFollows() == std::vector<int>{ 4, 5 });
            Assert::IsFalse(PKB::getInstance().getAllValuesFollows() == std::vector<int>{ 4, 7 });
            Assert::IsTrue(PKB::getInstance().getAllValuesFollowedBy() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllValuesFollowedBy() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_insert_Follows) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollows(3, 4);
            PKB::getInstance().insertFollows(4, 5);
            PKB::getInstance().insertFollows(5, 99999);
            PKB::getInstance().insertFollows(6, 13);
            PKB::getInstance().insertFollows(7, 14);
            PKB::getInstance().insertFollows(11111, 98);
            PKB::getInstance().insertFollows(-3, 67);
            PKB::getInstance().insertFollows(11, -5);

            std::unordered_map<int, int> testTable = { {3, 4}, {4, 5}, {5, 99999}, {6, 13}, {7, 14}, {11111, 98}, {-3, 67}, {11, -5} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getFollows(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = 365;

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getFollows(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            testTable = { {4, 3}, {5, 4}, {99999, 5}, {13, 6}, {14, 7}, {98, 11111}, {67, -3}, {-5, 11} };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getFollowedBy(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getFollowedBy(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isFollows_Follows) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollows(3, 5);
            PKB::getInstance().insertFollows(4, 8);
            PKB::getInstance().insertFollows(99999, 4);

            Assert::IsTrue(PKB::getInstance().isFollows(3, 5));
            Assert::IsFalse(PKB::getInstance().isFollows(3, 30));
            Assert::IsFalse(PKB::getInstance().isFollows(30, 5));

            Assert::IsTrue(PKB::getInstance().isFollowedBy(8, 4));
            Assert::IsFalse(PKB::getInstance().isFollowedBy(8, 20));
            Assert::IsFalse(PKB::getInstance().isFollowedBy(30, 4));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_FollowsStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertFollowsStar(3, { 4, 5 });
            PKB::getInstance().insertFollowsStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getFollowsStar(3) == std::unordered_set<int>{4, 5});
            Assert::IsTrue(PKB::getInstance().getSizeFollowsStar() == 1);
            Assert::IsTrue(PKB::getInstance().getFollowedByStar(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getSizeFollowedByStar() == 2);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_FollowsStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertFollowsStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getFollowsStar(4) == std::unordered_set<int>{});
            Assert::IsTrue(PKB::getInstance().getFollowedByStar(77) == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_FollowsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollowsStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getFollowsStar(3) == std::unordered_set<int>{4, 5});
            Assert::IsFalse(PKB::getInstance().getFollowsStar(3) == std::unordered_set<int>{3, 5});
            Assert::IsTrue(PKB::getInstance().getFollowedByStar(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getFollowedByStar(5) == std::unordered_set<int>{3});
            Assert::IsFalse(PKB::getInstance().getFollowedByStar(5) == std::unordered_set<int>{3, 5});
        }

        TEST_METHOD(PKB_class_getSize_FollowsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollowsStar(3, { 4, 5 });
            PKB::getInstance().insertFollowsStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getSizeFollowsStar() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeFollowsStar() == 3);
            Assert::IsTrue(PKB::getInstance().getSizeFollowedByStar() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeFollowedByStar() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_FollowsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollowsStar(3, { 4, 5 });
            PKB::getInstance().insertFollowsStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().hasKeyFollowsStar(3));
            Assert::IsFalse(PKB::getInstance().hasKeyFollowsStar(7));
            Assert::IsTrue(PKB::getInstance().hasKeyFollowedByStar(4));
            Assert::IsTrue(PKB::getInstance().hasKeyFollowedByStar(5));
            Assert::IsFalse(PKB::getInstance().hasKeyFollowedByStar(7));
        }

        TEST_METHOD(PKB_class_getAllKeys_FollowsStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertFollowsStar(3, { 4, 5 });
            PKB::getInstance().insertFollowsStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysFollowsStar() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysFollowsStar() == std::vector<int>{ 3, 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysFollowedByStar() == std::vector<int>{ 4, 5 });
            Assert::IsFalse(PKB::getInstance().getAllKeysFollowedByStar() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_getAllValues_FollowsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollowsStar(3, { 4, 5 });
            PKB::getInstance().insertFollowsStar(4, { 5 });

            Assert::IsTrue(PKB::getInstance().getAllValuesFollowsStar() == std::vector<std::unordered_set<int>>{ {4, 5}, { 5 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesFollowsStar() == std::vector<std::unordered_set<int>>{ {4, 6}, { 5 } });
            Assert::IsTrue(PKB::getInstance().getAllValuesFollowedByStar() == std::vector<std::unordered_set<int>>{ {3}, { 3,4 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesFollowedByStar() == std::vector<std::unordered_set<int>>{ {4}, { 3,4 } });
        }

        TEST_METHOD(PKB_class_insert_FollowsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollowsStar(3, { 5, 6 });
            PKB::getInstance().insertFollowsStar(3, { 4 });
            PKB::getInstance().insertFollowsStar(4, { 5 });
            PKB::getInstance().insertFollowsStar(99999, { 4 });
            PKB::getInstance().insertFollowsStar(0, { 23 });
            PKB::getInstance().insertFollowsStar(-3, { 25 });
            PKB::getInstance().insertFollowsStar(55, { -99 });
            PKB::getInstance().insertFollowsStar(60, { -3, 5 });

            std::unordered_map<int, std::unordered_set<int>> testTable = { {3, {4, 5, 6}}, {4, {5}}, {99999, {4}}, {0, {23}}, {-3, {25}}, {55, {-99}}, {60, { -3, 5 }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getFollowsStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getFollowsStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            testTable = { {5, {3,4,60}}, {6, {3}}, {4, {3,99999}}, {23, {0}}, {25, {-3}}, {-99, {55}}, {-3, {60}} };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getFollowedByStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getFollowedByStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isFollowsStarSet_FollowsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollowsStar(3, { 5, 6 });
            PKB::getInstance().insertFollowsStar(3, { 4 });
            PKB::getInstance().insertFollowsStar(4, { 5 });
            PKB::getInstance().insertFollowsStar(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isFollowsStar(3, { 4, 5, 6 }));
            Assert::IsTrue(PKB::getInstance().isFollowsStar(3, { 4, 5 }));
            Assert::IsTrue(PKB::getInstance().isFollowsStar(3, { 4 }));
            Assert::IsFalse(PKB::getInstance().isFollowsStar(3, { 7 }));
            Assert::IsFalse(PKB::getInstance().isFollowsStar(9, { 7 }));

            Assert::IsTrue(PKB::getInstance().isFollowedByStar(5, { 3, 4 }));
            Assert::IsTrue(PKB::getInstance().isFollowedByStar(6, { 3 }));
            Assert::IsTrue(PKB::getInstance().isFollowedByStar(4, { 3,99999 }));
            Assert::IsFalse(PKB::getInstance().isFollowedByStar(4, { 7 }));
            Assert::IsFalse(PKB::getInstance().isFollowedByStar(9, { 7 }));
        }

        TEST_METHOD(PKB_class_isFollowsStar_FollowsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertFollowsStar(3, { 5, 6 });
            PKB::getInstance().insertFollowsStar(3, { 4 });
            PKB::getInstance().insertFollowsStar(4, { 5 });
            PKB::getInstance().insertFollowsStar(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isFollowsStar(3, 5));
            Assert::IsFalse(PKB::getInstance().isFollowsStar(3, 30));
            Assert::IsFalse(PKB::getInstance().isFollowsStar(30, 5));

            Assert::IsTrue(PKB::getInstance().isFollowedByStar(5, 3));
            Assert::IsFalse(PKB::getInstance().isFollowedByStar(5, 20));
            Assert::IsFalse(PKB::getInstance().isFollowedByStar(30, 5));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Parent) {
            bool errorThrown = false;
            PKB::getInstance().clear();
            try {
                PKB::getInstance().insertParent(3, 4);
                PKB::getInstance().insertParent(3, 5);
            }
            catch (std::string error) {
                Logger::WriteMessage(error.c_str());
                Assert::IsTrue(error == "Entry already exists at lineNumber 3!");
                errorThrown = true;
            }
            Assert::IsTrue(errorThrown);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Parent) {
            bool errorThrown = false;
            PKB::getInstance().clear();
            PKB::getInstance().insertParent(3, 4);
            Assert::IsTrue(PKB::getInstance().getParent(4) == -1);
            Assert::IsTrue(PKB::getInstance().getChild(77) == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_Parent) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParent(3, 4);

            Assert::IsTrue(PKB::getInstance().getParent(3) == 4);
            Assert::IsFalse(PKB::getInstance().getParent(3) == 5);
            Assert::IsTrue(PKB::getInstance().getChild(4) == std::unordered_set<int>{3});
            Assert::IsFalse(PKB::getInstance().getChild(4) == std::unordered_set<int>{5});
        }

        TEST_METHOD(PKB_class_getSize_Parent) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParent(3, 4);
            PKB::getInstance().insertParent(4, 5);
            Assert::IsTrue(PKB::getInstance().getSizeParent() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeParent() == 3);
            Assert::IsTrue(PKB::getInstance().getSizeChild() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeChild() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Parent) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParent(3, 4);
            PKB::getInstance().insertParent(4, 5);
            Assert::IsTrue(PKB::getInstance().hasKeyParent(3));
            Assert::IsFalse(PKB::getInstance().hasKeyParent(7));
            Assert::IsTrue(PKB::getInstance().hasKeyChild(4));
            Assert::IsFalse(PKB::getInstance().hasKeyChild(7));
        }

        TEST_METHOD(PKB_class_getAllKeys_Parent) {
            PKB::getInstance().clear();

            PKB::getInstance().insertParent(3, 4);
            PKB::getInstance().insertParent(4, 5);
            Assert::IsTrue(PKB::getInstance().getAllKeysParent() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysParent() == std::vector<int>{ 3, 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysChild() == std::vector<int>{ 4, 5 });
            Assert::IsFalse(PKB::getInstance().getAllKeysChild() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_getAllValues_Parent) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParent(3, 4);
            PKB::getInstance().insertParent(4, 5);
            PKB::getInstance().insertParent(2, 5);

            Assert::IsTrue(PKB::getInstance().getAllValuesParent() == std::vector<int>{ 4, 5, 5 });
            Assert::IsFalse(PKB::getInstance().getAllValuesParent() == std::vector<int>{ 4, 7, 5 });
            Assert::IsTrue(PKB::getInstance().getAllValuesChild() == std::vector<std::unordered_set<int>>{ {3}, { 4, 2 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesChild() == std::vector<std::unordered_set<int>>{ {3}, { 2, 5 } });
        }

        TEST_METHOD(PKB_class_insert_Parent) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParent(3, 4);
            PKB::getInstance().insertParent(4, 5);
            PKB::getInstance().insertParent(5, 99999);
            PKB::getInstance().insertParent(6, 4);
            PKB::getInstance().insertParent(7, 14);
            PKB::getInstance().insertParent(11111, 4);
            PKB::getInstance().insertParent(-3, 5);
            PKB::getInstance().insertParent(11, -5);

            std::unordered_map<int, int> testTable = { {3, 4}, {4, 5}, {5, 99999}, {6, 4}, {7, 14}, {11111, 4}, {-3, 5}, {11, -5} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getParent(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = 365;

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getParent(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            std::unordered_map<int, std::unordered_set<int>> testTable2 = { {4, {3, 6, 11111}}, {5, {4, -3}}, {99999, {5}}, {14, {7}}, {-5, {11}} };

            testPassed = true;
            for (auto element : testTable2) {
                if (PKB::getInstance().getChild(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable2[33] = { {365} };

            testPassed = true;
            for (auto element : testTable2) {
                if (PKB::getInstance().getChild(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isParent_Parent) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParent(3, 5);
            PKB::getInstance().insertParent(4, 8);
            PKB::getInstance().insertParent(99999, 4);

            Assert::IsTrue(PKB::getInstance().isParent(3, 5));
            Assert::IsFalse(PKB::getInstance().isParent(3, 30));
            Assert::IsFalse(PKB::getInstance().isParent(30, 5));

            Assert::IsTrue(PKB::getInstance().isChild(8, 4));
            Assert::IsFalse(PKB::getInstance().isChild(8, 20));
            Assert::IsFalse(PKB::getInstance().isChild(30, 4));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_ParentStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertParentStar(3, { 4, 5 });
            PKB::getInstance().insertParentStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getParentStar(3) == std::unordered_set<int>{4, 5});
            Assert::IsTrue(PKB::getInstance().getSizeParentStar() == 1);
            Assert::IsTrue(PKB::getInstance().getChildStar(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getSizeChildStar() == 2);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_ParentStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertParentStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getParentStar(4) == std::unordered_set<int>{});
            Assert::IsTrue(PKB::getInstance().getChildStar(77) == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_ParentStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParentStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getParentStar(3) == std::unordered_set<int>{4, 5});
            Assert::IsFalse(PKB::getInstance().getParentStar(3) == std::unordered_set<int>{3, 5});
            Assert::IsTrue(PKB::getInstance().getChildStar(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getChildStar(5) == std::unordered_set<int>{3});
            Assert::IsFalse(PKB::getInstance().getChildStar(5) == std::unordered_set<int>{3, 5});
        }

        TEST_METHOD(PKB_class_getSize_ParentStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParentStar(3, { 4, 5 });
            PKB::getInstance().insertParentStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getSizeParentStar() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeParentStar() == 3);
            Assert::IsTrue(PKB::getInstance().getSizeChildStar() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeChildStar() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_ParentStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParentStar(3, { 4, 5 });
            PKB::getInstance().insertParentStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().hasKeyParentStar(3));
            Assert::IsFalse(PKB::getInstance().hasKeyParentStar(7));
            Assert::IsTrue(PKB::getInstance().hasKeyChildStar(4));
            Assert::IsTrue(PKB::getInstance().hasKeyChildStar(5));
            Assert::IsFalse(PKB::getInstance().hasKeyChildStar(7));
        }

        TEST_METHOD(PKB_class_getAllKeys_ParentStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertParentStar(3, { 4, 5 });
            PKB::getInstance().insertParentStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysParentStar() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysParentStar() == std::vector<int>{ 3, 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysChildStar() == std::vector<int>{ 4, 5 });
            Assert::IsFalse(PKB::getInstance().getAllKeysChildStar() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_getAllValues_ParentStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParentStar(3, { 4, 5 });
            PKB::getInstance().insertParentStar(4, { 5 });

            Assert::IsTrue(PKB::getInstance().getAllValuesParentStar() == std::vector<std::unordered_set<int>>{ {4, 5}, { 5 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesParentStar() == std::vector<std::unordered_set<int>>{ {4, 6}, { 5 } });
            Assert::IsTrue(PKB::getInstance().getAllValuesChildStar() == std::vector<std::unordered_set<int>>{ {3}, { 3,4 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesChildStar() == std::vector<std::unordered_set<int>>{ {4}, { 3,4 } });
        }

        TEST_METHOD(PKB_class_insert_ParentStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParentStar(3, { 5, 6 });
            PKB::getInstance().insertParentStar(3, { 4 });
            PKB::getInstance().insertParentStar(4, { 5 });
            PKB::getInstance().insertParentStar(99999, { 4 });
            PKB::getInstance().insertParentStar(0, { 23 });
            PKB::getInstance().insertParentStar(-3, { 25 });
            PKB::getInstance().insertParentStar(55, { -99 });
            PKB::getInstance().insertParentStar(60, { -3, 5 });

            std::unordered_map<int, std::unordered_set<int>> testTable = { {3, {4, 5, 6}}, {4, {5}}, {99999, {4}}, {0, {23}}, {-3, {25}}, {55, {-99}}, {60, { -3, 5 }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getParentStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getParentStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            testTable = { {5, {3,4,60}}, {6, {3}}, {4, {3,99999}}, {23, {0}}, {25, {-3}}, {-99, {55}}, {-3, {60}} };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getChildStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getChildStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isParentStarSet_ParentStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParentStar(3, { 5, 6 });
            PKB::getInstance().insertParentStar(3, { 4 });
            PKB::getInstance().insertParentStar(4, { 5 });
            PKB::getInstance().insertParentStar(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isParentStar(3, { 4, 5, 6 }));
            Assert::IsTrue(PKB::getInstance().isParentStar(3, { 4, 5 }));
            Assert::IsTrue(PKB::getInstance().isParentStar(3, { 4 }));
            Assert::IsFalse(PKB::getInstance().isParentStar(3, { 7 }));
            Assert::IsFalse(PKB::getInstance().isParentStar(9, { 7 }));

            Assert::IsTrue(PKB::getInstance().isChildStar(5, { 3, 4 }));
            Assert::IsTrue(PKB::getInstance().isChildStar(6, { 3 }));
            Assert::IsTrue(PKB::getInstance().isChildStar(4, { 3,99999 }));
            Assert::IsFalse(PKB::getInstance().isChildStar(4, { 7 }));
            Assert::IsFalse(PKB::getInstance().isChildStar(9, { 7 }));
        }

        TEST_METHOD(PKB_class_isParentStar_ParentStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertParentStar(3, { 5, 6 });
            PKB::getInstance().insertParentStar(3, { 4 });
            PKB::getInstance().insertParentStar(4, { 5 });
            PKB::getInstance().insertParentStar(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isParentStar(3, 5));
            Assert::IsFalse(PKB::getInstance().isParentStar(3, 30));
            Assert::IsFalse(PKB::getInstance().isParentStar(30, 5));

            Assert::IsTrue(PKB::getInstance().isChildStar(5, 3));
            Assert::IsFalse(PKB::getInstance().isChildStar(5, 20));
            Assert::IsFalse(PKB::getInstance().isChildStar(30, 5));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Uses) {
            PKB::getInstance().clear();

            PKB::getInstance().insertUses(7, { "x", "flag" });
            PKB::getInstance().insertUses(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getUses(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsTrue(PKB::getInstance().getSizeUses() == 1);
            Assert::IsTrue(PKB::getInstance().getUsedBy("x") == std::unordered_set<int>{7});
            Assert::IsTrue(PKB::getInstance().getSizeUsedBy() == 2);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Uses) {
            PKB::getInstance().clear();

            PKB::getInstance().insertUses(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getUses(4) == std::unordered_set<std::string>{});
            Assert::IsTrue(PKB::getInstance().getUsedBy("j") == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_Uses) {
            PKB::getInstance().clear();
            PKB::getInstance().insertUses(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getUses(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsFalse(PKB::getInstance().getUses(7) == std::unordered_set<std::string>{"y", "flag"});
            Assert::IsTrue(PKB::getInstance().getUsedBy("x") == std::unordered_set<int>{7});
            Assert::IsTrue(PKB::getInstance().getUsedBy("flag") == std::unordered_set<int>{7});
            Assert::IsFalse(PKB::getInstance().getUsedBy("flag") == std::unordered_set<int>{7, 9});
        }

        TEST_METHOD(PKB_class_getSize_Uses) {
            PKB::getInstance().clear();
            PKB::getInstance().insertUses(7, { "x", "flag" });
            PKB::getInstance().insertUses(10, { "count" });
            Assert::IsTrue(PKB::getInstance().getSizeUses() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeUses() == 3);
            Assert::IsTrue(PKB::getInstance().getSizeUsedBy() == 3);
            Assert::IsFalse(PKB::getInstance().getSizeUsedBy() == 2);
        }

        TEST_METHOD(PKB_class_hasKey_Uses) {
            PKB::getInstance().clear();
            PKB::getInstance().insertUses(7, { "x", "flag" });
            PKB::getInstance().insertUses(10, { "count" });
            Assert::IsTrue(PKB::getInstance().hasKeyUses(7));
            Assert::IsFalse(PKB::getInstance().hasKeyUses(6));
            Assert::IsTrue(PKB::getInstance().hasKeyUsedBy("x"));
            Assert::IsTrue(PKB::getInstance().hasKeyUsedBy("flag"));
            Assert::IsFalse(PKB::getInstance().hasKeyUsedBy("10"));
        }

        TEST_METHOD(PKB_class_getAllKeys_Uses) {
            PKB::getInstance().clear();

            PKB::getInstance().insertUses(7, { "x", "flag" });
            PKB::getInstance().insertUses(10, { "count" });
            Assert::IsTrue(PKB::getInstance().getAllKeysUses() == std::vector<int>{ 7, 10 });
            Assert::IsFalse(PKB::getInstance().getAllKeysUses() == std::vector<int>{ 7, 11 });
            Assert::IsTrue(PKB::getInstance().getAllKeysUsedBy() == std::vector<std::string>{ "x", "flag", "count" });
            Assert::IsFalse(PKB::getInstance().getAllKeysUsedBy() == std::vector<std::string>{ "x", "flag", "bird" });
        }

        TEST_METHOD(PKB_class_getAllValues_Uses) {
            PKB::getInstance().clear();
            PKB::getInstance().insertUses(7, { "x", "flag" });
            PKB::getInstance().insertUses(10, { "count" });

            Assert::IsTrue(PKB::getInstance().getAllValuesUses() == std::vector<std::unordered_set<std::string>>{ {"x", "flag"}, { "count" } });
            Assert::IsFalse(PKB::getInstance().getAllValuesUses() == std::vector<std::unordered_set<std::string>>{ {"x", "bird"}, { "count" }  });
            Assert::IsTrue(PKB::getInstance().getAllValuesUsedBy() == std::vector<std::unordered_set<int>>{ {7}, { 7 }, { 10 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesUsedBy() == std::vector<std::unordered_set<int>>{ {7}, { 4 }, { 10 } });
        }

        TEST_METHOD(PKB_class_insert_Uses) {
            PKB::getInstance().clear();
            PKB::getInstance().insertUses(7, { "x" });
            PKB::getInstance().insertUses(10, { "count" });
            PKB::getInstance().insertUses(10, { "cenX" });
            PKB::getInstance().insertUses(3, { "count" });
            PKB::getInstance().insertUses(-9, { "7", "flag" });
            PKB::getInstance().insertUses(99999, { "-30" });

            std::unordered_map<int, std::unordered_set<std::string>> testTable =
            { {7, {"x"}}, {10, {"count", "cenX"}}, {3, {"count"}}, {-9, {"7","flag"}}, {99999, { "-30" }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getUses(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { "365", "77" };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getUses(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            std::unordered_map<std::string, std::unordered_set<int>> testTable2 =
            { { "x", {7} }, { "count", {10, 3} }, { "cenX", {10} }, { "flag", {-9} }, { "7", {-9} }, { "-30", {99999} } };

            testPassed = true;
            for (auto element : testTable2) {
                if (PKB::getInstance().getUsedBy(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable2["33"] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable2) {
                if (PKB::getInstance().getUsedBy(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isUsesSet_Uses) {
            PKB::getInstance().clear();
            PKB::getInstance().insertUses(7, { "x", "y", "z" });
            PKB::getInstance().insertUses(8, { "x", "z" });
            PKB::getInstance().insertUses(17, { "x" });
            PKB::getInstance().insertUses(10, { "count" });
            PKB::getInstance().insertUses(10, { "cenX" });

            Assert::IsTrue(PKB::getInstance().isUses(7, std::unordered_set<std::string>{ "x", "y", "z" }));
            Assert::IsTrue(PKB::getInstance().isUses(7, std::unordered_set<std::string>{ "x", "z" }));
            Assert::IsTrue(PKB::getInstance().isUses(7, std::unordered_set<std::string>{ "y" }));
            Assert::IsFalse(PKB::getInstance().isUses(7, std::unordered_set<std::string>{ "a" }));
            Assert::IsFalse(PKB::getInstance().isUses(9, std::unordered_set<std::string>{ "y" }));

            Assert::IsTrue(PKB::getInstance().isUsedBy("x", std::unordered_set<int>{ 7, 8, 17 }));
            Assert::IsTrue(PKB::getInstance().isUsedBy("x", std::unordered_set<int>{ 7, 17 }));
            Assert::IsTrue(PKB::getInstance().isUsedBy("x", std::unordered_set<int>{ 17 }));
            Assert::IsFalse(PKB::getInstance().isUsedBy("cenX", std::unordered_set<int>{ 7 }));
            Assert::IsFalse(PKB::getInstance().isUsedBy("7", std::unordered_set<int>{ 7 }));
        }

        TEST_METHOD(PKB_class_isUses_Uses) {
            PKB::getInstance().clear();
            PKB::getInstance().insertUses(7, { "x", "y", "z" });
            PKB::getInstance().insertUses(8, { "x", "z" });
            PKB::getInstance().insertUses(17, { "x" });
            PKB::getInstance().insertUses(10, { "count" });
            PKB::getInstance().insertUses(10, { "cenX" });

            Assert::IsTrue(PKB::getInstance().isUses(7, "x"));
            Assert::IsTrue(PKB::getInstance().isUses(7, "y"));
            Assert::IsFalse(PKB::getInstance().isUses(7, "a"));
            Assert::IsFalse(PKB::getInstance().isUses(1, "x"));

            Assert::IsTrue(PKB::getInstance().isUsedBy("x", 8));
            Assert::IsTrue(PKB::getInstance().isUsedBy("x", 17));
            Assert::IsFalse(PKB::getInstance().isUsedBy("x", 1));
            Assert::IsFalse(PKB::getInstance().isUsedBy("a", 10));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Modifies) {
            PKB::getInstance().clear();

            PKB::getInstance().insertModifies(7, { "x", "flag" });
            PKB::getInstance().insertModifies(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getModifies(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsTrue(PKB::getInstance().getSizeModifies() == 1);
            Assert::IsTrue(PKB::getInstance().getModifiedBy("x") == std::unordered_set<int>{7});
            Assert::IsTrue(PKB::getInstance().getSizeModifiedBy() == 2);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Modifies) {
            PKB::getInstance().clear();

            PKB::getInstance().insertModifies(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getModifies(4) == std::unordered_set<std::string>{});
            Assert::IsTrue(PKB::getInstance().getModifiedBy("j") == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_Modifies) {
            PKB::getInstance().clear();
            PKB::getInstance().insertModifies(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getModifies(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsFalse(PKB::getInstance().getModifies(7) == std::unordered_set<std::string>{"y", "flag"});
            Assert::IsTrue(PKB::getInstance().getModifiedBy("x") == std::unordered_set<int>{7});
            Assert::IsTrue(PKB::getInstance().getModifiedBy("flag") == std::unordered_set<int>{7});
            Assert::IsFalse(PKB::getInstance().getModifiedBy("flag") == std::unordered_set<int>{7, 9});
        }

        TEST_METHOD(PKB_class_getSize_Modifies) {
            PKB::getInstance().clear();
            PKB::getInstance().insertModifies(7, { "x", "flag" });
            PKB::getInstance().insertModifies(10, { "count" });
            Assert::IsTrue(PKB::getInstance().getSizeModifies() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeModifies() == 3);
            Assert::IsTrue(PKB::getInstance().getSizeModifiedBy() == 3);
            Assert::IsFalse(PKB::getInstance().getSizeModifiedBy() == 2);
        }

        TEST_METHOD(PKB_class_hasKey_Modifies) {
            PKB::getInstance().clear();
            PKB::getInstance().insertModifies(7, { "x", "flag" });
            PKB::getInstance().insertModifies(10, { "count" });
            Assert::IsTrue(PKB::getInstance().hasKeyModifies(7));
            Assert::IsFalse(PKB::getInstance().hasKeyModifies(6));
            Assert::IsTrue(PKB::getInstance().hasKeyModifiedBy("x"));
            Assert::IsTrue(PKB::getInstance().hasKeyModifiedBy("flag"));
            Assert::IsFalse(PKB::getInstance().hasKeyModifiedBy("10"));
        }

        TEST_METHOD(PKB_class_getAllKeys_Modifies) {
            PKB::getInstance().clear();

            PKB::getInstance().insertModifies(7, { "x", "flag" });
            PKB::getInstance().insertModifies(10, { "count" });
            Assert::IsTrue(PKB::getInstance().getAllKeysModifies() == std::vector<int>{ 7, 10 });
            Assert::IsFalse(PKB::getInstance().getAllKeysModifies() == std::vector<int>{ 7, 11 });
            Assert::IsTrue(PKB::getInstance().getAllKeysModifiedBy() == std::vector<std::string>{ "x", "flag", "count" });
            Assert::IsFalse(PKB::getInstance().getAllKeysModifiedBy() == std::vector<std::string>{ "x", "flag", "bird" });
        }

        TEST_METHOD(PKB_class_getAllValues_Modifies) {
            PKB::getInstance().clear();
            PKB::getInstance().insertModifies(7, { "x", "flag" });
            PKB::getInstance().insertModifies(10, { "count" });

            Assert::IsTrue(PKB::getInstance().getAllValuesModifies() == std::vector<std::unordered_set<std::string>>{ {"x", "flag"}, { "count" } });
            Assert::IsFalse(PKB::getInstance().getAllValuesModifies() == std::vector<std::unordered_set<std::string>>{ {"x", "bird"}, { "count" }  });
            Assert::IsTrue(PKB::getInstance().getAllValuesModifiedBy() == std::vector<std::unordered_set<int>>{ {7}, { 7 }, { 10 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesModifiedBy() == std::vector<std::unordered_set<int>>{ {7}, { 4 }, { 10 } });
        }

        TEST_METHOD(PKB_class_insert_Modifies) {
            PKB::getInstance().clear();
            PKB::getInstance().insertModifies(7, { "x" });
            PKB::getInstance().insertModifies(10, { "count" });
            PKB::getInstance().insertModifies(10, { "cenX" });
            PKB::getInstance().insertModifies(3, { "count" });
            PKB::getInstance().insertModifies(-9, { "7", "flag" });
            PKB::getInstance().insertModifies(99999, { "-30" });

            std::unordered_map<int, std::unordered_set<std::string>> testTable =
            { {7, {"x"}}, {10, {"count", "cenX"}}, {3, {"count"}}, {-9, {"7","flag"}}, {99999, { "-30" }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getModifies(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { "365", "77" };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getModifies(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            std::unordered_map<std::string, std::unordered_set<int>> testTable2 =
            { { "x", {7} }, { "count", {10, 3} }, { "cenX", {10} }, { "flag", {-9} }, { "7", {-9} }, { "-30", {99999} } };

            testPassed = true;
            for (auto element : testTable2) {
                if (PKB::getInstance().getModifiedBy(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable2["33"] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable2) {
                if (PKB::getInstance().getModifiedBy(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isModifiesSet_Modifies) {
            PKB::getInstance().clear();
            PKB::getInstance().insertModifies(7, { "x", "y", "z" });
            PKB::getInstance().insertModifies(8, { "x", "z" });
            PKB::getInstance().insertModifies(17, { "x" });
            PKB::getInstance().insertModifies(10, { "count" });
            PKB::getInstance().insertModifies(10, { "cenX" });

            Assert::IsTrue(PKB::getInstance().isModifies(7, std::unordered_set<std::string>{ "x", "y", "z" }));
            Assert::IsTrue(PKB::getInstance().isModifies(7, std::unordered_set<std::string>{ "x", "z" }));
            Assert::IsTrue(PKB::getInstance().isModifies(7, std::unordered_set<std::string>{ "y" }));
            Assert::IsFalse(PKB::getInstance().isModifies(7, std::unordered_set<std::string>{ "a" }));
            Assert::IsFalse(PKB::getInstance().isModifies(9, std::unordered_set<std::string>{ "y" }));

            Assert::IsTrue(PKB::getInstance().isModifiedBy("x", std::unordered_set<int>{ 7, 8, 17 }));
            Assert::IsTrue(PKB::getInstance().isModifiedBy("x", std::unordered_set<int>{ 7, 17 }));
            Assert::IsTrue(PKB::getInstance().isModifiedBy("x", std::unordered_set<int>{ 17 }));
            Assert::IsFalse(PKB::getInstance().isModifiedBy("cenX", std::unordered_set<int>{ 7 }));
            Assert::IsFalse(PKB::getInstance().isModifiedBy("7", std::unordered_set<int>{ 7 }));
        }

        TEST_METHOD(PKB_class_isModifies_Modifies) {
            PKB::getInstance().clear();
            PKB::getInstance().insertModifies(7, { "x", "y", "z" });
            PKB::getInstance().insertModifies(8, { "x", "z" });
            PKB::getInstance().insertModifies(17, { "x" });
            PKB::getInstance().insertModifies(10, { "count" });
            PKB::getInstance().insertModifies(10, { "cenX" });

            Assert::IsTrue(PKB::getInstance().isModifies(7, "x"));
            Assert::IsTrue(PKB::getInstance().isModifies(7, "y"));
            Assert::IsFalse(PKB::getInstance().isModifies(7, "a"));
            Assert::IsFalse(PKB::getInstance().isModifies(1, "x"));

            Assert::IsTrue(PKB::getInstance().isModifiedBy("x", 8));
            Assert::IsTrue(PKB::getInstance().isModifiedBy("x", 17));
            Assert::IsFalse(PKB::getInstance().isModifiedBy("x", 1));
            Assert::IsFalse(PKB::getInstance().isModifiedBy("a", 10));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_StatementList) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatementList(3, { 4, 5 });
            PKB::getInstance().insertStatementList(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getStatementList(3) == std::unordered_set<int>{4, 5});
            Assert::IsTrue(PKB::getInstance().getSizeStatementList() == 1);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_StatementList) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatementList(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getStatementList(4) == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_StatementList) {
            PKB::getInstance().clear();
            PKB::getInstance().insertStatementList(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getStatementList(3) == std::unordered_set<int>{4, 5});
            Assert::IsFalse(PKB::getInstance().getStatementList(3) == std::unordered_set<int>{3, 5});
        }

        TEST_METHOD(PKB_class_insertGetKey_StatementList) {
            PKB::getInstance().clear();
            PKB::getInstance().insertStatementList(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getKeyStatementList(4) == 3);
            Assert::IsTrue(PKB::getInstance().getKeyStatementList(5) == 3);
            Assert::IsFalse(PKB::getInstance().getKeyStatementList(4) == 4);
            Assert::IsFalse(PKB::getInstance().getKeyStatementList(3) == 4);
        }

        TEST_METHOD(PKB_class_getSize_StatementList) {
            PKB::getInstance().clear();
            PKB::getInstance().insertStatementList(3, { 4, 5 });
            PKB::getInstance().insertStatementList(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getSizeStatementList() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeStatementList() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_StatementList) {
            PKB::getInstance().clear();
            PKB::getInstance().insertStatementList(3, { 4, 5 });
            PKB::getInstance().insertStatementList(4, { 5 });
            Assert::IsTrue(PKB::getInstance().hasKeyStatementList(3));
            Assert::IsFalse(PKB::getInstance().hasKeyStatementList(7));
        }

        TEST_METHOD(PKB_class_getAllKeys_StatementList) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatementList(3, { 4, 5 });
            PKB::getInstance().insertStatementList(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysStatementList() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysStatementList() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_getAllValues_StatementList) {
            PKB::getInstance().clear();
            PKB::getInstance().insertStatementList(3, { 4, 5 });
            PKB::getInstance().insertStatementList(4, { 5 });

            Assert::IsTrue(PKB::getInstance().getAllValuesStatementList() == std::vector<std::unordered_set<int>>{ {4, 5}, { 5 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesStatementList() == std::vector<std::unordered_set<int>>{ {4, 6}, { 5 } });
        }

        TEST_METHOD(PKB_class_insert_StatementList) {
            PKB::getInstance().clear();
            PKB::getInstance().insertStatementList(3, { 5, 6 });
            PKB::getInstance().insertStatementList(3, { 4 });
            PKB::getInstance().insertStatementList(4, { 5 });
            PKB::getInstance().insertStatementList(99999, { 4 });
            PKB::getInstance().insertStatementList(0, { 23 });
            PKB::getInstance().insertStatementList(-3, { 25 });
            PKB::getInstance().insertStatementList(55, { -99 });
            PKB::getInstance().insertStatementList(60, { -3, 5 });

            std::unordered_map<int, std::unordered_set<int>> testTable = { {3, {4, 5, 6}}, {4, {5}}, {99999, {4}}, {0, {23}}, {-3, {25}}, {55, {-99}}, {60, { -3, 5 }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getStatementList(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getStatementList(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Constant) {
            PKB::getInstance().clear();

            PKB::getInstance().insertConstant(1, { 4, 5 });
            PKB::getInstance().insertConstant(1, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getConstant(1) == std::unordered_set<int>{ 4, 5 });
            Assert::IsTrue(PKB::getInstance().getSizeConstant() == 1);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Constant) {
            PKB::getInstance().clear();

            PKB::getInstance().insertConstant(1, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getConstant(2) == std::unordered_set<int>{});
            Assert::IsTrue(PKB::getInstance().getConstant(100) == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_Constant) {
            PKB::getInstance().clear();
            PKB::getInstance().insertConstant(100, { 200, 300 });

            Assert::IsTrue(PKB::getInstance().getConstant(100) == std::unordered_set<int>{ 200, 300 });
            Assert::IsFalse(PKB::getInstance().getConstant(10) == std::unordered_set<int>{ 20, 50 });
        }

        TEST_METHOD(PKB_class_getSize_Constant) {
            PKB::getInstance().clear();
            PKB::getInstance().insertConstant(3, { 4, 5 });
            Assert::IsFalse(PKB::getInstance().getSizeConstant() == 2);
            Assert::IsTrue(PKB::getInstance().getSizeConstant() == 1);

        }

        TEST_METHOD(PKB_class_hasKey_Constant) {
            PKB::getInstance().clear();
            PKB::getInstance().insertConstant(3, { 4, 5 });
            Assert::IsTrue(PKB::getInstance().hasKeyConstant(3));
            Assert::IsFalse(PKB::getInstance().hasKeyConstant(10));
        }

        TEST_METHOD(PKB_class_getAllKeys_Constant) {
            PKB::getInstance().clear();

            PKB::getInstance().insertConstant(3, { 4, 5 });
            PKB::getInstance().insertConstant(4, { 6, 7 });
            Assert::IsTrue(PKB::getInstance().getAllKeysConstant() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysConstant() == std::vector<int>{ 3, 6 });
        }

        TEST_METHOD(PKB_class_getAllValues_Constant) {
            PKB::getInstance().clear();
            PKB::getInstance().insertConstant(3, { 4, 5, 6 });
            PKB::getInstance().insertConstant(4, { 1, 2, 3 });

            Assert::IsTrue(PKB::getInstance().getAllValuesConstant() == std::vector<std::unordered_set<int>>{ { 4, 5, 6 }, { 1, 2, 3 }});
            Assert::IsFalse(PKB::getInstance().getAllValuesConstant() == std::vector<std::unordered_set<int>>{ { 5, 6, 7 }});
        }

        TEST_METHOD(PKB_class_insert_Constant) {
            PKB::getInstance().clear();

            PKB::getInstance().insertConstant(3, { 1 });
            PKB::getInstance().insertConstant(3, { 2 });
            PKB::getInstance().insertConstant(4, { 5, 6 });
            PKB::getInstance().insertConstant(100000, { 8 });
            PKB::getInstance().insertConstant(0, { 10 });
            PKB::getInstance().insertConstant(-1, { 100 });
            PKB::getInstance().insertConstant(10, { 20 });
            PKB::getInstance().insertConstant(50, { -30, -10 });

            std::unordered_map<int, std::unordered_set<int>> testTable = { {3, { 1, 2 }}, {4, { 5, 6 }}, {100000, { 8 }}, {0, { 10 }}, {-1, { 100 }}, {10, { 20 }}, {50, { -30, -10 }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getConstant(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[66] = { 70, 100 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getConstant(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
        }

        TEST_METHOD(PKB_class_isConstantSet_Constant) {
            PKB::getInstance().clear();
            PKB::getInstance().insertConstant(3, { 5, 6 });
            PKB::getInstance().insertConstant(4, { 5 });
            PKB::getInstance().insertConstant(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isConstant(3, { 5, 6 }));
            Assert::IsTrue(PKB::getInstance().isConstant(3, { 5 }));
            Assert::IsFalse(PKB::getInstance().isConstant(3, { 4 }));
            Assert::IsFalse(PKB::getInstance().isConstant(3, { 7 }));
            Assert::IsFalse(PKB::getInstance().isConstant(9, { 4 }));
        }

        TEST_METHOD(PKB_class_isConstant_Constant) {
            PKB::getInstance().clear();
            PKB::getInstance().insertConstant(3, { 5, 6 });
            PKB::getInstance().insertConstant(4, { 5 });
            PKB::getInstance().insertConstant(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isConstant(3, 5));
            Assert::IsTrue(PKB::getInstance().isConstant(3, 6));
            Assert::IsTrue(PKB::getInstance().isConstant(4, 5));
            Assert::IsFalse(PKB::getInstance().isConstant(3, 30));
            Assert::IsFalse(PKB::getInstance().isConstant(30, 5));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var");
            int result = PKB::getInstance().insertVariable("var");

            Assert::IsTrue(result == 0);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var");
            Assert::IsTrue(PKB::getInstance().getVariable(2) == "");
        }

        TEST_METHOD(PKB_class_insertGetBasic_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var1");
            PKB::getInstance().insertVariable("var2");
            PKB::getInstance().insertVariable("var3");

            Assert::IsTrue(PKB::getInstance().getVariable(0) == "var1");
            Assert::IsTrue(PKB::getInstance().getVariable(1) == "var2");
            Assert::IsTrue(PKB::getInstance().getVariable(2) == "var3");
            Assert::IsTrue(PKB::getInstance().getVariable(3) == "");
            Assert::IsTrue(PKB::getInstance().getVariable(4) == "");
        }

        TEST_METHOD(PKB_class_getKeyVariable_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var1");
            PKB::getInstance().insertVariable("var2");
            PKB::getInstance().insertVariable("var3");

            Assert::IsTrue(PKB::getInstance().getKeyVariable("var1") == 0);
            Assert::IsTrue(PKB::getInstance().getKeyVariable("var3") == 2);
            Assert::IsFalse(PKB::getInstance().getKeyVariable("var4") == 4);
        }

        TEST_METHOD(PKB_class_getSize_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var1");
            PKB::getInstance().insertVariable("var2");

            Assert::IsTrue(PKB::getInstance().getSizeVariable() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeVariable() == 3);
        }

        TEST_METHOD(PKB_class_hasKey) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var1");
            PKB::getInstance().insertVariable("var2");

            Assert::IsTrue(PKB::getInstance().hasKeyVariable(0));
            Assert::IsFalse(PKB::getInstance().hasKeyVariable(2));
        }

        TEST_METHOD(PKB_class_getAllKeys_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var1");
            PKB::getInstance().insertVariable("var2");

            Assert::IsTrue(PKB::getInstance().getAllKeysVariable() == std::vector<int>{ 0, 1 });
            Assert::IsFalse(PKB::getInstance().getAllKeysVariable() == std::vector<int>{ 1, 2 });
        }

        TEST_METHOD(PKB_class_getAllValues_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var1");
            PKB::getInstance().insertVariable("var2");

            Assert::IsTrue(PKB::getInstance().getAllValuesVariable() == std::vector <std::string> { "var1", "var2" });
            Assert::IsFalse(PKB::getInstance().getAllValuesVariable() == std::vector<std::string>{ "var3", "var4" });
        }

        TEST_METHOD(PKB_class_insert_Variable) {
            PKB::getInstance().clear();

            PKB::getInstance().insertVariable("var1");
            PKB::getInstance().insertVariable("var2");
            PKB::getInstance().insertVariable("x");
            PKB::getInstance().insertVariable("var1");
            PKB::getInstance().insertVariable("y");

            std::unordered_map<int, std::string> testTable = { {0, "var1"}, {1, "var2"}, {2, "x"}, {3, "y"} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getVariable(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[5] = "z";

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getVariable(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(1, "statementType2");

            Assert::IsTrue(PKB::getInstance().getStatement(1) == "statementType1");
            Assert::IsTrue(PKB::getInstance().getSizeStatement() == 1);

        }

        TEST_METHOD(PKB_class_getNonExistentKey_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            Assert::IsTrue(PKB::getInstance().getStatement(2) == "");
        }

        TEST_METHOD(PKB_class_insertGetBasic_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(2, "statementType2");
            PKB::getInstance().insertStatement(3, "statementType3");

            Assert::IsTrue(PKB::getInstance().getStatement(1) == "statementType1");
            Assert::IsTrue(PKB::getInstance().getStatement(2) == "statementType2");
            Assert::IsTrue(PKB::getInstance().getStatement(3) == "statementType3");
            Assert::IsTrue(PKB::getInstance().getStatement(4) == "");
            Assert::IsTrue(PKB::getInstance().getStatement(0) == "");
        }

        TEST_METHOD(PKB_class_isStatementType_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(2, "statementType2");

            Assert::IsTrue(PKB::getInstance().isStatement(1, "statementType1") == true);
            Assert::IsTrue(PKB::getInstance().isStatement(2, "statementType4") == false);
        }

        TEST_METHOD(PKB_class_getTypeKeysStatement_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(2, "statementType1");
            PKB::getInstance().insertStatement(3, "statementType3");

            Assert::IsTrue(PKB::getInstance().getKeysStatement("statementType1") == std::unordered_set<int>{ 1, 2 });
            Assert::IsTrue(PKB::getInstance().getKeysStatement("statementType3") == std::unordered_set<int>{ 3 });
            Assert::IsTrue(PKB::getInstance().getKeysStatement("statementType4") == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_getSize_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(2, "statementType2");

            Assert::IsTrue(PKB::getInstance().getSizeStatement() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeStatement() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(2, "statementType2");

            Assert::IsTrue(PKB::getInstance().hasKeyStatement(1));
            Assert::IsFalse(PKB::getInstance().hasKeyStatement(3));
        }

        TEST_METHOD(PKB_class_getAllKeys_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(2, "statementType2");

            Assert::IsTrue(PKB::getInstance().getAllKeysStatement() == std::vector<int>{ 1, 2 });
            Assert::IsFalse(PKB::getInstance().getAllKeysStatement() == std::vector<int>{ 3, 4 });
        }

        TEST_METHOD(PKB_class_getAllValues_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(2, "statementType2");

            Assert::IsTrue(PKB::getInstance().getAllValuesStatement() == std::vector <std::string> { "statementType1", "statementType2" });
            Assert::IsFalse(PKB::getInstance().getAllValuesStatement() == std::vector<std::string>{ "statementType2", "statementType3" });
        }

        TEST_METHOD(PKB_class_insert_Statement) {
            PKB::getInstance().clear();

            PKB::getInstance().insertStatement(1, "statementType1");
            PKB::getInstance().insertStatement(2, "statementType2");
            PKB::getInstance().insertStatement(3, "x");
            PKB::getInstance().insertStatement(1, "statementType3");
            PKB::getInstance().insertStatement(4, "y");

            std::unordered_map<int, std::string> testTable = { {1, "statementType1"}, {2, "statementType2"}, {3, "x"}, {4, "y"} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getStatement(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[5] = "z";

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getStatement(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("procedure1");
            PKB::getInstance().insertProcedure("procedure1");

            Assert::IsTrue(PKB::getInstance().getProcedure(0) == "procedure1");
            Assert::IsTrue(PKB::getInstance().getSizeProcedure() == 1);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("procedure1");
            Assert::IsTrue(PKB::getInstance().getProcedure(2) == "");
        }

        TEST_METHOD(PKB_class_insertGetBasic_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("procedure1");
            PKB::getInstance().insertProcedure("procedure2");
            PKB::getInstance().insertProcedure("procedure3");

            Assert::IsTrue(PKB::getInstance().getProcedure(0) == "procedure1");
            Assert::IsTrue(PKB::getInstance().getProcedure(1) == "procedure2");
            Assert::IsTrue(PKB::getInstance().getProcedure(2) == "procedure3");
            Assert::IsTrue(PKB::getInstance().getProcedure(3) == "");
            Assert::IsTrue(PKB::getInstance().getProcedure(4) == "");
        }

        TEST_METHOD(PKB_class_getSize_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("procedure1");
            PKB::getInstance().insertProcedure("procedure2");

            Assert::IsTrue(PKB::getInstance().getSizeProcedure() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeProcedure() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("procedure1");
            PKB::getInstance().insertProcedure("procedure2");

            Assert::IsTrue(PKB::getInstance().hasKeyProcedure(0));
            Assert::IsFalse(PKB::getInstance().hasKeyProcedure(2));
        }

        TEST_METHOD(PKB_class_getAllKeys_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("procedure1");
            PKB::getInstance().insertProcedure("procedure2");

            Assert::IsTrue(PKB::getInstance().getAllKeysProcedure() == std::vector<int>{ 0, 1 });
            Assert::IsFalse(PKB::getInstance().getAllKeysProcedure() == std::vector<int>{ 1, 2 });
        }

        TEST_METHOD(PKB_class_getAllValues_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("procedure1");
            PKB::getInstance().insertProcedure("procedure2");

            Assert::IsTrue(PKB::getInstance().getAllValuesProcedure() == std::vector <std::string> { "procedure1", "procedure2" });
            Assert::IsFalse(PKB::getInstance().getAllValuesProcedure() == std::vector<std::string>{ "procedure3", "procedure4" });
        }

        TEST_METHOD(PKB_class_insert_Procedure) {
            PKB::getInstance().clear();

            PKB::getInstance().insertProcedure("procedure1");
            PKB::getInstance().insertProcedure("procedure2");
            PKB::getInstance().insertProcedure("x");
            PKB::getInstance().insertProcedure("procedure1");
            PKB::getInstance().insertProcedure("y");

            std::unordered_map<int, std::string> testTable = { {0, "procedure1"}, {1, "procedure2"}, {2, "x"}, {3, "y"} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getProcedure(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[5] = "z";

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getProcedure(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");
            PKB::getInstance().insertRead(1, "var2");

            Assert::IsTrue(PKB::getInstance().getRead(1) == "var1");
            Assert::IsTrue(PKB::getInstance().getSizeRead() == 1);

        }

        TEST_METHOD(PKB_class_getNonExistentKey_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");

            Assert::IsTrue(PKB::getInstance().getRead(2) == "");
        }

        TEST_METHOD(PKB_class_insertGetBasic_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");
            PKB::getInstance().insertRead(2, "var2");
            PKB::getInstance().insertRead(3, "var3");

            Assert::IsTrue(PKB::getInstance().getRead(1) == "var1");
            Assert::IsTrue(PKB::getInstance().getRead(2) == "var2");
            Assert::IsTrue(PKB::getInstance().getRead(3) == "var3");
            Assert::IsTrue(PKB::getInstance().getRead(4) == "");
            Assert::IsTrue(PKB::getInstance().getRead(0) == "");
        }

        TEST_METHOD(PKB_class_getKeysRead_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");
            PKB::getInstance().insertRead(2, "var1");
            PKB::getInstance().insertRead(3, "var3");

            Assert::IsTrue(PKB::getInstance().getKeysRead("var1") == std::unordered_set<int>{ 1, 2 });
            Assert::IsTrue(PKB::getInstance().getKeysRead("var3") == std::unordered_set<int>{ 3 });
            Assert::IsTrue(PKB::getInstance().getKeysRead("var4") == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_getSize_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");
            PKB::getInstance().insertRead(2, "var2");

            Assert::IsTrue(PKB::getInstance().getSizeRead() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeRead() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");
            PKB::getInstance().insertRead(2, "var2");

            Assert::IsTrue(PKB::getInstance().hasKeyRead(1));
            Assert::IsFalse(PKB::getInstance().hasKeyRead(3));
        }

        TEST_METHOD(PKB_class_getAllKeys_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");
            PKB::getInstance().insertRead(2, "var2");

            Assert::IsTrue(PKB::getInstance().getAllKeysRead() == std::vector<int>{ 1, 2 });
            Assert::IsFalse(PKB::getInstance().getAllKeysRead() == std::vector<int>{ 3, 4 });
        }

        TEST_METHOD(PKB_class_getAllValues_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");
            PKB::getInstance().insertRead(2, "var2");

            Assert::IsTrue(PKB::getInstance().getAllValuesRead() == std::vector <std::string> { "var1", "var2" });
            Assert::IsFalse(PKB::getInstance().getAllValuesRead() == std::vector<std::string>{ "var2", "var3" });
        }

        TEST_METHOD(PKB_class_insert_Read) {
            PKB::getInstance().clear();

            PKB::getInstance().insertRead(1, "var1");
            PKB::getInstance().insertRead(2, "var2");
            PKB::getInstance().insertRead(3, "x");
            PKB::getInstance().insertRead(1, "statementType3");
            PKB::getInstance().insertRead(4, "y");

            std::unordered_map<int, std::string> testTable = { {1, "var1"}, {2, "var2"}, {3, "x"}, {4, "y"} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getRead(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[5] = "z";

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getRead(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");
            PKB::getInstance().insertPrint(1, "var2");

            Assert::IsTrue(PKB::getInstance().getPrint(1) == "var1");
            Assert::IsTrue(PKB::getInstance().getSizePrint() == 1);

        }

        TEST_METHOD(PKB_class_getNonExistentKey_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");

            Assert::IsTrue(PKB::getInstance().getPrint(2) == "");
        }

        TEST_METHOD(PKB_class_insertGetBasic_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");
            PKB::getInstance().insertPrint(2, "var2");
            PKB::getInstance().insertPrint(3, "var3");

            Assert::IsTrue(PKB::getInstance().getPrint(1) == "var1");
            Assert::IsTrue(PKB::getInstance().getPrint(2) == "var2");
            Assert::IsTrue(PKB::getInstance().getPrint(3) == "var3");
            Assert::IsTrue(PKB::getInstance().getPrint(4) == "");
            Assert::IsTrue(PKB::getInstance().getPrint(0) == "");
        }

        TEST_METHOD(PKB_class_getKeysPrint_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");
            PKB::getInstance().insertPrint(2, "var1");
            PKB::getInstance().insertPrint(3, "var3");

            Assert::IsTrue(PKB::getInstance().getKeysPrint("var1") == std::unordered_set<int>{ 1, 2 });
            Assert::IsTrue(PKB::getInstance().getKeysPrint("var3") == std::unordered_set<int>{ 3 });
            Assert::IsTrue(PKB::getInstance().getKeysPrint("var4") == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_getSize_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");
            PKB::getInstance().insertPrint(2, "var2");

            Assert::IsTrue(PKB::getInstance().getSizePrint() == 2);
            Assert::IsFalse(PKB::getInstance().getSizePrint() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");
            PKB::getInstance().insertPrint(2, "var2");

            Assert::IsTrue(PKB::getInstance().hasKeyPrint(1));
            Assert::IsFalse(PKB::getInstance().hasKeyPrint(3));
        }

        TEST_METHOD(PKB_class_getAllKeys_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");
            PKB::getInstance().insertPrint(2, "var2");

            Assert::IsTrue(PKB::getInstance().getAllKeysPrint() == std::vector<int>{ 1, 2 });
            Assert::IsFalse(PKB::getInstance().getAllKeysPrint() == std::vector<int>{ 3, 4 });
        }

        TEST_METHOD(PKB_class_getAllValues_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");
            PKB::getInstance().insertPrint(2, "var2");

            Assert::IsTrue(PKB::getInstance().getAllValuesPrint() == std::vector <std::string> { "var1", "var2" });
            Assert::IsFalse(PKB::getInstance().getAllValuesPrint() == std::vector<std::string>{ "var2", "var3" });
        }

        TEST_METHOD(PKB_class_insert_Print) {
            PKB::getInstance().clear();

            PKB::getInstance().insertPrint(1, "var1");
            PKB::getInstance().insertPrint(2, "var2");
            PKB::getInstance().insertPrint(3, "x");
            PKB::getInstance().insertPrint(1, "var4");
            PKB::getInstance().insertPrint(4, "y");

            std::unordered_map<int, std::string> testTable = { {1, "var1"}, {2, "var2"}, {3, "x"}, {4, "y"} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getPrint(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[5] = "z";

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getPrint(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");
            PKB::getInstance().insertCall(1, "proc2");

            Assert::IsTrue(PKB::getInstance().getCall(1) == "proc1");
            Assert::IsTrue(PKB::getInstance().getSizeCall() == 1);

        }

        TEST_METHOD(PKB_class_getNonExistentKey_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");

            Assert::IsTrue(PKB::getInstance().getCall(2) == "");
        }

        TEST_METHOD(PKB_class_insertGetBasic_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");
            PKB::getInstance().insertCall(2, "proc2");
            PKB::getInstance().insertCall(3, "proc3");

            Assert::IsTrue(PKB::getInstance().getCall(1) == "proc1");
            Assert::IsTrue(PKB::getInstance().getCall(2) == "proc2");
            Assert::IsTrue(PKB::getInstance().getCall(3) == "proc3");
            Assert::IsTrue(PKB::getInstance().getCall(4) == "");
            Assert::IsTrue(PKB::getInstance().getCall(0) == "");
        }

        TEST_METHOD(PKB_class_getKeysCall_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");
            PKB::getInstance().insertCall(2, "proc1");
            PKB::getInstance().insertCall(3, "proc3");

            Assert::IsTrue(PKB::getInstance().getKeysCall("proc1") == std::unordered_set<int>{ 1, 2 });
            Assert::IsTrue(PKB::getInstance().getKeysCall("proc3") == std::unordered_set<int>{ 3 });
            Assert::IsTrue(PKB::getInstance().getKeysCall("proc4") == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_getSize_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");
            PKB::getInstance().insertCall(2, "proc2");

            Assert::IsTrue(PKB::getInstance().getSizeCall() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeCall() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");
            PKB::getInstance().insertCall(2, "proc2");

            Assert::IsTrue(PKB::getInstance().hasKeyCall(1));
            Assert::IsFalse(PKB::getInstance().hasKeyCall(3));
        }

        TEST_METHOD(PKB_class_getAllKeys_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");
            PKB::getInstance().insertCall(2, "proc2");

            Assert::IsTrue(PKB::getInstance().getAllKeysCall() == std::vector<int>{ 1, 2 });
            Assert::IsFalse(PKB::getInstance().getAllKeysCall() == std::vector<int>{ 3, 4 });
        }

        TEST_METHOD(PKB_class_getAllValues_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");
            PKB::getInstance().insertCall(2, "proc2");

            Assert::IsTrue(PKB::getInstance().getAllValuesCall() == std::vector <std::string> { "proc1", "proc2" });
            Assert::IsFalse(PKB::getInstance().getAllValuesCall() == std::vector<std::string>{ "proc2", "proc3" });
        }

        TEST_METHOD(PKB_class_insert_Call) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCall(1, "proc1");
            PKB::getInstance().insertCall(2, "proc2");
            PKB::getInstance().insertCall(3, "x");
            PKB::getInstance().insertCall(1, "proc4");
            PKB::getInstance().insertCall(4, "y");

            std::unordered_map<int, std::string> testTable = { {1, "proc1"}, {2, "proc2"}, {3, "x"}, {4, "y"} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCall(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[5] = "z";

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCall(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_While) {
            PKB::getInstance().clear();

            PKB::getInstance().insertWhile(7, { "x", "flag" });
            PKB::getInstance().insertWhile(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getWhile(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsTrue(PKB::getInstance().getSizeWhile() == 1);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_While) {
            PKB::getInstance().clear();

            PKB::getInstance().insertWhile(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getWhile(4) == std::unordered_set<std::string>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_While) {
            PKB::getInstance().clear();
            PKB::getInstance().insertWhile(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getWhile(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsFalse(PKB::getInstance().getWhile(7) == std::unordered_set<std::string>{"y", "flag"});
        }

        TEST_METHOD(PKB_class_getSize_While) {
            PKB::getInstance().clear();
            PKB::getInstance().insertWhile(7, { "x", "flag" });
            PKB::getInstance().insertWhile(10, { "count" });
            Assert::IsTrue(PKB::getInstance().getSizeWhile() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeWhile() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_While) {
            PKB::getInstance().clear();
            PKB::getInstance().insertWhile(7, { "x", "flag" });
            PKB::getInstance().insertWhile(10, { "count" });
            Assert::IsTrue(PKB::getInstance().hasKeyWhile(7));
            Assert::IsFalse(PKB::getInstance().hasKeyWhile(6));
        }

        TEST_METHOD(PKB_class_getAllKeys_While) {
            PKB::getInstance().clear();

            PKB::getInstance().insertWhile(7, { "x", "flag" });
            PKB::getInstance().insertWhile(10, { "count" });
            Assert::IsTrue(PKB::getInstance().getAllKeysWhile() == std::vector<int>{ 7, 10 });
            Assert::IsFalse(PKB::getInstance().getAllKeysWhile() == std::vector<int>{ 7, 11 });
        }

        TEST_METHOD(PKB_class_getAllValues_While) {
            PKB::getInstance().clear();
            PKB::getInstance().insertWhile(7, { "x", "flag" });
            PKB::getInstance().insertWhile(10, { "count" });
        }

        TEST_METHOD(PKB_class_insert_While) {
            PKB::getInstance().clear();
            PKB::getInstance().insertWhile(7, { "x" });
            PKB::getInstance().insertWhile(10, { "count" });
            PKB::getInstance().insertWhile(10, { "cenX" });
            PKB::getInstance().insertWhile(3, { "count" });
            PKB::getInstance().insertWhile(-9, { "7", "flag" });
            PKB::getInstance().insertWhile(99999, { "-30" });

            std::unordered_map<int, std::unordered_set<std::string>> testTable =
            { {7, {"x"}}, {10, {"count", "cenX"}}, {3, {"count"}}, {-9, {"7","flag"}}, {99999, { "-30" }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getWhile(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { "365", "77" };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getWhile(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
        }

        TEST_METHOD(PKB_class_isWhileSet_While) {
            PKB::getInstance().clear();
            PKB::getInstance().insertWhile(7, { "x", "y", "z" });
            PKB::getInstance().insertWhile(8, { "x", "z" });
            PKB::getInstance().insertWhile(17, { "x" });
            PKB::getInstance().insertWhile(10, { "count" });
            PKB::getInstance().insertWhile(10, { "cenX" });

            Assert::IsTrue(PKB::getInstance().isWhile(7, std::unordered_set<std::string>{ "x", "y", "z" }));
            Assert::IsTrue(PKB::getInstance().isWhile(7, std::unordered_set<std::string>{ "x", "z" }));
            Assert::IsTrue(PKB::getInstance().isWhile(7, std::unordered_set<std::string>{ "y" }));
            Assert::IsFalse(PKB::getInstance().isWhile(7, std::unordered_set<std::string>{ "a" }));
            Assert::IsFalse(PKB::getInstance().isWhile(9, std::unordered_set<std::string>{ "y" }));
        }

        TEST_METHOD(PKB_class_isWhile_While) {
            PKB::getInstance().clear();
            PKB::getInstance().insertWhile(7, { "x", "y", "z" });
            PKB::getInstance().insertWhile(8, { "x", "z" });
            PKB::getInstance().insertWhile(17, { "x" });
            PKB::getInstance().insertWhile(10, { "count" });
            PKB::getInstance().insertWhile(10, { "cenX" });

            Assert::IsTrue(PKB::getInstance().isWhile(7, "x"));
            Assert::IsTrue(PKB::getInstance().isWhile(7, "y"));
            Assert::IsFalse(PKB::getInstance().isWhile(7, "a"));
            Assert::IsFalse(PKB::getInstance().isWhile(1, "x"));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_If) {
            PKB::getInstance().clear();

            PKB::getInstance().insertIf(7, { "x", "flag" });
            PKB::getInstance().insertIf(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getIf(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsTrue(PKB::getInstance().getSizeIf() == 1);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_If) {
            PKB::getInstance().clear();

            PKB::getInstance().insertIf(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getIf(4) == std::unordered_set<std::string>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_If) {
            PKB::getInstance().clear();
            PKB::getInstance().insertIf(7, { "x", "flag" });

            Assert::IsTrue(PKB::getInstance().getIf(7) == std::unordered_set<std::string>{ "x", "flag" });
            Assert::IsFalse(PKB::getInstance().getIf(7) == std::unordered_set<std::string>{"y", "flag"});
        }

        TEST_METHOD(PKB_class_getSize_If) {
            PKB::getInstance().clear();
            PKB::getInstance().insertIf(7, { "x", "flag" });
            PKB::getInstance().insertIf(10, { "count" });
            Assert::IsTrue(PKB::getInstance().getSizeIf() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeIf() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_If) {
            PKB::getInstance().clear();
            PKB::getInstance().insertIf(7, { "x", "flag" });
            PKB::getInstance().insertIf(10, { "count" });
            Assert::IsTrue(PKB::getInstance().hasKeyIf(7));
            Assert::IsFalse(PKB::getInstance().hasKeyIf(6));
        }

        TEST_METHOD(PKB_class_getAllKeys_If) {
            PKB::getInstance().clear();

            PKB::getInstance().insertIf(7, { "x", "flag" });
            PKB::getInstance().insertIf(10, { "count" });
            Assert::IsTrue(PKB::getInstance().getAllKeysIf() == std::vector<int>{ 7, 10 });
            Assert::IsFalse(PKB::getInstance().getAllKeysIf() == std::vector<int>{ 7, 11 });
        }

        TEST_METHOD(PKB_class_getAllValues_If) {
            PKB::getInstance().clear();
            PKB::getInstance().insertIf(7, { "x", "flag" });
            PKB::getInstance().insertIf(10, { "count" });
        }

        TEST_METHOD(PKB_class_insert_If) {
            PKB::getInstance().clear();
            PKB::getInstance().insertIf(7, { "x" });
            PKB::getInstance().insertIf(10, { "count" });
            PKB::getInstance().insertIf(10, { "cenX" });
            PKB::getInstance().insertIf(3, { "count" });
            PKB::getInstance().insertIf(-9, { "7", "flag" });
            PKB::getInstance().insertIf(99999, { "-30" });

            std::unordered_map<int, std::unordered_set<std::string>> testTable =
            { {7, {"x"}}, {10, {"count", "cenX"}}, {3, {"count"}}, {-9, {"7","flag"}}, {99999, { "-30" }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getIf(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { "365", "77" };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getIf(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
        }

        TEST_METHOD(PKB_class_isIfSet_If) {
            PKB::getInstance().clear();
            PKB::getInstance().insertIf(7, { "x", "y", "z" });
            PKB::getInstance().insertIf(8, { "x", "z" });
            PKB::getInstance().insertIf(17, { "x" });
            PKB::getInstance().insertIf(10, { "count" });
            PKB::getInstance().insertIf(10, { "cenX" });

            Assert::IsTrue(PKB::getInstance().isIf(7, std::unordered_set<std::string>{ "x", "y", "z" }));
            Assert::IsTrue(PKB::getInstance().isIf(7, std::unordered_set<std::string>{ "x", "z" }));
            Assert::IsTrue(PKB::getInstance().isIf(7, std::unordered_set<std::string>{ "y" }));
            Assert::IsFalse(PKB::getInstance().isIf(7, std::unordered_set<std::string>{ "a" }));
            Assert::IsFalse(PKB::getInstance().isIf(9, std::unordered_set<std::string>{ "y" }));
        }

        TEST_METHOD(PKB_class_isIf_If) {
            PKB::getInstance().clear();
            PKB::getInstance().insertIf(7, { "x", "y", "z" });
            PKB::getInstance().insertIf(8, { "x", "z" });
            PKB::getInstance().insertIf(17, { "x" });
            PKB::getInstance().insertIf(10, { "count" });
            PKB::getInstance().insertIf(10, { "cenX" });

            Assert::IsTrue(PKB::getInstance().isIf(7, "x"));
            Assert::IsTrue(PKB::getInstance().isIf(7, "y"));
            Assert::IsFalse(PKB::getInstance().isIf(7, "a"));
            Assert::IsFalse(PKB::getInstance().isIf(1, "x"));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Calls) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCalls(3, { 4, 5 });
            PKB::getInstance().insertCalls(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getCalls(3) == std::unordered_set<int>{4, 5});
            Assert::IsTrue(PKB::getInstance().getSizeCalls() == 1);
            Assert::IsTrue(PKB::getInstance().getCalledBy(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getSizeCalledBy() == 2);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Calls) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCalls(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getCalls(4) == std::unordered_set<int>{});
            Assert::IsTrue(PKB::getInstance().getCalledBy(77) == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_Calls) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCalls(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getCalls(3) == std::unordered_set<int>{4, 5});
            Assert::IsFalse(PKB::getInstance().getCalls(3) == std::unordered_set<int>{3, 5});
            Assert::IsTrue(PKB::getInstance().getCalledBy(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getCalledBy(5) == std::unordered_set<int>{3});
            Assert::IsFalse(PKB::getInstance().getCalledBy(5) == std::unordered_set<int>{3, 5});
        }

        TEST_METHOD(PKB_class_getSize_Calls) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCalls(3, { 4, 5 });
            PKB::getInstance().insertCalls(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getSizeCalls() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeCalls() == 3);
            Assert::IsTrue(PKB::getInstance().getSizeCalledBy() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeCalledBy() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Calls) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCalls(3, { 4, 5 });
            PKB::getInstance().insertCalls(4, { 5 });
            Assert::IsTrue(PKB::getInstance().hasKeyCalls(3));
            Assert::IsFalse(PKB::getInstance().hasKeyCalls(7));
            Assert::IsTrue(PKB::getInstance().hasKeyCalledBy(4));
            Assert::IsTrue(PKB::getInstance().hasKeyCalledBy(5));
            Assert::IsFalse(PKB::getInstance().hasKeyCalledBy(7));
        }

        TEST_METHOD(PKB_class_getAllKeys_Calls) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCalls(3, { 4, 5 });
            PKB::getInstance().insertCalls(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysCalls() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysCalls() == std::vector<int>{ 3, 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysCalledBy() == std::vector<int>{ 4, 5 });
            Assert::IsFalse(PKB::getInstance().getAllKeysCalledBy() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_getAllValues_Calls) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCalls(3, { 4, 5 });
            PKB::getInstance().insertCalls(4, { 5 });

            Assert::IsTrue(PKB::getInstance().getAllValuesCalls() == std::vector<std::unordered_set<int>>{ {4, 5}, { 5 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesCalls() == std::vector<std::unordered_set<int>>{ {4, 6}, { 5 } });
            Assert::IsTrue(PKB::getInstance().getAllValuesCalledBy() == std::vector<std::unordered_set<int>>{ {3}, { 3,4 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesCalledBy() == std::vector<std::unordered_set<int>>{ {4}, { 3,4 } });
        }

        TEST_METHOD(PKB_class_insert_Calls) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCalls(3, { 5, 6 });
            PKB::getInstance().insertCalls(3, { 4 });
            PKB::getInstance().insertCalls(4, { 5 });
            PKB::getInstance().insertCalls(99999, { 4 });
            PKB::getInstance().insertCalls(0, { 23 });
            PKB::getInstance().insertCalls(-3, { 25 });
            PKB::getInstance().insertCalls(55, { -99 });
            PKB::getInstance().insertCalls(60, { -3, 5 });

            std::unordered_map<int, std::unordered_set<int>> testTable = { {3, {4, 5, 6}}, {4, {5}}, {99999, {4}}, {0, {23}}, {-3, {25}}, {55, {-99}}, {60, { -3, 5 }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCalls(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCalls(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            testTable = { {5, {3,4,60}}, {6, {3}}, {4, {3,99999}}, {23, {0}}, {25, {-3}}, {-99, {55}}, {-3, {60}} };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCalledBy(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCalledBy(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isCallsSet_Calls) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCalls(3, { 5, 6 });
            PKB::getInstance().insertCalls(3, { 4 });
            PKB::getInstance().insertCalls(4, { 5 });
            PKB::getInstance().insertCalls(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isCalls(3, { 4, 5, 6 }));
            Assert::IsTrue(PKB::getInstance().isCalls(3, { 4, 5 }));
            Assert::IsTrue(PKB::getInstance().isCalls(3, { 4 }));
            Assert::IsFalse(PKB::getInstance().isCalls(3, { 7 }));
            Assert::IsFalse(PKB::getInstance().isCalls(9, { 7 }));

            Assert::IsTrue(PKB::getInstance().isCalledBy(5, { 3, 4 }));
            Assert::IsTrue(PKB::getInstance().isCalledBy(6, { 3 }));
            Assert::IsTrue(PKB::getInstance().isCalledBy(4, { 3,99999 }));
            Assert::IsFalse(PKB::getInstance().isCalledBy(4, { 7 }));
            Assert::IsFalse(PKB::getInstance().isCalledBy(9, { 7 }));
        }

        TEST_METHOD(PKB_class_isCalls_Calls) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCalls(3, { 5, 6 });
            PKB::getInstance().insertCalls(3, { 4 });
            PKB::getInstance().insertCalls(4, { 5 });
            PKB::getInstance().insertCalls(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isCalls(3, 5));
            Assert::IsFalse(PKB::getInstance().isCalls(3, 30));
            Assert::IsFalse(PKB::getInstance().isCalls(30, 5));

            Assert::IsTrue(PKB::getInstance().isCalledBy(5, 3));
            Assert::IsFalse(PKB::getInstance().isCalledBy(5, 20));
            Assert::IsFalse(PKB::getInstance().isCalledBy(30, 5));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_CallsStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCallsStar(3, { 4, 5 });
            PKB::getInstance().insertCallsStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getCallsStar(3) == std::unordered_set<int>{4, 5});
            Assert::IsTrue(PKB::getInstance().getSizeCallsStar() == 1);
            Assert::IsTrue(PKB::getInstance().getCalledByStar(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getSizeCalledByStar() == 2);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_CallsStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCallsStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getCallsStar(4) == std::unordered_set<int>{});
            Assert::IsTrue(PKB::getInstance().getCalledByStar(77) == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_CallsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCallsStar(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getCallsStar(3) == std::unordered_set<int>{4, 5});
            Assert::IsFalse(PKB::getInstance().getCallsStar(3) == std::unordered_set<int>{3, 5});
            Assert::IsTrue(PKB::getInstance().getCalledByStar(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getCalledByStar(5) == std::unordered_set<int>{3});
            Assert::IsFalse(PKB::getInstance().getCalledByStar(5) == std::unordered_set<int>{3, 5});
        }

        TEST_METHOD(PKB_class_getSize_CallsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCallsStar(3, { 4, 5 });
            PKB::getInstance().insertCallsStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getSizeCallsStar() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeCallsStar() == 3);
            Assert::IsTrue(PKB::getInstance().getSizeCalledByStar() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeCalledByStar() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_CallsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCallsStar(3, { 4, 5 });
            PKB::getInstance().insertCallsStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().hasKeyCallsStar(3));
            Assert::IsFalse(PKB::getInstance().hasKeyCallsStar(7));
            Assert::IsTrue(PKB::getInstance().hasKeyCalledByStar(4));
            Assert::IsTrue(PKB::getInstance().hasKeyCalledByStar(5));
            Assert::IsFalse(PKB::getInstance().hasKeyCalledByStar(7));
        }

        TEST_METHOD(PKB_class_getAllKeys_CallsStar) {
            PKB::getInstance().clear();

            PKB::getInstance().insertCallsStar(3, { 4, 5 });
            PKB::getInstance().insertCallsStar(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysCallsStar() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysCallsStar() == std::vector<int>{ 3, 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysCalledByStar() == std::vector<int>{ 4, 5 });
            Assert::IsFalse(PKB::getInstance().getAllKeysCalledByStar() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_getAllValues_CallsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCallsStar(3, { 4, 5 });
            PKB::getInstance().insertCallsStar(4, { 5 });

            Assert::IsTrue(PKB::getInstance().getAllValuesCallsStar() == std::vector<std::unordered_set<int>>{ {4, 5}, { 5 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesCallsStar() == std::vector<std::unordered_set<int>>{ {4, 6}, { 5 } });
            Assert::IsTrue(PKB::getInstance().getAllValuesCalledByStar() == std::vector<std::unordered_set<int>>{ {3}, { 3,4 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesCalledByStar() == std::vector<std::unordered_set<int>>{ {4}, { 3,4 } });
        }

        TEST_METHOD(PKB_class_insert_CallsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCallsStar(3, { 5, 6 });
            PKB::getInstance().insertCallsStar(3, { 4 });
            PKB::getInstance().insertCallsStar(4, { 5 });
            PKB::getInstance().insertCallsStar(99999, { 4 });
            PKB::getInstance().insertCallsStar(0, { 23 });
            PKB::getInstance().insertCallsStar(-3, { 25 });
            PKB::getInstance().insertCallsStar(55, { -99 });
            PKB::getInstance().insertCallsStar(60, { -3, 5 });

            std::unordered_map<int, std::unordered_set<int>> testTable = { {3, {4, 5, 6}}, {4, {5}}, {99999, {4}}, {0, {23}}, {-3, {25}}, {55, {-99}}, {60, { -3, 5 }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCallsStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCallsStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            testTable = { {5, {3,4,60}}, {6, {3}}, {4, {3,99999}}, {23, {0}}, {25, {-3}}, {-99, {55}}, {-3, {60}} };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCalledByStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getCalledByStar(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isCallsStarSet_CallsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCallsStar(3, { 5, 6 });
            PKB::getInstance().insertCallsStar(3, { 4 });
            PKB::getInstance().insertCallsStar(4, { 5 });
            PKB::getInstance().insertCallsStar(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isCallsStar(3, { 4, 5, 6 }));
            Assert::IsTrue(PKB::getInstance().isCallsStar(3, { 4, 5 }));
            Assert::IsTrue(PKB::getInstance().isCallsStar(3, { 4 }));
            Assert::IsFalse(PKB::getInstance().isCallsStar(3, { 7 }));
            Assert::IsFalse(PKB::getInstance().isCallsStar(9, { 7 }));

            Assert::IsTrue(PKB::getInstance().isCalledByStar(5, { 3, 4 }));
            Assert::IsTrue(PKB::getInstance().isCalledByStar(6, { 3 }));
            Assert::IsTrue(PKB::getInstance().isCalledByStar(4, { 3,99999 }));
            Assert::IsFalse(PKB::getInstance().isCalledByStar(4, { 7 }));
            Assert::IsFalse(PKB::getInstance().isCalledByStar(9, { 7 }));
        }

        TEST_METHOD(PKB_class_isCallsStar_CallsStar) {
            PKB::getInstance().clear();
            PKB::getInstance().insertCallsStar(3, { 5, 6 });
            PKB::getInstance().insertCallsStar(3, { 4 });
            PKB::getInstance().insertCallsStar(4, { 5 });
            PKB::getInstance().insertCallsStar(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isCallsStar(3, 5));
            Assert::IsFalse(PKB::getInstance().isCallsStar(3, 30));
            Assert::IsFalse(PKB::getInstance().isCallsStar(30, 5));

            Assert::IsTrue(PKB::getInstance().isCalledByStar(5, 3));
            Assert::IsFalse(PKB::getInstance().isCalledByStar(5, 20));
            Assert::IsFalse(PKB::getInstance().isCalledByStar(30, 5));
        }

        TEST_METHOD(PKB_class_insertDuplicateKey_Next) {
            PKB::getInstance().clear();

            PKB::getInstance().insertNext(3, { 4, 5 });
            PKB::getInstance().insertNext(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getNext(3) == std::unordered_set<int>{4, 5});
            Assert::IsTrue(PKB::getInstance().getSizeNext() == 1);
            Assert::IsTrue(PKB::getInstance().getPrevious(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getSizePrevious() == 2);
        }

        TEST_METHOD(PKB_class_getNonExistentKey_Next) {
            PKB::getInstance().clear();

            PKB::getInstance().insertNext(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getNext(4) == std::unordered_set<int>{});
            Assert::IsTrue(PKB::getInstance().getPrevious(77) == std::unordered_set<int>{});
        }

        TEST_METHOD(PKB_class_insertGetBasic_Next) {
            PKB::getInstance().clear();
            PKB::getInstance().insertNext(3, { 4, 5 });

            Assert::IsTrue(PKB::getInstance().getNext(3) == std::unordered_set<int>{4, 5});
            Assert::IsFalse(PKB::getInstance().getNext(3) == std::unordered_set<int>{3, 5});
            Assert::IsTrue(PKB::getInstance().getPrevious(4) == std::unordered_set<int>{3});
            Assert::IsTrue(PKB::getInstance().getPrevious(5) == std::unordered_set<int>{3});
            Assert::IsFalse(PKB::getInstance().getPrevious(5) == std::unordered_set<int>{3, 5});
        }

        TEST_METHOD(PKB_class_getSize_Next) {
            PKB::getInstance().clear();
            PKB::getInstance().insertNext(3, { 4, 5 });
            PKB::getInstance().insertNext(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getSizeNext() == 2);
            Assert::IsFalse(PKB::getInstance().getSizeNext() == 3);
            Assert::IsTrue(PKB::getInstance().getSizePrevious() == 2);
            Assert::IsFalse(PKB::getInstance().getSizePrevious() == 3);
        }

        TEST_METHOD(PKB_class_hasKey_Next) {
            PKB::getInstance().clear();
            PKB::getInstance().insertNext(3, { 4, 5 });
            PKB::getInstance().insertNext(4, { 5 });
            Assert::IsTrue(PKB::getInstance().hasKeyNext(3));
            Assert::IsFalse(PKB::getInstance().hasKeyNext(7));
            Assert::IsTrue(PKB::getInstance().hasKeyPrevious(4));
            Assert::IsTrue(PKB::getInstance().hasKeyPrevious(5));
            Assert::IsFalse(PKB::getInstance().hasKeyPrevious(7));
        }

        TEST_METHOD(PKB_class_getAllKeys_Next) {
            PKB::getInstance().clear();

            PKB::getInstance().insertNext(3, { 4, 5 });
            PKB::getInstance().insertNext(4, { 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysNext() == std::vector<int>{ 3, 4 });
            Assert::IsFalse(PKB::getInstance().getAllKeysNext() == std::vector<int>{ 3, 5 });
            Assert::IsTrue(PKB::getInstance().getAllKeysPrevious() == std::vector<int>{ 4, 5 });
            Assert::IsFalse(PKB::getInstance().getAllKeysPrevious() == std::vector<int>{ 3, 5 });
        }

        TEST_METHOD(PKB_class_getAllValues_Next) {
            PKB::getInstance().clear();
            PKB::getInstance().insertNext(3, { 4, 5 });
            PKB::getInstance().insertNext(4, { 5 });

            Assert::IsTrue(PKB::getInstance().getAllValuesNext() == std::vector<std::unordered_set<int>>{ {4, 5}, { 5 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesNext() == std::vector<std::unordered_set<int>>{ {4, 6}, { 5 } });
            Assert::IsTrue(PKB::getInstance().getAllValuesPrevious() == std::vector<std::unordered_set<int>>{ {3}, { 3,4 } });
            Assert::IsFalse(PKB::getInstance().getAllValuesPrevious() == std::vector<std::unordered_set<int>>{ {4}, { 3,4 } });
        }

        TEST_METHOD(PKB_class_insert_Next) {
            PKB::getInstance().clear();
            PKB::getInstance().insertNext(3, { 5, 6 });
            PKB::getInstance().insertNext(3, { 4 });
            PKB::getInstance().insertNext(4, { 5 });
            PKB::getInstance().insertNext(99999, { 4 });
            PKB::getInstance().insertNext(0, { 23 });
            PKB::getInstance().insertNext(-3, { 25 });
            PKB::getInstance().insertNext(55, { -99 });
            PKB::getInstance().insertNext(60, { -3, 5 });

            std::unordered_map<int, std::unordered_set<int>> testTable = { {3, {4, 5, 6}}, {4, {5}}, {99999, {4}}, {0, {23}}, {-3, {25}}, {55, {-99}}, {60, { -3, 5 }} };

            bool testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getNext(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getNext(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);

            testTable.clear();
            testTable = { {5, {3,4,60}}, {6, {3}}, {4, {3,99999}}, {23, {0}}, {25, {-3}}, {-99, {55}}, {-3, {60}} };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getPrevious(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsTrue(testPassed);

            testTable[33] = { 365, 77 };

            testPassed = true;
            for (auto element : testTable) {
                if (PKB::getInstance().getPrevious(element.first) != element.second) {
                    testPassed = false;
                    break;
                }
            }
            Assert::IsFalse(testPassed);
        }

        TEST_METHOD(PKB_class_isNextSet_Next) {
            PKB::getInstance().clear();
            PKB::getInstance().insertNext(3, { 5, 6 });
            PKB::getInstance().insertNext(3, { 4 });
            PKB::getInstance().insertNext(4, { 5 });
            PKB::getInstance().insertNext(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isNext(3, { 4, 5, 6 }));
            Assert::IsTrue(PKB::getInstance().isNext(3, { 4, 5 }));
            Assert::IsTrue(PKB::getInstance().isNext(3, { 4 }));
            Assert::IsFalse(PKB::getInstance().isNext(3, { 7 }));
            Assert::IsFalse(PKB::getInstance().isNext(9, { 7 }));

            Assert::IsTrue(PKB::getInstance().isPrevious(5, { 3, 4 }));
            Assert::IsTrue(PKB::getInstance().isPrevious(6, { 3 }));
            Assert::IsTrue(PKB::getInstance().isPrevious(4, { 3,99999 }));
            Assert::IsFalse(PKB::getInstance().isPrevious(4, { 7 }));
            Assert::IsFalse(PKB::getInstance().isPrevious(9, { 7 }));
        }

        TEST_METHOD(PKB_class_isNext_Next) {
            PKB::getInstance().clear();
            PKB::getInstance().insertNext(3, { 5, 6 });
            PKB::getInstance().insertNext(3, { 4 });
            PKB::getInstance().insertNext(4, { 5 });
            PKB::getInstance().insertNext(99999, { 4 });

            Assert::IsTrue(PKB::getInstance().isNext(3, 5));
            Assert::IsFalse(PKB::getInstance().isNext(3, 30));
            Assert::IsFalse(PKB::getInstance().isNext(30, 5));

            Assert::IsTrue(PKB::getInstance().isPrevious(5, 3));
            Assert::IsFalse(PKB::getInstance().isPrevious(5, 20));
            Assert::IsFalse(PKB::getInstance().isPrevious(30, 5));
        }
        };
}