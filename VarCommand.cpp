//
// Created by kfir on 12/15/19.
//

#include <iostream>
#include "VarCommand.h"
#include "Executor.h"

using namespace std;
/**
 * execute the varcommand
 * @param index
 * @return the number to jump
 */
int VarCommand::execute(int index) {
    if(executor->commands->at(index+3) == "sim" && ((unsigned)index+4) < executor->commands->size() &&
        executor->commands->at(index+4)[0] == '/'){
        if (executor->commands->at(index+2) == "->"){
            executor->varMap.insert({executor->commands->at(index+1), new Var(executor->commands->at(index+1), 0, executor->commands->at(index+4))});
            Var* cur = executor->varMap[executor->commands->at(index+1)];
            cur->arrow = "->";
        } else { // case <-
            executor->varMap.insert({executor->commands->at(index+1), new Var(executor->commands->at(index+1), 0, executor->commands->at(index+4))});
            Var* cur = executor->varMap[executor->commands->at(index+1)];
            cur->arrow = "<-";
            executor->simToVarMap[cur->sim] = cur;
        }
        return 5;
    } else { // this is var expression.
        executor->varMap.insert({executor->commands->at(index+1), new Var(executor->commands->at(index+1),
                executor->interpretFromString(executor->commands->at(index+3)), "none")});
        return 4;
    }
}
/**
 * set the executor
 * @param exec
 */
VarCommand::VarCommand(Executor *exec) {
    this->executor = exec;
}

