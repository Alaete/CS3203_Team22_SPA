#include "QueryEvaluator.h"

QueryEvaluator::QueryEvaluator() {}
QueryEvaluator::~QueryEvaluator() {}

std::list<std::string> QueryEvaluator::solveQuery(Query query) {
    //Initialise
    answerTable.clear();
    evaluatedSynonyms.clear();
    QueryDEInterface::getInstance().clearTemporaryCache();
    std::list<std::string> emptyAnswer;

    //Initializations from Query object
    bool isQueryInvalid = !query.getIsValid();
    bool isValidSyntax = query.getIsValidSyntax();
    bool isValidSemantic = query.getIsValidSemantic();
    synTable = query.getSynonymsTable();
    std::vector<Query::Clause> clauseList = query.getClauses();
    std::vector<Query::Element> selectedSyn = query.getSelectedSynonyms();
    
    bool isReturnTypeBoolean = query.getIsSelectBoolean();

    //This is initialized to true so a select BOOLEAN query with no other clauses will return TRUE.
    bool queryBooleanReturn = true;

    //If Query is invalid, return an empty vector of strings.
    if (isQueryInvalid) {
        return emptyAnswer;
    }
    if (!isValidSyntax) {
        return emptyAnswer;
    }
    if (!isValidSemantic) {
        if (isReturnTypeBoolean) {
            return { "FALSE" };
        }
    }

    optimiseClauseList(clauseList);

    if (clauseList.size() > 0) {
        //Solve remaining clauses.
        for (Query::Clause c : clauseList) {
            switch (c.clauseType) {

            case Query::ClauseType::PATTERN: {
                bool isPatternFound = solvePatternClause(c);
                queryBooleanReturn = queryBooleanReturn && isPatternFound;
                break;
            }
            case Query::ClauseType::SUCH_THAT: {
                bool isClauseResolved = solveSuchThatClause(c);
                queryBooleanReturn = queryBooleanReturn && isClauseResolved;
                break;
            }
            //To be completed
            case Query::ClauseType::WITH: {
                bool isClauseResolved = solveWithClause(c);
                
                if (c.leftRef.refType == Query::ReferenceType::SYNONYM && c.rightRef.refType == Query::ReferenceType::SYNONYM && !isSynonymEvaluatedTogether(c.leftRef.refString, c.rightRef.refString)) {
                    tightenAnswerTable();
                }
                
                queryBooleanReturn = queryBooleanReturn && isClauseResolved;
                break;
            }

            //These 2 cases should not occur.
            case Query::ClauseType::NONE: {}
            case Query::ClauseType::SELECT: {}
            default:
                break;
            }
            //If any clause evaluates to false, evaluation can be cut short.
            if (!queryBooleanReturn) {
                return solveSelectClause(selectedSyn, queryBooleanReturn, isReturnTypeBoolean);
            }
        }
    }

    std::list<std::string> answer = solveSelectClause(selectedSyn, queryBooleanReturn, isReturnTypeBoolean);

    answerTable.clear();
    evaluatedSynonyms.clear();
    QueryDEInterface::getInstance().clearTemporaryCache();
    return answer;
}

void QueryEvaluator::printAnswerTable() {
    std::cout << "PRINTING ANSWER TABLE\n";
    for (auto v : answerTable) {
        auto var1name = v.first;
        for (auto v2 : answerTable[var1name]) {
            auto var1value = v2.first;
            for (auto v3 : answerTable[var1name][var1value]) {
                auto var2name = v3.first;
                std::cout << "syn - syn pair of: " << var1name << " && " << var2name << "\n";
                std::cout << "results:";
                for (auto v4 : answerTable[var1name][var1value][var2name]) {
                    std::cout << " (" << var1value << ", " << v4 << ")";
                }
                std::cout << "\n";
            }
        }
    }
}

void QueryEvaluator::printSynonymEvaluatedTable() {
    std::cout << "PRINTING SYNONYMS EVALUATED TABLE\n";
    for (auto s : evaluatedSynonyms) {
        auto s1 = s.first;
        for (auto v2 : evaluatedSynonyms[s1]) {
            std::cout << "(" << s1 << ", " << v2 << ") evaluated Together\n";
        }
    }
    std::cout << "\n";
}

bool QueryEvaluator::isPartialMatch(std::string assignString, std::string exprString) {
    bool isPMatch = false;
    std::vector<std::string> assignVector = splitBySpaces(assignString);
    std::vector<std::string> exprVector = splitBySpaces(exprString);
    // vector.size() is unsigned
    for (unsigned int i = 0; i < assignVector.size(); i++) {
        //Any word in assignVector is equivalent to the first word in exprVector
        if (assignVector[i].compare(exprVector[0]) == 0) {
            bool match = true;
            //Iterate both vectors by 1 step, checking along the way for it there is a match
            int j = 1;
            while (match == true && j < exprVector.size() && j < (assignVector.size() - i)) {
                if (assignVector[i + j].compare(exprVector[j]) != 0) {
                    match = false;
                }
                else {
                    match = true;
                }
                j++;
            }
            if (match == true && j == exprVector.size()) {
                isPMatch = true;
            }
        }
    }
    return isPMatch;
}

std::string QueryEvaluator::evaluateAttribute(Query::ReferenceAttributeType elemType, std::string synonym, std::string synonymValue, Query::DesignEntityType synType) {
    std::string elementString;
    switch (elemType) {
    case Query::ReferenceAttributeType::PROCNAME : {
        if (synType == Query::DesignEntityType::PROCEDURE) {
            elementString = synonymValue;
        }
        else if (synType == Query::DesignEntityType::CALL) {
            elementString = QueryPKBInterface::getInstance().getCall(synonymValue);
        }
        break;
    }
    case Query::ReferenceAttributeType::VARNAME: {
        if (synType == Query::DesignEntityType::VARIABLE) {
            elementString = synonymValue;
        }
        else if (synType == Query::DesignEntityType::PRINT) {
            elementString = QueryPKBInterface::getInstance().getPrint(synonymValue);
        }
        else if (synType == Query::DesignEntityType::READ) {
            elementString = QueryPKBInterface::getInstance().getRead(synonymValue);
        }
        break;
    }
    case Query::ReferenceAttributeType::VALUE: {
        bool isCorrectType = synType == Query::DesignEntityType::CONSTANT;
        if (isCorrectType) {
            elementString = synonymValue;
        }
        break;
    }
    case Query::ReferenceAttributeType::STMTNUM: {
        bool isCorrectType = (synType == Query::DesignEntityType::ASSIGN) || (synType == Query::DesignEntityType::CALL) || (synType == Query::DesignEntityType::IF) || (synType == Query::DesignEntityType::PRINT) || (synType == Query::DesignEntityType::READ) || (synType == Query::DesignEntityType::STMT) || (synType == Query::DesignEntityType::WHILE);
        if (isCorrectType) {
            elementString = synonymValue;
        }
        break;
    }

    default:
        break;
    }
    return elementString;
}

std::vector<std::string> QueryEvaluator::splitBySpaces(std::string str) {
    std::vector<std::string> output;
    std::string word = "";
    for (auto x : str) {
        if (x == ' ') {
            output.push_back(word);
            word = "";
        }
        else {
            word.push_back(x);
        }
    }
    if (word != " ") {
        output.push_back(word);
        return output;
    }
    else {
        return output;
    }
    return output;
}

//Solve Helpers------------------------------------------------------------------------------------------------------------------
//This function solves the SELECT clause if no other clause is called.
std::list<std::string> QueryEvaluator::solveSelectClause(std::vector<Query::Element> selectedSynonym, bool queryBooleanReturn, bool isReturnTypeBoolean) {
    
    std::list<std::string> emptyAnswer;
    //If a boolean return is required, return True/False immediately based on whether clauses evaluated to true/false.
    if (isReturnTypeBoolean) {
        if (queryBooleanReturn) {
            return { "TRUE" };
        }
        else {
            return { "FALSE" };
        }
    }
    if (queryBooleanReturn) {
        if (selectedSynonym.size() == 0) {
            return emptyAnswer;
        }
        else if (selectedSynonym.size() == 1) {
            Query::Element elem = selectedSynonym.front();
            std::string synonym = elem.synonymString;
            Query::DesignEntityType synType = getSynonymType(synonym);
            std::list<std::string> answerList;
            bool isEvaluated = isSynonymEvaluated(synonym);
            if (isEvaluated) {
                if (elem.elementType == Query::ElementType::SYNONYM) {
                    for (auto it : answerTable[synonym]) {
                        answerList.push_back(it.first);
                    }
                }
                else if (elem.elementType == Query::ElementType::ATTRIBUTE) {
                    std::unordered_set<std::string> answerSet;
                    for (auto it : answerTable[synonym]) {
                        std::string attributeValue = evaluateAttribute(elem.elementAttribType, synonym, it.first, synType);
                        answerSet.insert(attributeValue);
                    }
                    for (auto it : answerSet) {
                        answerList.push_back(it);
                    }
                }
                else {
                }
                return answerList;
            }
            else {
                std::vector<std::string> synonymValues = getDesignEntityValues(synonym, synType);
                if (elem.elementType == Query::ElementType::SYNONYM) {
                    for (auto it : synonymValues) {
                        answerList.push_back(it);
                    }
                }
                else if (elem.elementType == Query::ElementType::ATTRIBUTE) {
                    std::unordered_set<std::string> answerSet;
                    for (auto it : synonymValues) {
                        std::string attributeValue = evaluateAttribute(elem.elementAttribType, synonym, it, synType);
                        answerSet.insert(attributeValue);
                    }
                    for (auto it : answerSet) {
                        answerList.push_back(it);
                    }
                }
                else {

                }
                return answerList;
            }
            return emptyAnswer;
        }
        else {
            return solveSelectTuple(selectedSynonym);
        }
    }
    return emptyAnswer;
}

std::list<std::string> QueryEvaluator::solveSelectTuple(std::vector<Query::Element> selectedSynonym) {
    std::list<std::string> emptyAnswer;
    std::list<std::string> answerList;
    int numSyn = selectedSynonym.size();

    //Data structure to preserve the order of the tuple
    std::vector<std::string> synOrder;
    for (Query::Element elem : selectedSynonym) {
        synOrder.push_back(buildElementString(elem));
    }

    //All synonyms
    std::unordered_set<std::string> tupleSynSet;
    for (auto elem : selectedSynonym) {
        tupleSynSet.insert(elem.synonymString);
    }

    std::vector<std::unordered_map<std::string, std::string>> answers;
    std::unordered_set<std::string> consideredSyn;

    for (std::string syn : tupleSynSet) {
        //First synonym, initialize vector of answerMaps
        if (answers.empty()) {
            std::vector<std::string> values;
            if (!isSynonymEvaluated(syn)) {
                values = getDesignEntityValues(syn, getSynonymType(syn));
            }
            //If synonym has been evaluated in Query Evaluation
            else {
                values = extractValue(syn);
            }
            for (std::string v : values) {
                std::unordered_map<std::string, std::string> r;
                r[syn] = v;
                answers.push_back(r);
            }
            consideredSyn.insert(syn);
        }
        //Subesequent synonyms
        else {
            //Check if synonym is evaluated with other previously considered synonyms
            std::vector<std::string> synEvaluatedTogether;
            for (std::string syn2 : consideredSyn) {
                if (isSynonymEvaluatedTogether(syn, syn2)) {
                    synEvaluatedTogether.push_back(syn2);
                }
            }
            //If synonym is not evaluated with any other previously considered synonyms
            if (synEvaluatedTogether.size() == 0) {
                std::vector<std::string> values;
                //If synonym has not been evaluated ever in the Query Evaluation
                if (!isSynonymEvaluated(syn)) {
                    values = getDesignEntityValues(syn, getSynonymType(syn));
                }
                //If synonym has been evaluated in Query Evaluation
                else {
                    values = extractValue(syn);
                }
                std::vector<std::unordered_map<std::string, std::string>> tempAnswers;
                int target_answer_size = answers.back().size() + 1;
                for (std::string v : values) {
                    for (auto &a : answers) {
                        if (a.size() < target_answer_size) {
                            a[syn] = v;
                        }
                        else {
                            auto temp = a;
                            temp[syn] = v;
                            tempAnswers.push_back(temp);
                        }
                    }
                }
                std::move(tempAnswers.begin(), tempAnswers.end(), std::back_inserter(answers));
            }
            //If synonym is evaluated with at least one other previously considered synonyms
            else {
                
                std::vector<std::unordered_map<std::string, std::string>> tempAnswers;
                int target_answer_size = answers.back().size() + 1;
                int previousAnswerSize = answers.back().size();
                for (auto &a : answers) {
                    std::unordered_set<std::string> valuesSet;
                    bool isInitialized = false;
                    for (std::string syn2 : synEvaluatedTogether) {
                        std::string v2 = a[syn2];
                        if (!isInitialized) {
                            valuesSet = answerTable[syn2][v2][syn];
                        }
                        else {
                            for (std::string answerTablev : answerTable[syn2][v2][syn]) {
                                if (valuesSet.find(answerTablev) == valuesSet.end()) {
                                    valuesSet.erase(answerTablev);
                                }
                            }
                        }
                    }
                    for (std::string remainingValue : valuesSet) {
                        if (a.size() < target_answer_size) {
                            a[syn] = remainingValue;
                        }
                        else {
                            auto temp = a;
                            temp[syn] = remainingValue;
                            tempAnswers.push_back(temp);
                        }
                    }
                }
                std::move(tempAnswers.begin(), tempAnswers.end(), std::back_inserter(answers));
                for (int i = 0; i < answers.size(); i++) {
                    if (answers[i].size() < target_answer_size) {
                        answers.erase(answers.begin() + i);
                    }
                }
                
                
            }

        }
    }
    for (auto map : answers) {
        std::string answerString;
        for (Query::Element elem : selectedSynonym) {
            if (elem.elementType == Query::ElementType::ATTRIBUTE) {
                answerString = answerString + evaluateAttribute(elem.elementAttribType, elem.synonymString, map[elem.synonymString], getSynonymType(elem.synonymString)) + " ";
            }
            else {
                answerString = answerString + map[elem.synonymString] + " ";
            }
        }
        answerString.pop_back();
        answerList.push_back(answerString);
    }

    return answerList;
}

//This function solves a SUCH_THAT clause
bool QueryEvaluator::solveSuchThatClause(Query::Clause c) {

    //Extract info from clause
    Query::DesignAbstractionType clauseDAT = c.designAbstractionType;
    std::string ref1 = c.leftRef.refString;
    Query::DesignEntityType det1 = c.leftRef.refDentityType;
    Query::ReferenceType ref1Type = c.leftRef.refType;
    std::string ref2 = c.rightRef.refString;
    Query::DesignEntityType det2 = c.rightRef.refDentityType;
    Query::ReferenceType ref2Type = c.rightRef.refType;

    std::vector<std::string> ref1Values;
    std::vector<std::string> ref2Values;
    bool isRef1WildCard = false;
    bool isRef2WildCard = false;
    bool isEvaluatedTogether = false;
    bool isRef1Evaluated = false;
    bool isRef2Evaluated = false;
    bool isSynonymDuplicate = false;

    bool isClauseTrue = false;
    //Catch F/F*/P/P*/N/N*(s,s) - No impact on M/U(s,s) as they are caught as invalid in parser
    if (ref1.compare(ref2) == 0) {
        if (ref1Type == Query::ReferenceType::INTEGER || ref1Type == Query::ReferenceType::SYNONYM) {
            if (ref2Type == Query::ReferenceType::INTEGER || ref2Type == Query::ReferenceType::SYNONYM) {
                if (clauseDAT == Query::DesignAbstractionType::FOLLOWS || clauseDAT == Query::DesignAbstractionType::FOLLOWS_STAR || clauseDAT == Query::DesignAbstractionType::PARENT || clauseDAT == Query::DesignAbstractionType::PARENT_STAR || clauseDAT == Query::DesignAbstractionType::NEXT) {
                    return isClauseTrue;
                }
                else {
                    isSynonymDuplicate = true;
                }
            }
        }
    }

    if (ref1Type == Query::ReferenceType::SYNONYM) {
        if (isSynonymEvaluated(ref1)) {
            ref1Values = extractValue(ref1);
            isRef1Evaluated = true;
        }
        else {
            ref1Values = getDesignEntityValues(ref1, det1);
        }
    }
    else if (ref1Type == Query::ReferenceType::QUOTATION || ref1Type == Query::ReferenceType::INTEGER) {
        ref1Values = { ref1 };
        ref1 = "_";
    }
    else if (ref1Type == Query::ReferenceType::WILDCARD) {
        isRef1WildCard = true;
    }
    else {
        //Defensive programming, cases here should be caught under QueryPreprocessor
        return false;
    }

    if (ref2Type == Query::ReferenceType::SYNONYM) {
        if (isSynonymDuplicate){
        }
        else if (isSynonymEvaluatedTogether(ref1, ref2)) {
            isEvaluatedTogether = true;
        }
        else if (isSynonymEvaluated(ref2)) {
            ref2Values = extractValue(ref2);
            isRef2Evaluated = true;
        }
        else {
            ref2Values = getDesignEntityValues(ref2, det2);
        }
    }
    else if (ref2Type == Query::ReferenceType::QUOTATION || ref2Type == Query::ReferenceType::INTEGER) {
        ref2Values = { ref2 };
        ref2 = "_";
    }
    else if (ref2Type == Query::ReferenceType::WILDCARD) {
        isRef2WildCard = true;
    }
    else {
        //Defensive programming, cases here should be caught under QueryPreprocessor
        return false;
    }



    if (ref1Type == Query::ReferenceType::SYNONYM) {
        if (ref2Type == Query::ReferenceType::SYNONYM) {
            setSynonymsEvaluatedTogether(ref1, ref2);
        }
        setSynonymEvaluated(ref1);
    }
    if (ref2Type == Query::ReferenceType::SYNONYM) {
        setSynonymEvaluated(ref2);
    }


    //Check for previously evaluated synonyms
    if (isSynonymDuplicate) {
        for (std::string val : ref1Values) {
            bool isValid = assertDesignAbstractionValues(clauseDAT, val, val);
            if (isValid) {
                isClauseTrue = true;
                answerTable[ref1][val]["_"].insert("_");
            }
            else {
                answerTableCleanRemove(ref1, val);
            }
        }
    }
    else if (isEvaluatedTogether) {
        for (std::string v1 : ref1Values) {
            bool oneMatchFound = false;
            auto ref2ValuesSet = answerTable[ref1][v1][ref2];
            ref2Values.clear();
            for (std::string s : ref2ValuesSet) {
                ref2Values.push_back(s);
            }
            for (std::string v2 : ref2Values) {
                bool isFound = assertDesignAbstractionValues(clauseDAT, v1, v2);
                if (isFound) {
                    isClauseTrue = true;
                    oneMatchFound = true;
                    answerTable[ref1][v1][ref2].insert(v2);
                    answerTable[ref2][v2][ref1].insert(v1);
                }
                else {
                    answerTableCleanRemove(ref2, v2, ref1, v1);
                    answerTableCleanRemove(ref1, v1, ref2, v2);
                }
            }
            if (!oneMatchFound) {
                answerTableCleanRemove(ref1, v1);
            }
        }
        for (std::string v2 : ref2Values) {
            bool oneMatchFound = false;
            auto ref1ValuesSet = answerTable[ref2][v2][ref1];
            ref1Values.clear();
            for (std::string s : ref1ValuesSet) {
                ref1Values.push_back(s);
            }
            for (std::string v1 : ref1Values) {
                bool isFound = assertDesignAbstractionValues(clauseDAT, v1, v2);
                if (isFound) {
                    isClauseTrue = true;
                    oneMatchFound = true;
                    answerTable[ref1][v1][ref2].insert(v2);
                    answerTable[ref2][v2][ref1].insert(v1);
                }
                else {
                    answerTableCleanRemove(ref2, v2, ref1, v1);
                    answerTableCleanRemove(ref1, v1, ref2, v2);
                }
            }
            if (!oneMatchFound) {
                answerTableCleanRemove(ref2, v2);
            }
        }
    }
    //if ref1 found, ref2 not found, find possible values v2 for each value of ref1 in the answerTable, v1
    else if (isRef1Evaluated || ref1Type == Query::ReferenceType::QUOTATION || ref1Type == Query::ReferenceType::INTEGER) {
        //if ref1 found, ref2 not found, find possible values v2 for each value of ref1 in the answerTable, v1
        if (isRef1Evaluated && ref1Type == Query::ReferenceType::SYNONYM && isRef2Evaluated && ref2Type == Query::ReferenceType::SYNONYM){
            for (std::string v1 : ref1Values) {
                bool oneMatchFound = false;
                for (std::string v2 : ref2Values) {
                    bool isFound = assertDesignAbstractionValues(clauseDAT, v1, v2);
                    if (isFound) {
                        isClauseTrue = true;
                        oneMatchFound = true;
                        answerTable[ref1][v1][ref2].insert(v2);
                        answerTable[ref2][v2][ref1].insert(v1);
                    }
                    else {

                        if (ref2Type != Query::ReferenceType::SYNONYM) {
                            answerTableCleanRemove(ref1, v1);
                        }

                        if (ref1Type != Query::ReferenceType::SYNONYM) {
                            answerTableCleanRemove(ref2, v2);
                        }

                        answerTableCleanRemove(ref2, v2, ref1, v1);
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                    }
                }
                if (!oneMatchFound) {
                    answerTableCleanRemove(ref1, v1);
                }
            }
            for (std::string v2 : ref2Values) {
                bool oneMatchFound = false;
                for (std::string v1 : ref1Values) {
                    bool isFound = assertDesignAbstractionValues(clauseDAT, v1, v2);
                    if (isFound) {
                        isClauseTrue = true;
                        oneMatchFound = true;
                        answerTable[ref1][v1][ref2].insert(v2);
                        answerTable[ref2][v2][ref1].insert(v1);
                    }
                    else {
                        if (ref1Type != Query::ReferenceType::SYNONYM) {
                            answerTableCleanRemove(ref2, v2);
                        }

                        if (ref1Type != Query::ReferenceType::SYNONYM) {
                            answerTableCleanRemove(ref1, v1);
                        }
                        answerTableCleanRemove(ref2, v2, ref1, v1);
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                    }
                }
                if (!oneMatchFound) {
                    answerTableCleanRemove(ref2, v2);
                }
            }
        }
        else if (ref2Type == Query::ReferenceType::WILDCARD || (!isRef2Evaluated && ref2Type == Query::ReferenceType::SYNONYM)) {
            for (std::string v1 : ref1Values) {
                bool oneMatchFound = false;
                std::vector<std::string> ref2Values = getDesignAbstractionValues(clauseDAT, v1, det1, false);
                if (ref2Values.size() == 0) {
                    answerTableCleanRemove(ref1, v1);
                    answerTableCleanRemove(ref1, v1, ref2, "");
                }
                else {
                    bool hasref2Value = false;
                    for (auto v2 : ref2Values) {
                        bool isCorrectType = assertDesignEntityType(v2, det2);
                        if (ref2Type == Query::ReferenceType::WILDCARD || ref2Type == Query::ReferenceType::QUOTATION || ref2Type == Query::ReferenceType::INTEGER) {
                            isCorrectType = true;
                        }
                        if (isCorrectType) {
                            isClauseTrue = true;
                            oneMatchFound = true;
                            answerTable[ref1][v1][ref2].insert(v2);
                            answerTable[ref2][v2][ref1].insert(v1);
                        }
                        else {
                            if (ref2Type != Query::ReferenceType::SYNONYM) {
                                answerTableCleanRemove(ref1, v1);
                            }

                            if (ref1Type != Query::ReferenceType::SYNONYM) {
                                answerTableCleanRemove(ref2, v2);
                            }
                            answerTableCleanRemove(ref2, v2, ref1, v1);
                            answerTableCleanRemove(ref1, v1, ref2, v2);
                        }
                    }
                    if (!oneMatchFound) {
                        answerTableCleanRemove(ref1, v1);
                    }
                }
            }
            if (ref2Type == Query::ReferenceType::SYNONYM) {
                for (std::string v2 : extractValue(ref2)) {
                    if (answerTable[ref2][v2].find(ref1) == answerTable[ref2][v2].end()) {
                        answerTableCleanRemove(ref2, v2);
                    }
                }
            }
        }
        //if ref1 found, ref2 found, for each entry in ref1, ref2, assert. Remove from answerTable if false, do not touch if true.
        else {
            for (std::string v1 : ref1Values) {
                for (std::string v2 : ref2Values) {
                    bool isFound = assertDesignAbstractionValues(clauseDAT, v1, v2);
                    if (isFound) {
                        isClauseTrue = true;

                        answerTable[ref1][v1][ref2].insert(v2);
                        answerTable[ref2][v2][ref1].insert(v1);
                    }
                    else {

                        if (ref2Type != Query::ReferenceType::SYNONYM) {
                            answerTableCleanRemove(ref1, v1);
                        }

                        if (ref1Type != Query::ReferenceType::SYNONYM) {
                            answerTableCleanRemove(ref2, v2);
                        }

                        answerTableCleanRemove(ref2, v2, ref1, v1);
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                    }


                }
            }
            for (std::string v2 : ref2Values) {
                for (std::string v1 : ref1Values) {
                    bool isFound = assertDesignAbstractionValues(clauseDAT, v1, v2);
                    if (isFound) {
                        isClauseTrue = true;

                        answerTable[ref1][v1][ref2].insert(v2);
                        answerTable[ref2][v2][ref1].insert(v1);
                    }
                    else {
                        if (ref1Type != Query::ReferenceType::SYNONYM) {
                            answerTableCleanRemove(ref2, v2);
                        }

                        if (ref1Type != Query::ReferenceType::SYNONYM) {
                            answerTableCleanRemove(ref1, v1);
                        }
                        answerTableCleanRemove(ref2, v2, ref1, v1);
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                    }
                }
            }
        }
    }
    //opposite for ref1 not found, ref2 found.
    else if (ref1Type == Query::ReferenceType::WILDCARD || (!isRef1Evaluated && ref1Type == Query::ReferenceType::SYNONYM)) {
        if (isRef2Evaluated || ref2Type == Query::ReferenceType::QUOTATION || ref2Type == Query::ReferenceType::INTEGER) {
            for (std::string v2 : ref2Values) {
                bool oneMatchFound = false;
                std::vector<std::string> ref1Values = getDesignAbstractionValues(clauseDAT, v2, det2, true);
                if (ref1Values.size() == 0) {
                    answerTableCleanRemove(ref2, v2);
                    answerTableCleanRemove(ref2, v2, ref1, "");
                }
                else {
                    for (auto v1 : ref1Values) {
                        bool isCorrectType = assertDesignEntityType(v1, det1);
                        if (ref1Type == Query::ReferenceType::WILDCARD || ref1Type == Query::ReferenceType::QUOTATION || ref1Type == Query::ReferenceType::INTEGER) {
                            isCorrectType = true;
                            oneMatchFound = true;
                        }
                        if (isCorrectType) {
                            isClauseTrue = true;
                            oneMatchFound = true;
                            answerTable[ref1][v1][ref2].insert(v2);
                            answerTable[ref2][v2][ref1].insert(v1);
                        }
                        else {
                            if (ref2Type != Query::ReferenceType::SYNONYM) {
                                answerTableCleanRemove(ref1, v1);
                            }

                            if (ref1Type != Query::ReferenceType::SYNONYM) {
                                answerTableCleanRemove(ref2, v2);
                            }
                            answerTableCleanRemove(ref2, v2, ref1, v1);
                            answerTableCleanRemove(ref1, v1, ref2, v2);
                        }
                    }
                }
                if (!oneMatchFound) {
                    answerTableCleanRemove(ref2, v2);
                }
            }
            if (ref1Type == Query::ReferenceType::SYNONYM) {
                for (std::string v1 : extractValue(ref1)) {
                    if (answerTable[ref1][v1].find(ref2) == answerTable[ref1][v1].end()) {
                        answerTableCleanRemove(ref1, v1);
                    }
                }
            }
        }
        else if (ref1Type != Query::ReferenceType::WILDCARD) {
            for (std::string v1 : ref1Values) {
                bool oneMatchFound = false;
                std::vector<std::string> ref2Values = getDesignAbstractionValues(clauseDAT, v1, det1, false);
                if (ref2Values.size() == 0) {
                    answerTableCleanRemove(ref1, v1, ref2, "");
                }
                else {
                    for (auto v2 : ref2Values) {
                        bool isCorrectType = assertDesignEntityType(v2, det2);
                        if (ref2Type == Query::ReferenceType::WILDCARD || ref2Type == Query::ReferenceType::QUOTATION || ref2Type == Query::ReferenceType::INTEGER) {
                            isCorrectType = true;
                            oneMatchFound = true;
                        }
                        if (isCorrectType) {
                            isClauseTrue = true;
                            oneMatchFound = true;
                            answerTable[ref1][v1][ref2].insert(v2);
                            answerTable[ref2][v2][ref1].insert(v1);
                        }
                        else {
                            if (ref2Type != Query::ReferenceType::SYNONYM) {
                                answerTableCleanRemove(ref1, v1);
                            }

                            if (ref1Type != Query::ReferenceType::SYNONYM) {
                                answerTableCleanRemove(ref2, v2);
                            }
                            answerTableCleanRemove(ref2, v2, ref1, v1);
                            answerTableCleanRemove(ref1, v1, ref2, v2);
                        }
                    }
                }
                if (!oneMatchFound) {
                    answerTableCleanRemove(ref1, v1);
                }
            }}
        else if (ref1Type == Query::ReferenceType::WILDCARD && ref2Type != Query::ReferenceType::WILDCARD) {
            for (std::string v2 : ref2Values) {
                std::vector<std::string> ref1Values = getDesignAbstractionValues(clauseDAT, v2, det2, true);
                if (ref2Values.size() == 0) {
                    answerTableCleanRemove(ref2, v2, ref1, "");
                }
                else {
                    for (auto v1 : ref1Values) {
                        bool isCorrectType = assertDesignEntityType(v1, det1);
                        if (ref1Type == Query::ReferenceType::WILDCARD || ref1Type == Query::ReferenceType::QUOTATION || ref1Type == Query::ReferenceType::INTEGER) {
                            isCorrectType = true;
                        }
                        if (isCorrectType) {
                            isClauseTrue = true;
                            answerTable[ref1][v1][ref2].insert(v2);
                            answerTable[ref2][v2][ref1].insert(v1);
                        }
                        else {
                            if (ref2Type != Query::ReferenceType::SYNONYM) {
                                answerTableCleanRemove(ref1, v1);
                            }

                            if (ref1Type != Query::ReferenceType::SYNONYM) {
                                answerTableCleanRemove(ref2, v2);
                            }
                            answerTableCleanRemove(ref2, v2, ref1, v1);
                            answerTableCleanRemove(ref1, v1, ref2, v2);
                        }
                    }
                }
            }
        }
        else {
            if (IsDATEmpty(clauseDAT)) {
                isClauseTrue = false;
            }
            else {
                isClauseTrue = true;
            }
        }
    }

    if (ref1Type == Query::ReferenceType::SYNONYM && ref2Type == Query::ReferenceType::SYNONYM && !isEvaluatedTogether && !isSynonymDuplicate) {
        tightenAnswerTable();
    }
    
    return isClauseTrue;
}

//This function solves a PATTERN clause
bool QueryEvaluator::solvePatternClause(Query::Clause c) {
    switch (c.patternAbstractionType) {
    case Query::PatternAbstractionType::ASSIGN:
        return solveAssignPatternClause(c);

    case Query::PatternAbstractionType::IF:
        return solveIfPatternClause(c);

    case Query::PatternAbstractionType::WHILE:
        return solveWhilePatternClause(c);

    default:
        return false;
    }
}

bool QueryEvaluator::solveIfPatternClause(Query::Clause c) {
    bool isPatternFound = false;

    //Extract info from clause
    std::string ref1 = c.leftRef.refString;
    Query::DesignEntityType det1 = c.leftRef.refDentityType;
    Query::ReferenceType rt1 = c.leftRef.refType;
    std::string ref2 = c.rightRef.refString;
    Query::DesignEntityType det2 = c.rightRef.refDentityType;
    Query::ReferenceType rt2 = c.rightRef.refType;
    bool isVariableWildcard = false;
    bool isEvaluatedTogether = false;

    std::vector<std::string> ref1Values;
    std::vector<std::string> ref2Values;
    

    if (det1 != Query::DesignEntityType::IF) {
        //Defensive programming - case should be caught by QueryPreprocessor
        return false;
    }
    if (rt1 == Query::ReferenceType::SYNONYM) {
        if (isSynonymEvaluated(ref1)) {
            ref1Values = extractValue(ref1);
        }
        else {
            ref1Values = getDesignEntityValues(ref1, det1);
        }
    }

    if (rt2 == Query::ReferenceType::SYNONYM && det2 == Query::DesignEntityType::VARIABLE) {
        if (isSynonymEvaluatedTogether(ref1, ref2)) {
            isEvaluatedTogether = true;
        }
        else if (isSynonymEvaluated(ref2)) {
            ref2Values = extractValue(ref2);
        }
        else {
            ref2Values = getDesignEntityValues(ref2, Query::DesignEntityType::VARIABLE);
        }
    }
    else if (rt2 == Query::ReferenceType::QUOTATION) {
        ref2Values = { ref2 };
        ref2 = "_";
    }
    else if (rt2 == Query::ReferenceType::WILDCARD){
        isVariableWildcard = true;
    }
    else {
        //Defensive programming, cases here should be caught under QueryPreprocessor
        return false;
    }

    //Setting synonyms to be evaluated if the reference Type is SYNONYM
    if (rt1 == Query::ReferenceType::SYNONYM) {
        if (rt2 == Query::ReferenceType::SYNONYM) {
            setSynonymsEvaluatedTogether(ref1, ref2);
        }
        setSynonymEvaluated(ref1);
    }
    if (rt2 == Query::ReferenceType::SYNONYM) {
        setSynonymEvaluated(ref2);
    }


    //Evaluation
    for (std::string v1 : ref1Values) {
        bool oneMatch = false;
        std::vector<std::string> variables = QueryPKBInterface::getInstance().getIf(v1);
        for (auto s : variables) {

        }

        if (!isVariableWildcard) {
            //If synonyms are evaluated together:
            if (isEvaluatedTogether) {
                ref2Values = {};
                for (std::string v2 : answerTable[ref1][v1][ref2]) {
                    ref2Values.push_back(v2);
                }
                for (std::string v2 : ref2Values) {
                    auto it = std::find(variables.begin(), variables.end(), v2);
                    if (it == variables.end()){
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                        answerTableCleanRemove(ref2, v2, ref1, v1);
                    }
                    else {
                        isPatternFound = true;
                        oneMatch = true;
                    }
                }
            }
            //If synonyms are not evaluated together: - this covers the case of IDENT for variables.
            else {
                for (std::string v2 : ref2Values) {
                    auto it = std::find(variables.begin(), variables.end(), v2);
                    if (it == variables.end()) {
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                        answerTableCleanRemove(ref2, v2, ref1, v1);
                    }
                    else {
                        isPatternFound = true;
                        oneMatch = true;
                        answerTable[ref1][v1][ref2].insert(v2);
                        answerTable[ref2][v2][ref1].insert(v1);
                    }
                }
            }
        }
        //If wildcard, as long as one instance is found, return true.
        else {
            if (variables.size() > 0) {
                isPatternFound = true;
                oneMatch = true;
                answerTable[ref1][v1]["_"].insert("_");
            }

        }
        if (!oneMatch) {
            answerTableCleanRemove(ref1, v1);
        }
    }
    if (rt2 == Query::ReferenceType::SYNONYM) {
        for (std::string v2 : extractValue(ref2)) {
            if (answerTable[ref2][v2].find(ref1) == answerTable[ref2][v2].end()) {
                answerTableCleanRemove(ref2, v2);
            }
        }
    }
    if (rt1 == Query::ReferenceType::SYNONYM && rt2 == Query::ReferenceType::SYNONYM && !isEvaluatedTogether) {
        tightenAnswerTable();
    }
    
    return isPatternFound;
}

bool QueryEvaluator::solveWhilePatternClause(Query::Clause c) {
    bool isPatternFound = false;

    //Extract info from clause
    std::string ref1 = c.leftRef.refString;
    Query::DesignEntityType det1 = c.leftRef.refDentityType;
    Query::ReferenceType rt1 = c.leftRef.refType;
    std::string ref2 = c.rightRef.refString;
    Query::DesignEntityType det2 = c.rightRef.refDentityType;
    Query::ReferenceType rt2 = c.rightRef.refType;
    bool isVariableWildcard = false;
    bool isEvaluatedTogether = false;

    std::vector<std::string> ref1Values;
    std::vector<std::string> ref2Values;


    if (det1 != Query::DesignEntityType::WHILE) {
        //Defensive programming - case should be caught by QueryPreprocessor
        return false;
    }
    if (rt1 == Query::ReferenceType::SYNONYM) {
        if (isSynonymEvaluated(ref1)) {
            ref1Values = extractValue(ref1);
        }
        else {
            ref1Values = getDesignEntityValues(ref1, det1);
        }
    }

    if (rt2 == Query::ReferenceType::SYNONYM && det2 == Query::DesignEntityType::VARIABLE) {
        if (isSynonymEvaluatedTogether(ref1, ref2)) {
            isEvaluatedTogether = true;
        }
        else if (isSynonymEvaluated(ref2)) {
            ref2Values = extractValue(ref2);
        }
        else {
            ref2Values = getDesignEntityValues(ref2, Query::DesignEntityType::VARIABLE);
        }
    }
    else if (rt2 == Query::ReferenceType::QUOTATION) {
        ref2Values = { ref2 };
        ref2 = "_";
    }
    else if (rt2 == Query::ReferenceType::WILDCARD) {
        ref2Values = {};
        isVariableWildcard = true;
    }
    else {
        //Defensive programming, cases here should be caught under QueryPreprocessor
        return false;
    }
    //Setting synonyms to be evaluated if the reference Type is SYNONYM
    if (rt1 == Query::ReferenceType::SYNONYM) {
        if (rt2 == Query::ReferenceType::SYNONYM) {
            setSynonymsEvaluatedTogether(ref1, ref2);
        }
        setSynonymEvaluated(ref1);
    }
    if (rt2 == Query::ReferenceType::SYNONYM) {
        setSynonymEvaluated(ref2);
    }


    //Evaluation
    for (std::string v1 : ref1Values) {
        bool oneMatch = false;
        std::vector<std::string> variables = QueryPKBInterface::getInstance().getWhile(v1);
        if (!isVariableWildcard) {
            //If synonyms are evaluated together:
            if (isEvaluatedTogether) {
                ref2Values = {};
                for (std::string v2 : answerTable[ref1][v1][ref2]) {
                    ref2Values.push_back(v2);
                }
                for (std::string v2 : ref2Values) {
                    auto it = std::find(variables.begin(), variables.end(), v2);
                    if (it == variables.end()) {

                        answerTableCleanRemove(ref1, v1, ref2, v2);
                        answerTableCleanRemove(ref2, v2, ref1, v1);
                    }
                    else {

                        oneMatch = true;
                        isPatternFound = true;
                    }
                }
            }
            //If synonyms are not evaluated together: - this covers the case of IDENT for variables.
            else {
                for (std::string v2 : ref2Values) {
                    auto it = std::find(variables.begin(), variables.end(), v2);
                    if (it == variables.end()) {
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                        answerTableCleanRemove(ref2, v2, ref1, v1);
                    }
                    else {
                        oneMatch = true;
                        isPatternFound = true;
                        answerTable[ref1][v1][ref2].insert(v2);
                        answerTable[ref2][v2][ref1].insert(v1);
                    }
                }
            }
        }
        //If wildcard, as long as one instance is found, return true.
        else {
            if (variables.size() > 0) {
                oneMatch = true;
                isPatternFound = true;
                answerTable[ref1][v1]["_"].insert("_");
            }

        }
        if (!oneMatch) {
            answerTableCleanRemove(ref1, v1);
        }
    }
    if (rt2 == Query::ReferenceType::SYNONYM) {
        for (std::string v2 : extractValue(ref2)) {
            if (answerTable[ref2][v2].find(ref1) == answerTable[ref2][v2].end()) {
                answerTableCleanRemove(ref2, v2);
            }
        }
    }
    if (rt1 == Query::ReferenceType::SYNONYM && rt2 == Query::ReferenceType::SYNONYM && !isEvaluatedTogether) {
        tightenAnswerTable();
    }
    
    return isPatternFound;
}

bool QueryEvaluator::solveAssignPatternClause(Query::Clause c) {
    bool isPatternFound = false;

    //Extract info from clause
    std::string ref1 = c.leftRef.refString;
    Query::DesignEntityType det1 = c.leftRef.refDentityType;
    Query::ReferenceType rt1 = c.leftRef.refType;
    std::string ref2 = c.rightRef.refString;
    Query::DesignEntityType det2 = c.rightRef.refDentityType;
    Query::ReferenceType rt2 = c.rightRef.refType;

    Query::ExpressionType match = c.expr.exprType;
    std::string expr_string = c.expr.exprString;
    std::string shunted_string = ShuntingYard::shuntingYard(expr_string);

    std::vector<std::string> ref1Values;
    std::vector<std::string> ref2Values;
    bool isVariableWildcard = false;
    bool isEvaluatedTogether = false;

    if (det1 != Query::DesignEntityType::ASSIGN) {
        //Defensive programming - case should be caught by QueryPreprocessor
        return false;
    }
    if (rt1 == Query::ReferenceType::SYNONYM) {
        if (isSynonymEvaluated(ref1)) {
            ref1Values = extractValue(ref1);
        }
        else {
            ref1Values = getDesignEntityValues(ref1, det1);
        }
    }
    
    if (rt2 == Query::ReferenceType::SYNONYM || det2 == Query::DesignEntityType::VARIABLE) {
        if (isSynonymEvaluatedTogether(ref1, ref2)) {
            isEvaluatedTogether = true;
        }
        else if (isSynonymEvaluated(ref2)) {
            ref2Values = extractValue(ref2);
        }
        else {
            ref2Values = getDesignEntityValues(ref2, Query::DesignEntityType::VARIABLE);
        }
    }
    else if (rt2 == Query::ReferenceType::QUOTATION) {
        ref2Values = { ref2 };
        ref2 = "_";
    }
    else if (rt2 == Query::ReferenceType::WILDCARD) {
        isVariableWildcard = true;
    }
    else {
        //Defensive programming, cases here should be caught under QueryPreprocessor
        return false;
    }

    //Setting synonyms to be evaluated if the reference Type is SYNONYM
    if (rt1 == Query::ReferenceType::SYNONYM) {
        if (rt2 == Query::ReferenceType::SYNONYM) {
            setSynonymsEvaluatedTogether(ref1, ref2);
        }
        setSynonymEvaluated(ref1);
    }
    if (rt2 == Query::ReferenceType::SYNONYM) {
        setSynonymEvaluated(ref2);
    }




    for (std::string v1 : ref1Values) {
        std::pair<std::string, std::string> v1_assign = QueryPKBInterface::getInstance().getAssign(v1);
        std::string lHSvariable = v1_assign.first;
        if (!isVariableWildcard) {
            //If synonyms are evaluated together:
            if (isEvaluatedTogether) {
                ref2Values = {};
                for (std::string v2 : answerTable[ref1][v1][ref2]) {
                    ref2Values.push_back(v2);
                }
                bool syn1Valid = false;
                for (std::string v2 : ref2Values) {
                    if (lHSvariable.compare(v2) == 0) {
                        //If no match required
                        if (c.expr.exprType == Query::ExpressionType::NO_MATCH) {
                            isPatternFound = true;
                            syn1Valid = true;
                        }
                        //If exact match required
                        else if (match == Query::ExpressionType::EXACT_MATCH) {
                            //And found, flag isPatternFound set to true, add to answerTable[ref1][v1][ref2][v2] and answerTable[ref2][v2][ref1][v1]
                            if (v1_assign.second.compare(shunted_string) == 0) {
                                isPatternFound = true;
                                syn1Valid = true;
                            }
                            else {
                                answerTableCleanRemove(ref2, v2, ref1, v1);
                                answerTableCleanRemove(ref1, v1, ref2, v2);
                            }
                        }
                        //If partial match required
                        else if (match == Query::ExpressionType::PARTIAL_MATCH) {
                            //And found, flag isPatternFound set to true, add to answerTable[ref1][v1][ref2][v2] and answerTable[ref2][v2][ref1][v1]
                            //if (v1_assign.second.find(shunted_string) != std::string::npos) {
                            if (isPartialMatch(v1_assign.second, shunted_string)) {
                                isPatternFound = true;
                                syn1Valid = true;
                            }
                            else {
                                answerTableCleanRemove(ref2, v2, ref1, v1);
                                answerTableCleanRemove(ref1, v1, ref2, v2);
                            }
                        }
                    }
                    else {
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                        answerTableCleanRemove(ref2, v2, ref1, v1);
                    }
                }
                if (!syn1Valid) {
                    answerTableCleanRemove(ref1, v1);
                }

            }
            //If synonyms are not evaluated together: - this covers the case of IDENT for variables.
            else {
                bool syn1Valid = false;
                for (std::string v2 : ref2Values) {
                    if (lHSvariable.compare(v2) == 0) {
                        //If no match required
                        if (c.expr.exprType == Query::ExpressionType::NO_MATCH) {
                            isPatternFound = true;
                            syn1Valid = true;
                            answerTable[ref1][v1][ref2].insert(v2);
                            answerTable[ref2][v2][ref1].insert(v1);
                        }
                        //If exact match required
                        else if (match == Query::ExpressionType::EXACT_MATCH) {
                            //And found, flag isPatternFound set to true, add to answerTable[ref1][v1][ref2][v2] and answerTable[ref2][v2][ref1][v1]
                            if (v1_assign.second.compare(shunted_string) == 0) {
                                isPatternFound = true;
                                syn1Valid = true;
                                answerTable[ref1][v1][ref2].insert(v2);
                                answerTable[ref2][v2][ref1].insert(v1);
                            }
                            else {
                                answerTableCleanRemove(ref2, v2, ref1, v1);
                                answerTableCleanRemove(ref1, v1, ref2, v2);
                            }
                        }
                        //If partial match required
                        else if (match == Query::ExpressionType::PARTIAL_MATCH) {
                            //And found, flag isPatternFound set to true, add to answerTable[ref1][v1][ref2][v2] and answerTable[ref2][v2][ref1][v1]
                            //if (v1_assign.second.find(shunted_string) != std::string::npos) {
                            if (isPartialMatch(v1_assign.second, shunted_string)) {
                                isPatternFound = true;
                                syn1Valid = true;
                                answerTable[ref1][v1][ref2].insert(v2);
                                answerTable[ref2][v2][ref1].insert(v1);
                            }
                            else {
                                answerTableCleanRemove(ref2, v2, ref1, v1);
                                answerTableCleanRemove(ref1, v1, ref2, v2);
                            }
                        }
                    }
                    else {
                        answerTableCleanRemove(ref1, v1, ref2, v2);
                        answerTableCleanRemove(ref2, v2, ref1, v1);
                    }
                }
                if (!syn1Valid) {
                    answerTableCleanRemove(ref1, v1);
                }
                
            }
        }
        //If wildcard, as long as one instance is found, return true.
        else {
            std::string v2 = lHSvariable;
            if (c.expr.exprType == Query::ExpressionType::NO_MATCH) {
                isPatternFound = true;
                answerTable[ref1][v1][ref2].insert(v2);
            }
            //If exact match required
            else if (match == Query::ExpressionType::EXACT_MATCH) {
                //And found, flag isPatternFound set to true, add to answerTable[ref1][v1][ref2][v2] and answerTable[ref2][v2][ref1][v1]
                if (v1_assign.second.compare(shunted_string) == 0) {
                    isPatternFound = true;
                    answerTable[ref1][v1][ref2].insert(v2);
                }
                //And not found, cleanremove answerTable[ref1][v1][ref2][v2]
                else {
                    answerTableCleanRemove(ref1, v1, ref2, v2);
                }
            }
            //If partial match required
            else if (match == Query::ExpressionType::PARTIAL_MATCH) {
                //And found, flag isPatternFound set to true, add to answerTable[ref1][v1][ref2][v2] and answerTable[ref2][v2][ref1][v1]
                if (isPartialMatch(v1_assign.second, shunted_string)) {
                    isPatternFound = true;
                    answerTable[ref1][v1][ref2].insert(v2);
                }
                else {
                    answerTableCleanRemove(ref1, v1, ref2, v2);
                }
            }

        }
    }
    ref2Values = extractValue(ref2);
    if (rt2 == Query::ReferenceType::SYNONYM) {
        for (std::string v2 : ref2Values) {
            if (answerTable[ref2][v2].find(ref1) == answerTable[ref2][v2].end()) {
                answerTableCleanRemove(ref2, v2);
            }
        }
    }
    
    if (rt1 == Query::ReferenceType::SYNONYM && rt2 == Query::ReferenceType::SYNONYM && !isEvaluatedTogether) {
        tightenAnswerTable();
    }
    
    return isPatternFound;
}

std::pair<std::vector<std::string>, bool> QueryEvaluator::findReferenceAttribute(std::string refString, Query::ReferenceAttributeType refAttribType, Query::ReferenceType refType, Query::DesignEntityType refDentityType) {

    switch (refAttribType) {
    case Query::ReferenceAttributeType::PROCNAME:
    case Query::ReferenceAttributeType::VARNAME:
        return QueryEvaluator::findReferenceAttributeString(refDentityType);
    case Query::ReferenceAttributeType::VALUE:
    case Query::ReferenceAttributeType::NONE:
        switch (refType) {
        case Query::ReferenceType::SYNONYM:
        case Query::ReferenceType::ATTRIBUTE:
            return { QueryEvaluator::findReferenceAttributeInt(refDentityType), false };
        case Query::ReferenceType::INTEGER:
            return { { refString }, false };
        default:
            return {};
        }
    case Query::ReferenceAttributeType::STMTNUM:
        return { QueryEvaluator::findReferenceAttributeInt(refDentityType), false };
    default:
        return {};
    }
    return {};
}

std::pair<std::vector<std::string>, bool> QueryEvaluator::findReferenceAttributeString(Query::DesignEntityType type) {
    switch (type) {
    case Query::DesignEntityType::CALL:
        return { QueryPKBInterface::getInstance().getAllValuesCall(), true };
        break;

    case Query::DesignEntityType::PRINT:
        return { QueryPKBInterface::getInstance().getAllValuesPrint(), true };
        break;

    case Query::DesignEntityType::PROCEDURE:
        return { QueryPKBInterface::getInstance().getAllValuesProcedure(), false };
        break;

    case Query::DesignEntityType::READ:
        return { QueryPKBInterface::getInstance().getAllValuesRead(), true };
        break;

    case Query::DesignEntityType::VARIABLE:
        return { QueryPKBInterface::getInstance().getAllValuesVariable(), false };
        break;

    default:
        std::vector<std::string> empty;
        return { empty, false };
    }
}

std::vector<std::string> QueryEvaluator::findReferenceAttributeInt(Query::DesignEntityType type) {
    switch (type) {
    case Query::DesignEntityType::ASSIGN:
        return QueryPKBInterface::getInstance().getAllKeysAssign();
        break;

    case Query::DesignEntityType::CALL:
        return QueryPKBInterface::getInstance().getAllKeysCall();
        break;

    case Query::DesignEntityType::IF:
        return QueryPKBInterface::getInstance().getAllKeysIf();
        break;

    case Query::DesignEntityType::PRINT:
        return QueryPKBInterface::getInstance().getAllKeysPrint();
        break;

    case Query::DesignEntityType::READ:
        return QueryPKBInterface::getInstance().getAllKeysRead();
        break;

    case Query::DesignEntityType::STMT:
    case Query::DesignEntityType::PROG_LINE:
        return QueryPKBInterface::getInstance().getAllKeysStatement();
        break;

    case Query::DesignEntityType::WHILE:
        return QueryPKBInterface::getInstance().getAllKeysWhile();
        break;

    case Query::DesignEntityType::CONSTANT:
        return QueryPKBInterface::getInstance().getAllValuesConstant();
        break;

        //This case covers NONE and WILDCARD
    case Query::DesignEntityType::NONE:
    default:
        std::vector<std::string> empty;
        return empty;
    }
}

void QueryEvaluator::removeWithDifference(Query::Reference leftRef, Query::Reference rightRef, std::vector<std::string> leftResults, std::vector<std::string> rightResults) {
    std::vector<std::string> leftDiff;

    std::vector<std::string> leftKeys;
    std::vector<std::string> rightKeys;

    std::set_difference(leftKeys.begin(), leftKeys.end(), rightKeys.begin(), rightKeys.end(),
        std::inserter(leftDiff, leftDiff.begin()));
    for (auto item : leftDiff) {
        for (auto leftItem : leftResults) {
            for (auto key : QueryEvaluator::getKeysOrValues(leftRef, leftItem)) {
                leftKeys.push_back(key);
            }
        }
        QueryEvaluator::answerTableCleanRemove(leftRef.synonym, item);
    }
}

bool QueryEvaluator::findAndCompareWithSearchResults(Query::Reference leftRef, Query::Reference rightRef) {
    bool isValueLeft = false;
    bool isValueRight = false;
    if (isSynonymEvaluatedTogether(leftRef.synonym, rightRef.synonym)) {
        std::vector<std::string> leftResults = QueryEvaluator::extractValue(leftRef.synonym);
        std::vector<std::string> rightResults = QueryEvaluator::extractValue(rightRef.synonym);
        if (leftResults.empty() || rightResults.empty()) {
            return false;
        }
        else {
            std::sort(leftResults.begin(), leftResults.end());
            std::sort(rightResults.begin(), rightResults.end());

            QueryEvaluator::removeWithDifference(leftRef, rightRef, leftResults, rightResults);
            QueryEvaluator::removeWithDifference(rightRef, leftRef, rightResults, leftResults);
        }
    }
    else {
        // Either left has been evaluated and right is not, or right has been evaluated and left is not, or both not evaluated
        std::vector<std::string> leftResults;
        if (isSynonymEvaluated(leftRef.synonym)) {
            leftResults = QueryEvaluator::extractValue(leftRef.synonym);
            std::pair<std::vector<std::string>, bool> resultPair = QueryEvaluator::getKeysOrValues(leftRef, leftResults);
            leftResults = resultPair.first;
            isValueLeft = resultPair.second;
        }
        else {
            std::pair<std::vector<std::string>, bool> resultPair = QueryEvaluator::findReferenceAttribute(leftRef.refString, leftRef.refAttribType, leftRef.refType, leftRef.refDentityType);
            leftResults = resultPair.first;
            isValueLeft = resultPair.second;
        }
        if (leftResults.empty()) {
            return false;
        }

        std::vector<std::string> rightResults;
        if (isSynonymEvaluated(rightRef.synonym)) {
            rightResults = QueryEvaluator::extractValue(rightRef.synonym);
            std::pair<std::vector<std::string>, bool> resultPair = QueryEvaluator::getKeysOrValues(rightRef, rightResults);
            rightResults = resultPair.first;
            isValueRight = resultPair.second;
        }
        else {
            std::pair<std::vector<std::string>, bool> resultPair = QueryEvaluator::findReferenceAttribute(rightRef.refString, rightRef.refAttribType, rightRef.refType, rightRef.refDentityType);
            rightResults = resultPair.first;
            isValueRight = resultPair.second;
        }
        if (rightResults.empty()) {            
            return false;
        }

        std::sort(leftResults.begin(), leftResults.end());
        std::sort(rightResults.begin(), rightResults.end());

        std::vector<std::string> intersection;

        std::set_intersection(leftResults.begin(), leftResults.end(), rightResults.begin(), rightResults.end(),
            std::inserter(intersection, intersection.begin()));

        std::vector<std::string> leftItems;
        std::vector<std::string> rightItems;

        if (isSynonymEvaluated(leftRef.synonym)) {
            QueryEvaluator::removeWithDifference(leftRef, rightRef, leftResults, rightResults);

            for (auto item : intersection) {
                if (isValueLeft && isValueRight) {
                    auto leftItems = QueryEvaluator::getKeysOrValues(leftRef, item);
                    auto rightItems = QueryEvaluator::getKeysOrValues(rightRef, item);
                    for (auto leftItem : leftItems) {
                        for (auto rightItem : rightItems) {
                            answerTable[rightRef.synonym][rightItem][leftRef.synonym].insert(leftItem);
                        }
                    }
                }
                else if (isValueLeft) {
                    auto leftItems = QueryEvaluator::getKeysOrValues(leftRef, item);
                    for (auto leftItem : leftItems) {
                        answerTable[rightRef.synonym][item][leftRef.synonym].insert(leftItem);
                    }
                }
                else if (isValueRight) {
                    auto rightItems = QueryEvaluator::getKeysOrValues(rightRef, item);
                    for (auto rightItem : rightItems) {
                        answerTable[rightRef.synonym][rightItem][leftRef.synonym].insert(item);
                    }
                }
                else {
                    answerTable[rightRef.synonym][item][leftRef.synonym].insert(item);
                }
            }
        } 
        else if (isSynonymEvaluated(rightRef.synonym)) {
            QueryEvaluator::removeWithDifference(rightRef, leftRef, rightResults, leftResults);

            for (auto item : intersection) {
                if (isValueLeft && isValueRight) {
                    auto leftItems = QueryEvaluator::getKeysOrValues(leftRef, item);
                    auto rightItems = QueryEvaluator::getKeysOrValues(rightRef, item);
                    for (auto leftItem : leftItems) {
                        for (auto rightItem : rightItems) {
                            answerTable[leftRef.synonym][leftItem][rightRef.synonym].insert(rightItem);
                        }
                    }
                }
                else if (isValueLeft) {
                    auto leftItems = QueryEvaluator::getKeysOrValues(leftRef, item);
                    for (auto leftItem : leftItems) {
                        answerTable[leftRef.synonym][leftItem][rightRef.synonym].insert(item);
                    }
                }
                else if (isValueRight) {
                    auto rightItems = QueryEvaluator::getKeysOrValues(rightRef, item);
                    for (auto rightItem : rightItems) {
                        answerTable[leftRef.synonym][item][rightRef.synonym].insert(rightItem);
                    }
                }
                else {
                    answerTable[leftRef.synonym][item][rightRef.synonym].insert(item);
                }
            }
        }
        else {
            for (auto item : intersection) {
                if (isValueLeft && isValueRight) {
                    auto leftItems = QueryEvaluator::getKeysOrValues(leftRef, item);
                    auto rightItems = QueryEvaluator::getKeysOrValues(rightRef, item);
                    for (auto leftItem : leftItems) {
                        for (auto rightItem : rightItems) {
                            answerTable[rightRef.synonym][rightItem][leftRef.synonym].insert(leftItem);
                            answerTable[leftRef.synonym][leftItem][rightRef.synonym].insert(rightItem);
                        }
                    }
                }
                else if (isValueLeft) {
                    auto leftItems = QueryEvaluator::getKeysOrValues(leftRef, item);
                    for (auto leftItem : leftItems) {
                        answerTable[leftRef.synonym][leftItem][rightRef.synonym].insert(item);
                        answerTable[rightRef.synonym][item][leftRef.synonym].insert(leftItem);
                    }
                }
                else if (isValueRight) {
                    auto rightItems = QueryEvaluator::getKeysOrValues(rightRef, item);
                    for (auto rightItem : rightItems) {
                        answerTable[leftRef.synonym][item][rightRef.synonym].insert(rightItem);
                        answerTable[rightRef.synonym][rightItem][leftRef.synonym].insert(item);
                    }
                }
                else {
                    answerTable[rightRef.synonym][item][leftRef.synonym].insert(item);
                    answerTable[leftRef.synonym][item][rightRef.synonym].insert(item);
                }
            }
        }

        

        QueryEvaluator::setSynonymEvaluated(leftRef.synonym);
        QueryEvaluator::setSynonymEvaluated(rightRef.synonym);
        QueryEvaluator::setSynonymsEvaluatedTogether(leftRef.synonym, rightRef.synonym);
    }

    return true;
}

std::string QueryEvaluator::getKeyOrValue(Query::Reference leftRef, std::string key) {
    switch (leftRef.refAttribType) {
    case Query::ReferenceAttributeType::PROCNAME:
    case Query::ReferenceAttributeType::VARNAME:
        switch (leftRef.refDentityType) {
        case Query::DesignEntityType::CALL:
            return QueryPKBInterface::getInstance().getCall(key);

        case Query::DesignEntityType::PRINT:
            return QueryPKBInterface::getInstance().getPrint(key);

        case Query::DesignEntityType::READ:
            return QueryPKBInterface::getInstance().getRead(key);

        default:
            return key;
        }
    case Query::ReferenceAttributeType::VALUE:
    case Query::ReferenceAttributeType::STMTNUM:
    default:
        return key;
    }
}

std::vector<std::string> QueryEvaluator::getKeysOrValues(Query::Reference leftRef, std::string value) {
    std::vector<std::string> keys;
    switch (leftRef.refAttribType) {
    case Query::ReferenceAttributeType::PROCNAME:
    case Query::ReferenceAttributeType::VARNAME:
        switch (leftRef.refDentityType) {
        case Query::DesignEntityType::CALL:
            for (auto key : QueryPKBInterface::getInstance().getKeysCall(value)) {
                keys.push_back(key);
            }
            return keys;

        case Query::DesignEntityType::PRINT:
            for (auto key : QueryPKBInterface::getInstance().getKeysPrint(value)) {
                keys.push_back(key);
            }
            return keys;

        case Query::DesignEntityType::READ:
            for (auto key : QueryPKBInterface::getInstance().getKeysRead(value)) {
                keys.push_back(key);
            }
            return keys;

        default:
            return { value };
        }
    case Query::ReferenceAttributeType::VALUE:
    case Query::ReferenceAttributeType::STMTNUM:
    default:
        return { value };
    }
}

std::pair<std::vector<std::string>, bool> QueryEvaluator::getKeysOrValues(Query::Reference leftRef, std::vector<std::string> keys) {
    std::vector<std::string> values;
    switch (leftRef.refAttribType) {
    case Query::ReferenceAttributeType::PROCNAME:
    case Query::ReferenceAttributeType::VARNAME:
        switch (leftRef.refDentityType) {
        case Query::DesignEntityType::CALL:
            for (auto key : keys) {
                values.push_back(QueryPKBInterface::getInstance().getCall(key));
            }
            return { values, true };

        case Query::DesignEntityType::PRINT:
            for (auto key : keys) {
                values.push_back(QueryPKBInterface::getInstance().getPrint(key));
            }
            return { values, true };

        case Query::DesignEntityType::READ:
            for (auto key : keys) {
                values.push_back(QueryPKBInterface::getInstance().getRead(key));
            }
            return { values, true };

        default:
            return { keys, false };
        }
    case Query::ReferenceAttributeType::VALUE:
    case Query::ReferenceAttributeType::STMTNUM:
    default:
        return { keys, false };
    }
}

bool QueryEvaluator::findAndCompareWithSearchResults(Query::Reference leftRef, std::string rightRefString) {
    bool isValueLeft = false;
    bool isValid = false;
    std::vector<std::string> leftResults;
    if (isSynonymEvaluated(leftRef.synonym)) {
        leftResults = QueryEvaluator::extractValue(leftRef.synonym);
    }
    else {
        std::pair<std::vector<std::string>, bool> resultPair = QueryEvaluator::findReferenceAttribute(leftRef.refString, leftRef.refAttribType, leftRef.refType, leftRef.refDentityType);
        leftResults = resultPair.first;
        isValueLeft = resultPair.second;
    }
    if (leftResults.empty()) {
        return false;
    }
    QueryEvaluator::setSynonymEvaluated(leftRef.synonym);

    for (auto item : leftResults) {
        if (isValueLeft) {
            if (item != rightRefString) {
                auto leftItem = QueryEvaluator::getKeyOrValue(leftRef, item);
                QueryEvaluator::answerTableCleanRemove(leftRef.synonym, leftItem);
            }
            else {
                auto leftItems = QueryEvaluator::getKeysOrValues(leftRef, item);
                isValid = true;
                for (auto leftItem : leftItems) {
                    answerTable[leftRef.synonym][leftItem]["_"].insert(leftItem);
                }
            }
        }
        else {
            auto leftItem = QueryEvaluator::getKeyOrValue(leftRef, item);
            if (leftItem != rightRefString) {
                QueryEvaluator::answerTableCleanRemove(leftRef.synonym, item);
            }
            else {
                isValid = true;
                answerTable[leftRef.synonym][item]["_"].insert(item);
            }
        }
    }

    
    return isValid;
}

bool QueryEvaluator::solveWithClause(Query::Clause c) {
    // Left and right PROG_LINE
    if (c.leftRef.synonym == c.rightRef.synonym && c.leftRef.refType == Query::ReferenceType::SYNONYM && c.rightRef.refType == Query::ReferenceType::SYNONYM) {
        return true;
    }
    else if (c.leftRef.refDentityType == Query::DesignEntityType::PROG_LINE || c.rightRef.refDentityType == Query::DesignEntityType::PROG_LINE) {
        // Left PROG_LINE
        Query::ReferenceAttributeType refAttribType = c.rightRef.refAttribType;
        Query::Reference ref1 = c.rightRef;
        Query::Reference ref2 = c.leftRef;
        
        if (c.rightRef.refDentityType == Query::DesignEntityType::PROG_LINE) {
            // Right PROG_LINE
            refAttribType = c.leftRef.refAttribType;
            ref1 = c.leftRef;
            ref2 = c.rightRef;
        }
        ref2.synonym = ref2.refString;

        switch (refAttribType) {
        case Query::ReferenceAttributeType::VALUE:
        case Query::ReferenceAttributeType::STMTNUM:
            return QueryEvaluator::findAndCompareWithSearchResults(ref1, ref2);
            
        default:
            if (ref1.refType == Query::ReferenceType::INTEGER) {
                if (isSynonymEvaluated(ref2.synonym)) {
                    return QueryEvaluator::findAndCompareWithSearchResults(ref2, ref1.refString);
                }
                else {
                    answerTable[ref2.synonym][ref1.refString]["_"].clear();
                    answerTable[ref2.synonym][ref1.refString]["_"].insert(ref1.refString);
                    QueryEvaluator::setSynonymEvaluated(ref2.synonym);
                    return true;
                }
            }
            else {
                return false;
            }
        }
    }

    if (c.leftRef.refAttribType == Query::ReferenceAttributeType::PROCNAME || c.leftRef.refAttribType == Query::ReferenceAttributeType::VARNAME) {
        if (c.rightRef.refAttribType == Query::ReferenceAttributeType::PROCNAME || c.rightRef.refAttribType == Query::ReferenceAttributeType::VARNAME) {
            return QueryEvaluator::findAndCompareWithSearchResults(c.leftRef, c.rightRef);
        }
        else if (c.rightRef.refType == Query::ReferenceType::QUOTATION) {
            return QueryEvaluator::findAndCompareWithSearchResults(c.leftRef, c.rightRef.refString);
        }
    }
    else if (c.leftRef.refAttribType == Query::ReferenceAttributeType::VALUE || c.leftRef.refAttribType == Query::ReferenceAttributeType::STMTNUM) {
        if (c.rightRef.refAttribType == Query::ReferenceAttributeType::VALUE || c.rightRef.refAttribType == Query::ReferenceAttributeType::STMTNUM) {
            return QueryEvaluator::findAndCompareWithSearchResults(c.leftRef, c.rightRef);
        }
        else if (c.rightRef.refType == Query::ReferenceType::INTEGER) {
            return QueryEvaluator::findAndCompareWithSearchResults(c.leftRef, c.rightRef.refString);
        }
    }
    else if (c.leftRef.refType == Query::ReferenceType::INTEGER) {
        if (c.rightRef.refAttribType == Query::ReferenceAttributeType::VALUE || c.rightRef.refAttribType == Query::ReferenceAttributeType::STMTNUM) {
            return QueryEvaluator::findAndCompareWithSearchResults(c.rightRef, c.leftRef.refString);
        }
        else if (c.rightRef.refType == Query::ReferenceType::INTEGER) {
            return c.leftRef.refString == c.rightRef.refString;
        }
    }
    else if (c.leftRef.refType == Query::ReferenceType::QUOTATION) {
        if (c.rightRef.refAttribType == Query::ReferenceAttributeType::PROCNAME || c.rightRef.refAttribType == Query::ReferenceAttributeType::VARNAME) {
            return QueryEvaluator::findAndCompareWithSearchResults(c.rightRef, c.leftRef.refString);
        }
        else if (c.rightRef.refType == Query::ReferenceType::QUOTATION) {
            return c.leftRef.refString == c.rightRef.refString;
        }
    }
    return false;
}

//PQL2PKB call wrappers----------------------------------------------------------------------------------------------------------

//This function calls the relevant PQL2PKB interface functions to retrieve the possible values of a synonym.
std::vector<std::string> QueryEvaluator::getDesignEntityValues(std::string ent, Query::DesignEntityType type) {

    switch (type) {
    case Query::DesignEntityType::ASSIGN:
        return QueryPKBInterface::getInstance().getAllKeysAssign();
        break;

    case Query::DesignEntityType::CALL:
        return QueryPKBInterface::getInstance().getAllKeysCall();
        break;

    case Query::DesignEntityType::CONSTANT:
        return QueryPKBInterface::getInstance().getAllValuesConstant();
        break;

    case Query::DesignEntityType::IF:
        return QueryPKBInterface::getInstance().getAllKeysIf();
        break;

    case Query::DesignEntityType::PRINT:
        return QueryPKBInterface::getInstance().getAllKeysPrint();
        break;

    case Query::DesignEntityType::PROCEDURE:
        return QueryPKBInterface::getInstance().getAllValuesProcedure();
        break;

    case Query::DesignEntityType::READ:
        return QueryPKBInterface::getInstance().getAllKeysRead();
        break;

    case Query::DesignEntityType::PROG_LINE:
    case Query::DesignEntityType::STMT:
        return QueryPKBInterface::getInstance().getAllKeysStatement();
        break;

    case Query::DesignEntityType::VARIABLE:
        return QueryPKBInterface::getInstance().getAllValuesVariable();
        break;

    case Query::DesignEntityType::WHILE:
        return QueryPKBInterface::getInstance().getAllKeysWhile();
        break;

        //This case covers NONE and WILDCARD
    case Query::DesignEntityType::NONE:
    default:
        std::vector<std::string> empty;
        return empty;
    }
}

//This function checks that the ent input is of the DesignEntityType of the type input.
bool QueryEvaluator::assertDesignEntityType(std::string ent, Query::DesignEntityType type) {
    try {
        switch (type) {
        case Query::DesignEntityType::ASSIGN:
            return QueryPKBInterface::getInstance().hasKeyAssign(ent);
            break;

        case Query::DesignEntityType::CALL:
            return QueryPKBInterface::getInstance().hasKeyCall(ent);
            break;

        case Query::DesignEntityType::CONSTANT:
            return QueryPKBInterface::getInstance().hasValueConstant(ent);
            break;

        case Query::DesignEntityType::IF:
            return QueryPKBInterface::getInstance().hasKeyIf(ent);
            break;

        case Query::DesignEntityType::PRINT:
            return QueryPKBInterface::getInstance().hasKeyPrint(ent);
            break;

        case Query::DesignEntityType::PROCEDURE:
            return QueryPKBInterface::getInstance().hasValueProcedure(ent);
            break;

        case Query::DesignEntityType::READ:
            return QueryPKBInterface::getInstance().hasKeyRead(ent);
            break;

        case Query::DesignEntityType::PROG_LINE:
        case Query::DesignEntityType::STMT:
            return QueryPKBInterface::getInstance().hasKeyStatement(ent);
            break;

        case Query::DesignEntityType::VARIABLE:
            return QueryPKBInterface::getInstance().hasValueVariable(ent);
            break;

        case Query::DesignEntityType::WHILE:
            return QueryPKBInterface::getInstance().hasKeyWhile(ent);
            break;

            //This case covers NONE and WILDCARD
        case Query::DesignEntityType::NONE:
        default:
            return false;
        }
    }
    catch (...) {
        //std::stoi excepti0n is caught here. This implies the input is a string and will only be valid for asserting variables, constants, and procedures. All others will return false.
    }
    return false;
}

//This function calls the relevant PQL2PKB interface functions to retrieve the possible values of a synonym that matches the design abstraction
std::vector<std::string> QueryEvaluator::getDesignAbstractionValues(Query::DesignAbstractionType dAT, std::string name, Query::DesignEntityType type, bool isReverse) {
    if (!isReverse) {
        switch (dAT) {
        case Query::DesignAbstractionType::FOLLOWS: {
            std::string followsResult = QueryPKBInterface::getInstance().getFollowedBy(name);
            std::vector<std::string> result;
            if (followsResult != "") {
                result.push_back(followsResult);
            }
            return result;
        }
        case Query::DesignAbstractionType::FOLLOWS_STAR: {
            std::vector<std::string> followsStarResult = QueryPKBInterface::getInstance().getFollowedByStar(name);
            std::vector<std::string> result;
            for (std::string s : followsStarResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::MODIFIES: {
            std::vector<std::string> result;
            try {
                bool isNameProcedure = assertDesignEntityType(name, Query::DesignEntityType::PROCEDURE);

                std::vector<std::string> modifiesResult;
                if (isNameProcedure) {
                    modifiesResult = QueryPKBInterface::getInstance().getProcedureModifies(name);
                }
                else {
                    modifiesResult = QueryPKBInterface::getInstance().getModifies(name);
                }
                for (std::string s : modifiesResult) {
                    if (s != "") {
                        result.push_back(s);
                    }
                }
                return result;
            }
            catch (...) {
                return result;
            }
            break;
        }
        case Query::DesignAbstractionType::PARENT: {
            std::vector<std::string> parentResult = QueryPKBInterface::getInstance().getChild(name);
            std::vector<std::string> result;
            for (std::string s : parentResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::PARENT_STAR: {
            std::vector<std::string> parentStarResult = QueryPKBInterface::getInstance().getChildStar(name);
            std::vector<std::string> result;
            for (std::string s : parentStarResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::USES: {
            std::vector<std::string> result;
            try {
                bool isNameProcedure = assertDesignEntityType(name, Query::DesignEntityType::PROCEDURE);
                std::vector<std::string> usesResult;
                if (isNameProcedure) {
                    usesResult = QueryPKBInterface::getInstance().getProcedureUses(name);
                }
                else {
                    usesResult = QueryPKBInterface::getInstance().getUses(name);
                }

                for (std::string s : usesResult) {
                    if (s != "") {
                        result.push_back(s);
                    }
                }
                return result;
            }
            catch (...) {
                return result;
            }
            break;
        }
        case Query::DesignAbstractionType::CALLS: {
            bool isNameProcedure = assertDesignEntityType(name, Query::DesignEntityType::PROCEDURE);
            std::vector<std::string> callsResult;
            if (isNameProcedure) {
                callsResult = QueryPKBInterface::getInstance().getCalls(name);
            }
            else {
                //Keep return list empty.
            }
            std::vector<std::string> result;
            for (std::string s : callsResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::CALLS_STAR: {
            bool isNameProcedure = assertDesignEntityType(name, Query::DesignEntityType::PROCEDURE);
            std::vector<std::string> callsStarResult;
            if (isNameProcedure) {
                callsStarResult = QueryPKBInterface::getInstance().getCallsStar(name);
            }
            else {
                //Keep return list empty.
            }
            std::vector<std::string> result;
            for (std::string s : callsStarResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::NEXT: {
            std::vector<std::string> nextResult = QueryPKBInterface::getInstance().getNext(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::NEXT_STAR: {
            std::vector<std::string> nextResult = QueryDEInterface::getInstance().getNextStar(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::AFFECTS: {
            std::vector<std::string> nextResult = QueryDEInterface::getInstance().getAffects(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::AFFECTS_STAR: {
            std::vector<std::string> nextResult = QueryDEInterface::getInstance().getAffectsStar(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::NEXTBIP: {
            std::vector<std::string> nextResult = QueryPKBInterface::getInstance().getNextBip(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::NEXTBIP_STAR: {
            std::vector<std::string> nextResult = QueryPKBInterface::getInstance().getNextBipStar(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::AFFECTSBIP: {
            std::vector<std::string> nextResult = QueryPKBInterface::getInstance().getAffectsBip(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        /*case Query::DesignAbstractionType::AFFECTSBIP_STAR: {
            std::vector<std::string> nextResult = QueryDEInterface::getInstance().getAffectsStar(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }*/
        default:
            std::vector<std::string> empty;
            return empty;
        }
    }
    else {
        switch (dAT) {
        case Query::DesignAbstractionType::FOLLOWS: {
            std::string followsResult = QueryPKBInterface::getInstance().getFollows(name);
            std::vector<std::string> result;
            if (followsResult != "") {
                result.push_back(followsResult);
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::FOLLOWS_STAR: {
            std::vector<std::string> followsStarResult = QueryPKBInterface::getInstance().getFollowsStar(name);
            std::vector<std::string> result;
            for (std::string s : followsStarResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::MODIFIES: {
            std::vector<std::string> modifiesResult = QueryPKBInterface::getInstance().getModifiedBy(name);
            std::vector<std::string> result;
            for (std::string s : modifiesResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            modifiesResult = QueryPKBInterface::getInstance().getProcedureModifiedBy(name);
            for (std::string s : modifiesResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::PARENT: {
            std::string parentResult = QueryPKBInterface::getInstance().getParent(name);
            std::vector<std::string> result;
            if (parentResult != "") {
                result.push_back(parentResult);
            }
            return result;
            break;
        }

        case Query::DesignAbstractionType::PARENT_STAR: {
            std::vector<std::string> parentStarResult = QueryPKBInterface::getInstance().getParentStar(name);
            std::vector<std::string> result;
            for (std::string s : parentStarResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::USES: {
            std::vector<std::string> usesResult = QueryPKBInterface::getInstance().getUsedBy(name);
            std::vector<std::string> result;
            for (std::string s : usesResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            usesResult = QueryPKBInterface::getInstance().getProcedureUsedBy(name);
            for (std::string s : usesResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            return result;
            break;
        }
        case Query::DesignAbstractionType::CALLS: {
            bool isNameProcedure = assertDesignEntityType(name, Query::DesignEntityType::PROCEDURE);
            std::vector<std::string> calledByResult;
            if (isNameProcedure) {
                calledByResult = QueryPKBInterface::getInstance().getCalledBy(name);
            }
            else {
                //Keep return list empty.
            }
            std::vector<std::string> result;
            for (std::string s : calledByResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::CALLS_STAR: {
            bool isNameProcedure = assertDesignEntityType(name, Query::DesignEntityType::PROCEDURE);
            std::vector<std::string> calledByStarResult;
            if (isNameProcedure) {
                calledByStarResult = QueryPKBInterface::getInstance().getCalledByStar(name);
            }
            else {
                //Keep return list empty.
            }
            std::vector<std::string> result;
            for (std::string s : calledByStarResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::NEXT: {
            std::vector<std::string> previousResult = QueryPKBInterface::getInstance().getPrevious(name);
            std::vector<std::string> result;
            for (std::string s : previousResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::NEXT_STAR: {
            std::vector<std::string> previousResult = QueryDEInterface::getInstance().getPreviousStar(name);
            std::vector<std::string> result;
            for (std::string s : previousResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::AFFECTS: {
            std::vector<std::string> nextResult = QueryDEInterface::getInstance().getAffectedBy(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::AFFECTS_STAR: {
            std::vector<std::string> nextResult = QueryDEInterface::getInstance().getAffectedByStar(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::NEXTBIP: {
            std::vector<std::string> nextResult = QueryPKBInterface::getInstance().getPreviousBip(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::NEXTBIP_STAR: {
            std::vector<std::string> nextResult = QueryPKBInterface::getInstance().getPreviousBipStar(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        case Query::DesignAbstractionType::AFFECTSBIP: {
            std::vector<std::string> nextResult = QueryPKBInterface::getInstance().getAffectedByBip(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }
        /*case Query::DesignAbstractionType::AFFECTSBIP_STAR: {
            std::vector<std::string> nextResult = QueryDEInterface::getInstance().getAffectsStar(name);
            std::vector<std::string> result;
            for (std::string s : nextResult) {
                if (s != "") {
                    result.push_back(s);
                }
            }
            return result;
            break;
        }*/
        default:
            std::vector<std::string> empty;
            return empty;
        }
    }
}

//This function calls the relevant PQL2PKB interface functions to assert that the design abstraction exists between 2 synonyms
bool QueryEvaluator::assertDesignAbstractionValues(Query::DesignAbstractionType dAT, std::string var1, std::string var2) {
    switch (dAT) {
    case Query::DesignAbstractionType::FOLLOWS:
        return QueryPKBInterface::getInstance().isFollowedBy(var1, var2);
        break;
    case Query::DesignAbstractionType::FOLLOWS_STAR:
        return QueryPKBInterface::getInstance().isFollowedByStar(var1, var2);
        break;
    case Query::DesignAbstractionType::MODIFIES: {
        bool isNameProcedure = assertDesignEntityType(var1, Query::DesignEntityType::PROCEDURE);
        if (isNameProcedure) {
            return QueryPKBInterface::getInstance().isProcedureModifies(var1, var2);
        }
        return QueryPKBInterface::getInstance().isModifies(var1, var2);
        break; 
    }
    case Query::DesignAbstractionType::PARENT:
        return QueryPKBInterface::getInstance().isChild(var1, var2);
        break;
    case Query::DesignAbstractionType::PARENT_STAR:
        return QueryPKBInterface::getInstance().isChildStar(var1, var2);
        break;
    case Query::DesignAbstractionType::USES: {
        bool isNameProcedure = assertDesignEntityType(var1, Query::DesignEntityType::PROCEDURE);
        if (isNameProcedure) {
            return QueryPKBInterface::getInstance().isProcedureUses(var1, var2);
        }
        return QueryPKBInterface::getInstance().isUses(var1, var2);
        break;
    }
    case Query::DesignAbstractionType::CALLS:
        return QueryPKBInterface::getInstance().isCalls(var1, var2);
        break;
    case Query::DesignAbstractionType::CALLS_STAR:
        return QueryPKBInterface::getInstance().isCallsStar(var1, var2);
        break;
    case Query::DesignAbstractionType::NEXT:
        return QueryPKBInterface::getInstance().isNext(var1, var2);
        break;
    case Query::DesignAbstractionType::NEXT_STAR:
        return QueryDEInterface::getInstance().isNextStar(var1, var2);
        break;
    case Query::DesignAbstractionType::NEXTBIP:
        return QueryPKBInterface::getInstance().isNextBip(var1, var2);
        break;
    case Query::DesignAbstractionType::NEXTBIP_STAR:
        return QueryPKBInterface::getInstance().isNextBipStar(var1, var2);
        break;
    case Query::DesignAbstractionType::AFFECTS:
        return QueryDEInterface::getInstance().isAffects(var1, var2);
        break;
    case Query::DesignAbstractionType::AFFECTS_STAR:
        return QueryDEInterface::getInstance().isAffectsStar(var1, var2);
        break;
    case Query::DesignAbstractionType::AFFECTSBIP:
        return QueryPKBInterface::getInstance().isAffectsBip(var1, var2);
        break;
    //case Query::DesignAbstractionType::AFFECTSBIP_STAR:
    //    return QueryPKBInterface::getInstance().isAffectsBIPStar(var1, var2);
    //    break;

    default:
        break;
    }
    return false;
}


bool QueryEvaluator::IsDATEmpty(Query::DesignAbstractionType dAT) {
    switch (dAT) {
    case Query::DesignAbstractionType::FOLLOWS:
        return QueryPKBInterface::getInstance().getSizeFollows() == 0;
        break;
    case Query::DesignAbstractionType::FOLLOWS_STAR:
        return QueryPKBInterface::getInstance().getSizeFollowsStar() == 0;
        break;
    case Query::DesignAbstractionType::MODIFIES:
        return (QueryPKBInterface::getInstance().getSizeModifies() + QueryPKBInterface::getInstance().getSizeProcedureModifies() == 0);
        break;
    case Query::DesignAbstractionType::PARENT:
        return QueryPKBInterface::getInstance().getSizeParent() == 0;
        break;
    case Query::DesignAbstractionType::PARENT_STAR:
        return QueryPKBInterface::getInstance().getSizeParentStar() == 0;
        break;
    case Query::DesignAbstractionType::USES:
        return (QueryPKBInterface::getInstance().getSizeUses() + QueryPKBInterface::getInstance().getSizeProcedureUses() == 0);
        break;
    case Query::DesignAbstractionType::CALLS:
        return QueryPKBInterface::getInstance().getSizeCalls() == 0;
        break;
    case Query::DesignAbstractionType::CALLS_STAR:
        return QueryPKBInterface::getInstance().getSizeCallsStar() == 0;
        break;
    case Query::DesignAbstractionType::NEXT:
        return QueryPKBInterface::getInstance().getSizeNext() == 0;
        break;
    case Query::DesignAbstractionType::NEXT_STAR:
        //As a single Next relationship proves the existence of a Next* relationship, the size of the next table can serve as a replacement for the next* table.
        return QueryPKBInterface::getInstance().getSizeNext() == 0;
        break;
    default:
        break;
    }
    return false;
}

//general helper functions-------------------------------------------------------------------------------------------------------

//This function retrieves the DesignEntityType of a synonym, returning NONE if the synonym is not found in the synonymTable.
Query::DesignEntityType QueryEvaluator::getSynonymType(std::string syn) {
    Query::DesignEntityType d;

    if (synTable.find(syn) == synTable.end()) {
        d = Query::DesignEntityType::NONE;
    }
    else {
        d = synTable[syn];
    }
    return d;
}

//This function takes in a clauseList reference and sorts the clauseList inside based on the optimal evaluation order
void QueryEvaluator::optimiseClauseList(std::vector<Query::Clause>& clauseList) {
    if (isOptimize) {
        Optimiser::getInstance().optimise(clauseList);
    }
    else {
        std::vector<Query::Clause> sortedClauseList;

        //No need to sort if there is only 1 or less clauses to be evaluated.
        if (clauseList.size() <= 1) {
            return;
        }

        //Add pattern clauses to sortedList
        for (Query::Clause c : clauseList) {
            if (c.clauseType == Query::ClauseType::PATTERN) {
                sortedClauseList.push_back(c);
                //Optimisation: remove clause from current list?
            }
        }

        //Add suchthat clauses to sortedList
        for (Query::Clause c : clauseList) {
            if (c.clauseType == Query::ClauseType::SUCH_THAT) {
                sortedClauseList.push_back(c);
                //Optimisation: remove clause from current list?
            }
        }

        //Add with clauses to sortedList
        for (Query::Clause c : clauseList) {
            if (c.clauseType == Query::ClauseType::WITH) {
                sortedClauseList.push_back(c);
                //Optimisation: remove clause from current list?
            }
        }

        clauseList = sortedClauseList;
    }
}

bool QueryEvaluator::isSynonymEvaluated(std::string synonym) {
    if (evaluatedSynonyms.find(synonym) != evaluatedSynonyms.end()) {
        return true;
    }
    return false;
}

bool QueryEvaluator::isSynonymEvaluatedAlone(std::string synonym) {
    if (evaluatedSynonyms.find(synonym) != evaluatedSynonyms.end()) {
        if (evaluatedSynonyms[synonym].size() == 0) {
            return true;
        }
    }
    return false;
}

void QueryEvaluator::setSynonymEvaluated(std::string synonym) {
    if (evaluatedSynonyms.find(synonym) == evaluatedSynonyms.end()) {
        std::unordered_set<std::string> temp;
        evaluatedSynonyms[synonym] = temp;
    }

}

bool QueryEvaluator::isSynonymEvaluatedTogether(std::string synonym1, std::string synonym2) {
    if (evaluatedSynonyms.find(synonym1) != evaluatedSynonyms.end()) {
        if (evaluatedSynonyms[synonym1].find(synonym2) != evaluatedSynonyms[synonym1].end()) {
            return true;
        }
    }
    return false;
}

void QueryEvaluator::setSynonymsEvaluatedTogether(std::string synonym1, std::string synonym2) {
    evaluatedSynonyms[synonym1].insert(synonym2);
    evaluatedSynonyms[synonym2].insert(synonym1);
}

bool QueryEvaluator::isEvaluatedSeparately(Query::Element elem, std::vector<Query::Element> selectedSynonyms) {
    bool isEvaluatedSeparately = true;
    for (Query::Element e : selectedSynonyms) {
        if (isSynonymEvaluatedTogether(elem.synonymString, e.synonymString)) {
            isEvaluatedSeparately = false;
        }
    }
    return isEvaluatedSeparately;
}

std::vector<std::string> QueryEvaluator::extractValue(std::string synonym) {
    std::vector<std::string> values;
    if (answerTable.find(synonym) != answerTable.end()) {
        if (answerTable[synonym].size() > 0) {
            for (auto it : answerTable[synonym]) {
                values.push_back(it.first);
            }
        }
    }
    return values;
}

std::unordered_map<std::string, std::vector<std::string>> QueryEvaluator::extractPairValue(std::string synonym1, std::string synonym2) {
    std::unordered_map<std::string, std::vector<std::string>> values;
    if (answerTable.find(synonym1) != answerTable.end()) {
        if (answerTable[synonym1].size() > 0) {
            for (auto it : answerTable[synonym1]) {
                if (answerTable[synonym1][it.first].find(synonym2) != answerTable[synonym1][it.first].end()) {
                    if (answerTable[synonym2].size() > 0) {
                        for (auto it2 : answerTable[synonym1][it.first][synonym2]) {
                            values[it.first].push_back(it2);
                        }
                    }
                }
            }
        }
    }
    return values;
}

std::string QueryEvaluator::buildElementString(Query::Element e) {
    std::string synonym = e.synonymString;
    std::string attributeType;
    switch (e.elementAttribType) {
    case Query::ReferenceAttributeType::PROCNAME:
        attributeType = ".procName";
        break;
    case Query::ReferenceAttributeType::VARNAME:
        attributeType = ".varName";
        break;
    case Query::ReferenceAttributeType::VALUE:
        attributeType = ".value";
        break;
    case Query::ReferenceAttributeType::STMTNUM:
        attributeType = ".stmt#";
        break;
    case Query::ReferenceAttributeType::NONE:
    default:
        attributeType = "";
    }
    return synonym + attributeType;
}

void QueryEvaluator::tightenAnswerTable(std::string syn1, std::string syn2) {
    std::unordered_set<std::string> common;
    std::unordered_set<std::string> synonymsEvaluatedWithSyn1 = evaluatedSynonyms[syn1];
    std::unordered_set<std::string> synonymsEvaluatedWithSyn2 = evaluatedSynonyms[syn2];
    for (std::string s : synonymsEvaluatedWithSyn1) {
        if (synonymsEvaluatedWithSyn2.find(s) != synonymsEvaluatedWithSyn2.end()) {
            common.insert(s);
        }
    }

    for (std::string s : common) {
        if (answerTable.find(s) != answerTable.end()) {
            std::vector<std::string> sValues = extractValue(s);
            for (std::string v : sValues) {
                if (answerTable[s][v].find(syn1) == answerTable[s][v].end() || answerTable[s][v].find(syn2) == answerTable[s][v].end()) {
                    answerTableCleanRemove(s, v);
                }
            }
        }
    }

}

void QueryEvaluator::tightenAnswerTable() {
    std::vector<std::string> synonyms;
    for (auto entry : answerTable) {
        synonyms.push_back(entry.first);
    }
    for (std::string syn : synonyms){
        std::vector<std::string> synonymValues;
        std::unordered_set<std::string> synonymsEvaluatedWithSyn = evaluatedSynonyms[syn];
        for (auto value : answerTable[syn]) {
            synonymValues.push_back(value.first);
        }
        for(std::string value : synonymValues){
            for (std::string syn2 : synonymsEvaluatedWithSyn) {
                if (answerTable[syn][value].find(syn2) == answerTable[syn][value].end()) {
                    answerTableCleanRemove(syn, value);
                }
            }
        }
    }
}

//cleanRemove function for answerTable-------------------------------------------------------------------------------------------

//This function attempts to remove the entry answerTable[var1][var1value][var2][var2value] and related entry answerTable[var2][var2value]
//The function will be recursively called until all conflicting entries are removed.
void QueryEvaluator::answerTableCleanRemove(std::string var1, std::string var1value, std::string var2, std::string var2value) {
    if (answerTable[var1].size() == 0) {
        return;
    }
    else if (answerTable[var1][var1value].size() == 0) {
        answerTable[var1].erase(var1value);
    }
    else if (answerTable[var1][var1value][var2].size() == 0) {
        answerTable[var1][var1value].erase(var2);
    }
    else {
        answerTable[var1][var1value][var2].erase(var2value);
        if (answerTable[var1][var1value][var2].size() == 0) {
            answerTable[var1][var1value].erase(var2);
        }
        if (answerTable[var1][var1value].size() == 0) {
            answerTable[var1].erase(var1value);
        }
    }
    return;
}

void QueryEvaluator::answerTableCleanRemove(std::string var1, std::string var1Value) {
    if (answerTable.find(var1) != answerTable.end()) {
        if (answerTable[var1].find(var1Value) != answerTable[var1].end()) {
            std::vector<std::string> var2Refs;
            for (auto it : answerTable[var1][var1Value]) {
                var2Refs.push_back(it.first);
            }
            for (std::string var2 : var2Refs) {
                std::vector<std::string> var2Values;
                for (std::string var2Value : answerTable[var1][var1Value][var2]) {
                    var2Values.push_back(var2Value);
                }
                for (std::string var2Value : var2Values) {
                    answerTableCleanRemove(var1, var1Value, var2, var2Value);
                    answerTableCleanRemove(var2, var2Value, var1, var1Value);
                }
                if (answerTable[var1][var1Value][var2].size() == 0) {
                    answerTable[var1][var1Value].erase(var2);
                }
            }
            if (answerTable[var1][var1Value].size() == 0) {
                answerTable[var1].erase(var1Value);
            }
        }
    }

}