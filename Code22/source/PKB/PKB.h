#pragma once

#include "ConcreteClasses/PKB_Map_ProcedureVariable.h"
#include "ConcreteClasses/PKB_Map_StatementList.h"
#include "ConcreteClasses/PKB_Map_CallPrintReadStatement.h"
#include "ConcreteClasses/PKB_Map_IfWhile.h"
#include "ConcreteClasses/PKB_Map_Assign.h"
#include "ConcreteClasses/PKB_Map_Constant.h"

#include "ConcreteClasses/PKB_Map_Follows.h"
#include "ConcreteClasses/PKB_Map_Parent.h"
#include "ConcreteClasses/PKB_Map_ModifiesUses.h"
#include "ConcreteClasses/PKB_Map_AAstarCCstarFstarNNstarPstar.h"

#include "ConcreteClasses/PKB_Map_Node.h"

#include "PKB_Util.h"

class PKB {
private:
    PKB_Map_ProcedureVariable procedureTable;
    PKB_Map_CallPrintReadStatement statementTable;
    PKB_Map_StatementList statementListTable;
    PKB_Map_StatementList procedureStatementListTable;
    PKB_Map_CallPrintReadStatement readTable;
    PKB_Map_CallPrintReadStatement printTable;
    PKB_Map_Assign assignTable;
    PKB_Map_CallPrintReadStatement callTable;
    PKB_Map_IfWhile whileTable;
    PKB_Map_IfWhile ifTable;
    PKB_Map_ProcedureVariable variableTable;
    PKB_Map_Constant constantTable;

    PKB_Map_Follows followsTable;
    PKB_Map_AAstarCCstarFstarNNstarPstar followsStarTable;
    PKB_Map_Parent parentTable;
    PKB_Map_AAstarCCstarFstarNNstarPstar parentStarTable;
    PKB_Map_ModifiesUses usesTable;
    PKB_Map_ModifiesUses modifiesTable;
    PKB_Map_ModifiesUses procedureUsesTable;
    PKB_Map_ModifiesUses procedureModifiesTable;

    PKB_Map_AAstarCCstarFstarNNstarPstar callsTable;
    PKB_Map_AAstarCCstarFstarNNstarPstar callsStarTable;
    PKB_Map_AAstarCCstarFstarNNstarPstar nextTable;

    PKB_Map_AAstarCCstarFstarNNstarPstar nextBipTable;
    PKB_Map_AAstarCCstarFstarNNstarPstar nextBipStarTable;
    PKB_Map_AAstarCCstarFstarNNstarPstar affectsBipTable;
    PKB_Map_AAstarCCstarFstarNNstarPstar affectsBipStarTable;
    PKB_Map_AAstarCCstarFstarNNstarPstar affectsBipNodeTable;

    PKB(); // Prevent construction
    PKB(const PKB&); // Prevent construction by copying
    PKB& operator=(const PKB&); // Prevent assignment
    ~PKB(); // Prevent unwanted destruction

public:
    static PKB& getInstance() {
        static PKB inst;
        return inst;
    }

    void clear();
    void precompute();

    int insertProcedure(std::string procName);
    std::string getProcedure(int procIndex);
    int getKeyProcedure(std::string procName);
    int getSizeProcedure();
    bool hasKeyProcedure(int procIndex);
    std::vector<int> getAllKeysProcedure();
    std::vector<std::string> getAllValuesProcedure();

    void insertStatement(int lineNumber, std::string statementType);
    std::string getStatement(int lineNumber);
    bool isStatement(int lineNumber, std::string statementType);
    std::unordered_set<int> getKeysStatement(std::string statementType);
    int getSizeStatement();
    bool hasKeyStatement(int lineNumber);
    std::vector<int> getAllKeysStatement();
    std::vector<std::string> getAllValuesStatement();

    void insertStatementList(int lineNumber, std::unordered_set<int> statementLines);
    std::unordered_set<int> getStatementList(int lineNumber);
    int getKeyStatementList(int lineNumber);
    int getSizeStatementList();
    bool hasKeyStatementList(int lineNumber);
    std::vector<int> getAllKeysStatementList();
    std::vector<std::unordered_set<int>> getAllValuesStatementList();

    void insertProcedureStatementList(int lineNumber, std::unordered_set<int> statementLines);
    std::unordered_set<int> getProcedureStatementList(int lineNumber);
    int getKeyProcedureStatementList(int lineNumber);
    int getSizeProcedureStatementList();
    bool hasKeyProcedureStatementList(int lineNumber);
    std::vector<int> getAllKeysProcedureStatementList();
    std::vector<std::unordered_set<int>> getAllValuesProcedureStatementList();

    void insertRead(int lineNumber, std::string varName);
    std::string getRead(int lineNumber);
    std::unordered_set<int> getKeysRead(std::string varName);
    int getSizeRead();
    bool hasKeyRead(int lineNumber);
    std::vector<int> getAllKeysRead();
    std::vector<std::string> getAllValuesRead();

    void insertPrint(int lineNumber, std::string varName);
    std::string getPrint(int lineNumber);
    std::unordered_set<int> getKeysPrint(std::string varName);
    int getSizePrint();
    bool hasKeyPrint(int lineNumber);
    std::vector<int> getAllKeysPrint();
    std::vector<std::string> getAllValuesPrint();

    void insertAssignLHS(int lineNumber, std::string variableLHS);
    void insertAssignRHS(int lineNumber, std::string shuntedRHS);
    std::pair<std::string, std::string> getAssign(int lineNumber);
    int getSizeAssign();
    bool hasKeyAssign(int lineNumber);
    std::vector<int> getAllKeysAssign();
    std::vector<std::pair<std::string, std::string>> getAllValuesAssign();

    void insertCall(int lineNumber, std::string procName);
    std::string getCall(int lineNumber);
    std::unordered_set<int> getKeysCall(std::string procName);
    int getSizeCall();
    bool hasKeyCall(int lineNumber);
    std::vector<int> getAllKeysCall();
    std::vector<std::string> getAllValuesCall();

    void insertWhile(int lineNumber, std::unordered_set<std::string> condition);
    std::unordered_set<std::string> getWhile(int lineNumber);
    bool isWhile(int lineNumber, std::string condition);
    bool isWhile(int lineNumber, std::unordered_set<std::string> conditions);
    int getSizeWhile();
    int getAreaWhile();
    bool hasKeyWhile(int lineNumber);
    std::vector<int> getAllKeysWhile();
    std::vector<std::unordered_set<std::string>> getAllValuesWhile();

    void insertIf(int lineNumber, std::unordered_set<std::string> condition);
    std::unordered_set<std::string> getIf(int lineNumber);
    bool isIf(int lineNumber, std::string condition);
    bool isIf(int lineNumber, std::unordered_set<std::string> conditions);
    int getSizeIf();
    int getAreaIf();
    bool hasKeyIf(int lineNumber);
    std::vector<int> getAllKeysIf();
    std::vector<std::unordered_set<std::string>> getAllValuesIf();

    void insertIfWhile(int lineNumber, std::string condition);

    int insertVariable(std::string varName);
    std::string getVariable(int index);
    int getKeyVariable(std::string varName);
    int getSizeVariable();
    bool hasKeyVariable(int index);
    std::vector<int> getAllKeysVariable();
    std::vector<std::string> getAllValuesVariable();

    void insertConstant(int lineNumber, std::unordered_set<int> constantValues);
    std::unordered_set<int> getConstant(int lineNumber);
    bool isConstant(int lineNumber, std::unordered_set<int> constantValues);
    bool isConstant(int lineNumber, int constantValue);
    int getSizeConstant();
    bool hasKeyConstant(int lineNumber);
    std::vector<int> getAllKeysConstant();
    std::vector<std::unordered_set<int>> getAllValuesConstant();

    void insertFollows(int lineNumber, int leaderLine);
    int getFollows(int lineNumber);
    bool isFollows(int lineNumber, int leaderLine);
    int getSizeFollows();
    bool hasKeyFollows(int lineNumber);
    std::vector<int> getAllKeysFollows();
    std::vector<int> getAllValuesFollows();

    int getFollowedBy(int lineNumber);
    bool isFollowedBy(int lineNumber, int followerLine);
    int getSizeFollowedBy();
    bool hasKeyFollowedBy(int lineNumber);
    std::vector<int> getAllKeysFollowedBy();
    std::vector<int> getAllValuesFollowedBy();

    void insertFollowsStar(int lineNumber, std::unordered_set<int> leaderLines);
    std::unordered_set<int> getFollowsStar(int lineNumber);
    bool isFollowsStar(int lineNumber, int leaderLine);
    bool isFollowsStar(int lineNumber, std::unordered_set<int> leaderLines);
    int getSizeFollowsStar();
    int getAreaFollowsStar();
    bool hasKeyFollowsStar(int lineNumber);
    std::vector<int> getAllKeysFollowsStar();
    std::vector<std::unordered_set<int>> getAllValuesFollowsStar();

    std::unordered_set<int> getFollowedByStar(int lineNumber);
    bool isFollowedByStar(int lineNumber, int followerLine);
    bool isFollowedByStar(int lineNumber, std::unordered_set<int> followerLines);
    int getSizeFollowedByStar();
    int getAreaFollowedByStar();
    bool hasKeyFollowedByStar(int lineNumber);
    std::vector<int> getAllKeysFollowedByStar();
    std::vector<std::unordered_set<int>> getAllValuesFollowedByStar();

    void insertParent(int lineNumber, int parentLine);
    int getParent(int lineNumber);
    bool isParent(int lineNumber, int parentLine);
    int getSizeParent();
    bool hasKeyParent(int lineNumber);
    std::vector<int> getAllKeysParent();
    std::vector<int> getAllValuesParent();

    std::unordered_set<int> getChild(int lineNumber);
    bool isChild(int lineNumber, int childLine);
    bool isChild(int lineNumber, std::unordered_set<int> childLines);
    int getSizeChild();
    bool hasKeyChild(int lineNumber);
    std::vector<int> getAllKeysChild();
    std::vector<std::unordered_set<int>> getAllValuesChild();

    void insertParentStar(int lineNumber, std::unordered_set<int> parentLines);
    std::unordered_set<int> getParentStar(int lineNumber);
    bool isParentStar(int lineNumber, int parentLine);
    bool isParentStar(int lineNumber, std::unordered_set<int> parentLines);
    int getSizeParentStar();
    int getAreaParentStar();
    bool hasKeyParentStar(int lineNumber);
    std::vector<int> getAllKeysParentStar();
    std::vector<std::unordered_set<int>> getAllValuesParentStar();

    std::unordered_set<int> getChildStar(int lineNumber);
    bool isChildStar(int lineNumber, int childLine);
    bool isChildStar(int lineNumber, std::unordered_set<int> childLines);
    int getSizeChildStar();
    int getAreaChildStar();
    bool hasKeyChildStar(int lineNumber);
    std::vector<int> getAllKeysChildStar();
    std::vector<std::unordered_set<int>> getAllValuesChildStar();

    void insertUses(int lineNumber, std::unordered_set<std::string> usedNames);
    std::unordered_set<std::string> getUses(int lineNumber);
    bool isUses(int lineNumber, std::string usedName);
    bool isUses(int lineNumber, std::unordered_set<std::string> usedNames);
    int getSizeUses();
    int getAreaUses();
    bool hasKeyUses(int lineNumber);
    std::vector<int> getAllKeysUses();
    std::vector<std::unordered_set<std::string>> getAllValuesUses();

    std::unordered_set<int> getUsedBy(std::string name);
    bool isUsedBy(std::string name, int usedByLine);
    bool isUsedBy(std::string name, std::unordered_set<int> usedByLines);
    int getSizeUsedBy();
    int getAreaUsedBy();
    bool hasKeyUsedBy(std::string name);
    std::vector<std::string> getAllKeysUsedBy();
    std::vector<std::unordered_set<int>> getAllValuesUsedBy();

    void insertModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    std::unordered_set<std::string> getModifies(int lineNumber);
    bool isModifies(int lineNumber, std::string modifiedName);
    bool isModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    int getSizeModifies();
    int getAreaModifies();
    bool hasKeyModifies(int lineNumber);
    std::vector<int> getAllKeysModifies();
    std::vector<std::unordered_set<std::string>> getAllValuesModifies();

    std::unordered_set<int> getModifiedBy(std::string name);
    bool isModifiedBy(std::string name, int modifiedByLine);
    bool isModifiedBy(std::string name, std::unordered_set<int> modifiedByLines);
    int getSizeModifiedBy();
    int getAreaModifiedBy();
    bool hasKeyModifiedBy(std::string name);
    std::vector<std::string> getAllKeysModifiedBy();
    std::vector<std::unordered_set<int>> getAllValuesModifiedBy();

    void insertProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames);
    std::unordered_set<std::string> getProcedureUses(int lineNumber);
    bool isProcedureUses(int lineNumber, std::string procedureUsedName);
    bool isProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames);
    int getSizeProcedureUses();
    int getAreaProcedureUses();
    bool hasKeyProcedureUses(int lineNumber);
    std::vector<int> getAllKeysProcedureUses();
    std::vector<std::unordered_set<std::string>> getAllValuesProcedureUses();

    std::unordered_set<int> getProcedureUsedBy(std::string name);
    bool isProcedureUsedBy(std::string name, int usedByLine);
    bool isProcedureUsedBy(std::string name, std::unordered_set<int> usedByLines);
    int getSizeProcedureUsedBy();
    int getAreaProcedureUsedBy();
    bool hasKeyProcedureUsedBy(std::string name);
    std::vector<std::string> getAllKeysProcedureUsedBy();
    std::vector<std::unordered_set<int>> getAllValuesProcedureUsedBy();

    void insertProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    std::unordered_set<std::string> getProcedureModifies(int lineNumber);
    bool isProcedureModifies(int lineNumber, std::string modifiedName);
    bool isProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    int getSizeProcedureModifies();
    int getAreaProcedureModifies();
    bool hasKeyProcedureModifies(int lineNumber);
    std::vector<int> getAllKeysProcedureModifies();
    std::vector<std::unordered_set<std::string>> getAllValuesProcedureModifies();

    std::unordered_set<int> getProcedureModifiedBy(std::string name);
    bool isProcedureModifiedBy(std::string name, int modifiedByLine);
    bool isProcedureModifiedBy(std::string name, std::unordered_set<int> modifiedByLines);
    int getSizeProcedureModifiedBy();
    int getAreaProcedureModifiedBy();
    bool hasKeyProcedureModifiedBy(std::string name);
    std::vector<std::string> getAllKeysProcedureModifiedBy();
    std::vector<std::unordered_set<int>> getAllValuesProcedureModifiedBy();

    void insertCalls(int lineNumber, std::unordered_set<int> calledLines);
    std::unordered_set<int> getCalls(int lineNumber);
    bool isCalls(int lineNumber, int calledLine);
    bool isCalls(int lineNumber, std::unordered_set<int> calledLines);
    int getSizeCalls();
    int getAreaCalls();
    bool hasKeyCalls(int lineNumber);
    std::vector<int> getAllKeysCalls();
    std::vector<std::unordered_set<int>> getAllValuesCalls();

    std::unordered_set<int> getCalledBy(int lineNumber);
    bool isCalledBy(int lineNumber, int calledByLine);
    bool isCalledBy(int lineNumber, std::unordered_set<int> calledByLines);
    int getSizeCalledBy();
    int getAreaCalledBy();
    bool hasKeyCalledBy(int lineNumber);
    std::vector<int> getAllKeysCalledBy();
    std::vector<std::unordered_set<int>> getAllValuesCalledBy();

    void insertCallsStar(int lineNumber, std::unordered_set<int> calledLines);
    std::unordered_set<int> getCallsStar(int lineNumber);
    bool isCallsStar(int lineNumber, int calledLine);
    bool isCallsStar(int lineNumber, std::unordered_set<int> calledLines);
    int getSizeCallsStar();
    int getAreaCallsStar();
    bool hasKeyCallsStar(int lineNumber);
    std::vector<int> getAllKeysCallsStar();
    std::vector<std::unordered_set<int>> getAllValuesCallsStar();

    std::unordered_set<int> getCalledByStar(int lineNumber);
    bool isCalledByStar(int lineNumber, int calledByLine);
    bool isCalledByStar(int lineNumber, std::unordered_set<int> calledByLines);
    int getSizeCalledByStar();
    int getAreaCalledByStar();
    bool hasKeyCalledByStar(int lineNumber);
    std::vector<int> getAllKeysCalledByStar();
    std::vector<std::unordered_set<int>> getAllValuesCalledByStar();

    void insertNext(int lineNumber, std::unordered_set<int> nextLines);
    std::unordered_set<int> getNext(int lineNumber);
    bool isNext(int lineNumber, int nextLine);
    bool isNext(int lineNumber, std::unordered_set<int> nextLines);
    int getSizeNext();
    int getAreaNext();
    bool hasKeyNext(int lineNumber);
    std::vector<int> getAllKeysNext();
    std::vector<std::unordered_set<int>> getAllValuesNext();

    std::unordered_set<int> getPrevious(int lineNumber);
    bool isPrevious(int lineNumber, int previousLine);
    bool isPrevious(int lineNumber, std::unordered_set<int> previousLines);
    int getSizePrevious();
    int getAreaPrevious();
    bool hasKeyPrevious(int lineNumber);
    std::vector<int> getAllKeysPrevious();
    std::vector<std::unordered_set<int>> getAllValuesPrevious();

    void insertNextBip(int lineNumber, std::unordered_set<int> nextBipLines);
    std::unordered_set<int> getNextBip(int lineNumber);
    bool isNextBip(int lineNumber, int nextBipLine);
    bool isNextBip(int lineNumber, std::unordered_set<int> nextBipLines);
    int getSizeNextBip();
    int getAreaNextBip();
    bool hasKeyNextBip(int lineNumber);
    std::vector<int> getAllKeysNextBip();
    std::vector<std::unordered_set<int>> getAllValuesNextBip();

    std::unordered_set<int> getPreviousBip(int lineNumber);
    bool isPreviousBip(int lineNumber, int previousBipLine);
    bool isPreviousBip(int lineNumber, std::unordered_set<int> previousBipLines);
    int getSizePreviousBip();
    int getAreaPreviousBip();
    bool hasKeyPreviousBip(int lineNumber);
    std::vector<int> getAllKeysPreviousBip();
    std::vector<std::unordered_set<int>> getAllValuesPreviousBip();

    void insertNextBipStar(int lineNumber, std::unordered_set<int> nextBipLines);
    std::unordered_set<int> getNextBipStar(int lineNumber);
    bool isNextBipStar(int lineNumber, int nextBipStarLine);
    bool isNextBipStar(int lineNumber, std::unordered_set<int> nextBipStarLines);
    int getSizeNextBipStar();
    int getAreaNextBipStar();
    bool hasKeyNextBipStar(int lineNumber);
    std::vector<int> getAllKeysNextBipStar();
    std::vector<std::unordered_set<int>> getAllValuesNextBipStar();

    std::unordered_set<int> getPreviousBipStar(int lineNumber);
    bool isPreviousBipStar(int lineNumber, int previousBipStarLine);
    bool isPreviousBipStar(int lineNumber, std::unordered_set<int> previousBipStarLines);
    int getSizePreviousBipStar();
    int getAreaPreviousBipStar();
    bool hasKeyPreviousBipStar(int lineNumber);
    std::vector<int> getAllKeysPreviousBipStar();
    std::vector<std::unordered_set<int>> getAllValuesPreviousBipStar();

    void insertAffectsBip(int lineNumber, std::unordered_set<int> affectsBipLines);
    std::unordered_set<int> getAffectsBip(int lineNumber);
    bool isAffectsBip(int lineNumber, int affectsBipLine);
    bool isAffectsBip(int lineNumber, std::unordered_set<int> affectsBipLines);
    int getSizeAffectsBip();
    int getAreaAffectsBip();
    bool hasKeyAffectsBip(int lineNumber);
    std::vector<int> getAllKeysAffectsBip();
    std::vector<std::unordered_set<int>> getAllValuesAffectsBip();

    std::unordered_set<int> getAffectedByBip(int lineNumber);
    bool isAffectedByBip(int lineNumber, int affectedByBipLine);
    bool isAffectedByBip(int lineNumber, std::unordered_set<int> affectedByBipLines);
    int getSizeAffectedByBip();
    int getAreaAffectedByBip();
    bool hasKeyAffectedByBip(int lineNumber);
    std::vector<int> getAllKeysAffectedByBip();
    std::vector<std::unordered_set<int>> getAllValuesAffectedByBip();

    void insertAffectsBipStar(int lineNumber, std::unordered_set<int> affectsBipStarLines);
    std::unordered_set<int> getAffectsBipStar(int lineNumber);
    bool isAffectsBipStar(int lineNumber, int affectsBipStarLine);
    bool isAffectsBipStar(int lineNumber, std::unordered_set<int> affectsBipStarLines);
    int getSizeAffectsBipStar();
    int getAreaAffectsBipStar();
    bool hasKeyAffectsBipStar(int lineNumber);
    std::vector<int> getAllKeysAffectsBipStar();
    std::vector<std::unordered_set<int>> getAllValuesAffectsBipStar();

    std::unordered_set<int> getAffectedByBipStar(int lineNumber);
    bool isAffectedByBipStar(int lineNumber, int affectedByBipStarLine);
    bool isAffectedByBipStar(int lineNumber, std::unordered_set<int> affectedByBipStarLines);
    int getSizeAffectedByBipStar();
    int getAreaAffectedByBipStar();
    bool hasKeyAffectedByBipStar(int lineNumber);
    std::vector<int> getAllKeysAffectedByBipStar();
    std::vector<std::unordered_set<int>> getAllValuesAffectedByBipStar();

    void insertAffectsBipNode(int nodeNumber, std::unordered_set<int> affectsBipNodeNodes);
    std::unordered_set<int> getAffectsBipNode(int nodeNumber);
    bool isAffectsBipNode(int nodeNumber, int affectsBipNodeNode);
    bool isAffectsBipNode(int nodeNumber, std::unordered_set<int> affectsBipNodeNodes);
    int getSizeAffectsBipNode();
    int getAreaAffectsBipNode();
    bool hasKeyAffectsBipNode(int nodeNumber);
    std::vector<int> getAllKeysAffectsBipNode();
    std::vector<std::unordered_set<int>> getAllValuesAffectsBipNode();

    std::unordered_set<int> getAffectedByBipNode(int nodeNumber);
    bool isAffectedByBipNode(int nodeNumber, int affectedByBipNodeNode);
    bool isAffectedByBipNode(int nodeNumber, std::unordered_set<int> affectedByBipNodeNodes);
    int getSizeAffectedByBipNode();
    int getAreaAffectedByBipNode();
    bool hasKeyAffectedByBipNode(int nodeNumber);
    std::vector<int> getAllKeysAffectedByBipNode();
    std::vector<std::unordered_set<int>> getAllValuesAffectedByBipNode();
};
