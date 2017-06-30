#pragma once

#include <vector>

#include "json.hpp"
#include "register.h"

using namespace std;
using json = nlohmann::json;

class RegisterParser {
    private:
        static Register parseSingle(json jsonData);
    public:
        static vector<Register> parse(json jsonData);
};
