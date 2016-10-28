#include <string>

#include "addregisterconverter.h"
#include "opcode.h"
#include "register.h"
#include "qvector.h"

using namespace std;

string AddRegisterConverter::getBinaryFromAssembly(Opcode opcode, qvector<Register> registers, string assembly) {
    auto baseValue = opcode.opcode;
    auto regName = getRegisterName(assembly);
    auto reg = registers.first([regName] (auto r) { return r.name == regName; });

    auto intValue = baseValue + reg.value;
    return string("" + (char)intValue);
}

string AddRegisterConverter::getRegisterName(string assembly) {
    auto index = assembly.find(' ');
    auto regLength = assembly.size() - (index + 1);
    return assembly.substr(index + 1, regLength);
}
