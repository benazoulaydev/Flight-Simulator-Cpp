//
// Created by kfir on 12/15/19.
//

#include <iostream>
#include "VarCommand.h"
using namespace std;

int VarCommand::execute(int index) {
    if(commands->at(index+3) == "sim" && index+4< commands->size() && commands->at(index+4)[0] == '/'){
        this->vars->insert({commands->at(index+1), new Var(commands->at(index+1), 0, commands->at(index+4))});
        return 5;
    } else {
        return 4;
    }
}
