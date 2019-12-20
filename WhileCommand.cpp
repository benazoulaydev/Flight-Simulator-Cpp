//
// Created by kfir on 12/15/19.
//
#include <stack>
#include <iostream>

#include "WhileCommand.h"
int WhileCommand::execute(int index) {
    // settle the jumping of the scope
    stack<char> s;
    s.emplace('{');
    int jump = 5;
    int i = index + 5;
    while(!s.empty()){
        if (executor->commands->at(i)[0] == '}'){
            s.pop();
        } else if (executor->commands->at(i)[0] == '{'){
            s.emplace('{');
        }
        i++;
        jump++;
    }

    double leftExp = executor->interpretFromString(executor->commands->at(index+1)),
            rightExp = executor->interpretFromString(executor->commands->at(index+3));
    string compositor = executor->commands->at(index+2);
    while ((compositor == "==" && leftExp == rightExp) || (compositor == "!=" && leftExp != rightExp) ||
           (compositor == "<=" && leftExp <= rightExp) || (compositor == ">=" && leftExp >= rightExp) ||
           (compositor == "<" && leftExp < rightExp) || (compositor == ">" && leftExp > rightExp)){
        executor->executeScope(index+5, index+jump-1);
        leftExp = executor->interpretFromString(executor->commands->at(index+1));
        rightExp = executor->interpretFromString(executor->commands->at(index+3));
    }
    return jump;
}