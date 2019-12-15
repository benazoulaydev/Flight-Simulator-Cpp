//
// Created by kfir on 12/15/19.
//

#ifndef UNTITLED3_COMMAND_H
#define UNTITLED3_COMMAND_H
/*
 * Command interface
 */
class Command {
public:
    virtual int execute(int index) = 0;
    virtual ~Command() = default;
};

#endif //UNTITLED3_COMMAND_H
