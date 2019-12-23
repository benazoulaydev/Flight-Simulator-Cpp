#include <iostream>
#include "lexer.h"
#include "Executor.h"
//#include <unordered_map>
//#include "Command.h"
//#include "PrintCommand.h"
//#include "Var.h"
//#include "VarCommand.h"
//#include "SleepCommand.h"
//#include "IfCommand.h"
//#include "WhileCommand.h"
//#include "ConnectClientCommand.h"
//#include "OpenServerCommand.h"
//#include "expression/Interpreter.h"


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
