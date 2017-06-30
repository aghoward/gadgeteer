#pragma once

#include <string>

#include "register.h"
#include "opcode.h"
#include "converter.h"

class AssemblyParser {
    private:
        vector<Register> _registers;
        vector<Opcode> _opcodes;
        vector<Converter*> _converters;

        string getOperationString(string assembly);
        vector<string> parseSingleOperation(string assemblyString);
        vector<string> crossProduct(vector<string> a, vector<string> b);
        vector<string> splitOperations(string assembly);

    public:
        AssemblyParser(vector<Opcode> opcodes, vector<Register> registers);
        ~AssemblyParser();
        vector<string> getBinaryString(string assemblyString);

};

