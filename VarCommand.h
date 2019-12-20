//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_VARCOMMAND_H
#define UNTITLED3_VARCOMMAND_H


#include <string>
#include "Command.h"
#include "Var.h"
#include "expression/Interpreter.h"
//#include "Executor.h"
#include <vector>
#include <unordered_map>
using namespace std;
class Executor;
class VarCommand : public Command{
private:
    Executor* executor;
public:
    VarCommand(Executor* executor);
    int execute(int index) override;
//    double interpretFromString(string expression);
};


#endif //UNTITLED3_VARCOMMAND_H
