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
#include <strings.h>

using namespace std;

int OpenServerCommand::execute(int index) {
    //create the socket
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFD == -1){
        cerr<< "Could not create a socket" << endl;
        throw "Error";
    }
    //get the address and the port for connection
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
        int i = 0;
        int z = 0;
        char buffer[2048] = {0};
        int n = read( clientSocket , buffer, 2048);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        while (n >= 0) {
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            string numbArray[36];
            string numHelp = "";


            int index = 0;
            int flag = 0;

            while (buffer[i] != '\0') {
                for (int k = 0; buffer[k] != '\n'; k++) {
                    if (buffer[k] == ',') {
                        //print for testing
                        //cout<<numHelp<<" ";
                        numbArray[index] = numHelp;
                        numHelp = "";
                        index++;
                        continue;
                    }
                    numHelp += buffer[k];
                    z = k;
                }


                numbArray[index] = numHelp;
                //cout<<numHelp<<" ";
                numHelp = "";
                if (index != 35){

                    string numbArrayHlp[36];
                    int p = 0;
                    for (int k = 0; k<36; k++) {
                        if (index<35) {
                            numbArrayHlp[k] = "EMPTY";
                            index++;
                        } else {
                            numbArrayHlp[k] = numbArray[p];
                            p++;
                        }

                    }
                    *numbArray = *numbArrayHlp;
                }
                // update the variables
                for (int j = 1; j <= 36; ++j) {
                    if(executor->simToVarMap.find(executor->simMap[j]) != executor->varMap.end() &&
                       numbArray[j-1] != "EMPTY"){
                        executor->simToVarMap[executor->simMap[j]]->value = stod(numbArray[j-1]);
                    }
                }
                //cout<<endl;
                index = 0;
                flag = 1;
                i += z+1;
            }
            if (flag == 0){
                string numbArrayHlp[36];
                numbArrayHlp[0] = numHelp + numbArray[0];
                for (int k = 1; k<36; k++) {
                    if (index>0) {
                        numbArrayHlp[k] = numbArray[k];
                        index--;
                    } else {
                        numbArrayHlp[k] = "EMPTY";
                    }

                }
                *numbArray = *numbArrayHlp;
                for (int j = 1; j <= 36; ++j) {
                    if(executor->simToVarMap.find(executor->simMap[j]) != executor->varMap.end() &&
                       numbArray[j-1] != "EMPTY"){
                        executor->simToVarMap[executor->simMap[j]]->value = stod(numbArray[j-1]);
                    }
                }
                // i += z+1;
            }
            //actualizeData;
            i = 0;
            n = read(clientSocket, buffer, 2048);
        }
    }
    close(clientSocket);
    return 0;
}