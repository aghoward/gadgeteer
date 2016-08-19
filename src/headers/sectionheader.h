#ifndef SectionHeader_H
#define SectionHeader_H

#include <string>
#include <fstream>

#include "programheader.h"

using namespace std;

enum SECTION_TYPE {
    SECT_NONE = 0,
    SECT_PROGRAM = 1,
    SECT_SYMBOL_TABLE = 2,
    SECT_STRING_TABLE = 3,
    SECT_RELOCATABLE_ADDENDS = 4,
    SECT_HASH_TABLE = 5,
    SECT_DYNAMIC = 6,
    SECT_NOTE = 7,
    SECT_NOBITS = 8,
    SECT_RELOCATABLE = 9,
    SECT_SHLIB = 10,
    SECT_DYNAMIC_SYMBOL = 11
};

enum SECTION_FLAGS {
    SECT_WRITE = 1,
    SECT_ALLOCATE = 2,
    SECT_EXECUTE = 4,
    SECT_PROCESSOR = 8
};

class SectionHeader {
    private:
        void deserialize(fstream &fd, int wordSize, ENDIANESS endianess);
        string getTypeName();
        string getFlagString();

    public:
        string name;
        unsigned int name_offset;
        unsigned int type;
        unsigned int flags;
        unsigned long address;
        unsigned long file_offset;
        unsigned long size;
        unsigned int link;
        unsigned int info;
        unsigned long address_alignment;
        unsigned long entity_size;
        string contents;

        SectionHeader(fstream &fd, BITNESS bitness, ENDIANESS endianess);
        string toString();
        string getContents(fstream &fd);
};

#endif
