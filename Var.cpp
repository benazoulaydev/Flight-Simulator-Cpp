//
// Created by kfir on 12/15/19.
//

#include "Var.h"
/**
 *
 * @return  a string the var name = the value
 */
string Var::toStr() {

    return this->name+"="+to_string(value);
}
