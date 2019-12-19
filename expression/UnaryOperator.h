//
// Created by kfir on 11/4/19.
//

#ifndef EX1_UNARYOPERATOR_H
#define EX1_UNARYOPERATOR_H


#include "Expression.h"

class UnaryOperator: public Expression {
protected:
    Expression* exp;
};


#endif //EX1_UNARYOPERATOR_H
