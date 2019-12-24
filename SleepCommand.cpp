//
// Created by kfir on 12/15/19.
//

#include "SleepCommand.h"
#include <iostream>
#include "Executor.h"
int SleepCommand::execute(int index) {
    cout<<"start sleeping"<<endl;
    string time = executor->commands->at(index+1);
    this_thread::sleep_for(chrono::milliseconds(stoi(time)));
    cout<<"stop sleeping"<<endl;

    return 2;

}
