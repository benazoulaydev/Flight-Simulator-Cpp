//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_OPENSERVERCOMMAND_H
#define UNTITLED3_OPENSERVERCOMMAND_H


#include "Command.h"

class OpenServerCommand  : public Command{
public:
    int execute(int index) override;

};


#endif //UNTITLED3_OPENSERVERCOMMAND_H
