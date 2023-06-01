#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>

using namespace std;

enum CommandType { A, C, L, COMMENT, ERROR };

class Parser
{
public:
    Parser(string filename);
    virtual ~Parser();
    bool hasMoreCommands();
    void advance();
    CommandType commandType();
    string symbol();
    string dest();
    string comp();
    string jump();

protected:

private:
    ifstream asmfile;
    string current_line;
};


#endif // PARSER_H
