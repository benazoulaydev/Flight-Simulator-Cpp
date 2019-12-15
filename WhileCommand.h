//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_WHILECOMMAND_H
#define UNTITLED3_WHILECOMMAND_H


#include "Command.h"
#include "Var.h"
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class WhileCommand : public Command{
private:
    vector<string> *commands;
    unordered_map<string, Var*> *vars;
public:
    explicit WhileCommand(vector<string> *commands, unordered_map<string, Var*> *vars){
        this->commands = commands;
        this->vars = vars;
    }
    int execute(int index) override;
};


#endif //UNTITLED3_WHILECOMMAND_H
