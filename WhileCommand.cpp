//
// Created by kfir on 12/15/19.
//
#include <stack>
#include <iostream>

#include "WhileCommand.h"
/**
 * While execute command
 * @param index
 * @return
 */
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
    //get the left and right expression of the while

    double leftExp = executor->interpretFromString(executor->commands->at(index+1)),
            rightExp = executor->interpretFromString(executor->commands->at(index+3));
    //get the operator between the two expressions
    string compositor = executor->commands->at(index+2);
    //make a new scope (of the while) and execute it with the given leftepr rightexpr and compositor the opr
    while ((compositor == "==" && leftExp == rightExp) || (compositor == "!=" && leftExp != rightExp) ||
           (compositor == "<=" && leftExp <= rightExp) || (compositor == ">=" && leftExp >= rightExp) ||
           (compositor == "<" && leftExp < rightExp) || (compositor == ">" && leftExp > rightExp)){
        executor->executeScope(index+5, index+jump-1);
        leftExp = executor->interpretFromString(executor->commands->at(index+1));
        rightExp = executor->interpretFromString(executor->commands->at(index+3));
    }
    return jump;
}