#include <string>

#include "register.h"
#include "opcode.h"
#include "converter.h"
#include "defaultconverter.h"

using namespace std;

vector<string> DefaultConverter::getBinaryFromAssembly(Opcode opcode, vector<Register> registers, string assembly) {
    auto ret = vector<string>();
    auto entry = string();

    entry += (char)(opcode.opcode);
    ret.push_back(entry);

    return ret;
}
