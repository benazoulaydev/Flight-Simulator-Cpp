//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_CONNECTCLIENTCOMMAND_H
#define UNTITLED3_CONNECTCLIENTCOMMAND_H


#include "Command.h"
#include "Var.h"

class Executor;

class ConnectClientCommand  : public Command{
private:
    Executor* executor;
    int client_socket;
public:
    explicit ConnectClientCommand(Executor* executor) {
        this->executor = executor;
    }
    int execute(int index) override;
    void sendToServer(Var* aVar);

};


#endif //UNTITLED3_CONNECTCLIENTCOMMAND_H
