#include "Query.h"

Query::Query() : Query(true) {}
Query::Query(bool isValid) : isValid(isValid) {}
Query::~Query() {}

void Query::reset(bool isValid) {
    setIsValid(isValid);
    setIsSelectBoolean(false);
    setIsValidSyntax(isValid);
    synonymsTable.clear();
    clauses.clear();
}

void Query::setIsValid(bool isValid) {
    this->isValid = isValid;
}

void Query::setIsSelectBoolean(bool isSelectBoolean) {
    this->isSelectBoolean = isSelectBoolean;
}

void Query::setIsValidSemantic(bool isValidSemantic) {
    this->isValidSemantic = isValidSemantic;
};

void Query::setIsValidSyntax(bool isValidSyntax) {
    this->isValidSyntax = isValidSyntax;
};

bool Query::getIsValid() {
    return this->isValid;
}

bool Query::getIsSelectBoolean() {
    return this->isSelectBoolean;
}

bool Query::getIsValidSemantic() {
    return this->isValidSemantic;
};

bool Query::getIsValidSyntax() {
    return this->isValidSyntax;
};

void Query::addSynonymTable(std::unordered_map<std::string, Query::DesignEntityType>& synonymsResult) {
    synonymsTable = synonymsResult;
};

void Query::addClauses(std::vector<Clause>& clausesResult) {
    clauses = clausesResult;
};

void Query::addSelectedSynonyms(std::vector<Element>& selectedResult) {
    selectedSynonyms = selectedResult;
};

std::unordered_map<std::string, Query::DesignEntityType> Query::getSynonymsTable() {
    return synonymsTable;
}

std::vector<Query::Clause> Query::getClauses() {
    return clauses;
}

std::vector<Query::Element> Query::getSelectedSynonyms() {
    return selectedSynonyms;
}
