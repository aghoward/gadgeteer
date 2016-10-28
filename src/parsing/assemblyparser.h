#ifndef AssemblyParser_H
#define AssemblyParser_H

#include <string>

#include "qvector.h"
#include "register.h"
#include "opcode.h"
#include "converter.h"

class AssemblyParser {
    private:
        qvector<Register> _registers;
        qvector<Opcode> _opcodes;
        qvector<Converter*> _converters;

        string getOperationString(string assembly);

    public:
        AssemblyParser(qvector<Opcode> opcodes, qvector<Register> registers);
        ~AssemblyParser();
        string getBinaryString(string assemblyString);

};

#endif
