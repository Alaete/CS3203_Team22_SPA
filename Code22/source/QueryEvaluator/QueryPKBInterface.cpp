#include "QueryPKBInterface.h"
#include "../PKB/PKB.h"
#include <iostream>

QueryPKBInterface::QueryPKBInterface() {}
QueryPKBInterface::~QueryPKBInterface() {}

//Design Abstractions (relRef)
//--Follow--------------------------------------------------------------------------------------------------
//----Find----
std::string QueryPKBInterface::getFollows(std::string lineNumber) {
    int result = PKB::getInstance().getFollows(std::stoi(lineNumber));
    std::string string_result = "";
    if (result != -1) {
        string_result = std::to_string(result);
    }
    return string_result;
}
std::string QueryPKBInterface::getFollowedBy(std::string lineNumber) {
    int result = PKB::getInstance().getFollowedBy(std::stoi(lineNumber));
    std::string string_result = "";
    if (result != -1) {
        string_result = std::to_string(result);
    }
    return string_result;
}
int QueryPKBInterface::getSizeFollows() {
    return  PKB::getInstance().getSizeFollows();
}

//----Assert----
bool QueryPKBInterface::isFollows(int lineNumber, int leaderLine) {
    return PKB::getInstance().isFollows(lineNumber, leaderLine);
}

bool QueryPKBInterface::isFollowedBy(std::string lineNumber, std::string followerLine) {
    return PKB::getInstance().isFollowedBy(std::stoi(lineNumber), std::stoi(followerLine));
}


//--Follow*-------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getFollowsStar(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getFollowsStar(std::stoi(lineNumber));
    std::vector<std::string> string_result;
    for (int i : result) {
        if (i != -1) {
            string_result.push_back(std::to_string(i));
        }
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getFollowedByStar(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getFollowedByStar(std::stoi(lineNumber));
    std::vector<std::string> string_result;
    for (int i : result) {
        if (i != -1) {
            string_result.push_back(std::to_string(i));
        }
    }
    return string_result;
}
int QueryPKBInterface::getSizeFollowsStar() {
    return  PKB::getInstance().getSizeFollowsStar();
}
int QueryPKBInterface::getAreaFollowsStar() {
    return PKB::getInstance().getAreaFollowsStar();
}
//----Assert----
bool QueryPKBInterface::isFollowsStar(int lineNumber, int leaderLine) {
    return PKB::getInstance().isFollowsStar(lineNumber, leaderLine);
}
bool QueryPKBInterface::isFollowsStar(int lineNumber, std::unordered_set<int> leaderLines) {
    return PKB::getInstance().isFollowsStar(lineNumber, leaderLines);
}

bool QueryPKBInterface::isFollowedByStar(std::string lineNumber, std::string followerLine) {
    return PKB::getInstance().isFollowedByStar(std::stoi(lineNumber), std::stoi(followerLine));
}
bool QueryPKBInterface::isFollowedByStar(int lineNumber, std::unordered_set<int> followerLines) {
    return PKB::getInstance().isFollowedByStar(lineNumber, followerLines);
}

//--Parent--------------------------------------------------------------------------------------------------
//----Find----
std::string QueryPKBInterface::getParent(std::string lineNumber) {
    int result = PKB::getInstance().getParent(std::stoi(lineNumber));
    std::string string_result = "";
    if (result != -1) {
        string_result = std::to_string(result);
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getChild(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getChild(std::stoi(lineNumber));
    std::vector<std::string> string_result;
    for (int i : result) {
        if (i != -1) {
            string_result.push_back(std::to_string(i));
        }
    }
    return string_result;
}
int QueryPKBInterface::getSizeParent() {
    return  PKB::getInstance().getSizeParent();
}
//----Assert----
bool QueryPKBInterface::isParent(int lineNumber, int parentLine) {
    return PKB::getInstance().isParent(lineNumber, parentLine);
}

bool QueryPKBInterface::isChild(std::string lineNumber, std::string childLine) {
    return PKB::getInstance().isChild(std::stoi(lineNumber), std::stoi(childLine));
}

bool QueryPKBInterface::isChild(int lineNumber, std::unordered_set<int> childLines) {
    return PKB::getInstance().isChild(lineNumber, childLines);
}

//--Parent*-------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getParentStar(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getParentStar(std::stoi(lineNumber));
    std::vector<std::string> string_result;
    for (int i : result) {
        if (i != -1) {
            string_result.push_back(std::to_string(i));
        }
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getChildStar(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getChildStar(std::stoi(lineNumber));
    std::vector<std::string> string_result;
    for (int i : result) {
        if (i != -1) {
            string_result.push_back(std::to_string(i));
        }
    }
    return string_result;
}
int QueryPKBInterface::getSizeParentStar() {
    return  PKB::getInstance().getSizeParentStar();
}
int QueryPKBInterface::getAreaParentStar() {
    return PKB::getInstance().getAreaParentStar();
}
//----Assert----
bool QueryPKBInterface::isParentStar(int lineNumber, int parentLine) {
    return PKB::getInstance().isParentStar(lineNumber, parentLine);
}
bool QueryPKBInterface::isParentStar(int lineNumber, std::unordered_set<int> parentLines) {
    return PKB::getInstance().isParentStar(lineNumber, parentLines);
}

bool QueryPKBInterface::isChildStar(std::string lineNumber, std::string childLine) {
    return PKB::getInstance().isChildStar(std::stoi(lineNumber), std::stoi(childLine));
}
bool QueryPKBInterface::isChildStar(int lineNumber, std::unordered_set<int> childLines) {
    return PKB::getInstance().isChildStar(lineNumber, childLines);
}

//--Uses----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getUses(std::string lineNumber) {
    std::unordered_set<std::string> result = PKB::getInstance().getUses(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (std::string s : result) {
        vector_result.push_back(s);
    }
    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getUsedBy(std::string name) {
    std::unordered_set<int> result = PKB::getInstance().getUsedBy(name);
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeUses() {
    return  PKB::getInstance().getSizeUses();
}
int QueryPKBInterface::getAreaUses() {
    return PKB::getInstance().getAreaUses();
}
//----Assert----
bool QueryPKBInterface::isUses(std::string lineNumber, std::string usedName) {
    return PKB::getInstance().isUses(std::stoi(lineNumber), usedName);
}
bool QueryPKBInterface::isUses(std::string lineNumber, std::unordered_set<std::string> usedNames) {
    return PKB::getInstance().isUses(std::stoi(lineNumber), usedNames);
}
bool QueryPKBInterface::isUsedBy(std::string name, std::string usedByLine) {
    return PKB::getInstance().isUsedBy(name, std::stoi(usedByLine));
}
bool QueryPKBInterface::isUsedBy(std::string name, std::unordered_set<std::string> usedByLines) {
    std::unordered_set<int> int_usedByLines;
    for (std::string s : usedByLines) {
        int_usedByLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isUsedBy(name, int_usedByLines);
}

//--ProcedureUses----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getProcedureUses(std::string procedureName) {
    try {
        int intProcedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
        std::unordered_set<std::string> result = PKB::getInstance().getProcedureUses(intProcedureIndex);
        std::vector<std::string> vector_result;
        for (std::string s : result) {
            vector_result.push_back(s);
        }
        return vector_result;
    }
    catch (...) {
        return {};
    }
}
std::vector<std::string> QueryPKBInterface::getProcedureUsedBy(std::string name) {
    std::unordered_set<int> result = PKB::getInstance().getProcedureUsedBy(name);
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(PKB::getInstance().getProcedure(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeProcedureUses() {
    return  PKB::getInstance().getSizeProcedureUses();
}
int QueryPKBInterface::getAreaProcedureUses() {
    return PKB::getInstance().getAreaProcedureUses();
}
//----Assert----
bool QueryPKBInterface::isProcedureUses(std::string procedureName, std::string usedVarName) {
    int intProcedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    return PKB::getInstance().isProcedureUses(intProcedureIndex, usedVarName);
}
//bool QueryPKBInterface::isProcedureUses(std::string lineNumber, std::unordered_set<std::string> usedNames) {
//    return PKB::getInstance().isProcedureUses(std::stoi(lineNumber), usedNames);
//}
bool QueryPKBInterface::isProcedureUsedBy(std::string varName, std::string usedByProcedure) {
    int intProcedureIndex = PKB::getInstance().getKeyProcedure(usedByProcedure);
    return PKB::getInstance().isProcedureUsedBy(varName, intProcedureIndex);
}
//bool QueryPKBInterface::isProcedureUsedBy(std::string name, std::unordered_set<std::string> usedByLines) {
//    std::unordered_set<int> int_usedByLines;
//    for (std::string s : usedByLines) {
//        int_usedByLines.insert(std::stoi(s));
//    }
//    return PKB::getInstance().isProcedureUsedBy(name, int_usedByLines);
//}

//--Modifies------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getModifies(std::string lineNumber) {
    std::unordered_set<std::string> result = PKB::getInstance().getModifies(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (std::string s : result) {
        vector_result.push_back(s);
    }

    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getModifiedBy(std::string name) {
    std::unordered_set<int> result = PKB::getInstance().getModifiedBy(name);
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeModifies() {
    return  PKB::getInstance().getSizeModifies();
}
int QueryPKBInterface::getAreaModifies() {
    return PKB::getInstance().getAreaModifies();
}
//----Assert----
bool QueryPKBInterface::isModifies(std::string lineNumber, std::string modifiedName) {
    return PKB::getInstance().isModifies(std::stoi(lineNumber), modifiedName);
}
bool QueryPKBInterface::isModifies(std::string lineNumber, std::unordered_set<std::string> modifiedNames) {
    return PKB::getInstance().isModifies(std::stoi(lineNumber), modifiedNames);
}

bool QueryPKBInterface::isModifiedBy(std::string name, std::string modifiedByLine) {
    return PKB::getInstance().isModifiedBy(name, std::stoi(modifiedByLine));
}
bool QueryPKBInterface::isModifiedBy(std::string name, std::unordered_set<std::string> modifiedByLines) {
    std::unordered_set<int> int_modifiedByNames;
    for (std::string s : modifiedByLines) {
        int_modifiedByNames.insert(std::stoi(s));
    }
    return PKB::getInstance().isModifiedBy(name, int_modifiedByNames);
}

//--ProcedureModifies------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getProcedureModifies(std::string procedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<std::string> resultP = PKB::getInstance().getProcedureModifies(procedureIndex);
    std::vector<std::string> vector_result;
    for (std::string s : resultP) {
        vector_result.push_back(s);
    }
    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getProcedureModifiedBy(std::string name) {
    std::vector<std::string> vector_result;
    std::unordered_set<int> resultP = PKB::getInstance().getProcedureModifiedBy(name);
    for (int i : resultP) {
        vector_result.push_back(PKB::getInstance().getProcedure(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeProcedureModifies() {
    return  PKB::getInstance().getSizeProcedureModifies();
}
int QueryPKBInterface::getAreaProcedureModifies() {
    return PKB::getInstance().getAreaProcedureModifies();
}
//----Assert----
bool QueryPKBInterface::isProcedureModifies(std::string procedureName, std::string modifiedVarName) {
    int intProcedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    return PKB::getInstance().isProcedureModifies(intProcedureIndex, modifiedVarName);
}
//bool QueryPKBInterface::isProcedureModifies(std::string lineNumber, std::unordered_set<std::string> modifiedNames) {
//    return PKB::getInstance().isProcedureModifies(std::stoi(lineNumber), modifiedNames);
//}

bool QueryPKBInterface::isProcedureModifiedBy(std::string varName, std::string modifiedByProcedureName) {
    int intProcedureIndex = PKB::getInstance().getKeyProcedure(modifiedByProcedureName);
    return PKB::getInstance().isProcedureModifiedBy(varName, intProcedureIndex);
}
//bool QueryPKBInterface::isProcedureModifiedBy(std::string name, std::unordered_set<std::string> modifiedByLines) {
//    std::unordered_set<int> int_modifiedByNames;
//    for (std::string s : modifiedByLines) {
//        int_modifiedByNames.insert(std::stoi(s));
//    }
//    return PKB::getInstance().isProcedureModifiedBy(name, int_modifiedByNames);
//}

//--Calls----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getCalls(std::string procedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<int> result = PKB::getInstance().getCalls(procedureIndex);
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(PKB::getInstance().getProcedure(i));
    }
    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getCalledBy(std::string procedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<int> result = PKB::getInstance().getCalledBy(procedureIndex);
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(PKB::getInstance().getProcedure(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeCalls() {
    return  PKB::getInstance().getSizeCalls();
}
int QueryPKBInterface::getAreaCalls() {
    return PKB::getInstance().getAreaCalls();
}
//----Assert----
bool QueryPKBInterface::isCalls(std::string procedureName, std::string calledprocedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    int calledProcedureIndex = PKB::getInstance().getKeyProcedure(calledprocedureName);
    return PKB::getInstance().isCalls(procedureIndex, calledProcedureIndex);
}
bool QueryPKBInterface::isCalls(std::string procedureName, std::unordered_set<std::string> calledProcedureNames) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<int> calledProcedureIndexes;
    for (std::string s : calledProcedureNames) {
        calledProcedureIndexes.insert(PKB::getInstance().getKeyProcedure(s));
    }
    return PKB::getInstance().isCalls(procedureIndex, calledProcedureIndexes);
}
bool QueryPKBInterface::isCalledBy(std::string procedureName, std::string calledByProcedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    int calledProcedureIndex = PKB::getInstance().getKeyProcedure(calledByProcedureName);
    return PKB::getInstance().isCalledBy(procedureIndex, calledProcedureIndex);
}
bool QueryPKBInterface::isCalledBy(std::string procedureName, std::unordered_set<std::string> calledByProcedureNames) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<int> calledByProcedureIndexes;
    for (std::string s : calledByProcedureNames) {
        calledByProcedureIndexes.insert(PKB::getInstance().getKeyProcedure(s));
    }
    return PKB::getInstance().isCalledBy(procedureIndex, calledByProcedureIndexes);
}

//--CallsStar----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getCallsStar(std::string procedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<int> result = PKB::getInstance().getCallsStar(procedureIndex);
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(PKB::getInstance().getProcedure(i));
    }
    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getCalledByStar(std::string procedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<int> result = PKB::getInstance().getCalledByStar(procedureIndex);
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(PKB::getInstance().getProcedure(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeCallsStar() {
    return  PKB::getInstance().getSizeCallsStar();
}
int QueryPKBInterface::getAreaCallsStar() {
    return PKB::getInstance().getAreaCallsStar();
}
//----Assert----
bool QueryPKBInterface::isCallsStar(std::string procedureName, std::string calledprocedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    int calledProcedureIndex = PKB::getInstance().getKeyProcedure(calledprocedureName);
    return PKB::getInstance().isCallsStar(procedureIndex, calledProcedureIndex);
}
bool QueryPKBInterface::isCallsStar(std::string procedureName, std::unordered_set<std::string> calledProcedureNames) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<int> calledProcedureIndexes;
    for (std::string s : calledProcedureNames) {
        calledProcedureIndexes.insert(PKB::getInstance().getKeyProcedure(s));
    }
    return PKB::getInstance().isCallsStar(procedureIndex, calledProcedureIndexes);
}
bool QueryPKBInterface::isCalledByStar(std::string procedureName, std::string calledByProcedureName) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    int calledProcedureIndex = PKB::getInstance().getKeyProcedure(calledByProcedureName);
    return PKB::getInstance().isCalledByStar(procedureIndex, calledProcedureIndex);
}
bool QueryPKBInterface::isCalledByStar(std::string procedureName, std::unordered_set<std::string> calledByProcedureNames) {
    int procedureIndex = PKB::getInstance().getKeyProcedure(procedureName);
    std::unordered_set<int> calledByProcedureIndexes;
    for (std::string s : calledByProcedureNames) {
        calledByProcedureIndexes.insert(PKB::getInstance().getKeyProcedure(s));
    }
    return PKB::getInstance().isCalledByStar(procedureIndex, calledByProcedureIndexes);
}

//--Next----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getNext(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getNext(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getPrevious(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getPrevious(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeNext() {
    return  PKB::getInstance().getSizeNext();
}
int QueryPKBInterface::getAreaNext() {
    return PKB::getInstance().getAreaNext();
}
//----Assert----
bool QueryPKBInterface::isNext(std::string lineNumber, std::string nextLine) {
    return PKB::getInstance().isNext(std::stoi(lineNumber), std::stoi(nextLine));
}
bool QueryPKBInterface::isNext(std::string lineNumber, std::unordered_set<std::string> nextLines) {
    std::unordered_set<int> int_nextLines;
    for (std::string s : nextLines) {
        int_nextLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isNext(std::stoi(lineNumber), int_nextLines);
}
bool QueryPKBInterface::isPrevious(std::string lineNumber, std::string previousLine) {
    return PKB::getInstance().isPrevious(std::stoi(lineNumber), std::stoi(previousLine));
}
bool QueryPKBInterface::isPrevious(std::string lineNumber, std::unordered_set<std::string> previousLines) {
    std::unordered_set<int> int_previousLines;
    for (std::string s : previousLines) {
        int_previousLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isPrevious(std::stoi(lineNumber), int_previousLines);
}

//--NextBip----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getNextBip(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getNextBip(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getPreviousBip(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getPreviousBip(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeNextBip() {
    return  PKB::getInstance().getSizeNextBip();
}
int QueryPKBInterface::getAreaNextBip() {
    return PKB::getInstance().getAreaNextBip();
}
//----Assert----
bool QueryPKBInterface::isNextBip(std::string lineNumber, std::string nextLine) {
    return PKB::getInstance().isNextBip(std::stoi(lineNumber), std::stoi(nextLine));
}
bool QueryPKBInterface::isNextBip(std::string lineNumber, std::unordered_set<std::string> nextLines) {
    std::unordered_set<int> int_nextLines;
    for (std::string s : nextLines) {
        int_nextLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isNextBip(std::stoi(lineNumber), int_nextLines);
}
bool QueryPKBInterface::isPreviousBip(std::string lineNumber, std::string previousLine) {
    return PKB::getInstance().isPreviousBip(std::stoi(lineNumber), std::stoi(previousLine));
}
bool QueryPKBInterface::isPreviousBip(std::string lineNumber, std::unordered_set<std::string> previousLines) {
    std::unordered_set<int> int_previousLines;
    for (std::string s : previousLines) {
        int_previousLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isPreviousBip(std::stoi(lineNumber), int_previousLines);
}

//--AffectsBip----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAffectsBip(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getAffectsBip(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getAffectedByBip(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getAffectedByBip(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeAffectsBip() {
    return  PKB::getInstance().getSizeAffectsBip();
}
int QueryPKBInterface::getAreaAffectsBip() {
    return PKB::getInstance().getAreaAffectsBip();
}
//----Assert----
bool QueryPKBInterface::isAffectsBip(std::string lineNumber, std::string nextLine) {
    return PKB::getInstance().isAffectsBip(std::stoi(lineNumber), std::stoi(nextLine));
}
bool QueryPKBInterface::isAffectsBip(std::string lineNumber, std::unordered_set<std::string> nextLines) {
    std::unordered_set<int> int_nextLines;
    for (std::string s : nextLines) {
        int_nextLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isAffectsBip(std::stoi(lineNumber), int_nextLines);
}
bool QueryPKBInterface::isAffectedByBip(std::string lineNumber, std::string previousLine) {
    return PKB::getInstance().isAffectedByBip(std::stoi(lineNumber), std::stoi(previousLine));
}
bool QueryPKBInterface::isAffectedByBip(std::string lineNumber, std::unordered_set<std::string> previousLines) {
    std::unordered_set<int> int_previousLines;
    for (std::string s : previousLines) {
        int_previousLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isAffectedByBip(std::stoi(lineNumber), int_previousLines);
}

//--NextBipStar----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getNextBipStar(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getNextBipStar(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
std::vector<std::string> QueryPKBInterface::getPreviousBipStar(std::string lineNumber) {
    std::unordered_set<int> result = PKB::getInstance().getPreviousBipStar(std::stoi(lineNumber));
    std::vector<std::string> vector_result;
    for (int i : result) {
        vector_result.push_back(std::to_string(i));
    }
    return vector_result;
}
int QueryPKBInterface::getSizeNextBipStar() {
    return  PKB::getInstance().getSizeNextBipStar();
}
int QueryPKBInterface::getAreaNextBipStar() {
    return PKB::getInstance().getAreaNextBipStar();
}
//----Assert----
bool QueryPKBInterface::isNextBipStar(std::string lineNumber, std::string nextLine) {
    return PKB::getInstance().isNextBipStar(std::stoi(lineNumber), std::stoi(nextLine));
}
bool QueryPKBInterface::isNextBipStar(std::string lineNumber, std::unordered_set<std::string> nextLines) {
    std::unordered_set<int> int_nextLines;
    for (std::string s : nextLines) {
        int_nextLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isNextBipStar(std::stoi(lineNumber), int_nextLines);
}
bool QueryPKBInterface::isPreviousBipStar(std::string lineNumber, std::string previousLine) {
    return PKB::getInstance().isPreviousBipStar(std::stoi(lineNumber), std::stoi(previousLine));
}
bool QueryPKBInterface::isPreviousBipStar(std::string lineNumber, std::unordered_set<std::string> previousLines) {
    std::unordered_set<int> int_previousLines;
    for (std::string s : previousLines) {
        int_previousLines.insert(std::stoi(s));
    }
    return PKB::getInstance().isPreviousBipStar(std::stoi(lineNumber), int_previousLines);
}

//Design Entities (entRef)
//--Assign--------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllKeysAssign() {
    std::vector<int> result = PKB::getInstance().getAllKeysAssign();
    std::vector<std::string> string_result;
    for (int i : result) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}
std::pair<std::string, std::string> QueryPKBInterface::getAssign(std::string lineNumber) { //For pattern clauses
    return PKB::getInstance().getAssign(std::stoi(lineNumber));
}
int QueryPKBInterface::getSizeAssign() {
    return PKB::getInstance().getSizeAssign();
}
//----Assert----
bool QueryPKBInterface::hasKeyAssign(std::string lineNumber) {
    return PKB::getInstance().hasKeyAssign(std::stoi(lineNumber));
}

//--Statement-----------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllKeysStatement() {
    std::vector<int> result = PKB::getInstance().getAllKeysStatement();
    std::vector<std::string> string_result;
    for (int i : result) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}
//----Assert----
bool QueryPKBInterface::hasKeyStatement(std::string lineNumber) {
    return PKB::getInstance().hasKeyStatement(std::stoi(lineNumber));
}

//--Read----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllKeysRead() {
    std::vector<int> result = PKB::getInstance().getAllKeysRead();
    std::vector<std::string> string_result;
    for (int i : result) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getAllValuesRead() {
    return PKB::getInstance().getAllValuesRead();
}
//----Assert----
bool QueryPKBInterface::hasKeyRead(std::string lineNumber) {
    return PKB::getInstance().hasKeyRead(std::stoi(lineNumber));
}
//----Get----
std::string QueryPKBInterface::getRead(std::string lineNumber) {
    try {
        int intLineNumber = std::stoi(lineNumber);
        return PKB::getInstance().getRead(intLineNumber);
    }
    catch (...) {
        return "";
    }
}
std::vector<std::string> QueryPKBInterface::getKeysRead(std::string value) {
    std::vector<std::string> string_result;
    for (int i : PKB::getInstance().getKeysRead(value)) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}

//--Print---------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllKeysPrint() {
    std::vector<int> result = PKB::getInstance().getAllKeysPrint();
    std::vector<std::string> string_result;
    for (int i : result) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getAllValuesPrint() {
    return PKB::getInstance().getAllValuesPrint();
}
//----Assert----
bool QueryPKBInterface::hasKeyPrint(std::string lineNumber) {
    return PKB::getInstance().hasKeyPrint(std::stoi(lineNumber));
}
//----Get----
std::string QueryPKBInterface::getPrint(std::string lineNumber) {
    try {
        int intLineNumber = std::stoi(lineNumber);
        return PKB::getInstance().getPrint(intLineNumber);
    }
    catch (...) {
        return "";
    }
}

std::vector<std::string> QueryPKBInterface::getKeysPrint(std::string value) {
    std::vector<std::string> string_result;
    for (int i : PKB::getInstance().getKeysPrint(value)) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}

//--Call----------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllKeysCall() {
    std::vector<int> result = PKB::getInstance().getAllKeysCall();
    std::vector<std::string> string_result;
    for (int i : result) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getAllValuesCall() {
    return PKB::getInstance().getAllValuesCall();
}
//----Assert----
bool QueryPKBInterface::hasKeyCall(std::string lineNumber) {
    return PKB::getInstance().hasKeyCall(std::stoi(lineNumber));
}
//----Get----
std::string QueryPKBInterface::getCall(std::string lineNumber) {
    try {
        int intLineNumber = std::stoi(lineNumber);
        return PKB::getInstance().getCall(intLineNumber);
    }
    catch (...) {
        return "";
    }
}
std::vector<std::string> QueryPKBInterface::getKeysCall(std::string value) {
    std::vector<std::string> string_result;
    for (int i : PKB::getInstance().getKeysCall(value)) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}

//--While---------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllKeysWhile() {
    std::vector<int> result = PKB::getInstance().getAllKeysWhile();
    std::vector<std::string> string_result;
    for (int i : result) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getWhile(std::string lineNumber) {
    try {
        int intLineNumber = std::stoi(lineNumber);
        std::unordered_set<std::string> result = PKB::getInstance().getWhile(intLineNumber);
        std::vector<std::string> vector_result;
        for (std::string s : result) {
            vector_result.push_back(s);
        }
        return vector_result;
    }
    catch (...) {
        return {};
    }
}
int QueryPKBInterface::getAreaWhile() {
    return PKB::getInstance().getAreaWhile();
}
//----Assert----
bool QueryPKBInterface::hasKeyWhile(std::string lineNumber) {
    return PKB::getInstance().hasKeyWhile(std::stoi(lineNumber));
}

//--If------------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllKeysIf() {
    std::vector<int> result = PKB::getInstance().getAllKeysIf();
    std::vector<std::string> string_result;
    for (int i : result) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getIf(std::string lineNumber) {
    try {
        int intLineNumber = std::stoi(lineNumber);
        std::unordered_set<std::string> result = PKB::getInstance().getIf(intLineNumber);
        std::vector<std::string> vector_result;
        for (std::string s : result) {
            vector_result.push_back(s);
        }
        return vector_result;
    }
    catch (...) {
        return {};
    }
}
int QueryPKBInterface::getAreaIf() {
    return PKB::getInstance().getAreaIf();
}
//----Assert----
bool QueryPKBInterface::hasKeyIf(std::string lineNumber) {
    return PKB::getInstance().hasKeyIf(std::stoi(lineNumber));
}

//--Variable------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllValuesVariable() {
    return PKB::getInstance().getAllValuesVariable();
}
//----Assert----
bool QueryPKBInterface::hasKeyVariable(std::string index) {
    return PKB::getInstance().hasKeyVariable(std::stoi(index));
}


bool QueryPKBInterface::hasValueVariable(std::string varName) {
    std::vector<std::string> varList = PKB::getInstance().getAllValuesVariable();
    if (varList.empty()) {
        return false;
    }
    else {
        if (std::find(varList.begin(), varList.end(), varName) != varList.end()) {
            return true;
        }
    }
    return false;
}

//--Constant------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllKeysConstant() {
    std::vector<int> result = PKB::getInstance().getAllKeysConstant();
    std::vector<std::string> string_result;
    for (int i : result) {
        string_result.push_back(std::to_string(i));
    }
    return string_result;
}
std::vector<std::string> QueryPKBInterface::getAllValuesConstant() {
    std::vector<std::unordered_set<int>> result = PKB::getInstance().getAllValuesConstant();
    std::vector<std::string> string_result;
    for (auto set : result) {
        for (int i : set) {
            string_result.push_back(std::to_string(i));
        }
    }
    return string_result;
}
//----Assert----
bool QueryPKBInterface::hasKeyConstant(std::string lineNumber) {
    return PKB::getInstance().hasKeyConstant(std::stoi(lineNumber));
}
bool QueryPKBInterface::hasValueConstant(std::string varName) {
    std::vector<std::string> constList = PKB::getInstance().getAllValuesVariable();
    if (constList.empty()) {
        return false;
    }
    else {
        if (std::find(constList.begin(), constList.end(), varName) != constList.end()) {
            return true;
        }
    }
    return false;
}

//--Procedure-----------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryPKBInterface::getAllValuesProcedure() {
    return PKB::getInstance().getAllValuesProcedure();
}

//----Assert----
bool QueryPKBInterface::hasKeyProcedure(std::string lineNumber) {
    return PKB::getInstance().hasKeyProcedure(std::stoi(lineNumber));
}
bool QueryPKBInterface::hasValueProcedure(std::string procName) {
    std::vector<std::string> procList = PKB::getInstance().getAllValuesProcedure();
    if (procList.empty()) {
        return false;
    }
    else {
        if (std::find(procList.begin(), procList.end(), procName) != procList.end()) {
            return true;
        }
    }
    return false;
}


