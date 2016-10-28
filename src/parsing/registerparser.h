#ifndef RegisterParser_H
#define RegisterParser_H

#include <vector>

#include "qvector.h"
#include "json.hpp"
#include "register.h"

using namespace std;
using json = nlohmann::json;

class RegisterParser {
    private:
        static Register parseSingle(json jsonData);
    public:
        static qvector<Register> parse(json jsonData);
};

#endif
