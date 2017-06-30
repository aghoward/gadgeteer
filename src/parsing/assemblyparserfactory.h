#pragma once

#include <string>

#include "assemblyparser.h"
#include "register.h"
#include "opcode.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class AssemblyParserFactory {
    private:
        static json getJsonFromFile(string filename);
        static string getDataFromFile(string filename);

    public:
        static AssemblyParser create(string opcodeFile, string registerFile);
};
