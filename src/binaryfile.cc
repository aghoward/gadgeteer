#include <memory>

#include "qvector.h"

#include "binaryfile.h"
#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "headers/sectionheader.h"

using namespace std;

BinaryFile::BinaryFile(shared_ptr<ElfHeader> elf, qvector<shared_ptr<ProgramHeader>> programHeaders, qvector<shared_ptr<SectionHeader>> sectionHeaders) {
    this->elf_header = elf;
    this->program_headers = programHeaders;
    this->section_headers = sectionHeaders;
}
