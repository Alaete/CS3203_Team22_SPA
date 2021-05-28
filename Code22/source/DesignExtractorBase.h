#pragma once
#include "../source/PKB/ConcreteClasses/PKB_Map_NextStar.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_Affects.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_AffectsStar.h"
#include "../source/PKB/ConcreteClasses/PKB_Map_Node.h"

#include <queue> 
#include <set>
#include <stack>

template<class T>

class DesignExtractorBase {
public:
	static DesignExtractorBase& DesignExtractorBase::getInstance() {
		static DesignExtractorBase instance;
		return instance;
	}

	void extractAllDesigns() {
		extractFollowsStar();
		extractParentStar();
		extractUsesAndModifies();
		extractNext();
	}

	void extractExtensions() {
		clearExtension();
		constructProgramCFG();
		extractNextBip();
		extractNextBipStar();
		extractAffectsBip();
		extractAffectsBipStar();
	}

	PKB_Map_NextStar tempNextStarStorage;
	PKB_Map_Affects tempAffectsStorage;
	PKB_Map_AffectsStar tempAffectsStarStorage;

	std::unordered_map<int, int> nodeIndexToLineNumber_;
	std::unordered_map<int, std::unordered_set<int>> lineNumberToNodeIndex_;
	std::unordered_map<int, std::unordered_set<int>> nodeAdjacency_;

	void extractFollowsStar() {
		std::vector<int> followers = T::getInstance().getAllKeysFollows();
		for (int follower : followers) {
			std::unordered_set<int> leaders;
			int leaderLine = T::getInstance().getFollows(follower);
			while (leaderLine > 0) {
				leaders.insert(leaderLine);
				leaderLine = T::getInstance().getFollows(leaderLine);
			}
			T::getInstance().insertFollowsStar(follower, leaders);
		}
	}
	void extractParentStar() {
		std::vector<int> childList = T::getInstance().getAllKeysParent();
		for (int child : childList) {
			std::unordered_set<int> parents;
			int currParent = T::getInstance().getParent(child);
			while (currParent > 0) {
				parents.insert(currParent);
				currParent = T::getInstance().getParent(currParent);
			}
			T::getInstance().insertParentStar(child, parents);
		}
	}

	void extractUsesAndModifies() {
		std::vector<int> procedureList = T::getInstance().getAllKeysProcedure();
		for (int procedure : procedureList) {
			extractUsesAndModifiesForProcedure(procedure);
		}
	}

	void extractUsesAndModifiesForProcedure(int procedureIndex) {
		std::unordered_set<std::string> varUsedByProcedure;
		std::unordered_set<std::string> varModifiedByProcedure;

		// get statementList of procedure
		std::unordered_set<int> statementList = T::getInstance().getProcedureStatementList(procedureIndex);
		std::vector<int> assignLineNumbers;
		std::vector<int> printLineNumbers;
		std::vector<int> readLineNumbers;
		std::vector<int> containerLineNumbers; // stores all If and While statements
		std::vector<int> callLineNumbers;

		for (int statement : statementList) {
			if (T::getInstance().hasKeyAssign(statement)) {
				assignLineNumbers.push_back(statement);
			} 
			else if (T::getInstance().hasKeyPrint(statement)) {
				printLineNumbers.push_back(statement);
			}
			else if (T::getInstance().hasKeyRead(statement)) {
				readLineNumbers.push_back(statement);
			}
			else if (T::getInstance().hasKeyCall(statement)){
				callLineNumbers.push_back(statement);
			}
			else if (T::getInstance().hasKeyIf(statement) || T::getInstance().hasKeyWhile(statement)) {
				containerLineNumbers.push_back(statement);
			}
		}


		// For all assignment statements, extract Uses and Modifies
		for (int assignLineNumber : assignLineNumbers) {
			std::string assign_string = T::getInstance().getAssign(assignLineNumber).second;
			std::unordered_set<std::string> usedVarSet = getVarUsed(assign_string);
			std::string modifiedVar = T::getInstance().getAssign(assignLineNumber).first;
			for (std::string usedVar : usedVarSet) {
				T::getInstance().insertUses(assignLineNumber, { usedVar });
				varUsedByProcedure.insert(usedVar);
			}
			T::getInstance().insertModifies(assignLineNumber, { modifiedVar });
			varModifiedByProcedure.insert(modifiedVar);
		}
		// For all Print statement, extract Uses
		for (int printLineNumber : printLineNumbers) {
			std::string printVar = T::getInstance().getPrint(printLineNumber);
			T::getInstance().insertUses(printLineNumber, { printVar });
			varUsedByProcedure.insert(printVar);
		}
		// For all Read statements, extract Modifies
		for (int readLineNumber : readLineNumbers) {
			std::string readVar = T::getInstance().getRead(readLineNumber);
			T::getInstance().insertModifies(readLineNumber, { readVar });
			varModifiedByProcedure.insert(readVar);
		}
		// For all Call statements, extract Calls
		for (int callLineNumber : callLineNumbers) {
			if (!T::getInstance().hasKeyUses(callLineNumber) || !T::getInstance().hasKeyModifies(callLineNumber)) {
				// Call statement does not have it's uses and modifies populated yet
				std::string procedureCallName = T::getInstance().getCall(callLineNumber);
				int procedureCallIndex = T::getInstance().getKeyProcedure(procedureCallName);
				// recursively call until all procedure has uses and modifies populated properly
				extractUsesAndModifiesForProcedure(procedureCallIndex);
				// set callLineNumber to use all variables used and modified by procedure that it calls
				std::unordered_set<std::string> procedureUsedByCallStatement = T::getInstance().getProcedureUses(procedureCallIndex);
				std::unordered_set<std::string> procedureModifiedByCallStatement = T::getInstance().getProcedureModifies(procedureCallIndex);
				T::getInstance().insertUses(callLineNumber, procedureUsedByCallStatement);
				T::getInstance().insertModifies(callLineNumber, procedureModifiedByCallStatement);
				varUsedByProcedure.insert(procedureUsedByCallStatement.begin(), procedureUsedByCallStatement.end());
				varModifiedByProcedure.insert(procedureModifiedByCallStatement.begin(), procedureModifiedByCallStatement.end());
			}
		}

		// For all container statements (If/While) extract uses and modifies 
		// Sort all container lines to decreasing order so most nested loop is processed first
		std::sort(containerLineNumbers.begin(), containerLineNumbers.end(), std::greater<int>());
		for (int containerLineNumber : containerLineNumbers) {
			std::unordered_set<std::string> ifConditionVars = T::getInstance().getIf(containerLineNumber);
			std::unordered_set<std::string> whileConditionVars = T::getInstance().getWhile(containerLineNumber);
			if (!whileConditionVars.empty()) {
				// While statement
				//std::unordered_set<std::string> whileCondition = T::getInstance().getWhile(containerLineNumber);
				std::unordered_set<std::string> variablesUsedByWhile = whileConditionVars;
				std::unordered_set<std::string> variablesModifiedByWhile;
				std::unordered_set<int> childrenOfWhileLineNum = T::getInstance().getChildStar(containerLineNumber);
				for (int childLineNum : childrenOfWhileLineNum) {
					std::unordered_set<std::string> varUsedByChild = T::getInstance().getUses(childLineNum);
					std::unordered_set<std::string> varModifiedByChild = T::getInstance().getModifies(childLineNum);
					for (std::string varUsed : varUsedByChild) {
						variablesUsedByWhile.insert(varUsed);
					}
					for (std::string varModified : varModifiedByChild) {
						variablesModifiedByWhile.insert(varModified);
					}
				}
				T::getInstance().insertUses(containerLineNumber, variablesUsedByWhile);
				varUsedByProcedure.insert(variablesUsedByWhile.begin(), variablesUsedByWhile.end());
				T::getInstance().insertModifies(containerLineNumber, variablesModifiedByWhile);
				varModifiedByProcedure.insert(variablesModifiedByWhile.begin(), variablesModifiedByWhile.end());
			}
			else {
				// If statement
				std::unordered_set<std::string> variablesUsedByIf = ifConditionVars;
				std::unordered_set<std::string> variablesModifiedByIf;
				std::unordered_set<int> childrenOfIfLineNum = T::getInstance().getChildStar(containerLineNumber);
				for (int childLineNum : childrenOfIfLineNum) {
					std::unordered_set<std::string> varUsedByChild = T::getInstance().getUses(childLineNum);
					std::unordered_set<std::string> varModifiedByChild = T::getInstance().getModifies(childLineNum);
					for (std::string varUsed : varUsedByChild) {
						variablesUsedByIf.insert(varUsed);
					}
					for (std::string varModified : varModifiedByChild) {
						variablesModifiedByIf.insert(varModified);
					}
				}
				T::getInstance().insertUses(containerLineNumber, variablesUsedByIf);
				varUsedByProcedure.insert(variablesUsedByIf.begin(), variablesUsedByIf.end());
				T::getInstance().insertModifies(containerLineNumber, variablesModifiedByIf);
				varModifiedByProcedure.insert(variablesModifiedByIf.begin(), variablesModifiedByIf.end());

			}

		}
		// for the one and only procedure, store all uses and modifies inside it
		T::getInstance().insertProcedureUses(procedureIndex, varUsedByProcedure);
		T::getInstance().insertProcedureModifies(procedureIndex, varModifiedByProcedure);
	}

	void extractNext() {
		bool foundNextWhile = false;
		int follower;
		int parent;
		int whileStatement;
		std::string statementType;
		std::vector<int> lineNumbers = T::getInstance().getAllKeysStatement();
		for (auto& lineNumber : lineNumbers) {
			follower = T::getInstance().getFollowedBy(lineNumber);
			statementType = T::getInstance().getStatement(lineNumber);
			if (statementType == "assign" || statementType == "call" || statementType == "print" || statementType == "read") {
				follower = T::getInstance().getFollowedBy(lineNumber);
				if (follower != -1) {
					T::getInstance().insertNext(lineNumber, { follower });
				}
				else {
					parent = T::getInstance().getParent(lineNumber);
					while (true) {
						if (parent == -1) {
							break;
						}
						if (T::getInstance().getStatement(parent) == "while") {
							T::getInstance().insertNext(lineNumber, { parent });
							break;
						}
						follower = T::getInstance().getFollowedBy(parent);
						if (follower != -1) {
							T::getInstance().insertNext(lineNumber, { follower });
							break;
						}
						parent = T::getInstance().getParent(parent);
					}
				}
			}
			else if (statementType == "if") {
				T::getInstance().insertNext(lineNumber, { findFirstChild(lineNumber),  findFirstElseChild(lineNumber) });
			}
			else if (statementType == "while") {
				T::getInstance().insertNext(lineNumber, { findFirstChild(lineNumber) });
				whileStatement = lineNumber;
				while (true) {
					follower = T::getInstance().getFollowedBy(whileStatement);
					if (follower != -1) {
						T::getInstance().insertNext(lineNumber, { follower });
						break;
					}
					parent = T::getInstance().getParent(whileStatement);
					if (parent == -1) {
						break;
					}
					if (T::getInstance().getStatement(parent) == "while") {
						T::getInstance().insertNext(lineNumber, { parent });
						break;
					}
					whileStatement = parent;
				}
			}
		}
	}

	int findFirstChild(int lineNumber) {
		std::unordered_set<int> children = T::getInstance().getStatementList(lineNumber + 1);
		if (children.empty()) {
			return -1;
		}
		else {
			std::vector<int> vectorChildren(children.begin(), children.end());
			std::sort(vectorChildren.begin(), vectorChildren.end());
			return vectorChildren[0];
		}
	}

	int findLastIfChild(int lineNumber) {
		std::unordered_set<int> ifChildren = T::getInstance().getStatementList(lineNumber + 1);
		if (ifChildren.empty()) {
			return -1;
		}
		else {
			std::vector<int> vectorChildren(ifChildren.begin(), ifChildren.end());
			std::sort(vectorChildren.begin(), vectorChildren.end(), std::greater <>());
			return vectorChildren[0];
		}
	}

	int findFirstElseChild(int lineNumber) {
		std::unordered_set<int> ifChildren = T::getInstance().getStatementList(lineNumber + 1);
		std::unordered_set<int> allChildren = T::getInstance().getChild(lineNumber);
		if (ifChildren.empty() || allChildren.empty()) {
			return -1;
		}
		for (const auto& child : ifChildren) {
			allChildren.erase(child);
		}
		if (allChildren.empty()) {
			return -1;
		}
		std::vector<int> vectorChildren(allChildren.begin(), allChildren.end());
		std::sort(vectorChildren.begin(), vectorChildren.end());
		return vectorChildren[0];
	}

	int findLastElseChild(int lineNumber) {
		std::unordered_set<int> allChildren = T::getInstance().getChild(lineNumber);
		if (children.empty()) {
			return -1;
		}
		else {
			std::vector<int> vectorChildren(allChildren.begin(), allChildren.end());
			std::sort(vectorChildren.begin(), vectorChildren.end(), std::greater <>());
			return vectorChildren[0];
		}
	}

	// Returns all x such that Next*(lineNumber, x) is true
	std::unordered_set<int> getNextStar(int lineNumber) {
		if (!tempNextStarStorage.getNextStar(lineNumber).empty()) { 
			// this query has been done before, i will return you the result 
			return tempNextStarStorage.getNextStar(lineNumber);
		}
		else {
			// BFS all the next until all statements have been visitedat 
			std::queue<int> bfsQueue;
			std::vector<bool> visited(T::getInstance().getSizeStatement() + 1, false);
			visited[lineNumber] = true;
			bfsQueue.push(lineNumber);
			while (!bfsQueue.empty()) {
				int statementLine = bfsQueue.front();
				bfsQueue.pop();
				std::unordered_set<int> nextLines = T::getInstance().getNext(statementLine);
				for (int nextLine : nextLines) {
					tempNextStarStorage.insertNextStar(lineNumber, { nextLine });
					if (!visited[nextLine]) {
						// Statement have not been visited, and ChildStar for this statement has not been computed before
						bfsQueue.push(nextLine);
						visited[nextLine] = true;
					}
				}
			}
			return tempNextStarStorage.getNextStar(lineNumber);
		}
	}

	// Returns all x such that Next*(x, lineNumber) is true
	std::unordered_set<int> getPreviousStar(int lineNumber) {
		if (!tempNextStarStorage.getPreviousStar(lineNumber).empty()) {
			// this query has been done before, i will return you the result 
			return tempNextStarStorage.getPreviousStar(lineNumber);
		}
		else {
			// BFS all the previous until all statements have been visited
			std::queue<int> bfsQueue;
			std::vector<bool> visited(T::getInstance().getSizeStatement() + 1, false);
			visited[lineNumber] = true;
			bfsQueue.push(lineNumber);
			while (!bfsQueue.empty()) {
				int statementLine = bfsQueue.front();
				bfsQueue.pop();
				std::unordered_set<int> previousLines = T::getInstance().getPrevious(statementLine);
				for (int previousLine : previousLines) {
					tempNextStarStorage.insertPreviousStar(lineNumber, { previousLine });
					if (!visited[previousLine]) {
						bfsQueue.push(previousLine);
						visited[previousLine] = true;
					}

				}
			}
			return tempNextStarStorage.getPreviousStar(lineNumber);
		}
	}

	// Returns if Next*(firtLineNumber, secondLinNumber) is true
	bool isNextStar(int firstLineNumber, int secondLineNumber) {
		if (T::getInstance().isNext(firstLineNumber, secondLineNumber)) {
			return true;
		}
		else {
			if (!tempNextStarStorage.getNextStar(firstLineNumber).empty()) {
				return tempNextStarStorage.isNextStar(firstLineNumber, secondLineNumber);
			}
			else if (!tempNextStarStorage.getPreviousStar(secondLineNumber).empty()) {
				return tempNextStarStorage.isPreviousStar(secondLineNumber, firstLineNumber);
			}
			else {
				// has not been computed before for either firstLineNumber or secondLineNumber
				std::unordered_set<int> nextStarResults = getNextStar(firstLineNumber);
				return nextStarResults.find(secondLineNumber) != nextStarResults.end();
			}
		}
	}

	int getSizeNextStar() {
		return tempNextStarStorage.getSizeNextStar();
	}

	int getSizePreviousStar() {
		return tempNextStarStorage.getSizePreviousStar();
	}

	int getAreaNextStar() {
		return tempNextStarStorage.getAreaNextStar();
	}

	void clearNextStarCache() {
		tempNextStarStorage.clear();
	}
	
	void clearExtension() {
		nodeAdjacency_.clear();
		nodeIndexToLineNumber_.clear(); 
		lineNumberToNodeIndex_.clear();
	}

	// Returns all the line numbers x such that Affects(lineNumber, x) is true.
	std::unordered_set<int> getAffects(int lineNumber) {
		if (T::getInstance().getStatement(lineNumber) != "assign" ) {
			return {};
		}
		// find variable modified by lineNumber
		std::unordered_set<std::string> modifiedVariables = T::getInstance().getModifies(lineNumber);
		std::string modifiedVar = *(modifiedVariables.begin());
		std::unordered_set<int> varModifiedByStatements = T::getInstance().getModifiedBy(modifiedVar);
		
		std::queue<int> bfsQueue;
		std::vector<bool> visited(T::getInstance().getSizeStatement() + 1, false);
		for (int statement : varModifiedByStatements) {
			// set to true to make sure BFS wont visit aka blacklisting it.
			std::string statementType = T::getInstance().getStatement(statement);
			if (statementType != "while" && statementType != "if") {
				visited[statement] = true;
			}
		}

		// find out all statements that have a path from lineNumber to it such that no statements in between modifies the variable.
		visited[lineNumber] = true;
		bfsQueue.push(lineNumber);

		while (!bfsQueue.empty()) {
			int statementLine = bfsQueue.front();
			bfsQueue.pop();
			std::unordered_set<int> nextLines = T::getInstance().getNext(statementLine);
			for (int nextLine : nextLines) {
				std::string statementType = T::getInstance().getStatement(nextLine);
				if (statementType == "assign") {
					std::unordered_set<std::string> usedVariables = T::getInstance().getUses(nextLine);
					if (usedVariables.find(modifiedVar) != usedVariables.end()) {
						// if nextLine is an assign statement and also uses modifiedVar, then there is an Affects(linNumber, nextLine) r/s
						tempAffectsStorage.insertAffects(lineNumber, { nextLine });
					}
				}
				if (!visited[nextLine]) {
					// Statement have not been visited and it is not a blacklisted statement.
					bfsQueue.push(nextLine);
					visited[nextLine] = true;
				}
			}
		}
		return tempAffectsStorage.getAffects(lineNumber);
	}

	// Returns all the line numbers x such that Affects(x, lineNumber) is true.
	std::unordered_set<int> getAffectedBy(int lineNumber) {
		if (T::getInstance().getStatement(lineNumber) != "assign") {
			return {};
		}

		// find variables used by lineNumber
		std::unordered_set<std::string> usedVariables = T::getInstance().getUses(lineNumber);

		for (std::string usedVar : usedVariables) {
			std::unordered_set<int> usedVarModifiedByStatements = T::getInstance().getModifiedBy(usedVar);
			if (usedVarModifiedByStatements.empty()) {
				// this particular variable is used by lineNumber but has no statements that modifies it previously
				continue;
			}
			else {
				// BFS backwards to find all statements that modifies this usedVar and also have a path to lineNumber with no modification in between
				std::queue<int> bfsQueue;
				std::vector<bool> visited(T::getInstance().getSizeStatement() + 1, false);
				for (int statement : usedVarModifiedByStatements) {
					// set to true to make sure BFS wont visit aka blacklisting it.
					std::string statementType = T::getInstance().getStatement(statement);
					if (statementType != "while" && statementType != "if") {
						visited[statement] = true;
					}
				}

				visited[lineNumber] = true;
				bfsQueue.push(lineNumber);
				while (!bfsQueue.empty()) {
					int statementLine = bfsQueue.front();
					bfsQueue.pop();
					std::unordered_set<int> previousLines = T::getInstance().getPrevious(statementLine);
					for (int previousLine : previousLines) {
						std::string statementType = T::getInstance().getStatement(previousLine);
						if (statementType == "assign" && (usedVarModifiedByStatements.find(previousLine) != usedVarModifiedByStatements.end())) {
							// if its an assign statement, and its a statement that modifies the usedVar, then there is an Affects relationship
							tempAffectsStorage.insertAffectedBy(lineNumber, { previousLine });
						}
						if (!visited[previousLine]) {
							// Statement have not been visited and it is not a blacklisted statement.
							bfsQueue.push(previousLine);
							visited[previousLine] = true;
						}
					}
				}
			}

		}
		return tempAffectsStorage.getAffectedBy(lineNumber);
	}

	// Returns if Affects(firstLineNumber, secondLineNumber) is true.
	bool isAffects(int firstLineNumber, int secondLineNumber) {
		if ((T::getInstance().getStatement(firstLineNumber) != "assign") || (T::getInstance().getStatement(secondLineNumber) != "assign")) {
			// if either of the two statements are not assign statement, they can't have affects relationship
			return false;
		}
		std::unordered_set<std::string> firstStatementModifiedVariables = T::getInstance().getModifies(firstLineNumber);
		std::string firstStatementModifiedVar = *(firstStatementModifiedVariables.begin());
		std::unordered_set<std::string> secondStatementUsedVariables = T::getInstance().getUses(secondLineNumber);
		if (secondStatementUsedVariables.find(firstStatementModifiedVar) == secondStatementUsedVariables.end()) {
			// secondLineNumber does not use a variable that is modified by firstLineNumber
			return false;
		}

		if (!tempAffectsStorage.getAffects(firstLineNumber).empty()) {
			return tempAffectsStorage.isAffects(firstLineNumber, secondLineNumber);
		}
		else if (!tempAffectsStorage.getAffectedBy(secondLineNumber).empty()) {
			return tempAffectsStorage.isAffectedBy(secondLineNumber, firstLineNumber);
		}
		else {
			// has not been computed before for either firstLineNumber or secondLineNumber
			std::unordered_set<int> affectsResults = getAffects(firstLineNumber);
			return affectsResults.find(secondLineNumber) != affectsResults.end();
		}
	}

	// Returns all the line numbers x such that Affects*(lineNumber, x) is true.
	std::unordered_set<int> getAffectsStar(int lineNumber) {
		if (T::getInstance().getStatement(lineNumber) != "assign") {
			return {};
		}
		else if (tempAffectsStarStorage.hasKeyAffectsStar(lineNumber)) {
			return tempAffectsStarStorage.getAffectsStar(lineNumber);
		}
		int currentLineNumber;
		std::queue<int> bfsQueue;
		std::unordered_set<int> affectsResults;
		std::vector<bool> visited(T::getInstance().getSizeStatement() + 1, false);
		bfsQueue.push(lineNumber);
		while (!bfsQueue.empty()) {
			currentLineNumber = bfsQueue.front();
			bfsQueue.pop();
			affectsResults = getAffects(currentLineNumber);
			for (int affectedLineNumber : affectsResults) {
				if (!visited[affectedLineNumber]) {
					visited[affectedLineNumber] = true;
					tempAffectsStarStorage.insertAffectsStar(lineNumber, { affectedLineNumber });
					bfsQueue.push(affectedLineNumber);
				}
			}
		}
		return tempAffectsStarStorage.getAffectsStar(lineNumber);
	}

	// Returns all the line numbers x such that Affects*(x, lineNumber) is true.
	std::unordered_set<int> getAffectedByStar(int lineNumber) {
		if (T::getInstance().getStatement(lineNumber) != "assign") {
			return {};
		}
		else if (tempAffectsStarStorage.hasKeyAffectedByStar(lineNumber)) {
			return tempAffectsStarStorage.getAffectedByStar(lineNumber);
		}
		int currentLineNumber;
		std::queue<int> bfsQueue;
		std::unordered_set<int> affectsResults;
		std::vector<bool> visited(T::getInstance().getSizeStatement() + 1, false);
		bfsQueue.push(lineNumber);
		while (!bfsQueue.empty()) {
			currentLineNumber = bfsQueue.front();
			bfsQueue.pop();
			affectsResults = getAffectedBy(currentLineNumber);
			for (int affectedLineNumber : affectsResults) {
				if (!visited[affectedLineNumber]) {
					visited[affectedLineNumber] = true;
					tempAffectsStarStorage.insertAffectedByStar(lineNumber, { affectedLineNumber });
					bfsQueue.push(affectedLineNumber);
				}
			}
		}
		return tempAffectsStarStorage.getAffectedByStar(lineNumber);
	}

	// Returns all the line numbers x such that Affects*(firstLineNumber, secondLineNumber) is true.
	bool isAffectsStar(int firstLineNumber, int secondLineNumber) {
		// firstLineNumber or secondLineNumber is not an assign statement, so there will never be Affects* relationship between them
		if (T::getInstance().getStatement(firstLineNumber) != "assign" || T::getInstance().getStatement(secondLineNumber) != "assign") {
			return false;
		}
		std::unordered_set<int> storedResults;
		std::unordered_set<int> affectsResults;
		// getAffectsStar(firstLineNumber) has been computed before
		if (tempAffectsStarStorage.hasKeyAffectsStar(firstLineNumber)) {
			storedResults = tempAffectsStarStorage.getAffectsStar(firstLineNumber);
			if (storedResults.find(secondLineNumber) != storedResults.end()) {
				return true;
			}
			return false;
		}
		// getAffectedByStar(secondLineNumber) has been computed before
		else if (tempAffectsStarStorage.hasKeyAffectedByStar(secondLineNumber)) {
			storedResults = tempAffectsStarStorage.getAffectedByStar(secondLineNumber);
			if (storedResults.find(firstLineNumber) != storedResults.end()) {
				return true;
			}
			return false;
		}
		else {
			affectsResults = getAffectsStar(firstLineNumber);
			return affectsResults.find(secondLineNumber) != affectsResults.end();
		}
	}

	void clearAffectsCache() {
		tempAffectsStorage.clear();
	}

	void clearAffectsStarCache() {
		tempAffectsStarStorage.clear();
	}

	// Construct CFG for the entire program
	void constructProgramCFG() {
		int index = 0;
		int* nodeIndex = &index;
		std::vector<int> procedures = T::getInstance().getAllKeysProcedure();
		std::stack<int> callStack;
		for (int procedure : procedures) {
			constructProcedureCFG(procedure, callStack, nodeIndex);
		}
	}

	// (Recursively) Construct CFG for a given procedure, and extracts NextBipNode relationships
	std::unordered_set<int> constructProcedureCFG(int procedure, std::stack<int>& callStack, int* nodeIndex) {
		std::unordered_set<int> terminalNodes;
		std::unordered_set<int> terminalNodesOfCalledProcedure;
		std::unordered_set<int> procedureStatementList = T::getInstance().getProcedureStatementList(procedure);
		std::unordered_set<int> previouslySkippedWhileLines;
		std::unordered_set<int> previouslyVisitedWhileLines;
		int firstLine = *(procedureStatementList.begin());
		std::queue<std::pair<std::unordered_set<int>, int>> bfsQueue;
		if (!callStack.empty()) {
			int callingNode = callStack.top();
			bfsQueue.push({ { callingNode }, firstLine });
		}
		else {
			bfsQueue.push({ { }, firstLine });
		}
		while (!bfsQueue.empty()) {
			std::pair<std::unordered_set<int>, int> firstInQueue = bfsQueue.front();
			std::unordered_set<int> previousNodes = firstInQueue.first;
			int currentLineNumber = firstInQueue.second;
			// While statement has been visited at least twice
			if (previouslyVisitedWhileLines.count(currentLineNumber) != 0) {
				for (int previousNode : previousNodes) {
					std::unordered_set<int> currentNodes = lineNumberToNodeIndex_.at(currentLineNumber);
					if (nodeAdjacency_.find(previousNode) == nodeAdjacency_.end()) {
						nodeAdjacency_[previousNode] = { currentNodes };
					}
					else {
						for (int currentNode : currentNodes) {
							nodeAdjacency_[previousNode].insert(currentNode);
						}
					}
				}
			}
			else {
				int currentNode = (*nodeIndex);
				(*nodeIndex)++;
				nodeIndexToLineNumber_[currentNode] = currentLineNumber;
				if (lineNumberToNodeIndex_.find(currentLineNumber) == lineNumberToNodeIndex_.end()) {
					lineNumberToNodeIndex_[currentLineNumber] = { currentNode };
				}
				else {
					lineNumberToNodeIndex_[currentLineNumber].insert(currentNode);
				}
				for (int previousNode : previousNodes) {
					if (nodeAdjacency_.find(previousNode) == nodeAdjacency_.end()) {
						nodeAdjacency_[previousNode] = { currentNode };
					}
					else {
						nodeAdjacency_[previousNode].insert(currentNode);
					}
				}
				std::string statementType = T::getInstance().getStatement(currentLineNumber);
				if (statementType == "call") {
					std::string calledProcedureName = T::getInstance().getCall(currentLineNumber);
					int calledProcedure = T::getInstance().getKeyProcedure(calledProcedureName);
					std::unordered_set<int> calledProcedureStatementList = T::getInstance().getProcedureStatementList(calledProcedure);
					callStack.push(currentNode);
					terminalNodesOfCalledProcedure = constructProcedureCFG(calledProcedure, callStack, nodeIndex);
					if (!terminalNodesOfCalledProcedure.empty()) {
						std::unordered_set<int> nextLines = T::getInstance().getNext(currentLineNumber);
						if (nextLines.empty()) {
							for (int terminalNode : terminalNodesOfCalledProcedure) {
								terminalNodes.insert(terminalNode);
							}
						}
						else {
							int nextLine = *(nextLines.begin());
							bfsQueue.push({ terminalNodesOfCalledProcedure, nextLine });
						}
					}
					callStack.pop();
				}
				else {
					std::unordered_set<int> nextLines = T::getInstance().getNext(currentLineNumber);
					if (nextLines.empty()) {
						terminalNodes.insert(currentNode);
					}
					else if (statementType == "while") {
						if (previouslySkippedWhileLines.count(currentLineNumber) != 0) {
							previouslyVisitedWhileLines.insert(currentLineNumber);
						}
						else {
							previouslySkippedWhileLines.insert(currentLineNumber);
						}
						if (nextLines.size() == 1) {
							terminalNodes.insert(currentNode);
							bfsQueue.push({ { currentNode }, *(nextLines.begin()) });
						}
						else {
							for (int nextLine : nextLines) {
								bfsQueue.push({ { currentNode }, nextLine });
							}
						}
					}
					else {
						for (int nextLine : nextLines) {
							bfsQueue.push({ { currentNode }, nextLine });
						}
					}
				}
			}
			bfsQueue.pop();
		}
		return terminalNodes;
	}

	// Extracts all NextBip relationships
	void extractNextBip() {
		std::unordered_map<int, std::unordered_set<int>>::iterator nodeAdjacencyIt = nodeAdjacency_.begin();
		for (; nodeAdjacencyIt != nodeAdjacency_.end(); ++nodeAdjacencyIt) {
			int currentNode = nodeAdjacencyIt->first;
			int lineNumber = nodeIndexToLineNumber_.at(currentNode);
			std::unordered_set<int> nextNodes = nodeAdjacencyIt->second;
			std::unordered_set<int>::const_iterator nextNodesIt = nextNodes.begin();
			for (; nextNodesIt != nextNodes.end(); ++nextNodesIt) {
				int nextLineNumber = nodeIndexToLineNumber_.at(*nextNodesIt);
				T::getInstance().insertNextBip(lineNumber, { nextLineNumber });
			}
		}
	}

	// Extracts all NextBipNode* relationships
	void extractNextBipStar() {
		std::unordered_map<int, std::unordered_set<int>>::iterator nodeAdjacencyIt = nodeAdjacency_.begin();
		for (; nodeAdjacencyIt != nodeAdjacency_.end(); ++nodeAdjacencyIt) {
			int startingNode = nodeAdjacencyIt->first;
			int nodeLineNumber = nodeIndexToLineNumber_.at(startingNode);
			std::queue<int> bfsQueue;
			std::vector<bool> visited(nodeIndexToLineNumber_.size() + 1, false);
			visited[startingNode] = true;
			bfsQueue.push(startingNode);
			while (!bfsQueue.empty()) {
				int currentNode = bfsQueue.front();
				bfsQueue.pop();
				if (nodeAdjacency_.find(currentNode) != nodeAdjacency_.end()) {
					std::unordered_set<int> nextNodes = nodeAdjacency_.at(currentNode);
					std::unordered_set<int>::const_iterator nextNodesIt = nextNodes.begin();
					for (; nextNodesIt != nextNodes.end(); ++nextNodesIt) {
						int nextNode = *nextNodesIt;
						int nextLineNumber = nodeIndexToLineNumber_.at(nextNode);
						T::getInstance().insertNextBipStar(nodeLineNumber, { nextLineNumber });
						if (!visited[nextNode]) {
							bfsQueue.push(nextNode);
							visited[nextNode] = true;
						}
					}
				} 
			}
		}
	}

	// Extracts all AffectsBipNode relationships
	void extractAffectsBip() {
		std::unordered_map<int, std::unordered_set<int>>::iterator nodeAdjacencyIt = nodeAdjacency_.begin();
		for (; nodeAdjacencyIt != nodeAdjacency_.end(); ++nodeAdjacencyIt) {
			int startingNode = nodeAdjacencyIt->first;
			int nodeLineNumber = nodeIndexToLineNumber_.at(startingNode);
			if (T::getInstance().getStatement(nodeLineNumber) != "assign") {
				// if the current nodeLineNumber is not an assign statement, skip it.
				continue;
			}
			// find variable modified by nodeLineNumber
			std::unordered_set<std::string> modifiedVariables = T::getInstance().getModifies(nodeLineNumber);
			if (modifiedVariables.empty()) {
				continue;
			}
			std::string modifiedVar = *(modifiedVariables.begin());
			// find all statements that modifies the same variable
			std::unordered_set<int> varModifiedByStatements = T::getInstance().getModifiedBy(modifiedVar);
			// setting up the necessary data structures to BFS
			std::queue<int> bfsQueue;
			std::vector<bool> visited(nodeIndexToLineNumber_.size() + 1, false);
			for (int statement : varModifiedByStatements) {
				// set all statements that modifies the variable also to false so there is no path for BFS to continue through them
				std::string statementType = T::getInstance().getStatement(statement);
				if (statementType != "while" && statementType != "if" && statementType != "call") {
					std::unordered_set<int> nodesOfStatement = lineNumberToNodeIndex_.at(statement);
					for (int nodeOfStatement : nodesOfStatement) {
						visited[nodeOfStatement] = true;
					}
				}
			}
			// find out all statements that have a path from lineNumber to it such that no statements in between modifies the variable.
			visited[startingNode] = true;
			bfsQueue.push(startingNode);

			while (!bfsQueue.empty()) {
				int currentNode = bfsQueue.front();
				bfsQueue.pop();
				if (nodeAdjacency_.find(currentNode) != nodeAdjacency_.end()) {
					std::unordered_set<int> nextNodes = nodeAdjacency_.at(currentNode);
					std::unordered_set<int>::const_iterator nextNodesIt = nextNodes.begin();
					for (; nextNodesIt != nextNodes.end(); ++nextNodesIt) {
						int nextNode = *nextNodesIt;
						int nextLineNumber = nodeIndexToLineNumber_.at(nextNode);
						std::string statementType = T::getInstance().getStatement(nextLineNumber);
						if (statementType == "assign") {
							std::unordered_set<std::string> usedVariables = T::getInstance().getUses(nextLineNumber);
							if (usedVariables.find(modifiedVar) != usedVariables.end()) {
								// if nextLine is an assign statement and also uses modifiedVar, then there is an Affects(linNumber, nextLine) r/s
								T::getInstance().insertAffectsBipNode(startingNode, { nextNode });
								T::getInstance().insertAffectsBip(nodeLineNumber, { nextLineNumber });
							}
						}
						if (!visited[nextNode]) {
							// Statement have not been visited and it is not a blacklisted statement.
							bfsQueue.push(nextNode);
							visited[nextNode] = true;
						}
					}
				}
			}
		}
	}

	// Extracts all AffectsBip* relationships
	void extractAffectsBipStar() {
		std::vector<int> affectsBipKeys = T::getInstance().getAllKeysAffectsBipNode();
		std::vector<int>::const_iterator affectsBipKeysIt = affectsBipKeys.begin();
		for (; affectsBipKeysIt != affectsBipKeys.end(); ++affectsBipKeysIt) {
			int node = (*affectsBipKeysIt);
			int nodeLineNumber = nodeIndexToLineNumber_.at(node);
			std::queue<int> bfsQueue;
			std::vector<bool> visited(nodeIndexToLineNumber_.size() + 1, false);
			visited[node] = true;
			bfsQueue.push(node);
			while (!bfsQueue.empty()) {
				int currentNode = bfsQueue.front();
				bfsQueue.pop();
				std::unordered_set<int> affectsNodes = T::getInstance().getAffectsBipNode(currentNode);
				std::unordered_set<int>::const_iterator affectsNodesIt = affectsNodes.begin();
				for (; affectsNodesIt != affectsNodes.end(); ++affectsNodesIt) {
					int affectsNode = *affectsNodesIt;
					int affectsLineNumber = nodeIndexToLineNumber_.at(affectsNode);
					T::getInstance().insertAffectsBipStar(nodeLineNumber, { affectsLineNumber });
					if (!visited[affectsNode]) {
						bfsQueue.push(affectsNode);
						visited[affectsNode] = true;
					}
				}
			}
		}
	}
		
	// Checks if a string contains any numbers in it
	bool isNotNumber(const std::string& s) {
		bool has_only_digits = true;
		for (size_t n = 0; n < s.length(); n++)
		{
			if (!isdigit(s[n]))
			{
				has_only_digits = false;
				break;
			}
		}
		return has_only_digits;
	}

	// Checks if a string contains a space in it
	bool isContainSpace(std::string s) {
		bool containSpace = false;
		for (auto x : s) {
			if (x == ' ')
			{
				containSpace = true;
				break;
			}
		}
		return containSpace;
	}

	// Splits a string into a set of words
	std::unordered_set<std::string> splitBySpaces(std::string str) {
		std::unordered_set<std::string> output;
		std::string word = "";
		for (auto x : str) {
			if (x == ' ' || x == '<' || x == '>' || x == '=' || x == '!' || x == '|' || x == '&' || x == ';' || x == '+' || x == '-' || x == '*' || x == '/' || x == '%' || x == '(' || x == ')') {
				output.insert(word);
				word = "";
			} else {
				word.push_back(x);
			}
		}
		if (word != " ") {
			output.insert(word);
			return output;
		}
		else {
			return output;
		}
		return output;
	}
	
	// Extracts all variables used from a string containing variables (assignRHS)
	std::unordered_set<std::string> getVarUsed(std::string str) {
		//str.erase(remove(str.begin(), str.end(), ' '), str.end());
		str.push_back(';');
		std::unordered_set<std::string> output;
		std::string word = "";
		std::unordered_set<std::string> tokenized;
		tokenized = splitBySpaces(str);
		for (std::string s : tokenized) {
			if (isNotNumber(s)) {

			}
			else {
				output.insert(s);
			}
		}
		return output;
	}
};
