//
// Created by kfir on 12/13/19.
//
#include <fstream>
#include <regex>
#include <iostream>

using namespace std;
//TODO EMPTY LINES FLY.TXT
/**
 * Create the lexer from the file given in argument
 * @param commands
 * @param line
 */
void lexer(vector<string> *commands, string line){
    //regex for each command
    regex print("[ \t]{0,}Print.*");
    regex var("[ \t]{0,}var .*");
    regex sleep("[ \t]{0,}Sleep.*");
    regex openServer("[ \t]{0,}openDataServer.*");
    regex connectClient("[ \t]{0,}connectControlClient.*");
    regex whileLoop("[ \t]{0,}while.*");
    regex ifCon("[ \t]{0,}if.*");
    regex func("[^=]*\\(.*\\).*");
    regex funcDec(".*\\([ \t]{0,}var .*\\).*");

    //if print do:
    if (regex_match(line, print)){
        //add the command in the command vector
        (*commands).emplace_back("Print");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find_last_of(')');
        //get the string inside the print()
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
        //if variable do:
        (*commands).emplace_back("var");
        //add the command in the command vector
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
        //if sleep do:
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        //add the command in the command vector
        (*commands).emplace_back("Sleep");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find_last_of(')');
        (*commands).emplace_back(line.substr(startPos+1,endPos-startPos-1));
    } else if (regex_match(line, openServer)){
        //if openServer do:
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        //add the command in the command vector
        (*commands).emplace_back("openDataServer");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find_last_of(')');
        (*commands).emplace_back(line.substr(startPos+1,endPos-startPos-1));
    } else if (regex_match(line, connectClient)){
        //if connectClient do:
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        //add the command in the command vector
        (*commands).emplace_back("connectControlClient");
        unsigned startPos = line.find ('(');
        unsigned endPos = line.find_last_of(')');
        string in = line.substr(startPos+1,endPos-startPos-1);
        string right = in.substr(1, in.find(','));
        right = in.substr(1, right.size() - 2);
        string left = in.substr(in.find(',')+1);
        (*commands).emplace_back(right);
        (*commands).emplace_back(left);
    } else if (regex_match(line, whileLoop) || regex_match(line, ifCon)){
        //if whileLoop do:
        string in;
        if (regex_match(line, ifCon)){
            (*commands).emplace_back("if");
            //add the command in the command vector
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            in = line.substr(2);
        } else {
            (*commands).emplace_back("while");
            //add the command in the command vector
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            in = line.substr(5);
        }
        string dl = "";
        unsigned i = 0;
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
    } else if(regex_match(line, func)){ // function declaration or usage
        if(regex_match(line, funcDec)){ // function declaration
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            (*commands).emplace_back(line.substr(0,line.find('(')));
            (*commands).emplace_back("var");
            unsigned startPos = line.find ('(');
            unsigned endPos = line.find(')');
            string in = line.substr(startPos + 4, endPos - startPos - 4);
            (*commands).emplace_back(in);
            (*commands).emplace_back("{");
        } else { // usage
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
            (*commands).emplace_back(line.substr(0,line.find('(')));
            unsigned startPos = line.find ('(');
            unsigned endPos = line.find(')');
            string in = line.substr(startPos + 1, endPos - startPos - 1);
            (*commands).emplace_back(in);
        }
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

/**
 * Create the lexer from file
 * @param commands
 * @param fileName
 */
void lexerFromFile(vector<string> *commands, string fileName) {
    //open the file and create the lexer form it
    ifstream file(fileName);
    if (file.is_open()) {
        string line;

        while (getline(file, line)) {
            lexer(commands, line);
        }
        file.close();
    }
}

