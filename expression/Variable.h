//
// Created by kfir on 11/3/19.
//

#ifndef EX1_VARIABLE_H
#define EX1_VARIABLE_H


#include <string>
#include "Expression.h"

class Variable: public Expression {
private:
    string name;
    double value;
public:
    double calculate() override{
        return this->value;
    }
    Variable(const string &n, double val){
        this->name = n;
        this->value = val;
    }
    Variable& operator++(){
        this->value+=1;
        return *this;
    }
    Variable& operator++(int){
        this->value+=1;
        return *this;
    }
    Variable& operator+=(double v){
        this->value += v;
        return *this;
    }
    Variable& operator--(){
        this->value-=1;
        return *this;
    }
    Variable operator--(int){
        this->value-=1;
        return *this;
    }
    Variable& operator-=(double v){
        this->value -= v;
        return *this;
    }
};


#endif //EX1_VARIABLE_H
