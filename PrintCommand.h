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

class PrintCommand:public Command{
private:
    vector<string> *commands;
    unordered_map<string, Var*> *vars;
public:
    explicit PrintCommand(vector<string> *commands, unordered_map<string, Var*> *vars){
        this->commands = commands;
        this->vars = vars;
    }
    int execute(int index) override;
};


#endif //UNTITLED3_PRINTCOMMAND_H
