//
// Created by kfir on 12/15/19.
//

#include <iostream>
#include "PrintCommand.h"
#include "Executor.h"
/**
 * execute the print command
 * @param index
 * @return 2 the index to jump
 */
int PrintCommand::execute(int index) {
    string currentCmd = executor->commands->at(index+1);
    if (currentCmd[0] == '"'){
        cout<<currentCmd<<endl;
    } else {
        cout << executor->interpretFromString(currentCmd) << endl;
    }
    return 2;
}
