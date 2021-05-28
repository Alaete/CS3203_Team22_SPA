#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Query {

public:
    // Constructor and Deconstructor
    Query();
    Query(bool);
    ~Query();

    enum class ClauseType {
        NONE = 0,
        SELECT = 1,
        SUCH_THAT = 2,
        PATTERN = 3,
        WITH = 4
    };

    enum class DesignEntityType {
        ASSIGN = 0,
        CALL = 1,
        CONSTANT = 2,
        IF = 3,
        PRINT = 4,
        PROCEDURE = 5,
        READ = 6,
        STMT = 7,
        VARIABLE = 8,
        WHILE = 9,
        NONE = 10,
        WILDCARD = 11,
        PROG_LINE = 12
    };

    enum class DesignAbstractionType {
        FOLLOWS = 0,
        FOLLOWS_STAR = 1,
        MODIFIES = 2,
        PARENT = 3,
        PARENT_STAR = 4,
        USES = 5,
        CALLS = 6,
        CALLS_STAR = 7,
        NEXT = 8,
        NEXT_STAR = 9,
        AFFECTS = 10,
        AFFECTS_STAR = 11,
        NEXTBIP = 12,
        NEXTBIP_STAR = 13,
        AFFECTSBIP = 14,
        AFFECTSBIP_STAR = 15
    };

    enum class ExpressionType {
        PARTIAL_MATCH = 0,
        EXACT_MATCH = 1,
        NO_MATCH = 2
    };

    enum class ElementType {
        SYNONYM = 0,
        ATTRIBUTE = 1
    };

    enum class PatternAbstractionType {
        ASSIGN = 0,
        IF = 1,
        WHILE = 2
    };

    enum class ReferenceType {
        SYNONYM = 0,
        INTEGER = 1,
        WILDCARD = 2,
        QUOTATION = 3,
        ATTRIBUTE = 4
    };

    enum class ReferenceAttributeType {
        NONE = 0,
        PROCNAME = 1,
        VARNAME = 2,
        VALUE = 3,
        STMTNUM = 4
    };

    struct Element {
        ElementType elementType;
        ReferenceAttributeType elementAttribType;
        std::string synonymString;
    };

    struct Expression {
        ExpressionType exprType;
        std::string exprString;
    };

    struct Reference {
        DesignEntityType refDentityType;
        ReferenceAttributeType refAttribType;
        ReferenceType refType;
        std::string refString;
        std::string synonym;
    };

    struct Clause {
        ClauseType clauseType;
        DesignAbstractionType designAbstractionType;
        Reference leftRef;
        Reference rightRef;
        PatternAbstractionType patternAbstractionType;
        Expression expr;
        int staticScore;
        int dynamicScore;
    };

    void reset(bool);
    void setIsValid(bool);
    void setIsSelectBoolean(bool);
    void setIsValidSemantic(bool);
    void setIsValidSyntax(bool);

    // Methods to add results to query object
    void addSynonymTable(std::unordered_map<std::string, Query::DesignEntityType>& synonymsTable);
    void addClauses(std::vector<Clause>& clauses);
    void addSelectedSynonyms(std::vector<Element>& selectedSynonym);

    // Getter methods
    std::unordered_map<std::string, DesignEntityType> getSynonymsTable();
    std::vector<Clause> getClauses();
    std::vector<Element> getSelectedSynonyms();
    bool getIsValid();
    bool getIsValidSemantic();
    bool getIsValidSyntax();
    bool getIsSelectBoolean();

private:
    bool isValid;
    bool isValidSemantic;
    bool isValidSyntax;
    bool isSelectBoolean;
    std::unordered_map<std::string, DesignEntityType> synonymsTable;
    std::vector<Clause> clauses;
    std::vector<Element> selectedSynonyms;
};

