#include <string>

#include "assemblyparser.h"
#include "qvector.h"
#include "register.h"
#include "opcode.h"
#include "converter.h"
#include "defaultconverter.h"
#include "addregisterconverter.h"

AssemblyParser::AssemblyParser(qvector<Opcode> opcodes, qvector<Register> registers)
    : _opcodes(opcodes), _registers(registers)
{
    _converters = qvector<Converter*>();
    _converters.push_back(new DefaultConverter());
    _converters.push_back(new AddRegisterConverter());
}

AssemblyParser::~AssemblyParser() {
    for (auto it = _converters.begin(); it != _converters.end(); it++)
        delete *it;
}

string AssemblyParser::getBinaryString(string assemblyString) {
    auto operation = getOperationString(assemblyString);
    auto opcode = _opcodes.first([operation] (auto oc) { return oc.name == operation; });
    auto converterName = opcode.operation;
    auto converter = _converters.first([converterName] (auto conv) { return conv->_function == converterName; });

    return converter->getBinaryFromAssembly(opcode, _registers, assemblyString);
}

string AssemblyParser::getOperationString(string assembly) {
    auto operationIndex = assembly.find(' ');
    if (operationIndex == string::npos)
        return assembly;

    return assembly.substr(0, operationIndex);
}
