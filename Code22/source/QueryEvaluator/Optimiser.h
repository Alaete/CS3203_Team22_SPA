#pragma once

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

#include "../QueryPreprocessor/Query.h"
#include "QueryDEInterface.h"
#include "QueryPKBInterface.h"

class Optimiser {
public:
    // Making Optimizer singleton
    ~Optimiser();

    static Optimiser& getInstance();
    Optimiser(Optimiser const&) = delete;
    void operator=(Optimiser const&) = delete;

    // Public API
    void optimise(std::vector<Query::Clause>& clauseList);

private:
    Optimiser();
    std::vector<std::vector<Query::Clause>> groups;

    int getStaticScore(Query::Clause& clause);
    static int getDynamicScore(Query::Clause clause);
    static int getDynamicScoreSizeArea(Query::Clause clause);
    static bool compareClauseByScore(Query::Clause firstClause, Query::Clause secondClause);
    void sortClausesInGroups();
    void groupClauses(std::vector<Query::Clause>& clauseList);
    std::vector<Query::Clause> unpackGroups();

    // Static scores
    static const int withScore = 0;
    static const int followsScore = 1;
    static const int followsStarScore = 3;
    static const int patternIfScore = 2;
    static const int patternWhileScore = 2;
    static const int patternAssignScore = 3;
    static const int parentScore = 2;
    static const int usesScore = 2;
    static const int modifiesScore = 2;
    static const int nextScore = 2;
    static const int parentsStarScore = 3;
    static const int callsStarScore = 3;
    static const int callsScore = 2;
    static const int nextStarScore = 4;
    static const int affectsScore = 5;
    static const int affectsStarScore = 6;
    static const int affectsBipScore = 6;
    static const int affectsBipStarScore = 6;
    static const int nextBipScore = 6;
    static const int nextBipStarScore = 6;
    static const int invalidScore = INT_MAX;
};