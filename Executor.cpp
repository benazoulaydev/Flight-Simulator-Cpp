//
// Created by kfir on 12/19/19.
//

#include "Executor.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "VarCommand.h"
#include "ConnectClientCommand.h"
#include "OpenServerCommand.h"
#include "expression/Interpreter.cpp"

void Executor::initiate() {
    // initializing commands objects.
    PrintCommand* p = new PrintCommand(this);
    commandsMap["Print"] = (Command*)p;
    VarCommand* v = new VarCommand(this);
    commandsMap["var"] = (Command*)v;
    OpenServerCommand* os = new OpenServerCommand(this);
    commandsMap["openDataServer"] = (Command*)os;
    ConnectClientCommand* cc = new ConnectClientCommand();
    commandsMap["connectControlClient"] = (Command*)cc;
    SleepCommand* s = new SleepCommand();
    commandsMap["Sleep"] = (Command*)s;
    IfCommand* ic = new IfCommand(this);
    commandsMap["if"] = (Command*)ic;
    WhileCommand* w = new WhileCommand(this);
    commandsMap["while"] = (Command*)w;

    createSimMap();
}

void Executor::executeScope(int start, int end) {
    // execute the commands.
    int i = start;
    while (i < end){
        if (commandsMap.find(commands->at(i)) != commandsMap.end()){
            Command* c = commandsMap.at(commands->at(i));
            i += c->execute(i);
        } else {
            varMap[commands->at(i)]->value = interpretFromString(commands->at(i+2));
            i += 3;
        }
    }
}

double Executor::interpretFromString(string expression) {
    refreshVariables();
    return this->interpreter.interpret(expression)->calculate();
}

void Executor::refreshVariables() {
    for(auto varPair : this->varMap){
        this->interpreter.setVariables(varPair.second->toStr());
    }
}

void Executor::createSimMap() {
    simMap[1] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    simMap[2] = "/sim/time/warp";
    simMap[3] = "/controls/switches/magnetos";
    simMap[4] = "/instrumentation/heading-indicator/offset-deg";
    simMap[5] = "/instrumentation/altimeter/indicated-altitude-ft";
    simMap[6] = "/instrumentation/altimeter/pressure-alt-ft";
    simMap[7] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    simMap[8] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    simMap[9] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    simMap[10] = "/instrumentation/attitude-indicator/internal-roll-deg";
    simMap[11] = "/instrumentation/encoder/indicated-altitude-ft";
    simMap[12] = "/instrumentation/encoder/pressure-alt-ft";
    simMap[13] = "/instrumentation/gps/indicated-altitude-ft";
    simMap[14] = "/instrumentation/gps/indicated-ground-speed-kt";
    simMap[15] = "/instrumentation/gps/indicated-vertical-speed";
    simMap[16] = "/instrumentation/heading-indicator/indicated-heading-deg";
    simMap[17] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    simMap[18] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    simMap[19] = "/instrumentation/turn-indicator/indicated-turn-rate";
    simMap[20] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    simMap[21] = "/controls/flight/aileron";
    simMap[22] = "/controls/flight/elevator";
    simMap[23] = "/controls/flight/rudder";
    simMap[24] = "/controls/flight/flaps";
    simMap[25] = "/controls/engines/engine/throttle";
    simMap[26] = "/controls/engines/current-engine/throttle";
    simMap[27] = "/controls/switches/master-avionics";
    simMap[28] = "/controls/switches/starter";
    simMap[29] = "/engines/active-engine/auto-start";
    simMap[30] = "/controls/flight/speedbrake";
    simMap[31] = "/sim/model/c172p/brake-parking";
    simMap[32] = "/controls/engines/engine/primer";
    simMap[33] = "/controls/engines/current-engine/mixture";
    simMap[34] = "/controls/switches/master-bat";
    simMap[35] = "/controls/switches/master-alt";
    simMap[36] = "/engines/engine/rpm";
}