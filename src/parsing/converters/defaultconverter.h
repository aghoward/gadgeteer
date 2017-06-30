#pragma once

#include <string>
#include <vector>

#include "converter.h"
#include "register.h"
#include "opcode.h"

class DefaultConverter : public Converter {
    public:
        DefaultConverter() : Converter("default") {};
        vector<string> getBinaryFromAssembly(Opcode opcode, vector<Register> registers, string assembly);
};

using namespace std;
