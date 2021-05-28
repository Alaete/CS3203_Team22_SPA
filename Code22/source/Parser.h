#pragma once

#include <algorithm>
#include <fstream>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "PKB/PKB.h"

class Parser {
public:
    struct ParserException : public std::exception {
        std::string message;
        const char* what() const noexcept override {
            return message.c_str();
        }
        explicit ParserException(std::string message) {
            this->message = std::move(message);
        }
    };
    ~Parser();
    Parser(Parser const&) = delete;
    void operator=(Parser const&) = delete;
    static Parser& getInstance();
    void parseProgram(const std::string& filename);

private:
    int lineNumber_ = 0;
    int currentProcedureIndex_ = -1;
    std::ifstream fileStream_;
    std::stack<int> parentStack_;
    Parser();
    std::string getNextToken();
    int parseProcedure();
    void parseStatementList(bool isProcedure);
    void parseReadStatement();
    void parsePrintStatement();
    void parseCallStatement();
    void parseIfStatement();
    void parseWhileStatement();
    void parseAssignStatement(std::string token);
    void parseExpression();
    int parseBracketedExpression(int statementType);
    void parseConditionalExpression(int statementType);
    void throwParserException(std::string message);
    void throwProcedureParserException(std::string message);
    void throwCallParserException(std::string procedureName);
    void extractCalls();
    void extractCallsStar();
    void recursiveExtractCallsStar(int procedureIndex, std::vector<bool> &visited, std::vector<bool> &recursionVisited);
    static bool validateName(std::string token);
    static bool validateInteger(std::string token);
};
