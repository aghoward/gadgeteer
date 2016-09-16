#ifndef BinaryFile_H
#define BinaryFile_H

#include "qvector.h"

#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "headers/sectionheader.h"

using namespace std;

class BinaryFile {
    public:
        ElfHeader elf_header;
        qvector<ProgramHeader> program_headers;
        qvector<SectionHeader> section_headers;

        BinaryFile() {};
        BinaryFile(ElfHeader elf, qvector<ProgramHeader> programHeaders, qvector<SectionHeader> sectionHeaders);
};

#endif
