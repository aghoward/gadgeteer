#include <string>
#include <fstream>

#include "assemblyparserfactory.h"
#include "assemblyparser.h"
#include "opcodeparser.h"
#include "registerparser.h"
#include "register.h"
#include "opcode.h"
#include "qvector.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

AssemblyParser AssemblyParserFactory::create(string opcodeFile, string registerFile) {
    auto opcodeData = getJsonFromFile(opcodeFile);
    auto registerData = getJsonFromFile(registerFile);

    auto opcodes = OpcodeParser::parse(opcodeData);
    auto registers = RegisterParser::parse(registerData);

    return AssemblyParser(opcodes, registers);
}

json AssemblyParserFactory::getJsonFromFile(string filename) {
    return json::parse(getDataFromFile(filename));
}

string AssemblyParserFactory::getDataFromFile(string filename) {
    fstream fd(filename, ios_base::in);
    
    fd.seekg(0, ios_base::end);
    int length = fd.tellg();
    fd.seekg(0, ios_base::beg);

    char buf[length + 1];
    fd.read(buf, length);
    buf[length] = '\0';
    fd.close();

    return string(buf);
}
