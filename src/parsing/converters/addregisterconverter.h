#ifndef AddRegisterConverter_H
#define AddRegisterConverter_H

#include <string>

#include "qvector.h"
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
        qvector<string> getBinaryFromAssembly(Opcode opcode, qvector<Register> registers, string assembly);
};

#endif

