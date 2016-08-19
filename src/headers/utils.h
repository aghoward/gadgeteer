#ifndef Utils_H
#define Utils_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

enum BITNESS {
    BITNESS_NONE = 0,
    BITNESS_32 = 1,
    BITNESS_64 = 2
};

enum ENDIANESS {
    ENDIAN_NONE = 0,
    ENDIAN_LITTLE = 1,
    ENDIAN_BIG = 2
};

const int BYTE = 8;

namespace utils {
    template<typename T> string to_hex(T value) {
        stringstream s;
        s << hex << "0x" << value;
        return string(s.str());
    }

    unsigned long getBytes(fstream &fd, int num, ENDIANESS endianess);
    string readString(fstream &fd);

    template<typename T> vector<T> where(vector<T> list, function<bool (T)> matches) {
        auto matching = vector<T>();
        for(auto it = list.begin(); it != list.end(); it++) {
            if (matches(*it))
                matching.push_back(*it);
        }
        return matching;
    }
}

#endif
