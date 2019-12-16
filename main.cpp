#include <iostream>
#include <unordered_map>
#include "lexer.h"
#include "Command.h"
#include "PrintCommand.h"
#include "Var.h"
#include "VarCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "ConnectClientCommand.h"
#include "OpenServerCommand.h"
#include "expression/ex1.h"

using namespace std;


int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Error No file inserted";
        return -1;
    }
    vector<string> commands;
    lexerFromFile(&commands, argv[1]);
    // for checking - print the commands from the lexer
//    for (auto i = commands.begin(); i != commands.end(); ++i)
//        std::cout << *i << endl;

    // initializing data structures.
    unordered_map<string, Command*> commandsMap;
    unordered_map<string, Var*> varMap;
    // initializing commands objects.
    PrintCommand p = PrintCommand(&commands, &varMap);
    commandsMap["Print"] = (Command*)&p;
    VarCommand v = VarCommand(&commands, &varMap);
    commandsMap["var"] = (Command*)&v;
    OpenServerCommand os = OpenServerCommand();
    commandsMap["openDataServer"] = (Command*)&os;
    ConnectClientCommand cc = ConnectClientCommand();
    commandsMap["connectControlClient"] = (Command*)&cc;
    SleepCommand s = SleepCommand();
    commandsMap["Sleep"] = (Command*)&s;
    IfCommand ic = IfCommand(&commands, &varMap);
    commandsMap["if"] = (Command*)&ic;
    WhileCommand w = WhileCommand(&commands, &varMap);
    commandsMap["while"] = (Command*)&w;

    // execute the commands.
    int i = 0;
    while (i < commands.size()){
        if (commandsMap.find(commands.at(i)) != commandsMap.end()){
            Command* c = commandsMap.at(commands.at(i));
            i += c->execute(i);
        } else {
            varMap[commands.at(i)]->value = commandsMap["var"]->interpretFromString(commands.at(i+2));//stod(commands.at(i+2));
            i += 3;
        }
    }
    return 0;
}
