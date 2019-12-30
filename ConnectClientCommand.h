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
    //create the client socket keeps it for further messages to send
    int client_socket;
public:
    //access the executor object
    explicit ConnectClientCommand(Executor* exec) {
        this->executor = exec;
    }

    int execute(int index) override;
    void sendToServer(Var* aVar);

    ~ConnectClientCommand(){
        //close the socket
        close(client_socket);
    };
};


#endif //UNTITLED3_CONNECTCLIENTCOMMAND_H
