#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <iostream>

#include "../QueryPreprocessor/Query.h"
#include "../QueryUtil.h"
#include "Optimiser.h"
#include "QueryPKBInterface.h"
#include "QueryDEInterface.h"
#include "../ShuntingYard.h"

class QueryEvaluator {
private:
    //Singleton Implementation
    QueryEvaluator(); // Prevent construction
    QueryEvaluator(const PKB&); // Prevent construction by copying
    QueryEvaluator& operator=(const PKB&); // Prevent assignment
    ~QueryEvaluator(); // Prevent unwanted destruction
public:
    bool isOptimize = false;

    static QueryEvaluator& QueryEvaluator::getInstance() {
        static QueryEvaluator instance;
        return instance;
    }

    //Solve Wrapper Function.
    //This function takes in a Query object, solves it, and returns a formatted string containing the answer to the query.
    std::list<std::string> solveQuery(Query query);

    std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_set<std::string>>>> answerTable;
    std::vector<Query::Clause> clauseList;
    std::unordered_map<std::string, Query::DesignEntityType> synTable;
    std::unordered_map<std::string, std::unordered_set<std::string>> evaluatedSynonyms;

    //Solve Helper Functions.

    //This function solves a SELECT clause
    std::list<std::string> solveSelectClause(std::vector<Query::Element> selectedSynonym, bool queryBooleanReturn, bool isReturnTypeBoolean);

    std::list<std::string> solveSelectTuple(std::vector<Query::Element> selectedSynonym);

    //This function solves a SUCH_THAT clause
    bool solveSuchThatClause(Query::Clause clause);

    //This function solves a PATTERN clause
    bool solvePatternClause(Query::Clause clause);

    bool solveIfPatternClause(Query::Clause c);

    bool solveWhilePatternClause(Query::Clause c);

    bool solveAssignPatternClause(Query::Clause clause);

    //This function solves a WITH clause
    bool solveWithClause(Query::Clause clause);

    //This function looks for a reference that has a valid referenceAttributeType.
    std::pair<std::vector<std::string>, bool> findReferenceAttribute(std::string refString, Query::ReferenceAttributeType refAttribType, Query::ReferenceType refType, Query::DesignEntityType refDentityType);
    std::pair<std::vector<std::string>, bool> findReferenceAttributeString(Query::DesignEntityType type);
    std::vector<std::string> findReferenceAttributeInt(Query::DesignEntityType type);

    //This function looks for references that have valid referenceAttributeTypes and compares their results. Returns true if there is at least one similarity.
    bool findAndCompareWithSearchResults(Query::Reference leftRef, Query::Reference rightRef);
    bool findAndCompareWithSearchResults(Query::Reference leftRef, std::string rightRefString);

    //This function looks for elements in the left vector that is not in the right vector, and removes them from the answerTable.
    void removeWithDifference(Query::Reference leftRef, Query::Reference rightRef, std::vector<std::string> leftResults, std::vector<std::string> rightResults);

    //These functions return the keys of a value if applicable. Otherwise, they just return the value.
    std::string QueryEvaluator::getKeyOrValue(Query::Reference leftRef, std::string value);
    std::vector<std::string> getKeysOrValues(Query::Reference leftRef, std::string values);
    std::pair<std::vector<std::string>, bool> getKeysOrValues(Query::Reference leftRef, std::vector<std::string> values);

    //This function retrieves the DesignEntityType of a synonym, returning NONE if the synonym is not found in the synonymTable.
    Query::DesignEntityType getSynonymType(std::string syn);

    //This function calls the relevant PQL2PKB interface functions to retrieve the possible values of a synonym.
    std::vector<std::string> getDesignEntityValues(std::string ent, Query::DesignEntityType type);

    //This function checks that the ent input is of the DesignEntityType of the type input.
    bool assertDesignEntityType(std::string ent, Query::DesignEntityType type);

    //This function calls the relevant PQL2PKB interface functions to retrieve the possible values of a synonym that matches the design abstraction
    std::vector<std::string> getDesignAbstractionValues(Query::DesignAbstractionType dAT, std::string name, Query::DesignEntityType type, bool isReverse);

    //This function calls the relevant PQL2PKB interface functions to assert that the design abstraction exists between 2 synonyms
    bool assertDesignAbstractionValues(Query::DesignAbstractionType dAT, std::string var1, std::string var2);

    //This function takes in a clauseList reference and sorts the clauseList inside based on the optimal evaluation order
    void optimiseClauseList(std::vector<Query::Clause>& clauseList);

    //This function attempts to remove the entry answerTable[var1][var1value][var2][var2value] and related entry answerTable[var2][var2value]
    void answerTableCleanRemove(std::string var1, std::string var1value, std::string var2, std::string var2value);
    // This function arrempts to remove the entry answerTable[var1][var1value] and will call answerTableCleanRemove for all answerTable[var1][var1value][x][x's value] and answerTable[x][x's value][var1][var1value]
    void answerTableCleanRemove(std::string var1, std::string var1value);

    //This function searches the assignString for the exprString
    bool isPartialMatch(std::string assignString, std::string exprString);

    //Thif function takes in a string of literals/operators separated by spaces and tokenizes them into a list of strings
    std::vector<std::string> splitBySpaces(std::string str);

	bool IsDATEmpty(Query::DesignAbstractionType dAT);

	std::string evaluateAttribute(Query::ReferenceAttributeType elemType, std::string synonym, std::string synonymValue, Query::DesignEntityType synType);

    bool isSynonymEvaluated(std::string synonym);
    bool isSynonymEvaluatedAlone(std::string synonym);
    bool isSynonymEvaluatedTogether(std::string synonym1, std::string synonym2);
    void setSynonymEvaluated(std::string synonym);
    void setSynonymsEvaluatedTogether(std::string synonym1, std::string synonym2);

    bool isEvaluatedSeparately(Query::Element elem, std::vector<Query::Element> selectedSynonyms);

    std::string buildElementString(Query::Element e);

    std::vector<std::string> extractValue(std::string synonym);
    std::unordered_map<std::string, std::vector<std::string>> extractPairValue(std::string synonym1, std::string synonym2);

    void tightenAnswerTable(std::string syn1, std::string syn2);
    void tightenAnswerTable();

    void printAnswerTable();
    void printSynonymEvaluatedTable();
};

