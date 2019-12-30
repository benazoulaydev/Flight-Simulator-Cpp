//
// Created by kfir on 12/23/19.
//

#include "FunctionCommand.h"
/**
 * Execute the function command
 * @param index
 * @return
 */
int FunctionCommand::execute(int index) {
    executor->varMap.at(var)->value = stod(executor->commands->at(index+1));
    executor->executeScope(startIndex+4, startIndex + executor->jumpScope(startIndex)-1);
    return 2;
}
