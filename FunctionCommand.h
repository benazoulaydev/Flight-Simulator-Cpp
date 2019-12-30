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
    FunctionCommand(Executor* pExecutor, int start) {
        this->executor = pExecutor;
        this->startIndex = start;
        this->var = pExecutor->commands->at(start + 2);
        pExecutor->varMap.insert({var, new Var(var, 0, "none")});
    }
    int execute(int index) override;
};


#endif //UNTITLED3_FUNCTIONCOMMAND_H
