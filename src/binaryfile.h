#ifndef BinaryFile_H
#define BinaryFile_H

#include <vector>

#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "headers/sectionheader.h"

using namespace std;

class BinaryFile {
    public:
        ElfHeader elf_header;
        vector<ProgramHeader> program_headers;
        vector<SectionHeader> section_headers;

        BinaryFile() {};
        BinaryFile(ElfHeader elf, vector<ProgramHeader> programHeaders, vector<SectionHeader> sectionHeaders);
};

#endif
