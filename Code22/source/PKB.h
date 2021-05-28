#pragma once

#include "../source/PKB_Map_Procedure.h"
#include "../source/PKB_Map_Statement.h"
#include "../source/PKB_Map_StatementList.h"
#include "../source/PKB_Map_Read.h"
#include "../source/PKB_Map_Print.h"
#include "../source/PKB_Map_Assign.h"
#include "../source/PKB_Map_Assign_NonShunted.h"
#include "../source/PKB_Map_Call.h"
#include "../source/PKB_Map_While.h"
#include "../source/PKB_Map_If.h"
#include "../source/PKB_Map_Variable.h"
#include "../source/PKB_Map_Constant.h"

#include "../source/PKB_Map_Follows.h"
#include "../source/PKB_Map_FollowsStar.h"
#include "../source/PKB_Map_Parent.h"
#include "../source/PKB_Map_ParentStar.h"
#include "../source/PKB_Map_Uses.h"
#include "../source/PKB_Map_Modifies.h"

#include "../source/PKB_Util.h"

class PKB {
private:
    PKB_Map_Procedure procedureTable;
    PKB_Map_Statement statementTable;
    PKB_Map_StatementList statementListTable;
    PKB_Map_StatementList procedureStatementListTable;
    PKB_Map_Read readTable;
    PKB_Map_Print printTable;
    PKB_Map_Assign assignTable;
    PKB_Map_Assign_NonShunted assignTableNonShunted;
    PKB_Map_Call callTable;
    PKB_Map_While whileTable;
    PKB_Map_If ifTable;
    PKB_Map_Variable variableTable;
    PKB_Map_Constant constantTable;

    PKB_Map_Follows followsTable;
    PKB_Map_FollowsStar followsStarTable;
    PKB_Map_Parent parentTable;
    PKB_Map_ParentStar parentStarTable;
    PKB_Map_Uses usesTable;
    PKB_Map_Modifies modifiesTable;
    PKB_Map_Uses procedureUsesTable;
    PKB_Map_Modifies procedureModifiesTable;

    PKB(); // Prevent construction
    PKB(const PKB&); // Prevent construction by copying
    PKB& operator=(const PKB&); // Prevent assignment
    ~PKB(); // Prevent unwanted destruction

public:
    static PKB& getInstance()
    {
        static PKB inst;
        return inst;
    }

    void clearAll();

    void insertProcedure(std::string procName);
    std::string getProcedure(int procIndex);
    int getSizeProcedure();
    bool hasKeyProcedure(int procIndex);
    std::vector<int> getAllKeysProcedure();
    std::vector<std::string> getAllValuesProcedure();

    void insertStatement(int lineNumber, std::string statementType);
    std::string getStatement(int lineNumber);
    bool isStatementType(int lineNumber, std::string statementType);
    std::unordered_set<int> getStatementKeys(std::string statementType);
    int getSizeStatement();
    bool hasKeyStatement(int lineNumber);
    std::vector<int> getAllKeysStatement();
    std::vector<std::string> getAllValuesStatement();

    void insertStatementList(int lineNumber, std::unordered_set<int> statementLines);
    std::unordered_set<int> getStatementList(int lineNumber);
    int getSizeStatementList();
    bool hasKeyStatementList(int lineNumber);
    std::vector<int> getAllKeysStatementList();
    std::vector<std::unordered_set<int>> getAllValuesStatementList();

    void insertProcedureStatementList(int lineNumber, std::unordered_set<int> statementLines);
    std::unordered_set<int> getProcedureStatementList(int lineNumber);
    int getSizeProcedureStatementList();
    bool hasKeyProcedureStatementList(int lineNumber);
    std::vector<int> getAllKeysProcedureStatementList();
    std::vector<std::unordered_set<int>> getAllValuesProcedureStatementList();

    void insertRead(int lineNumber, std::string varName);
    std::string getRead(int lineNumber);
    std::unordered_set<int> getReadKeys(std::string varName);
    int getSizeRead();
    bool hasKeyRead(int lineNumber);
    std::vector<int> getAllKeysRead();
    std::vector<std::string> getAllValuesRead();

    void insertPrint(int lineNumber, std::string varName);
    std::string getPrint(int lineNumber);
    std::unordered_set<int> getPrintKeys(std::string varName);
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

    void insertAssignNonShunted(int lineNumber, std::string assignStmt);
    std::string getAssignNonShunted(int lineNumber);
    int getSizeAssignNonShunted();
    bool hasKeyAssignNonShunted(int lineNumber);
    std::vector<int> getAllKeysAssignNonShunted();
    std::vector<std::string> getAllValuesAssignNonShunted();

    void insertCall(int lineNumber, std::string procName);
    std::string getCall(int lineNumber);
    std::unordered_set<int> getCallKeys(std::string procName);
    int getSizeCall();
    bool hasKeyCall(int lineNumber);
    std::vector<int> getAllKeysCall();
    std::vector<std::string> getAllValuesCall();

    void insertWhile(int lineNumber, std::string condition);
    std::string getWhile(int lineNumber);
    std::unordered_set<int> getWhileKeys(std::string condition);
    int getSizeWhile();
    bool hasKeyWhile(int lineNumber);
    std::vector<int> getAllKeysWhile();
    std::vector<std::string> getAllValuesWhile();

    void insertIf(int lineNumber, std::string condition);
    std::string getIf(int lineNumber);
    std::unordered_set<int> getIfKeys(std::string condition);
    int getSizeIf();
    bool hasKeyIf(int lineNumber);
    std::vector<int> getAllKeysIf();
    std::vector<std::string> getAllValuesIf();

    void insertIfWhile(int lineNumber, std::string condition);

    int insertVariable(std::string varName);
    std::string getVariable(int index);
    int getVariableKey(std::string varName);
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
    bool hasKeyFollowsStar(int lineNumber);
    std::vector<int> getAllKeysFollowsStar();
    std::vector<std::unordered_set<int>> getAllValuesFollowsStar();

    std::unordered_set<int> getFollowedByStar(int lineNumber);
    bool isFollowedByStar(int lineNumber, int followerLine);
    bool isFollowedByStar(int lineNumber, std::unordered_set<int> followerLines);
    int getSizeFollowedByStar();
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
    bool hasKeyParentStar(int lineNumber);
    std::vector<int> getAllKeysParentStar();
    std::vector<std::unordered_set<int>> getAllValuesParentStar();

    std::unordered_set<int> getChildStar(int lineNumber);
    bool isChildStar(int lineNumber, int childLine);
    bool isChildStar(int lineNumber, std::unordered_set<int> childLines);
    int getSizeChildStar();
    bool hasKeyChildStar(int lineNumber);
    std::vector<int> getAllKeysChildStar();
    std::vector<std::unordered_set<int>> getAllValuesChildStar();

    void insertUses(int lineNumber, std::unordered_set<std::string> usedNames);
    std::unordered_set<std::string> getUses(int lineNumber);
    bool isUses(int lineNumber, std::string usedName);
    bool isUses(int lineNumber, std::unordered_set<std::string> usedNames);
    int getSizeUses();
    bool hasKeyUses(int lineNumber);
    std::vector<int> getAllKeysUses();
    std::vector<std::unordered_set<std::string>> getAllValuesUses();

    std::unordered_set<int> getUsedBy(std::string name);
    bool isUsedBy(std::string name, int usedByLine);
    bool isUsedBy(std::string name, std::unordered_set<int> usedByLines);
    int getSizeUsedBy();
    bool hasKeyUsedBy(std::string name);
    std::vector<std::string> getAllKeysUsedBy();
    std::vector<std::unordered_set<int>> getAllValuesUsedBy();

    void insertModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    std::unordered_set<std::string> getModifies(int lineNumber);
    bool isModifies(int lineNumber, std::string modifiedName);
    bool isModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    int getSizeModifies();
    bool hasKeyModifies(int lineNumber);
    std::vector<int> getAllKeysModifies();
    std::vector<std::unordered_set<std::string>> getAllValuesModifies();

    std::unordered_set<int> getModifiedBy(std::string name);
    bool isModifiedBy(std::string name, int modifiedByLine);
    bool isModifiedBy(std::string name, std::unordered_set<int> modifiedByLines);
    int getSizeModifiedBy();
    bool hasKeyModifiedBy(std::string name);
    std::vector<std::string> getAllKeysModifiedBy();
    std::vector<std::unordered_set<int>> getAllValuesModifiedBy();

    void insertProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames);
    std::unordered_set<std::string> getProcedureUses(int lineNumber);
    bool isProcedureUses(int lineNumber, std::string procedureUsedName);
    bool isProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames);
    int getSizeProcedureUses();
    bool hasKeyProcedureUses(int lineNumber);
    std::vector<int> getAllKeysProcedureUses();
    std::vector<std::unordered_set<std::string>> getAllValuesProcedureUses();

    std::unordered_set<int> getProcedureUsedBy(std::string name);
    bool isProcedureUsedBy(std::string name, int usedByLine);
    bool isProcedureUsedBy(std::string name, std::unordered_set<int> usedByLines);
    int getSizeProcedureUsedBy();
    bool hasKeyProcedureUsedBy(std::string name);
    std::vector<std::string> getAllKeysProcedureUsedBy();
    std::vector<std::unordered_set<int>> getAllValuesProcedureUsedBy();

    void insertProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    std::unordered_set<std::string> getProcedureModifies(int lineNumber);
    bool isProcedureModifies(int lineNumber, std::string modifiedName);
    bool isProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
    int getSizeProcedureModifies();
    bool hasKeyProcedureModifies(int lineNumber);
    std::vector<int> getAllKeysProcedureModifies();
    std::vector<std::unordered_set<std::string>> getAllValuesProcedureModifies();

    std::unordered_set<int> getProcedureModifiedBy(std::string name);
    bool isProcedureModifiedBy(std::string name, int modifiedByLine);
    bool isProcedureModifiedBy(std::string name, std::unordered_set<int> modifiedByLines);
    int getSizeProcedureModifiedBy();
    bool hasKeyProcedureModifiedBy(std::string name);
    std::vector<std::string> getAllKeysProcedureModifiedBy();
    std::vector<std::unordered_set<int>> getAllValuesProcedureModifiedBy();
};