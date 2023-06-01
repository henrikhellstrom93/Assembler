#ifndef CODE_H
#define CODE_H

#include <iostream>

using namespace std;

class Code
{
public:
    Code();
    virtual ~Code();
    string dest(string mnemonic);
    string comp(string mnemonic);
    string jump(string mnemonic);

protected:

private:
};

#endif // CODE_H
