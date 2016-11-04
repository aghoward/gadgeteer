#include <string>

#include "addregisterconverter.h"
#include "opcode.h"
#include "register.h"
#include "qvector.h"

using namespace std;

qvector<string> AddRegisterConverter::getBinaryFromAssembly(Opcode opcode, qvector<Register> registers, string assembly) {
    auto ret = qvector<string>();
    auto baseValue = opcode.opcode;
    auto regName = getRegisterName(assembly);
    auto predicate = [regName] (Register r) { return r.name == regName; };

    if (registers.any(predicate)) {
        auto reg = registers.first(predicate);
        ret.push_back(getValueForRegister(reg, baseValue));
    }
    else if (regName == "*") {
        for (auto& it : registers) {
            ret.push_back(getValueForRegister(it, baseValue));
        }
    }

    return ret;
}

string AddRegisterConverter::getValueForRegister(Register reg, int baseValue) {
    auto ret = string();
    ret += (char)(baseValue + reg.value);
    return ret;
}

string AddRegisterConverter::getRegisterName(string assembly) {
    auto index = assembly.find(' ');
    auto regLength = assembly.size() - (index + 1);
    return assembly.substr(index + 1, regLength);
}
