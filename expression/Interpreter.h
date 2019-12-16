//
// Created by kfir on 11/7/19.
//

#ifndef EX1_INTERPRETER_H
#define EX1_INTERPRETER_H


#include <string>
#include <map>
#include "Expression.h"
#include "UMinus.h"

class Interpreter {
private:
    map<string, string> variables;
public:
    Expression* interpret(const string& exp);
    void setVariables(const string& exp);

    string replaceVariables(string exp);

    string replaceMinus(string exp);
};


#endif //EX1_INTERPRETER_H
