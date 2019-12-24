//
// Created by kfir on 12/15/19.
//

#include "ConnectClientCommand.h"
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Executor.h"

using namespace std;

int ConnectClientCommand::execute(int index) {
    //create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(stoi(executor->commands->at(index+2)));
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }



    return 3;
}

void ConnectClientCommand::sendToServer(Var* aVar) {
//if here we made a connection
    //string toSend = "set " + aVar->sim + " " + to_string(aVar->value);
    string toSend = "set /controls/flight/rudder -1";

    int n = toSend.length();

    // declaring character array
    char char_array[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, toSend.c_str());
    std::cout<<char_array <<std::endl;

    int is_sent = send(client_socket , char_array , toSend.size() , 0 );
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"Hello message sent to server" <<std::endl;
    }

//    close(client_socket);

}
