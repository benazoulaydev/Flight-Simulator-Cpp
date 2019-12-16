//
// Created by kfir on 12/15/19.
//

#include "Var.h"

string Var::toStr() {

    return this->name+"="+to_string(value);
}
