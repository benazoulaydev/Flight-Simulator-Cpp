//
// Created by kfir on 11/3/19.
//

#ifndef EX1_DIV_H
#define EX1_DIV_H


#include "Variable.h"
#include "UMinus.h"
#include "BinaryOperator.h"

class Div: public BinaryOperator {

public:
    Div(Expression *l, Expression *r){
        this->left = l;
        this->right = r;
    }
    double calculate() override {
        double u = this->right->calculate();
        if (u==0){
            throw "Division by 0 Error";
        }
        return this->left->calculate() / u;
    }
};


#endif //EX1_DIV_H
