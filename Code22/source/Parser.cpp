#include <iostream>

#include "Parser.h"
#include "PKB/PKB.h"
#include "ShuntingYard.h"

Parser::Parser() = default;
Parser::~Parser() = default;

Parser& Parser::getInstance() {
    static Parser instance;
    return instance;
}

std::string Parser::getNextToken() {
    char c;
    std::unordered_set<char> invalidPunctuation = { '"', '#', '$', '\'', ',', '.', '\\', ':', '?', '@', '[', ']', '^', '_', '`', '~' };
    do {
        fileStream_.get(c);
        if (fileStream_.eof()) {
            return "EOF";
        }
    } while (isspace(c));

    std::string token(1, c);
    if (ispunct(c)) {
        if (invalidPunctuation.find(c) != invalidPunctuation.end()) {
            throwParserException("Invalid token");
        }
        else if (c == '>' || c == '<' || c == '=' || c == '!') {
            if (fileStream_.peek() == '=') {
                fileStream_.get(c);
                token += c;
            }
        }
        else if (c == '|') {
            if (fileStream_.peek() == '|') {
                fileStream_.get(c);
                token += c;
            }
        }
        else if (c == '&') {
            if (fileStream_.peek() == '&') {
                fileStream_.get(c);
                token += c;
            }
        }
        return token;
    }
    if (iscntrl(c)) {
        throwParserException("Invalid token");
    }
    while (isalnum(fileStream_.peek())) {
        fileStream_.get(c);
        token += c;
    }
    return token;
}

void Parser::parseProgram(const std::string & filename) {
    fileStream_.open(filename);
    std::string token;
    while (Parser::parseProcedure());
    extractCalls();
    extractCallsStar();
    lineNumber_ = 0;
    fileStream_.close();
    std::stack<int>().swap(parentStack_);
}

int Parser::parseProcedure() {
    std::string token;
    token = getNextToken();
    if (token == "EOF") {
        return 0;
    }
    else if (token != "procedure") {
        throwProcedureParserException("Keyword 'procedure' not found");
    }
    token = getNextToken();
    std::vector<std::string> procedureNames = PKB::getInstance().getAllValuesProcedure();
    if (!validateName(token)) {
        throwProcedureParserException("Invalid procedure name");
    }
    else {
        if (std::find(procedureNames.begin(), procedureNames.end(), token) != procedureNames.end()) {
            throwProcedureParserException("Duplicate procedure name");
        }
        currentProcedureIndex_ = PKB::getInstance().insertProcedure(token);
    }
    parseStatementList(true);
    return 1;
}

void Parser::parseStatementList(bool isProcedure) {
    int startLineNumber;
    std::string token;
    std::vector<int> statementList;
    std::unordered_set<std::string> statementTypes = { "read", "print", "call", "while", "if" };
    token = getNextToken();
    if (token != "{") {
        throwParserException("Opening brace not found");
    }
    while (true) {
        token = getNextToken();
        if (token == "}") {
            break;
        } 
        else {
            lineNumber_++;
            statementList.push_back(lineNumber_);
            if (!parentStack_.empty()) {
                PKB::getInstance().insertParent(lineNumber_, parentStack_.top());
            }
            if (token == "EOF") {
                throwParserException("Closing brace not found");
            }
            else if (statementTypes.find(token) != statementTypes.end()) {
                PKB::getInstance().insertStatement(lineNumber_, token);
                if (token == "read") {
                    parseReadStatement();
                }
                else if (token == "print") {
                    parsePrintStatement();
                }
                else if (token == "call") {
                    parseCallStatement();
                }
                else if (token == "while") {
                    parseWhileStatement();
                }
                else if (token == "if") {
                    parseIfStatement();
                }
            }
            else if (validateName(token)) {
                PKB::getInstance().insertStatement(lineNumber_, "assign");
                parseAssignStatement(token);
            }
            else {
                throwParserException("Invalid statement");
            }
        }
    }
    if (statementList.empty()) {
        throwParserException("Empty statement list");
    }
    int previousStatementNumber = 0;
    for (auto& statementNumber : statementList) {
        if (previousStatementNumber == 0) {
            previousStatementNumber = statementNumber;
        }
        else {
            PKB::getInstance().insertFollows(statementNumber, previousStatementNumber);
            previousStatementNumber = statementNumber;
        }
    }
    startLineNumber = statementList.front();
    if (isProcedure) {
        std::unordered_set<int> procedureStatementListSet;
        for (int statement = startLineNumber; statement <= lineNumber_; ++statement) {
            procedureStatementListSet.insert(statement);
        }
        PKB::getInstance().insertProcedureStatementList(currentProcedureIndex_, procedureStatementListSet);
    }
    else {
        std::unordered_set<int> statementListSet(statementList.begin(), statementList.end());
        PKB::getInstance().insertStatementList(startLineNumber, statementListSet);
    }
}

void Parser::parseReadStatement() {
    std::string token;
    token = getNextToken();
    if (!validateName(token)) {
        throwParserException("Invalid variable name");
    }
    PKB::getInstance().insertRead(lineNumber_, token);
    PKB::getInstance().insertVariable(token);
    token = getNextToken();
    if (token != ";") {
        throwParserException("Semicolon not found");
    }
}

void Parser::parsePrintStatement() {
    std::string token;
    token = getNextToken();
    if (!validateName(token)) {
        throwParserException("Invalid variable name");
    }
    PKB::getInstance().insertPrint(lineNumber_, token);
    PKB::getInstance().insertVariable(token);
    token = getNextToken();
    if (token != ";") {
        throwParserException("Semicolon not found");
    }
}

void Parser::parseCallStatement() {
    std::string token;
    token = getNextToken();
    if (!validateName(token)) {
        throwParserException("Invalid procedure name");
    }
    if (token == PKB::getInstance().getProcedure(currentProcedureIndex_)) {
        throwParserException("Recursive call");
    }
    PKB::getInstance().insertCall(lineNumber_, token);
    token = getNextToken();
    if (token != ";") {
        throwParserException("Semicolon not found");
    }
}

void Parser::parseAssignStatement(std::string token) {
    if (!validateName(token)) {
        throwParserException("Invalid variable name");
    }
    PKB::getInstance().insertVariable(token);
    PKB::getInstance().insertAssignLHS(lineNumber_, token);
    token = getNextToken();
    if (token != "=") {
        throwParserException("Equals sign not found");
    }
    parseExpression();
}

void Parser::parseExpression() {
    std::unordered_set<std::string> operators = { "+", "-", "*", "/", "%" };
    std::unordered_set<int> constants;
    std::string expression = "";
    std::string token;
    int numberOfOpenParentheses = 0;
    bool emptyExpression = true;
    bool lastWasVariable = false;
    bool lastWasOperator = false;
    bool lastWasOpenParenthesis = false;
    bool lastWasCloseParenthesis = false;
    while (true) {
        token = getNextToken();
        if (token == ";") {
            if (numberOfOpenParentheses != 0 || lastWasOperator || lastWasOpenParenthesis || emptyExpression) {
                throwParserException("Invalid expression");
            }
            PKB::getInstance().insertConstant(lineNumber_, constants);
            std::string shuntedExpression = ShuntingYard::shuntingYard(expression);
            PKB::getInstance().insertAssignRHS(lineNumber_, shuntedExpression);
            break;
        }
        if (token == "EOF") {
            throwParserException("Semicolon not found");
        }
        if (token == "(") {
            if (lastWasCloseParenthesis || lastWasVariable) {
                throwParserException("Invalid expression");
            }
            numberOfOpenParentheses++;
            emptyExpression = false;
            lastWasOperator = false;
            lastWasVariable = false;
            lastWasOpenParenthesis = true;
            lastWasCloseParenthesis = false;
        }
        else if (token == ")") {
            if (numberOfOpenParentheses <= 0 || lastWasOperator || lastWasOpenParenthesis || emptyExpression) {
                throwParserException("Invalid expression");
            }
            emptyExpression = false;
            lastWasOperator = false;
            lastWasVariable = false;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = true;
            numberOfOpenParentheses--;
        }
        else if (operators.find(token) != operators.end()) {
            if (lastWasOperator || lastWasOpenParenthesis || emptyExpression) {
                throwParserException("Invalid expression");
            }
            emptyExpression = false;
            lastWasOperator = true;
            lastWasVariable = false;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = false;
        }
        else if (validateName(token) || validateInteger(token)) {
            if (lastWasVariable || lastWasCloseParenthesis) {
                throwParserException("Invalid expression");
            }
            emptyExpression = false;
            lastWasOperator = false;
            lastWasVariable = true;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = false;
        }
        else {
            throwParserException("Invalid expression");
        }
        expression += token;
        if (validateName(token)) {
            PKB::getInstance().insertVariable(token);
        }
        if (validateInteger(token)) {
            constants.insert(stoi(token));
        }
    }
}

void Parser::parseIfStatement() {
    std::string token;
    parentStack_.push(lineNumber_);
    PKB::getInstance().insertIf(lineNumber_, { });
    parseConditionalExpression(0);
    token = getNextToken();
    if (token != "then") {
        throwParserException("Keyword 'then' not found");
    }
    parseStatementList(false);
    token = getNextToken();
    if (token != "else") {
        throwParserException("Keyword 'else' not found");
    }
    parseStatementList(false);
    parentStack_.pop();
}

void Parser::parseWhileStatement() {
    parentStack_.push(lineNumber_);
    PKB::getInstance().insertWhile(lineNumber_, { });
    parseConditionalExpression(1);
    parseStatementList(false);
    parentStack_.pop();
}

int Parser::parseBracketedExpression(int statementType) {
    std::unordered_set<std::string> operators = { "+", "-", "*", "/", "%" };
    std::unordered_set<std::string> conditionalOperators = { "||", "&&", "!" };
    std::unordered_set<std::string> relationalOperators = { "<", ">", "<=", ">=", "==", "!=" };
    std::string token;
    std::string expression;
    bool lastWasVariable = false;
    bool lastWasOperator = false;
    bool lastWasOpenParenthesis = false;
    bool lastWasCloseParenthesis = false;
    int relationalOperator = 0;
    bool hasConditionalOperator = false;
    bool expectedConditionalExpression = false;
    bool expectedRelationalFactor = false;
    int previousBracketedExpressionType = 0;
    lastWasOpenParenthesis = true;

    while (true) {
        token = getNextToken();
        if (token == "EOF") {
            throwParserException("Missing closing parenthesis");
        }
        if (token == "(") {
            if (lastWasCloseParenthesis || lastWasVariable) {
                throwParserException("Invalid conditional expression");
            }
            previousBracketedExpressionType = parseBracketedExpression(statementType);
            if (expectedConditionalExpression) {
                if (previousBracketedExpressionType == 0) {
                    throwParserException("Invalid conditional expression");
                }
                previousBracketedExpressionType = 2;
                expectedConditionalExpression = false;
            }
            else if (expectedRelationalFactor) {
                if (previousBracketedExpressionType == 1 || previousBracketedExpressionType == 2) {
                    throwParserException("Invalid conditional expression");
                }
                expectedRelationalFactor = false;
            }
            lastWasOperator = false;
            lastWasVariable = false;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = true;
        }
        else if (token == ")") {
            if (lastWasOperator || lastWasOpenParenthesis) {
                throwParserException("Invalid conditional expression");
            }
            if (expectedConditionalExpression) {
                throwParserException("Invalid conditional expression");
            }
            if (relationalOperator > 1) {
                throwParserException("Invalid conditional expression");
            }
            if (hasConditionalOperator) {
                return 2; // Conditional Expression
            }
            else if (relationalOperator > 0) {
                return 1; // Relational Expression
            }
            else {
                return 0; // Expression
            }
        }
        else if (relationalOperators.find(token) != relationalOperators.end()) {
            if (lastWasOperator || lastWasOpenParenthesis) {
                throwParserException("Invalid conditional expression");
            }
            if (lastWasCloseParenthesis && (previousBracketedExpressionType == 1 || previousBracketedExpressionType == 2)) {
                throwParserException("Invalid conditional expression");
            }
            lastWasOperator = true;
            lastWasVariable = false;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = false;
            relationalOperator += 1;
            expectedRelationalFactor = true;
        }
        else if (conditionalOperators.find(token) != conditionalOperators.end()) {
            if ((!lastWasCloseParenthesis && token != "!") || (!lastWasOpenParenthesis && token == "!")) {
                throwParserException("Invalid conditional expression");
            }
            if (lastWasCloseParenthesis && (previousBracketedExpressionType == 0)) {
                throwParserException("Invalid conditional expression");
            }
            lastWasOperator = true;
            lastWasVariable = false;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = false;
            hasConditionalOperator = true;
            expectedConditionalExpression = true;
        }
        else if (operators.find(token) != operators.end()) {
            if (lastWasOperator || lastWasOpenParenthesis) {
                throwParserException("Invalid conditional expression");
            }
            if (lastWasCloseParenthesis && (previousBracketedExpressionType == 1 || previousBracketedExpressionType == 2)) {
                throwParserException("Invalid conditional expression");
            }
            lastWasOperator = true;
            lastWasVariable = false;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = false;
        }
        else if (validateName(token) || validateInteger(token)) {
            if (lastWasVariable || lastWasCloseParenthesis) {
                throwParserException("Invalid conditional expression");
            }
            lastWasOperator = false;
            lastWasVariable = true;
            lastWasOpenParenthesis = false;
            lastWasCloseParenthesis = false;
        }
        else {
            throwParserException("Invalid conditional expression");
        }
        if (validateName(token)) {
            PKB::getInstance().insertVariable(token);
            if (statementType == 0) { // if statement
                PKB::getInstance().insertIf(lineNumber_, { token });
            }
            else { // while statement
                PKB::getInstance().insertWhile(lineNumber_, { token });
            }
        }
        if (validateInteger(token)) {
            std::unordered_set<int> constantValue = { stoi(token) };
            PKB::getInstance().insertConstant(lineNumber_, constantValue);
        }
    }
}

void Parser::parseConditionalExpression(int statementType) {
    std::string token;
    int bracketedStatementType;
    token = getNextToken();
    if (token != "(") {
        throwParserException("Missing opening parenthesis");
    }
    bracketedStatementType = parseBracketedExpression(statementType);
    if (bracketedStatementType == 0) {
        throwParserException("Invalid conditional expression");
    }
}

bool Parser::validateName(std::string token) {
    if (isdigit(token[0])) {
        return false;
    }
    for (char i : token) {
        if (!isalnum(i)) {
            return false;
        }
    }
    return true;
}

bool Parser::validateInteger(std::string token) {
    if (token[0] == '0' && token.size() != 1) {
        return false;
    }
    for (char i : token) {
        if (!isdigit(i)) {
            return false;
        }
    }
    return true;
}

void Parser::throwParserException(std::string message) {
    std::string errorLineNumber = std::to_string(lineNumber_);
    lineNumber_ = 0;
    fileStream_.close();
    std::stack<int>().swap(parentStack_);
    throw Parser::ParserException(message + " at Line " + errorLineNumber);
}

void Parser::throwProcedureParserException(std::string message) {
    int erroneousProcedureIndex = currentProcedureIndex_;
    lineNumber_ = 0;
    fileStream_.close();
    std::stack<int>().swap(parentStack_);
    throw Parser::ParserException(message + " at Procedure " + PKB::getInstance().getProcedure(erroneousProcedureIndex));
}

void Parser::throwCallParserException(std::string procedureName) {
    std::unordered_set<int> callLines = PKB::getInstance().getKeysCall(procedureName);
    std::string lines = "";
    for (auto& line : callLines) {
        lines += std::to_string(line) + ", ";
    }
    lines = lines.substr(0, lines.length() - 2);
    lineNumber_ = 0;
    fileStream_.close();
    std::stack<int>().swap(parentStack_);
    throw Parser::ParserException("Call to non-existing procedure " + procedureName + " at Line: " + lines);
}

void Parser::extractCalls() {
    std::vector<std::string> procedureNames = PKB::getInstance().getAllValuesProcedure();
    std::vector<int> lineCalling = PKB::getInstance().getAllKeysCall();
    std::vector<std::string> proceduresCalled = PKB::getInstance().getAllValuesCall();
    std::vector<int>::const_iterator callingIt = lineCalling.begin();
    std::vector<std::string>::const_iterator calledIt = proceduresCalled.begin();
    for (; callingIt != lineCalling.end() && calledIt != proceduresCalled.end(); ++callingIt, ++calledIt) {
        if (std::find(procedureNames.begin(), procedureNames.end(), *calledIt) == procedureNames.end()) {
            throwCallParserException(*calledIt);
        }
        PKB::getInstance().insertCalls(PKB::getInstance().getKeyProcedureStatementList(*callingIt), { PKB::getInstance().getKeyProcedure(*calledIt) });
    }
}

void Parser::extractCallsStar() {
    std::vector<bool> visited(PKB::getInstance().getSizeProcedure(), false);
    std::vector<bool> recursionVisited(PKB::getInstance().getSizeProcedure(), false);
    std::vector<int> proceduresCalling = PKB::getInstance().getAllKeysCalls();
    for (auto& procedureCalling : proceduresCalling) {
        if (!visited[procedureCalling]) {
            recursiveExtractCallsStar(procedureCalling, visited, recursionVisited);
        }
    }
}

void Parser::recursiveExtractCallsStar(int procedureIndex, std::vector<bool>& visited, std::vector<bool>& recursionVisited) {
    if (recursionVisited[procedureIndex] == true) {
        throwParserException("Cyclic call");
    }
    recursionVisited[procedureIndex] = true;
    std::unordered_set<int> calledProcedures = PKB::getInstance().getCalls(procedureIndex);
    for (int calledProcedure : calledProcedures) {
        if (!visited[calledProcedure]) {
            recursiveExtractCallsStar(calledProcedure, visited, recursionVisited);
        }
        PKB::getInstance().insertCallsStar(procedureIndex, { calledProcedure });
        std::unordered_set<int> calledStarProcedures = PKB::getInstance().getCallsStar(calledProcedure);
        for (int calledStarProcedure : calledStarProcedures) {
            if (calledStarProcedure == procedureIndex) {
                throwParserException("Cyclic call");
            }
            PKB::getInstance().insertCallsStar(procedureIndex, { calledStarProcedure });
        }
    }
    visited[procedureIndex] = true;
    recursionVisited[procedureIndex] = false;
}
