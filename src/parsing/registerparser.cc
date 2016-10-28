#include <string>
#include <vector>

#include "qvector.h"
#include "json.hpp"
#include "register.h"
#include "registerparser.h"

using namespace std;
using json = nlohmann::json;

qvector<Register> RegisterParser::parse(json jsonData) {
    auto ret = qvector<Register>();

    for (auto it = jsonData.begin(); it != jsonData.end(); it++)
        ret.push_back(parseSingle(*it));

    return ret;
}

Register RegisterParser::parseSingle(json jsonData) {
    auto ret = Register();
    ret.name = jsonData["name"];
    ret.value = jsonData["value"];
    return ret;
}
