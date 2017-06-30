#ifndef Utils_H
#define Utils_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

namespace utils {
    template<typename T> string to_hex(T value) {
        stringstream s;
        s << hex << "0x" << value;
        return string(s.str());
    }
}

#endif
