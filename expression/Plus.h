//
// Created by kfir on 11/3/19.
//

#ifndef EX1_PLUS_H
#define EX1_PLUS_H


#include "BinaryOperator.h"

class Plus: public BinaryOperator {
public:
    Plus(Expression *l, Expression *r){
        this->left = l;
        this->right = r;
    }
    double calculate() override {
        return this->left->calculate() + this->right->calculate();
    }
};


#endif //EX1_PLUS_H
