#ifndef Opcode_H
#define Opcode_H

#include <string>
#include <vector>

using namespace std;

class Opcode {
    public:
        string name;
        int opcode;
        string operation;
        vector<int> operandSizes;

        Opcode();
};


#endif
