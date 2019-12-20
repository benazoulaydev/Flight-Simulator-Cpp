//
// Created by kfir on 12/13/19.
//
#include <fstream>
#include <regex>
#include <iostream>

using namespace std;

void lexer(vector<string> *commands, string line){
    regex print("[ \t]{0,}Print.*");
    regex var("[ \t]{0,}var .*");
    regex sleep("[ \t]{0,}Sleep.*");
    regex openServer("[ \t]{0,}openDataServer.*");
    regex connectClient("[ \t]{0,}connectControlClient.*");
    regex whileLoop("[ \t]{0,}while.*");
    regex ifCon("[ \t]{0,}if.*");

    if (regex_match(line, print)){
        (*commands).emplace_back("Print");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find(')');
        string in = line.substr(startPos + 1, endPos - startPos - 1);
        if (in.find('"') == string::npos){
            in.erase(std::remove_if(in.begin(), in.end(), ::isspace), in.end());
            (*commands).emplace_back(in);
        } else {
            unsigned startPos2 = line.find ('"');
            unsigned endPos2 = line.find_last_of('"');
            string inside2 = line.substr(startPos2, endPos2 - startPos2+1);
            (*commands).emplace_back(inside2);
        }
    } else if (regex_match(line, var)){
        (*commands).emplace_back("var");
        string in = line.substr(line.find("var")+3);
        in.erase(std::remove_if(in.begin(), in.end(), ::isspace), in.end());
        regex rightArrow(".*->.*");
        regex leftArrow(".*<-.*");
        if (regex_match(in,rightArrow)){
            (*commands).emplace_back(in.substr(0, in.find("->")));
            (*commands).emplace_back("->");
            (*commands).emplace_back("sim");
            unsigned startPos = line.find ('"');
            unsigned endPos = line.find_last_of('"');
            (*commands).emplace_back(line.substr(startPos+1,endPos-startPos-1));
        } else if (regex_match(in,leftArrow)){
            (*commands).emplace_back(in.substr(0, in.find("<-")));
            (*commands).emplace_back("<-");
            (*commands).emplace_back("sim");
            unsigned startPos = line.find ('"');
            unsigned endPos = line.find_last_of('"');
            (*commands).emplace_back(line.substr(startPos+1,endPos-startPos-1));
        } else { // other options
            (*commands).emplace_back(in.substr(0, in.find('=')));
            (*commands).emplace_back("=");
            (*commands).emplace_back(in.substr(in.find('=')+1));
        }
    } else if (regex_match(line, sleep)){
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        (*commands).emplace_back("Sleep");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find_last_of(')');
        (*commands).emplace_back(line.substr(startPos+1,endPos-startPos-1));
    } else if (regex_match(line, openServer)){
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        (*commands).emplace_back("openDataServer");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find_last_of(')');
        (*commands).emplace_back(line.substr(startPos+1,endPos-startPos-1));
    } else if (regex_match(line, connectClient)){
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        (*commands).emplace_back("connectControlClient");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find_last_of(')');
        string in = line.substr(startPos+1,endPos-startPos-1);
        (*commands).emplace_back(in.substr(0, in.find(',')));
        (*commands).emplace_back(in.substr(in.find(',')+1));
    } else if (regex_match(line, whileLoop) || regex_match(line, ifCon)){
        string in;
        if (regex_match(line, ifCon)){
            (*commands).emplace_back("if");
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            in = line.substr(2);
        } else {
            (*commands).emplace_back("while");
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            in = line.substr(5);
        }
        string dl = "";
        int i = 0;
        while(i < in.size()){
            if (in[i]=='<' || in[i]=='>' || in[i]=='!' || in[i]=='=')
                dl+=in[i];
            i++;
        }
        if (in[0] != '!') // when it is like: !exp there is no first exp.
            (*commands).emplace_back(in.substr(0, in.find(dl)));
        (*commands).emplace_back(dl);
        string in2 = in.substr(in.find(dl) + dl.length());
        (*commands).emplace_back(in2.substr(0,in2.find('{')));
        (*commands).emplace_back("{");
    } else { // just changing var or }
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line[0] == '}'){
            (*commands).emplace_back("}");
        } else {
            (*commands).emplace_back(line.substr(0, line.find('=')));
            (*commands).emplace_back("=");
            (*commands).emplace_back(line.substr(line.find('=')+1));
        }
    }
}

void lexerFromFile(vector<string> *commands, string fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lexer(commands, line);
        }
        file.close();
    }
}

