//
// Created by kfir on 12/15/19.
//

#include "IfCommand.h"

int IfCommand::execute(int index) {
    //need to rewrite with stack!!
    int jump = 2;
    while(this->commands->at(index)[0] != '}'){
        index++;
        jump++;
    }
    return jump;
}
