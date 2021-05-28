#include "stdafx.h"
#include "CppUnitTest.h"
#include <sstream>


#include <iostream>
#include "../source/Parser.h"
#include "DesignExtractorTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTesting
{

	TEST_CLASS(TestDE)
	{
	public:
		TEST_METHOD(testExtractFollowsStar) {
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(4, 3);
			SimulatedPKB::getInstance().insertFollows(10, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 6);
			DesignExtractorTest::getInstance().extractFollowsStar();
			// Test extracting basic follow star that is already in follows
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(2, 1), true);
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(3, 2), true);
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(4, 3), true);

			// Test extracting advanced FollowsStar
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(10, 1), true);
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(10, 2), true);
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(4, 1), true);

			// Test invalid relationships do not exists
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(1, 1), false);
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(1, 10), false);
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(-11, 30), false);

			// Test no wrong extraction of FollowsStar
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(5, 1), false);
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(6, 10), false);
			Assert::AreEqual(SimulatedPKB::getInstance().isFollowsStar(10, 5), false);
			SimulatedPKB::getInstance().clear();

		}

		TEST_METHOD(testExtractParentStar) {
			Logger::WriteMessage("testExtractParentStar1");

			SimulatedPKB::getInstance().insertParent(2, 1);
			SimulatedPKB::getInstance().insertParent(3, 2);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(10, 4);
			SimulatedPKB::getInstance().insertParent(6, 5);
			SimulatedPKB::getInstance().insertParent(7, 6);
			DesignExtractorTest::getInstance().extractParentStar();

			Logger::WriteMessage("testExtractParentStar2");

			// Test extracting basic follow star that is already in Parent
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(2, 1), true);
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(3, 2), true);
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(4, 3), true);

			// Test extracting advanced ParentStar
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(10, 1), true);
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(10, 2), true);
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(4, 1), true);

			// Test invalid relationships do not exists
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(1, 1), false);
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(1, 10), false);
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(-11, 30), false);

			// Test no wrong extraction of ParentStar
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(5, 1), false);
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(6, 10), false);
			Assert::AreEqual(SimulatedPKB::getInstance().isParentStar(10, 5), false);
			SimulatedPKB::getInstance().clear();

		}

		TEST_METHOD(testExtractUsesAndModifiesForProcedure) {
			SimulatedPKB::getInstance().clear();
			Logger::WriteMessage("testExtractUsesAndModifiesForProcedure1");
			// This is to test the extraction for a single procedure.

			// forming basic design entities

			SimulatedPKB::getInstance().insertProcedure("main");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20});
			SimulatedPKB::getInstance().insertAssignLHS(1, "varOne");
			SimulatedPKB::getInstance().insertAssignRHS(1, "varTwo");
			SimulatedPKB::getInstance().insertAssignLHS(2, "varTwo");
			SimulatedPKB::getInstance().insertAssignRHS(2, "varThree");
			SimulatedPKB::getInstance().insertAssignLHS(3, "varThree");
			SimulatedPKB::getInstance().insertAssignRHS(3, "varFour");
			SimulatedPKB::getInstance().insertPrint(4, "printVarOne");
			SimulatedPKB::getInstance().insertPrint(5, "printVarTwo");
			SimulatedPKB::getInstance().insertPrint(6, "printVarThree");
			SimulatedPKB::getInstance().insertRead(7, "readVarOne");
			SimulatedPKB::getInstance().insertRead(8, "readVarTwo");
			SimulatedPKB::getInstance().insertRead(9, "readVarThree");
			SimulatedPKB::getInstance().insertIf(10, { "condVarOne" });
			SimulatedPKB::getInstance().insertIf(11, { "condVarTwo", "condVarThree" });
			SimulatedPKB::getInstance().insertIf(12, { "condVarFour", "condVarFive" });
			SimulatedPKB::getInstance().insertIf(13, { "condVarSix", "condVarSeven" });
			SimulatedPKB::getInstance().insertWhile(14, { "condVarEight" });
			SimulatedPKB::getInstance().insertWhile(15, { "condVarNine", "condVarTen" });
			SimulatedPKB::getInstance().insertWhile(16, { "condVarEleven", "condVarTwelve" });

			// forming a nested relationship
			SimulatedPKB::getInstance().insertWhile(17, {"condVarThirteen"});
			SimulatedPKB::getInstance().insertAssignLHS(18, "varFive");
			SimulatedPKB::getInstance().insertAssignRHS(18, "varSix");
			SimulatedPKB::getInstance().insertPrint(19, "printVarFour");
			SimulatedPKB::getInstance().insertRead(20, "readVarFive");
			SimulatedPKB::getInstance().insertParent(18, 17);
			SimulatedPKB::getInstance().insertParent(19, 17);
			SimulatedPKB::getInstance().insertParent(20, 17);

			DesignExtractorTest::getInstance().extractAllDesigns();

			Logger::WriteMessage("testExtractUsesAndModifiesForProcedure2");

			// Test if uses and modifies can be extracted for assignment statements
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(1) == std::unordered_set<std::string>{"varTwo"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(2) == std::unordered_set<std::string>{"varThree"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(1) == std::unordered_set<std::string>{"varOne"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(2) == std::unordered_set<std::string>{"varTwo"});

			// Test no wrong extraction of uses
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(1) == std::unordered_set< std::string>{"varOne"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(2) == std::unordered_set< std::string>{"varTwo"});

			// Test no wrong extraction of modifies
			Assert::AreEqual(false, SimulatedPKB::getInstance().getModifies(1) == std::unordered_set< std::string>{"varTwo"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getModifies(2) == std::unordered_set< std::string>{"varThree"});

			// Test if uses can be extracted for print statements
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(4) == std::unordered_set< std::string>{"printVarOne"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(5) == std::unordered_set< std::string>{"printVarTwo"});

			// Test no wrong extraction of uses for print statements
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(1) == std::unordered_set< std::string>{"printVarOne"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(2) == std::unordered_set< std::string>{"printVarTwo"});

			// Test if modifies can be extracted for read statements
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(7) == std::unordered_set< std::string>{"readVarOne"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(8) == std::unordered_set< std::string>{"readVarTwo"});

			// Test no wrong extraction of uses for read statements
			Assert::AreEqual(false, SimulatedPKB::getInstance().getModifies(7) == std::unordered_set< std::string>{"printVarOne"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getModifies(9) == std::unordered_set< std::string>{"printVarOne"});

			// Test if uses can be extracted for if and while(containers)'s conditions
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(10) == std::unordered_set< std::string>{"condVarOne"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(11) == std::unordered_set< std::string>{"condVarTwo", "condVarThree"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(12) == std::unordered_set< std::string>{"condVarFour", "condVarFive"});

			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(14) == std::unordered_set< std::string>{"condVarEight"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(15) == std::unordered_set< std::string>{"condVarNine", "condVarTen"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(16) == std::unordered_set< std::string>{"condVarEleven", "condVarTwelve"});

			// Test no wrong extraction of uses for if and while(containers)'s conditions 
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(10) == std::unordered_set< std::string>{"1"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(11) == std::unordered_set< std::string>{"condVarTwo"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(11) == std::unordered_set< std::string>{"readVarTwo"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(14) == std::unordered_set< std::string>{"condVarOne"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(15) == std::unordered_set< std::string>{"condVarTwelve"});

			// Test if uses and modifies can be extracted for if and while(containers)'s statements
			// Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(17) == std::unordered_set< std::string>{"condVarThirteen", "varSix", "printVarFour"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(18) == std::unordered_set< std::string>{"varSix"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(19) == std::unordered_set< std::string>{"printVarFour"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(17) == std::unordered_set< std::string>{"varFive", "readVarFive"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(18) == std::unordered_set< std::string>{"varFive"});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(20) == std::unordered_set< std::string>{"readVarFive"});

			// Test no wrong extraction of uses and modifies for if and while(containers)'s statements 
			Assert::AreEqual(false, SimulatedPKB::getInstance().getUses(17) == std::unordered_set< std::string>{"condVarThirteen"});
			Assert::AreEqual(false , SimulatedPKB::getInstance().getUses(17) == std::unordered_set< std::string>{"varFive", "readVarFive"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getModifies(17) == std::unordered_set< std::string>{"condVarThirteen", "varSix", "printVarFour"});
			Assert::AreEqual(false, SimulatedPKB::getInstance().getModifies(18) == std::unordered_set< std::string>{"varSix"});
			SimulatedPKB::getInstance().clear();

		}

		TEST_METHOD(testExtractUsesAndModifies) {
			SimulatedPKB::getInstance().clear();
			Logger::WriteMessage("testExtractUsesAndModifies1");

			// This test is for multiple procedures for uses and modifies
			SimulatedPKB::getInstance().insertProcedure("procOne"); //index0
			SimulatedPKB::getInstance().insertProcedure("procTwo"); //index1
			SimulatedPKB::getInstance().insertProcedure("procThree"); //index2
			SimulatedPKB::getInstance().insertProcedure("procFour"); //index3
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4});
			SimulatedPKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{5, 6, 7, 8, 9, 10});
			SimulatedPKB::getInstance().insertProcedureStatementList(2, std::unordered_set<int>{11, 12, 13});
			SimulatedPKB::getInstance().insertProcedureStatementList(3, std::unordered_set<int>{14, 15, 16, 17, 18, 19, 20});
			SimulatedPKB::getInstance().insertIf(1, { "varOne", "varTwo" });
			SimulatedPKB::getInstance().insertAssignLHS(2, "varThree");
			SimulatedPKB::getInstance().insertAssignRHS(2, "varFour");
			SimulatedPKB::getInstance().insertCall(3, "procTwo");
			SimulatedPKB::getInstance().insertPrint(4, "varOne");
			SimulatedPKB::getInstance().insertParent(2, 1);
			SimulatedPKB::getInstance().insertParent(3, 1);
			SimulatedPKB::getInstance().insertParent(4, 1);
			SimulatedPKB::getInstance().insertCall(5, "procThree");
			SimulatedPKB::getInstance().insertWhile(6, { "varFive", "varSix" });
			SimulatedPKB::getInstance().insertRead(7, "varSeven");
			SimulatedPKB::getInstance().insertWhile(8, { "varEight", "varNine" });
			SimulatedPKB::getInstance().insertParent(7, 6);
			SimulatedPKB::getInstance().insertParent(8, 6);
			SimulatedPKB::getInstance().insertCall(9, "procFour");
			SimulatedPKB::getInstance().insertAssignLHS(10, "varTen");
			SimulatedPKB::getInstance().insertAssignRHS(10, "varEleven + 2000");
			SimulatedPKB::getInstance().insertParent(9, 8);
			SimulatedPKB::getInstance().insertParent(10, 8);
			SimulatedPKB::getInstance().insertAssignLHS(11, "varTwelve");
			SimulatedPKB::getInstance().insertAssignRHS(11, "varThirteen");
			SimulatedPKB::getInstance().insertIf(12, { "varFourteen", "varFifteen" });
			SimulatedPKB::getInstance().insertPrint(13, "varTwelve");
			SimulatedPKB::getInstance().insertParent(13, 12);
			SimulatedPKB::getInstance().insertRead(14, "varFifteen");
			SimulatedPKB::getInstance().insertPrint(15, "varSixteen");
			SimulatedPKB::getInstance().insertIf(16, { "varSixteen", "varFifteen" });
			SimulatedPKB::getInstance().insertWhile(17, { "varSeventeen"});
			SimulatedPKB::getInstance().insertParent(17, 16);
			SimulatedPKB::getInstance().insertIf(18, { "varEighteen", "varNineteen" });
			SimulatedPKB::getInstance().insertParent(18, 17);
			SimulatedPKB::getInstance().insertAssignLHS(19, "varTwenty");
			SimulatedPKB::getInstance().insertAssignRHS(19, "2");
			SimulatedPKB::getInstance().insertPrint(20, "varTwentyOne");
			SimulatedPKB::getInstance().insertParent(19, 18);
			SimulatedPKB::getInstance().insertParent(20, 18);
			DesignExtractorTest::getInstance().extractAllDesigns();


			// checks if all uses from nested calls are extracted
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(1) == std::unordered_set< std::string>{
				"varOne", "varTwo", "varFour", "varFive", "varSix", "varEight", "varNine", "varEleven", "varThirteen",  "varFourteen",  "varFifteen",  "varTwelve", "varSixteen",  "varSeventeen",  "varEighteen",
					"varNineteen",  "varTwentyOne"
			});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(3) == std::unordered_set< std::string>{
				"varFive", "varSix", "varEight", "varNine", "varEleven", "varThirteen", "varFourteen", "varFifteen", "varTwelve", "varSixteen", "varSeventeen", "varEighteen",
					"varNineteen", "varTwentyOne"
			});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(5) == std::unordered_set< std::string>{
				"varThirteen", "varFourteen", "varFifteen", "varTwelve"
			});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getUses(9) == std::unordered_set< std::string>{
				"varSixteen", "varSeventeen", "varFifteen", "varEighteen", "varNineteen", "varTwentyOne"
			});

			// checks if all modifies from nested calls are extracted
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(1) == std::unordered_set< std::string>{
				"varThree", "varSeven", "varTen", "varTwelve", "varFifteen", "varTwenty"
			});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(3) == std::unordered_set< std::string>{
				"varSeven", "varTen", "varTwelve", "varFifteen", "varTwenty"
			});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(5) == std::unordered_set< std::string>{
				"varTwelve"
			});
			Assert::AreEqual(true, SimulatedPKB::getInstance().getModifies(9) == std::unordered_set< std::string>{
				"varFifteen", "varTwenty"
			});
		}

		TEST_METHOD(testGetVarUsedFromCondition) {
			std::string cond1 = "a == b";
			std::string cond2 = "c != d";
			std::string cond3 = "e < f";
			std::string cond4 = "g > h";
			std::string cond5 = "!i";
			std::string cond6 = "j && k";
			std::string cond7 = "l || m";
			std::string cond8 = "n == 1";

			// getting output from the method to be tested
			std::unordered_set<std::string> cond1Output = DesignExtractorTest::getInstance().getVarUsed(cond1);
			std::unordered_set<std::string> cond2Output = DesignExtractorTest::getInstance().getVarUsed(cond2);
			std::unordered_set<std::string> cond3Output = DesignExtractorTest::getInstance().getVarUsed(cond3);
			std::unordered_set<std::string> cond4Output = DesignExtractorTest::getInstance().getVarUsed(cond4);
			std::unordered_set<std::string> cond5Output = DesignExtractorTest::getInstance().getVarUsed(cond5);
			std::unordered_set<std::string> cond6Output = DesignExtractorTest::getInstance().getVarUsed(cond6);
			std::unordered_set<std::string> cond7Output = DesignExtractorTest::getInstance().getVarUsed(cond7);
			std::unordered_set<std::string> cond8Output = DesignExtractorTest::getInstance().getVarUsed(cond8);

			// checking if they meet expected.
			Assert::AreEqual(true, cond1Output == std::unordered_set< std::string>{"a", "b"});
			Assert::AreEqual(true, cond2Output == std::unordered_set< std::string>{"c", "d"});
			Assert::AreEqual(true, cond3Output == std::unordered_set< std::string>{"e", "f"});
			Assert::AreEqual(true, cond4Output == std::unordered_set< std::string>{"g", "h"});
			Assert::AreEqual(true, cond5Output == std::unordered_set< std::string>{"i"});
			Assert::AreEqual(true, cond6Output == std::unordered_set< std::string>{"j", "k"});
			Assert::AreEqual(true, cond7Output == std::unordered_set< std::string>{"l", "m"});
			Assert::AreEqual(true, cond8Output == std::unordered_set< std::string>{"n"});
			SimulatedPKB::getInstance().clear();

		}

		TEST_METHOD(testExtractNext) {
			Logger::WriteMessage("testExtractNext");

			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "if");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertStatement(5, "assign");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertStatement(7, "assign");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertFollows(8, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(6, 3);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(9, 8);
			SimulatedPKB::getInstance().insertParent(2, 1);
			SimulatedPKB::getInstance().insertParent(3, 1);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 1);
			SimulatedPKB::getInstance().insertParent(7, 1);
			SimulatedPKB::getInstance().insertStatementList(2, { 2, 3, 6 });
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5 });
			SimulatedPKB::getInstance().insertStatementList(7, { 7 });
			DesignExtractorTest::getInstance().extractNext();
			std::unordered_set<int> next1 = SimulatedPKB::getInstance().getNext(1);
			std::unordered_set<int> next2 = SimulatedPKB::getInstance().getNext(2);
			std::unordered_set<int> next3 = SimulatedPKB::getInstance().getNext(3);
			std::unordered_set<int> next4 = SimulatedPKB::getInstance().getNext(4);
			std::unordered_set<int> next5 = SimulatedPKB::getInstance().getNext(5);
			std::unordered_set<int> next6 = SimulatedPKB::getInstance().getNext(6);
			std::unordered_set<int> next7 = SimulatedPKB::getInstance().getNext(7);
			std::unordered_set<int> next8 = SimulatedPKB::getInstance().getNext(8);
			std::unordered_set<int> next9 = SimulatedPKB::getInstance().getNext(9);
			std::unordered_set<int> actualNext1 = { 2, 7 };
			std::unordered_set<int> actualNext2 = { 3 };
			std::unordered_set<int> actualNext3 = { 4, 6 };
			std::unordered_set<int> actualNext4 = { 5 };
			std::unordered_set<int> actualNext5 = { 3 };
			std::unordered_set<int> actualNext6 = { 8 };
			std::unordered_set<int> actualNext7 = { 8 };
			std::unordered_set<int> actualNext8 = { 9 };
			std::unordered_set<int> actualNext9 = { };
			SimulatedPKB::getInstance().clear();
			Assert::IsTrue(next1 == actualNext1);
			Assert::IsTrue(next2 == actualNext2);
			Assert::IsTrue(next2 == actualNext2);
			Assert::IsTrue(next3 == actualNext3);
			Assert::IsTrue(next4 == actualNext4);
			Assert::IsTrue(next5 == actualNext5);
			Assert::IsTrue(next6 == actualNext6);
			Assert::IsTrue(next7 == actualNext7);
			Assert::IsTrue(next8 == actualNext8);
			Assert::IsTrue(next9 == actualNext9);
		}

		TEST_METHOD(testGetNextStar) {
			Logger::WriteMessage("testExtractNextStar");

			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			DesignExtractorTest::getInstance().extractNext();
			std::unordered_set<int> nextStar1 = DesignExtractorTest::getInstance().getNextStar(1);
			std::unordered_set<int> nextStar2 = DesignExtractorTest::getInstance().getNextStar(2);
			std::unordered_set<int> nextStar3 = DesignExtractorTest::getInstance().getNextStar(3);
			std::unordered_set<int> nextStar4 = DesignExtractorTest::getInstance().getNextStar(4);
			std::unordered_set<int> nextStar5 = DesignExtractorTest::getInstance().getNextStar(5);
			std::unordered_set<int> nextStar6 = DesignExtractorTest::getInstance().getNextStar(6);
			std::unordered_set<int> nextStar7 = DesignExtractorTest::getInstance().getNextStar(7);
			std::unordered_set<int> nextStar8 = DesignExtractorTest::getInstance().getNextStar(8);
			std::unordered_set<int> nextStar9 = DesignExtractorTest::getInstance().getNextStar(9);
			std::unordered_set<int> nextStar10 = DesignExtractorTest::getInstance().getNextStar(10);
			std::unordered_set<int> nextStar11 = DesignExtractorTest::getInstance().getNextStar(11);
			std::unordered_set<int> nextStar12 = DesignExtractorTest::getInstance().getNextStar(12);
			std::unordered_set<int> actualNextStar1 = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
			std::unordered_set<int> actualNextStar2 = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
			std::unordered_set<int> actualNextStar3 = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
			std::unordered_set<int> actualNextStar4 = { 4, 5, 6, 3, 7, 8, 9, 10, 11, 12};
			std::unordered_set<int> actualNextStar5 = { 5, 6, 3, 4, 7, 8, 9, 10, 11, 12};
			std::unordered_set<int> actualNextStar6 = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
			std::unordered_set<int> actualNextStar7 = { 8, 9, 10, 11, 12 };
			std::unordered_set<int> actualNextStar8 = { 10, 11, 12 };
			std::unordered_set<int> actualNextStar9 = { 10, 11, 12 };
			std::unordered_set<int> actualNextStar10 = { 11, 12 };
			std::unordered_set<int> actualNextStar11 = { 12 };
			std::unordered_set<int> actualNextStar12 = { };
			Assert::IsTrue(nextStar1 == actualNextStar1);
			Assert::IsTrue(nextStar2 == actualNextStar2);
			Assert::IsTrue(nextStar3 == actualNextStar3);
			Assert::IsTrue(nextStar4 == actualNextStar4);
			Assert::IsTrue(nextStar5 == actualNextStar5);
			Assert::IsTrue(nextStar6 == actualNextStar6);
			Assert::IsTrue(nextStar7 == actualNextStar7);
			Assert::IsTrue(nextStar8 == actualNextStar8);
			Assert::IsTrue(nextStar9 == actualNextStar9);
			Assert::IsTrue(nextStar10 == actualNextStar10);
			Assert::IsTrue(nextStar11 == actualNextStar11);
			Assert::IsTrue(nextStar12 == actualNextStar12);
			SimulatedPKB::getInstance().clear();
			DesignExtractorTest::getInstance().clearNextStarCache();
		}

		TEST_METHOD(testIsNextStar) {
			Logger::WriteMessage("testisNextStar");

			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			DesignExtractorTest::getInstance().extractNext();
			Assert::IsTrue(true == DesignExtractorTest::getInstance().isNextStar(1,2));
			Assert::IsTrue(true == DesignExtractorTest::getInstance().isNextStar(1, 12));
			Assert::IsTrue(true == DesignExtractorTest::getInstance().isNextStar(5, 6));
			Assert::IsTrue(true == DesignExtractorTest::getInstance().isNextStar(11, 12));
			Assert::IsTrue(false == DesignExtractorTest::getInstance().isNextStar(12, 1));
			Assert::IsTrue(false == DesignExtractorTest::getInstance().isNextStar(1, 13));
			DesignExtractorTest::getInstance().clearNextStarCache();
		}

		TEST_METHOD(testGetPreviousStar) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			DesignExtractorTest::getInstance().extractNext();
			std::unordered_set<int> previousStar1 = DesignExtractorTest::getInstance().getPreviousStar(1);
			std::unordered_set<int> previousStar2 = DesignExtractorTest::getInstance().getPreviousStar(2);
			std::unordered_set<int> previousStar3 = DesignExtractorTest::getInstance().getPreviousStar(3);
			std::unordered_set<int> previousStar4 = DesignExtractorTest::getInstance().getPreviousStar(4);
			std::unordered_set<int> previousStar5 = DesignExtractorTest::getInstance().getPreviousStar(5);
			std::unordered_set<int> previousStar6 = DesignExtractorTest::getInstance().getPreviousStar(6);
			std::unordered_set<int> previousStar7 = DesignExtractorTest::getInstance().getPreviousStar(7);
			std::unordered_set<int> previousStar8 = DesignExtractorTest::getInstance().getPreviousStar(8);
			std::unordered_set<int> previousStar9 = DesignExtractorTest::getInstance().getPreviousStar(9);
			std::unordered_set<int> previousStar10 = DesignExtractorTest::getInstance().getPreviousStar(10);
			std::unordered_set<int> previousStar11 = DesignExtractorTest::getInstance().getPreviousStar(11);
			std::unordered_set<int> previousStar12 = DesignExtractorTest::getInstance().getPreviousStar(12);
			std::unordered_set<int> actualPreviousStar1 = { };
			std::unordered_set<int> actualPreviousStar2 = { 1 };
			std::unordered_set<int> actualPreviousStar3 = { 1, 2, 3, 4, 5, 6};
			std::unordered_set<int> actualPreviousStar4 = { 1, 2, 3, 4, 5, 6 };
			std::unordered_set<int> actualPreviousStar5 = { 1, 2, 3, 4, 5, 6 };
			std::unordered_set<int> actualPreviousStar6 = { 1, 2, 3, 4, 5, 6 };
			std::unordered_set<int> actualPreviousStar7 = { 1, 2, 3, 4, 5, 6 };
			std::unordered_set<int> actualPreviousStar8 = { 1, 2, 3, 4, 5, 6, 7 };
			std::unordered_set<int> actualPreviousStar9 = { 1, 2, 3, 4, 5, 6, 7 };
			std::unordered_set<int> actualPreviousStar10 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			std::unordered_set<int> actualPreviousStar11 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			std::unordered_set<int> actualPreviousStar12 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
			Assert::IsTrue(previousStar1 == actualPreviousStar1);
			Assert::IsTrue(previousStar2 == actualPreviousStar2);
			Assert::IsTrue(previousStar3 == actualPreviousStar3);
			Assert::IsTrue(previousStar4 == actualPreviousStar4);
			Assert::IsTrue(previousStar5 == actualPreviousStar5);
			Assert::IsTrue(previousStar6 == actualPreviousStar6);
			Assert::IsTrue(previousStar7 == actualPreviousStar7);
			Assert::IsTrue(previousStar8 == actualPreviousStar8);
			Assert::IsTrue(previousStar9 == actualPreviousStar9);
			Assert::IsTrue(previousStar10 == actualPreviousStar10);
			Assert::IsTrue(previousStar11 == actualPreviousStar11);
			Assert::IsTrue(previousStar12 == actualPreviousStar12);
		}

		TEST_METHOD(testGetAffectsBasic) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			DesignExtractorTest::getInstance().clearAffectsCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(1, "x");
			SimulatedPKB::getInstance().insertAssignRHS(1, "0");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(2, "i");
			SimulatedPKB::getInstance().insertAssignRHS(2, "5");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(4, "x");
			SimulatedPKB::getInstance().insertAssignRHS(4, "x + 2*y");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(6, "i");
			SimulatedPKB::getInstance().insertAssignRHS(6, "i - 1");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(8, "x");
			SimulatedPKB::getInstance().insertAssignRHS(8, "x + 1");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(9, "z");
			SimulatedPKB::getInstance().insertAssignRHS(9, "1");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(10, "z");
			SimulatedPKB::getInstance().insertAssignRHS(10, "z + x + i");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(11, "y");
			SimulatedPKB::getInstance().insertAssignRHS(11, "z + 2");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(12, "x");
			SimulatedPKB::getInstance().insertAssignRHS(12, "x * y + z;");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			SimulatedPKB::getInstance().insertProcedure("main");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractNext();
			std::unordered_set<int> affects1 = DesignExtractorTest::getInstance().getAffects(1);
			std::unordered_set<int> affects2 = DesignExtractorTest::getInstance().getAffects(2);
			std::unordered_set<int> affects4 = DesignExtractorTest::getInstance().getAffects(4);
			std::unordered_set<int> affects6 = DesignExtractorTest::getInstance().getAffects(6);
			std::unordered_set<int> affects8 = DesignExtractorTest::getInstance().getAffects(8);
			std::unordered_set<int> affects9 = DesignExtractorTest::getInstance().getAffects(9);
			std::unordered_set<int> affects10 = DesignExtractorTest::getInstance().getAffects(10);
			std::unordered_set<int> affects11 = DesignExtractorTest::getInstance().getAffects(11);
			std::unordered_set<int> actualAffects1 = {4,8,10,12};
			std::unordered_set<int> actualAffects2 = {6,10};
			std::unordered_set<int> actualAffects4 = {4,8,10,12};
			std::unordered_set<int> actualAffects6 = {6,10};
			std::unordered_set<int> actualAffects8 = {10,12};
			std::unordered_set<int> actualAffects9 = {10};
			std::unordered_set<int> actualAffects10 = {11,12};
			std::unordered_set<int> actualAffects11 = {12};
			Assert::AreEqual(affects1.size() , actualAffects1.size());
			Assert::IsTrue(affects1 == actualAffects1);
			Assert::IsTrue(affects2 == actualAffects2);
			Assert::IsTrue(affects4 == actualAffects4);
			Assert::IsTrue(affects6 == actualAffects6);
			Assert::IsTrue(affects8 == actualAffects8);
			Assert::IsTrue(affects9 == actualAffects9);
			Assert::IsTrue(affects10 == actualAffects10);
			Assert::IsTrue(affects11 == actualAffects11);
		}

		TEST_METHOD(testGetAffectedByBasic) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			DesignExtractorTest::getInstance().clearAffectsCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(1, "x");
			SimulatedPKB::getInstance().insertAssignRHS(1, "0");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(2, "i");
			SimulatedPKB::getInstance().insertAssignRHS(2, "5");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(4, "x");
			SimulatedPKB::getInstance().insertAssignRHS(4, "x + 2*y");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(6, "i");
			SimulatedPKB::getInstance().insertAssignRHS(6, "i - 1");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(8, "x");
			SimulatedPKB::getInstance().insertAssignRHS(8, "x + 1");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(9, "z");
			SimulatedPKB::getInstance().insertAssignRHS(9, "1");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(10, "z");
			SimulatedPKB::getInstance().insertAssignRHS(10, "z + x + i");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(11, "y");
			SimulatedPKB::getInstance().insertAssignRHS(11, "z + 2");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(12, "x");
			SimulatedPKB::getInstance().insertAssignRHS(12, "x * y + z;");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			SimulatedPKB::getInstance().insertProcedure("main");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractNext();
			std::unordered_set<int> affectedBy4 = DesignExtractorTest::getInstance().getAffectedBy(4);
			std::unordered_set<int> affectedBy6 = DesignExtractorTest::getInstance().getAffectedBy(6);
			std::unordered_set<int> affectedBy8 = DesignExtractorTest::getInstance().getAffectedBy(8);
			std::unordered_set<int> affectedBy10 = DesignExtractorTest::getInstance().getAffectedBy(10);
			std::unordered_set<int> affectedBy11 = DesignExtractorTest::getInstance().getAffectedBy(11);
			std::unordered_set<int> affectedBy12 = DesignExtractorTest::getInstance().getAffectedBy(12);
			std::unordered_set<int> actualAffectedBy4 = { 1,4 };
			std::unordered_set<int> actualAffectedBy6 = { 2,6 };
			std::unordered_set<int> actualAffectedBy8 = { 1,4 };
			std::unordered_set<int> actualAffectedBy10 = { 1,2,4,6,8,9 };
			std::unordered_set<int> actualAffectedBy11 = { 10 };
			std::unordered_set<int> actualAffectedBy12 = { 1,4,8,10,11 };
			Assert::IsTrue(affectedBy4 == actualAffectedBy4);
			Assert::IsTrue(affectedBy6 == actualAffectedBy6);
			Assert::IsTrue(affectedBy8 == actualAffectedBy8);
			Assert::IsTrue(affectedBy10 == actualAffectedBy10);
			Assert::IsTrue(affectedBy11 == actualAffectedBy11);
			Assert::IsTrue(affectedBy12 == actualAffectedBy12);
		}

		TEST_METHOD(testIsAffectedByBasic) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			DesignExtractorTest::getInstance().clearAffectsCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(1, "x");
			SimulatedPKB::getInstance().insertAssignRHS(1, "0");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(2, "i");
			SimulatedPKB::getInstance().insertAssignRHS(2, "5");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(4, "x");
			SimulatedPKB::getInstance().insertAssignRHS(4, "x + 2*y");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(6, "i");
			SimulatedPKB::getInstance().insertAssignRHS(6, "i - 1");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(8, "x");
			SimulatedPKB::getInstance().insertAssignRHS(8, "x + 1");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(9, "z");
			SimulatedPKB::getInstance().insertAssignRHS(9, "1");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(10, "z");
			SimulatedPKB::getInstance().insertAssignRHS(10, "z + x + i");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(11, "y");
			SimulatedPKB::getInstance().insertAssignRHS(11, "z + 2");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(12, "x");
			SimulatedPKB::getInstance().insertAssignRHS(12, "x * y + z;");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			SimulatedPKB::getInstance().insertProcedure("main");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractNext();
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffects(1, 4));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffects(2, 6));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffects(4, 12));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffects(9, 10));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffects(10, 11));
		}

		TEST_METHOD(testGetAffectsStarBasic) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			DesignExtractorTest::getInstance().clearAffectsCache();
			DesignExtractorTest::getInstance().clearAffectsStarCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(1, "x");
			SimulatedPKB::getInstance().insertAssignRHS(1, "0");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(2, "i");
			SimulatedPKB::getInstance().insertAssignRHS(2, "5");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(4, "x");
			SimulatedPKB::getInstance().insertAssignRHS(4, "x + 2*y");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(6, "i");
			SimulatedPKB::getInstance().insertAssignRHS(6, "i - 1");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(8, "x");
			SimulatedPKB::getInstance().insertAssignRHS(8, "x + 1");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(9, "z");
			SimulatedPKB::getInstance().insertAssignRHS(9, "1");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(10, "z");
			SimulatedPKB::getInstance().insertAssignRHS(10, "z + x + i");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(11, "y");
			SimulatedPKB::getInstance().insertAssignRHS(11, "z + 2");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(12, "x");
			SimulatedPKB::getInstance().insertAssignRHS(12, "x * y + z;");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			SimulatedPKB::getInstance().insertProcedure("main");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractNext();
			std::unordered_set<int> affectsStar1 = DesignExtractorTest::getInstance().getAffectsStar(1);
			std::unordered_set<int> affectsStar2 = DesignExtractorTest::getInstance().getAffectsStar(2);
			std::unordered_set<int> affectsStar4 = DesignExtractorTest::getInstance().getAffectsStar(4);
			std::unordered_set<int> affectsStar6 = DesignExtractorTest::getInstance().getAffectsStar(6);
			std::unordered_set<int> affectsStar8 = DesignExtractorTest::getInstance().getAffectsStar(8);
			std::unordered_set<int> affectsStar9 = DesignExtractorTest::getInstance().getAffectsStar(9);
			std::unordered_set<int> affectsStar10 = DesignExtractorTest::getInstance().getAffectsStar(10);
			std::unordered_set<int> affectsStar11 = DesignExtractorTest::getInstance().getAffectsStar(11);
			std::unordered_set<int> affectsStar12 = DesignExtractorTest::getInstance().getAffectsStar(12);
			std::unordered_set<int> actualAffectsStar1 = { 4, 8, 10, 11, 12 };
			std::unordered_set<int> actualAffectsStar2 = { 6, 10, 11, 12 };
			std::unordered_set<int> actualAffectsStar4 = { 4, 8, 10, 11, 12 };
			std::unordered_set<int> actualAffectsStar6 = { 6, 10, 11, 12 };
			std::unordered_set<int> actualAffectsStar8 = { 10, 11, 12 };
			std::unordered_set<int> actualAffectsStar9 = { 10, 11, 12 };
			std::unordered_set<int> actualAffectsStar10 = { 11, 12 };
			std::unordered_set<int> actualAffectsStar11 = { 12 };
			std::unordered_set<int> actualAffectsStar12 = {};
			Assert::IsTrue(affectsStar1 == actualAffectsStar1);
			Assert::IsTrue(affectsStar2 == actualAffectsStar2);
			Assert::IsTrue(affectsStar4 == actualAffectsStar4);
			Assert::IsTrue(affectsStar6 == actualAffectsStar6);
			Assert::IsTrue(affectsStar8 == actualAffectsStar8);
			Assert::IsTrue(affectsStar9 == actualAffectsStar9);
			Assert::IsTrue(affectsStar10 == actualAffectsStar10);
			Assert::IsTrue(affectsStar11 == actualAffectsStar11);
			Assert::IsTrue(affectsStar12 == actualAffectsStar12);
		}

		TEST_METHOD(testGetAffectedByStarBasic) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			DesignExtractorTest::getInstance().clearAffectsCache();
			DesignExtractorTest::getInstance().clearAffectsStarCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(1, "x");
			SimulatedPKB::getInstance().insertAssignRHS(1, "0");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(2, "i");
			SimulatedPKB::getInstance().insertAssignRHS(2, "5");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(4, "x");
			SimulatedPKB::getInstance().insertAssignRHS(4, "x + 2*y");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(6, "i");
			SimulatedPKB::getInstance().insertAssignRHS(6, "i - 1");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(8, "x");
			SimulatedPKB::getInstance().insertAssignRHS(8, "x + 1");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(9, "z");
			SimulatedPKB::getInstance().insertAssignRHS(9, "1");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(10, "z");
			SimulatedPKB::getInstance().insertAssignRHS(10, "z + x + i");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(11, "y");
			SimulatedPKB::getInstance().insertAssignRHS(11, "z + 2");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(12, "x");
			SimulatedPKB::getInstance().insertAssignRHS(12, "x * y + z;");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			SimulatedPKB::getInstance().insertProcedure("main");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractNext();
			std::unordered_set<int> affectedByStar1 = DesignExtractorTest::getInstance().getAffectedByStar(1);
			std::unordered_set<int> affectedByStar2 = DesignExtractorTest::getInstance().getAffectedByStar(2);
			std::unordered_set<int> affectedByStar4 = DesignExtractorTest::getInstance().getAffectedByStar(4);
			std::unordered_set<int> affectedByStar6 = DesignExtractorTest::getInstance().getAffectedByStar(6);
			std::unordered_set<int> affectedByStar8 = DesignExtractorTest::getInstance().getAffectedByStar(8);
			std::unordered_set<int> affectedByStar9 = DesignExtractorTest::getInstance().getAffectedByStar(9);
			std::unordered_set<int> affectedByStar10 = DesignExtractorTest::getInstance().getAffectedByStar(10);
			std::unordered_set<int> affectedByStar11 = DesignExtractorTest::getInstance().getAffectedByStar(11);
			std::unordered_set<int> affectedByStar12 = DesignExtractorTest::getInstance().getAffectedByStar(12);
			std::unordered_set<int> actualAffectedByStar1 = { };
			std::unordered_set<int> actualAffectedByStar2 = { };
			std::unordered_set<int> actualAffectedByStar4 = { 1, 4 };
			std::unordered_set<int> actualAffectedByStar6 = { 2, 6 };
			std::unordered_set<int> actualAffectedByStar8 = { 1, 4 };
			std::unordered_set<int> actualAffectedByStar9 = { };
			std::unordered_set<int> actualAffectedByStar10 = { 1, 2, 4, 6, 8, 9 };
			std::unordered_set<int> actualAffectedByStar11 = { 1, 2, 4, 6, 8, 9, 10 };
			std::unordered_set<int> actualAffectedByStar12 = { 1, 2, 4, 6, 8, 9, 10, 11 };
			Assert::IsTrue(affectedByStar1 == actualAffectedByStar1);
			Assert::IsTrue(affectedByStar2 == actualAffectedByStar2);
			Assert::IsTrue(affectedByStar4 == actualAffectedByStar4);
			Assert::IsTrue(affectedByStar6 == actualAffectedByStar6);
			Assert::IsTrue(affectedByStar8 == actualAffectedByStar8);
			Assert::IsTrue(affectedByStar9 == actualAffectedByStar9);
			Assert::IsTrue(affectedByStar10 == actualAffectedByStar10);
			Assert::IsTrue(affectedByStar11 == actualAffectedByStar11);
			Assert::IsTrue(affectedByStar12 == actualAffectedByStar12);
		}

		TEST_METHOD(testIsAffectedByStarBasic) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			DesignExtractorTest::getInstance().clearAffectsCache();
			DesignExtractorTest::getInstance().clearAffectsStarCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(1, "x");
			SimulatedPKB::getInstance().insertAssignRHS(1, "0");
			SimulatedPKB::getInstance().insertStatement(2, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(2, "i");
			SimulatedPKB::getInstance().insertAssignRHS(2, "5");
			SimulatedPKB::getInstance().insertStatement(3, "while");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(4, "x");
			SimulatedPKB::getInstance().insertAssignRHS(4, "x + 2*y");
			SimulatedPKB::getInstance().insertStatement(5, "call");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(6, "i");
			SimulatedPKB::getInstance().insertAssignRHS(6, "i - 1");
			SimulatedPKB::getInstance().insertStatement(7, "if");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(8, "x");
			SimulatedPKB::getInstance().insertAssignRHS(8, "x + 1");
			SimulatedPKB::getInstance().insertStatement(9, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(9, "z");
			SimulatedPKB::getInstance().insertAssignRHS(9, "1");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(10, "z");
			SimulatedPKB::getInstance().insertAssignRHS(10, "z + x + i");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(11, "y");
			SimulatedPKB::getInstance().insertAssignRHS(11, "z + 2");
			SimulatedPKB::getInstance().insertStatement(12, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(12, "x");
			SimulatedPKB::getInstance().insertAssignRHS(12, "x * y + z;");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 3);
			SimulatedPKB::getInstance().insertFollows(10, 7);
			SimulatedPKB::getInstance().insertFollows(11, 10);
			SimulatedPKB::getInstance().insertFollows(12, 11);
			SimulatedPKB::getInstance().insertParent(4, 3);
			SimulatedPKB::getInstance().insertParent(5, 3);
			SimulatedPKB::getInstance().insertParent(6, 3);
			SimulatedPKB::getInstance().insertParent(8, 7);
			SimulatedPKB::getInstance().insertParent(9, 7);
			SimulatedPKB::getInstance().insertStatementList(4, { 4, 5, 6 });
			SimulatedPKB::getInstance().insertStatementList(8, { 8 });
			SimulatedPKB::getInstance().insertStatementList(9, { 9 });
			SimulatedPKB::getInstance().insertProcedure("main");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractNext();
			Assert::IsFalse(DesignExtractorTest::getInstance().isAffectsStar(1, 1));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(1, 4));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(1, 8));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(1, 10));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(1, 11));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(1, 12));
			Assert::IsFalse(DesignExtractorTest::getInstance().isAffectsStar(2, 2));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(2, 6));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(2, 10));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(2, 11));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(2, 12));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(4, 4));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(4, 8));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(4, 10));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(4, 11));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(4, 12));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(6, 6));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(6, 10));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(6, 11));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(6, 12));
			Assert::IsFalse(DesignExtractorTest::getInstance().isAffectsStar(8, 8));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(8, 10));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(8, 11));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(8, 12));
			Assert::IsFalse(DesignExtractorTest::getInstance().isAffectsStar(9, 9));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(9, 10));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(9, 11));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(9, 12));
			Assert::IsFalse(DesignExtractorTest::getInstance().isAffectsStar(10, 10));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(10, 11));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(10, 12));
			Assert::IsFalse(DesignExtractorTest::getInstance().isAffectsStar(11, 11));
			Assert::IsTrue(DesignExtractorTest::getInstance().isAffectsStar(11, 12));
		}

		TEST_METHOD(testExtractNextBipBasic) {
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertProcedure("One");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5});
			SimulatedPKB::getInstance().insertProcedure("Two");
			SimulatedPKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{6, 7, 8});
			SimulatedPKB::getInstance().insertProcedure("Three");
			SimulatedPKB::getInstance().insertProcedureStatementList(2, std::unordered_set<int>{9, 10, 11});
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertStatement(2, "call");
			SimulatedPKB::getInstance().insertStatement(3, "assign");
			SimulatedPKB::getInstance().insertStatement(4, "call");
			SimulatedPKB::getInstance().insertStatement(5, "assign");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertStatement(7, "call");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertStatement(9, "if");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertCall(2, "Two");
			SimulatedPKB::getInstance().insertCall(4, "Three");
			SimulatedPKB::getInstance().insertCall(7, "Three");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(4, 3);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(7, 6);
			SimulatedPKB::getInstance().insertFollows(8, 7);
			SimulatedPKB::getInstance().insertParent(10, 9);
			SimulatedPKB::getInstance().insertParent(11, 9);
			SimulatedPKB::getInstance().insertStatementList(10, { 10 });
			SimulatedPKB::getInstance().insertStatementList(11, { 11 });
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractExtensions();
			std::unordered_set<int> nextBip1 = SimulatedPKB::getInstance().getNextBip(1);
			std::unordered_set<int> nextBip2 = SimulatedPKB::getInstance().getNextBip(2);
			std::unordered_set<int> nextBip3 = SimulatedPKB::getInstance().getNextBip(3);
			std::unordered_set<int> nextBip4 = SimulatedPKB::getInstance().getNextBip(4);
			std::unordered_set<int> nextBip5 = SimulatedPKB::getInstance().getNextBip(5);
			std::unordered_set<int> nextBip6 = SimulatedPKB::getInstance().getNextBip(6);
			std::unordered_set<int> nextBip7 = SimulatedPKB::getInstance().getNextBip(7);
			std::unordered_set<int> nextBip8 = SimulatedPKB::getInstance().getNextBip(8);
			std::unordered_set<int> nextBip9 = SimulatedPKB::getInstance().getNextBip(9);
			std::unordered_set<int> nextBip10 = SimulatedPKB::getInstance().getNextBip(10);
			std::unordered_set<int> nextBip11 = SimulatedPKB::getInstance().getNextBip(11);
			std::unordered_set<int> actualNextBip1 = { 2 };
			std::unordered_set<int> actualNextBip2 = { 6 };
			std::unordered_set<int> actualNextBip3 = { 4 };
			std::unordered_set<int> actualNextBip4 = { 9 };
			std::unordered_set<int> actualNextBip5 = {  };
			std::unordered_set<int> actualNextBip6 = { 7 };
			std::unordered_set<int> actualNextBip7 = { 9 };
			std::unordered_set<int> actualNextBip8 = { 3 };
			std::unordered_set<int> actualNextBip9 = { 10, 11 };
			std::unordered_set<int> actualNextBip10 = { 5, 8 };
			std::unordered_set<int> actualNextBip11 = { 5, 8 };
			Assert::IsTrue(nextBip1 == actualNextBip1);
			Assert::IsTrue(nextBip2 == actualNextBip2);
			Assert::IsTrue(nextBip3 == actualNextBip3);
			Assert::IsTrue(nextBip4 == actualNextBip4);
			Assert::IsTrue(nextBip5 == actualNextBip5);
			Assert::IsTrue(nextBip6 == actualNextBip6);
			Assert::IsTrue(nextBip7 == actualNextBip7);
			Assert::IsTrue(nextBip8 == actualNextBip8);
			Assert::IsTrue(nextBip9 == actualNextBip9);
			Assert::IsTrue(nextBip10 == actualNextBip10);
			Assert::IsTrue(nextBip11 == actualNextBip11);
		}

		TEST_METHOD(testExtractNextBipMultipleCalls) {
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertProcedure("One");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3});
			SimulatedPKB::getInstance().insertProcedure("Two");
			SimulatedPKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{4, 5, 6});
			SimulatedPKB::getInstance().insertStatement(1, "call");
			SimulatedPKB::getInstance().insertStatement(2, "call");
			SimulatedPKB::getInstance().insertStatement(3, "call");
			SimulatedPKB::getInstance().insertCall(1, "Two");
			SimulatedPKB::getInstance().insertCall(2, "Two");
			SimulatedPKB::getInstance().insertCall(3, "Two");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertStatement(5, "assign");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractExtensions();
			std::unordered_set<int> nextBip1 = SimulatedPKB::getInstance().getNextBip(1);
			std::unordered_set<int> nextBip2 = SimulatedPKB::getInstance().getNextBip(2);
			std::unordered_set<int> nextBip3 = SimulatedPKB::getInstance().getNextBip(3);
			std::unordered_set<int> nextBip4 = SimulatedPKB::getInstance().getNextBip(4);
			std::unordered_set<int> nextBip5 = SimulatedPKB::getInstance().getNextBip(5);
			std::unordered_set<int> nextBip6 = SimulatedPKB::getInstance().getNextBip(6);
			std::unordered_set<int> actualNextBip1 = { 4 };
			std::unordered_set<int> actualNextBip2 = { 4 };
			std::unordered_set<int> actualNextBip3 = { 4 };
			std::unordered_set<int> actualNextBip4 = { 5 };
			std::unordered_set<int> actualNextBip5 = { 6 };
			std::unordered_set<int> actualNextBip6 = { 2, 3 };
			Assert::IsTrue(nextBip1 == actualNextBip1);
			Assert::IsTrue(nextBip2 == actualNextBip2);
			Assert::IsTrue(nextBip3 == actualNextBip3);
			Assert::IsTrue(nextBip4 == actualNextBip4);
			Assert::IsTrue(nextBip5 == actualNextBip5);
			Assert::IsTrue(nextBip6 == actualNextBip6);
		}

		TEST_METHOD(testExtractNextBipStarBasic) {
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertProcedure("One");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5});
			SimulatedPKB::getInstance().insertProcedure("Two");
			SimulatedPKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{6, 7, 8});
			SimulatedPKB::getInstance().insertProcedure("Three");
			SimulatedPKB::getInstance().insertProcedureStatementList(2, std::unordered_set<int>{9, 10, 11});
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertStatement(2, "call");
			SimulatedPKB::getInstance().insertStatement(3, "assign");
			SimulatedPKB::getInstance().insertStatement(4, "call");
			SimulatedPKB::getInstance().insertStatement(5, "assign");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertStatement(7, "call");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertStatement(9, "if");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertCall(2, "Two");
			SimulatedPKB::getInstance().insertCall(4, "Three");
			SimulatedPKB::getInstance().insertCall(7, "Three");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(4, 3);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(7, 6);
			SimulatedPKB::getInstance().insertFollows(8, 7);
			SimulatedPKB::getInstance().insertParent(10, 9);
			SimulatedPKB::getInstance().insertParent(11, 9);
			SimulatedPKB::getInstance().insertStatementList(10, { 10 });
			SimulatedPKB::getInstance().insertStatementList(11, { 11 });
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractExtensions();
			std::unordered_set<int> nextBipStar1 = SimulatedPKB::getInstance().getNextBipStar(1);
			std::unordered_set<int> nextBipStar2 = SimulatedPKB::getInstance().getNextBipStar(2);
			std::unordered_set<int> nextBipStar3 = SimulatedPKB::getInstance().getNextBipStar(3);
			std::unordered_set<int> nextBipStar4 = SimulatedPKB::getInstance().getNextBipStar(4);
			std::unordered_set<int> nextBipStar5 = SimulatedPKB::getInstance().getNextBipStar(5);
			std::unordered_set<int> nextBipStar6 = SimulatedPKB::getInstance().getNextBipStar(6);
			std::unordered_set<int> nextBipStar7 = SimulatedPKB::getInstance().getNextBipStar(7);
			std::unordered_set<int> nextBipStar8 = SimulatedPKB::getInstance().getNextBipStar(8);
			std::unordered_set<int> nextBipStar9 = SimulatedPKB::getInstance().getNextBipStar(9);
			std::unordered_set<int> nextBipStar10 = SimulatedPKB::getInstance().getNextBipStar(10);
			std::unordered_set<int> nextBipStar11 = SimulatedPKB::getInstance().getNextBipStar(11);
			std::unordered_set<int> actualNextBipStar1 = { 2, 6, 7, 9, 10, 11, 8, 3, 4, 5 };
			std::unordered_set<int> actualNextBipStar2 = { 6, 7, 9, 10, 11, 8, 3, 4, 5 };
			std::unordered_set<int> actualNextBipStar3 = { 4, 9, 10, 11, 5 };
			std::unordered_set<int> actualNextBipStar4 = { 9, 10, 11, 5 };
			std::unordered_set<int> actualNextBipStar5 = {  };
			std::unordered_set<int> actualNextBipStar6 = { 7, 9, 10, 11, 8, 3, 4, 5 };
			std::unordered_set<int> actualNextBipStar7 = { 9, 10, 11, 8, 3, 4, 5 };
			std::unordered_set<int> actualNextBipStar8 = { 3, 4, 9, 10, 11, 5 };
			std::unordered_set<int> actualNextBipStar9 = { 10, 11, 8, 3, 4, 9, 5 };
			std::unordered_set<int> actualNextBipStar10 = { 8, 3, 4, 9, 10, 11, 5 };
			std::unordered_set<int> actualNextBipStar11 = { 8, 3, 4, 9, 10, 11, 5 };
			Assert::IsTrue(nextBipStar1 == actualNextBipStar1);
			Assert::IsTrue(nextBipStar2 == actualNextBipStar2);
			Assert::IsTrue(nextBipStar3 == actualNextBipStar3);
			Assert::IsTrue(nextBipStar4 == actualNextBipStar4);
			Assert::IsTrue(nextBipStar5 == actualNextBipStar5);
			Assert::IsTrue(nextBipStar6 == actualNextBipStar6);
			Assert::IsTrue(nextBipStar7 == actualNextBipStar7);
			Assert::IsTrue(nextBipStar8 == actualNextBipStar8);
			Assert::IsTrue(nextBipStar9 == actualNextBipStar9);
			Assert::IsTrue(nextBipStar10 == actualNextBipStar10);
			Assert::IsTrue(nextBipStar11 == actualNextBipStar11);
		}

		TEST_METHOD(testExtractNextBipStarMultipleCalls) {
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertProcedure("One");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3});
			SimulatedPKB::getInstance().insertProcedure("Two");
			SimulatedPKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{4, 5, 6});
			SimulatedPKB::getInstance().insertStatement(1, "call");
			SimulatedPKB::getInstance().insertStatement(2, "call");
			SimulatedPKB::getInstance().insertStatement(3, "call");
			SimulatedPKB::getInstance().insertCall(1, "Two");
			SimulatedPKB::getInstance().insertCall(2, "Two");
			SimulatedPKB::getInstance().insertCall(3, "Two");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertStatement(5, "assign");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractExtensions();
			std::unordered_set<int> nextBipStar1 = SimulatedPKB::getInstance().getNextBipStar(1);
			std::unordered_set<int> nextBipStar2 = SimulatedPKB::getInstance().getNextBipStar(2);
			std::unordered_set<int> nextBipStar3 = SimulatedPKB::getInstance().getNextBipStar(3);
			std::unordered_set<int> nextBipStar4 = SimulatedPKB::getInstance().getNextBipStar(4);
			std::unordered_set<int> nextBipStar5 = SimulatedPKB::getInstance().getNextBipStar(5);
			std::unordered_set<int> nextBipStar6 = SimulatedPKB::getInstance().getNextBipStar(6);
			std::unordered_set<int> actualNextBipStar1 = { 4, 5, 6, 2, 3 };
			std::unordered_set<int> actualNextBipStar2 = { 4, 5, 6, 3 };
			std::unordered_set<int> actualNextBipStar3 = { 4, 5, 6 };
			std::unordered_set<int> actualNextBipStar4 = { 5, 6, 2, 4, 3 };
			std::unordered_set<int> actualNextBipStar5 = { 6, 2, 4, 5, 3 };
			std::unordered_set<int> actualNextBipStar6 = { 2, 4, 5, 6, 3 };
			Assert::IsTrue(nextBipStar1 == actualNextBipStar1);
			Assert::IsTrue(nextBipStar2 == actualNextBipStar2);
			Assert::IsTrue(nextBipStar3 == actualNextBipStar3);
			Assert::IsTrue(nextBipStar4 == actualNextBipStar4);
			Assert::IsTrue(nextBipStar5 == actualNextBipStar5);
			Assert::IsTrue(nextBipStar6 == actualNextBipStar6);
		}
		TEST_METHOD(testExtractAffectsBipBasic) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			DesignExtractorTest::getInstance().clearAffectsCache();
			DesignExtractorTest::getInstance().clearAffectsStarCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertProcedure("One");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5});
			SimulatedPKB::getInstance().insertProcedure("Two");
			SimulatedPKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{6, 7, 8});
			SimulatedPKB::getInstance().insertProcedure("Three");
			SimulatedPKB::getInstance().insertProcedureStatementList(2, std::unordered_set<int>{9, 10, 11});
			SimulatedPKB::getInstance().insertStatement(1, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(1, "x");
			SimulatedPKB::getInstance().insertAssignRHS(1, "5");
			SimulatedPKB::getInstance().insertStatement(2, "call");
			SimulatedPKB::getInstance().insertCall(2, "Two");
			SimulatedPKB::getInstance().insertStatement(3, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(3, "y");
			SimulatedPKB::getInstance().insertAssignRHS(3, "x + 6");
			SimulatedPKB::getInstance().insertStatement(4, "call");
			SimulatedPKB::getInstance().insertCall(4, "Three");
			SimulatedPKB::getInstance().insertStatement(5, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(5, "z");
			SimulatedPKB::getInstance().insertAssignRHS(5, "x * y + 2");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(6, "y");
			SimulatedPKB::getInstance().insertAssignRHS(6, "x * 3");
			SimulatedPKB::getInstance().insertStatement(7, "call");
			SimulatedPKB::getInstance().insertCall(7, "Three");
			SimulatedPKB::getInstance().insertStatement(8, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(8, "z");
			SimulatedPKB::getInstance().insertAssignRHS(8, "x + y");
			SimulatedPKB::getInstance().insertStatement(9, "if");
			SimulatedPKB::getInstance().insertStatement(10, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(10, "x");
			SimulatedPKB::getInstance().insertAssignRHS(10, "x + z");
			SimulatedPKB::getInstance().insertStatement(11, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(11, "y");
			SimulatedPKB::getInstance().insertAssignRHS(11, "x * y");

			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(4, 3);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(7, 6);
			SimulatedPKB::getInstance().insertFollows(8, 7);
			SimulatedPKB::getInstance().insertParent(10, 9);
			SimulatedPKB::getInstance().insertParent(11, 9);
			SimulatedPKB::getInstance().insertStatementList(10, { 10 });
			SimulatedPKB::getInstance().insertStatementList(11, { 11 });
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractExtensions();
			std::unordered_set<int> affectsBip1 = SimulatedPKB::getInstance().getAffectsBip(1);
			std::unordered_set<int> affectsBip3 = SimulatedPKB::getInstance().getAffectsBip(3);
			std::unordered_set<int> affectsBip6 = SimulatedPKB::getInstance().getAffectsBip(6);
			std::unordered_set<int> actualAffectsBip1 = { 3, 5, 6, 8, 10, 11 };
			std::unordered_set<int> actualAffectsBip3 = { 5, 11 };
			std::unordered_set<int> actualAffectsBip6 = { 8, 11 };
			Assert::IsTrue(affectsBip1 == actualAffectsBip1);
			Assert::IsTrue(affectsBip3 == actualAffectsBip3);
			Assert::IsTrue(affectsBip6 == actualAffectsBip6);
		}

		TEST_METHOD(testExtractAffectsBipStarMultipleCalls) {
			DesignExtractorTest::getInstance().clearNextStarCache();
			DesignExtractorTest::getInstance().clearAffectsCache();
			DesignExtractorTest::getInstance().clearAffectsStarCache();
			SimulatedPKB::getInstance().clear();
			SimulatedPKB::getInstance().insertProcedure("B");
			SimulatedPKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3});
			SimulatedPKB::getInstance().insertProcedure("C");
			SimulatedPKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{4, 5, 6, 7});
			SimulatedPKB::getInstance().insertStatement(1, "call");
			SimulatedPKB::getInstance().insertStatement(2, "call");
			SimulatedPKB::getInstance().insertStatement(3, "call");
			SimulatedPKB::getInstance().insertCall(1, "C");
			SimulatedPKB::getInstance().insertCall(2, "C");
			SimulatedPKB::getInstance().insertCall(3, "C");
			SimulatedPKB::getInstance().insertStatement(4, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(4, "d");
			SimulatedPKB::getInstance().insertAssignRHS(4, "a");
			SimulatedPKB::getInstance().insertStatement(5, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(5, "a");
			SimulatedPKB::getInstance().insertAssignRHS(5, "b");
			SimulatedPKB::getInstance().insertStatement(6, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(6, "b");
			SimulatedPKB::getInstance().insertAssignRHS(6, "c");
			SimulatedPKB::getInstance().insertStatement(7, "assign");
			SimulatedPKB::getInstance().insertAssignLHS(7, "c");
			SimulatedPKB::getInstance().insertAssignRHS(7, "d");
			SimulatedPKB::getInstance().insertFollows(2, 1);
			SimulatedPKB::getInstance().insertFollows(3, 2);
			SimulatedPKB::getInstance().insertFollows(5, 4);
			SimulatedPKB::getInstance().insertFollows(6, 5);
			SimulatedPKB::getInstance().insertFollows(7, 6);
			DesignExtractorTest::getInstance().extractAllDesigns();
			DesignExtractorTest::getInstance().extractExtensions();
			std::unordered_set<int> affectsBipStar1 = SimulatedPKB::getInstance().getAffectsBipStar(1);
			std::unordered_set<int> affectsBipStar2 = SimulatedPKB::getInstance().getAffectsBipStar(2);
			std::unordered_set<int> affectsBipStar3 = SimulatedPKB::getInstance().getAffectsBipStar(3);
			std::unordered_set<int> affectsBipStar4 = SimulatedPKB::getInstance().getAffectsBipStar(4);
			std::unordered_set<int> affectsBipStar5 = SimulatedPKB::getInstance().getAffectsBipStar(5);
			std::unordered_set<int> affectsBipStar6 = SimulatedPKB::getInstance().getAffectsBipStar(6);
			std::unordered_set<int> affectsBipStar7 = SimulatedPKB::getInstance().getAffectsBipStar(7);
			std::unordered_set<int> actualAffectsBipStar1 = { };
			std::unordered_set<int> actualAffectsBipStar2 = { };
			std::unordered_set<int> actualAffectsBipStar3 = { };
			std::unordered_set<int> actualAffectsBipStar4 = { 7, 6, 5 };
			std::unordered_set<int> actualAffectsBipStar5 = { 4, 7, 6 };
			std::unordered_set<int> actualAffectsBipStar6 = { 5, 4, 7 };
			std::unordered_set<int> actualAffectsBipStar7 = { 6, 5 };
			Assert::IsTrue(affectsBipStar1 == actualAffectsBipStar1);
			Assert::IsTrue(affectsBipStar2 == actualAffectsBipStar2);
			Assert::IsTrue(affectsBipStar3 == actualAffectsBipStar3);
			Assert::IsTrue(affectsBipStar4 == actualAffectsBipStar4);
			Assert::IsTrue(affectsBipStar5 == actualAffectsBipStar5);
			Assert::IsTrue(affectsBipStar6 == actualAffectsBipStar6);
			Assert::IsTrue(affectsBipStar7 == actualAffectsBipStar7);
		}
	};
}
