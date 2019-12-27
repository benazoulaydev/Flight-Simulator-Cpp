#include <iostream>
#include "lexer.h"
#include "Executor.h"

#include <string>
#include <chrono>
#include <thread>

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cout << "Error No file inserted";
        return -1;
    }
    vector<string> commands;
    lexerFromFile(&commands, argv[1]);
    bool status = false;
    Executor executor(&commands, &status);
    executor.initiate();
    executor.executeScope(0, commands.size());
    this_thread::sleep_for(chrono::milliseconds(5000));
    return 0;
}
