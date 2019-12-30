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
    //vector of all commands
    vector<string> *commands;
    //map the command string and the class object of the command
    unordered_map<string, Command*> commandsMap;
    //map for variables objects
    unordered_map<string, Var*> varMap;
    //keep the interpreter for expression
    Interpreter interpreter;
    //order all sim url by order diplayed in the xml file
    unordered_map<int, string> simMap;
    //order the sim to the current variable object pointing to it
    unordered_map<string, Var*> simToVarMap;
    //status close the server socket if the program need to stop
    bool* status;
    //constructor
    Executor(vector<string> *commandsVector, bool* statusPtr){
        this->commands = commandsVector;
        this->status = statusPtr;
    }

    int execute(int index) override{return index;}
    void initiate();
    void executeScope(int start, int end);
    void refreshVariables();
    double interpretFromString(string expression);
    int jumpScope(int index);
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
