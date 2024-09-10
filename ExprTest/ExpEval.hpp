#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <unordered_map>
#include <variant>
#include <cmath>
#include <set>
#include <typeinfo>

class ExpressionEvaluator {
public:
    using Value = std::variant<int, float, double, std::string>;


    ExpressionEvaluator() {
        // Register built-in functions
        functions["sqrt"] = [](const Value& v) {
            return std::visit([](auto&& arg) -> Value {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_arithmetic_v<T>) {
                    return static_cast<Value>(std::sqrt(arg));
                }
                else {
                    throw std::runtime_error("Invalid type for sqrt");
                }
                }, v);
            };
    }

    void setVariable(const std::string& name, const Value& value) {
        variables[name] = value;
    }

    Value evaluate(const std::string& expression) {
        this->_iseval = true;
        std::istringstream iss(expression);
        return parseExpression(iss);
    }

    std::set<std::string> extractVariables(const std::string& expression) {
        this->_iseval = false;
        std::istringstream iss(expression);
        std::set<std::string> variableSet;
        parseExpression(iss, &variableSet);
        return variableSet;
    }

private:
    std::unordered_map<std::string, Value> variables;
    std::unordered_map<std::string, std::function<Value(const Value&)>> functions;
    bool _iseval = false;

    Value parseExpression(std::istringstream& iss, std::set<std::string>* variableSet = nullptr) {
        Value result = parseTerm(iss, variableSet);
        char op;
        while (iss >> op) {
            if (op == '+' || op == '-') {
                Value rhs = parseTerm(iss, variableSet);
                result = applyOperator(result, rhs, op);
            }
            else {
                iss.putback(op);
                break;
            }
        }
        return result;
    }

    Value parseTerm(std::istringstream& iss, std::set<std::string>* variableSet = nullptr) {
        Value result = parseFactor(iss, variableSet);
        char op;
        while (iss >> op) {
            if (op == '*' || op == '/') {
                Value rhs = parseFactor(iss, variableSet);
                result = applyOperator(result, rhs, op);
            }
            else {
                iss.putback(op);
                break;
            }
        }
        return result;
    }

    Value parseFactor(std::istringstream& iss, std::set<std::string>* variableSet = nullptr) {
        char ch;
        if (iss >> ch) {
            if (std::isdigit(ch) || ch == '.') {
                iss.putback(ch);
                float number;
                iss >> number;
                return static_cast<Value>(number);
            }
            else if (std::isalpha(ch) || ch=='$') {
                std::string token;
                iss.putback(ch);
                iss >> token;
                if (variableSet && functions.find(token) == functions.end()) {
                    variableSet->insert(token);  // Insert variable if it's not a function
                }
                return handleFunctionOrVariable(token, variableSet);
            }
            else if (ch == '(') {
                Value result = parseExpression(iss, variableSet);
                iss >> ch; // Should be ')'
                return result;
            }
        }
        throw std::runtime_error("Invalid expression");
    }

    Value handleFunctionOrVariable(const std::string& token, std::set<std::string>* variableSet = nullptr) {
        if (functions.find(token) != functions.end()) {
            char ch;
            std::istringstream iss;
            std::cin >> ch; // Expecting '('
            if (ch == '(') {
                Value arg = parseExpression(iss, variableSet);
                std::cin >> ch; // Expecting ')'
                return functions[token](arg);
            }
        }
        else {
            if (this->_iseval) {
                if (variables.find(token) != variables.end()) {
                    return variables[token];
                }
            }
            else {
                return 0;
            }
        }
        throw std::runtime_error("Unknown function or variable: " + token);
    }

    Value applyOperator(const Value& lhs, const Value& rhs, char op) {
        return std::visit([op](auto&& arg1, auto&& arg2) -> Value {
            using T1 = std::decay_t<decltype(arg1)>;
            using T2 = std::decay_t<decltype(arg2)>;

            // Jika salah satu operand adalah string, lakukan konversi operand lain ke string
            if constexpr (std::is_same_v<T1, std::string> || std::is_same_v<T2, std::string>) {
                std::string lhsStr;
                std::string rhsStr;
                if constexpr (std::is_same_v<T1, std::string>) lhsStr = arg1;
                else lhsStr = std::to_string(arg1);
                if constexpr (std::is_same_v<T2, std::string>) rhsStr = arg2;
                else rhsStr = std::to_string(arg2);
                if (op == '+') {
                    return static_cast<Value>(lhsStr + rhsStr);  // Concatenation for strings
                }
                else {
                    throw std::runtime_error("Invalid operator for string operations");
                }
            }
            // Operasi untuk tipe numerik (int, float)
            else if constexpr (std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>) {
                switch (op) {
                case '+': return static_cast<Value>(arg1 + arg2);
                case '-': return static_cast<Value>(arg1 - arg2);
                case '*': return static_cast<Value>(arg1 * arg2);
                case '/':
                    if (arg2 == 0) throw std::runtime_error("Division by zero");
                    return static_cast<Value>(arg1 / arg2);
                default: throw std::runtime_error("Unknown operator");
                }
            }
            // Jika tipe tidak kompatibel
            else {
                throw std::runtime_error("Invalid types for operation");
            }
            }, lhs, rhs);
    }
};

