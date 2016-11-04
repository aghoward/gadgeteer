#include <string>

#include "qvector.h"
#include "register.h"
#include "opcode.h"
#include "converter.h"
#include "defaultconverter.h"

using namespace std;

qvector<string> DefaultConverter::getBinaryFromAssembly(Opcode opcode, qvector<Register> registers, string assembly) {
    auto ret = qvector<string>();
    auto entry = string();

    entry += (char)(opcode.opcode);
    ret.push_back(entry);

    return ret;
}
