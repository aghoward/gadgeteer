#ifndef DefaultConverter_H
#define DefaultConverter_H

#include <string>

#include "converter.h"
#include "qvector.h"
#include "register.h"
#include "opcode.h"

class DefaultConverter : public Converter {
    public:
        DefaultConverter() : Converter("default") {};
        qvector<string> getBinaryFromAssembly(Opcode opcode, qvector<Register> registers, string assembly);
};

using namespace std;

#endif
