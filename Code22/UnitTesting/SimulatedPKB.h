#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

class SimulatedFollowsTable {
public:
	void SimulatedFollowsTable::insertFollows(int lineNumber, int leaderLine) {
		followsTable[lineNumber] = leaderLine;
		insertFollowedBy(leaderLine, lineNumber);
	}

	void SimulatedFollowsTable::insertFollowedBy(int lineNumber, int followerLine) {
		followedByTable[lineNumber] = followerLine;
	}

	std::vector<int> SimulatedFollowsTable::getAllKeysFollows() {
		std::vector<int> values;
		for (auto const& element : followsTable) {
			values.push_back(element.first);
		}
		return values;
	}

	int SimulatedFollowsTable::getFollows(int lineNumber) {
		std::unordered_map<int, int>::const_iterator iterator = followsTable.find(lineNumber);
		if (iterator != followsTable.end()) {
			return iterator->second;
		}
		else {
			return -1;
		}
	}

	int SimulatedFollowsTable::getFollowedBy(int lineNumber) {
		std::unordered_map<int, int>::const_iterator iterator = followedByTable.find(lineNumber);
		if (iterator != followedByTable.end()) {
			return iterator->second;
		}
		else {
			return -1;
		}
	}

	void SimulatedFollowsTable::clear() {
		followsTable.clear();
		followedByTable.clear();
	}

	bool SimulatedFollowsTable::isFollows(int lineNumber, int leaderLine) {
		return followsTable[lineNumber] == leaderLine;
	}
private:
	std::unordered_map<int, int> followsTable;
	std::unordered_map<int, int> followedByTable;
};

class SimulatedFollowsStarTable {
public:
	void SimulatedFollowsStarTable::insertFollowsStar(int lineNumber, std::unordered_set<int> leaderLines) {
		if (followsStarTable.count(lineNumber) == 0) {
			followsStarTable[lineNumber] = leaderLines;
		}
		else {
			auto pos = followsStarTable[lineNumber].begin();
			for (auto it = leaderLines.begin(); it != leaderLines.end(); ++it) {
				pos = followsStarTable[lineNumber].insert(pos, *it);
			}
		}
	}

	bool SimulatedFollowsStarTable::isFollowsStar(int lineNumber, int leaderLine) {
		return followsStarTable[lineNumber].count(leaderLine);
	}


	void  SimulatedFollowsStarTable::clear() {
		followsStarTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> followsStarTable;
};

class SimulatedParentTable {
public:
	void SimulatedParentTable::insertParent(int lineNumber, int parentLine) {
		parentTable[lineNumber] = parentLine;
		childTable[parentLine] = { lineNumber };
	}

	std::vector<int> SimulatedParentTable::getAllKeysParent() {
		std::vector<int> values;
		for (auto const& element : parentTable) {
			values.push_back(element.first);
		}
		return values;
	}

	int SimulatedParentTable::getParent(int lineNumber) {
		std::unordered_map<int, int>::const_iterator iterator = parentTable.find(lineNumber);
		if (iterator != parentTable.end()) {
			return iterator->second;
		}
		else {
			return -1;
		}
	}

	std::unordered_set<int> getChild(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator thing_iterator = childTable.find(lineNumber);
		if (thing_iterator != childTable.end()) {
			return thing_iterator->second;
		}
		else {
			return {};
		}
	}

	void SimulatedParentTable::clear() {
		parentTable.clear();
		childTable.clear();
	}

private:
	std::unordered_map<int, int> parentTable;
	std::unordered_map<int, std::unordered_set<int>> childTable;
};

class SimulatedParentStarTable {
public:
	void SimulatedParentStarTable::insertParentStar(int lineNumber, std::unordered_set<int> parentLines) {
		if (parentStarTable.count(lineNumber) == 0) {
			parentStarTable[lineNumber] = parentLines;
		}
		else {
			auto pos = parentStarTable[lineNumber].begin();
			for (auto it = parentLines.begin(); it != parentLines.end(); ++it) {
				pos = parentStarTable[lineNumber].insert(pos, *it);
			}
		}
		for (int element : parentLines) {
			SimulatedParentStarTable::makeChildStar(element, { lineNumber });
		}
	}
	void SimulatedParentStarTable::makeChildStar(int lineNumber, std::unordered_set<int> childLines) {
		if (childStarTable.count(lineNumber) == 0) {
			childStarTable[lineNumber] = childLines;
		}
		else {
			auto pos = childStarTable[lineNumber].begin();
			for (auto it = childLines.begin(); it != childLines.end(); ++it) {
				pos = childStarTable[lineNumber].insert(pos, *it);
			}
		}
	}

	bool SimulatedParentStarTable::isParentStar(int lineNumber, int parentLine) {
		return parentStarTable[lineNumber].count(parentLine);
	}

	void SimulatedParentStarTable::clear() {
		parentStarTable.clear();
		childStarTable.clear();
	}

	std::unordered_set<int> SimulatedParentStarTable::getChildStar(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator thing_iterator = childStarTable.find(lineNumber);
		if (thing_iterator != childStarTable.end()) {
			return thing_iterator->second;
		}
		else {
			return {};
		}
	}


private:
	std::unordered_map<int, std::unordered_set<int>> parentStarTable;
	std::unordered_map<int, std::unordered_set<int>> childStarTable;
};

class SimulatedAssignTable {
public:
	void SimulatedAssignTable::insertAssignLHS(int lineNumber, std::string variableLHS) {
		assignTable[lineNumber] = { variableLHS , "" };
	}

	void SimulatedAssignTable::insertAssignRHS(int lineNumber, std::string shuntedRHS) {
		std::pair<std::string, std::string> value = getAssign(lineNumber);
		value.second = shuntedRHS;
		assignTable[lineNumber] = value;
	}

	std::vector<int> SimulatedAssignTable::getAllKeysAssign() {
		std::vector<int> keys;
		for (auto const& element : assignTable) {
			keys.push_back(element.first);
		}
		return keys;
	}

	std::pair<std::string, std::string> SimulatedAssignTable::getAssign(int lineNumber) {
		std::unordered_map<int, std::pair<std::string, std::string>>::const_iterator iterator = assignTable.find(lineNumber);
		if (iterator != assignTable.end()) {
			return iterator->second;
		}
		else {
			return { "", "" };
		}
	}

	bool hasKeyAssign(int lineNumber) {
		return assignTable.count(lineNumber);
	}

	void SimulatedAssignTable::clear() {
		assignTable.clear();
	}

private:
	std::unordered_map<int, std::pair<std::string, std::string>> assignTable;
};

class SimulatedPrintTable {
public:
	void SimulatedPrintTable::insertPrint(int lineNumber, std::string varName) {
		printTable[lineNumber] = varName;
	}

	std::vector<int> SimulatedPrintTable::getAllKeysPrint() {
		std::vector<int> values;
		for (auto const& element : printTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::string SimulatedPrintTable::getPrint(int lineNumber) {
		std::unordered_map<int, std::string>::const_iterator iterator = printTable.find(lineNumber);
		if (iterator != printTable.end()) {
			return iterator->second;
		}
		else {
			return "";
		}
	}

	bool hasKeyPrint(int lineNumber) {
		return printTable.count(lineNumber);
	}

	void SimulatedPrintTable::clear() {
		printTable.clear();
	}

private:
	std::unordered_map<int, std::string> printTable;
};

class SimulatedReadTable {
public:
	void SimulatedReadTable::insertRead(int lineNumber, std::string readVar) {
		readTable[lineNumber] = readVar;
	}

	std::vector<int> SimulatedReadTable::getAllKeysRead() {
		std::vector<int> values;
		for (auto const& element : readTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::string SimulatedReadTable::getRead(int lineNumber) {
		std::unordered_map<int, std::string>::const_iterator iterator = readTable.find(lineNumber);
		if (iterator != readTable.end()) {
			return iterator->second;
		}
		else {
			return "";
		}
	}

	bool hasKeyRead(int lineNumber) {
		return readTable.count(lineNumber);
	}

	void SimulatedReadTable::clear() {
		readTable.clear();
	}

private:
	std::unordered_map<int, std::string> readTable;
};

class SimulatedCallTable {
public:
	void SimulatedCallTable::insertCall(int lineNumber, std::string procName) {
		callTable[lineNumber] = procName;
	}

	std::vector<int> SimulatedCallTable::getAllKeysCall() {
		std::vector<int> values;
		for (auto const& element : callTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::string SimulatedCallTable::getCall(int lineNumber) {
		std::unordered_map<int, std::string>::const_iterator iterator = callTable.find(lineNumber);
		if (iterator != callTable.end()) {
			return iterator->second;
		}
		else {
			return "";
		}
	}

	bool hasKeyCall(int lineNumber) {
		return callTable.count(lineNumber);
	}

	void SimulatedCallTable::clear() {
		callTable.clear();
	}

private:
	std::unordered_map<int, std::string> callTable;
};

class SimulatedIfTable {
public:
	void SimulatedIfTable::insertIf(int lineNumber, std::unordered_set<std::string> condition) {
		ifTable[lineNumber] = condition;
	}

	std::vector<int> SimulatedIfTable::getAllKeysIf() {
		std::vector<int> values;
		for (auto const& element : ifTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::unordered_set<std::string> SimulatedIfTable::getIf(int lineNumber) {
		std::unordered_map<int, std::unordered_set<std::string>>::const_iterator iterator = ifTable.find(lineNumber);
		if (iterator != ifTable.end()) {
			return iterator->second;
		}
		else {
			return {};
		}
	}

	bool hasKeyIf(int lineNumber) {
		return ifTable.count(lineNumber);
	}

	void SimulatedIfTable::clear() {
		ifTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<std::string>> ifTable;
};

class SimulatedWhileTable {
public:
	void SimulatedWhileTable::insertWhile(int lineNumber, std::unordered_set<std::string> condition) {
		whileTable[lineNumber] = condition;
	}

	std::vector<int> SimulatedWhileTable::getAllKeysWhile() {
		std::vector<int> values;
		for (auto const& element : whileTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::unordered_set<std::string> SimulatedWhileTable::getWhile(int lineNumber) {
		std::unordered_map<int, std::unordered_set<std::string>>::const_iterator iterator = whileTable.find(lineNumber);
		if (iterator != whileTable.end()) {
			return iterator->second;
		}
		else {
			return {};
		}
	}

	bool hasKeyWhile(int lineNumber) {
		return whileTable.count(lineNumber);
	}

	void SimulatedWhileTable::clear() {
		whileTable.clear();
	}


private:
	std::unordered_map<int, std::unordered_set<std::string>> whileTable;
};


class SimulatedUsesTable {
public:
	void SimulatedUsesTable::insertUses(int lineNumber, std::unordered_set<std::string> usedNames) {
		if (usesTable.count(lineNumber) == 0) {
			usesTable[lineNumber] = usedNames;
		}
		else {
			auto pos = usesTable[lineNumber].begin();
			for (auto it = usedNames.begin(); it != usedNames.end(); ++it) {
				pos = usesTable[lineNumber].insert(pos, *it);
			}
		}
	}

	std::vector<int> SimulatedUsesTable::getAllKeysUses() {
		std::vector<int> keys;
		for (auto const& element : usesTable) {
			keys.push_back(element.first);
		}
		return keys;
	}

	std::unordered_set<std::string> SimulatedUsesTable::getUses(int lineNumber) {
		std::unordered_map<int, std::unordered_set<std::string>>::const_iterator thing_iterator = usesTable.find(lineNumber);
		if (thing_iterator != usesTable.end()) {
			return thing_iterator->second;
		}
		else {
			return {};
		}
	}

	bool hasKeyUses(int lineNumber) {
		return usesTable.count(lineNumber);
	}

	void SimulatedUsesTable::clear() {
		usesTable.clear();
	}
private:
	std::unordered_map<int, std::unordered_set<std::string>> usesTable;
};

class SimulatedModifiesTable {
public:
	void SimulatedModifiesTable::insertModifies(int lineNumber, std::unordered_set<std::string> modifiedNames) {
		if (modifiesTable.count(lineNumber) == 0) {
			modifiesTable[lineNumber] = modifiedNames;
		}
		else {
			auto pos = modifiesTable[lineNumber].begin();
			for (auto it = modifiedNames.begin(); it != modifiedNames.end(); ++it) {
				pos = modifiesTable[lineNumber].insert(pos, *it);
			}
		}

		for (std::string element : modifiedNames) {
			insertModifiedBy(element, { lineNumber });
		}


	}

	std::vector<int> SimulatedModifiesTable::getAllKeysModifies() {
		std::vector<int> keys;
		for (auto const& element : modifiesTable) {
			keys.push_back(element.first);
		}
		return keys;
	}

	std::unordered_set<std::string> SimulatedModifiesTable::getModifies(int lineNumber) {
		std::unordered_map<int, std::unordered_set<std::string>>::const_iterator thing_iterator = modifiesTable.find(lineNumber);
		if (thing_iterator != modifiesTable.end()) {
			return thing_iterator->second;
		}
		else {
			return {};
		}
	}

	std::unordered_set<int> getModifiedBy(std::string name) {
		std::unordered_map<std::string, std::unordered_set<int>>::const_iterator thing_iterator = modifiedByTable.find(name);
		if (thing_iterator != modifiedByTable.end()) {
			return thing_iterator->second;
		}
		else {
			return {};
		}
	}



	void insertModifiedBy(std::string name, std::unordered_set<int> modifiedByLines) {
		if (modifiedByTable.count(name) == 0) {
			modifiedByTable[name] = modifiedByLines;
		}
		else {
			auto pos = modifiedByTable[name].begin();
			for (auto it = modifiedByLines.begin(); it != modifiedByLines.end(); ++it) {
				pos = modifiedByTable[name].insert(pos, *it);
			}
		}
	}

	bool hasKeyModifies(int lineNumber) {
		return modifiesTable.count(lineNumber);
	}

	void SimulatedModifiesTable::clear() {
		modifiesTable.clear();
		modifiedByTable.clear();
	}
private:
	std::unordered_map<int, std::unordered_set<std::string>> modifiesTable;
	std::unordered_map<std::string, std::unordered_set<int>> modifiedByTable;
};

class SimulatedProcedureTable {
public:
	int SimulatedProcedureTable::insertProcedure(std::string procName) {
		auto item = procedureReverseTable.find(procName);
		if (item != procedureReverseTable.end()) {
			return item->second;
		}

		procedureReverseTable.insert({ procName, currentIndex });

		if (procedureTable.count(currentIndex) == 0) {
			procedureTable[currentIndex] = procName;
		}


		++currentIndex;
		return currentIndex - 1;
	}

	std::vector<int> SimulatedProcedureTable::getAllKeysProcedure() {
		std::vector<int> keys;
		for (auto const& element : procedureTable) {
			keys.push_back(element.first);
		}
		return keys;
	}

	int SimulatedProcedureTable::getKeyProcedure(std::string procName) {
		auto item = procedureReverseTable.find(procName);
		if (item != procedureReverseTable.end()) {
			return item->second;
		}
		else {
			return -1;
		}
	}

	void  SimulatedProcedureTable::clear() {
		currentIndex = 0;
		procedureTable.clear();
		procedureReverseTable.clear();
	}
private:
	std::unordered_map<int, std::string> procedureTable;
	std::unordered_map<std::string, int> procedureReverseTable;
	int currentIndex = 0;
};

class SimulatedProcedureStatementListTable {
public:
	void SimulatedProcedureStatementListTable::insertProcedureStatementList(int procIndex, std::unordered_set<int> statementLines) {
		if (procedureStatementListTable.count(procIndex) == 0) {
			procedureStatementListTable[procIndex] = statementLines;
		}
		else {
			auto pos = procedureStatementListTable[procIndex].begin();
			for (auto it = statementLines.begin(); it != statementLines.end(); ++it) {
				pos = procedureStatementListTable[procIndex].insert(pos, *it);
			}
		}
	}

	std::unordered_set<int> getProcedureStatementList(int procIndex) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator thing_iterator = procedureStatementListTable.find(procIndex);
		if (thing_iterator != procedureStatementListTable.end()) {
			return thing_iterator->second;
		}
		else {
			return {};
		}
	}

	void  SimulatedProcedureStatementListTable::clear() {
		procedureStatementListTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> procedureStatementListTable;
};

class SimulatedStatementListTable {
public:
	void SimulatedStatementListTable::insertStatementList(int index, std::unordered_set<int> statementLines) {
		if (statementListTable.count(index) == 0) {
			statementListTable[index] = statementLines;
		}
		else {
			auto pos = statementListTable[index].begin();
			for (auto it = statementLines.begin(); it != statementLines.end(); ++it) {
				pos = statementListTable[index].insert(pos, *it);
			}
		}
	}

	std::unordered_set<int> getStatementList(int index) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator thing_iterator = statementListTable.find(index);
		if (thing_iterator != statementListTable.end()) {
			return thing_iterator->second;
		}
		else {
			return {};
		}
	}

	void SimulatedStatementListTable::clear() {
		statementListTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> statementListTable;
};

class SimulatedStatementTable {
public:
	void SimulatedStatementTable::insertStatement(int lineNumber, std::string statementType) {
		statementTable[lineNumber] = statementType;
	}

	std::vector<int> SimulatedStatementTable::getAllKeysStatement() {
		std::vector<int> values;
		for (auto const& element : statementTable) {
			values.push_back(element.first);
		}
		return values;
	}

	void SimulatedStatementTable::clear() {
		statementTable.clear();
	}

	int SimulatedStatementTable::getSizeStatement() {
		return statementTable.size();
	}

	std::string SimulatedStatementTable::getStatement(int lineNumber) {
		std::unordered_map<int, std::string>::const_iterator thing_iterator = statementTable.find(lineNumber);
		if (thing_iterator != statementTable.end()) {
			return thing_iterator->second;
		}
		else {
			return "";
		}
	}



private:
	std::unordered_map<int, std::string> statementTable;
};

class SimulatedNextTable {
public:
	void SimulatedNextTable::insertNext(int lineNumber, std::unordered_set<int> nextLines) {
		if (nextTable.count(lineNumber) == 0) {
			nextTable[lineNumber] = nextLines;
		}
		else {
			auto pos = nextTable[lineNumber].begin();
			for (auto it = nextLines.begin(); it != nextLines.end(); ++it) {
				pos = nextTable[lineNumber].insert(pos, *it);
			}
		}
		for (int element : nextLines) {
			SimulatedNextTable::insertPrevious(element, { lineNumber });
		}
	}
	bool SimulatedNextTable::isNext(int lineNumber, int nextLine) {
		return nextTable[lineNumber].count(nextLine);
	}

	void SimulatedNextTable::insertPrevious(int lineNumber, std::unordered_set<int> previousLines) {
		if (previousTable.count(lineNumber) == 0) {
			previousTable[lineNumber] = previousLines;
		}
		else {
			auto pos = previousTable[lineNumber].begin();
			for (auto it = previousLines.begin(); it != previousLines.end(); ++it) {
				pos = previousTable[lineNumber].insert(pos, *it);
			}
		}
	}

	std::vector<int> SimulatedNextTable::getAllKeysNext() {
		std::vector<int> values;
		for (auto const& element : nextTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::unordered_set<int> SimulatedNextTable::getNext(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = nextTable.find(lineNumber);
		if (iterator != nextTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	std::unordered_set<int> SimulatedNextTable::getPrevious(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = previousTable.find(lineNumber);
		if (iterator != previousTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	void SimulatedNextTable::clear() {
		nextTable.clear();
		previousTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> nextTable;
	std::unordered_map<int, std::unordered_set<int>> previousTable;
};

class SimulatedNextBipTable {
public:
	void SimulatedNextBipTable::insertNextBip(int lineNumber, std::unordered_set<int> nextBipLines) {
		if (nextBipTable.count(lineNumber) == 0) {
			nextBipTable[lineNumber] = nextBipLines;
		}
		else {
			auto pos = nextBipTable[lineNumber].begin();
			for (auto it = nextBipLines.begin(); it != nextBipLines.end(); ++it) {
				pos = nextBipTable[lineNumber].insert(pos, *it);
			}
		}
		for (int element : nextBipLines) {
			SimulatedNextBipTable::insertPreviousBip(element, { lineNumber });
		}
	}
	bool SimulatedNextBipTable::isNextBip(int lineNumber, int nextBipLine) {
		return nextBipTable[lineNumber].count(nextBipLine);
	}

	void SimulatedNextBipTable::insertPreviousBip(int lineNumber, std::unordered_set<int> previousBipLines) {
		if (previousBipTable.count(lineNumber) == 0) {
			previousBipTable[lineNumber] = previousBipLines;
		}
		else {
			auto pos = previousBipTable[lineNumber].begin();
			for (auto it = previousBipLines.begin(); it != previousBipLines.end(); ++it) {
				pos = previousBipTable[lineNumber].insert(pos, *it);
			}
		}
	}

	std::vector<int> SimulatedNextBipTable::getAllKeysNextBip() {
		std::vector<int> values;
		for (auto const& element : nextBipTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::unordered_set<int> SimulatedNextBipTable::getNextBip(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = nextBipTable.find(lineNumber);
		if (iterator != nextBipTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	std::unordered_set<int> SimulatedNextBipTable::getPreviousBip(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = previousBipTable.find(lineNumber);
		if (iterator != previousBipTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	void SimulatedNextBipTable::clear() {
		nextBipTable.clear();
		previousBipTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> nextBipTable;
	std::unordered_map<int, std::unordered_set<int>> previousBipTable;
};

class SimulatedNextBipStarTable {
public:
	void SimulatedNextBipStarTable::insertNextBipStar(int lineNumber, std::unordered_set<int> nextBipStarLines) {
		if (nextBipStarTable.count(lineNumber) == 0) {
			nextBipStarTable[lineNumber] = nextBipStarLines;
		}
		else {
			auto pos = nextBipStarTable[lineNumber].begin();
			for (auto it = nextBipStarLines.begin(); it != nextBipStarLines.end(); ++it) {
				pos = nextBipStarTable[lineNumber].insert(pos, *it);
			}
		}
		for (int element : nextBipStarLines) {
			SimulatedNextBipStarTable::insertPreviousBipStar(element, { lineNumber });
		}
	}
	bool SimulatedNextBipStarTable::isNextBipStar(int lineNumber, int nextBipStarLine) {
		return nextBipStarTable[lineNumber].count(nextBipStarLine);
	}

	void SimulatedNextBipStarTable::insertPreviousBipStar(int lineNumber, std::unordered_set<int> previousBipStarLines) {
		if (previousBipStarTable.count(lineNumber) == 0) {
			previousBipStarTable[lineNumber] = previousBipStarLines;
		}
		else {
			auto pos = previousBipStarTable[lineNumber].begin();
			for (auto it = previousBipStarLines.begin(); it != previousBipStarLines.end(); ++it) {
				pos = previousBipStarTable[lineNumber].insert(pos, *it);
			}
		}
	}

	std::vector<int> SimulatedNextBipStarTable::getAllKeysNextBipStar() {
		std::vector<int> values;
		for (auto const& element : nextBipStarTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::unordered_set<int> SimulatedNextBipStarTable::getNextBipStar(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = nextBipStarTable.find(lineNumber);
		if (iterator != nextBipStarTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	std::unordered_set<int> SimulatedNextBipStarTable::getPreviousBipStar(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = previousBipStarTable.find(lineNumber);
		if (iterator != previousBipStarTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	void SimulatedNextBipStarTable::clear() {
		nextBipStarTable.clear();
		previousBipStarTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> nextBipStarTable;
	std::unordered_map<int, std::unordered_set<int>> previousBipStarTable;
};

class SimulatedAffectsBipTable {
public:
	void SimulatedAffectsBipTable::insertAffectsBip(int lineNumber, std::unordered_set<int> affectsBipLines) {
		if (affectsBipTable.count(lineNumber) == 0) {
			affectsBipTable[lineNumber] = affectsBipLines;
		}
		else {
			auto pos = affectsBipTable[lineNumber].begin();
			for (auto it = affectsBipLines.begin(); it != affectsBipLines.end(); ++it) {
				pos = affectsBipTable[lineNumber].insert(pos, *it);
			}
		}
		for (int element : affectsBipLines) {
			SimulatedAffectsBipTable::insertAffectedByBip(element, { lineNumber });
		}
	}
	bool SimulatedAffectsBipTable::isAffectsBip(int lineNumber, int affectsBipLine) {
		return affectsBipTable[lineNumber].count(affectsBipLine);
	}

	void SimulatedAffectsBipTable::insertAffectedByBip(int lineNumber, std::unordered_set<int> affectedByBipLines) {
		if (affectedByBipTable.count(lineNumber) == 0) {
			affectedByBipTable[lineNumber] = affectedByBipLines;
		}
		else {
			auto pos = affectedByBipTable[lineNumber].begin();
			for (auto it = affectedByBipLines.begin(); it != affectedByBipLines.end(); ++it) {
				pos = affectedByBipTable[lineNumber].insert(pos, *it);
			}
		}
	}

	std::vector<int> SimulatedAffectsBipTable::getAllKeysAffectsBip() {
		std::vector<int> values;
		for (auto const& element : affectsBipTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::unordered_set<int> SimulatedAffectsBipTable::getAffectsBip(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = affectsBipTable.find(lineNumber);
		if (iterator != affectsBipTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	std::unordered_set<int> SimulatedAffectsBipTable::getAffectedByBip(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = affectedByBipTable.find(lineNumber);
		if (iterator != affectedByBipTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	void SimulatedAffectsBipTable::clear() {
		affectsBipTable.clear();
		affectedByBipTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> affectsBipTable;
	std::unordered_map<int, std::unordered_set<int>> affectedByBipTable;
};

class SimulatedAffectsBipStarTable {
public:
	void SimulatedAffectsBipStarTable::insertAffectsBipStar(int lineNumber, std::unordered_set<int> affectsBipStarLines) {
		if (affectsBipStarTable.count(lineNumber) == 0) {
			affectsBipStarTable[lineNumber] = affectsBipStarLines;
		}
		else {
			auto pos = affectsBipStarTable[lineNumber].begin();
			for (auto it = affectsBipStarLines.begin(); it != affectsBipStarLines.end(); ++it) {
				pos = affectsBipStarTable[lineNumber].insert(pos, *it);
			}
		}
		for (int element : affectsBipStarLines) {
			SimulatedAffectsBipStarTable::insertAffectedByBipStar(element, { lineNumber });
		}
	}
	bool SimulatedAffectsBipStarTable::isAffectsBipStar(int lineNumber, int affectsBipStarLine) {
		return affectsBipStarTable[lineNumber].count(affectsBipStarLine);
	}

	void SimulatedAffectsBipStarTable::insertAffectedByBipStar(int lineNumber, std::unordered_set<int> affectedByBipStarLines) {
		if (affectedByBipStarTable.count(lineNumber) == 0) {
			affectedByBipStarTable[lineNumber] = affectedByBipStarLines;
		}
		else {
			auto pos = affectedByBipStarTable[lineNumber].begin();
			for (auto it = affectedByBipStarLines.begin(); it != affectedByBipStarLines.end(); ++it) {
				pos = affectedByBipStarTable[lineNumber].insert(pos, *it);
			}
		}
	}

	std::vector<int> SimulatedAffectsBipStarTable::getAllKeysAffectsBipStar() {
		std::vector<int> values;
		for (auto const& element : affectsBipStarTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::unordered_set<int> SimulatedAffectsBipStarTable::getAffectsBipStar(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = affectsBipStarTable.find(lineNumber);
		if (iterator != affectsBipStarTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	std::unordered_set<int> SimulatedAffectsBipStarTable::getAffectedByBipStar(int lineNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = affectedByBipStarTable.find(lineNumber);
		if (iterator != affectedByBipStarTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	void SimulatedAffectsBipStarTable::clear() {
		affectsBipStarTable.clear();
		affectedByBipStarTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> affectsBipStarTable;
	std::unordered_map<int, std::unordered_set<int>> affectedByBipStarTable;
};

class SimulatedAffectsBipNodeTable {
public:
	void SimulatedAffectsBipNodeTable::insertAffectsBipNode(int nodeNumber, std::unordered_set<int> affectsBipNodeNodes) {
		if (affectsBipNodeTable.count(nodeNumber) == 0) {
			affectsBipNodeTable[nodeNumber] = affectsBipNodeNodes;
		}
		else {
			auto pos = affectsBipNodeTable[nodeNumber].begin();
			for (auto it = affectsBipNodeNodes.begin(); it != affectsBipNodeNodes.end(); ++it) {
				pos = affectsBipNodeTable[nodeNumber].insert(pos, *it);
			}
		}
		for (int element : affectsBipNodeNodes) {
			SimulatedAffectsBipNodeTable::insertAffectedByBipNode(element, { nodeNumber });
		}
	}
	bool SimulatedAffectsBipNodeTable::isAffectsBipNode(int nodeNumber, int affectsBipNodeNode) {
		return affectsBipNodeTable[nodeNumber].count(affectsBipNodeNode);
	}

	void SimulatedAffectsBipNodeTable::insertAffectedByBipNode(int nodeNumber, std::unordered_set<int> affectedByBipNodeNodes) {
		if (affectedByBipNodeTable.count(nodeNumber) == 0) {
			affectedByBipNodeTable[nodeNumber] = affectedByBipNodeNodes;
		}
		else {
			auto pos = affectedByBipNodeTable[nodeNumber].begin();
			for (auto it = affectedByBipNodeNodes.begin(); it != affectedByBipNodeNodes.end(); ++it) {
				pos = affectedByBipNodeTable[nodeNumber].insert(pos, *it);
			}
		}
	}

	std::vector<int> SimulatedAffectsBipNodeTable::getAllKeysAffectsBipNode() {
		std::vector<int> values;
		for (auto const& element : affectsBipNodeTable) {
			values.push_back(element.first);
		}
		return values;
	}

	std::vector<std::unordered_set<int>> SimulatedAffectsBipNodeTable::getAllValuesAffectsBipNode() {
		std::vector<std::unordered_set<int>> values;
		for (auto const& element : affectsBipNodeTable) {
			values.push_back(element.second);
		}
		return values;
	}

	std::unordered_set<int> SimulatedAffectsBipNodeTable::getAffectsBipNode(int nodeNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = affectsBipNodeTable.find(nodeNumber);
		if (iterator != affectsBipNodeTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	std::unordered_set<int> SimulatedAffectsBipNodeTable::getAffectedByBipNode(int nodeNumber) {
		std::unordered_map<int, std::unordered_set<int>>::const_iterator iterator = affectedByBipNodeTable.find(nodeNumber);
		if (iterator != affectedByBipNodeTable.end()) {
			return iterator->second;
		}
		else {
			return { };
		}
	}

	void SimulatedAffectsBipNodeTable::clear() {
		affectsBipNodeTable.clear();
		affectedByBipNodeTable.clear();
	}

private:
	std::unordered_map<int, std::unordered_set<int>> affectsBipNodeTable;
	std::unordered_map<int, std::unordered_set<int>> affectedByBipNodeTable;
};

class SimulatedPKB {
private:
	SimulatedFollowsTable followsTable;
	SimulatedFollowsStarTable followsStarTable;
	SimulatedParentTable parentTable;
	SimulatedParentStarTable parentStarTable;
	SimulatedAssignTable assignTable;
	SimulatedPrintTable printTable;
	SimulatedReadTable readTable;
	SimulatedCallTable callTable;
	SimulatedIfTable ifTable;
	SimulatedWhileTable whileTable;
	SimulatedUsesTable usesTable;
	SimulatedModifiesTable modifiesTable;
	SimulatedUsesTable procedureUsesTable;
	SimulatedModifiesTable procedureModifiesTable;
	SimulatedProcedureTable procedureTable;
	SimulatedProcedureStatementListTable procedureStatementListTable;
	SimulatedStatementTable statementTable;
	SimulatedStatementListTable statementListTable;
	SimulatedNextTable nextTable;
	SimulatedNextBipTable nextBipTable;
	SimulatedNextBipStarTable nextBipStarTable;
	SimulatedAffectsBipTable affectsBipTable;
	SimulatedAffectsBipNodeTable affectsBipNodeTable;
	SimulatedAffectsBipStarTable affectsBipStarTable;

	SimulatedPKB(); // Prevent construction
	SimulatedPKB(const SimulatedPKB&); // Prevent construction by copying
	SimulatedPKB& operator=(const SimulatedPKB&); // Prevent assignment
	~SimulatedPKB(); // Prevent unwanted destruction

public:
	static SimulatedPKB& getInstance()
	{
		static SimulatedPKB inst;
		return inst;
	}

	void SimulatedPKB::insertFollows(int lineNumber, int leaderLine);
	std::vector<int> SimulatedPKB::getAllKeysFollows();
	int SimulatedPKB::getFollows(int lineNumber);
	int SimulatedPKB::getFollowedBy(int lineNumber);
	void SimulatedPKB::insertFollowsStar(int lineNumber, std::unordered_set<int> leaderLines);
	bool SimulatedPKB::isFollowsStar(int lineNumber, int leaderLine);
	bool SimulatedPKB::isFollows(int lineNumber, int leaderLine);

	void SimulatedPKB::insertParent(int lineNumber, int leaderLine);
	std::vector<int> SimulatedPKB::getAllKeysParent();
	int SimulatedPKB::getParent(int lineNumber);
	std::unordered_set<int> SimulatedPKB::getChild(int lineNumber);

	void SimulatedPKB::insertParentStar(int lineNumber, std::unordered_set<int> leaderLines);
	bool SimulatedPKB::isParentStar(int lineNumber, int leaderLine);
	std::unordered_set<int> SimulatedPKB::getChildStar(int lineNumber);

	void SimulatedPKB::insertAssignLHS(int lineNumber, std::string variableLHS);
	void SimulatedPKB::insertAssignRHS(int lineNumber, std::string shuntedRHS);
	std::pair<std::string, std::string> SimulatedPKB::getAssign(int lineNumber);
	std::vector<int> SimulatedPKB::getAllKeysAssign();
	bool SimulatedPKB::hasKeyAssign(int lineNumber);

	void SimulatedPKB::insertPrint(int lineNumber, std::string varName);
	std::vector<int> SimulatedPKB::getAllKeysPrint();
	std::string SimulatedPKB::getPrint(int lineNumber);
	bool SimulatedPKB::hasKeyPrint(int lineNumber);

	void SimulatedPKB::insertRead(int lineNumber, std::string readVar);
	std::vector<int> SimulatedPKB::getAllKeysRead();
	std::string SimulatedPKB::getRead(int lineNumber);
	bool SimulatedPKB::hasKeyRead(int lineNumber);

	void SimulatedPKB::insertCall(int lineNumber, std::string procName);
	std::vector<int> SimulatedPKB::getAllKeysCall();
	std::string SimulatedPKB::getCall(int lineNumber);
	bool SimulatedPKB::hasKeyCall(int lineNumber);


	void SimulatedPKB::insertIf(int lineNumber, std::unordered_set<std::string> condition);
	std::vector<int> SimulatedPKB::getAllKeysIf();
	std::unordered_set<std::string> SimulatedPKB::getIf(int lineNumber);
	bool SimulatedPKB::hasKeyIf(int lineNumber);


	void SimulatedPKB::insertWhile(int lineNumber, std::unordered_set<std::string> condition);
	std::vector<int> SimulatedPKB::getAllKeysWhile();
	std::unordered_set<std::string> SimulatedPKB::getWhile(int lineNumber);
	bool SimulatedPKB::hasKeyWhile(int lineNumber);


	void SimulatedPKB::insertUses(int lineNumber, std::unordered_set<std::string> usedNames);
	std::vector<int> SimulatedPKB::getAllKeysUses();
	std::unordered_set<std::string> SimulatedPKB::getUses(int lineNumber);
	bool SimulatedPKB::hasKeyUses(int lineNumber);


	void SimulatedPKB::insertModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);
	std::vector<int> SimulatedPKB::getAllKeysModifies();
	std::unordered_set<std::string> SimulatedPKB::getModifies(int lineNumber);
	bool SimulatedPKB::hasKeyModifies(int lineNumber);
	std::unordered_set<int> SimulatedPKB::getModifiedBy(std::string name);


	void SimulatedPKB::insertProcedureUses(int lineNumber, std::unordered_set<std::string> usedNames);
	void SimulatedPKB::insertProcedureModifies(int lineNumber, std::unordered_set<std::string> modifiedNames);

	std::unordered_set<std::string> SimulatedPKB::getProcedureModifies(int lineNumber);
	std::unordered_set<std::string> SimulatedPKB::getProcedureUses(int lineNumber);

	int SimulatedPKB::insertProcedure(std::string procName);
	std::vector<int> SimulatedPKB::getAllKeysProcedure();
	int SimulatedPKB::getKeyProcedure(std::string procName);

	std::unordered_set<int> SimulatedPKB::getStatementList(int index);
	void SimulatedPKB::insertStatementList(int index, std::unordered_set<int> statementLines);

	std::unordered_set<int> SimulatedPKB::getProcedureStatementList(int procIndex);
	void SimulatedPKB::insertProcedureStatementList(int procIndex, std::unordered_set<int> statementLines);

	void SimulatedPKB::insertNext(int lineNumber, std::unordered_set<int> nextLines);
	std::vector<int> SimulatedPKB::getAllKeysNext();
	std::unordered_set<int> SimulatedPKB::getNext(int lineNumber);
	std::unordered_set<int> SimulatedPKB::getPrevious(int lineNumber);
	bool SimulatedPKB::isNext(int lineNumber, int nextLine);

	void SimulatedPKB::insertStatement(int lineNumber, std::string statementType);
	std::vector<int> SimulatedPKB::getAllKeysStatement();
	std::string SimulatedPKB::getStatement(int lineNumber);
	int SimulatedPKB::getSizeStatement();
	void SimulatedPKB::clear();

	void SimulatedPKB::insertNextBip(int lineNumber, std::unordered_set<int> nextBipLines);
	std::vector<int> SimulatedPKB::getAllKeysNextBip();
	std::unordered_set<int> SimulatedPKB::getNextBip(int lineNumber);
	std::unordered_set<int> SimulatedPKB::getPreviousBip(int lineNumber);
	bool SimulatedPKB::isNextBip(int lineNumber, int nextBipLine);

	void SimulatedPKB::insertNextBipStar(int lineNumber, std::unordered_set<int> nextBipStarLines);
	std::vector<int> SimulatedPKB::getAllKeysNextBipStar();
	std::unordered_set<int> SimulatedPKB::getNextBipStar(int lineNumber);
	std::unordered_set<int> SimulatedPKB::getPreviousBipStar(int lineNumber);
	bool SimulatedPKB::isNextBipStar(int lineNumber, int nextBipStarLine);

	void SimulatedPKB::insertAffectsBip(int lineNumber, std::unordered_set<int> affectsBipLines);
	std::vector<int> SimulatedPKB::getAllKeysAffectsBip();
	std::unordered_set<int> SimulatedPKB::getAffectsBip(int lineNumber);
	std::unordered_set<int> SimulatedPKB::getAffectedByBip(int lineNumber);
	bool SimulatedPKB::isAffectsBip(int lineNumber, int affectsBipLine);

	void SimulatedPKB::insertAffectsBipStar(int lineNumber, std::unordered_set<int> affectsBipStarLines);
	std::vector<int> SimulatedPKB::getAllKeysAffectsBipStar();
	std::unordered_set<int> SimulatedPKB::getAffectsBipStar(int lineNumber);
	std::unordered_set<int> SimulatedPKB::getAffectedByBipStar(int lineNumber);
	bool SimulatedPKB::isAffectsBipStar(int lineNumber, int affectsBipStarLine);

	void SimulatedPKB::insertAffectsBipNode(int nodeNumber, std::unordered_set<int> affectsBipNodeNodes);
	std::vector<int> SimulatedPKB::getAllKeysAffectsBipNode();
	std::vector<std::unordered_set<int>> SimulatedPKB::getAllValuesAffectsBipNode();
	std::unordered_set<int> SimulatedPKB::getAffectsBipNode(int nodeNumber);
	std::unordered_set<int> SimulatedPKB::getAffectedByBipNode(int nodeNumber);
	bool SimulatedPKB::isAffectsBipNode(int nodeNumber, int affectsBipNodeNode);
};
