//
// Created by kfir on 12/19/19.
//

#ifndef UNTITLED3_EXECUTOR_H
#define UNTITLED3_EXECUTOR_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Command.h"
#include "Var.h"
#include "expression/Interpreter.h"
#include <iterator>

using namespace std;

class Executor : public Command {
public:
    vector<string> *commands;
    unordered_map<string, Command*> commandsMap;
    unordered_map<string, Var*> varMap;
    Interpreter interpreter;
    unordered_map<int, string> simMap;
    unordered_map<string, Var*> simToVarMap;
    Executor(vector<string> *commandsVector){
        this->commands = commandsVector;
    }
    // this function is meaningless
    int execute(int index) override{return index;}
    void initiate();
    void executeScope(int start, int end);
    void refreshVariables();
    double interpretFromString(string expression);
    ~Executor(){
        for(auto varPair : this->varMap){
            delete(varPair.second);
        }
        for(auto varPair : this->commandsMap){
            delete(varPair.second);
        }
    }

    void createSimMap();
};


#endif //UNTITLED3_EXECUTOR_H
