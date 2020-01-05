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
        string bufferString = "";
        string bufferStringLast = "";
        string allBuffer = "";




        char buffer[4096] = {0};
        bzero(buffer, 4096);
        int n = read( clientSocket , buffer, 4096);
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
            string numHelpHlp = "";




            int indexChar = 0;
            int endLine;
            int endbuffer;
            while (1) {
                endLine = bufferString.find ('\n');
                endbuffer = bufferString.find ('\0');
                bufferString += bufferStringLast;
                if (endLine != -1) {
                    allBuffer = bufferString;
                    bufferStringLast = bufferString.substr(endLine + 1,endbuffer - 1);
                    bufferString = bufferString.substr(0,endLine);
                    break;

                }


                while (buffer[indexChar] != '\0') {
                    bufferString += buffer[indexChar];
                    indexChar++;

                }
                indexChar = 0;
                bzero(buffer, 4096);
                n = read(clientSocket, buffer, 4096);

            }
            std::string delimiter = ",";

            //bufferString = "1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.00,11.0,12.0,13.0,14.0,
            // 15.0,16.0,17.0,18.0,19.0,20.000,21.0,22.0,23.0,24.0,25.0,26.0,27.0,28.0,29.0,
            // 30,31,32,33,34,35,36";


            size_t pos = 0;
            std::string token;
            int j=0;
            while ((pos = bufferString.find(delimiter)) != std::string::npos) {
                token = bufferString.substr(0, pos);
                numbArray[j] = token;
                bufferString.erase(0, pos + delimiter.length());
                j++;
            }
            numbArray[j] = bufferString;

            for (int h = 1; h <= 36; ++h) {
                //actualizeData;

                if(executor->simToVarMap.find(executor->simMap[h]) != executor->varMap.end()){
                    executor->simToVarMap[executor->simMap[h]]->value = stod(numbArray[h-1]);
                }
            }

        }
    }
    //close the socket
    close(clientSocket);
    return 0;
}