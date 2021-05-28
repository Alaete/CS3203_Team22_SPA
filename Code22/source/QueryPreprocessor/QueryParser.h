#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include "Query.h"

class QueryParser {

public:

    enum class DataType {
        NAME,
        NUMBER
    };

    // Making a QueryParser singleton
    ~QueryParser();

    static QueryParser& getInstance();
    QueryParser(QueryParser const&) = delete;
    void operator=(QueryParser const&) = delete;

    // Public API for QueryParser
    Query& parseQuery(const std::string& query_str);

    // Exception class to handle syntax error
    struct SyntaxErrorException : public std::exception {
        std::string errorMessage;
        SyntaxErrorException(std::string error) : errorMessage(error) {}
        ~SyntaxErrorException() throw () {}
        const char* what() const throw () { return errorMessage.c_str(); }
    };

    // Exception class to handle semantic error
    struct SemanticErrorException : public std::exception {
        std::string message;
        SemanticErrorException(std::string errorMessage) : message(errorMessage) {}
        ~SemanticErrorException() throw() {};
        const char* what() const throw() { return message.c_str(); }
    };

private:
    std::string queryString;
    unsigned int startIndex = 0;
    unsigned int endIndex = 0;
    std::unordered_map<std::string, Query::DesignEntityType> synonymsTable;
    std::vector<Query::Clause> clauses;
    std::vector<Query::Element> selectedSynonyms;
    Query result;
    Query& GetQueryResult();

    std::unordered_set<char> arithmeticSymbols{ '+', '-', '*', '/', '%', '(', ')' };

    // Makes QueryParser a singleton
    QueryParser();

    // Resets QueryParser before next query
    void reset(bool);
    void setInvalidQuery();

    // Check if synonym name is in the synonym table
    bool containSynonymName(std::string& synonym);

    void extractAndAddToSynonymTable(std::vector<std::string>& synonymsList, Query::DesignEntityType& designEntityType);

    bool isInteger(std::string& synonym);
    bool isSynonym(std::string synonym);
    bool invalidSelectBoolean = false;
    bool isSelectBoolean = false;
    bool isValidSemantic = true;
    bool isValidSyntax = false;

    // Trim leading and trailing spaces
    std::string trim(std::string& str);
    // Split Query and Synonym by delimiters
    std::vector<std::string> splitQuery(std::string& str, char delimiter);
    std::vector<std::string> splitSynonym(std::string& str, char delimiter);
    std::string getNextToken(std::string& stmt, char delim1, char delim2, bool isLast);
    std::string getExpression(std::string& stmt);

    // Parsing Methods
    void parsePatternClause(std::string& stmt);
    void parseDeclaration(std::string& declaration);
    void parseSelect(std::string& stmt);
    void parseSelectedSynonyms(std::string& stmt);
    void parseSuchThatClause(std::string& stmt);
    void parseClauses(std::string& stmt, std::string prevClauseType);
    void parseWithClause(std::string& stmt);
    void parseWithRef(Query::Reference& clauseRef, std::string& ref);
    void parsePatternAssignClause(Query::Clause& clause, std::string& ref, std::string& entRef);
    void parsePatternIfClause(Query::Clause& clause, std::string& ref);
    void parsePatternWhileClause(Query::Clause& clause, std::string& ref);

    void createClause(Query::Clause& clause, Query::ClauseType clauseType);
    Query::Reference getReference(std::string& ref);
    Query::Element getSynonymAndAttributes(std::string& synonym);

    void assignExpressionTypeToClause(Query::Clause& clause, std::string& expr);
    // Get Design Entity/Abstraction Types
    Query::DesignEntityType getDesignEntity(std::string& type);
    Query::DesignAbstractionType getDesignAbstractionType(std::string& type);
    Query::DesignEntityType getDesignEntityTypeFromTable(std::string& ref);
    Query::ReferenceAttributeType getReferenceAttributeType(std::string& ref);

    // Methods for validation
    bool isValidDesignAbstractReference(Query::DesignAbstractionType designAbstractType,
        Query::Reference leftRef, Query::Reference rightRef);
    bool isValidSynonymAndAttribute(Query::ReferenceAttributeType attribute, Query::DesignEntityType designEntityType);
    void validateQuotes(std::string target, std::string errorString);
    std::vector<std::string> tokenizeExpression(std::string expression);
    void validateExpression(std::vector<std::string> tokens, std::string errorString);
    void validatePatternClauseReference(std::string& leftRef, std::string& rightRef);
    void validateWithReferences(Query::Clause& clause);
    DataType getDataType(Query::ReferenceType refType, Query::ReferenceAttributeType attribType);

    // For checking purposes
    void printSynonymTable();

    // Clauses Types
    const std::string keywordSelect = "Select";
    const std::string clauseSuch = "such";
    const std::string clauseThat = "that";
    const std::string clausePattern = "pattern";
    const std::string clauseNone = "none";
    const std::string clauseAnd = "and";
    const std::string clauseWith = "with";

    // Design Entities
    const std::string designEntityStmt = "stmt";
    const std::string designEntityRead = "read";
    const std::string designEntityPrint = "print";
    const std::string designEntityCall = "call";
    const std::string designEntityWhile = "while";
    const std::string designEntityIf = "if";
    const std::string designEntityAssign = "assign";
    const std::string designEntityVariable = "variable";
    const std::string designEntityConstant = "constant";
    const std::string designEntityProcedure = "procedure";
    const std::string designEntityProgLine = "prog_line";

    // Design Abstractions
    const std::string designAbstractFollows = "Follows";
    const std::string designAbstractFollowsStar = "Follows*";
    const std::string designAbstractModifies = "Modifies";
    const std::string designAbstractParent = "Parent";
    const std::string designAbstractParentStar = "Parent*";
    const std::string designAbstractUses = "Uses";
    const std::string designAbstractCalls = "Calls";
    const std::string designAbstractCallsStar = "Calls*";
    const std::string designAbstractNext = "Next";
    const std::string designAbstractNextStar = "Next*";
    const std::string designAbstractAffects = "Affects";
    const std::string designAbstractAffectsStar = "Affects*";
    const std::string designAbstractNextBip = "NextBip";
    const std::string designAbstractNextBipStar = "NextBip*";
    const std::string designAbstractAffectsBip = "AffectsBip";
    const std::string designAbstractAffectsBipStar = "AffectsBip*";

    // Attributes
    const std::string attributeStmt = "stmt#";
    const std::string attributeProcName = "procName";
    const std::string attributeVarName = "varName";
    const std::string attributeValue = "value";
    const char keywordSpace = ' ';
    const std::string keywordWildcard = "_";
    const std::string keywordQuotation = "\"";
};

