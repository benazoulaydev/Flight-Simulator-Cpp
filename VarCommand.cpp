//
// Created by kfir on 12/15/19.
//

#include <iostream>
#include "VarCommand.h"
using namespace std;

int VarCommand::execute(int index) {
    if(commands->at(index+3) == "sim" && index+4< commands->size() && commands->at(index+4)[0] == '/'){
        // need to finish!!!
        if (commands->at(index+2) == "->"){
            this->vars->insert({commands->at(index+1), new Var(commands->at(index+1), 0, commands->at(index+4))});
        } else {

        }
        return 5;
    } else { // this is var expression.
        this->vars->insert({commands->at(index+1), new Var(commands->at(index+1),
                interpretFromString(commands->at(index+3)), commands->at(index+4))});
        return 4;
    }
}

double VarCommand::interpretFromString(string expression) {
    for(auto varPair : *this->vars){
        this->interpreter->setVariables(varPair.second->toStr());
    }

    return this->interpreter->interpret(expression)->calculate();
}
