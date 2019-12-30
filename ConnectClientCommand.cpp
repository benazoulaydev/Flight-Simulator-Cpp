//
// Created by kfir on 12/15/19.
//

#include "ConnectClientCommand.h"
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Executor.h"

using namespace std;
/**
 *
 * @param index
 * @return 0
 *
 * execute func by the executor class
 */
int ConnectClientCommand::execute(int index) {
    //create socket
    this->client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4

    //string to char *
    string addressRecvStr = executor->commands->at(index+1);
    int n = addressRecvStr.length();
    // declaring character array
    char* addressRecvStrChar = new char[n + 1];
    // copying the contents of the
    // string to char array
    strcpy(addressRecvStrChar, addressRecvStr.c_str());
    address.sin_addr.s_addr = inet_addr(addressRecvStrChar);  //the localhost address
    address.sin_port = htons(stoi(executor->commands->at(index+2)));
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    }
    delete [] addressRecvStrChar;
    return 3;
}

/**
 *
 * @param aVar
 * send to server value to change.
 */
void ConnectClientCommand::sendToServer(Var* aVar) {
    //if here we made a connection send to server msg with at the end "\r\n"
    string toSend = "set " + aVar->sim + " " + to_string(aVar->value) + "\r\n";
    //length of message to send
    int n = toSend.length();

    // declaring character array
    char* char_array =  new char[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, toSend.c_str());
    //send the message
    int is_sent = send(client_socket , char_array , toSend.size() , 0 );
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    }
    delete [] char_array;
}
