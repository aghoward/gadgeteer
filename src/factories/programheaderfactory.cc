#include <fstream>
#include <vector>

#include "programheaderfactory.h"
#include "../headers/programheader.h"
#include "../headers/elfheader.h"

using namespace std;

vector<ProgramHeader> ProgramHeaderFactory::Create(fstream &fd, ElfHeader elf) {
    auto headers = vector<ProgramHeader>();

    for (auto i = 0; i < elf.program_entry_count; i++) {
        auto offset = elf.program_offset + (i * elf.program_entry_size);
        fd.seekg(offset);

        auto header = ProgramHeader(fd, elf.bitness, elf.endianess);
        headers.push_back(header);
    }

    return headers;
}
