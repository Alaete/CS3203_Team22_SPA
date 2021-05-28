#include "Optimiser.h"

// Constructor and Deconstructor
Optimiser::Optimiser() {}
Optimiser::~Optimiser() {}

// Instance of Optimizer
Optimiser& Optimiser::getInstance() {
    static Optimiser instance;
    return instance;
}

// todo
void Optimiser::optimise(std::vector<Query::Clause>& clauseList) {
    // assign static score to clauses
    for (Query::Clause c : clauseList) {
        c.staticScore = getStaticScore(c);
    }
    groupClauses(clauseList);
    sortClausesInGroups();
    clauseList = unpackGroups();
};

// sort clauses in groups by combined scores
void Optimiser::sortClausesInGroups() {
    for (std::vector<Query::Clause> group : groups) {
        sort(group.begin(), group.end(), compareClauseByScore);
    }
}

// two scores will be multiplied to produce a combined score, and compare by combined scores
bool Optimiser::compareClauseByScore(Query::Clause firstClause, Query::Clause secondClause) {
    if (firstClause.staticScore != secondClause.staticScore) {
        return firstClause.staticScore < secondClause.staticScore;
    }
    else {
        firstClause.dynamicScore = firstClause.staticScore * getDynamicScore(firstClause);
        secondClause.dynamicScore = secondClause.staticScore * getDynamicScore(secondClause);
        if (firstClause.dynamicScore == secondClause.dynamicScore) {
            firstClause.dynamicScore *= getDynamicScoreSizeArea(firstClause);
            secondClause.dynamicScore *= getDynamicScoreSizeArea(secondClause);
        }
        return firstClause.dynamicScore < secondClause.dynamicScore;
    }
}

// assign static scores to the clause types/rs
int Optimiser::getStaticScore(Query::Clause& clause) {
    Query::ClauseType clauseType = clause.clauseType;
    Query::DesignAbstractionType designAbstractionType = clause.designAbstractionType;
    if (clauseType == Query::ClauseType::SUCH_THAT) {
        switch (designAbstractionType) {
        case Query::DesignAbstractionType::AFFECTS:
            return affectsScore;
        case Query::DesignAbstractionType::AFFECTSBIP:
            return affectsBipScore;
        case Query::DesignAbstractionType::AFFECTSBIP_STAR:
            return affectsBipStarScore;
        case Query::DesignAbstractionType::AFFECTS_STAR:
            return affectsStarScore;
        case Query::DesignAbstractionType::CALLS:
            return callsScore;
        case Query::DesignAbstractionType::CALLS_STAR:
            return callsStarScore;
        case Query::DesignAbstractionType::FOLLOWS:
            return followsScore;
        case Query::DesignAbstractionType::FOLLOWS_STAR:
            return followsStarScore;
        case Query::DesignAbstractionType::MODIFIES:
            return modifiesScore;
        case Query::DesignAbstractionType::NEXT:
            return nextScore;
        case Query::DesignAbstractionType::NEXTBIP:
            return nextBipScore;
        case Query::DesignAbstractionType::NEXTBIP_STAR:
            return nextBipStarScore;
        case Query::DesignAbstractionType::NEXT_STAR:
            return nextStarScore;
        case Query::DesignAbstractionType::PARENT:
            return parentScore;
        case Query::DesignAbstractionType::PARENT_STAR:
            return parentsStarScore;
        case Query::DesignAbstractionType::USES:
            return usesScore;
        default:
            return invalidScore;
        }
    }
    else if (clauseType == Query::ClauseType::PATTERN) {
        Query::PatternAbstractionType patternAbstractionType = clause.patternAbstractionType;
        switch (patternAbstractionType) {
        case Query::PatternAbstractionType::ASSIGN:
            return patternAssignScore;
        case Query::PatternAbstractionType::IF:
            return patternIfScore;
        case Query::PatternAbstractionType::WHILE:
            return patternWhileScore;
        default:
            return invalidScore;
        }
    }
    else if (clauseType == Query::ClauseType::WITH) {
        return withScore;
    }
    else {
        return invalidScore;
    }
};

int Optimiser::getDynamicScore(Query::Clause clause) {
    if (clause.leftRef.refType == Query::ReferenceType::SYNONYM && clause.rightRef.refType == Query::ReferenceType::SYNONYM) {
        return 3;
    }
    else if (clause.leftRef.refType == Query::ReferenceType::SYNONYM || clause.rightRef.refType == Query::ReferenceType::SYNONYM) {
        return 2;
    }
    else {
        return 1;
    }
}

// todo: take from jiahao
int Optimiser::getDynamicScoreSizeArea(Query::Clause clause) {
    Query::ClauseType clauseType = clause.clauseType;
    Query::DesignAbstractionType designAbstractionType = clause.designAbstractionType;
    if (clauseType == Query::ClauseType::SUCH_THAT) {
        switch (designAbstractionType) {
        case Query::DesignAbstractionType::AFFECTS:
            //return QueryDEInterface::getAffectsArea();
            return 0;
        case Query::DesignAbstractionType::AFFECTSBIP:
            //return QueryDEInterface::getAffectsBipArea();
            return 0;
        case Query::DesignAbstractionType::AFFECTSBIP_STAR:
            //return QueryDEInterface::getAffectsBipStarArea();
            return 0;
        case Query::DesignAbstractionType::AFFECTS_STAR:
            //return QueryDEInterface::getAffectsStarArea();
            return 0;
        case Query::DesignAbstractionType::CALLS:
            return QueryPKBInterface::getInstance().getAreaCalls();
        case Query::DesignAbstractionType::CALLS_STAR:
            return QueryPKBInterface::getInstance().getAreaCallsStar();
        case Query::DesignAbstractionType::FOLLOWS:
            return QueryPKBInterface::getInstance().getSizeFollows();
        case Query::DesignAbstractionType::FOLLOWS_STAR:
            return QueryPKBInterface::getInstance().getAreaFollowsStar();
        case Query::DesignAbstractionType::MODIFIES:
            return QueryPKBInterface::getInstance().getAreaModifies();
        case Query::DesignAbstractionType::NEXT:
            return QueryPKBInterface::getInstance().getAreaNext();
        case Query::DesignAbstractionType::NEXTBIP:
            //return QueryPKBInterface::getInstance().getAreaNextBip();
        case Query::DesignAbstractionType::NEXTBIP_STAR:
            //return QueryPKBInterface::getInstance().getAreaNextBipStar();
        case Query::DesignAbstractionType::NEXT_STAR:
            return QueryDEInterface::getInstance().getAreaNextStar();
        case Query::DesignAbstractionType::PARENT:
            return QueryPKBInterface::getInstance().getSizeParent();
        case Query::DesignAbstractionType::PARENT_STAR:
            return QueryPKBInterface::getInstance().getAreaParentStar();
        case Query::DesignAbstractionType::USES:
            return QueryPKBInterface::getInstance().getAreaUses();
        default:
            return invalidScore;
        }
    }
    else if (clauseType == Query::ClauseType::PATTERN) {
        Query::PatternAbstractionType patternAbstractionType = clause.patternAbstractionType;
        switch (patternAbstractionType) {
        case Query::PatternAbstractionType::ASSIGN:
            return QueryPKBInterface::getInstance().getSizeAssign();
        case Query::PatternAbstractionType::IF:
            return QueryPKBInterface::getInstance().getAreaIf();
        case Query::PatternAbstractionType::WHILE:
            return QueryPKBInterface::getInstance().getAreaWhile();
        default:
            return invalidScore;
        }
    }
    else if (clauseType == Query::ClauseType::WITH) {
        return withScore;
    }
    else {
        return invalidScore;
    }
}

void Optimiser::groupClauses(std::vector<Query::Clause>& clauseList) {
    std::vector<Query::Clause> clausesNoSynonyms;
    std::vector<Query::Clause> clauses1Synonym;
    std::vector<Query::Clause> clauses2Synonym;
    
    for (Query::Clause c : clauseList) {
        if (c.leftRef.refType != Query::ReferenceType::SYNONYM && c.rightRef.refType != Query::ReferenceType::SYNONYM) {
            clausesNoSynonyms.push_back(c);
        }
        else if (c.leftRef.refType == Query::ReferenceType::SYNONYM && c.rightRef.refType == Query::ReferenceType::SYNONYM) {
            clauses2Synonym.push_back(c);
        }
        else if (c.leftRef.refType == Query::ReferenceType::SYNONYM || c.rightRef.refType == Query::ReferenceType::SYNONYM) {
            clauses1Synonym.push_back(c);
        }
        else {

        }
    }

    groups.clear();
    groups.push_back(clausesNoSynonyms);
    groups.push_back(clauses1Synonym);
    groups.push_back(clauses2Synonym);
}

std::vector<Query::Clause> Optimiser::unpackGroups() {
    std::vector<Query::Clause> sortedList;
    sortedList.clear();
    for (Query::Clause c : groups[0]) {
        sortedList.push_back(c);
    }
    for (Query::Clause c : groups[1]) {
        sortedList.push_back(c);
    }
    for (Query::Clause c : groups[2]) {
        sortedList.push_back(c);
    }
    return sortedList;
}
