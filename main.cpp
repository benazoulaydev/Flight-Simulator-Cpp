#include <iostream>
#include "lexer.h"
#include "Executor.h"

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;


int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Error No file inserted";
        return -1;
    }
    vector<string> commands;
    lexerFromFile(&commands, argv[1]);
//     for checking - print the commands from the lexer
//    for (auto i = commands.begin(); i != commands.end(); ++i)
//        std::cout << *i << endl;

    Executor executor(&commands);
    executor.initiate();
    executor.executeScope(0, commands.size());
    return 0;


}
