//
// Created by kfir on 12/15/19.
//

#include "OpenServerCommand.h"
#include "Executor.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

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

    thread thread1(&OpenServerCommand::serverExecution,this, client_socket);
    thread1.detach();
    return 2;
}
int OpenServerCommand::serverExecution(int clientSocket) {
    //reading from client
    while(*executor->status){
        char buffer[2048] = {0};
        read( clientSocket , buffer, 2048);
        string numbArray[36];
        string numHelp = "";
        int index = 0;
        for (int k = 0; buffer[k] != '\n'; k++) {
            if (buffer[k] == ',') {
                numbArray[index] = numHelp;
                numHelp = "";
                index++;
                continue;
            }
            numHelp += buffer[k];
        }
        numbArray[index] = numHelp;
        // update the variables
        for (int j = 1; j <= 36; ++j) {
            if(executor->simToVarMap.find(executor->simMap[j]) != executor->varMap.end()){
                executor->simToVarMap[executor->simMap[j]]->value = stod(numbArray[j-1]);
            }
        }
    }
    return 0;
}
