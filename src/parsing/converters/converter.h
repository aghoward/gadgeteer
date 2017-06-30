#pragma once

#include <string>
#include <vector>

#include "opcode.h"
#include "register.h"

using namespace std;

class Converter {
    public:
        string _function;
        Converter(string function) : _function(function) {};
        virtual vector<string> getBinaryFromAssembly(Opcode opcode, vector<Register> registers, string assembly) = 0;
};
