//
// Created by kfir on 12/23/19.
//

#ifndef UNTITLED3_FUNCTIONCOMMAND_H
#define UNTITLED3_FUNCTIONCOMMAND_H


#include "Command.h"
#include "Var.h"
#include "expression/Interpreter.h"
#include "Executor.h"
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class FunctionCommand : public Command{
private:
    Executor* executor;
    int startIndex;
    string var;
public:
    FunctionCommand(Executor* executor, int startIndex) {
        this->executor = executor;
        this->startIndex = startIndex;
        this->var = executor->commands->at(startIndex+2);
        executor->varMap.insert({var,new Var(var, 0, "none")});
    }
    int execute(int index) override;
};


#endif //UNTITLED3_FUNCTIONCOMMAND_H
