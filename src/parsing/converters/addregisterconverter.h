#pragma once

#include <string>
#include <vector>

#include "opcode.h"
#include "register.h"
#include "converter.h"
#include "register.h"

using namespace std;

class AddRegisterConverter : public Converter {
    private:
        string getRegisterName(string assembly);
        string getValueForRegister(Register reg, int baseValue);

    public:
        AddRegisterConverter() : Converter("addRegister") {};
        vector<string> getBinaryFromAssembly(Opcode opcode, vector<Register> registers, string assembly);
};

