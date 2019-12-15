//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_CONNECTCLIENTCOMMAND_H
#define UNTITLED3_CONNECTCLIENTCOMMAND_H


#include "Command.h"

class ConnectClientCommand  : public Command{
public:
    int execute(int index) override;
};


#endif //UNTITLED3_CONNECTCLIENTCOMMAND_H
