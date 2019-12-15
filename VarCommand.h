//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_VARCOMMAND_H
#define UNTITLED3_VARCOMMAND_H


#include <string>
#include "Command.h"
#include "Var.h"
#include <vector>
#include <unordered_map>

using namespace std;

class VarCommand : public Command{
private:
    vector<string> *commands;
    unordered_map<string, Var*> *vars;
public:
    explicit VarCommand(vector<string> *commands, unordered_map<string, Var*> *vars){
        this->commands = commands;
        this->vars = vars;
    }
    int execute(int index) override;
};


#endif //UNTITLED3_VARCOMMAND_H
