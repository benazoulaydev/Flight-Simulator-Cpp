#include <iostream>
#include "lexer.h"
using namespace std;


int main(int argc, char* argv[]) {
    vector<string> commands;
    lexerFromFile(commands, argv[1]);
    return 0;

}
