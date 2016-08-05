#ifndef ProgramHeader_H
#define ProgramHeader_H

#include <string>

#include "utils.h"

using namespace std;
using namespace utils;

class ProgramHeader {
    private:
        void deserialize32(fstream &fd, ENDIANESS endianess);
        void deserialize64(fstream &fd, ENDIANESS endianess);

    public:
        unsigned int type;
        unsigned int offset;
        unsigned int virtual_address;
        unsigned int physical_address;
        unsigned int file_size;
        unsigned int memory_size;
        unsigned int flags;
        unsigned int alignment;

        ProgramHeader(fstream &fd, BITNESS bitness, ENDIANESS endianess);
        string toString();
};

#endif
