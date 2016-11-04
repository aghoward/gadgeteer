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
        qvector<string> parseSingleOperation(string assemblyString);
        qvector<string> crossProduct(qvector<string> a, qvector<string> b);
        qvector<string> splitOperations(string assembly);

    public:
        AssemblyParser(qvector<Opcode> opcodes, qvector<Register> registers);
        ~AssemblyParser();
        qvector<string> getBinaryString(string assemblyString);

};

#endif
