//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_SLEEPCOMMAND_H
#define UNTITLED3_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command{
public:
    int execute(int index) override;

};


#endif //UNTITLED3_SLEEPCOMMAND_H
