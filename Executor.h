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

using namespace std;

class Executor : public Command {
public:
    vector<string> *commands;
    unordered_map<string, Command*> commandsMap;
    unordered_map<string, Var*> varMap;
    Interpreter interpreter;
    Executor(vector<string> *commands){
        this->commands = commands;
    }
    int execute(int index) override{return 0;}
    void initiate();
    void executeScope(int start, int end);
    void refreshVariables();
    double interpretFromString(string expression);
    ~Executor(){
        //TODO delete commandsMap
    }
};


#endif //UNTITLED3_EXECUTOR_H
