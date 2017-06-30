#include <algorithm>
#include <string>
#include <vector>

#include "assemblyparser.h"
#include "register.h"
#include "opcode.h"
#include "converter.h"
#include "defaultconverter.h"
#include "addregisterconverter.h"
#include "queryalgorithms.h"

AssemblyParser::AssemblyParser(vector<Opcode> opcodes, vector<Register> registers)
    : _opcodes(opcodes), _registers(registers)
{
    _converters = vector<Converter*>();
    _converters.push_back(new DefaultConverter());
    _converters.push_back(new AddRegisterConverter());
}

AssemblyParser::~AssemblyParser() {
    for (auto it = _converters.begin(); it != _converters.end(); it++)
        delete *it;
}

vector<string> AssemblyParser::parseSingleOperation(string assemblyString) {
    auto operation = getOperationString(assemblyString);

    auto opcode = *find_if(_opcodes.begin(), _opcodes.end(), [operation] (auto oc) { return oc.name == operation; });    

    auto converterName = opcode.operation;
    auto converter = *find_if(_converters.begin(), _converters.end(), [converterName] (auto conv) { return conv->_function == converterName; });

    return converter->getBinaryFromAssembly(opcode, _registers, assemblyString);
}

vector<string> AssemblyParser::getBinaryString(string assemblyString) {
    auto ret = vector<string>();

    auto allOperations = splitOperations(assemblyString);
    for (auto operationString : allOperations) {
        auto currentOperations = parseSingleOperation(operationString);
        ret = crossProduct(ret, currentOperations);
    }

    return ret;
}

vector<string> AssemblyParser::crossProduct(vector<string> a, vector<string> b) {
    auto ret = vector<string>();

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

vector<string> AssemblyParser::splitOperations(string assembly) {
    char token = ';';
    auto ret = vector<string>();
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

