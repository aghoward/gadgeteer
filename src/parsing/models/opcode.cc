#include <string>
#include <vector>

#include "opcode.h"

using namespace std;

Opcode::Opcode() {
    name = "";
    opcode = 0;
    operation = "";
    operandSizes = vector<int>();
}
