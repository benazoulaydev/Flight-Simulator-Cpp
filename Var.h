//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_VAR_H
#define UNTITLED3_VAR_H

#include <string>

using namespace std;

class Var {
private:
public:
    string name;
    double value;
    string sim;
    Var(string name, double value, string sim){
        this->name = name;
        this->value = value;
        this->sim = sim;
    }
    string toStr();
};


#endif //UNTITLED3_VAR_H
