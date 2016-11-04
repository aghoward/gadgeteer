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

qvector<string> AssemblyParser::parseSingleOperation(string assemblyString) {
    auto operation = getOperationString(assemblyString);

    auto opcode = _opcodes.first([operation] (auto oc) { return oc.name == operation; });

    auto converterName = opcode.operation;
    auto converter = _converters.first([converterName] (auto conv) { return conv->_function == converterName; });

    return converter->getBinaryFromAssembly(opcode, _registers, assemblyString);
}

qvector<string> AssemblyParser::getBinaryString(string assemblyString) {
    auto ret = qvector<string>();

    auto allOperations = splitOperations(assemblyString);
    for (auto operationString : allOperations) {
        auto currentOperations = parseSingleOperation(operationString);
        ret = crossProduct(ret, currentOperations);
    }

    return ret;
}

qvector<string> AssemblyParser::crossProduct(qvector<string> a, qvector<string> b) {
    auto ret = qvector<string>();

    if (a.empty())
        return b;
    if (b.empty())
        return a;

    for (auto i : a) {
        for (auto j : b) {
            ret.push_back(i + j);
        }
    }

    return ret;
}

string AssemblyParser::getOperationString(string assembly) {
    auto operationIndex = assembly.find(' ');
    if (operationIndex == string::npos)
        return assembly;

    return assembly.substr(0, operationIndex);
}

qvector<string> AssemblyParser::splitOperations(string assembly) {
    char token = ';';
    auto ret = qvector<string>();
    int curr = 0, next = assembly.find(token);

    while (curr < assembly.size() && (next = assembly.find(token, curr)) != string::npos) {
        ret.push_back(assembly.substr(curr, next - curr));
        curr = next + 1;
        while(assembly.at(curr) == ' ')
            curr++;
        assembly = assembly.substr(curr, assembly.size() - curr);
    }

    if (assembly.size() > 0)
        ret.push_back(assembly);

    return ret;
}

