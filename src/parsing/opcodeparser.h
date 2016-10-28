#ifndef OpcodeParser_H
#define OpcodeParser_H

#include <string>

#include "qvector.h"
#include "opcode.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class OpcodeParser {
    private:
        static Opcode parseSingle(json modelData);
        static int getOpcode(json jsonData);
        static string getOperation(json jsonData);
        static qvector<int> getOperandSizes(json jsonData);

    public:
        static qvector<Opcode> parse(json jsonData);
};

#endif
