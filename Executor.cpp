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
#include "FunctionCommand.h"

void Executor::initiate() {
    // initializing commands objects.
    PrintCommand* p = new PrintCommand(this);
    commandsMap["Print"] = (Command*)p;
    VarCommand* v = new VarCommand(this);
    commandsMap["var"] = (Command*)v;
    OpenServerCommand* os = new OpenServerCommand();
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
        if (commands->at(i+1) == "var"){
            //create functionCommand and jump as needed
            commandsMap.insert({commands->at(i), new FunctionCommand(this, i)});
            i += jumpScope(i);
        }else if (commandsMap.find(commands->at(i)) != commandsMap.end()){
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

int Executor::jumpScope(int index) {
    stack<char> s;
    s.emplace('{');
    int jump = 4;
    int i = index + 4;
    while(!s.empty()){
        if (commands->at(i)[0] == '}'){
            s.pop();
        } else if (commands->at(i)[0] == '{'){
            s.emplace('{');
        }
        i++;
        jump++;
    }
    return jump;
}
