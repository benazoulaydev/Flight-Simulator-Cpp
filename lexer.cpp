//
// Created by kfir on 12/13/19.
//
#include <fstream>
#include <regex>
#include <iostream>

using namespace std;

void lexer(vector<string> commands, string line){
    regex print("[ \t]{0,}Print.*");
    regex var("[ \t]{0,}var .*");

    if (regex_match(line, print)){
        commands.emplace_back("Print");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find(')');
        string inside = line.substr(startPos + 1, endPos - startPos - 1);
        if (inside.find('"') == string::npos){
            inside.erase(std::remove_if(inside.begin(), inside.end(), ::isspace), inside.end());
            commands.emplace_back(inside);
        } else {
            unsigned startPos2 = line.find ('"');
            unsigned endPos2 = line.find_last_of('"');
            string inside2 = line.substr(startPos2, endPos2 - startPos2+1);
            commands.emplace_back(inside2);
        }
    } else if (regex_match(line, var)){
//        cout << line.c_str()<<endl;
    }
    for (auto i = commands.begin(); i != commands.end(); ++i)
        std::cout << *i << endl;
}

void lexerFromFile(vector<string> commands, string fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lexer(commands, line);
        }
        file.close();
    }
}

