//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_SLEEPCOMMAND_H
#define UNTITLED3_SLEEPCOMMAND_H

#include <thread>
#include <chrono>
#include <iostream>
#include "Command.h"

class Executor;


class SleepCommand : public Command{
private:
    Executor* executor;
public:
    explicit SleepCommand(Executor* executor) {
        this->executor = executor;
    }
    int execute(int index) override;

};


#endif //UNTITLED3_SLEEPCOMMAND_H
