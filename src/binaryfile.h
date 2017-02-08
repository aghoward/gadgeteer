#ifndef BinaryFile_H
#define BinaryFile_H

#include <memory>

#include "qvector.h"

#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "headers/sectionheader.h"

using namespace std;

class BinaryFile {
    public:
        shared_ptr<ElfHeader> elf_header;
        qvector<shared_ptr<ProgramHeader>> program_headers;
        qvector<shared_ptr<SectionHeader>> section_headers;

        BinaryFile() {};
        BinaryFile(shared_ptr<ElfHeader> elf, qvector<shared_ptr<ProgramHeader>> programHeaders, qvector<shared_ptr<SectionHeader>> sectionHeaders);
};

#endif
