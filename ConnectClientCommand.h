//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_CONNECTCLIENTCOMMAND_H
#define UNTITLED3_CONNECTCLIENTCOMMAND_H


#include <unistd.h>
#include "Command.h"
#include "Var.h"

class Executor;

class ConnectClientCommand  : public Command{
private:
    Executor* executor;
    int client_socket;
public:
    explicit ConnectClientCommand(Executor* exec) {
        this->executor = exec;
    }
    int execute(int index) override;
    void sendToServer(Var* aVar);
    ~ConnectClientCommand(){
        close(client_socket);
    };
};


#endif //UNTITLED3_CONNECTCLIENTCOMMAND_H
