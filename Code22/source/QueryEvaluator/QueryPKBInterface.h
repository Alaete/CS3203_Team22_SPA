#pragma once

#include <string>
#include <vector>
#include "../PKB/PKB.h"
#include <unordered_map>
#include <unordered_set>

class QueryPKBInterface {
private:
    QueryPKBInterface(); // Prevent construction
    QueryPKBInterface(const PKB&); // Prevent construction by copying
    QueryPKBInterface& operator=(const PKB&); // Prevent assignment
    ~QueryPKBInterface(); // Prevent unwanted destruction

public:
    //Singleton Implementation

    static QueryPKBInterface& getInstance() {
        static QueryPKBInterface instance;
        return instance;
    }

	//Design Abstractions (relRef)
	//--Follow--------------------------------------------------------------------------------------------------
	//----Find----
	std::string getFollows(std::string lineNumber);
	std::string getFollowedBy(std::string lineNumber);
	int getSizeFollows();
	//----Assert----
	bool isFollows(int lineNumber, int leaderLine);

    bool isFollowedBy(std::string lineNumber, std::string followerLine);


	//--Follow*-------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getFollowsStar(std::string lineNumber);
	std::vector<std::string> getFollowedByStar(std::string lineNumber);
	int getSizeFollowsStar();
	int getAreaFollowsStar();
	//----Assert----
	bool isFollowsStar(int lineNumber, int leaderLine);
	bool isFollowsStar(int lineNumber, std::unordered_set<int> leaderLines);

    bool isFollowedByStar(std::string lineNumber, std::string followerLine);
    bool isFollowedByStar(int lineNumber, std::unordered_set<int> followerLines);

	//--Parent--------------------------------------------------------------------------------------------------
	//----Find----
	std::string getParent(std::string lineNumber);
	std::vector<std::string> getChild(std::string lineNumber);
	int getSizeParent();
	//----Assert----
	bool isParent(int lineNumber, int parentLine);

    bool isChild(std::string lineNumber, std::string childLine);
    bool isChild(int lineNumber, std::unordered_set<int> childLines);

	//--Parent*-------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getParentStar(std::string lineNumber);
	std::vector<std::string> getChildStar(std::string lineNumber);
	int getSizeParentStar();
	int getAreaParentStar();
	//----Assert----
	bool isParentStar(int lineNumber, int parentLine);
	bool isParentStar(int lineNumber, std::unordered_set<int> parentLines);

    bool isChildStar(std::string lineNumber, std::string childLine);
    bool isChildStar(int lineNumber, std::unordered_set<int> childLines);

	//--Uses----------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getUses(std::string name);
	std::vector<std::string> getUsedBy(std::string name);
	int getSizeUses();
	int getAreaUses();
	//----Assert----
	bool isUses(std::string lineNumber, std::string usedName);
	bool isUses(std::string lineNumber, std::unordered_set<std::string> usedNames);
	bool isUsedBy(std::string name, std::string usedByLine);
	bool isUsedBy(std::string name, std::unordered_set<std::string> usedByLines);

	//--ProcedureUses----------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getProcedureUses(std::string name);
	std::vector<std::string> getProcedureUsedBy(std::string name);
	int getSizeProcedureUses();
	int getAreaProcedureUses();
	//----Assert----
	bool isProcedureUses(std::string lineNumber, std::string usedName);
	bool isProcedureUses(std::string lineNumber, std::unordered_set<std::string> usedNames);
	bool isProcedureUsedBy(std::string name, std::string usedByLine);
	bool isProcedureUsedBy(std::string name, std::unordered_set<std::string> usedByLines);

	//--Modifies------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getModifies(std::string lineNumber);
	std::vector<std::string> getModifiedBy(std::string name);
	int getSizeModifies();
	int getAreaModifies();
	//----Assert----
	bool isModifies(std::string lineNumber, std::string modifiedName);
	bool isModifies(std::string lineNumber, std::unordered_set<std::string> modifiedNames);
	bool isModifiedBy(std::string name, std::string modifiedByLine);
	bool isModifiedBy(std::string name, std::unordered_set<std::string> modifiedByLines);

	//--ProcedureModifies------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getProcedureModifies(std::string procName);
	std::vector<std::string> getProcedureModifiedBy(std::string name);
	int getSizeProcedureModifies();
	int getAreaProcedureModifies();
	//----Assert----
	bool isProcedureModifies(std::string lineNumber, std::string modifiedName);
	bool isProcedureModifies(std::string lineNumber, std::unordered_set<std::string> modifiedNames);
	bool isProcedureModifiedBy(std::string name, std::string modifiedByLine);
	bool isProcedureModifiedBy(std::string name, std::unordered_set<std::string> modifiedByLines);

	//--Calls----------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getCalls(std::string procedureName);
	std::vector<std::string> getCalledBy(std::string procedureName);
	int getSizeCalls();
	int getAreaCalls();
	//----Assert----
	bool isCalls(std::string procedureName, std::string calledprocedureName);
	bool isCalls(std::string procedureName, std::unordered_set<std::string> calledprocedureNames);
	bool isCalledBy(std::string procedureName, std::string calledByprocedureName);
	bool isCalledBy(std::string procedureName, std::unordered_set<std::string> calledByPprocedureNames);

	//--CallsStar----------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getCallsStar(std::string procedureName);
	std::vector<std::string> getCalledByStar(std::string procedureName);
	int getSizeCallsStar();
	int getAreaCallsStar();
	//----Assert----
	bool isCallsStar(std::string procedureName, std::string calledprocedureName);
	bool isCallsStar(std::string procedureName, std::unordered_set<std::string> calledprocedureNames);
	bool isCalledByStar(std::string procedureName, std::string calledByprocedureName);
	bool isCalledByStar(std::string procedureName, std::unordered_set<std::string> calledByprocedureNames);

	//--Next----------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getNext(std::string lineNumber);
	std::vector<std::string> getPrevious(std::string lineNumber);
	int getSizeNext();
	int getAreaNext();
	//----Assert----
	bool isNext(std::string lineNumber, std::string nextLine);
	bool isNext(std::string lineNumber, std::unordered_set<std::string> nextLines);
	bool isPrevious(std::string lineNumber, std::string previousLine);
	bool isPrevious(std::string lineNumber, std::unordered_set<std::string> previousLines);

	//--NextBIP----------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getNextBip(std::string lineNumber);
	std::vector<std::string> getPreviousBip(std::string lineNumber);
	int getSizeNextBip();
	int getAreaNextBip();
	//----Assert----
	bool isNextBip(std::string lineNumber, std::string nextLine);
	bool isNextBip(std::string lineNumber, std::unordered_set<std::string> nextLines);
	bool isPreviousBip(std::string lineNumber, std::string previousLine);
	bool isPreviousBip(std::string lineNumber, std::unordered_set<std::string> previousLines);

	//--AffectsBip----------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getAffectsBip(std::string lineNumber);
	std::vector<std::string> getAffectedByBip(std::string lineNumber);
	int getSizeAffectsBip();
	int getAreaAffectsBip();
	//----Assert----
	bool isAffectsBip(std::string lineNumber, std::string nextLine);
	bool isAffectsBip(std::string lineNumber, std::unordered_set<std::string> nextLines);
	bool isAffectedByBip(std::string lineNumber, std::string previousLine);
	bool isAffectedByBip(std::string lineNumber, std::unordered_set<std::string> previousLines);

	//--NextBipStar----------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getNextBipStar(std::string lineNumber);
	std::vector<std::string> getPreviousBipStar(std::string lineNumber);
	int getSizeNextBipStar();
	int getAreaNextBipStar();
	//----Assert----
	bool isNextBipStar(std::string lineNumber, std::string nextLine);
	bool isNextBipStar(std::string lineNumber, std::unordered_set<std::string> nextLines);
	bool isPreviousBipStar(std::string lineNumber, std::string previousLine);
	bool isPreviousBipStar(std::string lineNumber, std::unordered_set<std::string> previousLines);


	//Design Entities (entRef)
	//--Assign--------------------------------------------------------------------------------------------------
	//----Find----
	std::vector<std::string> getAllKeysAssign();
	std::pair<std::string, std::string> getAssign(std::string lineNumber); //For pattern clauses
	int getSizeAssign();
	//----Assert----
	bool hasKeyAssign(std::string lineNumber);

    //--Statement-----------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllKeysStatement();
    //----Assert----
    bool QueryPKBInterface::hasKeyStatement(std::string lineNumber);

    //--Read----------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllKeysRead();
	std::vector<std::string> getAllValuesRead();
    //----Assert----
    bool hasKeyRead(std::string lineNumber);
	//----Get----
	std::string getRead(std::string lineNumber);
	std::vector<std::string> getKeysRead(std::string value);

    //--Print---------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllKeysPrint();
	std::vector<std::string> getAllValuesPrint();
    //----Assert----
    bool hasKeyPrint(std::string lineNumber);
	//----Get----
	std::string getPrint(std::string lineNumber);
	std::vector<std::string> getKeysPrint(std::string value);

    //--Call----------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllKeysCall();
	std::vector<std::string> getAllValuesCall();
    //----Assert----
    bool hasKeyCall(std::string lineNumber);
	//----Get----
	std::string getCall(std::string lineNumber);
	std::vector<std::string> getKeysCall(std::string value);

    //--While---------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllKeysWhile();
	std::vector<std::string> getWhile(std::string lineNumber);
	int getAreaWhile();
    //----Assert----
    bool hasKeyWhile(std::string lineNumber);

    //--If------------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllKeysIf();
	std::vector<std::string> getIf(std::string lineNumber);
	int getAreaIf();
    //----Assert----
    bool hasKeyIf(std::string lineNumber);

    //--Variable------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllValuesVariable();
    //----Assert----
    bool hasKeyVariable(std::string index);
    bool hasValueVariable(std::string varName);

    //--Constant------------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllKeysConstant();
    std::vector<std::string> getAllValuesConstant();
    //----Assert----
    bool hasKeyConstant(std::string constant);
    bool hasValueConstant(std::string varName);

    //--Procedure-----------------------------------------------------------------------------------------------
    //----Find----
    std::vector<std::string> getAllValuesProcedure();
    //----Assert----
    bool hasKeyProcedure(std::string lineNumber);
    bool hasValueProcedure(std::string procName);

	
};

