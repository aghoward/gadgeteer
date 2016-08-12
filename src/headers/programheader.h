#ifndef ProgramHeader_H
#define ProgramHeader_H

#include <string>

#include "utils.h"

using namespace std;
using namespace utils;

enum PROGRAM_TYPE {
    NONE = 0x0,
    LOADABLE = 0x1,
    DYNAMIC = 0x2,
    INTERPRETER = 0x3,
    NOTE = 0x4,
    LIBRARY = 0x5,
    PROGRAMHEADER = 0x6,
    OSLOW = 0x60000000,
    OSHIGH = 0x6fffffff,
    PROCLOW = 0x70000000,
    PROCHIGH = 0x7fffffff
};

enum FLAGS {
    EXECUTE = 0x1,
    WRITE = 0x2,
    READ = 0x4
};

class ProgramHeader {
    private:
        void deserialize32(fstream &fd, ENDIANESS endianess);
        void deserialize64(fstream &fd, ENDIANESS endianess);

    public:
        PROGRAM_TYPE type;
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
