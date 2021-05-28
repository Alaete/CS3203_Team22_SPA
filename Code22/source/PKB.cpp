#include "PKB.h"

PKB::PKB() {}
PKB::~PKB() {}

void PKB::clearAll() {
    procedureTable.clearAll();
    statementTable.clearAll();
    statementListTable.clearAll();
    procedureStatementListTable.clearAll();
    readTable.clearAll();
    printTable.clearAll();
    assignTable.clearAll();
    assignTableNonShunted.clearAll();
    callTable.clearAll();
    whileTable.clearAll();
    ifTable.clearAll();
    variableTable.clearAll();
    constantTable.clearAll();

    followsTable.clearAll();
    followsStarTable.clearAll();
    parentTable.clearAll();
    parentStarTable.clearAll();
    usesTable.clearAll();
    modifiesTable.clearAll();
    procedureUsesTable.clearAll();
    procedureModifiesTable.clearAll();
}

void PKB::insertProcedure(std::string procName)
{
    PKB::procedureTable.insertProcedure(procName);
}
std::string PKB::getProcedure(int procIndex)
{
    return PKB::procedureTable.getProcedure(procIndex);
}
int PKB::getSizeProcedure()
{
    return PKB::procedureTable.getSizeProcedure();
}
bool PKB::hasKeyProcedure(int procIndex)
{
    return PKB::procedureTable.hasKeyProcedure(procIndex);
}
std::vector<int> PKB::getAllKeysProcedure()
{
    return PKB::procedureTable.getAllKeysProcedure();
}
std::vector<std::string> PKB::getAllValuesProcedure()
{
    return PKB::procedureTable.getAllValuesProcedure();
}

void PKB::insertStatementList(int lineNumber, std::unordered_set<int> statementLines) {
    PKB::statementListTable.insertStatementList(lineNumber, statementLines);
}
std::unordered_set<int> PKB::getStatementList(int lineNumber) {
    return PKB::statementListTable.getStatementList(lineNumber);
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

void PKB::insertRead(int lineNumber, std::string varName)
{
    PKB::readTable.insertRead(lineNumber, varName);
}
std::string PKB::getRead(int lineNumber)
{
    return PKB::readTable.getRead(lineNumber);
}
std::unordered_set<int> PKB::getReadKeys(std::string varName)
{
    return PKB::readTable.getReadKeys(varName);
}
int PKB::getSizeRead()
{
    return PKB::readTable.getSizeRead();
}
bool PKB::hasKeyRead(int lineNumber)
{
    return PKB::readTable.hasKeyRead(lineNumber);
}
std::vector<int> PKB::getAllKeysRead()
{
    return PKB::readTable.getAllKeysRead();
}
std::vector<std::string> PKB::getAllValuesRead()
{
    return PKB::readTable.getAllValuesRead();
}

void PKB::insertPrint(int lineNumber, std::string varName)
{
    PKB::printTable.insertPrint(lineNumber, varName);
}
std::string PKB::getPrint(int lineNumber)
{
    return PKB::printTable.getPrint(lineNumber);
}
std::unordered_set<int> PKB::getPrintKeys(std::string varName)
{
    return PKB::printTable.getPrintKeys(varName);
}
int PKB::getSizePrint()
{
    return PKB::printTable.getSizePrint();
}
bool PKB::hasKeyPrint(int lineNumber)
{
    return PKB::printTable.hasKeyPrint(lineNumber);
}
std::vector<int> PKB::getAllKeysPrint()
{
    return PKB::printTable.getAllKeysPrint();
}
std::vector<std::string> PKB::getAllValuesPrint()
{
    return PKB::printTable.getAllValuesPrint();
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

void PKB::insertAssignNonShunted(int lineNumber, std::string assignStmt)
{
    PKB::assignTableNonShunted.insertAssign(lineNumber, assignStmt);
}
std::string PKB::getAssignNonShunted(int lineNumber)
{
    return PKB::assignTableNonShunted.getAssign(lineNumber);
}
int PKB::getSizeAssignNonShunted()
{
    return PKB::assignTableNonShunted.getSizeAssign();
}
bool PKB::hasKeyAssignNonShunted(int lineNumber)
{
    return PKB::assignTableNonShunted.hasKeyAssign(lineNumber);
}
std::vector<int> PKB::getAllKeysAssignNonShunted()
{
    return PKB::assignTableNonShunted.getAllKeysAssign();
}
std::vector<std::string> PKB::getAllValuesAssignNonShunted()
{
    return PKB::assignTableNonShunted.getAllValuesAssign();
}

void PKB::insertCall(int lineNumber, std::string procName)
{
    PKB::callTable.insertCall(lineNumber, procName);
}
std::string PKB::getCall(int lineNumber)
{
    return PKB::callTable.getCall(lineNumber);
}
std::unordered_set<int> PKB::getCallKeys(std::string procName)
{
    return PKB::callTable.getCallKeys(procName);
}
int PKB::getSizeCall()
{
    return PKB::callTable.getSizeCall();
}
bool PKB::hasKeyCall(int lineNumber)
{
    return PKB::callTable.hasKeyCall(lineNumber);
}
std::vector<int> PKB::getAllKeysCall()
{
    return PKB::callTable.getAllKeysCall();
}
std::vector<std::string> PKB::getAllValuesCall()
{
    return PKB::callTable.getAllValuesCall();
}

void PKB::insertWhile(int lineNumber, std::string condition)
{
    PKB::whileTable.insertWhile(lineNumber, condition);
}
std::string PKB::getWhile(int lineNumber)
{
    return PKB::whileTable.getWhile(lineNumber);
}
std::unordered_set<int> PKB::getWhileKeys(std::string condition)
{
    return PKB::whileTable.getWhileKeys(condition);
}
int PKB::getSizeWhile()
{
    return PKB::whileTable.getSizeWhile();
}
bool PKB::hasKeyWhile(int lineNumber)
{
    return PKB::whileTable.hasKeyWhile(lineNumber);
}
std::vector<int> PKB::getAllKeysWhile()
{
    return PKB::whileTable.getAllKeysWhile();
}
std::vector<std::string> PKB::getAllValuesWhile()
{
    return PKB::whileTable.getAllValuesWhile();
}

void PKB::insertIf(int lineNumber, std::string condition)
{
    PKB::ifTable.insertIf(lineNumber, condition);
}
std::string PKB::getIf(int lineNumber)
{
    return PKB::ifTable.getIf(lineNumber);
}
std::unordered_set<int> PKB::getIfKeys(std::string condition)
{
    return PKB::ifTable.getIfKeys(condition);
}
int PKB::getSizeIf()
{
    return PKB::ifTable.getSizeIf();
}
bool PKB::hasKeyIf(int lineNumber)
{
    return PKB::ifTable.hasKeyIf(lineNumber);
}
std::vector<int> PKB::getAllKeysIf()
{
    return PKB::ifTable.getAllKeysIf();
}
std::vector<std::string> PKB::getAllValuesIf()
{
    return PKB::ifTable.getAllValuesIf();
}

void PKB::insertIfWhile(int lineNumber, std::string condition)
{
    if (ifTable.hasKeyIf(lineNumber)) {
        PKB::insertIf(lineNumber, condition);
    }
    else if (whileTable.hasKeyWhile(lineNumber)){
        PKB::insertWhile(lineNumber, condition);
    }
    else {
        throw PKB_Util::noIfWhileEntryError(lineNumber);
    }
}

int PKB::insertVariable(std::string varName)
{
    return PKB::variableTable.insertVariable(varName);
}
std::string PKB::getVariable(int index)
{
    return PKB::variableTable.getVariable(index);
}
int PKB::getVariableKey(std::string varName)
{
    return PKB::variableTable.getVariableKey(varName);
}
int PKB::getSizeVariable()
{
    return PKB::variableTable.getSizeVariable();
}
bool PKB::hasKeyVariable(int index)
{
    return PKB::variableTable.hasKeyVariable(index);
}
std::vector<int> PKB::getAllKeysVariable()
{
    return PKB::variableTable.getAllKeysVariable();
}
std::vector<std::string> PKB::getAllValuesVariable()
{
    return PKB::variableTable.getAllValuesVariable();
}

void PKB::insertConstant(int lineNumber, std::unordered_set<int> constantValues)
{
    PKB::constantTable.insertConstant(lineNumber, constantValues);
}
std::unordered_set<int> PKB::getConstant(int lineNumber)
{
    return PKB::constantTable.getConstant(lineNumber);
}
bool PKB::isConstant(int lineNumber, std::unordered_set<int> constantValues)
{
    return PKB::constantTable.isConstant(lineNumber, constantValues);
}
bool PKB::isConstant(int lineNumber, int constantValue)
{
    return PKB::constantTable.isConstant(lineNumber, constantValue);
}
int PKB::getSizeConstant()
{
    return PKB::constantTable.getSizeConstant();
}
bool PKB::hasKeyConstant(int lineNumber)
{
    return PKB::constantTable.hasKeyConstant(lineNumber);
}
std::vector<int> PKB::getAllKeysConstant()
{
    return PKB::constantTable.getAllKeysConstant();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesConstant()
{
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
    PKB::followsStarTable.insertFollowsStar(lineNumber, leaderLines);
}
std::unordered_set<int> PKB::getFollowsStar(int lineNumber) {
    return PKB::followsStarTable.getFollowsStar(lineNumber);
}
bool PKB::isFollowsStar(int lineNumber, int leaderLine) {
    return PKB::followsStarTable.isFollowsStar(lineNumber, leaderLine);
}
bool PKB::isFollowsStar(int lineNumber, std::unordered_set<int> leaderLines) {
    return PKB::followsStarTable.isFollowsStar(lineNumber, leaderLines);
}
int PKB::getSizeFollowsStar() {
    return PKB::followsStarTable.getSizeFollowsStar();
}
bool PKB::hasKeyFollowsStar(int lineNumber) {
    return PKB::followsStarTable.hasKeyFollowsStar(lineNumber);
}
std::vector<int> PKB::getAllKeysFollowsStar() {
    return PKB::followsStarTable.getAllKeysFollowsStar();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesFollowsStar() {
    return PKB::followsStarTable.getAllValuesFollowsStar();
}

std::unordered_set<int> PKB::getFollowedByStar(int lineNumber) {
    return PKB::followsStarTable.getFollowedByStar(lineNumber);
}
bool PKB::isFollowedByStar(int lineNumber, int followerLine) {
    return PKB::followsStarTable.isFollowedByStar(lineNumber, followerLine);
}
bool PKB::isFollowedByStar(int lineNumber, std::unordered_set<int> followerLines) {
    return PKB::followsStarTable.isFollowedByStar(lineNumber, followerLines);
}
int PKB::getSizeFollowedByStar() {
    return PKB::followsStarTable.getSizeFollowedByStar();
}
bool PKB::hasKeyFollowedByStar(int lineNumber) {
    return PKB::followsStarTable.hasKeyFollowedByStar(lineNumber);
}
std::vector<int> PKB::getAllKeysFollowedByStar() {
    return PKB::followsStarTable.getAllKeysFollowedByStar();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesFollowedByStar() {
    return PKB::followsStarTable.getAllValuesFollowedByStar();
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
    PKB::parentStarTable.insertParentStar(lineNumber, parentLines);
}
std::unordered_set<int> PKB::getParentStar(int lineNumber) {
    return PKB::parentStarTable.getParentStar(lineNumber);
}
bool PKB::isParentStar(int lineNumber, int parentLine) {
    return PKB::parentStarTable.isParentStar(lineNumber, parentLine);
}
bool PKB::isParentStar(int lineNumber, std::unordered_set<int> parentLines) {
    return PKB::parentStarTable.isParentStar(lineNumber, parentLines);
}
int PKB::getSizeParentStar() {
    return PKB::parentStarTable.getSizeParentStar();
}
bool PKB::hasKeyParentStar(int lineNumber) {
    return PKB::parentStarTable.hasKeyParentStar(lineNumber);
}
std::vector<int> PKB::getAllKeysParentStar() {
    return PKB::parentStarTable.getAllKeysParentStar();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesParentStar() {
    return PKB::parentStarTable.getAllValuesParentStar();
}

std::unordered_set<int> PKB::getChildStar(int lineNumber) {
    return PKB::parentStarTable.getChildStar(lineNumber);
}
bool PKB::isChildStar(int lineNumber, int childLine) {
    return PKB::parentStarTable.isChildStar(lineNumber, childLine);
}
bool PKB::isChildStar(int lineNumber, std::unordered_set<int> childLines) {
    return PKB::parentStarTable.isChildStar(lineNumber, childLines);
}
int PKB::getSizeChildStar() {
    return PKB::parentStarTable.getSizeChildStar();
}
bool PKB::hasKeyChildStar(int lineNumber) {
    return PKB::parentStarTable.hasKeyChildStar(lineNumber);
}
std::vector<int> PKB::getAllKeysChildStar() {
    return PKB::parentStarTable.getAllKeysChildStar();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesChildStar() {
    return PKB::parentStarTable.getAllValuesChildStar();
}

void PKB::insertUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    PKB::usesTable.insertUses(lineNumber, usedNames);
}
std::unordered_set<std::string> PKB::getUses(int lineNumber) {
    return PKB::usesTable.getUses(lineNumber);
}
bool PKB::isUses(int lineNumber, std::string usedName) {
    return PKB::usesTable.isUses(lineNumber, usedName);
}
bool PKB::isUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    return PKB::usesTable.isUses(lineNumber, usedNames);
}
int PKB::getSizeUses() {
    return PKB::usesTable.getSizeUses();
}
bool PKB::hasKeyUses(int lineNumber) {
    return PKB::usesTable.hasKeyUses(lineNumber);
}
std::vector<int> PKB::getAllKeysUses() {
    return PKB::usesTable.getAllKeysUses();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesUses() {
    return PKB::usesTable.getAllValuesUses();
}

std::unordered_set<int> PKB::getUsedBy(std::string name) {
    return PKB::usesTable.getUsedBy(name);
}
bool PKB::isUsedBy(std::string name, int usedByLine) {
    return PKB::usesTable.isUsedBy(name, usedByLine);
}
bool PKB::isUsedBy(std::string name, std::unordered_set<int> usedByLines) {
    return PKB::usesTable.isUsedBy(name, usedByLines);
}
int PKB::getSizeUsedBy() {
    return PKB::usesTable.getSizeUsedBy();
}
bool PKB::hasKeyUsedBy(std::string name) {
    return PKB::usesTable.hasKeyUsedBy(name);
}
std::vector<std::string> PKB::getAllKeysUsedBy() {
    return PKB::usesTable.getAllKeysUsedBy();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesUsedBy() {
    return PKB::usesTable.getAllValuesUsedBy();
}

void PKB::insertModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
    PKB::modifiesTable.insertModifies(lineNumber, modifiedNames);
}
std::unordered_set<std::string> PKB::getModifies(int lineNumber) {
    return PKB::modifiesTable.getModifies(lineNumber);
}
bool PKB::isModifies(int lineNumber, std::string modifiedName) {
    return PKB::modifiesTable.isModifies(lineNumber, modifiedName);
}
bool PKB::isModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
    return PKB::modifiesTable.isModifies(lineNumber, modifiedNames);
}
int PKB::getSizeModifies() {
    return PKB::modifiesTable.getSizeModifies();
}
bool PKB::hasKeyModifies(int lineNumber) {
    return PKB::modifiesTable.hasKeyModifies(lineNumber);
}
std::vector<int> PKB::getAllKeysModifies() {
    return PKB::modifiesTable.getAllKeysModifies();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesModifies() {
    return PKB::modifiesTable.getAllValuesModifies();
}

std::unordered_set<int> PKB::getModifiedBy(std::string name) {
    return PKB::modifiesTable.getModifiedBy(name);
}
bool PKB::isModifiedBy(std::string name, int modifiedByLine) {
    return PKB::modifiesTable.isModifiedBy(name, modifiedByLine);
}
bool PKB::isModifiedBy(std::string name, std::unordered_set<int> modifiedByLines) {
    return PKB::modifiesTable.isModifiedBy(name, modifiedByLines);
}
int PKB::getSizeModifiedBy() {
    return PKB::modifiesTable.getSizeModifiedBy();
}
bool PKB::hasKeyModifiedBy(std::string name) {
    return PKB::modifiesTable.hasKeyModifiedBy(name);
}
std::vector<std::string> PKB::getAllKeysModifiedBy() {
    return PKB::modifiesTable.getAllKeysModifiedBy();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesModifiedBy() {
    return PKB::modifiesTable.getAllValuesModifiedBy();
}

void PKB::insertProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    PKB::procedureUsesTable.insertUses(lineNumber, usedNames);
}
std::unordered_set<std::string> PKB::getProcedureUses(int lineNumber) {
    return PKB::procedureUsesTable.getUses(lineNumber);
}
bool PKB::isProcedureUses(int lineNumber, std::string usedName) {
    return PKB::procedureUsesTable.isUses(lineNumber, usedName);
}
bool PKB::isProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames) {
    return PKB::procedureUsesTable.isUses(lineNumber, usedNames);
}
int PKB::getSizeProcedureUses() {
    return PKB::procedureUsesTable.getSizeUses();
}
bool PKB::hasKeyProcedureUses(int lineNumber) {
    return PKB::procedureUsesTable.hasKeyUses(lineNumber);
}
std::vector<int> PKB::getAllKeysProcedureUses() {
    return PKB::procedureUsesTable.getAllKeysUses();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesProcedureUses() {
    return PKB::procedureUsesTable.getAllValuesUses();
}

std::unordered_set<int> PKB::getProcedureUsedBy(std::string name) {
    return PKB::procedureUsesTable.getUsedBy(name);
}
bool PKB::isProcedureUsedBy(std::string name, int usedByLine) {
    return PKB::procedureUsesTable.isUsedBy(name, usedByLine);
}
bool PKB::isProcedureUsedBy(std::string name, std::unordered_set<int> usedByLines) {
    return PKB::procedureUsesTable.isUsedBy(name, usedByLines);
}
int PKB::getSizeProcedureUsedBy() {
    return PKB::procedureUsesTable.getSizeUsedBy();
}
bool PKB::hasKeyProcedureUsedBy(std::string name) {
    return PKB::procedureUsesTable.hasKeyUsedBy(name);
}
std::vector<std::string> PKB::getAllKeysProcedureUsedBy() {
    return PKB::procedureUsesTable.getAllKeysUsedBy();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesProcedureUsedBy() {
    return PKB::procedureUsesTable.getAllValuesUsedBy();
}

void PKB::insertProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
    PKB::procedureModifiesTable.insertModifies(lineNumber, modifiedNames);
}
std::unordered_set<std::string> PKB::getProcedureModifies(int lineNumber) {
    return PKB::procedureModifiesTable.getModifies(lineNumber);
}
bool PKB::isProcedureModifies(int lineNumber, std::string modifiedName) {
    return PKB::procedureModifiesTable.isModifies(lineNumber, modifiedName);
}
bool PKB::isProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
    return PKB::procedureModifiesTable.isModifies(lineNumber, modifiedNames);
}
int PKB::getSizeProcedureModifies() {
    return PKB::procedureModifiesTable.getSizeModifies();
}
bool PKB::hasKeyProcedureModifies(int lineNumber) {
    return PKB::procedureModifiesTable.hasKeyModifies(lineNumber);
}
std::vector<int> PKB::getAllKeysProcedureModifies() {
    return PKB::procedureModifiesTable.getAllKeysModifies();
}
std::vector<std::unordered_set<std::string>> PKB::getAllValuesProcedureModifies() {
    return PKB::procedureModifiesTable.getAllValuesModifies();
}

std::unordered_set<int> PKB::getProcedureModifiedBy(std::string name) {
    return PKB::procedureModifiesTable.getModifiedBy(name);
}
bool PKB::isProcedureModifiedBy(std::string name, int modifiedByLine) {
    return PKB::procedureModifiesTable.isModifiedBy(name, modifiedByLine);
}
bool PKB::isProcedureModifiedBy(std::string name, std::unordered_set<int> modifiedByLines) {
    return PKB::procedureModifiesTable.isModifiedBy(name, modifiedByLines);
}
int PKB::getSizeProcedureModifiedBy() {
    return PKB::procedureModifiesTable.getSizeModifiedBy();
}
bool PKB::hasKeyProcedureModifiedBy(std::string name) {
    return PKB::procedureModifiesTable.hasKeyModifiedBy(name);
}
std::vector<std::string> PKB::getAllKeysProcedureModifiedBy() {
    return PKB::procedureModifiesTable.getAllKeysModifiedBy();
}
std::vector<std::unordered_set<int>> PKB::getAllValuesProcedureModifiedBy() {
    return PKB::procedureModifiesTable.getAllValuesModifiedBy();
}

void PKB::insertStatement(int lineNumber, std::string statementType)
{
    PKB::statementTable.insertStatement(lineNumber, statementType);
}

std::string PKB::getStatement(int lineNumber)
{
    return PKB::statementTable.getStatement(lineNumber);
}

bool PKB::isStatementType(int lineNumber, std::string statementType)
{
    return PKB::statementTable.isStatementType(lineNumber, statementType);
}

std::unordered_set<int> PKB::getStatementKeys(std::string statementType)
{
    return PKB::statementTable.getStatementKeys(statementType);
}

int PKB::getSizeStatement()
{
    return PKB::statementTable.getSizeStatement();
}

bool PKB::hasKeyStatement(int lineNumber)
{
    return PKB::statementTable.hasKeyStatement(lineNumber);
}

std::vector<int> PKB::getAllKeysStatement()
{
    return PKB::statementTable.getAllKeysStatement();
}

std::vector<std::string> PKB::getAllValuesStatement()
{
    return PKB::statementTable.getAllValuesStatement();
}
