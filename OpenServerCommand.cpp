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
/**
 * execute the openserver command
 * @param index
 * @return how much to jump here 2
 */
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
    //close the socketFD
    close(socketFD);
    //create new thread for running open server command in the background
    thread thread1(&OpenServerCommand::serverExecution,this, client_socket);
    thread1.detach();
    //return how much to jump
    return 2;
}
/**
 * Server execution to accepts 36 values and update them
 * @param clientSocket
 * @return 0
 */
int OpenServerCommand::serverExecution(int clientSocket) {
    //while the status == true
    while(*executor->status){
        int i = 0;
        int z = 0;
        char buffer[2048] = {0};
        int n = read( clientSocket , buffer, 2048);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        //while we can read from the socket
        while (n >= 0) {
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            //create a string array of the 36 values
            string numbArray[36];
            //numhelp is the leftside of a number in the first buffer if a value is  between two buffers
            string numHelp = "";
            //index of "," separator to check if there are 35
            int index = 0;
            //flag to see if the buffer is empty we read less than 36 value
            // and the rest is in the other buffer
            int flag = 0;
            //while buffer "not empty"
            while (buffer[i] != '\0') {
                //get the 36 values
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
                //the last value
                numbArray[index] = numHelp;

                //cout<<numHelp<<" ";
                //if the while did not stop(buffer not empty) and if
                //index != 35 it means only the last 36 values are in the numarray
                //so update only them
                numHelp = "";
                if (index != 35){

                    string numbArrayHlp[36];
                    int p = 0;
                    for (int k = 0; k<36; k++) {
                        if (index<35) {
                            //the values were no in the buffer
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
            //if the while stop it means the buffer is empty
            //if the flag = 0 it means we didnot update the first values in the 36 values
            // so we update them
            if (flag == 0){
                string numbArrayHlp[36];
                numbArrayHlp[0] = numHelp + numbArray[0];
                for (int k = 1; k<36; k++) {
                    if (index>0) {
                        numbArrayHlp[k] = numbArray[k];
                        index--;
                    } else {
                        //the last is empty
                        numbArrayHlp[k] = "EMPTY";
                    }

                }
                *numbArray = *numbArrayHlp;
                //update the values
                for (int j = 1; j <= 36; ++j) {
                    if(executor->simToVarMap.find(executor->simMap[j]) != executor->varMap.end() &&
                       numbArray[j-1] != "EMPTY"){
                        executor->simToVarMap[executor->simMap[j]]->value = stod(numbArray[j-1]);
                    }
                }
            }
            //actualizeData;
            i = 0;
            n = read(clientSocket, buffer, 2048);
        }
    }
    //close the socket
    close(clientSocket);
    return 0;
}