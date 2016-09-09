#ifndef ProgramHeader_H
#define ProgramHeader_H

#include <string>

#include "utils.h"

using namespace std;
using namespace utils;

enum PROGRAM_TYPE {
    PROG_NONE = 0x0,
    PROG_LOADABLE = 0x1,
    PROG_DYNAMIC = 0x2,
    PROG_INTERPRETER = 0x3,
    PROG_NOTE = 0x4,
    PROG_LIBRARY = 0x5,
    PROG_PROGRAMHEADER = 0x6,
    PROG_OSLOW = 0x60000000,
    PROG_OSHIGH = 0x6fffffff,
    PROG_PROCLOW = 0x70000000,
    PROG_PROCHIGH = 0x7fffffff
};

enum PROGRAM_FLAGS {
    PROG_EXECUTE = 0x1,
    PROG_WRITE = 0x2,
    PROG_READ = 0x4
};

class ProgramHeader {
    public:
        PROGRAM_TYPE type;
        unsigned int offset;
        unsigned int virtual_address;
        unsigned int physical_address;
        unsigned int file_size;
        unsigned int memory_size;
        unsigned int flags;
        unsigned int alignment;

        ProgramHeader() {};
        string toString();
};

#endif
