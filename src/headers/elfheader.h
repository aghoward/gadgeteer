#ifndef ElfHeader_H
#define ElfHeader_H

#include <string>
#include <elf.h>
#include <sstream>
#include <fstream>

#include "utils.h"

using namespace std;

const int IDENT_CHARS = 0x10;

class ElfHeader {
    private:
        string getIdentity(fstream &fd);
        unsigned int getHalf(fstream &fd);
        unsigned long getWord(fstream &fd);
        void setBitness();
        void setEndianess();

    public:
        string ident;
        BITNESS bitness;
        ENDIANESS endianess;
        unsigned short type;
        unsigned short machine;
        unsigned int version;
        unsigned long entry;
        unsigned long program_offset;
        unsigned long section_offset;
        unsigned int flags;
        unsigned short program_size;
        unsigned short program_entry_size;
        unsigned short program_entry_count;
        unsigned short section_entry_size;
        unsigned short section_entry_count;
        unsigned short section_name_index;

        ElfHeader(fstream& fd);
        string toString();

        string getBitness();
        string getEndianess();
};

#endif
