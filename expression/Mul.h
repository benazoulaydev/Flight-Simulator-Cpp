//
// Created by kfir on 11/3/19.
//

#ifndef EX1_MUL_H
#define EX1_MUL_H


#include "BinaryOperator.h"
#include "Value.h"

class Mul: public BinaryOperator {
public:
    Mul(Expression *l, Expression *r){
        this->left = l;
        this->right = r;
    }
    double calculate() override {
        return this->left->calculate() * this->right->calculate();
    }
};


#endif //EX1_MUL_H
