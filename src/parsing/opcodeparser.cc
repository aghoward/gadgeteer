#include <string>
#include <iostream>
#include <vector>

#include "opcodeparser.h"
#include "opcode.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

vector<Opcode> OpcodeParser::parse(json jsonData) {
    auto ret = vector<Opcode>();

    for (auto it = jsonData.begin(); it != jsonData.end(); it++)
        ret.push_back(parseSingle(*it));

    return ret;
}

Opcode OpcodeParser::parseSingle(json modelData) {
    auto model = Opcode();
    model.name = modelData["name"];
    model.opcode = getOpcode(modelData);
    model.operation = getOperation(modelData);
    model.operandSizes = getOperandSizes(modelData);
    return model;
}

int OpcodeParser::getOpcode(json jsonData) {
    string opcodeValue = jsonData["opcode"];
    return stoi(opcodeValue, NULL, 16);
}

string OpcodeParser::getOperation(json jsonData) {
    if (jsonData.find("operation") == jsonData.end())
        return "default";
    return jsonData["operation"];
}

vector<int> OpcodeParser::getOperandSizes(json jsonData) {
    auto sizes = vector<int>();
    if (jsonData.find("operandSizes") != jsonData.end())
        return sizes;

    auto node = jsonData["operandSizes"];
    for (auto it = node.begin(); it != node.end(); it++)
        sizes.push_back(*it);

    return sizes;
}
