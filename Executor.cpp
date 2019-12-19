//
// Created by kfir on 12/19/19.
//

#include "executor.h"

void executor::initiate() {
    // initializing commands objects.
    PrintCommand p = PrintCommand(commands, &varMap);
    commandsMap["Print"] = (Command*)&p;
    VarCommand v = VarCommand(commands, &varMap, &inp);
    commandsMap["var"] = (Command*)&v;
    OpenServerCommand os = OpenServerCommand();
    commandsMap["openDataServer"] = (Command*)&os;
    ConnectClientCommand cc = ConnectClientCommand();
    commandsMap["connectControlClient"] = (Command*)&cc;
    SleepCommand s = SleepCommand();
    commandsMap["Sleep"] = (Command*)&s;
    IfCommand ic = IfCommand(commands, &varMap);
    commandsMap["if"] = (Command*)&ic;
    WhileCommand w = WhileCommand(commands, &varMap, &inp);
    commandsMap["while"] = (Command*)&w;
}

void executor::executeScope() {
    // execute the commands.
    int i = 0;
    while (i < commands->size()){
        if (commandsMap.find(commands->at(i)) != commandsMap.end()){
            Command* c = commandsMap.at(commands->at(i));
            i += c->execute(i);
        } else {
            varMap[commands->at(i)]->value = ((VarCommand*)commandsMap["var"])->
                    interpretFromString(commands->at(i+2));
            i += 3;
        }
    }


}
