#include "CppUnitTest.h"
#include "stdafx.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "../source/Parser.h"
#include "../source/PKB/PKB.h"
#include "../source/DesignExtractor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTesting {
	TEST_CLASS(TestDEPKB) {
public:
	TEST_METHOD(testExtractFollowStar) {
		PKB::getInstance().clear();
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(4, 3);
		DesignExtractor::getInstance().extractFollowsStar();
		// Test that both Follows and FollowedBy are stored
		Assert::AreEqual(true, PKB::getInstance().getFollowsStar(4) == std::unordered_set<int>{ 1, 2, 3 });
		Assert::AreEqual(true, PKB::getInstance().getFollowsStar(3) == std::unordered_set<int>{ 1, 2 });
		Assert::AreEqual(true, PKB::getInstance().getFollowedByStar(1) == std::unordered_set<int>{ 2, 3, 4 });
		Assert::AreEqual(true, PKB::getInstance().getFollowedByStar(2) == std::unordered_set<int>{ 3, 4 });

		// Test no wrongful extraction
		Assert::AreEqual(false, PKB::getInstance().getFollowsStar(4) == std::unordered_set<int>{ 1 });
		Assert::AreEqual(false, PKB::getInstance().getFollowsStar(1) == std::unordered_set<int>{ 4 });
		Assert::AreEqual(false, PKB::getInstance().getFollowedByStar(4) == std::unordered_set<int>{ 3 });
		Assert::AreEqual(false, PKB::getInstance().getFollowedByStar(1) == std::unordered_set<int>{ 5 });
	}

	TEST_METHOD(testExtractParentStar) {
		PKB::getInstance().clear();
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 2);
		PKB::getInstance().insertParent(4, 3);
		DesignExtractor::getInstance().extractParentStar();
		// Test that both Parent and Child relationship are stored
		Assert::AreEqual(true, PKB::getInstance().getParentStar(4) == std::unordered_set<int>{ 1, 2, 3 });
		Assert::AreEqual(true, PKB::getInstance().getParentStar(3) == std::unordered_set<int>{ 1, 2 });
		Assert::AreEqual(true, PKB::getInstance().getChildStar(1) == std::unordered_set<int>{ 2, 3, 4 });
		Assert::AreEqual(true, PKB::getInstance().getChildStar(2) == std::unordered_set<int>{ 3, 4 });
		// Test no wrongful extraction
		Assert::AreEqual(false, PKB::getInstance().getParentStar(4) == std::unordered_set<int>{ 1 });
		Assert::AreEqual(false, PKB::getInstance().getParentStar(1) == std::unordered_set<int>{ 4 });
		Assert::AreEqual(false, PKB::getInstance().getChildStar(4) == std::unordered_set<int>{ 3 });
		Assert::AreEqual(false, PKB::getInstance().getChildStar(1) == std::unordered_set<int>{ 5 });
	}

	TEST_METHOD(testExtractUsesAndModifies) {

		// This test is for multiple procedures for uses and modifies
		PKB::getInstance().clear();
		PKB::getInstance().insertProcedure("procOne"); //index0
		PKB::getInstance().insertProcedure("procTwo"); //index1
		PKB::getInstance().insertProcedure("procThree"); //index2
		PKB::getInstance().insertProcedure("procFour"); //index3
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4});
		PKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{5, 6, 7, 8, 9, 10});
		PKB::getInstance().insertProcedureStatementList(2, std::unordered_set<int>{11, 12, 13});
		PKB::getInstance().insertProcedureStatementList(3, std::unordered_set<int>{14, 15, 16, 17, 18, 19, 20});
		PKB::getInstance().insertIf(1, { "varOne", "varTwo" });
		PKB::getInstance().insertAssignLHS(2, "varThree");
		PKB::getInstance().insertAssignRHS(2, "varFour");
		PKB::getInstance().insertCall(3, "procTwo");
		PKB::getInstance().insertPrint(4, "varOne");
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 1);
		PKB::getInstance().insertParent(4, 1);
		PKB::getInstance().insertCall(5, "procThree");
		PKB::getInstance().insertWhile(6, { "varFive", "varSix" });
		PKB::getInstance().insertRead(7, "varSeven");
		PKB::getInstance().insertWhile(8, { "varEight", "varNine" });
		PKB::getInstance().insertParent(7, 6);
		PKB::getInstance().insertParent(8, 6);
		PKB::getInstance().insertCall(9, "procFour");
		PKB::getInstance().insertAssignLHS(10, "varTen");
		PKB::getInstance().insertAssignRHS(10, "varEleven + 2000");
		PKB::getInstance().insertParent(9, 8);
		PKB::getInstance().insertParent(10, 8);
		PKB::getInstance().insertAssignLHS(11, "varTwelve");
		PKB::getInstance().insertAssignRHS(11, "varThirteen");
		PKB::getInstance().insertIf(12, { "varFourteen", "varFifteen" });
		PKB::getInstance().insertPrint(13, "varTwelve");
		PKB::getInstance().insertParent(13, 12);
		PKB::getInstance().insertRead(14, "varFifteen");
		PKB::getInstance().insertPrint(15, "varSixteen");
		PKB::getInstance().insertIf(16, { "varSixteen", "varFifteen" });
		PKB::getInstance().insertWhile(17, { "varSeventeen" });
		PKB::getInstance().insertParent(17, 16);
		PKB::getInstance().insertIf(18, { "varEighteen", "varNineteen" });
		PKB::getInstance().insertParent(18, 17);
		PKB::getInstance().insertAssignLHS(19, "varTwenty");
		PKB::getInstance().insertAssignRHS(19, "2");
		PKB::getInstance().insertPrint(20, "varTwentyOne");
		PKB::getInstance().insertParent(19, 18);
		PKB::getInstance().insertParent(20, 18);
		DesignExtractor::getInstance().extractAllDesigns();

		// checks if all uses from nested calls are extracted
		Assert::AreEqual(true, PKB::getInstance().getUses(1) == std::unordered_set< std::string>{
			"varOne", "varTwo", "varFour", "varFive", "varSix", "varEight", "varNine", "varEleven", "varThirteen", "varFourteen", "varFifteen", "varTwelve", "varSixteen", "varSeventeen", "varEighteen",
				"varNineteen", "varTwentyOne"
		});
		Assert::AreEqual(true, PKB::getInstance().getUses(3) == std::unordered_set< std::string>{
			"varFive", "varSix", "varEight", "varNine", "varEleven", "varThirteen", "varFourteen", "varFifteen", "varTwelve", "varSixteen", "varSeventeen", "varEighteen",
				"varNineteen", "varTwentyOne"
		});
		Assert::AreEqual(true, PKB::getInstance().getUses(5) == std::unordered_set< std::string>{
			"varThirteen", "varFourteen", "varFifteen", "varTwelve"
		});
		Assert::AreEqual(true, PKB::getInstance().getUses(9) == std::unordered_set< std::string>{
			"varSixteen", "varSeventeen", "varFifteen", "varEighteen", "varNineteen", "varTwentyOne"
		});

		// checks if all modifies from nested calls are extracted
		Assert::AreEqual(true, PKB::getInstance().getModifies(1) == std::unordered_set< std::string>{
			"varThree", "varSeven", "varTen", "varTwelve", "varFifteen", "varTwenty"
		});
		Assert::AreEqual(true, PKB::getInstance().getModifies(3) == std::unordered_set< std::string>{
			"varSeven", "varTen", "varTwelve", "varFifteen", "varTwenty"
		});
		Assert::AreEqual(true, PKB::getInstance().getModifies(5) == std::unordered_set< std::string>{
			"varTwelve"
		});
		Assert::AreEqual(true, PKB::getInstance().getModifies(9) == std::unordered_set< std::string>{
			"varFifteen", "varTwenty"
		});

	}

	TEST_METHOD(testExtractUsesAndModifiesForProcedure) {
		// This tests for only a single procedure
		PKB::getInstance().clear();
		// forming basic design entities
		PKB::getInstance().insertProcedure("main");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
		PKB::getInstance().insertAssignLHS(1, "varOne");
		PKB::getInstance().insertAssignRHS(1, "varTwo");
		PKB::getInstance().insertAssignLHS(2, "varThree");
		PKB::getInstance().insertAssignRHS(2, "varFour");
		PKB::getInstance().insertPrint(4, "printVarOne");
		PKB::getInstance().insertPrint(5, "printVarTwo");
		PKB::getInstance().insertRead(7, "readVarOne");
		PKB::getInstance().insertRead(8, "readVarTwo");
		PKB::getInstance().insertIf(9, { "condVarOne" });
		PKB::getInstance().insertIf(10, { "condVarTwo", "condVarThree" });
		PKB::getInstance().insertWhile(11, { "condVarFour" });
		PKB::getInstance().insertWhile(12, { "condVarFive", "condVarSix" });
		// forming basic design
		PKB::getInstance().insertAssignLHS(13, "varFive");
		PKB::getInstance().insertAssignRHS(13, "varSix");
		PKB::getInstance().insertPrint(14, "printVarThree");
		PKB::getInstance().insertRead(15, "readVarThree");
		PKB::getInstance().insertParent(13, 12);
		PKB::getInstance().insertParent(14, 12);
		PKB::getInstance().insertParent(15, 12);

		DesignExtractor::getInstance().extractParentStar();
		DesignExtractor::getInstance().extractUsesAndModifies();

		// Test Extraction of Uses and Modifies for assign statements
		Assert::AreEqual(true, PKB::getInstance().getUses(1) == std::unordered_set< std::string>{"varTwo" });
		Assert::AreEqual(true, PKB::getInstance().getUses(2) == std::unordered_set< std::string>{"varFour"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(1) == std::unordered_set< std::string>{"varOne"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(2) == std::unordered_set< std::string>{"varThree"});

		// Test no wrong extraction of Uses and Modifies for assign statements
		Assert::AreEqual(false, PKB::getInstance().getUses(1) == std::unordered_set< std::string>{"varOne"});
		Assert::AreEqual(false, PKB::getInstance().getUses(2) == std::unordered_set< std::string>{"varTwo"});
		Assert::AreEqual(false, PKB::getInstance().getModifies(1) == std::unordered_set< std::string>{"varTwo"});
		Assert::AreEqual(false, PKB::getInstance().getModifies(2) == std::unordered_set< std::string>{"varFour"});

		// Test Extraction of Uses for print statements
		Assert::AreEqual(true, PKB::getInstance().getUses(4) == std::unordered_set< std::string>{"printVarOne"});
		Assert::AreEqual(true, PKB::getInstance().getUses(5) == std::unordered_set< std::string>{"printVarTwo"});

		// Test no wrong extraction of Uses and Modifies for print statements
		Assert::AreEqual(false, PKB::getInstance().getUses(1) == std::unordered_set< std::string>{"printVarOne"});
		Assert::AreEqual(false, PKB::getInstance().getUses(2) == std::unordered_set< std::string>{"printVarTwo"});

		// Test Extraction of Uses for read statements
		Assert::AreEqual(true, PKB::getInstance().getModifies(7) == std::unordered_set< std::string>{"readVarOne"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(8) == std::unordered_set< std::string>{"readVarTwo"});

		// Test no wrong extraction of uses for read statements
		Assert::AreEqual(false, PKB::getInstance().getModifies(7) == std::unordered_set< std::string>{"printVarOne"});
		Assert::AreEqual(false, PKB::getInstance().getModifies(9) == std::unordered_set< std::string>{"printVarOne"});

		// Test if uses can be extracted for if and while(containers)'s conditions
		Assert::AreEqual(true, PKB::getInstance().getUses(9) == std::unordered_set< std::string>{"condVarOne"});
		Assert::AreEqual(true, PKB::getInstance().getUses(10) == std::unordered_set< std::string>{"condVarTwo", "condVarThree"});
		Assert::AreEqual(true, PKB::getInstance().getUses(11) == std::unordered_set< std::string>{"condVarFour"});

		// Test no wrong extraction of uses for if and while(containers)'s conditions 
		Assert::AreEqual(false, PKB::getInstance().getUses(9) == std::unordered_set< std::string>{"1"});
		Assert::AreEqual(false, PKB::getInstance().getUses(11) == std::unordered_set< std::string>{"condVarOne"});
		Assert::AreEqual(false, PKB::getInstance().getUses(11) == std::unordered_set< std::string>{"readVarTwo"});
		Assert::AreEqual(false, PKB::getInstance().getUses(14) == std::unordered_set< std::string>{"condVarOne"});

		// Test if uses and modifies can be extracted for if and while(containers)'s statements
		Assert::AreEqual(true, PKB::getInstance().getUses(12) == std::unordered_set< std::string>{"condVarFive", "condVarSix", "varSix", "printVarThree"});
		Assert::AreEqual(true, PKB::getInstance().getUses(13) == std::unordered_set< std::string>{"varSix"});
		Assert::AreEqual(true, PKB::getInstance().getUses(14) == std::unordered_set< std::string>{"printVarThree"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(12) == std::unordered_set< std::string>{"varFive", "readVarThree"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(13) == std::unordered_set< std::string>{"varFive"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(15) == std::unordered_set< std::string>{"readVarThree"});

		// Test no wrong extraction of uses and modifies for if and while(containers)'s statements 
		Assert::AreEqual(false, PKB::getInstance().getUses(12) == std::unordered_set< std::string>{"condVarFive"});
		Assert::AreEqual(false, PKB::getInstance().getUses(12) == std::unordered_set< std::string>{"varFive", "readVarThree"});
		Assert::AreEqual(false, PKB::getInstance().getModifies(12) == std::unordered_set< std::string>{"condVarFive", "varSix", "printVarThree"});
		Assert::AreEqual(false, PKB::getInstance().getModifies(13) == std::unordered_set< std::string>{"varSix"});


		// Test for multiple nested loops
		PKB::getInstance().insertProcedure("main");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{20, 21, 22, 23, 24, 25, 26, 27, 28});
		PKB::getInstance().insertWhile(20, { "varA", "varB" });
		PKB::getInstance().insertWhile(21, { "varC", "varD" });
		PKB::getInstance().insertParent(21, 20);
		PKB::getInstance().insertAssignLHS(22, "varE");
		PKB::getInstance().insertAssignRHS(22, "varF");
		PKB::getInstance().insertParent(22, 21);
		PKB::getInstance().insertPrint(23, "varG");
		PKB::getInstance().insertParent(23, 21);
		PKB::getInstance().insertWhile(24, { "varH", "varI" });
		PKB::getInstance().insertParent(24, 21);
		PKB::getInstance().insertAssignLHS(25, "varJ");
		PKB::getInstance().insertAssignRHS(25, "varK");
		PKB::getInstance().insertParent(25, 24);
		PKB::getInstance().insertPrint(26, "varJ");
		PKB::getInstance().insertParent(26, 24);
		PKB::getInstance().insertAssignLHS(27, "varL");
		PKB::getInstance().insertAssignRHS(27, "varM");
		PKB::getInstance().insertParent(27, 24);
		PKB::getInstance().insertPrint(28, "varN");
		PKB::getInstance().insertParent(28, 21);
		DesignExtractor::getInstance().extractAllDesigns();
		Assert::AreEqual(true, PKB::getInstance().getUses(20) == std::unordered_set< std::string>{"varA", "varB", "varC", "varD", "varF", "varG", "varH", "varI", "varK", "varJ", "varM", "varN"});
		Assert::AreEqual(true, PKB::getInstance().getUses(21) == std::unordered_set< std::string>{"varC", "varD", "varF", "varG", "varH", "varI", "varK", "varJ", "varM", "varN"});
		Assert::AreEqual(true, PKB::getInstance().getUses(24) == std::unordered_set< std::string>{"varH", "varI", "varK", "varJ", "varM"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(20) == std::unordered_set< std::string>{"varE", "varJ", "varL"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(21) == std::unordered_set< std::string>{"varE", "varJ", "varL"});
		Assert::AreEqual(true, PKB::getInstance().getModifies(24) == std::unordered_set< std::string>{"varJ", "varL"});


		std::unordered_set<std::string> s = PKB::getInstance().getUses(21);
		Assert::AreEqual(true, s.find("varH") != s.end());
		PKB::getInstance().clear();

	}

	TEST_METHOD(testExtractNextNoFollower) {
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "if");
		PKB::getInstance().insertStatement(2, "while");
		PKB::getInstance().insertStatement(3, "assign");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 2);
		PKB::getInstance().insertParent(4, 1);
		PKB::getInstance().insertParent(5, 1);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertStatementList(2, { 2 });
		PKB::getInstance().insertStatementList(3, { 3 });
		PKB::getInstance().insertStatementList(4, { 4, 5 });
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> next1 = PKB::getInstance().getNext(1);
		std::unordered_set<int> next2 = PKB::getInstance().getNext(2);
		std::unordered_set<int> next3 = PKB::getInstance().getNext(3);
		std::unordered_set<int> next4 = PKB::getInstance().getNext(4);
		std::unordered_set<int> next5 = PKB::getInstance().getNext(5);
		std::unordered_set<int> actualNext1 = { 2, 4 };
		std::unordered_set<int> actualNext2 = { 3 };
		std::unordered_set<int> actualNext3 = { 2 };
		std::unordered_set<int> actualNext4 = { 5 };
		std::unordered_set<int> actualNext5 = { };
		PKB::getInstance().clear();
		Assert::IsTrue(next1 == actualNext1);
		Assert::IsTrue(next2 == actualNext2);
		Assert::IsTrue(next3 == actualNext3);
		Assert::IsTrue(next4 == actualNext4);
		Assert::IsTrue(next5 == actualNext5);
	}

	TEST_METHOD(testExtractNextWhileFollower) {
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "while");
		PKB::getInstance().insertStatement(2, "if");
		PKB::getInstance().insertStatement(3, "while");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertStatement(5, "while");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertStatement(7, "assign");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 2);
		PKB::getInstance().insertParent(7, 2);
		PKB::getInstance().insertParent(8, 2);
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 5);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(8, 7);
		PKB::getInstance().insertStatementList(2, { 2 });
		PKB::getInstance().insertStatementList(3, { 3 });
		PKB::getInstance().insertStatementList(4, { 4, 5 });
		PKB::getInstance().insertStatementList(6, { 6 });
		PKB::getInstance().insertStatementList(7, { 7, 8 });
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> next1 = PKB::getInstance().getNext(1);
		std::unordered_set<int> next2 = PKB::getInstance().getNext(2);
		std::unordered_set<int> next3 = PKB::getInstance().getNext(3);
		std::unordered_set<int> next4 = PKB::getInstance().getNext(4);
		std::unordered_set<int> next5 = PKB::getInstance().getNext(5);
		std::unordered_set<int> next6 = PKB::getInstance().getNext(6);
		std::unordered_set<int> next7 = PKB::getInstance().getNext(7);
		std::unordered_set<int> next8 = PKB::getInstance().getNext(8);
		std::unordered_set<int> actualNext1 = { 2 };
		std::unordered_set<int> actualNext2 = { 3, 7 };
		std::unordered_set<int> actualNext3 = { 1, 4 };
		std::unordered_set<int> actualNext4 = { 5 };
		std::unordered_set<int> actualNext5 = { 3, 6 };
		std::unordered_set<int> actualNext6 = { 5 };
		std::unordered_set<int> actualNext7 = { 8 };
		std::unordered_set<int> actualNext8 = { 1 };
		PKB::getInstance().clear();
		Assert::IsTrue(next1 == actualNext1);
		Assert::IsTrue(next2 == actualNext2);
		Assert::IsTrue(next3 == actualNext3);
		Assert::IsTrue(next4 == actualNext4);
		Assert::IsTrue(next5 == actualNext5);
		Assert::IsTrue(next6 == actualNext6);
		Assert::IsTrue(next7 == actualNext7);
		Assert::IsTrue(next8 == actualNext8);
	}

	TEST_METHOD(testExtractNextBothFollower) {
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "while");
		PKB::getInstance().insertStatement(2, "if");
		PKB::getInstance().insertStatement(3, "while");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertStatement(5, "while");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertStatement(7, "assign");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 2);
		PKB::getInstance().insertParent(7, 2);
		PKB::getInstance().insertParent(8, 2);
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 5);
		PKB::getInstance().insertFollows(9, 1);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(8, 7);
		PKB::getInstance().insertStatementList(2, { 2 });
		PKB::getInstance().insertStatementList(3, { 3 });
		PKB::getInstance().insertStatementList(4, { 4, 5 });
		PKB::getInstance().insertStatementList(6, { 6 });
		PKB::getInstance().insertStatementList(7, { 7, 8 });
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> next1 = PKB::getInstance().getNext(1);
		std::unordered_set<int> next2 = PKB::getInstance().getNext(2);
		std::unordered_set<int> next3 = PKB::getInstance().getNext(3);
		std::unordered_set<int> next4 = PKB::getInstance().getNext(4);
		std::unordered_set<int> next5 = PKB::getInstance().getNext(5);
		std::unordered_set<int> next6 = PKB::getInstance().getNext(6);
		std::unordered_set<int> next7 = PKB::getInstance().getNext(7);
		std::unordered_set<int> next8 = PKB::getInstance().getNext(8);
		std::unordered_set<int> next9 = PKB::getInstance().getNext(9);
		std::unordered_set<int> actualNext1 = { 2, 9 };
		std::unordered_set<int> actualNext2 = { 3, 7 };
		std::unordered_set<int> actualNext3 = { 1, 4 };
		std::unordered_set<int> actualNext4 = { 5 };
		std::unordered_set<int> actualNext5 = { 3, 6 };
		std::unordered_set<int> actualNext6 = { 5 };
		std::unordered_set<int> actualNext7 = { 8 };
		std::unordered_set<int> actualNext8 = { 1 };
		std::unordered_set<int> actualNext9 = { };
		PKB::getInstance().clear();
		Assert::IsTrue(next1 == actualNext1);
		Assert::IsTrue(next2 == actualNext2);
		Assert::IsTrue(next3 == actualNext3);
		Assert::IsTrue(next4 == actualNext4);
		Assert::IsTrue(next5 == actualNext5);
		Assert::IsTrue(next6 == actualNext6);
		Assert::IsTrue(next7 == actualNext7);
		Assert::IsTrue(next8 == actualNext8);
		Assert::IsTrue(next9 == actualNext9);
	}


	TEST_METHOD(testExtractNextComplex) {
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "print");
		PKB::getInstance().insertStatement(2, "read");
		PKB::getInstance().insertStatement(3, "if");
		PKB::getInstance().insertStatement(4, "print");
		PKB::getInstance().insertStatement(5, "read");
		PKB::getInstance().insertStatement(6, "read");
		PKB::getInstance().insertStatement(7, "print");
		PKB::getInstance().insertStatement(8, "if");
		PKB::getInstance().insertStatement(9, "if");
		PKB::getInstance().insertStatement(10, "read");
		PKB::getInstance().insertStatement(11, "read");
		PKB::getInstance().insertStatement(12, "while");
		PKB::getInstance().insertStatement(13, "while");
		PKB::getInstance().insertStatement(14, "read");
		PKB::getInstance().insertStatement(15, "assign");
		PKB::getInstance().insertStatement(16, "read");
		PKB::getInstance().insertStatement(17, "read");
		PKB::getInstance().insertStatement(18, "print");
		PKB::getInstance().insertStatement(19, "print");
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 3);
		PKB::getInstance().insertParent(7, 3);
		PKB::getInstance().insertParent(9, 8);
		PKB::getInstance().insertParent(18, 8);
		PKB::getInstance().insertParent(10, 9);
		PKB::getInstance().insertParent(11, 9);
		PKB::getInstance().insertParent(12, 9);
		PKB::getInstance().insertParent(17, 9);
		PKB::getInstance().insertParent(13, 12);
		PKB::getInstance().insertParent(16, 12);
		PKB::getInstance().insertParent(14, 13);
		PKB::getInstance().insertParent(15, 13);
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(8, 3);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(7, 6);
		PKB::getInstance().insertFollows(19, 8);
		PKB::getInstance().insertFollows(11, 10);
		PKB::getInstance().insertFollows(17, 12);
		PKB::getInstance().insertFollows(16, 13);
		PKB::getInstance().insertFollows(15, 14);
		PKB::getInstance().insertStatementList(4, { 4, 5 });
		PKB::getInstance().insertStatementList(6, { 6, 7 });
		PKB::getInstance().insertStatementList(9, { 9 });
		PKB::getInstance().insertStatementList(10, { 10, 11 });
		PKB::getInstance().insertStatementList(12, { 12, 17 });
		PKB::getInstance().insertStatementList(13, { 13, 16 });
		PKB::getInstance().insertStatementList(14, { 14, 15 });
		PKB::getInstance().insertStatementList(18, { 18 });
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> next1 = PKB::getInstance().getNext(1);
		std::unordered_set<int> next2 = PKB::getInstance().getNext(2);
		std::unordered_set<int> next3 = PKB::getInstance().getNext(3);
		std::unordered_set<int> next4 = PKB::getInstance().getNext(4);
		std::unordered_set<int> next5 = PKB::getInstance().getNext(5);
		std::unordered_set<int> next6 = PKB::getInstance().getNext(6);
		std::unordered_set<int> next7 = PKB::getInstance().getNext(7);
		std::unordered_set<int> next8 = PKB::getInstance().getNext(8);
		std::unordered_set<int> next9 = PKB::getInstance().getNext(9);
		std::unordered_set<int> next10 = PKB::getInstance().getNext(10);
		std::unordered_set<int> next11 = PKB::getInstance().getNext(11);
		std::unordered_set<int> next12 = PKB::getInstance().getNext(12);
		std::unordered_set<int> next13 = PKB::getInstance().getNext(13);
		std::unordered_set<int> next14 = PKB::getInstance().getNext(14);
		std::unordered_set<int> next15 = PKB::getInstance().getNext(15);
		std::unordered_set<int> next16 = PKB::getInstance().getNext(16);
		std::unordered_set<int> next17 = PKB::getInstance().getNext(17);
		std::unordered_set<int> next18 = PKB::getInstance().getNext(18);
		std::unordered_set<int> next19 = PKB::getInstance().getNext(19);
		std::unordered_set<int> actualNext1 = { 2 };
		std::unordered_set<int> actualNext2 = { 3 };
		std::unordered_set<int> actualNext3 = { 4, 6 };
		std::unordered_set<int> actualNext4 = { 5 };
		std::unordered_set<int> actualNext5 = { 8 };
		std::unordered_set<int> actualNext6 = { 7 };
		std::unordered_set<int> actualNext7 = { 8 };
		std::unordered_set<int> actualNext8 = { 9, 18 };
		std::unordered_set<int> actualNext9 = { 10, 12 };
		std::unordered_set<int> actualNext10 = { 11 };
		std::unordered_set<int> actualNext11 = { 19 };
		std::unordered_set<int> actualNext12 = { 13, 17 };
		std::unordered_set<int> actualNext13 = { 14, 16 };
		std::unordered_set<int> actualNext14 = { 15 };
		std::unordered_set<int> actualNext15 = { 13 };
		std::unordered_set<int> actualNext16 = { 12 };
		std::unordered_set<int> actualNext17 = { 19 };
		std::unordered_set<int> actualNext18 = { 19 };
		std::unordered_set<int> actualNext19 = { };
		PKB::getInstance().clear();
		Assert::IsTrue(next1 == actualNext1);
		Assert::IsTrue(next2 == actualNext2);
		Assert::IsTrue(next3 == actualNext3);
		Assert::IsTrue(next4 == actualNext4);
		Assert::IsTrue(next5 == actualNext5);
		Assert::IsTrue(next6 == actualNext6);
		Assert::IsTrue(next7 == actualNext7);
		Assert::IsTrue(next8 == actualNext8);
		Assert::IsTrue(next9 == actualNext9);
		Assert::IsTrue(next10 == actualNext10);
		Assert::IsTrue(next11 == actualNext11);
		Assert::IsTrue(next12 == actualNext12);
		Assert::IsTrue(next13 == actualNext13);
		Assert::IsTrue(next14 == actualNext14);
		Assert::IsTrue(next15 == actualNext15);
		Assert::IsTrue(next16 == actualNext16);
		Assert::IsTrue(next17 == actualNext17);
		Assert::IsTrue(next18 == actualNext18);
		Assert::IsTrue(next19 == actualNext19);
	}

	TEST_METHOD(testExtractNextNested) {
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "while");
		PKB::getInstance().insertStatement(2, "if");
		PKB::getInstance().insertStatement(3, "call");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 2);
		PKB::getInstance().insertParent(4, 2);
		PKB::getInstance().insertParent(5, 2);
		PKB::getInstance().insertFollows(4, 3);
		PKB::getInstance().insertStatementList(2, { 2 });
		PKB::getInstance().insertStatementList(3, { 3, 4 });
		PKB::getInstance().insertStatementList(5, { 5 });
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> next1 = PKB::getInstance().getNext(1);
		std::unordered_set<int> next2 = PKB::getInstance().getNext(2);
		std::unordered_set<int> next3 = PKB::getInstance().getNext(3);
		std::unordered_set<int> next4 = PKB::getInstance().getNext(4);
		std::unordered_set<int> next5 = PKB::getInstance().getNext(5);
		std::unordered_set<int> actualNext1 = { 2 };
		std::unordered_set<int> actualNext2 = { 3, 5 };
		std::unordered_set<int> actualNext3 = { 4 };
		std::unordered_set<int> actualNext4 = { 1 };
		std::unordered_set<int> actualNext5 = { 1 };
		PKB::getInstance().clear();
		Assert::IsTrue(next1 == actualNext1);
		Assert::IsTrue(next2 == actualNext2);
		Assert::IsTrue(next3 == actualNext3);
		Assert::IsTrue(next4 == actualNext4);
		Assert::IsTrue(next5 == actualNext5);
	}

	TEST_METHOD(testGetNextStar) {

		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "while");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertStatement(3, "assign");
		PKB::getInstance().insertStatement(4, "while");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertStatement(6, "if");
		PKB::getInstance().insertStatement(7, "assign");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertStatement(13, "assign");
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 1);
		PKB::getInstance().insertParent(4, 1);
		PKB::getInstance().insertParent(5, 4);
		PKB::getInstance().insertParent(6, 4);
		PKB::getInstance().insertParent(7, 6);
		PKB::getInstance().insertParent(8, 6);
		PKB::getInstance().insertParent(9, 6);
		PKB::getInstance().insertParent(10, 4);
		PKB::getInstance().insertParent(11, 1);
		PKB::getInstance().insertParent(12, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(4, 3);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(8, 7);
		PKB::getInstance().insertFollows(10, 6);
		PKB::getInstance().insertFollows(11, 4);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertFollows(13, 1);
		PKB::getInstance().insertStatementList(2, { 2, 3, 4, 11, 12 });
		PKB::getInstance().insertStatementList(5, { 5, 6, 10 });
		PKB::getInstance().insertStatementList(7, { 7, 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> nextStar1 = DesignExtractor::getInstance().getNextStar(1);
		std::unordered_set<int> nextStar2 = DesignExtractor::getInstance().getNextStar(2);
		std::unordered_set<int> nextStar3 = DesignExtractor::getInstance().getNextStar(3);
		std::unordered_set<int> nextStar4 = DesignExtractor::getInstance().getNextStar(4);
		std::unordered_set<int> nextStar5 = DesignExtractor::getInstance().getNextStar(5);
		std::unordered_set<int> nextStar6 = DesignExtractor::getInstance().getNextStar(6);
		std::unordered_set<int> nextStar7 = DesignExtractor::getInstance().getNextStar(7);
		std::unordered_set<int> nextStar8 = DesignExtractor::getInstance().getNextStar(8);
		std::unordered_set<int> nextStar9 = DesignExtractor::getInstance().getNextStar(9);
		std::unordered_set<int> nextStar10 = DesignExtractor::getInstance().getNextStar(10);
		std::unordered_set<int> nextStar11 = DesignExtractor::getInstance().getNextStar(11);
		std::unordered_set<int> nextStar12 = DesignExtractor::getInstance().getNextStar(12);
		std::unordered_set<int> nextStar13 = DesignExtractor::getInstance().getNextStar(13);

		std::unordered_set<int> actualNextStar1 = { 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar5 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar6 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar7 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar8 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar9 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar10 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar11 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar12 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		std::unordered_set<int> actualNextStar13 = { };

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
		Assert::IsTrue(nextStar13 == actualNextStar13);
	}

	TEST_METHOD(testIsNextStar) {
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "while");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertStatement(3, "assign");
		PKB::getInstance().insertStatement(4, "while");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertStatement(6, "if");
		PKB::getInstance().insertStatement(7, "assign");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertStatement(13, "assign");
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 1);
		PKB::getInstance().insertParent(4, 1);
		PKB::getInstance().insertParent(5, 4);
		PKB::getInstance().insertParent(6, 4);
		PKB::getInstance().insertParent(7, 6);
		PKB::getInstance().insertParent(8, 6);
		PKB::getInstance().insertParent(9, 6);
		PKB::getInstance().insertParent(10, 4);
		PKB::getInstance().insertParent(11, 1);
		PKB::getInstance().insertParent(12, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(4, 3);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(8, 7);
		PKB::getInstance().insertFollows(10, 6);
		PKB::getInstance().insertFollows(11, 4);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertFollows(13, 1);
		PKB::getInstance().insertStatementList(2, { 2, 3, 4, 11, 12 });
		PKB::getInstance().insertStatementList(5, { 5, 6, 10 });
		PKB::getInstance().insertStatementList(7, { 7, 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		DesignExtractor::getInstance().extractNext();
		Assert::IsTrue(true == DesignExtractor::getInstance().isNextStar(1, 2));
		Assert::IsTrue(true == DesignExtractor::getInstance().isNextStar(1, 12));
		Assert::IsTrue(true == DesignExtractor::getInstance().isNextStar(5, 6));
		Assert::IsTrue(true == DesignExtractor::getInstance().isNextStar(11, 12));

		Assert::IsTrue(false == DesignExtractor::getInstance().isNextStar(12, 18));
		Assert::IsTrue(false == DesignExtractor::getInstance().isNextStar(1, 19));

	}

	TEST_METHOD(testGetPreviousStar) {
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "while");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertStatement(3, "assign");
		PKB::getInstance().insertStatement(4, "while");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertStatement(6, "if");
		PKB::getInstance().insertStatement(7, "assign");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertStatement(13, "assign");
		PKB::getInstance().insertParent(2, 1);
		PKB::getInstance().insertParent(3, 1);
		PKB::getInstance().insertParent(4, 1);
		PKB::getInstance().insertParent(5, 4);
		PKB::getInstance().insertParent(6, 4);
		PKB::getInstance().insertParent(7, 6);
		PKB::getInstance().insertParent(8, 6);
		PKB::getInstance().insertParent(9, 6);
		PKB::getInstance().insertParent(10, 4);
		PKB::getInstance().insertParent(11, 1);
		PKB::getInstance().insertParent(12, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(4, 3);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(8, 7);
		PKB::getInstance().insertFollows(10, 6);
		PKB::getInstance().insertFollows(11, 4);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertFollows(13, 1);
		PKB::getInstance().insertStatementList(2, { 2, 3, 4, 11, 12 });
		PKB::getInstance().insertStatementList(5, { 5, 6, 10 });
		PKB::getInstance().insertStatementList(7, { 7, 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> previousStar1 = DesignExtractor::getInstance().getPreviousStar(1);
		std::unordered_set<int> previousStar2 = DesignExtractor::getInstance().getPreviousStar(2);
		std::unordered_set<int> previousStar3 = DesignExtractor::getInstance().getPreviousStar(3);
		std::unordered_set<int> previousStar4 = DesignExtractor::getInstance().getPreviousStar(4);
		std::unordered_set<int> previousStar5 = DesignExtractor::getInstance().getPreviousStar(5);
		std::unordered_set<int> previousStar6 = DesignExtractor::getInstance().getPreviousStar(6);
		std::unordered_set<int> previousStar7 = DesignExtractor::getInstance().getPreviousStar(7);
		std::unordered_set<int> previousStar8 = DesignExtractor::getInstance().getPreviousStar(8);
		std::unordered_set<int> previousStar9 = DesignExtractor::getInstance().getPreviousStar(9);
		std::unordered_set<int> previousStar10 = DesignExtractor::getInstance().getPreviousStar(10);
		std::unordered_set<int> previousStar11 = DesignExtractor::getInstance().getPreviousStar(11);
		std::unordered_set<int> previousStar12 = DesignExtractor::getInstance().getPreviousStar(12);
		std::unordered_set<int> previousStar13 = DesignExtractor::getInstance().getPreviousStar(13);

		std::unordered_set<int> actualPreviousStar1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar2 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar5 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar6 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar7 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar8 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar9 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar10 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar11 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar12 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		std::unordered_set<int> actualPreviousStar13 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

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
		Assert::IsTrue(previousStar13 == actualPreviousStar13);
	}

	TEST_METHOD(testGetAffectsBasic) {
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertAssignLHS(1, "x");
		PKB::getInstance().insertAssignRHS(1, "0");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertAssignLHS(2, "i");
		PKB::getInstance().insertAssignRHS(2, "5");
		PKB::getInstance().insertStatement(3, "while");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertAssignLHS(4, "x");
		PKB::getInstance().insertAssignRHS(4, "x + 2*y");
		PKB::getInstance().insertStatement(5, "call");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertAssignLHS(6, "i");
		PKB::getInstance().insertAssignRHS(6, "i - 1");
		PKB::getInstance().insertStatement(7, "if");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertAssignLHS(8, "x");
		PKB::getInstance().insertAssignRHS(8, "x + 1");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertAssignLHS(9, "z");
		PKB::getInstance().insertAssignRHS(9, "1");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertAssignLHS(10, "z");
		PKB::getInstance().insertAssignRHS(10, "z + x + i");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertAssignLHS(11, "y");
		PKB::getInstance().insertAssignRHS(11, "z + 2");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertAssignLHS(12, "x");
		PKB::getInstance().insertAssignRHS(12, "x * y + z;");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(7, 3);
		PKB::getInstance().insertFollows(10, 7);
		PKB::getInstance().insertFollows(11, 10);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 3);
		PKB::getInstance().insertParent(8, 7);
		PKB::getInstance().insertParent(9, 7);
		PKB::getInstance().insertStatementList(4, { 4, 5, 6 });
		PKB::getInstance().insertStatementList(8, { 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		PKB::getInstance().insertProcedure("main");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> affects1 = DesignExtractor::getInstance().getAffects(1);
		std::unordered_set<int> affects2 = DesignExtractor::getInstance().getAffects(2);
		std::unordered_set<int> affects4 = DesignExtractor::getInstance().getAffects(4);
		std::unordered_set<int> affects6 = DesignExtractor::getInstance().getAffects(6);
		std::unordered_set<int> affects8 = DesignExtractor::getInstance().getAffects(8);
		std::unordered_set<int> affects9 = DesignExtractor::getInstance().getAffects(9);
		std::unordered_set<int> affects10 = DesignExtractor::getInstance().getAffects(10);
		std::unordered_set<int> affects11 = DesignExtractor::getInstance().getAffects(11);
		std::unordered_set<int> actualAffects1 = { 4,8,10,12 };
		std::unordered_set<int> actualAffects2 = { 6,10 };
		std::unordered_set<int> actualAffects4 = { 4,8,10,12 };
		std::unordered_set<int> actualAffects6 = { 6,10 };
		std::unordered_set<int> actualAffects8 = { 10,12 };
		std::unordered_set<int> actualAffects9 = { 10 };
		std::unordered_set<int> actualAffects10 = { 11,12 };
		std::unordered_set<int> actualAffects11 = { 12 };
		Assert::AreEqual(affects1.size(), actualAffects1.size());
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
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertAssignLHS(1, "x");
		PKB::getInstance().insertAssignRHS(1, "0");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertAssignLHS(2, "i");
		PKB::getInstance().insertAssignRHS(2, "5");
		PKB::getInstance().insertStatement(3, "while");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertAssignLHS(4, "x");
		PKB::getInstance().insertAssignRHS(4, "x + 2*y");
		PKB::getInstance().insertStatement(5, "call");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertAssignLHS(6, "i");
		PKB::getInstance().insertAssignRHS(6, "i - 1");
		PKB::getInstance().insertStatement(7, "if");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertAssignLHS(8, "x");
		PKB::getInstance().insertAssignRHS(8, "x + 1");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertAssignLHS(9, "z");
		PKB::getInstance().insertAssignRHS(9, "1");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertAssignLHS(10, "z");
		PKB::getInstance().insertAssignRHS(10, "z + x + i");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertAssignLHS(11, "y");
		PKB::getInstance().insertAssignRHS(11, "z + 2");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertAssignLHS(12, "x");
		PKB::getInstance().insertAssignRHS(12, "x * y + z;");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(7, 3);
		PKB::getInstance().insertFollows(10, 7);
		PKB::getInstance().insertFollows(11, 10);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 3);
		PKB::getInstance().insertParent(8, 7);
		PKB::getInstance().insertParent(9, 7);
		PKB::getInstance().insertStatementList(4, { 4, 5, 6 });
		PKB::getInstance().insertStatementList(8, { 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		PKB::getInstance().insertProcedure("main");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> affectedBy4 = DesignExtractor::getInstance().getAffectedBy(4);
		std::unordered_set<int> affectedBy6 = DesignExtractor::getInstance().getAffectedBy(6);
		std::unordered_set<int> affectedBy8 = DesignExtractor::getInstance().getAffectedBy(8);
		std::unordered_set<int> affectedBy10 = DesignExtractor::getInstance().getAffectedBy(10);
		std::unordered_set<int> affectedBy11 = DesignExtractor::getInstance().getAffectedBy(11);
		std::unordered_set<int> affectedBy12 = DesignExtractor::getInstance().getAffectedBy(12);
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

	TEST_METHOD(testIsAffectsBasic) {
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertAssignLHS(1, "x");
		PKB::getInstance().insertAssignRHS(1, "0");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertAssignLHS(2, "i");
		PKB::getInstance().insertAssignRHS(2, "5");
		PKB::getInstance().insertStatement(3, "while");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertAssignLHS(4, "x");
		PKB::getInstance().insertAssignRHS(4, "x + 2*y");
		PKB::getInstance().insertStatement(5, "call");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertAssignLHS(6, "i");
		PKB::getInstance().insertAssignRHS(6, "i - 1");
		PKB::getInstance().insertStatement(7, "if");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertAssignLHS(8, "x");
		PKB::getInstance().insertAssignRHS(8, "x + 1");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertAssignLHS(9, "z");
		PKB::getInstance().insertAssignRHS(9, "1");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertAssignLHS(10, "z");
		PKB::getInstance().insertAssignRHS(10, "z + x + i");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertAssignLHS(11, "y");
		PKB::getInstance().insertAssignRHS(11, "z + 2");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertAssignLHS(12, "x");
		PKB::getInstance().insertAssignRHS(12, "x * y + z;");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(7, 3);
		PKB::getInstance().insertFollows(10, 7);
		PKB::getInstance().insertFollows(11, 10);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 3);
		PKB::getInstance().insertParent(8, 7);
		PKB::getInstance().insertParent(9, 7);
		PKB::getInstance().insertStatementList(4, { 4, 5, 6 });
		PKB::getInstance().insertStatementList(8, { 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		PKB::getInstance().insertProcedure("main");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractNext();

		Assert::IsTrue(DesignExtractor::getInstance().isAffects(1, 4));
		Assert::IsTrue(DesignExtractor::getInstance().isAffects(2, 6));
		Assert::IsTrue(DesignExtractor::getInstance().isAffects(4, 12));
		Assert::IsTrue(DesignExtractor::getInstance().isAffects(9, 10));
		Assert::IsTrue(DesignExtractor::getInstance().isAffects(10, 11));
	}

	TEST_METHOD(testGetAffectsStarBasic) {
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertAssignLHS(1, "x");
		PKB::getInstance().insertAssignRHS(1, "0");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertAssignLHS(2, "i");
		PKB::getInstance().insertAssignRHS(2, "5");
		PKB::getInstance().insertStatement(3, "while");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertAssignLHS(4, "x");
		PKB::getInstance().insertAssignRHS(4, "x + 2*y");
		PKB::getInstance().insertStatement(5, "call");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertAssignLHS(6, "i");
		PKB::getInstance().insertAssignRHS(6, "i - 1");
		PKB::getInstance().insertStatement(7, "if");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertAssignLHS(8, "x");
		PKB::getInstance().insertAssignRHS(8, "x + 1");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertAssignLHS(9, "z");
		PKB::getInstance().insertAssignRHS(9, "1");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertAssignLHS(10, "z");
		PKB::getInstance().insertAssignRHS(10, "z + x + i");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertAssignLHS(11, "y");
		PKB::getInstance().insertAssignRHS(11, "z + 2");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertAssignLHS(12, "x");
		PKB::getInstance().insertAssignRHS(12, "x * y + z;");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(7, 3);
		PKB::getInstance().insertFollows(10, 7);
		PKB::getInstance().insertFollows(11, 10);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 3);
		PKB::getInstance().insertParent(8, 7);
		PKB::getInstance().insertParent(9, 7);
		PKB::getInstance().insertStatementList(4, { 4, 5, 6 });
		PKB::getInstance().insertStatementList(8, { 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		PKB::getInstance().insertProcedure("main");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> affectsStar1 = DesignExtractor::getInstance().getAffectsStar(1);
		std::unordered_set<int> affectsStar2 = DesignExtractor::getInstance().getAffectsStar(2);
		std::unordered_set<int> affectsStar4 = DesignExtractor::getInstance().getAffectsStar(4);
		std::unordered_set<int> affectsStar6 = DesignExtractor::getInstance().getAffectsStar(6);
		std::unordered_set<int> affectsStar8 = DesignExtractor::getInstance().getAffectsStar(8);
		std::unordered_set<int> affectsStar9 = DesignExtractor::getInstance().getAffectsStar(9);
		std::unordered_set<int> affectsStar10 = DesignExtractor::getInstance().getAffectsStar(10);
		std::unordered_set<int> affectsStar11 = DesignExtractor::getInstance().getAffectsStar(11);
		std::unordered_set<int> affectsStar12 = DesignExtractor::getInstance().getAffectsStar(12);
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
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertAssignLHS(1, "x");
		PKB::getInstance().insertAssignRHS(1, "0");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertAssignLHS(2, "i");
		PKB::getInstance().insertAssignRHS(2, "5");
		PKB::getInstance().insertStatement(3, "while");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertAssignLHS(4, "x");
		PKB::getInstance().insertAssignRHS(4, "x + 2*y");
		PKB::getInstance().insertStatement(5, "call");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertAssignLHS(6, "i");
		PKB::getInstance().insertAssignRHS(6, "i - 1");
		PKB::getInstance().insertStatement(7, "if");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertAssignLHS(8, "x");
		PKB::getInstance().insertAssignRHS(8, "x + 1");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertAssignLHS(9, "z");
		PKB::getInstance().insertAssignRHS(9, "1");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertAssignLHS(10, "z");
		PKB::getInstance().insertAssignRHS(10, "z + x + i");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertAssignLHS(11, "y");
		PKB::getInstance().insertAssignRHS(11, "z + 2");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertAssignLHS(12, "x");
		PKB::getInstance().insertAssignRHS(12, "x * y + z;");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(7, 3);
		PKB::getInstance().insertFollows(10, 7);
		PKB::getInstance().insertFollows(11, 10);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 3);
		PKB::getInstance().insertParent(8, 7);
		PKB::getInstance().insertParent(9, 7);
		PKB::getInstance().insertStatementList(4, { 4, 5, 6 });
		PKB::getInstance().insertStatementList(8, { 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		PKB::getInstance().insertProcedure("main");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractNext();
		std::unordered_set<int> affectedByStar1 = DesignExtractor::getInstance().getAffectedByStar(1);
		std::unordered_set<int> affectedByStar2 = DesignExtractor::getInstance().getAffectedByStar(2);
		std::unordered_set<int> affectedByStar4 = DesignExtractor::getInstance().getAffectedByStar(4);
		std::unordered_set<int> affectedByStar6 = DesignExtractor::getInstance().getAffectedByStar(6);
		std::unordered_set<int> affectedByStar8 = DesignExtractor::getInstance().getAffectedByStar(8);
		std::unordered_set<int> affectedByStar9 = DesignExtractor::getInstance().getAffectedByStar(9);
		std::unordered_set<int> affectedByStar10 = DesignExtractor::getInstance().getAffectedByStar(10);
		std::unordered_set<int> affectedByStar11 = DesignExtractor::getInstance().getAffectedByStar(11);
		std::unordered_set<int> affectedByStar12 = DesignExtractor::getInstance().getAffectedByStar(12);
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
	
	TEST_METHOD(testIsAffectsStarBasic) {
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertAssignLHS(1, "x");
		PKB::getInstance().insertAssignRHS(1, "0");
		PKB::getInstance().insertStatement(2, "assign");
		PKB::getInstance().insertAssignLHS(2, "i");
		PKB::getInstance().insertAssignRHS(2, "5");
		PKB::getInstance().insertStatement(3, "while");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertAssignLHS(4, "x");
		PKB::getInstance().insertAssignRHS(4, "x + 2*y");
		PKB::getInstance().insertStatement(5, "call");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertAssignLHS(6, "i");
		PKB::getInstance().insertAssignRHS(6, "i - 1");
		PKB::getInstance().insertStatement(7, "if");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertAssignLHS(8, "x");
		PKB::getInstance().insertAssignRHS(8, "x + 1");
		PKB::getInstance().insertStatement(9, "assign");
		PKB::getInstance().insertAssignLHS(9, "z");
		PKB::getInstance().insertAssignRHS(9, "1");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertAssignLHS(10, "z");
		PKB::getInstance().insertAssignRHS(10, "z + x + i");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertAssignLHS(11, "y");
		PKB::getInstance().insertAssignRHS(11, "z + 2");
		PKB::getInstance().insertStatement(12, "assign");
		PKB::getInstance().insertAssignLHS(12, "x");
		PKB::getInstance().insertAssignRHS(12, "x * y + z;");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(7, 3);
		PKB::getInstance().insertFollows(10, 7);
		PKB::getInstance().insertFollows(11, 10);
		PKB::getInstance().insertFollows(12, 11);
		PKB::getInstance().insertParent(4, 3);
		PKB::getInstance().insertParent(5, 3);
		PKB::getInstance().insertParent(6, 3);
		PKB::getInstance().insertParent(8, 7);
		PKB::getInstance().insertParent(9, 7);
		PKB::getInstance().insertStatementList(4, { 4, 5, 6 });
		PKB::getInstance().insertStatementList(8, { 8 });
		PKB::getInstance().insertStatementList(9, { 9 });
		PKB::getInstance().insertProcedure("main");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractNext();
		Assert::IsFalse(DesignExtractor::getInstance().isAffectsStar(1, 1));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(1, 4));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(1, 8));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(1, 10));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(1, 11));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(1, 12));
		Assert::IsFalse(DesignExtractor::getInstance().isAffectsStar(2, 2));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(2, 6));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(2, 10));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(2, 11));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(2, 12));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(4, 4));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(4, 8));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(4, 10));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(4, 11));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(4, 12));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(6, 6));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(6, 10));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(6, 11));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(6, 12));
		Assert::IsFalse(DesignExtractor::getInstance().isAffectsStar(8, 8));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(8, 10));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(8, 11));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(8, 12));
		Assert::IsFalse(DesignExtractor::getInstance().isAffectsStar(9, 9));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(9, 10));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(9, 11));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(9, 12));
		Assert::IsFalse(DesignExtractor::getInstance().isAffectsStar(10, 10));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(10, 11));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(10, 12));
		Assert::IsFalse(DesignExtractor::getInstance().isAffectsStar(11, 11));
		Assert::IsTrue(DesignExtractor::getInstance().isAffectsStar(11, 12));
	}
	TEST_METHOD(testExtractNextBipBasic) {
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertProcedure("One");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5});
		PKB::getInstance().insertProcedure("Two");
		PKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{6, 7, 8});
		PKB::getInstance().insertProcedure("Three");
		PKB::getInstance().insertProcedureStatementList(2, std::unordered_set<int>{9, 10, 11});
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertStatement(2, "call");
		PKB::getInstance().insertStatement(3, "assign");
		PKB::getInstance().insertStatement(4, "call");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertStatement(7, "call");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertStatement(9, "if");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertCall(2, "Two");
		PKB::getInstance().insertCall(4, "Three");
		PKB::getInstance().insertCall(7, "Three");

		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(4, 3);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(7, 6);
		PKB::getInstance().insertFollows(8, 7);
		PKB::getInstance().insertParent(10, 9);
		PKB::getInstance().insertParent(11, 9);
		PKB::getInstance().insertStatementList(10, { 10 });
		PKB::getInstance().insertStatementList(11, { 11 });
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractExtensions();
		std::unordered_set<int> nextBip1 = PKB::getInstance().getNextBip(1);
		std::unordered_set<int> nextBip2 = PKB::getInstance().getNextBip(2);
		std::unordered_set<int> nextBip3 = PKB::getInstance().getNextBip(3);
		std::unordered_set<int> nextBip4 = PKB::getInstance().getNextBip(4);
		std::unordered_set<int> nextBip5 = PKB::getInstance().getNextBip(5);
		std::unordered_set<int> nextBip6 = PKB::getInstance().getNextBip(6);
		std::unordered_set<int> nextBip7 = PKB::getInstance().getNextBip(7);
		std::unordered_set<int> nextBip8 = PKB::getInstance().getNextBip(8);
		std::unordered_set<int> nextBip9 = PKB::getInstance().getNextBip(9);
		std::unordered_set<int> nextBip10 = PKB::getInstance().getNextBip(10);
		std::unordered_set<int> nextBip11 = PKB::getInstance().getNextBip(11);
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
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertProcedure("One");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3});
		PKB::getInstance().insertProcedure("Two");
		PKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{4, 5, 6});
		PKB::getInstance().insertStatement(1, "call");
		PKB::getInstance().insertStatement(2, "call");
		PKB::getInstance().insertStatement(3, "call");
		PKB::getInstance().insertCall(1, "Two");
		PKB::getInstance().insertCall(2, "Two");
		PKB::getInstance().insertCall(3, "Two");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractExtensions();
		std::unordered_set<int> nextBip1 = PKB::getInstance().getNextBip(1);
		std::unordered_set<int> nextBip2 = PKB::getInstance().getNextBip(2);
		std::unordered_set<int> nextBip3 = PKB::getInstance().getNextBip(3);
		std::unordered_set<int> nextBip4 = PKB::getInstance().getNextBip(4);
		std::unordered_set<int> nextBip5 = PKB::getInstance().getNextBip(5);
		std::unordered_set<int> nextBip6 = PKB::getInstance().getNextBip(6);
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
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertProcedure("One");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5});
		PKB::getInstance().insertProcedure("Two");
		PKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{6, 7, 8});
		PKB::getInstance().insertProcedure("Three");
		PKB::getInstance().insertProcedureStatementList(2, std::unordered_set<int>{9, 10, 11});
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertStatement(2, "call");
		PKB::getInstance().insertStatement(3, "assign");
		PKB::getInstance().insertStatement(4, "call");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertStatement(7, "call");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertStatement(9, "if");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertCall(2, "Two");
		PKB::getInstance().insertCall(4, "Three");
		PKB::getInstance().insertCall(7, "Three");

		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(4, 3);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(7, 6);
		PKB::getInstance().insertFollows(8, 7);
		PKB::getInstance().insertParent(10, 9);
		PKB::getInstance().insertParent(11, 9);
		PKB::getInstance().insertStatementList(10, { 10 });
		PKB::getInstance().insertStatementList(11, { 11 });
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractExtensions();
		std::unordered_set<int> nextBipStar1 = PKB::getInstance().getNextBipStar(1);
		std::unordered_set<int> nextBipStar2 = PKB::getInstance().getNextBipStar(2);
		std::unordered_set<int> nextBipStar3 = PKB::getInstance().getNextBipStar(3);
		std::unordered_set<int> nextBipStar4 = PKB::getInstance().getNextBipStar(4);
		std::unordered_set<int> nextBipStar5 = PKB::getInstance().getNextBipStar(5);
		std::unordered_set<int> nextBipStar6 = PKB::getInstance().getNextBipStar(6);
		std::unordered_set<int> nextBipStar7 = PKB::getInstance().getNextBipStar(7);
		std::unordered_set<int> nextBipStar8 = PKB::getInstance().getNextBipStar(8);
		std::unordered_set<int> nextBipStar9 = PKB::getInstance().getNextBipStar(9);
		std::unordered_set<int> nextBipStar10 = PKB::getInstance().getNextBipStar(10);
		std::unordered_set<int> nextBipStar11 = PKB::getInstance().getNextBipStar(11);
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
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertProcedure("One");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3});
		PKB::getInstance().insertProcedure("Two");
		PKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{4, 5, 6});
		PKB::getInstance().insertStatement(1, "call");
		PKB::getInstance().insertStatement(2, "call");
		PKB::getInstance().insertStatement(3, "call");
		PKB::getInstance().insertCall(1, "Two");
		PKB::getInstance().insertCall(2, "Two");
		PKB::getInstance().insertCall(3, "Two");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractExtensions();
		std::unordered_set<int> nextBipStar1 = PKB::getInstance().getNextBipStar(1);
		std::unordered_set<int> nextBipStar2 = PKB::getInstance().getNextBipStar(2);
		std::unordered_set<int> nextBipStar3 = PKB::getInstance().getNextBipStar(3);
		std::unordered_set<int> nextBipStar4 = PKB::getInstance().getNextBipStar(4);
		std::unordered_set<int> nextBipStar5 = PKB::getInstance().getNextBipStar(5);
		std::unordered_set<int> nextBipStar6 = PKB::getInstance().getNextBipStar(6);
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
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertProcedure("One");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3, 4, 5});
		PKB::getInstance().insertProcedure("Two");
		PKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{6, 7, 8});
		PKB::getInstance().insertProcedure("Three");
		PKB::getInstance().insertProcedureStatementList(2, std::unordered_set<int>{9, 10, 11});
		PKB::getInstance().insertStatement(1, "assign");
		PKB::getInstance().insertAssignLHS(1, "x");
		PKB::getInstance().insertAssignRHS(1, "5");
		PKB::getInstance().insertStatement(2, "call");
		PKB::getInstance().insertCall(2, "Two");
		PKB::getInstance().insertStatement(3, "assign");
		PKB::getInstance().insertAssignLHS(3, "y");
		PKB::getInstance().insertAssignRHS(3, "x + 6");
		PKB::getInstance().insertStatement(4, "call");
		PKB::getInstance().insertCall(4, "Three");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertAssignLHS(5, "z");
		PKB::getInstance().insertAssignRHS(5, "x * y + 2");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertAssignLHS(6, "y");
		PKB::getInstance().insertAssignRHS(6, "x * 3");
		PKB::getInstance().insertStatement(7, "call");
		PKB::getInstance().insertCall(7, "Three");
		PKB::getInstance().insertStatement(8, "assign");
		PKB::getInstance().insertAssignLHS(8, "z");
		PKB::getInstance().insertAssignRHS(8, "x + y");
		PKB::getInstance().insertStatement(9, "if");
		PKB::getInstance().insertStatement(10, "assign");
		PKB::getInstance().insertAssignLHS(10, "x");
		PKB::getInstance().insertAssignRHS(10, "x + z");
		PKB::getInstance().insertStatement(11, "assign");
		PKB::getInstance().insertAssignLHS(11, "y");
		PKB::getInstance().insertAssignRHS(11, "x * y");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(4, 3);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(7, 6);
		PKB::getInstance().insertFollows(8, 7);
		PKB::getInstance().insertParent(10, 9);
		PKB::getInstance().insertParent(11, 9);
		PKB::getInstance().insertStatementList(10, { 10 });
		PKB::getInstance().insertStatementList(11, { 11 });
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractExtensions();
		std::unordered_set<int> affectsBip1 = PKB::getInstance().getAffectsBip(1);
		std::unordered_set<int> affectsBip3 = PKB::getInstance().getAffectsBip(3);
		std::unordered_set<int> affectsBip6 = PKB::getInstance().getAffectsBip(6);
		std::unordered_set<int> actualAffectsBip1 = { 3, 5, 6, 8, 10, 11 };
		std::unordered_set<int> actualAffectsBip3 = { 5, 11 };
		std::unordered_set<int> actualAffectsBip6 = { 8, 11 };
		Assert::IsTrue(affectsBip1 == actualAffectsBip1);
		Assert::IsTrue(affectsBip3 == actualAffectsBip3);
		Assert::IsTrue(affectsBip6 == actualAffectsBip6);
	}
	TEST_METHOD(testExtractAffectsBipStarMultipleCalls) {
		DesignExtractor::getInstance().clearNextStarCache();
		DesignExtractor::getInstance().clearAffectsCache();
		DesignExtractor::getInstance().clearAffectsStarCache();
		PKB::getInstance().clear();
		PKB::getInstance().insertProcedure("B");
		PKB::getInstance().insertProcedureStatementList(0, std::unordered_set<int>{1, 2, 3});
		PKB::getInstance().insertProcedure("C");
		PKB::getInstance().insertProcedureStatementList(1, std::unordered_set<int>{4, 5, 6, 7});
		PKB::getInstance().insertStatement(1, "call");
		PKB::getInstance().insertStatement(2, "call");
		PKB::getInstance().insertStatement(3, "call");
		PKB::getInstance().insertCall(1, "C");
		PKB::getInstance().insertCall(2, "C");
		PKB::getInstance().insertCall(3, "C");
		PKB::getInstance().insertStatement(4, "assign");
		PKB::getInstance().insertAssignLHS(4, "d");
		PKB::getInstance().insertAssignRHS(4, "a");
		PKB::getInstance().insertStatement(5, "assign");
		PKB::getInstance().insertAssignLHS(5, "a");
		PKB::getInstance().insertAssignRHS(5, "b");
		PKB::getInstance().insertStatement(6, "assign");
		PKB::getInstance().insertAssignLHS(6, "b");
		PKB::getInstance().insertAssignRHS(6, "c");
		PKB::getInstance().insertStatement(7, "assign");
		PKB::getInstance().insertAssignLHS(7, "c");
		PKB::getInstance().insertAssignRHS(7, "d");
		PKB::getInstance().insertFollows(2, 1);
		PKB::getInstance().insertFollows(3, 2);
		PKB::getInstance().insertFollows(5, 4);
		PKB::getInstance().insertFollows(6, 5);
		PKB::getInstance().insertFollows(7, 6);
		DesignExtractor::getInstance().extractAllDesigns();
		DesignExtractor::getInstance().extractExtensions();
		std::unordered_set<int> affectsBipStar1 = PKB::getInstance().getAffectsBipStar(1);
		std::unordered_set<int> affectsBipStar2 = PKB::getInstance().getAffectsBipStar(2);
		std::unordered_set<int> affectsBipStar3 = PKB::getInstance().getAffectsBipStar(3);
		std::unordered_set<int> affectsBipStar4 = PKB::getInstance().getAffectsBipStar(4);
		std::unordered_set<int> affectsBipStar5 = PKB::getInstance().getAffectsBipStar(5);
		std::unordered_set<int> affectsBipStar6 = PKB::getInstance().getAffectsBipStar(6);
		std::unordered_set<int> affectsBipStar7 = PKB::getInstance().getAffectsBipStar(7);
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
