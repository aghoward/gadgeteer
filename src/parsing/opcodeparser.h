#pragma once

#include <string>
#include <vector>

#include "opcode.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class OpcodeParser {
    private:
        static Opcode parseSingle(json modelData);
        static int getOpcode(json jsonData);
        static string getOperation(json jsonData);
        static vector<int> getOperandSizes(json jsonData);

    public:
        static vector<Opcode> parse(json jsonData);
};
