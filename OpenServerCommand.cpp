//
// Created by kfir on 12/15/19.
//

#include "OpenServerCommand.h"
#include "Executor.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int OpenServerCommand::execute(int index) {
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFD == -1){
        cerr<< "Could not create a socket" << endl;
        throw "Error";
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(stoi(executor->commands->at(index+1)));
    if(bind(socketFD, (struct sockaddr*)&address, sizeof(address)) == -1){
        cerr<<"Could not bind socket to an IP" << endl;
        throw "Error";
    }
    if(listen(socketFD, 5) == -1){
        cerr<<"Error during listenning command" << endl;
        throw "Error";
    }
    int client_socket = accept(socketFD, (struct sockaddr*)&address, (socklen_t*)&address);
    if(client_socket == -1){
        cerr<<"Error accepting client" << endl;
        throw "Error";
    }
    close(socketFD);

    //reading from client
    unsigned long int i = 1;
    while(i<10){
        char buffer[1024] = {0};
        int valread = read( client_socket , buffer, 1024);
        cout<<buffer<<endl;
        i++;
    }
    return 2;
}
