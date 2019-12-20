//
// Created by kfir on 12/15/19.
//

#include <iostream>
#include "VarCommand.h"
#include "Executor.h"

using namespace std;

int VarCommand::execute(int index) {
    if(executor->commands->at(index+3) == "sim" && index+4< executor->commands->size() &&
        executor->commands->at(index+4)[0] == '/'){
        // TODO change between -> to <-
        if (executor->commands->at(index+2) == "->"){
            executor->varMap.insert({executor->commands->at(index+1), new Var(executor->commands->at(index+1), 0, executor->commands->at(index+4))});
        } else {
            executor->varMap.insert({executor->commands->at(index+1), new Var(executor->commands->at(index+1), 0, executor->commands->at(index+4))});
        }
        return 5;
    } else { // this is var expression.
        executor->varMap.insert({executor->commands->at(index+1), new Var(executor->commands->at(index+1),
                executor->interpretFromString(executor->commands->at(index+3)), "none")});
        return 4;
    }
}

//double VarCommand::interpretFromString(string expression) {
//    for(auto varPair : executor->varMap){
//        this->interpreter->setVariables(varPair.second->toStr());
//    }
//    return this->interpreter->interpret(expression)->calculate();
//}

VarCommand::VarCommand(Executor *executor) {
    this->executor = executor;
}

