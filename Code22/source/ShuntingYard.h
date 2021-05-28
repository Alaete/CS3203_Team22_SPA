#pragma once

#include <string>
#include <unordered_set>
#include <stack>

class ShuntingYard {
    public:
        static std::string shuntingYard(std::string expression) {
            std::unordered_set<std::string> operators = { "+", "-", "*", "/", "%" };
            std::stack<std::string> tokenStack;
            std::vector<std::string> input = tokenizeExpression(expression);
            std::string output = "";
            for (std::string& token : input) {
                if (validateName(token) || validateInteger(token)) {
                    output += token;
                    output += " ";
                }
                else if (operators.find(token) != operators.end()) {
                    while ((!tokenStack.empty()) && (operators.find(tokenStack.top()) != operators.end()) && (precedence(tokenStack.top()) >= precedence(token))) {
                        output += tokenStack.top();
                        output += " ";
                        tokenStack.pop();
                    }
                    tokenStack.push(token);
                }
                else if (token == "(") {
                    tokenStack.push(token);
                }
                else if (token == ")") {
                    while (tokenStack.top() != "(") {
                        output += tokenStack.top();
                        output += " ";
                        tokenStack.pop();
                    }
                    tokenStack.pop();
                }
            }
            while (!tokenStack.empty()) {
                output += tokenStack.top();
                output += " ";
                tokenStack.pop();
            }
            return output.substr(0, output.length() - 1);
        }

    private:
        static int precedence(std::string token) {
            std::vector<std::pair<std::string, int>> operatorPrecedence = { {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3}, {"%", 3} };
            for (const std::pair<std::string, int>& reference : operatorPrecedence)
            {
                if (reference.first == token) {
                    return reference.second;
                }
            }
            return 1;
        }

        static std::vector<std::string> tokenizeExpression(std::string expression) {
            int expressionLength = expression.length();
            std::string token;
            std::vector<std::string> tokens;
            for (int i = 0; i < expressionLength; ++i) {
                if (isspace(expression[i])) {
                    if (token.length() != 0) {
                        tokens.push_back(token);
                        token = "";
                    }
                }
                else if (ispunct(expression[i])) {
                    if (token.length() != 0) {
                        tokens.push_back(token);
                        token = "";
                    }
                    std::string stringToken(1, expression[i]);
                    tokens.push_back(stringToken);
                }
                else {
                    token += expression[i];
                    if (i == expressionLength - 1) {
                        tokens.push_back(token);
                    }
                }
            }
            return tokens;
        }

        static bool validateName(std::string token) {
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

        static bool validateInteger(std::string token) {
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
};
