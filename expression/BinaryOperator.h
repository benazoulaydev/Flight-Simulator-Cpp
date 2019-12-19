//
// Created by kfir on 11/4/19.
//

#ifndef EX1_BINARYOPERATOR_H
#define EX1_BINARYOPERATOR_H


#include "Expression.h"

class BinaryOperator: public Expression{
protected:
    Expression *left;
    Expression *right;
};


#endif //EX1_BINARYOPERATOR_H
