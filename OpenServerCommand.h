//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_OPENSERVERCOMMAND_H
#define UNTITLED3_OPENSERVERCOMMAND_H


#include "Command.h"
class Executor;

class OpenServerCommand  : public Command{
private:
    Executor* executor;public:
public:
    explicit OpenServerCommand(Executor* executor) {
        this->executor = executor;
    }
    int execute(int index) override;

};


#endif //UNTITLED3_OPENSERVERCOMMAND_H
