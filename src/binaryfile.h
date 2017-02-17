#ifndef BinaryFile_H
#define BinaryFile_H

#include <memory>

#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "headers/sectionheader.h"

using namespace std;

class BinaryFile {
    public:
        shared_ptr<ElfHeader> elf_header;
        vector<shared_ptr<ProgramHeader>> program_headers;
        vector<shared_ptr<SectionHeader>> section_headers;

        BinaryFile() {};
        BinaryFile(shared_ptr<ElfHeader> elf, vector<shared_ptr<ProgramHeader>> programHeaders, vector<shared_ptr<SectionHeader>> sectionHeaders);
};

#endif
