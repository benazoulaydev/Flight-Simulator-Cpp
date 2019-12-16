//
// Created by kfir on 11/7/19.
//

#include "Interpreter.h"
#include "Minus.h"
#include "Plus.h"
#include "Div.h"
#include "Mul.h"
#include <stack>
#include <queue>
#include <cctype>
#include <iostream>
#include <map>
#include <regex>

void printQ(queue<string> q){
    cout << "queue: ";
    while(!q.empty()){
        cout<< " "<< q.front();
        q.pop();
    }
    cout << endl;
}
void printS(stack<char> s){
    cout << "stack: ";
    while(!s.empty()){
        cout<< " "<< s.top();
        s.pop();
    }
    cout << endl;
}
void printM(map<string, string> map){
    for (auto& t : map)
        std::cout << t.first << "," << t.second << "\n";
}
string extractNumber(const string &exp, int index) {
    int i = index;
    while(exp[i] == '.' || isdigit(exp[i])){
        i++;
    }
    return exp.substr(index, i-index);
}
string Interpreter::replaceVariables(string exp){
    for (auto& t : this->variables){
        exp = regex_replace(exp, regex(t.first), t.second);
    }
    return exp;
}
bool greaterThen(char a, char b){
    if((a =='*' || a=='/') && (b=='-' || b=='+')){

    }
    return false;
}
bool isUnaryOp(string exp, int index){
    return (exp[index] == '+' || exp[index] == '-') && (index == 0 || exp[index - 1] == '(');
}
bool equals(char a, char b){
    return a==b || (a=='-' && b=='+') || (a=='+' && b=='-') || (a=='*' && b=='/') || (a=='/' && b=='*');
}
bool validation(string expStr, string expVars) {
    // check parentheses
    stack<char> s;
    for(unsigned int i=0; i < expStr.size(); i++){
        if (expStr[i] == '(') {
            s.push('(');
        } else if (expStr[i] == ')'){
            if (s.empty() || s.top() == ')'){
                return false;
            }
            s.pop();
        }
    }
    if(!s.empty()){
        return false;
    }
    // check regex
    regex r = regex("[-][a-zA-Z]");
    if(regex_search(expVars, r)){
        return false;
    }
    r=regex("^[-+(]*(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?[)]*([-+*/][-+(]*(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?[)]*)*$");
    if(!regex_match(expStr, r)){
        return false;
    }
    r = regex("[-+*/][-+*/]+");

    return !regex_search(expStr, r);
}

Expression *Interpreter::interpret(const string &exp) {
    string expr = replaceVariables(exp);
    if(!validation(expr, exp)){
        throw "Invalid Syntax";
    }
    expr = replaceMinus(expr);
    stack<char> s;
    queue<string> q;
    unsigned int i = 0;
    char token;
    while(i<expr.size()){
        token = expr[i];
        if(isUnaryOp(expr, i)){
            i++;
            if(token == '-'){
                string numberStr = extractNumber(expr, i);
                i+=numberStr.size();
                q.push("-"+numberStr);
            }
        } else if(isdigit(token)){
            string numberStr = extractNumber(expr, i);
            q.push(numberStr);
            i+=numberStr.size();
        } else if(token != '(' && token != ')'){
            while(!s.empty() && (greaterThen(s.top(), token) || (equals(token, s.top())))){ //&& s.top() != '('???
                cout <<string(1, s.top())<<endl;
                q.push(string(1, s.top()));
                s.pop();
            }

            s.push(token);
            i++;
        } else if(token == '('){
            s.push(token);
            i++;
        } else if(token == ')'){
            while(s.top() != '('){
                q.push(string(1, s.top()));
                s.pop();
                if(s.empty()){
                    //if the stack runs out without finding a left paren, then there are mismatched parentheses.
                }
            }
            s.pop(); // the char must be '('
            i++;
        }
    }
    while(!s.empty()){
        q.push(string(1, s.top()));
        s.pop();
    }
    // converting to expression
    stack<Expression*> expStack;
    string tok;
    Expression* e1, *e2;
    while(!q.empty()){
        tok = q.front();
        q.pop();
        if(isdigit(tok[0])){
            expStack.push(new Value(stod(tok)));
        } else if(tok[0]=='-' && tok!="-") {
            expStack.push(new UMinus(new Value(stod(tok.substr(1)))));
        } else {
            e1 = expStack.top();
            expStack.pop();
            if(!expStack.empty()){
                e2 = expStack.top();
                expStack.pop();
                if(tok=="-"){
                    expStack.push(new Minus(e2, e1));
                } else if(tok=="+"){
                    expStack.push(new Plus(e2, e1));
                } else if(tok=="*"){
                    expStack.push(new Mul(e2, e1));
                } else if(tok=="/"){
                    expStack.push(new Div(e2, e1));
                }
            } else {
                if(tok=="-"){
                    expStack.push(new UMinus(e1));
                } else {
                    expStack.push(e1);
                }
            }
        }
    }
    e1 = expStack.top();
    expStack.pop();
    return e1;
}

void Interpreter::setVariables(const string &exp) {
    // validation
    regex r = regex("[a-zA-Z][a-zA-Z_0-9]*[=][-]?[1-9][0-9]*[.]?[0-9]*");
    map<string, string> elements;
    string delimiter = ";", token, expr = exp+";";
    long int i = 0;
    while ((i = expr.find(delimiter)) != (long int)string::npos) {
        token = expr.substr(0, i);
        if(!regex_match(token, r)) {
            throw "Invalid variable input";
        }
        int delIndex = token.find('=');
        this->variables[token.substr(0, delIndex)] = token.substr(delIndex+1, token.size()-delIndex);
        expr = expr.substr(i + 1);
    }
}

string Interpreter::replaceMinus(string exp) {
    exp = regex_replace(exp, regex("-\\("), "-1*(");
    return exp;
}
