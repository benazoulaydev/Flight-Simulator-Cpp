//
// Created by kfir on 11/3/19.
//

#ifndef EX1_UPLUS_H
#define EX1_UPLUS_H


#include "UnaryOperator.h"
#include "Value.h"

class UPlus: public UnaryOperator {
public:
    explicit UPlus(Expression *expression) {
        this->exp = expression;
    }
    double calculate() override {
        return this->exp->calculate();
    }
};


#endif //EX1_UPLUS_H
