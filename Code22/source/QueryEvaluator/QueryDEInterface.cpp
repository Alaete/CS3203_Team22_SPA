#include "QueryDEInterface.h"

QueryDEInterface::QueryDEInterface() {}
QueryDEInterface::~QueryDEInterface() {}

//CACHE
void QueryDEInterface::clearTemporaryCache() {
    DesignExtractor::getInstance().clearNextStarCache();
}

//Design Abstractions (relRef)
//--Next*--------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryDEInterface::getNextStar(std::string firstLine) {
    try {
        int intFirstLineNumber = std::stoi(firstLine);
        std::unordered_set<int> intResult = DesignExtractor::getInstance().getNextStar(intFirstLineNumber);
        std::vector<std::string> string_result;
        for (int i : intResult) {
            if (i != -1) {
                string_result.push_back(std::to_string(i));
            }
        }
        return string_result;
    }
    catch (...) {
        return {};
    }
}

std::vector<std::string> QueryDEInterface::getPreviousStar(std::string nextLine) {
    try {
        int intNextLineNumber = std::stoi(nextLine);
        std::unordered_set<int> intResult = DesignExtractor::getInstance().getPreviousStar(intNextLineNumber);
        std::vector<std::string> string_result;
        for (int i : intResult) {
            if (i != -1) {
                string_result.push_back(std::to_string(i));
            }
        }
        return string_result;
    }
    catch (...) {
        return {};
    }
}

int QueryDEInterface::getSizeNextStar() {
    return DesignExtractor::getInstance().getSizeNextStar();
}
int QueryDEInterface::getSizePreviousStar() {
    return DesignExtractor::getInstance().getSizePreviousStar();
}
int QueryDEInterface::getAreaNextStar() {
    return DesignExtractor::getInstance().getAreaNextStar();
}

//----Assert----
bool QueryDEInterface::isNextStar(std::string firstLine, std::string secondLine) {
    int intFirstLineNumber;
    int intSecondLineNumber;
    try {
        intFirstLineNumber = std::stoi(firstLine);
        intSecondLineNumber = std::stoi(secondLine);
        return DesignExtractor::getInstance().isNextStar(intFirstLineNumber, intSecondLineNumber);
    }
    catch (...) {
        return false;
    }
}

//--Affects--------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryDEInterface::getAffects(std::string firstLine) {
    try {
        int intFirstLineNumber = std::stoi(firstLine);
        std::unordered_set<int> intResult = DesignExtractor::getInstance().getAffects(intFirstLineNumber);
        std::vector<std::string> string_result;
        for (int i : intResult) {
            if (i != -1) {
                string_result.push_back(std::to_string(i));
            }
        }
        return string_result;
    }
    catch (...) {
        return {};
    }
}

std::vector<std::string> QueryDEInterface::getAffectedBy(std::string nextLine) {
    try {
        int intNextLineNumber = std::stoi(nextLine);
        std::unordered_set<int> intResult = DesignExtractor::getInstance().getAffectedBy(intNextLineNumber);
        std::vector<std::string> string_result;
        for (int i : intResult) {
            if (i != -1) {
                string_result.push_back(std::to_string(i));
            }
        }
        return string_result;
    }
    catch (...) {
        return {};
    }
}

//----Assert----
bool QueryDEInterface::isAffects(std::string firstLine, std::string secondLine) {
    int intFirstLineNumber;
    int intSecondLineNumber;
    try {
        intFirstLineNumber = std::stoi(firstLine);
        intSecondLineNumber = std::stoi(secondLine);
        return DesignExtractor::getInstance().isAffects(intFirstLineNumber, intSecondLineNumber);
    }
    catch (...) {
        return false;
    }
}

//--Affects*--------------------------------------------------------------------------------------------------
//----Find----
std::vector<std::string> QueryDEInterface::getAffectsStar(std::string firstLine) {
    try {
        int intFirstLineNumber = std::stoi(firstLine);
        std::unordered_set<int> intResult = DesignExtractor::getInstance().getAffectsStar(intFirstLineNumber);
        std::vector<std::string> string_result;
        for (int i : intResult) {
            if (i != -1) {
                string_result.push_back(std::to_string(i));
            }
        }
        return string_result;
    }
    catch (...) {
        return {};
    }
}

std::vector<std::string> QueryDEInterface::getAffectedByStar(std::string nextLine) {
    try {
        int intNextLineNumber = std::stoi(nextLine);
        std::unordered_set<int> intResult = DesignExtractor::getInstance().getAffectedByStar(intNextLineNumber);
        std::vector<std::string> string_result;
        for (int i : intResult) {
            if (i != -1) {
                string_result.push_back(std::to_string(i));
            }
        }
        return string_result;
    }
    catch (...) {
        return {};
    }
}

//----Assert----
bool QueryDEInterface::isAffectsStar(std::string firstLine, std::string secondLine) {
    int intFirstLineNumber;
    int intSecondLineNumber;
    try {
        intFirstLineNumber = std::stoi(firstLine);
        intSecondLineNumber = std::stoi(secondLine);
        return DesignExtractor::getInstance().isAffectsStar(intFirstLineNumber, intSecondLineNumber);
    }
    catch (...) {
        return false;
    }
}
