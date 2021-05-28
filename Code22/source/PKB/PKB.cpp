#include "PKB.h"

PKB::PKB() {}
PKB::~PKB() {}

void PKB::clear() {
    procedureTable.clear();
    statementTable.clear();
    statementListTable.clear();
    procedureStatementListTable.clear();
    readTable.clear();
    printTable.clear();
    assignTable.clear();
    callTable.clear();
    whileTable.clear();
    ifTable.clear();
    variableTable.clear();
    constantTable.clear();

    followsTable.clear();
    followsStarTable.clear();
    parentTable.clear();
    parentStarTable.clear();
    usesTable.clear();
    modifiesTable.clear();
    procedureUsesTable.clear();
    procedureModifiesTable.clear();

    callsTable.clear();
    callsStarTable.clear();
    nextTable.clear();
    nextBipTable.clear();
    nextBipStarTable.clear();
    affectsBipTable.clear();
    affectsBipStarTable.clear();
    affectsBipNodeTable.clear();
}

void PKB::precompute() {
    whileTable.getArea();
    ifTable.getArea();

    followsStarTable.getArea();
    parentStarTable.getArea();
    usesTable.getArea();
    modifiesTable.getArea();
    procedureUsesTable.getArea();
    procedureModifiesTable.getArea();

    callsTable.getArea();
    callsStarTable.getArea();
    nextTable.getArea();
    nextBipTable.getArea();
    nextBipStarTable.getArea();
    affectsBipTable.getArea();
    affectsBipStarTable.getArea();
    affectsBipNodeTable.getArea();
}

int PKB::insertProcedure(std::string procName) {
    return PKB::procedureTable.insertThing(procName);
}
std::string PKB::getProcedure(int procIndex) {
    return PKB::procedureTable.getThing(procIndex);
}
int PKB::getKeyProcedure(std::string procName) {
    return PKB::procedureTable.getKey(procName);
}
int PKB::getSizeProcedure() {
    return PKB::procedureTable.getSize();
}
bool PKB::hasKeyProcedure(int procIndex) {
    return PKB::procedureTable.hasKey(procIndex);
}
std::vector<int> PKB::getAllKeysProcedure() {
    return PKB::procedureTable.getAllKeys();
}
std::vector<std::string> PKB::getAllValuesProcedure() {
    return PKB::procedureTable.getAllValues();
}

void PKB::insertStatement(int lineNumber, std::string statementType) {
    PKB::statementTable.insertThing(lineNumber, statementType);
}
std::string PKB::getStatement(int lineNumber) {
    return PKB::statementTable.getThing(lineNumber);
}
bool PKB::isStatement(int lineNumber, std::string statementType) {
    return PKB::statementTable.isThing(lineNumber, statementType);
}
std::unordered_set<int> PKB::getKeysStatement(std::string statementType) {
    return PKB::statementTable.getKeys(statementType);
}
int PKB::getSizeStatement() {
    return PKB::statementTable.getSize();
}
bool PKB::hasKeyStatement(int lineNumber) {
    return PKB::statementTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysStatement() {
    return PKB::statementTable.getAllKeys();
}
std::vector<std::string> PKB::getAllValuesStatement() {
    return PKB::statementTable.getAllValues();
}

void PKB::insertStatementList(int lineNumber, std::unordered_set<int> statementLines) {
    PKB::statementListTable.insertStatementList(lineNumber, statementLines);
}
std::unordered_set<int> PKB::getStatementList(int lineNumber) {
    return PKB::statementListTable.getStatementList(lineNumber);
}
int PKB::getKeyStatementList(int lineNumber) {
    return PKB::statementListTable.getKeyStatementList(lineNumber);
}
int PKB::getSizeStatementList() {
    return PKB::statementListTable.getSizeStatementList();
}
bool PKB::hasKeyStatementList(int lineNumber) {
    return PKB::statementListTable.hasKeyStatementList(lineNumber);
}
std::vector<int> PKB::getAllKeysStatementList() {
    return PKB::statementListTable.getAllKeysStatementList();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesStatementList() {
    return PKB::statementListTable.getAllValuesStatementList();
}

void PKB::insertProcedureStatementList(int lineNumber, std::unordered_set<int> statementLines) {
    PKB::procedureStatementListTable.insertStatementList(lineNumber, statementLines);
}
std::unordered_set<int> PKB::getProcedureStatementList(int lineNumber) {
    return PKB::procedureStatementListTable.getStatementList(lineNumber);
}
int PKB::getKeyProcedureStatementList(int lineNumber) {
    return PKB::procedureStatementListTable.getKeyStatementList(lineNumber);
}
int PKB::getSizeProcedureStatementList() {
    return PKB::procedureStatementListTable.getSizeStatementList();
}
bool PKB::hasKeyProcedureStatementList(int lineNumber) {
    return PKB::procedureStatementListTable.hasKeyStatementList(lineNumber);
}
std::vector<int> PKB::getAllKeysProcedureStatementList() {
    return PKB::procedureStatementListTable.getAllKeysStatementList();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesProcedureStatementList() {
    return PKB::procedureStatementListTable.getAllValuesStatementList();
}

void PKB::insertRead(int lineNumber, std::string varName) {
    PKB::readTable.insertThing(lineNumber, varName);
}
std::string PKB::getRead(int lineNumber) {
    return PKB::readTable.getThing(lineNumber);
}
std::unordered_set<int> PKB::getKeysRead(std::string varName) {
    return PKB::readTable.getKeys(varName);
}
int PKB::getSizeRead() {
    return PKB::readTable.getSize();
}
bool PKB::hasKeyRead(int lineNumber) {
    return PKB::readTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysRead() {
    return PKB::readTable.getAllKeys();
}
std::vector<std::string> PKB::getAllValuesRead() {
    return PKB::readTable.getAllValues();
}

void PKB::insertPrint(int lineNumber, std::string varName) {
    PKB::printTable.insertThing(lineNumber, varName);
}
std::string PKB::getPrint(int lineNumber) {
    return PKB::printTable.getThing(lineNumber);
}
std::unordered_set<int> PKB::getKeysPrint(std::string varName) {
    return PKB::printTable.getKeys(varName);
}
int PKB::getSizePrint() {
    return PKB::printTable.getSize();
}
bool PKB::hasKeyPrint(int lineNumber) {
    return PKB::printTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysPrint() {
    return PKB::printTable.getAllKeys();
}
std::vector<std::string> PKB::getAllValuesPrint() {
    return PKB::printTable.getAllValues();
}

void PKB::insertAssignLHS(int lineNumber, std::string variableLHS) {
    PKB::assignTable.insertAssignLHS(lineNumber, variableLHS);
}
void PKB::insertAssignRHS(int lineNumber, std::string shuntedRHS) {
    PKB::assignTable.insertAssignRHS(lineNumber, shuntedRHS);
}
std::pair<std::string, std::string> PKB::getAssign(int lineNumber) {
    return PKB::assignTable.getAssign(lineNumber);
}
int PKB::getSizeAssign() {
    return PKB::assignTable.getSizeAssign();
}
bool PKB::hasKeyAssign(int lineNumber) {
    return PKB::assignTable.hasKeyAssign(lineNumber);
}
std::vector<int> PKB::getAllKeysAssign() {
    return PKB::assignTable.getAllKeysAssign();
}
std::vector<std::pair<std::string, std::string>> PKB::getAllValuesAssign() {
    return PKB::assignTable.getAllValuesAssign();
}

void PKB::insertCall(int lineNumber, std::string procName) {
    PKB::callTable.insertThing(lineNumber, procName);
}
std::string PKB::getCall(int lineNumber) {
    return PKB::callTable.getThing(lineNumber);
}
std::unordered_set<int> PKB::getKeysCall(std::string procName) {
    return PKB::callTable.getKeys(procName);
}
int PKB::getSizeCall() {
    return PKB::callTable.getSize();
}
bool PKB::hasKeyCall(int lineNumber) {
    return PKB::callTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysCall() {
    return PKB::callTable.getAllKeys();
}
std::vector<std::string> PKB::getAllValuesCall() {
    return PKB::callTable.getAllValues();
}

void PKB::insertWhile(int lineNumber, std::unordered_set<std::string> condition) {
    PKB::whileTable.insertThing(lineNumber, condition);
}
std::unordered_set<std::string> PKB::getWhile(int lineNumber) {
    return PKB::whileTable.getThing(lineNumber);
}
bool PKB::isWhile(int lineNumber, std::string condition) {
    return PKB::whileTable.isThing(lineNumber, condition);
}
bool PKB::isWhile(int lineNumber, std::unordered_set<std::string> conditions) {
    return PKB::whileTable.isThing(lineNumber, conditions);
}
int PKB::getSizeWhile() {
    return PKB::whileTable.getSize();
}
int PKB::getAreaWhile() {
    return PKB::whileTable.getArea();
}
bool PKB::hasKeyWhile(int lineNumber) {
    return PKB::whileTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysWhile() {
    return PKB::whileTable.getAllKeys();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesWhile() {
    return PKB::whileTable.getAllValues();
}

void PKB::insertIf(int lineNumber, std::unordered_set<std::string> condition) {
    PKB::ifTable.insertThing(lineNumber, condition);
}
std::unordered_set<std::string> PKB::getIf(int lineNumber) {
    return PKB::ifTable.getThing(lineNumber);
}
bool PKB::isIf(int lineNumber, std::string condition) {
    return PKB::ifTable.isThing(lineNumber, condition);
}
bool PKB::isIf(int lineNumber, std::unordered_set<std::string> conditions) {
    return PKB::ifTable.isThing(lineNumber, conditions);
}
int PKB::getSizeIf() {
    return PKB::ifTable.getSize();
}
int PKB::getAreaIf() {
    return PKB::ifTable.getArea();
}
bool PKB::hasKeyIf(int lineNumber) {
    return PKB::ifTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysIf() {
    return PKB::ifTable.getAllKeys();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesIf() {
    return PKB::ifTable.getAllValues();
}

void PKB::insertIfWhile(int lineNumber, std::string condition) {
    if (ifTable.hasKey(lineNumber)) {
        PKB::insertIf(lineNumber, { condition });
    }
    else if (whileTable.hasKey(lineNumber)) {
        PKB::insertWhile(lineNumber, { condition });
    }
    else {
        throw PKB_Util::noIfWhileEntryError(lineNumber);
    }
}

int PKB::insertVariable(std::string varName) {
    return PKB::variableTable.insertThing(varName);
}
std::string PKB::getVariable(int index) {
    return PKB::variableTable.getThing(index);
}
int PKB::getKeyVariable(std::string varName) {
    return PKB::variableTable.getKey(varName);
}
int PKB::getSizeVariable() {
    return PKB::variableTable.getSize();
}
bool PKB::hasKeyVariable(int index) {
    return PKB::variableTable.hasKey(index);
}
std::vector<int> PKB::getAllKeysVariable() {
    return PKB::variableTable.getAllKeys();
}
std::vector<std::string> PKB::getAllValuesVariable() {
    return PKB::variableTable.getAllValues();
}

void PKB::insertConstant(int lineNumber, std::unordered_set<int> constantValues) {
    PKB::constantTable.insertConstant(lineNumber, constantValues);
}
std::unordered_set<int> PKB::getConstant(int lineNumber) {
    return PKB::constantTable.getConstant(lineNumber);
}
bool PKB::isConstant(int lineNumber, std::unordered_set<int> constantValues) {
    return PKB::constantTable.isConstant(lineNumber, constantValues);
}
bool PKB::isConstant(int lineNumber, int constantValue) {
    return PKB::constantTable.isConstant(lineNumber, constantValue);
}
int PKB::getSizeConstant() {
    return PKB::constantTable.getSizeConstant();
}
bool PKB::hasKeyConstant(int lineNumber) {
    return PKB::constantTable.hasKeyConstant(lineNumber);
}
std::vector<int> PKB::getAllKeysConstant() {
    return PKB::constantTable.getAllKeysConstant();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesConstant() {
    return PKB::constantTable.getAllValuesConstant();
}

void PKB::insertFollows(int lineNumber, int leaderLine) {
    PKB::followsTable.insertFollows(lineNumber, leaderLine);
}
int PKB::getFollows(int lineNumber) {
    return PKB::followsTable.getFollows(lineNumber);
}
bool PKB::isFollows(int lineNumber, int leaderLine) {
    return PKB::followsTable.isFollows(lineNumber, leaderLine);
}
int PKB::getSizeFollows() {
    return PKB::followsTable.getSizeFollows();
}
bool PKB::hasKeyFollows(int lineNumber) {
    return PKB::followsTable.hasKeyFollows(lineNumber);
}
std::vector<int> PKB::getAllKeysFollows() {
    return PKB::followsTable.getAllKeysFollows();
}
std::vector<int> PKB::getAllValuesFollows() {
    return PKB::followsTable.getAllValuesFollows();
}

int PKB::getFollowedBy(int lineNumber) {
    return PKB::followsTable.getFollowedBy(lineNumber);
}
bool PKB::isFollowedBy(int lineNumber, int followerLine) {
    return PKB::followsTable.isFollowedBy(lineNumber, followerLine);
}
int PKB::getSizeFollowedBy() {
    return PKB::followsTable.getSizeFollowedBy();
}
bool PKB::hasKeyFollowedBy(int lineNumber) {
    return PKB::followsTable.hasKeyFollowedBy(lineNumber);
}
std::vector<int> PKB::getAllKeysFollowedBy() {
    return PKB::followsTable.getAllKeysFollowedBy();
}
std::vector<int> PKB::getAllValuesFollowedBy() {
    return PKB::followsTable.getAllValuesFollowedBy();
}

void PKB::insertFollowsStar(int lineNumber, std::unordered_set<int> leaderLines) {
    PKB::followsStarTable.insertThing(lineNumber, leaderLines);
}
std::unordered_set<int> PKB::getFollowsStar(int lineNumber) {
    return PKB::followsStarTable.getThing(lineNumber);
}
bool PKB::isFollowsStar(int lineNumber, int leaderLine) {
    return PKB::followsStarTable.isThing(lineNumber, leaderLine);
}
bool PKB::isFollowsStar(int lineNumber, std::unordered_set<int> leaderLines) {
    return PKB::followsStarTable.isThing(lineNumber, leaderLines);
}
int PKB::getSizeFollowsStar() {
    return PKB::followsStarTable.getSize();
}
int PKB::getAreaFollowsStar() {
    return PKB::followsStarTable.getArea();
}
bool PKB::hasKeyFollowsStar(int lineNumber) {
    return PKB::followsStarTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysFollowsStar() {
    return PKB::followsStarTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesFollowsStar() {
    return PKB::followsStarTable.getAllValues();
}

std::unordered_set<int> PKB::getFollowedByStar(int lineNumber) {
    return PKB::followsStarTable.getThingReverse(lineNumber);
}
bool PKB::isFollowedByStar(int lineNumber, int followerLine) {
    return PKB::followsStarTable.isThingReverse(lineNumber, followerLine);
}
bool PKB::isFollowedByStar(int lineNumber, std::unordered_set<int> followerLines) {
    return PKB::followsStarTable.isThingReverse(lineNumber, followerLines);
}
int PKB::getSizeFollowedByStar() {
    return PKB::followsStarTable.getSizeReverse();
}
int PKB::getAreaFollowedByStar() {
    return PKB::followsStarTable.getArea();
}
bool PKB::hasKeyFollowedByStar(int lineNumber) {
    return PKB::followsStarTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysFollowedByStar() {
    return PKB::followsStarTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesFollowedByStar() {
    return PKB::followsStarTable.getAllValuesReverse();
}

void PKB::insertParent(int lineNumber, int parentLine) {
    PKB::parentTable.insertParent(lineNumber, parentLine);
}
int PKB::getParent(int lineNumber) {
    return PKB::parentTable.getParent(lineNumber);
}
bool PKB::isParent(int lineNumber, int parentLine) {
    return PKB::parentTable.isParent(lineNumber, parentLine);
}
int PKB::getSizeParent() {
    return PKB::parentTable.getSizeParent();
}
bool PKB::hasKeyParent(int lineNumber) {
    return PKB::parentTable.hasKeyParent(lineNumber);
}
std::vector<int> PKB::getAllKeysParent() {
    return PKB::parentTable.getAllKeysParent();
}
std::vector<int> PKB::getAllValuesParent() {
    return PKB::parentTable.getAllValuesParent();
}

std::unordered_set<int> PKB::getChild(int lineNumber) {
    return PKB::parentTable.getChild(lineNumber);
}
bool PKB::isChild(int lineNumber, int childLine) {
    return PKB::parentTable.isChild(lineNumber, childLine);
}
bool PKB::isChild(int lineNumber, std::unordered_set<int> childLines) {
    return PKB::parentTable.isChild(lineNumber, childLines);
}
int PKB::getSizeChild() {
    return PKB::parentTable.getSizeChild();
}
bool PKB::hasKeyChild(int lineNumber) {
    return PKB::parentTable.hasKeyChild(lineNumber);
}
std::vector<int> PKB::getAllKeysChild() {
    return PKB::parentTable.getAllKeysChild();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesChild() {
    return PKB::parentTable.getAllValuesChild();
}

void PKB::insertParentStar(int lineNumber, std::unordered_set<int> parentLines) {
    PKB::parentStarTable.insertThing(lineNumber, parentLines);
}
std::unordered_set<int> PKB::getParentStar(int lineNumber) {
    return PKB::parentStarTable.getThing(lineNumber);
}
bool PKB::isParentStar(int lineNumber, int parentLine) {
    return PKB::parentStarTable.isThing(lineNumber, parentLine);
}
bool PKB::isParentStar(int lineNumber, std::unordered_set<int> parentLines) {
    return PKB::parentStarTable.isThing(lineNumber, parentLines);
}
int PKB::getSizeParentStar() {
    return PKB::parentStarTable.getSize();
}
int PKB::getAreaParentStar() {
    return PKB::parentStarTable.getArea();
}
bool PKB::hasKeyParentStar(int lineNumber) {
    return PKB::parentStarTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysParentStar() {
    return PKB::parentStarTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesParentStar() {
    return PKB::parentStarTable.getAllValues();
}

std::unordered_set<int> PKB::getChildStar(int lineNumber) {
    return PKB::parentStarTable.getThingReverse(lineNumber);
}
bool PKB::isChildStar(int lineNumber, int childLine) {
    return PKB::parentStarTable.isThingReverse(lineNumber, childLine);
}
bool PKB::isChildStar(int lineNumber, std::unordered_set<int> childLines) {
    return PKB::parentStarTable.isThingReverse(lineNumber, childLines);
}
int PKB::getSizeChildStar() {
    return PKB::parentStarTable.getSizeReverse();
}
int PKB::getAreaChildStar() {
    return PKB::parentStarTable.getArea();
}
bool PKB::hasKeyChildStar(int lineNumber) {
    return PKB::parentStarTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysChildStar() {
    return PKB::parentStarTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesChildStar() {
    return PKB::parentStarTable.getAllValuesReverse();
}

void PKB::insertUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    PKB::usesTable.insertThing(lineNumber, usedNames);
}
std::unordered_set<std::string> PKB::getUses(int lineNumber) {
    return PKB::usesTable.getThing(lineNumber);
}
bool PKB::isUses(int lineNumber, std::string usedName) {
    return PKB::usesTable.isThing(lineNumber, usedName);
}
bool PKB::isUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    return PKB::usesTable.isThing(lineNumber, usedNames);
}
int PKB::getSizeUses() {
    return PKB::usesTable.getSize();
}
int PKB::getAreaUses() {
    return PKB::usesTable.getArea();
}
bool PKB::hasKeyUses(int lineNumber) {
    return PKB::usesTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysUses() {
    return PKB::usesTable.getAllKeys();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesUses() {
    return PKB::usesTable.getAllValues();
}

std::unordered_set<int> PKB::getUsedBy(std::string name) {
    return PKB::usesTable.getThingReverse(name);
}
bool PKB::isUsedBy(std::string name, int usedByLine) {
    return PKB::usesTable.isThingReverse(name, usedByLine);
}
bool PKB::isUsedBy(std::string name, std::unordered_set<int> usedByLines) {
    return PKB::usesTable.isThingReverse(name, usedByLines);
}
int PKB::getSizeUsedBy() {
    return PKB::usesTable.getSizeReverse();
}
int PKB::getAreaUsedBy() {
    return PKB::usesTable.getArea();
}
bool PKB::hasKeyUsedBy(std::string name) {
    return PKB::usesTable.hasKeyReverse(name);
}
std::vector<std::string> PKB::getAllKeysUsedBy() {
    return PKB::usesTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesUsedBy() {
    return PKB::usesTable.getAllValuesReverse();
}

void PKB::insertModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
    PKB::modifiesTable.insertThing(lineNumber, modifiedNames);
}
std::unordered_set<std::string> PKB::getModifies(int lineNumber) {
    return PKB::modifiesTable.getThing(lineNumber);
}
bool PKB::isModifies(int lineNumber, std::string modifiedName) {
    return PKB::modifiesTable.isThing(lineNumber, modifiedName);
}
bool PKB::isModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
    return PKB::modifiesTable.isThing(lineNumber, modifiedNames);
}
int PKB::getSizeModifies() {
    return PKB::modifiesTable.getSize();
}
int PKB::getAreaModifies() {
    return PKB::modifiesTable.getArea();
}
bool PKB::hasKeyModifies(int lineNumber) {
    return PKB::modifiesTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysModifies() {
    return PKB::modifiesTable.getAllKeys();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesModifies() {
    return PKB::modifiesTable.getAllValues();
}

std::unordered_set<int> PKB::getModifiedBy(std::string name) {
    return PKB::modifiesTable.getThingReverse(name);
}
bool PKB::isModifiedBy(std::string name, int modifiedByLine) {
    return PKB::modifiesTable.isThingReverse(name, modifiedByLine);
}
bool PKB::isModifiedBy(std::string name, std::unordered_set<int> modifiedByLines) {
    return PKB::modifiesTable.isThingReverse(name, modifiedByLines);
}
int PKB::getSizeModifiedBy() {
    return PKB::modifiesTable.getSizeReverse();
}
int PKB::getAreaModifiedBy() {
    return PKB::modifiesTable.getArea();
}
bool PKB::hasKeyModifiedBy(std::string name) {
    return PKB::modifiesTable.hasKeyReverse(name);
}
std::vector<std::string> PKB::getAllKeysModifiedBy() {
    return PKB::modifiesTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesModifiedBy() {
    return PKB::modifiesTable.getAllValuesReverse();
}

void PKB::insertProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    PKB::procedureUsesTable.insertThing(lineNumber, usedNames);
}
std::unordered_set<std::string> PKB::getProcedureUses(int lineNumber) {
    return PKB::procedureUsesTable.getThing(lineNumber);
}
bool PKB::isProcedureUses(int lineNumber, std::string usedName) {
    return PKB::procedureUsesTable.isThing(lineNumber, usedName);
}
bool PKB::isProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    return PKB::procedureUsesTable.isThing(lineNumber, usedNames);
}
int PKB::getSizeProcedureUses() {
    return PKB::procedureUsesTable.getSize();
}
int PKB::getAreaProcedureUses() {
    return PKB::procedureUsesTable.getArea();
}
bool PKB::hasKeyProcedureUses(int lineNumber) {
    return PKB::procedureUsesTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysProcedureUses() {
    return PKB::procedureUsesTable.getAllKeys();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesProcedureUses() {
    return PKB::procedureUsesTable.getAllValues();
}

std::unordered_set<int> PKB::getProcedureUsedBy(std::string name) {
    return PKB::procedureUsesTable.getThingReverse(name);
}
bool PKB::isProcedureUsedBy(std::string name, int usedByLine) {
    return PKB::procedureUsesTable.isThingReverse(name, usedByLine);
}
bool PKB::isProcedureUsedBy(std::string name, std::unordered_set<int> usedByLines) {
    return PKB::procedureUsesTable.isThingReverse(name, usedByLines);
}
int PKB::getSizeProcedureUsedBy() {
    return PKB::procedureUsesTable.getSizeReverse();
}
int PKB::getAreaProcedureUsedBy() {
    return PKB::procedureUsesTable.getArea();
}
bool PKB::hasKeyProcedureUsedBy(std::string name) {
    return PKB::procedureUsesTable.hasKeyReverse(name);
}
std::vector<std::string> PKB::getAllKeysProcedureUsedBy() {
    return PKB::procedureUsesTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesProcedureUsedBy() {
    return PKB::procedureUsesTable.getAllValuesReverse();
}

void PKB::insertProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
    PKB::procedureModifiesTable.insertThing(lineNumber, modifiedNames);
}
std::unordered_set<std::string> PKB::getProcedureModifies(int lineNumber) {
    return PKB::procedureModifiesTable.getThing(lineNumber);
}
bool PKB::isProcedureModifies(int lineNumber, std::string modifiedName) {
    return PKB::procedureModifiesTable.isThing(lineNumber, modifiedName);
}
bool PKB::isProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
    return PKB::procedureModifiesTable.isThing(lineNumber, modifiedNames);
}
int PKB::getSizeProcedureModifies() {
    return PKB::procedureModifiesTable.getSize();
}
int PKB::getAreaProcedureModifies() {
    return PKB::procedureModifiesTable.getArea();
}
bool PKB::hasKeyProcedureModifies(int lineNumber) {
    return PKB::procedureModifiesTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysProcedureModifies() {
    return PKB::procedureModifiesTable.getAllKeys();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesProcedureModifies() {
    return PKB::procedureModifiesTable.getAllValues();
}

std::unordered_set<int> PKB::getProcedureModifiedBy(std::string name) {
    return PKB::procedureModifiesTable.getThingReverse(name);
}
bool PKB::isProcedureModifiedBy(std::string name, int modifiedByLine) {
    return PKB::procedureModifiesTable.isThingReverse(name, modifiedByLine);
}
bool PKB::isProcedureModifiedBy(std::string name, std::unordered_set<int> modifiedByLines) {
    return PKB::procedureModifiesTable.isThingReverse(name, modifiedByLines);
}
int PKB::getSizeProcedureModifiedBy() {
    return PKB::procedureModifiesTable.getSizeReverse();
}
int PKB::getAreaProcedureModifiedBy() {
    return PKB::procedureModifiesTable.getArea();
}
bool PKB::hasKeyProcedureModifiedBy(std::string name) {
    return PKB::procedureModifiesTable.hasKeyReverse(name);
}
std::vector<std::string> PKB::getAllKeysProcedureModifiedBy() {
    return PKB::procedureModifiesTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesProcedureModifiedBy() {
    return PKB::procedureModifiesTable.getAllValuesReverse();
}

void PKB::insertCalls(int lineNumber, std::unordered_set<int> calledLines) {
    PKB::callsTable.insertThing(lineNumber, calledLines);
}
std::unordered_set<int> PKB::getCalls(int lineNumber) {
    return PKB::callsTable.getThing(lineNumber);
}
bool PKB::isCalls(int lineNumber, int parentLine) {
    return PKB::callsTable.isThing(lineNumber, parentLine);
}
bool PKB::isCalls(int lineNumber, std::unordered_set<int> calledLines) {
    return PKB::callsTable.isThing(lineNumber, calledLines);
}
int PKB::getSizeCalls() {
    return PKB::callsTable.getSize();
}
int PKB::getAreaCalls() {
    return PKB::callsTable.getArea();
}
bool PKB::hasKeyCalls(int lineNumber) {
    return PKB::callsTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysCalls() {
    return PKB::callsTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesCalls() {
    return PKB::callsTable.getAllValues();
}

std::unordered_set<int> PKB::getCalledBy(int lineNumber) {
    return PKB::callsTable.getThingReverse(lineNumber);
}
bool PKB::isCalledBy(int lineNumber, int childLine) {
    return PKB::callsTable.isThingReverse(lineNumber, childLine);
}
bool PKB::isCalledBy(int lineNumber, std::unordered_set<int> calledByLines) {
    return PKB::callsTable.isThingReverse(lineNumber, calledByLines);
}
int PKB::getSizeCalledBy() {
    return PKB::callsTable.getSizeReverse();
}
int PKB::getAreaCalledBy() {
    return PKB::callsTable.getArea();
}
bool PKB::hasKeyCalledBy(int lineNumber) {
    return PKB::callsTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysCalledBy() {
    return PKB::callsTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesCalledBy() {
    return PKB::callsTable.getAllValuesReverse();
}

void PKB::insertCallsStar(int lineNumber, std::unordered_set<int> calledLines) {
    PKB::callsStarTable.insertThing(lineNumber, calledLines);
}
std::unordered_set<int> PKB::getCallsStar(int lineNumber) {
    return PKB::callsStarTable.getThing(lineNumber);
}
bool PKB::isCallsStar(int lineNumber, int parentLine) {
    return PKB::callsStarTable.isThing(lineNumber, parentLine);
}
bool PKB::isCallsStar(int lineNumber, std::unordered_set<int> calledLines) {
    return PKB::callsStarTable.isThing(lineNumber, calledLines);
}
int PKB::getSizeCallsStar() {
    return PKB::callsStarTable.getSize();
}
int PKB::getAreaCallsStar() {
    return PKB::callsStarTable.getArea();
}
bool PKB::hasKeyCallsStar(int lineNumber) {
    return PKB::callsStarTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysCallsStar() {
    return PKB::callsStarTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesCallsStar() {
    return PKB::callsStarTable.getAllValues();
}

std::unordered_set<int> PKB::getCalledByStar(int lineNumber) {
    return PKB::callsStarTable.getThingReverse(lineNumber);
}
bool PKB::isCalledByStar(int lineNumber, int childLine) {
    return PKB::callsStarTable.isThingReverse(lineNumber, childLine);
}
bool PKB::isCalledByStar(int lineNumber, std::unordered_set<int> calledByLines) {
    return PKB::callsStarTable.isThingReverse(lineNumber, calledByLines);
}
int PKB::getSizeCalledByStar() {
    return PKB::callsStarTable.getSizeReverse();
}
int PKB::getAreaCalledByStar() {
    return PKB::callsStarTable.getArea();
}
bool PKB::hasKeyCalledByStar(int lineNumber) {
    return PKB::callsStarTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysCalledByStar() {
    return PKB::callsStarTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesCalledByStar() {
    return PKB::callsStarTable.getAllValuesReverse();
}

void PKB::insertNext(int lineNumber, std::unordered_set<int> nextLines) {
    PKB::nextTable.insertThing(lineNumber, nextLines);
}
std::unordered_set<int> PKB::getNext(int lineNumber) {
    return PKB::nextTable.getThing(lineNumber);
}
bool PKB::isNext(int lineNumber, int parentLine) {
    return PKB::nextTable.isThing(lineNumber, parentLine);
}
bool PKB::isNext(int lineNumber, std::unordered_set<int> nextLines) {
    return PKB::nextTable.isThing(lineNumber, nextLines);
}
int PKB::getSizeNext() {
    return PKB::nextTable.getSize();
}
int PKB::getAreaNext() {
    return PKB::nextTable.getArea();
}
bool PKB::hasKeyNext(int lineNumber) {
    return PKB::nextTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysNext() {
    return PKB::nextTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesNext() {
    return PKB::nextTable.getAllValues();
}

std::unordered_set<int> PKB::getPrevious(int lineNumber) {
    return PKB::nextTable.getThingReverse(lineNumber);
}
bool PKB::isPrevious(int lineNumber, int childLine) {
    return PKB::nextTable.isThingReverse(lineNumber, childLine);
}
bool PKB::isPrevious(int lineNumber, std::unordered_set<int> previousLines) {
    return PKB::nextTable.isThingReverse(lineNumber, previousLines);
}
int PKB::getSizePrevious() {
    return PKB::nextTable.getSizeReverse();
}
int PKB::getAreaPrevious() {
    return PKB::nextTable.getArea();
}
bool PKB::hasKeyPrevious(int lineNumber) {
    return PKB::nextTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysPrevious() {
    return PKB::nextTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesPrevious() {
    return PKB::nextTable.getAllValuesReverse();
}

void PKB::insertNextBip(int lineNumber, std::unordered_set<int> nextBipLines) {
    PKB::nextBipTable.insertThing(lineNumber, nextBipLines);
}
std::unordered_set<int> PKB::getNextBip(int lineNumber) {
    return PKB::nextBipTable.getThing(lineNumber);
}
bool PKB::isNextBip(int lineNumber, int nextBipLine) {
    return PKB::nextBipTable.isThing(lineNumber, nextBipLine);
}
bool PKB::isNextBip(int lineNumber, std::unordered_set<int> nextBipLines) {
    return PKB::nextBipTable.isThing(lineNumber, nextBipLines);
}
int PKB::getSizeNextBip() {
    return PKB::nextBipTable.getSize();
}
int PKB::getAreaNextBip() {
    return PKB::nextBipTable.getArea();
}
bool PKB::hasKeyNextBip(int lineNumber) {
    return PKB::nextBipTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysNextBip() {
    return PKB::nextBipTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesNextBip() {
    return PKB::nextBipTable.getAllValues();
}

std::unordered_set<int> PKB::getPreviousBip(int lineNumber) {
    return PKB::nextBipTable.getThingReverse(lineNumber);
}
bool PKB::isPreviousBip(int lineNumber, int previousBipLine) {
    return PKB::nextBipTable.isThingReverse(lineNumber, previousBipLine);
}
bool PKB::isPreviousBip(int lineNumber, std::unordered_set<int> previousBipLines) {
    return PKB::nextBipTable.isThingReverse(lineNumber, previousBipLines);
}
int PKB::getSizePreviousBip() {
    return PKB::nextBipTable.getSizeReverse();
}
int PKB::getAreaPreviousBip() {
    return PKB::nextBipTable.getArea();
}
bool PKB::hasKeyPreviousBip(int lineNumber) {
    return PKB::nextBipTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysPreviousBip() {
    return PKB::nextBipTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesPreviousBip() {
    return PKB::nextBipTable.getAllValuesReverse();
}

void PKB::insertNextBipStar(int lineNumber, std::unordered_set<int> nextBipStarLines) {
    PKB::nextBipStarTable.insertThing(lineNumber, nextBipStarLines);
}
std::unordered_set<int> PKB::getNextBipStar(int lineNumber) {
    return PKB::nextBipStarTable.getThing(lineNumber);
}
bool PKB::isNextBipStar(int lineNumber, int nextBipStarLine) {
    return PKB::nextBipStarTable.isThing(lineNumber, nextBipStarLine);
}
bool PKB::isNextBipStar(int lineNumber, std::unordered_set<int> nextBipStarLines) {
    return PKB::nextBipStarTable.isThing(lineNumber, nextBipStarLines);
}
int PKB::getSizeNextBipStar() {
    return PKB::nextBipStarTable.getSize();
}
int PKB::getAreaNextBipStar() {
    return PKB::nextBipStarTable.getArea();
}
bool PKB::hasKeyNextBipStar(int lineNumber) {
    return PKB::nextBipStarTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysNextBipStar() {
    return PKB::nextBipStarTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesNextBipStar() {
    return PKB::nextBipStarTable.getAllValues();
}

std::unordered_set<int> PKB::getPreviousBipStar(int lineNumber) {
    return PKB::nextBipStarTable.getThingReverse(lineNumber);
}
bool PKB::isPreviousBipStar(int lineNumber, int previousBipStarLine) {
    return PKB::nextBipStarTable.isThingReverse(lineNumber, previousBipStarLine);
}
bool PKB::isPreviousBipStar(int lineNumber, std::unordered_set<int> previousBipStarLines) {
    return PKB::nextBipStarTable.isThingReverse(lineNumber, previousBipStarLines);
}
int PKB::getSizePreviousBipStar() {
    return PKB::nextBipStarTable.getSizeReverse();
}
int PKB::getAreaPreviousBipStar() {
    return PKB::nextBipStarTable.getArea();
}
bool PKB::hasKeyPreviousBipStar(int lineNumber) {
    return PKB::nextBipStarTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysPreviousBipStar() {
    return PKB::nextBipStarTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesPreviousBipStar() {
    return PKB::nextBipStarTable.getAllValuesReverse();
}

void PKB::insertAffectsBip(int lineNumber, std::unordered_set<int> affectsBipLines) {
    PKB::affectsBipTable.insertThing(lineNumber, affectsBipLines);
}
std::unordered_set<int> PKB::getAffectsBip(int lineNumber) {
    return PKB::affectsBipTable.getThing(lineNumber);
}
bool PKB::isAffectsBip(int lineNumber, int affectsBipLine) {
    return PKB::affectsBipTable.isThing(lineNumber, affectsBipLine);
}
bool PKB::isAffectsBip(int lineNumber, std::unordered_set<int> affectsBipLines) {
    return PKB::affectsBipTable.isThing(lineNumber, affectsBipLines);
}
int PKB::getSizeAffectsBip() {
    return PKB::affectsBipTable.getSize();
}
int PKB::getAreaAffectsBip() {
    return PKB::affectsBipTable.getArea();
}
bool PKB::hasKeyAffectsBip(int lineNumber) {
    return PKB::affectsBipTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysAffectsBip() {
    return PKB::affectsBipTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesAffectsBip() {
    return PKB::affectsBipTable.getAllValues();
}

std::unordered_set<int> PKB::getAffectedByBip(int lineNumber) {
    return PKB::affectsBipTable.getThingReverse(lineNumber);
}
bool PKB::isAffectedByBip(int lineNumber, int previousBipLine) {
    return PKB::affectsBipTable.isThingReverse(lineNumber, previousBipLine);
}
bool PKB::isAffectedByBip(int lineNumber, std::unordered_set<int> previousBipLines) {
    return PKB::affectsBipTable.isThingReverse(lineNumber, previousBipLines);
}
int PKB::getSizeAffectedByBip() {
    return PKB::affectsBipTable.getSizeReverse();
}
int PKB::getAreaAffectedByBip() {
    return PKB::affectsBipTable.getArea();
}
bool PKB::hasKeyAffectedByBip(int lineNumber) {
    return PKB::affectsBipTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysAffectedByBip() {
    return PKB::affectsBipTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesAffectedByBip() {
    return PKB::affectsBipTable.getAllValuesReverse();
}

void PKB::insertAffectsBipStar(int lineNumber, std::unordered_set<int> affectsBipStarLines) {
    PKB::affectsBipStarTable.insertThing(lineNumber, affectsBipStarLines);
}
std::unordered_set<int> PKB::getAffectsBipStar(int lineNumber) {
    return PKB::affectsBipStarTable.getThing(lineNumber);
}
bool PKB::isAffectsBipStar(int lineNumber, int affectsBipStarLine) {
    return PKB::affectsBipStarTable.isThing(lineNumber, affectsBipStarLine);
}
bool PKB::isAffectsBipStar(int lineNumber, std::unordered_set<int> affectsBipStarLines) {
    return PKB::affectsBipStarTable.isThing(lineNumber, affectsBipStarLines);
}
int PKB::getSizeAffectsBipStar() {
    return PKB::affectsBipStarTable.getSize();
}
int PKB::getAreaAffectsBipStar() {
    return PKB::affectsBipStarTable.getArea();
}
bool PKB::hasKeyAffectsBipStar(int lineNumber) {
    return PKB::affectsBipStarTable.hasKey(lineNumber);
}
std::vector<int> PKB::getAllKeysAffectsBipStar() {
    return PKB::affectsBipStarTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesAffectsBipStar() {
    return PKB::affectsBipStarTable.getAllValues();
}

std::unordered_set<int> PKB::getAffectedByBipStar(int lineNumber) {
    return PKB::affectsBipStarTable.getThingReverse(lineNumber);
}
bool PKB::isAffectedByBipStar(int lineNumber, int previousBipStarLine) {
    return PKB::affectsBipStarTable.isThingReverse(lineNumber, previousBipStarLine);
}
bool PKB::isAffectedByBipStar(int lineNumber, std::unordered_set<int> previousBipStarLines) {
    return PKB::affectsBipStarTable.isThingReverse(lineNumber, previousBipStarLines);
}
int PKB::getSizeAffectedByBipStar() {
    return PKB::affectsBipStarTable.getSizeReverse();
}
int PKB::getAreaAffectedByBipStar() {
    return PKB::affectsBipStarTable.getArea();
}
bool PKB::hasKeyAffectedByBipStar(int lineNumber) {
    return PKB::affectsBipStarTable.hasKeyReverse(lineNumber);
}
std::vector<int> PKB::getAllKeysAffectedByBipStar() {
    return PKB::affectsBipStarTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesAffectedByBipStar() {
    return PKB::affectsBipStarTable.getAllValuesReverse();
}

void PKB::insertAffectsBipNode(int nodeNumber, std::unordered_set<int> affectsBipNodeNodes) {
    PKB::affectsBipNodeTable.insertThing(nodeNumber, affectsBipNodeNodes);
}
std::unordered_set<int> PKB::getAffectsBipNode(int nodeNumber) {
    return PKB::affectsBipNodeTable.getThing(nodeNumber);
}
bool PKB::isAffectsBipNode(int nodeNumber, int affectsBipNodeNode) {
    return PKB::affectsBipNodeTable.isThing(nodeNumber, affectsBipNodeNode);
}
bool PKB::isAffectsBipNode(int nodeNumber, std::unordered_set<int> affectsBipNodeNodes) {
    return PKB::affectsBipNodeTable.isThing(nodeNumber, affectsBipNodeNodes);
}
int PKB::getSizeAffectsBipNode() {
    return PKB::affectsBipNodeTable.getSize();
}
int PKB::getAreaAffectsBipNode() {
    return PKB::affectsBipNodeTable.getArea();
}
bool PKB::hasKeyAffectsBipNode(int nodeNumber) {
    return PKB::affectsBipNodeTable.hasKey(nodeNumber);
}
std::vector<int> PKB::getAllKeysAffectsBipNode() {
    return PKB::affectsBipNodeTable.getAllKeys();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesAffectsBipNode() {
    return PKB::affectsBipNodeTable.getAllValues();
}

std::unordered_set<int> PKB::getAffectedByBipNode(int nodeNumber) {
    return PKB::affectsBipNodeTable.getThingReverse(nodeNumber);
}
bool PKB::isAffectedByBipNode(int nodeNumber, int affectedByBipNodeNode) {
    return PKB::affectsBipNodeTable.isThingReverse(nodeNumber, affectedByBipNodeNode);
}
bool PKB::isAffectedByBipNode(int nodeNumber, std::unordered_set<int> affectedByBipNodeNodes) {
    return PKB::affectsBipNodeTable.isThingReverse(nodeNumber, affectedByBipNodeNodes);
}
int PKB::getSizeAffectedByBipNode() {
    return PKB::affectsBipNodeTable.getSizeReverse();
}
int PKB::getAreaAffectedByBipNode() {
    return PKB::affectsBipNodeTable.getArea();
}
bool PKB::hasKeyAffectedByBipNode(int nodeNumber) {
    return PKB::affectsBipNodeTable.hasKeyReverse(nodeNumber);
}
std::vector<int> PKB::getAllKeysAffectedByBipNode() {
    return PKB::affectsBipNodeTable.getAllKeysReverse();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesAffectedByBipNode() {
    return PKB::affectsBipNodeTable.getAllValuesReverse();
}
