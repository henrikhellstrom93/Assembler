#include <string>

#include "Parser.h"

Parser::Parser(string filename)
{
    asmfile.open(filename);
    if (!asmfile.is_open()) {
        cout << "ERROR: Unable to open file with path '" << filename << "'\n";
    }
}

Parser::~Parser()
{
    asmfile.close();
}

bool Parser::hasMoreCommands() {
    char next = asmfile.peek();
    if ((int)next != EOF) {
        return true;
    }
    else {
        return false;
    }
}

void Parser::advance() {
    getline(asmfile, current_line);
    if (current_line == "") {
        if (hasMoreCommands()) {
            //Keep going until either 1) There are no more lines in the file or 2) The current line is not blank
            advance();
        }
    }
}

CommandType Parser::commandType() {
    size_t pos = current_line.find_first_not_of(" ");

    if (current_line[pos] == '@') {
        return CommandType::A;
    }
    if (current_line[pos] == '(') {
        return CommandType::L;
    }
    if (current_line[pos] == '/') {
        return CommandType::COMMENT;
    }
    if (pos == -1) {
        //It is a line with only whitespace, we can treat this as a comment
        return CommandType::COMMENT;
    }

    //C commands always have either "=" or ";"
    pos = current_line.find_first_of("=;");

    if (pos != string::npos) {
        return CommandType::C;
    }


    cout << "ERROR: Line '" << current_line << "' contains an unrecognizable command.\n";

    return CommandType::ERROR;
}

string Parser::symbol() {
    //Error handling
    if (commandType() != CommandType::A && commandType() != CommandType::L) {
        cout << "ERROR: symbol() called but the current command is neither an A or L command.\n";
        return "ERROR";
    }

    //Find symbol
    int start_pos = current_line.find_first_of("@(");
    int end_pos = current_line.find_first_of(") ");
    //If there's no trailing spaces or closing parantheses, we have current_line = "@xxxxxx"
    if (end_pos == -1) {
        end_pos = current_line.size();
    }
    string symbol = current_line.substr(start_pos + 1, end_pos - start_pos);

    return symbol;
}

string Parser::dest() {
    //Error handling
    if (commandType() != CommandType::C) {
        cout << "ERROR: dest() called but the current command is not a C command.\n";
        return "ERROR";
    }

    //Find dest
    int start_pos = current_line.find_first_not_of(" ");
    int end_pos = current_line.find_first_of("=");
    //If there's no equal sign, this must be a jump command, i.e., "C;JJJ"
    if (end_pos == -1) {
        return "";
    }
    string dest = current_line.substr(start_pos, end_pos - start_pos);

    return dest;
}

string Parser::comp() {
    //Error handling
    if (commandType() != CommandType::C) {
        cout << "ERROR: comp() called but the current command is not a C command.\n";
        return "ERROR";
    }

    //Find dest
    int start_pos = current_line.find_first_of("=") + 1;
    int end_pos = current_line.find_first_of(";") - 1;
    //If there's no semicolon, this must be without a jump command, i.e., "D=C"
    if (end_pos == -1) {
        end_pos = current_line.size();
    }
    string comp = current_line.substr(start_pos, end_pos - start_pos + 1);

    return comp;
}

string Parser::jump() {
    //Error handling
    if (commandType() != CommandType::C) {
        cout << "ERROR: jump() called but the current command is not a C command.\n";
        return "ERROR";
    }

    //Find dest
    int start_pos = current_line.find_first_of(";");
    int end_pos = current_line.size();
    //If there's no semicolon, this must be without a jump command, i.e., "D=C"
    if (start_pos == -1) {
        return "";
    }
    string jump = current_line.substr(start_pos+1, end_pos - start_pos + 1);

    return jump;
}
