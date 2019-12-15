//
// Created by kfir on 12/15/19.
//

#include "WhileCommand.h"

int WhileCommand::execute(int index) {
    //need to rewrite with stack!!
    int jump = 1;
    while(this->commands->at(index)[0] != '}'){
        index++;
        jump++;
    }
    return jump;
}
