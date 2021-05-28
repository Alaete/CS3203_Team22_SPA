#include "stdafx.h"
#include "SimulatedPKB.h"

SimulatedPKB::SimulatedPKB() {};
SimulatedPKB::~SimulatedPKB() {};

void SimulatedPKB::insertFollows(int lineNumber, int leaderLine) {
	SimulatedPKB::followsTable.insertFollows(lineNumber, leaderLine);
}

std::vector<int> SimulatedPKB::getAllKeysFollows() {
	return SimulatedPKB::followsTable.getAllKeysFollows();
}

int SimulatedPKB::getFollows(int lineNumber) {
	return SimulatedPKB::followsTable.getFollows(lineNumber);
}

int SimulatedPKB::getFollowedBy(int lineNumber) {
	return SimulatedPKB::followsTable.getFollowedBy(lineNumber);
}

void SimulatedPKB::insertFollowsStar(int lineNumber, std::unordered_set<int> leaderLines) {
	SimulatedPKB::followsStarTable.insertFollowsStar(lineNumber, leaderLines);
}
bool SimulatedPKB::isFollowsStar(int lineNumber, int leaderLine) {
	return SimulatedPKB::followsStarTable.isFollowsStar(lineNumber, leaderLine);
}
bool SimulatedPKB::isFollows(int lineNumber, int leaderLine) {
	return SimulatedPKB::followsTable.isFollows(lineNumber, leaderLine);
}

void SimulatedPKB::insertParent(int lineNumber, int leaderLine) {
	SimulatedPKB::parentTable.insertParent(lineNumber, leaderLine);
}
std::vector<int> SimulatedPKB::getAllKeysParent() {
	return SimulatedPKB::parentTable.getAllKeysParent();
}

int SimulatedPKB::getParent(int lineNumber) {
	return SimulatedPKB::parentTable.getParent(lineNumber);
}

std::unordered_set<int> SimulatedPKB::getChild(int lineNumber) {
	return SimulatedPKB::parentTable.getChild(lineNumber);
}


void SimulatedPKB::insertParentStar(int lineNumber, std::unordered_set<int> leaderLines) {
	SimulatedPKB::parentStarTable.insertParentStar(lineNumber, leaderLines);
}
bool SimulatedPKB::isParentStar(int lineNumber, int leaderLine) {
	return SimulatedPKB::parentStarTable.isParentStar(lineNumber, leaderLine);
}

std::unordered_set<int> SimulatedPKB::getChildStar(int lineNumber) {
	return  SimulatedPKB::parentStarTable.getChildStar(lineNumber);
}

void SimulatedPKB::insertAssignLHS(int lineNumber, std::string variableLHS) {
	SimulatedPKB::assignTable.insertAssignLHS(lineNumber, variableLHS);
}
void SimulatedPKB::insertAssignRHS(int lineNumber, std::string shuntedRHS) {
	SimulatedPKB::assignTable.insertAssignRHS(lineNumber, shuntedRHS);
}
std::pair<std::string, std::string> SimulatedPKB::getAssign(int lineNumber) {
	return SimulatedPKB::assignTable.getAssign(lineNumber);
}
std::vector<int> SimulatedPKB::getAllKeysAssign() {
	return SimulatedPKB::assignTable.getAllKeysAssign();
}

bool SimulatedPKB::hasKeyAssign(int lineNumber) {
	return SimulatedPKB::assignTable.hasKeyAssign(lineNumber);
}

void SimulatedPKB::insertPrint(int lineNumber, std::string varName) {
	SimulatedPKB::printTable.insertPrint(lineNumber, varName);
}
std::vector<int> SimulatedPKB::getAllKeysPrint() {
	return SimulatedPKB::printTable.getAllKeysPrint();
}
std::string SimulatedPKB::getPrint(int lineNumber) {
	return SimulatedPKB::printTable.getPrint(lineNumber);
}

bool SimulatedPKB::hasKeyPrint(int lineNumber) {
	return SimulatedPKB::printTable.hasKeyPrint(lineNumber);
}

void SimulatedPKB::insertRead(int lineNumber, std::string readVar) {
	SimulatedPKB::readTable.insertRead(lineNumber, readVar);
}
std::vector<int> SimulatedPKB::getAllKeysRead() {
	return SimulatedPKB::readTable.getAllKeysRead();
}
std::string SimulatedPKB::getRead(int lineNumber) {
	return SimulatedPKB::readTable.getRead(lineNumber);
}
bool SimulatedPKB::hasKeyRead(int lineNumber) {
	return SimulatedPKB::readTable.hasKeyRead(lineNumber);
}

void SimulatedPKB::insertCall(int lineNumber, std::string procName) {
	SimulatedPKB::callTable.insertCall(lineNumber, procName);
}
std::vector<int> SimulatedPKB::getAllKeysCall() {
	return SimulatedPKB::callTable.getAllKeysCall();
}
std::string SimulatedPKB::getCall(int lineNumber) {
	return SimulatedPKB::callTable.getCall(lineNumber);
}

bool SimulatedPKB::hasKeyCall(int lineNumber) {
	return SimulatedPKB::callTable.hasKeyCall(lineNumber);
}

void SimulatedPKB::insertIf(int lineNumber, std::unordered_set<std::string> condition) {
	SimulatedPKB::ifTable.insertIf(lineNumber, condition);
}
std::vector<int> SimulatedPKB::getAllKeysIf() {
	return SimulatedPKB::ifTable.getAllKeysIf();
}
std::unordered_set<std::string> SimulatedPKB::getIf(int lineNumber) {
	return SimulatedPKB::ifTable.getIf(lineNumber);
}
bool SimulatedPKB::hasKeyIf(int lineNumber) {
	return SimulatedPKB::ifTable.hasKeyIf(lineNumber);
}

void SimulatedPKB::insertWhile(int lineNumber, std::unordered_set<std::string> condition) {
	SimulatedPKB::whileTable.insertWhile(lineNumber, condition);
}
std::vector<int> SimulatedPKB::getAllKeysWhile() {
	return SimulatedPKB::whileTable.getAllKeysWhile();
}
std::unordered_set<std::string> SimulatedPKB::getWhile(int lineNumber) {
	return SimulatedPKB::whileTable.getWhile(lineNumber);
}
bool SimulatedPKB::hasKeyWhile(int lineNumber) {
	return SimulatedPKB::whileTable.hasKeyWhile(lineNumber);
}


void SimulatedPKB::insertUses(int lineNumber, std::unordered_set<std::string> usedNames) {
	SimulatedPKB::usesTable.insertUses(lineNumber, usedNames);
}
std::vector<int> SimulatedPKB::getAllKeysUses() {
	return SimulatedPKB::usesTable.getAllKeysUses();

}
std::unordered_set<std::string> SimulatedPKB::getUses(int lineNumber) {
	return SimulatedPKB::usesTable.getUses(lineNumber);

}
bool SimulatedPKB::hasKeyUses(int lineNumber) {
	return SimulatedPKB::usesTable.hasKeyUses(lineNumber);
}

void SimulatedPKB::insertModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
	SimulatedPKB::modifiesTable.insertModifies(lineNumber, modifiedNames);
}
std::vector<int> SimulatedPKB::getAllKeysModifies() {
	return SimulatedPKB::modifiesTable.getAllKeysModifies();
}
std::unordered_set<std::string> SimulatedPKB::getModifies(int lineNumber) {
	return SimulatedPKB::modifiesTable.getModifies(lineNumber);
}
bool SimulatedPKB::hasKeyModifies(int lineNumber) {
	return SimulatedPKB::modifiesTable.hasKeyModifies(lineNumber);
}
std::unordered_set<int> SimulatedPKB::getModifiedBy(std::string name) {
	return SimulatedPKB::modifiesTable.getModifiedBy(name);
}


void SimulatedPKB::insertProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames) {
	SimulatedPKB::procedureUsesTable.insertUses(lineNumber, usedNames);
}

void SimulatedPKB::insertProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
	SimulatedPKB::procedureModifiesTable.insertModifies(lineNumber, modifiedNames);
}

std::unordered_set<std::string> SimulatedPKB::getProcedureModifies(int lineNumber) {
	return SimulatedPKB::procedureModifiesTable.getModifies(lineNumber);
}

std::unordered_set<std::string> SimulatedPKB::getProcedureUses(int lineNumber) {
	return SimulatedPKB::procedureUsesTable.getUses(lineNumber);
}

void SimulatedPKB::insertNext(int lineNumber, std::unordered_set<int> nextLines) {
	SimulatedPKB::nextTable.insertNext(lineNumber, nextLines);
}

bool SimulatedPKB::isNext(int lineNumber, int nextLine) {
	return SimulatedPKB::nextTable.isNext(lineNumber, nextLine);
}


std::vector<int> SimulatedPKB::getAllKeysNext() {
	return SimulatedPKB::nextTable.getAllKeysNext();
}

std::unordered_set<int> SimulatedPKB::getNext(int lineNumber) {
	return SimulatedPKB::nextTable.getNext(lineNumber);
}

std::unordered_set<int> SimulatedPKB::getPrevious(int lineNumber) {
	return SimulatedPKB::nextTable.getPrevious(lineNumber);
}

void SimulatedPKB::insertStatement(int lineNumber, std::string statementType) {
	SimulatedPKB::statementTable.insertStatement(lineNumber, statementType);
}

std::vector<int> SimulatedPKB::getAllKeysStatement() {
	return SimulatedPKB::statementTable.getAllKeysStatement();
}

std::string SimulatedPKB::getStatement(int lineNumber) {
	return SimulatedPKB::statementTable.getStatement(lineNumber);
}
int SimulatedPKB::getSizeStatement() {
	return SimulatedPKB::statementTable.getSizeStatement();
}


int SimulatedPKB::insertProcedure(std::string procName) {
	return SimulatedPKB::procedureTable.insertProcedure(procName);
}
std::vector<int> SimulatedPKB::getAllKeysProcedure() {
	return SimulatedPKB::procedureTable.getAllKeysProcedure();
}
int SimulatedPKB::getKeyProcedure(std::string procName) {
	return SimulatedPKB::procedureTable.getKeyProcedure(procName);
}


std::unordered_set<int> SimulatedPKB::getProcedureStatementList(int procIndex) {
	return SimulatedPKB::procedureStatementListTable.getProcedureStatementList(procIndex);
}
void SimulatedPKB::insertProcedureStatementList(int procIndex, std::unordered_set<int> statementLines) {
	return SimulatedPKB::procedureStatementListTable.insertProcedureStatementList(procIndex, statementLines);
}

std::unordered_set<int> SimulatedPKB::getStatementList(int index) {
	return SimulatedPKB::statementListTable.getStatementList(index);
}
void SimulatedPKB::insertStatementList(int index, std::unordered_set<int> statementLines) {
	return SimulatedPKB::statementListTable.insertStatementList(index, statementLines);
}

void SimulatedPKB::insertNextBip(int lineNumber, std::unordered_set<int> nextBipLines) {
	SimulatedPKB::nextBipTable.insertNextBip(lineNumber, nextBipLines);
}

bool SimulatedPKB::isNextBip(int lineNumber, int nextBipLine) {
	return SimulatedPKB::nextBipTable.isNextBip(lineNumber, nextBipLine);
}

std::vector<int> SimulatedPKB::getAllKeysNextBip() {
	return SimulatedPKB::nextBipTable.getAllKeysNextBip();
}

std::unordered_set<int> SimulatedPKB::getNextBip(int lineNumber) {
	return SimulatedPKB::nextBipTable.getNextBip(lineNumber);
}

std::unordered_set<int> SimulatedPKB::getPreviousBip(int lineNumber) {
	return SimulatedPKB::nextBipTable.getPreviousBip(lineNumber);
}

void SimulatedPKB::insertNextBipStar(int lineNumber, std::unordered_set<int> nextBipStarLines) {
	SimulatedPKB::nextBipStarTable.insertNextBipStar(lineNumber, nextBipStarLines);
}

bool SimulatedPKB::isNextBipStar(int lineNumber, int nextBipStarLine) {
	return SimulatedPKB::nextBipStarTable.isNextBipStar(lineNumber, nextBipStarLine);
}

std::vector<int> SimulatedPKB::getAllKeysNextBipStar() {
	return SimulatedPKB::nextBipStarTable.getAllKeysNextBipStar();
}

std::unordered_set<int> SimulatedPKB::getNextBipStar(int lineNumber) {
	return SimulatedPKB::nextBipStarTable.getNextBipStar(lineNumber);
}

std::unordered_set<int> SimulatedPKB::getPreviousBipStar(int lineNumber) {
	return SimulatedPKB::nextBipStarTable.getPreviousBipStar(lineNumber);
}

void SimulatedPKB::insertAffectsBip(int lineNumber, std::unordered_set<int> affectsBipLines) {
	SimulatedPKB::affectsBipTable.insertAffectsBip(lineNumber, affectsBipLines);
}

bool SimulatedPKB::isAffectsBip(int lineNumber, int affectsBipLine) {
	return SimulatedPKB::affectsBipTable.isAffectsBip(lineNumber, affectsBipLine);
}

std::vector<int> SimulatedPKB::getAllKeysAffectsBip() {
	return SimulatedPKB::affectsBipTable.getAllKeysAffectsBip();
}

std::unordered_set<int> SimulatedPKB::getAffectsBip(int lineNumber) {
	return SimulatedPKB::affectsBipTable.getAffectsBip(lineNumber);
}

std::unordered_set<int> SimulatedPKB::getAffectedByBip(int lineNumber) {
	return SimulatedPKB::affectsBipTable.getAffectedByBip(lineNumber);
}

void SimulatedPKB::insertAffectsBipStar(int lineNumber, std::unordered_set<int> affectsBipStarLines) {
	SimulatedPKB::affectsBipStarTable.insertAffectsBipStar(lineNumber, affectsBipStarLines);
}

bool SimulatedPKB::isAffectsBipStar(int lineNumber, int affectsBipStarLine) {
	return SimulatedPKB::affectsBipStarTable.isAffectsBipStar(lineNumber, affectsBipStarLine);
}

std::vector<int> SimulatedPKB::getAllKeysAffectsBipStar() {
	return SimulatedPKB::affectsBipStarTable.getAllKeysAffectsBipStar();
}

std::unordered_set<int> SimulatedPKB::getAffectsBipStar(int lineNumber) {
	return SimulatedPKB::affectsBipStarTable.getAffectsBipStar(lineNumber);
}

std::unordered_set<int> SimulatedPKB::getAffectedByBipStar(int lineNumber) {
	return SimulatedPKB::affectsBipStarTable.getAffectedByBipStar(lineNumber);
}

void SimulatedPKB::insertAffectsBipNode(int nodeNumber, std::unordered_set<int> affectsBipNodeNodes) {
	SimulatedPKB::affectsBipNodeTable.insertAffectsBipNode(nodeNumber, affectsBipNodeNodes);
}

bool SimulatedPKB::isAffectsBipNode(int nodeNumber, int affectsBipNodeNode) {
	return SimulatedPKB::affectsBipNodeTable.isAffectsBipNode(nodeNumber, affectsBipNodeNode);
}

std::vector<int> SimulatedPKB::getAllKeysAffectsBipNode() {
	return SimulatedPKB::affectsBipNodeTable.getAllKeysAffectsBipNode();
}

std::vector<std::unordered_set<int>> SimulatedPKB::getAllValuesAffectsBipNode() {
	return SimulatedPKB::affectsBipNodeTable.getAllValuesAffectsBipNode();
}

std::unordered_set<int> SimulatedPKB::getAffectsBipNode(int nodeNumber) {
	return SimulatedPKB::affectsBipNodeTable.getAffectsBipNode(nodeNumber);
}

std::unordered_set<int> SimulatedPKB::getAffectedByBipNode(int nodeNumber) {
	return SimulatedPKB::affectsBipNodeTable.getAffectedByBipNode(nodeNumber);
}

void SimulatedPKB::clear() {
	procedureTable.clear();
	procedureStatementListTable.clear();
	readTable.clear();
	printTable.clear();
	assignTable.clear();
	callTable.clear();
	whileTable.clear();
	ifTable.clear();
	followsTable.clear();
	followsStarTable.clear();
	parentTable.clear();
	parentStarTable.clear();
	usesTable.clear();
	modifiesTable.clear();
	procedureUsesTable.clear();
	procedureModifiesTable.clear();
	nextTable.clear();
	statementTable.clear();
	statementListTable.clear();

	nextBipTable.clear();
	nextBipStarTable.clear();
	affectsBipTable.clear();
	affectsBipStarTable.clear();
	affectsBipNodeTable.clear();
}