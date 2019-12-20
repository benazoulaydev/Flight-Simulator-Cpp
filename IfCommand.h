//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_IFCOMMAND_H
#define UNTITLED3_IFCOMMAND_H


#include "Command.h"
#include "Var.h"
#include "Executor.h"
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class IfCommand  : public Command{
private:
    Executor* executor;
public:
    explicit IfCommand(Executor* executor) {
        this->executor = executor;
    }

    int execute(int index) override;

};


#endif //UNTITLED3_IFCOMMAND_H
