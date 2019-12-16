//
// Created by kfir on 11/7/19.
//

#ifndef EX1_MINUS_H
#define EX1_MINUS_H


#include "Expression.h"
#include "BinaryOperator.h"

class Minus: public BinaryOperator {
public:
    Minus(Expression *l, Expression *r){
        this->left = l;
        this->right = r;
    }
    double calculate() override {
        return this->left->calculate() - this->right->calculate();
    }
};


#endif //EX1_MINUS_H
