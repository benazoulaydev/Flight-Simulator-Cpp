//
// Created by kfir on 12/19/19.
//

#ifndef UNTITLED3_EXECUTOR_H
#define UNTITLED3_EXECUTOR_H

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "lexer.h"
#include "Command.h"
#include "PrintCommand.h"
#include "Var.h"
#include "VarCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "ConnectClientCommand.h"
#include "OpenServerCommand.h"
#include "expression/Interpreter.h"

using namespace std;

class executor {
protected:
    vector<string> *commands;
    unordered_map<string, Command*> commandsMap;
    unordered_map<string, Var*> varMap;
    Interpreter inp;
public:
    executor(vector<string> *commands){
        this->commands = commands;
        initiate();
    }
    void initiate();
    void executeScope();
};


#endif //UNTITLED3_EXECUTOR_H
