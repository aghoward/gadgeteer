#include <vector>

#include "binaryfile.h"
#include "headers/elfheader.h"
#include "headers/programheader.h"
#include "headers/sectionheader.h"

using namespace std;

BinaryFile::BinaryFile(ElfHeader elf, vector<ProgramHeader> programHeaders, vector<SectionHeader> sectionHeaders) {
    this->elf_header = elf;
    this->program_headers = programHeaders;
    this->section_headers = sectionHeaders;
}
