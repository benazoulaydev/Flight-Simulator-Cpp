//
// Created by kfir on 11/3/19.
//

#ifndef EX1_VALUE_H
#define EX1_VALUE_H


#include "Expression.h"

class Value: public Expression {
private:
    double value;
public:
    explicit Value(double d){
        this->value = d;
    }
    double calculate() override{
        return this->value;
    }
};




#endif //EX1_VALUE_H
