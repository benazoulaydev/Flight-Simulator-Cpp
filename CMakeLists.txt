cmake_minimum_required(VERSION 3.15)
project(untitled3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
file(GLOB expression_SRC
    "*.h"
    "*.cpp"
)

add_executable(expression ${expression_SRC})

add_executable(untitled3 main.cpp  lexer.h lexer.cpp Command.h PrintCommand.cpp PrintCommand.h Var.cpp Var.h VarCommand.cpp VarCommand.h SleepCommand.cpp SleepCommand.h WhileCommand.cpp WhileCommand.h IfCommand.cpp IfCommand.h OpenServerCommand.cpp OpenServerCommand.h ConnectClientCommand.cpp ConnectClientCommand.h Executor.cpp Executor.h FunctionCommand.cpp FunctionCommand.h)