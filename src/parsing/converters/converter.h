#ifndef Converter_H
#define Converter_H

#include <string>

#include "opcode.h"
#include "register.h"
#include "qvector.h"

using namespace std;

class Converter {
    public:
        string _function;
        Converter(string function) : _function(function) {};
        virtual qvector<string> getBinaryFromAssembly(Opcode opcode, qvector<Register> registers, string assembly) = 0;
};

#endif
