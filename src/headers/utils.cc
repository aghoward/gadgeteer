#include <fstream>


#include <iostream>
using namespace std;

#include "utils.h"

namespace utils {
    unsigned long getBytes(fstream &fd, int num, ENDIANESS endianess) {
        char c;
        unsigned short curr = 0;
        unsigned long ret = 0;
        int shift = 0;

        for (int i = 0; i < num; i++) {
            c = (char)(fd.get());
            curr = (unsigned short)(c) & 0x00FF;

            shift = (endianess == ENDIAN_LITTLE) ? (i * BYTE) : ((num - i) * BYTE);

            ret += curr << shift;
        }

        return ret;
    }
}
