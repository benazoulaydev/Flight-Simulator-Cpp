//
// Created by kfir on 12/23/19.
//

#include "FunctionCommand.h"

int FunctionCommand::execute(int index) {
    executor->varMap.at(var)->value = stod(executor->commands->at(index+1));
    executor->executeScope(startIndex, startIndex + executor->jumpScope(startIndex));
    return 2;
}
