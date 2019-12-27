//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_WHILECOMMAND_H
#define UNTITLED3_WHILECOMMAND_H


#include "Command.h"
#include "Var.h"
#include "expression/Interpreter.h"
#include "Executor.h"
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class WhileCommand : public Command{
private:
    Executor* executor;
public:
    WhileCommand(Executor* exec) {
        this->executor = exec;
    }
    int execute(int index) override;
};


#endif //UNTITLED3_WHILECOMMAND_H
