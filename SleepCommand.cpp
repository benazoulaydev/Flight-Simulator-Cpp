//
// Created by kfir on 12/15/19.
//

#include "SleepCommand.h"
#include <iostream>
#include "Executor.h"
/**
 * execute the sleep command
 * @param index
 * @return 2 the index to jump
 */
int SleepCommand::execute(int index) {
    string time = executor->commands->at(index+1);
    this_thread::sleep_for(chrono::milliseconds(stoi(time)));
    return 2;
}
