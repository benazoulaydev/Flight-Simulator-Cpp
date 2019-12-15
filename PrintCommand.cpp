//
// Created by kfir on 12/15/19.
//

#include <iostream>
#include "PrintCommand.h"

int PrintCommand::execute(int index) {
    string currentCmd = this->commands->at(index+1);
    if (currentCmd[0] == '"'){
        cout<<currentCmd<<endl;
    } else {
        if (this->vars->find(currentCmd) != this->vars->end()) {
            cout << this->vars->at(currentCmd)->value << endl;
        }
    }
    return 2;
}
