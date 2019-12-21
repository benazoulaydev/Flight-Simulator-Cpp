//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_PRINTCOMMAND_H
#define UNTITLED3_PRINTCOMMAND_H

#include "Command.h"
#include "Var.h"
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
class Executor;

class PrintCommand:public Command{
private:
    Executor* executor;public:
public:
    explicit PrintCommand(Executor* executor) {
        this->executor = executor;
    }
    int execute(int index) override;
};


#endif //UNTITLED3_PRINTCOMMAND_H
