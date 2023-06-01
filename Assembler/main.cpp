#include <iostream>
#include <fstream>
#include <bitset>
#include <string>

#include "Parser.h"
#include "Code.h"

using namespace std;

int main()
{
    string path = "C:\\Users\\Henri\\source\\repos\\Assembler\\Assembler\\Tests\\rect\\";
    string filename = "RectL";
    Parser p(path+filename+".asm");
    Code c;
    bool with_symbols = false;

    if (with_symbols == false) {
        ofstream hackfile;
        hackfile.open(path+filename+".hack");

        while (p.hasMoreCommands()) {
            p.advance();
            if (p.commandType() == CommandType::COMMENT) {
                continue;
            }
            if (p.commandType() == CommandType::A) {
                bitset<16> a_command = bitset<16>(stoi(p.symbol()));
                hackfile << a_command.to_string() << "\n";
            }
            else if (p.commandType() == CommandType::C) {
                string c_command = "1110000000000000";
                
                string comp = c.comp(p.comp());
                string dest = c.dest(p.dest());
                string jump = c.jump(p.jump());

                //index        0123456789012345
                //C-command = "111cccccccdddjjj" where c = comp, d = dest, j = jump
                c_command.replace(3, 7, comp);
                c_command.replace(10, 3, dest);
                c_command.replace(13, 3, jump);

                hackfile << c_command << "\n";
            }
        }

        hackfile.close();
    }

    cout << "Translation complete.\n";

    return 0;
}