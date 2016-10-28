#include <string>

#include "qvector.h"
#include "register.h"
#include "opcode.h"
#include "converter.h"
#include "defaultconverter.h"

using namespace std;

string DefaultConverter::getBinaryFromAssembly(Opcode opcode, qvector<Register> registers, string assembly) {
    return string("" + (char)opcode.opcode);
}
