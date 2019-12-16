//
// Created by kfir on 11/3/19.
//

#ifndef EX1_UMINUS_H
#define EX1_UMINUS_H


#include "Value.h"
#include "UnaryOperator.h"

class UMinus: public UnaryOperator {
public:
    explicit UMinus(Expression *expression) {
        this->exp = expression;
    }
    double calculate() override {
        return -(this->exp->calculate());
    }
};


#endif //EX1_UMINUS_H
