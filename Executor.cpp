//
// Created by kfir on 12/19/19.
//

#include "Executor.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "VarCommand.h"
#include "ConnectClientCommand.h"
#include "OpenServerCommand.h"
#include "expression/Interpreter.cpp"

void Executor::initiate() {
    // initializing commands objects.
    PrintCommand* p = new PrintCommand(this);
    commandsMap["Print"] = (Command*)p;
    VarCommand* v = new VarCommand(this);
    commandsMap["var"] = (Command*)v;
    OpenServerCommand* os = new OpenServerCommand(this);
    commandsMap["openDataServer"] = (Command*)os;
    ConnectClientCommand* cc = new ConnectClientCommand();
    commandsMap["connectControlClient"] = (Command*)cc;
    SleepCommand* s = new SleepCommand();
    commandsMap["Sleep"] = (Command*)s;
    IfCommand* ic = new IfCommand(this);
    commandsMap["if"] = (Command*)ic;
    WhileCommand* w = new WhileCommand(this);
    commandsMap["while"] = (Command*)w;

}

void Executor::executeScope(int start, int end) {
    // execute the commands.
    int i = start;
    while (i < end){
        if( commands->at(i+1)=="x")
            cout<<"hi"<<i<<endl;
        if (commandsMap.find(commands->at(i)) != commandsMap.end()){
            Command* c = commandsMap.at(commands->at(i));
            i += c->execute(i);
        } else {
            varMap[commands->at(i)]->value = interpretFromString(commands->at(i+2));
            i += 3;
        }
    }
}

double Executor::interpretFromString(string expression) {
    refreshVariables();
    return this->interpreter.interpret(expression)->calculate();
}

void Executor::refreshVariables() {
    for(auto varPair : this->varMap){
        this->interpreter.setVariables(varPair.second->toStr());
    }
}
